#include "cloudgamefix.hpp"

using namespace cloudgameZero;
using namespace cloudgameZero::Foundation;
using namespace cloudgameZero::Foundation::Tool;
using namespace cloudgameZero::Foundation::dynamincLibrayFunc::function;
using namespace cloudgameZero::Interface;
using namespace cloudgameZero::Interface::sigmaInterface::guid;
using namespace cloudgameZero::Interface::sigmaInterface::Implement;
using namespace cloudgameZero::ToastPlatform;
using namespace cloudgameZero::ToastPlatform::API;
using namespace cloudgameZero::ToastPlatform::Enums;

#define MakeCloudgameComponent(x) class DECLSPEC_UUID(x) DECLSPEC_NOVTABLE

#pragma warning(push)
#pragma warning(disable : CLOUDGAME_FIX_ZERO_DISABLE_WARNING)

static inline void setError(_Out_opt_ Enums::ToastError* error, _In_ Enums::ToastError value)
{
	if (error) {
		*error = value;
	}
}

static std::wstring configureAUMI(_In_ std::wstring const& companyName, _In_ std::wstring const& productName, _In_ std::wstring const& subProduct = std::wstring(), _In_ std::wstring const& versionInformation = std::wstring())
{
	std::wstring aumi = companyName;
	aumi += L"." + productName;
	if (subProduct.length() > 0)
	{
		aumi += L"." + subProduct;
		if (versionInformation.length() > 0)
		{
			aumi += L"." + versionInformation;
		}
	}
	if (aumi.length() > SCHAR_MAX)
	{
		DEBUG_MESSAGE(L"错误：用户模型ID总长度不应该超过127");
	}
	return aumi;
}

static std::wstring const& getToastErrorMessage(_In_ Enums::ToastError error)
{
	auto const iter = Libray::ToastErrors.find(error);
	assert(iter != Libray::ToastErrors.end());
	return iter->second;
}

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
					virtual BOOL fixSystemRestriction() override;
					virtual void fixFileExt(_In_ mode mode) override;
					virtual void resetGroupPolicy() override;
					virtual HRESULT repairGameFile() override;
					virtual void fixUpdateFiles(_In_ std::string manifest, _In_opt_ BOOL useGetRequest = FALSE) override;
					virtual void fixUpdateService() override;
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
					virtual void setWallpaper(_In_ const std::string& path);
					virtual void downloadWallpaperAndSet(IN const std::string& url, IN const std::string path) override;
					virtual void changeResolution(IN short length, IN short height) override;
					virtual void changeTheme(IN Theme theme);
					virtual BOOL fixSystemRestriction() override;
					virtual void fixFileExt(_In_ mode mode) override;
					virtual void resetGroupPolicy() override;
					virtual HRESULT repairGameFile() override;
					virtual void fixUpdateFiles(_In_ std::string manifest,_In_opt_ BOOL useGetRequest = FALSE) override;
					virtual void fixUpdateService() override;
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
				extern IUnknown* Query(_In_ const IID& iid)
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
		}
	}
}

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
		{__cgFix::origin,							"D:\\origin games_tran"},
		{__cgFix::epic,								"D:\\EpicGames_tran"},
		{__cgFix::steam,							"D:\\steamapps\\steamapps_tran"},
		{__cgFix::uplay,							"D:\\uplay_tran"}
};
static std::map<Interface::cgSystem::Theme,std::string> ThemeIndex = { 
		{ Interface::cgSystem::Theme::Default,		"aero.theme" },
		{ Interface::cgSystem::Theme::white,		"Light.theme" },
		{ Interface::cgSystem::Theme::windows,		"theme1.theme" },
		{ Interface::cgSystem::Theme::flower,		"theme2.theme" }
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
	if (--this->ref; this->ref == 0)
	{
		delete this;
	}
	else 
	{
		return this->ref;
	}
	return NULL;
}

BOOL  __cgFix::fixSystemRestriction()
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
					CL()->info("成功删除HKCU\\{}", i);
				}
				else
				{
					CL()->warn("在删除HKCU\\{}出现问题", i);
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

void  __cgFix::fixFileExt(_In_ __cgFix::mode mode)
{
	switch (mode)
	{
	case mode::cloudgame:
	{
		std::cout << "开始修复文件关联" << "\n";
		std::cout << "创建注册表对象中..." << "\n";
		cloudgameZero::Foundation::Tool::Regedit reg(Infomation::HKCR);
		static std::vector<std::string> list = { ".reg",".bat",".cmd" };
		static std::vector<std::string> value = { "regfile","batfile","cmdfile" };
		for (
			std::vector<std::string>::iterator it = list.begin(), itr = value.begin();
			it != list.end() && itr != value.end();
			it++, itr++
		)
		{
			reg.setValue(it->c_str(), REG_SZ, itr->c_str());
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
		CL()->info("修复完成！");
		break;
	}
	case mode::cloudpc:
	{
		EventBus bus;
		CL()->info("开始修改HKLM\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies下的数据");
		cloudgameZero::Foundation::Tool::Regedit reg(Infomation::HKLM,"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System");
		bus.subscribe("reg_set_failed", [](void* data) 
			{
				if (data != nullptr)
				{
					DWORD* Data = (DWORD*)data;
					CL()->warn("无法修改HKLM\\{}",formatWindowsErrorMessage(*Data));
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
	toast.setSecondLine(L"出现此消息意味着程序完成了指令，并且函数已经完成");
	toast.setFirstLine(L"完成组策略重置指令");
	CL()->debug("准备删除组策略的文件");
	std::filesystem::remove_all("C:\\Windows\\System32\\GroupPolicy");
	std::filesystem::remove_all("C:\\Windows\\System32\\GroupPolicyUsers");
	CL()->info("开始执行重置指令");
	ShellExecuteA(NULL, "open", "cmd.exe", " /c gpupdate /force", NULL, SW_HIDE);
	CL()->info("成功完成调用");
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
			CL()->info("成功重命名: {} -> {}", i->second, itr->second);
		}
		else
		{
			CL()->warn("在重命名: {} 为 {}时遇到问题", i->second, itr->second);
			has_Warn = true;
		}
		Sleep(500);
		if (!std::rename(it->second.c_str(), i->second.c_str()))
		{
			CL()->info("成功重命名: {} -> {}", it->second, i->second);
		}
		else
		{
			CL()->info("成功重命名: {} -> {}", it->second, i->second);
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

void cloudgameZero::Interface::sigmaInterface::Implement::__cgFix::fixUpdateFiles(_In_ std::string manifest,_In_opt_ BOOL useGetRequest)
{
	namespace fs = std::filesystem;
	EventBus bus;
	if (!fs::exists(manifest) && !useGetRequest)
	{
		bus.post("file_not_found");
		return;
	}
	Experiment::Curl curl;
	rapidjson::Document Dom;
	if (useGetRequest)
	{
		if (!std::regex_match(manifest, std::regex(Infomation::Secutriy::urlLinkRegex.data())))
		{
			bus.post("invaild_args");
			return;
		}
		curl.init();
		curl.setUrl(manifest.c_str());
		curl.setOperater(Experiment::Curl::operater::Request);
		Dom = curl.getJsonDomByRequest(Experiment::Curl::operation::GET);
		curl.cleanup();
	}
	else
	{
		if (std::regex_match(manifest, std::regex(Infomation::Secutriy::urlLinkRegex.data())))
		{
			bus.post("invaild_args");
			return;
		}
		std::fstream in(manifest, std::ios::in);
		if (!in.is_open())
		{
			bus.post("file_open_failed");
			return;
		}
		std::string data((std::istream_iterator<char>(in)), std::istream_iterator<char>());
		in.close();
		if (Dom.Parse(data.c_str()); Dom.HasParseError())
		{
			bus.post("json_parse_error");
			return;
		}
	}
	if (!(Dom.HasMember("cloudpc") && Dom.HasMember("cloudgame")))
	{
		bus.post("invalid_args");
		return;
	}
	auto& cloudgame = Dom[Infomation::isCloudPC ? "cloudpc" : "cloudgame"];
	std::string url;
	bool invalid_args = true;
	do {
		if (!cloudgame.HasMember("proxy"))
			break;
		if (!(cloudgame["proxy"].HasMember("enable") && cloudgame["proxy"].HasMember("url")))
			break;
		if (!(cloudgame["proxy"]["enable"].IsBool() && cloudgame["proxy"]["url"].IsString()))
			break;
		if (cloudgame["proxy"]["enable"].GetBool())
			url += cloudgame["proxy"]["url"].GetString();
		if (!cloudgame.HasMember("repo"))
			break;
		if (!cloudgame["repo"].IsString())
			break;
		LPCSTR repo = cloudgame["repo"].GetString();
		if (!repo)
			break;
		url += repo;
		if (!cloudgame.HasMember("files"))
			break;
		if (!cloudgame["files"].IsObject())
			break;
		if (!cloudgame["files"]["services"].IsArray())
			break;
		invalid_args = false;
	} while (false);
	if (invalid_args)
	{
		bus.post("invalid_args");
		return;
	}
	rapidjson::GenericArray<false, rapidjson::Value> files = cloudgame["files"]["services"].GetArray();
	auto& zindex = files[0];
	if (!(zindex.HasMember("filename") && zindex.HasMember("savePath") && zindex.HasMember("check") && zindex.HasMember("description")))
	{
		bus.post("invalid_args");
		return;
	}
	std::string download;
	static errno_t error = 0;
	curl.init();
	curl.setOperater(Experiment::Curl::operater::Download);
	for (auto& iterator : files)
	{
		LPCSTR filename = iterator["filename"].GetString();
		std::string check = cloudgameZero::format<char>("%s%s", iterator["savePath"].GetString(), filename);
		std::string fileurl = cloudgameZero::format<char>("%s%s", url.c_str(), filename);
		if (!fs::exists(check))
		{
			CL()->info("Starting Download For : {}", fileurl);
			curl.setUrl(fileurl);
			curl.sendDownloadRequest(Experiment::Curl::operation::GET, check);
		}
		size_t size = fs::file_size(check), c_size = iterator["check"]["size"].GetInt();
		std::string sha1 = cloudgameZero::getFileSha1(check), c_sha1 = iterator["check"]["sha1"].GetString();
		if (size != c_size)
		{
			CL()->warn("The size specified in the manifest file does not match the actual size. Try to download it again for verification");
			CL()->info("Starting Download For : {}", fileurl);
			curl.setUrl(fileurl);
			curl.sendDownloadRequest(Experiment::Curl::operation::GET, check);
			std::size_t size = fs::file_size(check);
			std::string sha1 = cloudgameZero::getFileSha1(check);
			if (size != c_size)
			{
				error = 1;
				bus.post("verify_failed", &error);
			}
			else if (sha1 != c_sha1)
			{
				error = 2;
				bus.post("verify_failed", &error);
			}
			return;
		}
		if (sha1 != c_sha1)
		{
			CL()->warn("The hash check value of the file is detected to be inconsistent with the hash check value specified by the manifest,Try to download it again for verification");
			CL()->info("Starting Download For : {}", fileurl);
			curl.setUrl(fileurl);
			curl.sendDownloadRequest(Experiment::Curl::operation::GET, check);
			std::size_t size = fs::file_size(check);
			std::string sha1 = cloudgameZero::getFileSha1(check);
			if (size != c_size)
			{
				error = 3;
				bus.post("verify_failed", &error);
			}
			else if (sha1 != c_sha1)
			{
				error = 4;
				bus.post("verify_failed", &error);
			}
			return;
		}
	}
	curl.cleanup();
	/* We can just notify the component that the transaction has completed with an event */
	bus.post("success");
}

void cloudgameZero::Interface::sigmaInterface::Implement::__cgFix::fixUpdateService()
{
	EventBus bus;
	namespace fs = std::filesystem;
	if (!fs::exists("C:\\Windows\\System32\\wuaueng.dll") || !fs::exists("C:\\Windows\\System32\\WaaSMedicSvc.dll"))
	{
		bus.post("file_not_found");
		CL()->debug("请尝试确认服务需要的dll模块是否存在");
		return;
	}
	CL()->trace("所有文件已就位");
	CL()->trace("准备获取句柄");
	SC_HANDLE LOCAL_MACHINE = OpenSCManagerW(NULL, SERVICES_ACTIVE_DATABASE, SC_MANAGER_ALL_ACCESS);
	if (!LOCAL_MACHINE)
	{
		bus.post("sm_open_failed");
		return;
	}
	CL()->debug("准备拿取wuauserv句柄并修改TrustedInstaller");
	static Regedit reg(Infomation::HKLM, "SYSTEM\\CurrentControlSet\\Services\\TrustedInstaller");
	reg.setValue("Start", REG_DWORD, "3");
	/* 由于TrustedInstaller服务无法直接拿到句柄，因此使用注册表实现这个功能 */
	SC_HANDLE wuauserv = OpenServiceA(LOCAL_MACHINE, Infomation::wuauserv_str.data(), SC_MANAGER_ALL_ACCESS);
	if (!wuauserv)
	{
		bus.post("service_open_failed");
		return;
	}
	BOOL ret = ChangeServiceConfigA(wuauserv, SERVICE_NO_CHANGE, SERVICE_DEMAND_START, SERVICE_NO_CHANGE, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
	if (!ret)
	{
		bus.post("edit_service_failed");
		return;
	}
	ret = StartServiceA(wuauserv, NULL, nullptr);
	if (!ret)
	{
		bus.post("edit_service_failed");
	}
	ShellExecuteA(NULL, "open", "net", "start TrustedInstaller", NULL, SW_HIDE);
	return;
}


/*
cgFix接口结束
cgSystem接口开始
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

void cloudgameZero::Interface::sigmaInterface::Implement::__cgSystem::setWallpaper(_In_ const std::string& path)
{
	SystemParametersInfoA(SPI_SETDESKWALLPAPER, 0, (PVOID)path.c_str(), SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);
}


void cloudgameZero::Interface::sigmaInterface::Implement::__cgSystem::downloadWallpaperAndSet(IN const std::string& url, IN const std::string path)
{
	if (std::filesystem::exists(path))
	{
		LibError(std::domain_error("文件已存在"));
	}
	Experiment::Curl curl;
	curl.setUrl(url);
	curl.setOperater(Experiment::Curl::operater::Download);
	curl.init();
	CURLcode code = curl.sendDownloadRequest(Experiment::Curl::operation::GET, path.c_str());
	if (code != CURLE_OK)
	{
		LibError(std::logic_error(std::format("错误：{}", (int)code).c_str()));
	}
	curl.cleanup();
	return setWallpaper(path.c_str());
}

void cloudgameZero::Interface::sigmaInterface::Implement::__cgSystem::changeResolution(IN short length, IN short height)
{
	CL()->trace("准备修改分辨率");
	CL()->info("开始创建结构体");
	DEVMODEA temp{};
	CL()->info("开始枚举显示器");
	EnumDisplaySettingsA(0, ENUM_CURRENT_SETTINGS, &temp);
	CL()->info("枚举完成");
	temp.dmPelsWidth = static_cast<DWORD>(length);
	temp.dmPelsHeight = static_cast<DWORD>(height);
	ChangeDisplaySettingsA(&temp, NULL);
	CL()->info("修改完毕");
}

void cloudgameZero::Interface::sigmaInterface::Implement::__cgSystem::changeTheme(IN Theme theme)
{
	std::string str = ThemeIndex[theme];
	ShellExecuteA(NULL, "open", std::format("C:\\Windows\\Resources\\Themes\\{}", str).c_str(), NULL, NULL, SW_HIDE);
}

BOOL sigmaInterface::Implement::__cgSystem::fixSystemRestriction()
{
	return __cgFix::fixSystemRestriction();
}

void sigmaInterface::Implement::__cgSystem::fixFileExt(_In_ mode mode)
{
	return __cgFix::fixFileExt(mode);
}
void sigmaInterface::Implement::__cgSystem::resetGroupPolicy()
{
	return __cgFix::resetGroupPolicy();
}
HRESULT sigmaInterface::Implement::__cgSystem::repairGameFile()
{
	return __cgFix::repairGameFile();
}

void sigmaInterface::Implement::__cgSystem::fixUpdateFiles(_In_ std::string manifest, _In_opt_ BOOL useGetRequest)
{
	return __cgFix::fixUpdateFiles(manifest,useGetRequest);
}

void sigmaInterface::Implement::__cgSystem::fixUpdateService()
{
	return __cgFix::fixUpdateService();
}

/* 通知实体类方法实现 */

extern void testNoti()
{
	
}

bool cloudgameZero::Infomation::isSupportingModernFeatures()
{
	constexpr auto MinimumSupportedVersion = 6;
	return Libray::Util::getRealOSVersion().dwMajorVersion > MinimumSupportedVersion;
}

bool cloudgameZero::Infomation::isWin10AnniversaryOrHigher()
{
	return Libray::Util::getRealOSVersion().dwBuildNumber >= 14393;
}

#pragma warning(pop)