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

int main(int argc,CHAR** argv)
{
	std::cout << "��ʼ��ȡ�ļ��嵥..." << "\n";
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
	Experiment::Curl curl;
	std::ifstream in("manifest_conf.json",std::ios::in);
	if (!in.is_open())
	{
		return -1;
	}
	in >> std::noskipws;
	std::string json_content((std::istream_iterator<char>(in)), std::istream_iterator<char>());
	std::cout << json_content << "\n";
	rapidjson::Document Dom;
	Dom.Parse(json_content.c_str());
	if (Dom.HasParseError())
	{
		std::cout << "����json�ļ�ʧ��" << "\n";

	}
	auto array = Dom["files"].GetArray();
	for(auto& i : array)
	{
		std::string filename = i["name"].GetString();
		if (!fs::exists(filename))
		{
			object.info("��ʼ�����ļ���{}",filename);
			break;
		}
		auto sha1 = getFileSha1(i["name"].GetString());
		if (!(fs::file_size(filename) == i["check"]["size"].GetInt()))
		{
			object.warn("�ļ���{}��С��ʵ�ʲ�����",filename);
			break;
		}
		else if (!(sha1 == i["check"]["sha1"].GetString()))
		{
			object.warn("�ļ���{}У��õ�����֤�Ͳ�ƥ��!", filename);
			break;
		}
	}
	CL()->info("�����ļ��Ѿ��������!");
	//Experiment::Curl curl;
	//curl.setOperater(Experiment::Curl::operater::Request);
	//curl.setUrl("https://gitee.com");
	//auto Dom = curl.getJsonDomByRequest(Experiment::Curl::operation::GET);
	//std::string checkSha1 = Dom["files"]["main"]["sha1"].GetString();
	
}