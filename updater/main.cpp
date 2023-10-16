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
	std::cout << "开始获取文件清单..." << "\n";
	std::cout << "设置日志对象中..." << "\n";	
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
	std::cout << "日志信息将存储到 -> {}目录中.log后缀名的文件中"_zF(path, file) << "\n";
	/* 在此，我们初始化了应用程序的基础目录，接下来，我们需要下载DLL库文件，程序主文件，配置环境变量等 */
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
		std::cout << "解析json文件失败" << "\n";

	}
	auto array = Dom["files"].GetArray();
	for(auto& i : array)
	{
		std::string filename = i["name"].GetString();
		if (!fs::exists(filename))
		{
			object.info("开始下载文件：{}",filename);
			break;
		}
		auto sha1 = getFileSha1(i["name"].GetString());
		if (!(fs::file_size(filename) == i["check"]["size"].GetInt()))
		{
			object.warn("文件：{}大小与实际不符合",filename);
			break;
		}
		else if (!(sha1 == i["check"]["sha1"].GetString()))
		{
			object.warn("文件：{}校验得到的验证和不匹配!", filename);
			break;
		}
	}
	CL()->info("所有文件已经下载完毕!");
	//Experiment::Curl curl;
	//curl.setOperater(Experiment::Curl::operater::Request);
	//curl.setUrl("https://gitee.com");
	//auto Dom = curl.getJsonDomByRequest(Experiment::Curl::operation::GET);
	//std::string checkSha1 = Dom["files"]["main"]["sha1"].GetString();
	
}