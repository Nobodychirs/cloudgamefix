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
	object.info("��ʼ�����ļ���{}", filename);
	std::string url = Dom["repo"].GetString() + filename;
	object.info("�趨urlΪ�� {}", url);
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
					std::cout << "������ֻ����ѡ��Ĳ���" << "\n";
					break;
				}
				proxy = argList[static_cast<std::vector<std::string, std::allocator<std::string>>::size_type>(it) + 1];
			}
			it++;
		}
	}
	std::cout << "׼��cloudgamefix�ͻ����ļ�..." << "\n";
	std::cout << "��ʼ��ȡ�ļ��嵥..." << "\n";
	std::cout << "׼��curl��..." << "\n";
	Experiment::Curl curl;
	curl.init();
	curl.setOperater(Experiment::Curl::operater::Request);
	curl.setUrl(proxy + "manifest_conf.json");
	auto Dom = curl.getJsonDomByRequest(Experiment::Curl::operation::GET);
	curl.cleanup();
	std::cout << "�ɹ���ȡ�嵥�ļ�������ʵ����..." << "\n";
	std::cout << "׼����������Ŀ¼..." << "\n";
	if (!fs::exists(Dict))
	{
		std::cout << "Ŀ¼�����ڣ�׼������..." << "\n";
		fs::create_directories(Dict);
	}
	else
	{
		std::cout << "Ŀ¼�Ѵ��ڣ���������" << "\n";
	}
	std::cout << "������־������..." << "\n";
	std::string path, file;
	cloudgameZero::Foundation::zeroLog object(true, "C:\\cloudgamefix\\updater.json", 
		[&path](rapidjson::Document& Dom) 
		{
			path = Dom["logToFile"]["Dictionary"].SetString("C:\\cloudgamefix").GetString();
			Dom["logToFile"]["File"]["filename"].SetString("${format}updater.log");
		});
	std::cout << "��־��Ϣ���洢�� -> {}Ŀ¼��.log��׺�����ļ���"_zF(path, file) << "\n";
	object.info("��־����׼������!");
	if (!(Dom.HasMember("repo") && Dom["repo"].IsString()))
	{
		object.fatal("������ṩrepo�ṩ��������Ϊ������Ҫͨ��һ����ַ��ȡ����Ҫ���ļ�");
		PRESSANYBOTTON();
		return -1;
	}
	if (!(Dom.HasMember("files") && Dom["files"].IsArray()))
	{
		object.fatal("�����proxy������嵥�ļ������Ϲ淶�����޷�����!");
		PRESSANYBOTTON();
		return -1;
	}
	object.info("��ʼ��ȡ�ļ��б�");
	/* �ڴˣ����ǳ�ʼ����Ӧ�ó���Ļ���Ŀ¼����������������Ҫ����DLL���ļ����������ļ������û��������� */
	auto array = Dom["files"].GetArray();
	std::string filename,filepath;
	object.info("��ʼ�����Դ�����г�ʼ��...");
	for(auto& i : array)
	{
		filename = i["name"].GetString();
		filepath = std::format("{}{}", Dict, filename);
		if (!fs::exists(filepath))
		{
			object.info("��ʼ�����ļ���{}",filename);
			download(Dom, object, filename, filepath);
		}
		auto sha1 = getFileSha1(filepath);
		auto file_get_size = i["check"]["size"].GetInt();
		if (auto size = fs::file_size(filepath);size != file_get_size)
		{
			object.warn("�ļ���{}��С��ʵ�ʲ�����",filename);
			download(Dom, object, filename, filepath);
			size = fs::file_size(filepath);
			if (size != file_get_size)
			{
				std::cout << "�����޷��ɹ������ļ����뽫������㱨��������" << "\n";
				PRESSANYBOTTON();
				return -1;
			}
			
		}
		if (std::string real = i["check"]["sha1"].GetString();real != sha1)
		{
			object.warn("�ļ���{}У��õ�����֤�Ͳ�ƥ��!", filename);
			download(Dom, object, filename, filepath);
			if (real != sha1)
			{
				std::cout << "�����޷��ɹ������ļ����뽫������㱨��������" << "\n";
				PRESSANYBOTTON();
				return -1;
			}
		}
	}
	/* �������ǲ������Ӧ�ó���������ҪΪ���򴴽�һ����ݷ�ʽ */
	object.info("�����ļ��Ѿ���ȷ��!");
	object.info("����׼��Client");
	HRESULT hr = ::CoInitialize(NULL);
	do {
		LPITEMIDLIST pitemIlist{};
		hr = SHGetSpecialFolderLocation(NULL, CSIDL_DESKTOP, &pitemIlist);
		if (FAILED(hr))
		{
			object.error("�޷���ѯ��Ŀ��·��!");
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
				object.info("��ȷ���ļ����ڣ���������");
				break;
			}
		}
		if (FAILED(hr))
		{
			object.warn("�޷�׼����ݷ�ʽ!");
			break;
		}
		IShellLinkA* link{};
		IPersistFile* file{};
		object.info("��ʼ����ʵ������");
		hr = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLinkA, (void**)&link);
		if (FAILED(hr))
		{
			object.error("�޷�����ʵ��!");
			break;
		}
		std::string path = std::format("{}{}", Dict.data(), ::filename.data());
		hr = link->SetPath(path.c_str());
		if (FAILED(hr))
		{
			object.warn("�޷�����·��");
			break;
		}
		WCHAR _TargetPath[MAX_PATH];
		ZeroMemory(TargetPath, MAX_PATH);
		SHGetPathFromIDList(pitemIlist, _TargetPath);
		wcscat_s(_TargetPath, wcslen(_TargetPath) + 20, L"\\cloudgamefix.lnk");
		hr = link->QueryInterface(IID_IPersistFile, (void**)&file);
		if (FAILED(hr))
		{
			object.error("�޷������ļ�ʵ��!");
			break;
		}
		hr = file->Save(_TargetPath, FALSE);
		if (FAILED(hr))
		{
			object.error("�޷�������ݷ�ʽ");
			break;
		}
		object.info("�ɹ�������ݷ�ʽ");
		file->Release();
		link->Release();
	} while (false);
	object.info("��ɰ�װ");
	object.info("��ʼ����Client");
	//ShellExecuteA(NULL, NULL, "{}{}"_zF(Dict,::filename).c_str(), NULL, NULL, SW_SHOW);
	object.info("�������!");
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	return 0;
}