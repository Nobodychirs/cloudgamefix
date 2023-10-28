#include "cloudgamefix.hpp"

using namespace cloudgameZero::Interface::sigmaInterface::Implement;
using namespace cloudgameZero::Interface::sigmaInterface::guid;
using namespace cloudgameZero::Interface;
using namespace cloudgameZero::ToastPlatform;
using namespace cloudgameZero;

#define MakeCloudgameComponent(x) class DECLSPEC_UUID(x) DECLSPEC_NOVTABLE

namespace cloudgameZero
{
	namespace Interface
	{
		namespace sigmaInterface
		{
			namespace Implement
			{
				class __cgFix : public cgFix
				{
				public:
					__cgFix() = default;
					virtual ~__cgFix() = default;
					virtual HRESULT QueryInterface(const IID& iid, void** ppv) override;
					virtual ULONG AddRef() override;
					virtual ULONG Release() override;
					virtual BOOL fixSystem() override;
					virtual void fixFile(_In_ mode mode) override;
					virtual void resetGroupPolicy() override;
					virtual HRESULT repairGameFile() override;
					enum game_file_m { origin, epic, steam, uplay };
				private:
					ULONG ref = 0;
					__cgFix(const __cgFix& other) = delete;
					cgFix& operator=(cgFix& other) = delete;
					std::mutex mtx;
				};

				class __cgSystem : public cgSystem,public __cgFix
				{
				public:
					__cgSystem() = default;
					virtual ~__cgSystem() = default;
					virtual HRESULT QueryInterface(const IID& iid, void** ppv) override;
					virtual ULONG AddRef() override;
					virtual ULONG Release() override;
					virtual void setWallpaper(IN const std::string& path);
					virtual void downloadWallpaperAndSet(IN const std::string& url, IN const std::string path) override;
					virtual void changeResolution(IN short length, IN short height) override;
					virtual void changeTheme(IN Theme theme);
					virtual BOOL fixSystem() override;
					virtual void fixFile(_In_ mode mode) override;
					virtual void resetGroupPolicy() override;
					virtual HRESULT repairGameFile() override;
				private:
					ULONG ref = 0;
					__cgSystem(const __cgSystem& other) = delete;
					cgSystem& operator=(cgSystem& other) = delete;
					std::mutex mtx;
				};

			    MakeCloudgameComponent("20C48CAD-6744-403E-8ED5-34F3F65F533E")
				__cgToolA_s : virtual public cgToolA
				{

				};

				
			}

			inline namespace guid
			{
				extern const IID IID_CLOUDGAME_FIX_ZERO_IID_IcgFix = __uuidof(cgFix);
				extern const IID IID_CLOUDGAME_FIX_ZERO_IID_IcgSystem = __uuidof(cgSystem);
				extern const IID IID_CLOUDGAME_FIX_ZERO_IID_IcgToolA = __uuidof(cgToolA);
				extern const IID IID_CLOUDGAME_FIX_ZERO_IID_IcgToolW = __uuidof(cgToolW);
				extern const IID IID_CLOUDGAME_FIX_ZERO_IID_IcgToolA_s = __uuidof(__cgToolA_s);

				//This function is normally called by the createInstance function, which takes a uuid and compares it to the corresponding IUnknown pointer
				extern IUnknown* Query(const IID& iid)
				{
					if (iid == IID_CLOUDGAME_FIX_ZERO_IID_IcgFix)
					{
						return new __cgFix;
					}
					else if (iid == IID_CLOUDGAME_FIX_ZERO_IID_IcgSystem)
					{
						cgSystem* ptr = new __cgSystem;
						return ptr;
					}
					else 
					{
						return nullptr;
					}
				}
			}

			//HRESULT createInstance(const GUID iid, void** ppv)
			//{
			//	IUnknown* ptr = Query(iid);
			//	if (!ptr)
			//	{
			//		*ppv = nullptr;
			//		return E_NOINTERFACE; // No such interface is available.
			//	}
			//	HRESULT hr = ptr->QueryInterface(iid, ppv); // Query for the requested interface using QueryInterface method.
			//	if (FAILED(hr))
			//	{
			//		*ppv = nullptr;
			//		return hr; // Failed to obtain the requested interface.
			//	}
			//	reinterpret_cast<IUnknown*>(*ppv)->AddRef();// Increase the reference count of the obtained interface to manage its lifetime.
			//	ptr->Release();	// Release the initial IUnknown pointer to avoid memory leaks.
			//	return S_OK;	// Success, the interface has been created and is ready for use.
			//}
		}
	}
}

//HRESULT Interface::createInstance(_In_ const GUID iid, _Outptr_ void** ppv)
//{
//	IUnknown* ptr = Query(iid);
//	if (!ptr)
//	{
//		*ppv = nullptr;
//		return E_NOINTERFACE; // No such interface is available.
//	}
//	HRESULT hr = ptr->QueryInterface(iid, ppv); // Query for the requested interface using QueryInterface method.
//	if (FAILED(hr))
//	{
//		*ppv = nullptr;
//		return hr; // Failed to obtain the requested interface.
//	}
//	reinterpret_cast<IUnknown*>(*ppv)->AddRef();// Increase the reference count of the obtained interface to manage its lifetime.
//	ptr->Release();	// Release the initial IUnknown pointer to avoid memory leaks.
//	return S_OK;	// Success, the interface has been created and is ready for use.
//}

static std::map<int, std::string> path = {
		{__cgFix::origin,	"D:\\origin games"},
		{__cgFix::epic,		"D:\\EpicGames"},
		{__cgFix::steam,	"D:\\steamapps\\steamapps"},
		{__cgFix::uplay,	"D:\\uplay"}
};
static std::map<int, std::string> path_Tran = {
		{__cgFix::origin,		"D:\\origin games1"},
		{__cgFix::epic,			"D:\\EpicGames1"},
		{__cgFix::steam,		"D:\\steamapps\\steamapps1"},
		{__cgFix::uplay,		"D:\\uplay1"}
};
static std::map<int, std::string> path_After = {
		{__cgFix::origin,	"D:\\origin games_tran"},
		{__cgFix::epic,	"D:\\EpicGames_tran"},
		{__cgFix::steam,	"D:\\steamapps\\steamapps_tran"},
		{__cgFix::uplay,	"D:\\uplay_tran"}
};
static std::map<Interface::cgSystem::Theme,std::string> ThemeIndex = { 
		{ Interface::cgSystem::Theme::Default,"aero.theme" },
		{ Interface::cgSystem::Theme::white,"Light.theme" },
		{ Interface::cgSystem::Theme::windows,"theme1.theme" },
		{ Interface::cgSystem::Theme::flower,"theme2.theme" }
};

HRESULT  __cgFix::QueryInterface(const IID& iid, void** ppv)
{
	if (iid == __uuidof(cgFix))
	{
		*ppv = dynamic_cast<cgFix*>(new __cgFix);
	}
	else {
		*ppv = nullptr;
		return E_NOINTERFACE;
	}
	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return S_OK;
}

ULONG  __cgFix::AddRef()
{
	this->ref++;
	return this->ref;
}

ULONG  __cgFix::Release()
{
	if (this->ref--; this->ref == 0)
	{
		delete this;
	}
	else 
	{
		return this->ref;
	}
	return NULL;
}

BOOL  __cgFix::fixSystem()
{
	std::unique_lock<std::mutex> lock(mtx);	// Lock the mutex for thread safety
	namespace fs = std::filesystem;	// Alias for the filesystem namespace
	bool has_success = false;	// Initialize a flag to track the success of the operations
	CL()->info("Start removing restrictions");
	CL()->info("Preparing to start the event bus listener");
	EventBus bus;
	CL()->trace("Preparing to listen for the 'reg_delete_failed' event");
	int id = bus.subscribe("reg_delete_failed", [this](void* Data)
		{
			CL()->error("Triggered the 'reg_delete_failed' event! Found error: {}", formatWindowsErrorMessage(*(static_cast<long*>(Data))));
		});
	/*
	The deleteKey method in the Regedit class within the library,
	if it fails to delete a key, will publish the "reg_delete_failed" event and include error information.
	Therefore, we obtain error messages for the user through this event.
	*/
	CL()->trace("Successfully obtained event ID: {}", id);
	// Initialize a vector of registry keys
	std::vector<std::string_view> HKCU;
	CL()->info("Start pushing data onto the stack");
	if (fs::exists("E:\\Builds"))
	{
		HKCU = {
			"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",
			"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",
			"Software\\Policies\\Microsoft\\MMC",
			"Software\\Policies\\Microsoft\\Edge"
		};
	}
	else
	{
		HKCU = {
			"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",
			"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",
			"Software\\Policies",
		};
	}
	CL()->info("Stack data pushed successfully");
	CL()->trace("Start working");
	cloudgameZero::Foundation::Tool::Regedit Reg(Infomation::HKCU); //Create a Regedit object for registry operations
	/* Threads are just responsible for cleaning up constraints while fixing the desktop */
	ThreadPlatform threads([&HKCU, &Reg, &has_success,this]()
		{	
			for (auto& i : HKCU)
			{
				if (Reg.deleteKey(i.data()))
				{
					CL()->info("�ɹ�ɾ��HKCU\\{}", i);
				}
				else
				{
					CL()->warn("��ɾ��HKCU\\{}��������", i);
					has_success = false;
				}
			}
		});
	threads.Start();
	std::this_thread::sleep_for(std::chrono::milliseconds(50));
	/* The thread is just responsible for cleaning up constraints when we need time to start the thread to fix the desktop */
	CL()->info("Thread creation completed");
	CL()->trace("Prepare to repair the desktop and execute remaining instructions");
	CL()->info("Start repairing the desktop");
	if (fs::exists("E:\\Builds"))
	{
		CL()->info("Attempting to hide DesktopMgr64.exe");
		if (cloudgameZero::Foundation::Tool::isProcessExists("DesktopMgr64.exe"))
		{
			std::cout << "Found the process" << "\n";
			coro::coroutine<bool> coro = []() -> coro::coroutine<bool>
				{
					if (HWND Handle = FindWindowA(&cloudgameZero::Infomation::DesktopMgr64[0], NULL))
					{
						ShowWindow(Handle, SW_HIDE);
						if (HWND WND = FindWindowA(&cloudgameZero::Infomation::DesktopTaskBar64[0], NULL))
						{
							PostMessageA(WND, WM_CLOSE, NULL, NULL);
						}
						else
						{
							co_yield false;
						}
					}
					else
					{
						co_yield false;
					}
					co_return true;
				}
			();
			coro.resume();
			if (!coro.GetValue())
			{
				std::cout << "Unable to hide DesktopMgr64.exe using the handle" << "\n";
				std::cout << "Attempting to intervene forcibly..." << "\n";
				switch (cloudgameZero::Foundation::Tool::function::Terminate(L"DesktopMgr64.exe"))
				{
				case 1:
					std::cout << "Termination completed!" << "\n";
					break;
				case 0:
					std::cout << "Process not found!" << "\n";
					break;
				case -1:
					std::cout << "Unable to obtain the handle!" << "\n";
					break;
				}
			}
		}
		else
		{
			std::cout << "DesktopMgr64.exe does not exist!" << "\n";
			std::cout << "Skipping execution" << "\n";
		}
	}
	std::cout << "Prepare for Plan 1..." << "\n";
	coro::coroutine<bool> coro = []() -> coro::coroutine<bool>
		{
			if (HWND Handle = FindWindowA(&cloudgameZero::Infomation::Shell_TrayWnd[0], NULL); Handle)
			{
				ShowWindow(Handle, SW_SHOW);
				if (HWND Second = FindWindowA(&cloudgameZero::Infomation::Shell_SecondaryTrayWnd[0], NULL); Handle)
				{
					ShowWindow(Second, SW_SHOW);
				}
			}
			else
			{
				co_yield false;
			}
			co_return true;
		}
	();
	coro.resume();
	// Check if the coroutine succeeded
	if (!coro.GetValue())
	{
		std::cout << "Plan 1 failed!" << "\n";
		std::cout << "Preparing to terminate explorer.exe" << "\n";
		switch (cloudgameZero::Foundation::Tool::function::Terminate(L"explorer.exe"))
		{
		case 1:
			std::cout << "Termination completed!" << "\n";
			break;
		case 0:
			std::cout << "Process not found!" << "\n";
			break;
		case -1:
			std::cout << "Unable to obtain the handle!" << "\n";
			break;
		}
	}
	else
	{
		std::cout << "All transactions have been completed!" << "\n";
	}
	threads.join();
	bus.unsubscribe("reg_delete_failed", id);
	return has_success;
}

void  __cgFix::fixFile(_In_ __cgFix::mode mode)
{
	switch (mode)
	{
	case mode::cloudgame:
	{
		std::cout << "��ʼ�޸��ļ�����" << "\n";
		std::cout << "����ע��������..." << "\n";
		cloudgameZero::Foundation::Tool::Regedit reg(Infomation::HKCR);
		std::vector<std::string> list = { ".reg",".bat",".cmd" };
		std::vector<std::string> value = { "regfile","batfile","cmdfile" };
		for (
			std::vector<std::string>::iterator it = list.begin(), itr = value.begin();
			it != list.end() && itr != value.end();
			it++, itr++
		)
		{
			reg.setValue(it->c_str(), REG_SZ, itr->c_str());
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
		CL()->info("�޸���ɣ�");
		break;
	}
	case mode::cloudpc:
	{
		EventBus bus;
		CL()->info("��ʼ�޸�HKLM\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies�µ�����");
		cloudgameZero::Foundation::Tool::Regedit reg(Infomation::HKLM,"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System");
		bus.subscribe("reg_set_failed", [](void* data) 
			{
				if (data != nullptr)
				{
					DWORD* Data = (DWORD*)data;
					CL()->warn("�޷��޸�HKLM\\{}",formatWindowsErrorMessage(*Data));
				}
			});
		reg.setValue("EnableLUA", REG_DWORD, "1");
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		break;
	}
	}
}

void  __cgFix::resetGroupPolicy()
{
	API::ToastTemplate toast(Enums::ToastTemplateType::Text02);
	API::ToastNotification::instance()->setAppUserModelId(cloudgameZero::Infomation::AUMI);
	API::ToastNotification::instance()->setAppName(cloudgameZero::Infomation::APPNAME);
	API::ToastNotification::instance()->Init();
	toast.setSecondLine(L"���ִ���Ϣ��ζ�ų��������ָ����Һ����Ѿ����");
	toast.setFirstLine(L"������������ָ��");
	CL()->debug("׼��ɾ������Ե��ļ�");
	std::filesystem::remove_all("C:\\Windows\\System32\\GroupPolicy");
	std::filesystem::remove_all("C:\\Windows\\System32\\GroupPolicyUsers");
	CL()->info("��ʼִ������ָ��");
	ShellExecuteA(NULL, "open", "cmd.exe", " /c gpupdate /force", NULL, SW_HIDE);
	CL()->info("�ɹ���ɵ���");
	API::ToastNotification::instance()->show(toast, new API::PreDefineHandler);
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	return;
}

HRESULT  __cgFix::repairGameFile()
{
	bool has_Warn = false;
	for (
		auto i = path.begin(), it = path_Tran.begin(), itr = path_After.begin();
		i != path.end() && it != path_Tran.end() && itr != path_After.end();
		i++, itr++, it++
		)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		if (!std::rename(i->second.c_str(), itr->second.c_str()))
		{
			CL()->info("�ɹ�������: {} -> {}", i->second, itr->second);
		}
		else
		{
			CL()->warn("��������: {} Ϊ {}ʱ��������", i->second, itr->second);
			has_Warn = true;
		}
		Sleep(500);
		if (!std::rename(it->second.c_str(), i->second.c_str()))
		{
			CL()->info("�ɹ�������: {} -> {}", it->second, i->second);
		}
		else
		{
			CL()->info("�ɹ�������: {} -> {}", it->second, i->second);
			has_Warn = true;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
	if (!has_Warn)
	{
		return S_OK;
	}
	return E_FAIL;
}

/*
cgFix�ӿڽ���
cgSystem�ӿڿ�ʼ
*/

HRESULT __cgSystem::QueryInterface(const IID& iid, void** ppv)
{
	if (iid == __uuidof(cgFix))
	{
		*ppv = dynamic_cast<cgFix*>(new __cgFix);
	}
	else if (iid == __uuidof(cgSystem))
	{
		*ppv = dynamic_cast<cgSystem*>(new __cgSystem);
	}
	else
	{
		*ppv = nullptr;
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

ULONG cloudgameZero::Interface::sigmaInterface::Implement::__cgSystem::Release()
{
	if (this->ref--; this->ref == 0)
	{
		delete this;
	}
	else
	{
		return this->ref;
	}
	return NULL;
}

void cloudgameZero::Interface::sigmaInterface::Implement::__cgSystem::setWallpaper(IN const std::string& path)
{
	SystemParametersInfoA(SPI_SETDESKWALLPAPER, 0, (PVOID)path.c_str(), SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);
}


void cloudgameZero::Interface::sigmaInterface::Implement::__cgSystem::downloadWallpaperAndSet(IN const std::string& url, IN const std::string path)
{
	if (std::filesystem::exists(path))
	{
		LibError(std::domain_error("�ļ��Ѵ���"));
	}
	Experiment::Curl curl;
	curl.setUrl(url);
	curl.setOperater(Experiment::Curl::operater::Download);
	curl.init();
	CURLcode code = curl.sendDownloadRequest(Experiment::Curl::operation::GET, path.c_str());
	if (code != CURLE_OK)
	{
		LibError(std::logic_error(std::format("����{}", (int)code).c_str()));
	}
	curl.cleanup();
	return setWallpaper(path.c_str());
}

void cloudgameZero::Interface::sigmaInterface::Implement::__cgSystem::changeResolution(IN short length, IN short height)
{
	CL()->info("׼���޸ķֱ���");
	CL()->info("��ʼ�����ṹ��");
	DEVMODEA temp{};
	CL()->info("��ʼö����ʾ��");
	EnumDisplaySettingsA(0, ENUM_CURRENT_SETTINGS, &temp);
	CL()->info("ö�����");
	temp.dmPelsWidth = static_cast<DWORD>(length);
	temp.dmPelsHeight = static_cast<DWORD>(height);
	ChangeDisplaySettingsA(&temp, NULL);
	CL()->info("�޸����");
}

void cloudgameZero::Interface::sigmaInterface::Implement::__cgSystem::changeTheme(IN Theme theme)
{
	std::string str = ThemeIndex[theme];
	ShellExecuteA(NULL, "open", std::format("C:\\Windows\\Resources\\Themes\\{}", str).c_str(), NULL, NULL, SW_HIDE);
}

BOOL sigmaInterface::Implement::__cgSystem::fixSystem()
{
	return __cgFix::fixSystem();
}

void sigmaInterface::Implement::__cgSystem::fixFile(_In_ mode mode)
{
	return __cgFix::fixFile(mode);
}
void sigmaInterface::Implement::__cgSystem::resetGroupPolicy()
{
	return __cgFix::resetGroupPolicy();
}
HRESULT sigmaInterface::Implement::__cgSystem::repairGameFile()
{
	return __cgFix::repairGameFile();
}