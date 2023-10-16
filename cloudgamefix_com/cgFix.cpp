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
	logs.info("��־");
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
			logs.info("�ɹ��޸�HKEY_CLASSES_ROOT\\{}\\{}�µļ�ֵ", *it, *itr);
		}
		else
		{
			CL()->warn("�޷��޸�HKEY_CLASSES_ROOT\\{}\\{}�µļ�ֵ", *it, *itr);
			has_WARN = true;
			error_List.push_back(*it);
		}
		Sleep(200);
	}
	if (has_WARN)
	{
		std::for_each(error_List.begin(), error_List.end(), [](std::string error) {std::cout << "��������ڣ�" << error << std::endl; });
		CL()->info("�������޸����г�������");
	}
	if (mode == cloudpc)
	{
		HKEY hkey = NULL;
		RegOpenKeyA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", &hkey);
		CL()->info("��ʼ�޸�HKLM\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies�µ�����");
		if (RegSetValueExW(hkey, L"EnableLUA", NULL, REG_DWORD, (BYTE*)"\0\x0000\000\0", sizeof(DWORD)) == ERROR_SUCCESS)
		{
			CL()->info("�ɹ��޸�ֵ������ֵΪERROR_SUCCESS");
			DEBUG_MESSAGE("�ɹ��޸�ֵ");
		}
		else
		{
			CL()->warn("�޷��޸�ֵ������ֵ��ERROR_SUCCESS��Ȩ���ƺ��������޸ģ�����ϵ������!");
			DEBUG_MESSAGE("�޸�ʧ��");
		}
	}
	return S_OK;
}
