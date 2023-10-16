#include "cgFix.h"

using namespace cloudgameZero;

CcgFix::CcgFix()
{
	this->path = {
		{origin,	"D:\\origin games"},
		{epic,	"D:\\EpicGames"},
		{steam,	"D:\\steamapps\\steamapps"},
		{uplay,	"D:\\uplay"}
	};
	this->path_After = {
		{origin,	"D:\\origin games1"},
		{epic,	"D:\\EpicGames1"},
		{steam,	"D:\\steamapps\\steamapps1"},
		{uplay,	"D:\\uplay1"}
	};
	this->path_Tran = {
		{origin,	"D:\\origin games_tran"},
		{epic,	"D:\\EpicGames_tran"},
		{steam,	"D:\\steamapps\\steamapps_tran"},
		{uplay,	"D:\\uplay_tran"}
	};
}

STDMETHODIMP CcgFix::fixSystem(int mode)
{
	cloudgameZero::log logs(true , "logConfig.json", [](rapidjson::Document& Dom) {
		Dom["outToTerminal"]["Enable"].SetBool(false);
		Dom["logToFile"]["File"]["filename"].SetString("${format}component_zero.log");
	},"cgFix","fix");
	logs.info("日志");
	return S_OK;
}

STDMETHODIMP CcgFix::fixFile(int mode)
{
	cloudgameZero::log logs(true, "logConfig.json", [](rapidjson::Document& Dom) {
		Dom["outToTerminal"]["Enable"].SetBool(false);
		Dom["logToFile"]["File"]["filename"].SetString("${format}component_zero.log");
		}, "cgFix", "fix");
	if (mode < cloudgame && mode > cloudpc)
	{
		return E_INVALIDARG;
	}
	bool has_WARN = false;
	std::vector<std::string> list = { ".reg",".bat",".cmd" };
	std::vector<std::string>::iterator it = list.begin();
	std::vector<std::string> value = { "regfile","batfile","cmdfile" };
	std::vector<std::string> error_List;
	for (std::vector<std::string>::iterator it = list.begin(), itr = value.begin(); it != list.end() && itr != value.end(); it++, itr++)
	{
		if (LSTATUS result = RegSetValueA(HKEY_CLASSES_ROOT, it->c_str(), REG_SZ, itr->c_str(), sizeof(REG_SZ)); result == ERROR_SUCCESS)
		{
			logs.info("成功修改HKEY_CLASSES_ROOT\\{}\\{}下的键值", *it, *itr);
		}
		else
		{
			CL()->warn("无法修改HKEY_CLASSES_ROOT\\{}\\{}下的键值", *it, *itr);
			has_WARN = true;
			error_List.push_back(*it);
		}
		Sleep(200);
	}
	if (has_WARN)
	{
		std::for_each(error_List.begin(), error_List.end(), [](std::string error) {std::cout << "错误出现在：" << error << std::endl; });
		CL()->info("由于在修复项中出现问题");
	}
	if (mode == cloudpc)
	{
		HKEY hkey = NULL;
		RegOpenKeyA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", &hkey);
		CL()->info("开始修改HKLM\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies下的数据");
		if (RegSetValueExW(hkey, L"EnableLUA", NULL, REG_DWORD, (BYTE*)"\0\x0000\000\0", sizeof(DWORD)) == ERROR_SUCCESS)
		{
			CL()->info("成功修改值，返回值为ERROR_SUCCESS");
			DEBUG_MESSAGE("成功修改值");
		}
		else
		{
			CL()->warn("无法修改值，返回值非ERROR_SUCCESS，权限似乎不足以修改，请联系开发者!");
			DEBUG_MESSAGE("修改失败");
		}
	}
	return S_OK;
}
