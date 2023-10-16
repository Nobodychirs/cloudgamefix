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

int main(int argc,CHAR** argv)
{
	std::cout << "׼��cloudgamefix�ͻ����ļ�..." << "\n";
	std::cout << "��ʼ��ȡ�ļ��嵥..." << "\n";
	std::cout << "׼��curl��..." << "\n";
	Experiment::Curl curl;
	curl.setUrl("");
	curl.getJsonDomByRequest(Experiment::Curl::operation::GET);
	
	std::cout << "������־������..." << "\n";	
	if (!fs::exists(Dict))
	{
		fs::create_directories(Dict);
	}
	std::string path, file;
	cloudgameZero::Foundation::zeroLog object(true, "C:\\cloudgamefix\\updater.json", 
		[&path](rapidjson::Document& Dom) 
		{
			path = Dom["logToFile"]["Dictionary"].SetString("C:\\cloudgamefix").GetString();
			Dom["logToFile"]["File"]["filename"].SetString("${format}updater.log");
		});
	std::cout << "��־��Ϣ���洢�� -> {}Ŀ¼��.log��׺�����ļ���"_zF(path, file) << "\n";
	/* �ڴˣ����ǳ�ʼ����Ӧ�ó���Ļ���Ŀ¼����������������Ҫ����DLL���ļ����������ļ������û��������� */
	std::ifstream in("manifest_conf.json",std::ios::in);
	if (!in.is_open())
	{
		return -1;
	}
	in >> std::noskipws;
	std::string json_content((std::istream_iterator<char>(in)), std::istream_iterator<char>());
	rapidjson::Document Dom;
	Dom.Parse(json_content.c_str());
	if (Dom.HasParseError())
	{
		std::cout << "����json�ļ�ʧ��" << "\n";

	}
	auto array = Dom["files"].GetArray();
	std::string filename,filepath;
	for(auto& i : array)
	{
		filename = i["name"].GetString();
		filepath = std::format("{}{}", Dict, filename);
		if (!fs::exists(path))
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
	object.info("�����ļ��Ѿ��������!");
	object.info("����׼��Client");
	HRESULT hr = ::CoInitialize(NULL);
	if (FAILED(hr))
	{
		object.warn("�޷�׼����ݷ�ʽ!");
	}
	else
	{
		IShellLinkA* link{};
		IPersistFile* file{};
		do {
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
			LPITEMIDLIST pitemIlist;
			hr = SHGetSpecialFolderLocation(NULL, CSIDL_DESKTOP, &pitemIlist);
			if (FAILED(hr))
			{
				object.error("�޷���ѯ��Ŀ��·��!");
				break;
			}
			WCHAR TargetPath[MAX_PATH];
			ZeroMemory(TargetPath, MAX_PATH);
			SHGetPathFromIDList(pitemIlist, TargetPath);
			wcscat_s(TargetPath, wcslen(TargetPath) + 20, L"\\cloudgamefix.lnk");
			hr = link->QueryInterface(IID_IPersistFile, (void**)&file);
			if (FAILED(hr))
			{
				object.error("�޷������ļ�ʵ��!");
				break;
			}
			hr = file->Save(TargetPath,FALSE);
			if (FAILED(hr)) 
			{
				object.error("�޷�������ݷ�ʽ");
				break;
			}
			object.info("�ɹ�������ݷ�ʽ");
			file->Release();
			link->Release();
		} while (false);
	}
	object.info("��ɰ�װ");
	object.info("��ʼ����Client");
	ShellExecuteA(NULL, NULL, "{}{}"_zF(Dict,::filename).c_str(), NULL, NULL, SW_SHOW);
	return 0;
}