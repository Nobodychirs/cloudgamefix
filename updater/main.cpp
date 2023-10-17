#include"../cloudgamefix/cloudgamefix.hpp"

using namespace cloudgameZero;
using namespace cloudgameZero::Foundation::Tool;
using namespace cloudgameZero::Foundation::dynamincLibrayFunc::function;
using namespace cloudgameZero::Interface;
using namespace cloudgameZero::Interface::sigmaInterface::guid;
namespace ToastPlatformAPI = cloudgameZero::ToastPlatform::API;
namespace ToastPlatformEnums = cloudgameZero::ToastPlatform::Enums;

std::string_view Dict = "C:\\cloudgamefix\\";
std::string_view filename = "cloudgamefix.exe";
std::string_view session = "session.exe";
std::string_view moduleNameCurl = "libcurl.dll";
std::string_view moduleNameZLib = "zlib1.dll";

namespace fs = std::filesystem;

void download(rapidjson::Document& Dom,cloudgameZero::Foundation::zeroLog& object,std::string filename,std::string path)
{
	Experiment::Curl curl;
	object.info("开始下载文件：{}", filename);
	std::string url = Dom["repo"].GetString() + filename;
	object.info("设定url为： {}", url);
	curl.init();
	curl.setUrl(url);
	curl.setOperater(Experiment::Curl::operater::Download);
	curl.sendDownloadRequest(Experiment::Curl::operation::GET, path, true);
	curl.cleanup();
}

INT main(INT argc,CHAR** argv)
{
	std::string proxy = "https://gitee.com/eGlhb2p1emk/cloudgamefix/raw/develop/static/";
	if (argc > 1)
	{
		auto argList = Experiment::makeArgumentsView(argc,argv);
		int it = 0;
		for (auto& i : argList)
		{
			if (i == "--proxy")
			{
				if (it == argc)
				{
					std::cout << "不接受只带有选项的参数" << "\n";
					break;
				}
				proxy = argList[static_cast<std::vector<std::string, std::allocator<std::string>>::size_type>(it) + 1];
			}
			it++;
		}
	}
	std::cout << "准备cloudgamefix客户端文件..." << "\n";
	std::cout << "开始获取文件清单..." << "\n";
	std::cout << "准备curl中..." << "\n";
	Experiment::Curl curl;
	curl.init();
	curl.setOperater(Experiment::Curl::operater::Request);
	curl.setUrl(proxy + "manifest_conf.json");
	auto Dom = curl.getJsonDomByRequest(Experiment::Curl::operation::GET);
	curl.cleanup();
	std::cout << "成功获取清单文件，清理实例中..." << "\n";
	std::cout << "准备创建程序目录..." << "\n";
	if (!fs::exists(Dict))
	{
		std::cout << "目录不存在，准备创建..." << "\n";
		fs::create_directories(Dict);
	}
	else
	{
		std::cout << "目录已存在，跳过创建" << "\n";
	}
	std::cout << "设置日志对象中..." << "\n";
	std::string path, file;
	cloudgameZero::Foundation::zeroLog object(true, "C:\\cloudgamefix\\updater.json", 
		[&path](rapidjson::Document& Dom) 
		{
			path = Dom["logToFile"]["Dictionary"].SetString("C:\\cloudgamefix").GetString();
			Dom["logToFile"]["File"]["filename"].SetString("${format}updater.log");
		});
	std::cout << "日志信息将存储到 -> {}目录中.log后缀名的文件中"_zF(path, file) << "\n";
	object.info("日志对象准备就绪!");
	if (!(Dom.HasMember("repo") && Dom["repo"].IsString()))
	{
		object.fatal("你必须提供repo提供给程序，因为程序需要通过一个网址获取到需要的文件");
		PRESSANYBOTTON();
		return -1;
	}
	if (!(Dom.HasMember("files") && Dom["files"].IsArray()))
	{
		object.fatal("错误的proxy，如果清单文件不符合规范，则无法解析!");
		PRESSANYBOTTON();
		return -1;
	}
	object.info("开始获取文件列表");
	/* 在此，我们初始化了应用程序的基础目录，接下来，我们需要下载DLL库文件，程序主文件，配置环境变量等 */
	auto array = Dom["files"].GetArray();
	std::string filename,filepath;
	object.info("开始检查资源，进行初始化...");
	for(auto& i : array)
	{
		filename = i["name"].GetString();
		filepath = std::format("{}{}", Dict, filename);
		if (!fs::exists(filepath))
		{
			object.info("开始下载文件：{}",filename);
			download(Dom, object, filename, filepath);
		}
		auto sha1 = getFileSha1(filepath);
		auto file_get_size = i["check"]["size"].GetInt();
		if (auto size = fs::file_size(filepath);size != file_get_size)
		{
			object.warn("文件：{}大小与实际不符合",filename);
			download(Dom, object, filename, filepath);
			size = fs::file_size(filepath);
			if (size != file_get_size)
			{
				std::cout << "程序无法成功下载文件，请将此情况汇报给开发者" << "\n";
				PRESSANYBOTTON();
				return -1;
			}
			
		}
		if (std::string real = i["check"]["sha1"].GetString();real != sha1)
		{
			object.warn("文件：{}校验得到的验证和不匹配!", filename);
			download(Dom, object, filename, filepath);
			if (real != sha1)
			{
				std::cout << "程序无法成功下载文件，请将此情况汇报给开发者" << "\n";
				PRESSANYBOTTON();
				return -1;
			}
		}
	}
	/* 这里我们部署好了应用程序，我们需要为程序创建一个快捷方式 */
	object.info("所有文件已经已确认!");
	object.info("正在准备Client");
	HRESULT hr = ::CoInitialize(NULL);
	do {
		LPITEMIDLIST pitemIlist{};
		hr = SHGetSpecialFolderLocation(NULL, CSIDL_DESKTOP, &pitemIlist);
		if (FAILED(hr))
		{
			object.error("无法查询到目标路径!");
			break;
		}
		CHAR TargetPath[MAX_PATH];
		ZeroMemory(TargetPath, MAX_PATH);
		SHGetPathFromIDListA(pitemIlist, TargetPath);
		if (TargetPath)
		{
			std::string path = TargetPath;
			path += "\\cloudgamefix.lnk";
			if (fs::exists(path))
			{
				object.info("已确认文件存在，跳过创建");
				break;
			}
		}
		if (FAILED(hr))
		{
			object.warn("无法准备快捷方式!");
			break;
		}
		IShellLinkA* link{};
		IPersistFile* file{};
		object.info("开始创建实例对象");
		hr = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLinkA, (void**)&link);
		if (FAILED(hr))
		{
			object.error("无法创建实例!");
			break;
		}
		std::string path = std::format("{}{}", Dict.data(), ::filename.data());
		hr = link->SetPath(path.c_str());
		if (FAILED(hr))
		{
			object.warn("无法设置路径");
			break;
		}
		WCHAR _TargetPath[MAX_PATH];
		ZeroMemory(TargetPath, MAX_PATH);
		SHGetPathFromIDList(pitemIlist, _TargetPath);
		wcscat_s(_TargetPath, wcslen(_TargetPath) + 20, L"\\cloudgamefix.lnk");
		hr = link->QueryInterface(IID_IPersistFile, (void**)&file);
		if (FAILED(hr))
		{
			object.error("无法创建文件实例!");
			break;
		}
		hr = file->Save(_TargetPath, FALSE);
		if (FAILED(hr))
		{
			object.error("无法创建快捷方式");
			break;
		}
		object.info("成功创建快捷方式");
		file->Release();
		link->Release();
	} while (false);
	object.info("完成安装");
	object.info("开始拉起Client");
	//ShellExecuteA(NULL, NULL, "{}{}"_zF(Dict,::filename).c_str(), NULL, NULL, SW_SHOW);
	object.info("启动完成!");
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	return 0;
}