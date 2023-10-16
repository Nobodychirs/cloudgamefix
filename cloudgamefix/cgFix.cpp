#include "cgFix.h"
#pragma once
/*�ڲ�ʵ��*/
using namespace cloudgameZero;
using namespace cloudgameZero::ToastPlatform;
using namespace cloudgameZero::ToastPlatform::API;
using namespace cloudgameZero::Interface;
using namespace cloudgameZero::Interface::Exceptions;
using namespace cloudgameZero::Interface::sigmaInterface;
using namespace cloudgameZero::Interface::sigmaInterface::guid;
using namespace cloudgameZero::Interface::sigmaInterface::Implement;

namespace cloudgameZero
{
	namespace Interface 
	{
		namespace sigmaInterface
		{
			namespace Implement
			{
				class __cgFix : virtual public cgFix
				{
				public:
					__cgFix();
					virtual ~__cgFix();
					virtual HRESULT QueryInterface(const IID& iid, void** ppv) override;
					virtual ULONG AddRef() override;
					virtual ULONG Release() override;
					virtual BOOL fixSystem(_In_ mode mode) override;
					virtual void fixFile(_In_ mode mode) override;
					virtual void resetGroupPolicy() override;
					virtual HRESULT repairGameFile() override;
				private:
					ULONG ref = 0;
					__cgFix(__cgFix& other) = delete;
					cgFix& operator=(cgFix& other) = delete;
					enum game_file_m { origin, epic, steam, uplay };
					std::map<int, std::string> path;
					std::map<int, std::string> path_Tran;
					std::map<int, std::string> path_After;
				};

				class __cgSystem : public cgSystem, __cgFix
				{
				public:
					__cgSystem() = default;
					virtual ~__cgSystem() = default;
					virtual HRESULT QueryInterface(const IID& iid, void** ppv) override;
					virtual ULONG AddRef() override;
					virtual ULONG Release() override;
					virtual void setWallpaper(IN const std::string& path) override;
					virtual void downloadWallpaperAndSet(IN const std::string& url, IN const std::string path) override;
					virtual void changeResolution(IN short length, IN short width) override;
					virtual void changeResolution_s(IN Resolution resolution) override;
					virtual void changeTheme(IN Theme theme) override;
					virtual BOOL fixSystem(_In_ mode mode) override {
						return __cgFix::fixSystem(mode);
					}
					virtual void fixFile(_In_ mode mode) override {
						return __cgFix::fixFile(mode);
					}
					virtual void resetGroupPolicy() override {
						return __cgFix::resetGroupPolicy();
					}
					virtual HRESULT repairGameFile() override {
						return __cgFix::repairGameFile();
					}
				private:
					ULONG ref = 0;
					__cgSystem(__cgSystem& other) = delete;
					cgSystem& operator=(cgSystem& other) = delete;
				};
			}

			namespace guid
			{
				extern "C++" IID const IID_CLOUDGAME_FIX_ZERO_CGFIX = { 0x56E77AA7,0xB6E0,0xACCB,{0x43,0x14,0x32,0xD4,0x33,0x03,0x02,0x9A} };
				extern "C++" IID const IID_CLOUDGAME_FIX_ZERO_CGSYSTEM = { 0xfee66767, 0xdacd, 0x48fb, { 0xa2, 0xfa, 0x17, 0x19, 0x4e, 0xad, 0x75, 0xc6 } };
			}
		}

		extern "C++" IUnknown * cgSystemCreateInstance()
		{
			IUnknown* ptr = dynamic_cast<cgSystem*>(new __cgSystem);
			ptr->AddRef();
			return ptr;
		}
	}
}

#pragma region Interface
HRESULT __cgSystem::QueryInterface(const IID& iid, void** ppv)
{
	if (iid == IID_CLOUDGAME_FIX_ZERO_CGFIX) {
		*ppv = dynamic_cast<cgFix*>(new __cgFix);
	}
	else if (iid == IID_CLOUDGAME_FIX_ZERO_CGSYSTEM){
		*ppv = dynamic_cast<cgSystem*>(new __cgSystem);
	}
	else {
		*ppv = NULL;
		return E_NOINTERFACE;
	}
	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return S_OK;
}

ULONG cloudgameZero::Interface::sigmaInterface::Implement::__cgSystem::AddRef()
{
	this->ref++;
	return this->ref;
}

ULONG __cgSystem::Release()
{
	if (this->ref--; this->ref == 0) {
		delete this;
	}
	else {
		return this->ref;
	}
	return NULL;
}
void __cgSystem::setWallpaper(IN const std::string& path)
{
}
void __cgSystem::downloadWallpaperAndSet(IN const std::string& url, IN const std::string path)
{
}
void __cgSystem::changeResolution(IN short length, IN short width)
{
}
void __cgSystem::changeResolution_s(IN Resolution resolution)
{
}
void __cgSystem::changeTheme(IN Theme theme)
{
}

HRESULT  __cgFix::QueryInterface(const IID& iid, void** ppv)
{
	DEBUG_MESSAGE("�����ڳ��Ե���cgFix��QueryInterface��Ȼ��cgSystemCreateInstance�Ѿ��ṩ�˲�ѯ");
	return E_FAIL;
}

ULONG  __cgFix::AddRef()
{
	this->ref++;
	return this->ref;
}
#pragma endregion
#pragma region __CGFIX_METHOD
__cgFix::__cgFix()
{
	if (!zeroLog::Instance()->IsInit()){
		zeroLog::Instance()->Init();
	}
	this->path = {
		{this->origin,	"D:\\origin games"},
		{this->epic,	"D:\\EpicGames"},
		{this->steam,	"D:\\steamapps\\steamapps"},
		{this->uplay,	"D:\\uplay"}
	};
	this->path_After = {
		{this->origin,	"D:\\origin games1"},
		{this->epic,	"D:\\EpicGames1"},
		{this->steam,	"D:\\steamapps\\steamapps1"},
		{this->uplay,	"D:\\uplay1"}
	};
	this->path_Tran = {
		{this->origin,	"D:\\origin games_tran"},
		{this->epic,	"D:\\EpicGames_tran"},
		{this->steam,	"D:\\steamapps\\steamapps_tran"},
		{this->uplay,	"D:\\uplay_tran"}
	};
}

__cgFix::~__cgFix()
{
	if (!this->path.empty()){
		this->path.clear();
	}
	if (!this->path_Tran.empty()){
		this->path_Tran.clear();
	}
	if (!this->path_After.empty()){
		this->path_After.clear();
	}
	return;
}

ULONG  __cgFix::Release()
{
	if (this->ref--; this->ref == 0) {
		delete this;
	}
	else {
		return this->ref;
	}
	return NULL;
}

BOOL  __cgFix::fixSystem(_In_ mode mode)
{
	bool has_Error = false;
	if (mode == mode::reserved)
	{
		zeroLog::Instance()->write(FATAL, "����Ĵ��Σ��������յ�reserved");
		zeroLog::Instance()->write(FATAL, "��⵽�쳣��std::invalid_argument ׼���ر�Object");
		throw reservedArgs("����Ĵ��Σ��ú���������cloudpc,cloudgame����������������һ����������Ӧ��Ϊreserved");
	}
	else
	{
		zeroLog::Instance()->write(Info, "��ʼ�޸�ϵͳ");
		zeroLog::Instance()->write(Info, "��ʼɾ������");
		zeroLog::Instance()->write(Info, "׼�����غ���");
		std::stringstream stream;
		LSTATUS(WINAPI * RegDelete)(HKEY hkey, LPCSTR lpsubkey);
		if (SUCCEEDED(Foundation::dynamincLibrayFunc::loadFunFromLib(cloudgameZero::Foundation::dynamincLibrayFunc::KERNEL, "RegDeleteTreeA", RegDelete)))
		{
			stream << "�ɹ����غ��������ַΪ" << RegDelete;
			zeroLog::Instance()->write(Info, stream.str().c_str());
		}
		else
		{
			stream << "�޷����غ�����ַ������ʧ��";
			zeroLog::Instance()->write(FATAL, stream.str().c_str());
			return ERROR;
		}
		std::stack<LPCSTR> HKCU;
		zeroLog::Instance()->write(Info, "��ʼ��ջ");
		zeroLog::Instance()->write(Info, "��ʼ��ջѹ������");
		if (mode == mode::cloudgame)
		{
			HKCU.push("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer");
			HKCU.push("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System");
			HKCU.push("Software\\Policies\\Microsoft\\MMC");
			HKCU.push("Software\\Policies\\Microsoft\\Edge");
		}
		else
		{
			HKCU.push("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer");
			HKCU.push("Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System");
			HKCU.push("Software\\Policies");
		}
		zeroLog::Instance()->write(Info, "��ջ���");
		zeroLog::Instance()->write(Info, "�ɹ�����������HKCU�µ�ջ");
		Sleep(1000);
		zeroLog::Instance()->write(Info, "׼������whileѭ��...");
		Sleep(500);
		zeroLog::Instance()->write(Info, "׼����ջ�߳�");
		ThreadPlatform threads([&HKCU, &RegDelete, &has_Error]()
			{
				while (!HKCU.empty())
				{
					std::string temp = HKCU.top();
					if (LSTATUS error = RegDelete(cloudgameZero::Infomation::HKCU, HKCU.top()) != ERROR_SUCCESS) {
						zeroLog::Instance()->write(WARN, std::format("��ɾ��: HKEY_CURRENT_USER\\{}ʱ��������,�����Ϊ: {}", temp, zeroLog::formatErrorMessage(error)).c_str());
						has_Error = true;
					}
					else {
						zeroLog::Instance()->write(Info, std::format("�ɹ�ɾ��: HKEY_CURRENT_USER\\{}", temp).c_str());
					}
					HKCU.pop();
				}
			});
		threads.Start();
		zeroLog::Instance()->write(Info, "�������");
		zeroLog::Instance()->write(Info, "׼���޸��������񣬲�����ʣ�µĺ���");
		zeroLog::Instance()->write(Info, "��ʼ�޸�����...");
		Sleep(500);
		char public_path[10] = "E:\\Builds";
		if (mode == mode::cloudpc)
		{
			zeroLog::Instance()->write(logLevel::Info, "ģʽ�� �Ƶ���");
			DEBUG_MESSAGE("������ֹexplorer.exe");
			zeroLog::Instance()->write(logLevel::Info, "������ֹexplorer.exe...");
			ShellExecuteA(NULL, "open", "taskkill", " /f /im explorer.exe", NULL, SW_HIDE);
			Sleep(1000);
			DEBUG_MESSAGE("��������explorer.exe");
			zeroLog::Instance()->write(logLevel::Info, "��������explorer.exe...");
			ShellExecuteA(NULL, "open", "explorer.exe", NULL, NULL, SW_NORMAL);
			threads.StopThread();
			RegDelete = nullptr;
			return has_Error;
		}
		else if (mode == mode::cloudgame)
		{
			zeroLog::Instance()->write(logLevel::Info, "ģʽ�� ����Ϸ");
			DEBUG_MESSAGE("������ֹDesktopMgr64.exe");
			zeroLog::Instance()->write(logLevel::Info, "������ֹDesktopMgr64.exe", false);
			ShellExecuteA(NULL, "open", "taskkill", " /f /im DesktopMgr64.exe", NULL, SW_HIDE);
			DEBUG_MESSAGE("������ֹexplorer.exe");
			zeroLog::Instance()->write(logLevel::Info, "������ֹexplorer.exe", false);
			Sleep(1000);
			ShellExecuteA(NULL, "open", "taskkill", " /f /im explorer.exe", NULL, SW_HIDE);
			DEBUG_MESSAGE("��������explorer.exe");
			zeroLog::Instance()->write(logLevel::Info, "��������explorer.exe", false);
			Sleep(1000);
			ShellExecuteA(NULL, "open", "explorer.exe", NULL, NULL, SW_NORMAL);
			threads.StopThread();
			RegDelete = nullptr;
			return has_Error;
		}
		else
		{
			return FALSE;
		}
		return FALSE;
	}
	return 0;
}

void  __cgFix::fixFile(_In_ mode mode)
{
	zeroLog::Instance()->write(logLevel::Info, "�����뺯���� fix_file", false);
	switch (mode)
	{
	case mode::cloudgame:
	{
		std::cout << "��ʼ�޸��ļ�����" << std::endl;
		bool has_WARN = false;
		std::vector<std::string> list = { ".reg",".bat",".cmd" };
		std::vector<std::string>::iterator it = list.begin();
		std::vector<std::string> value = { "regfile","batfile","cmdfile" };
		std::vector<std::string> error_List;
		for (std::vector<std::string>::iterator it = list.begin(), itr = value.begin(); it != list.end() && itr != value.end(); it++, itr++)
		{
			if (LSTATUS result = RegSetValueA(HKEY_CLASSES_ROOT, it->c_str(), REG_SZ, itr->c_str(), sizeof(REG_SZ)); result == ERROR_SUCCESS)
			{
				zeroLog::Instance()->write(logLevel::Info, std::format("�ɹ��޸�HKEY_CLASSES_ROOT\\{}\\{}�µļ�ֵ", *it, *itr).c_str());
			}
			else
			{
				zeroLog::Instance()->write(logLevel::Error, std::format("�޷��޸�HKEY_CLASSES_ROOT\\{}\\{}�µļ�ֵ��������Ϣ��{}", *it, *itr, zeroLog::formatErrorMessage(result)).c_str());
				DEBUG_MESSAGE(std::format("�޷��޸�HKEY_CLASSES_ROOT\\{}\\{}�µļ�ֵ", *it, *itr).c_str());
				has_WARN = true;
				error_List.push_back(*it);
			}
			Sleep(200);
		}
		if (has_WARN)
		{
			std::for_each(error_List.begin(), error_List.end(), [](std::string error) {std::cout << "��������ڣ�" << error << std::endl; });
			std::cout << "�����Ǵ��������" << std::endl;
			zeroLog::Instance()->write(logLevel::WARN, "�������޸����г�������");
			return;
		}
		zeroLog::Instance()->write(logLevel::Info, "�޸���ɣ�");
		return;
	}
	case mode::cloudpc:
	{
		HKEY hkey = NULL;
		RegOpenKeyA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", &hkey);
		zeroLog::Instance()->write(logLevel::Info, "��ʼ�޸�HKLM\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies�µ�����");
		if (RegSetValueExW(hkey, L"EnableLUA", NULL, REG_DWORD, (BYTE*)"\0\x0000\000\0", sizeof(DWORD)) == ERROR_SUCCESS)
		{
			zeroLog::Instance()->write(logLevel::Info, "�ɹ��޸�ֵ������ֵΪERROR_SUCCESS");
			DEBUG_MESSAGE("�ɹ��޸�ֵ");
		}
		else
		{
			zeroLog::Instance()->write(logLevel::WARN, "�޷��޸�ֵ������ֵ��ERROR_SUCCESS��Ȩ���ƺ��������޸ģ�����ϵ������!");
			DEBUG_MESSAGE("�޸�ʧ��");
		}
		return;
	}
	case mode::reserved:
	{
		zeroLog::Instance()->write(FATAL, "���󣬺�����������reserved");
		throw reservedArgs("reserved�Ǳ����Ĳ���������ʹ��");
		break;
	}
	default:
	{
		zeroLog::Instance()->write(logLevel::WARN, "���棬δ�������");
		break;
	}
	}
}

void  __cgFix::resetGroupPolicy()
{
	ToastTemplate toast(Enums::Text02);
	API::ToastNotification object;
	object.setAppUserModelId(cloudgameZero::Infomation::AUMI);
	object.setAppName(cloudgameZero::Infomation::APPNAME);
	object.Init();
	if (std::filesystem::exists("E:\\Builds"))
	{
		zeroLog::Instance()->write(logLevel::Info, "����ʵ������Ϊʵ��ģʽΪcloudgame", false);
		DEBUG_MESSAGE("����ʵ������Ϊʵ��ģʽΪcloudgame");
		return;
	}
	else
	{
		toast.setSecondLine(L"���ִ���Ϣ��ζ�ų��������ָ����Һ����Ѿ����");
		toast.setFirstLine(L"������������ָ��");
	}
	zeroLog::Instance()->write(logLevel::Info, "�����뺯���� reset_Group_Policy", false);
	zeroLog::Instance()->write(logLevel::Info, "׼��ɾ������Ե��ļ�", false);
	uintmax_t group = std::filesystem::remove_all("C:\\Windows\\System32\\GroupPolicy");
	Sleep(1000);
	uintmax_t groupUser = std::filesystem::remove_all("C:\\Windows\\System32\\GroupPolicyUsers");
	Sleep(1000);
	zeroLog::Instance()->write(logLevel::Info, std::format("�ɹ�ɾ��GroupPolicy{}���ļ�",group).c_str(), false);
	zeroLog::Instance()->write(logLevel::Info, std::format("�ɹ�ɾ��GroupPolicyUsers{}���ļ�",groupUser).c_str(), false);
	zeroLog::Instance()->write(logLevel::Info, "��ʼִ������ָ��", false);
	ShellExecuteA(NULL, "open", "cmd.exe", " /c gpupdate /force", NULL, SW_HIDE);
	zeroLog::Instance()->write(logLevel::Info, "�ɹ���ɵ���", false);
	object.show(toast,new API::PreDefineHandler);
	return;
}

HRESULT  __cgFix::repairGameFile()
{
	using logLevel::Info;
	using logLevel::WARN;
	bool has_Warn = false;
	for (
		std::map<INT, std::string>::iterator i = this->path.begin(), it = this->path_Tran.begin(), itr = this->path_After.begin();
		i != this->path.end() && it != this->path_Tran.end() && itr != this->path_After.end();
		i++, itr++, it++
		)
	{
		Sleep(250);
		if (!std::rename(i->second.c_str(), itr->second.c_str()))
		{
			zeroLog::Instance()->write(Info, std::format("�ɹ�������: {} -> {}",i->second,itr->second).c_str());
		}
		else
		{
			zeroLog::Instance()->write(WARN, std::format("��������: {} Ϊ {}ʱ��������",i->second,itr->second).c_str());
			has_Warn = true;
		}
		Sleep(500);
		if (!std::rename(it->second.c_str(), i->second.c_str()))
		{
			zeroLog::Instance()->write(Info, std::format("�ɹ�������: {} -> {}", it->second, i->second).c_str());
		}
		else
		{
			zeroLog::Instance()->write(Info, std::format("�ɹ�������: {} -> {}", it->second, i->second).c_str());
			has_Warn = true;
		}
		Sleep(250);
	}
	if (!has_Warn)
	{
		return S_OK;
	}
	else
	{
		return E_FAIL;
	}
}

#pragma endregion