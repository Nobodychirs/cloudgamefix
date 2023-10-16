#include "cloudgamefix.hpp"

using namespace cloudgameZero::Interface::sigmaInterface::Implement;
using namespace cloudgameZero::Interface::sigmaInterface::guid;
using namespace cloudgameZero::Interface;
using namespace cloudgameZero::ToastPlatform;
using namespace cloudgameZero;

namespace cloudgameZero
{
	namespace Interface
	{
		namespace sigmaInterface
		{
			namespace Implement
			{
				class __cgFix : virtual public cloudgameZero::Interface::cgFix
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

				class __cgSystem : virtual public cloudgameZero::Interface::cgSystem,__cgFix
				{
				public:
					__cgSystem() = default;
					virtual ~__cgSystem() = default;
					virtual HRESULT QueryInterface(const IID& iid, void** ppv) override;
					virtual ULONG AddRef() override
					{
						this->ref++;
						return this->ref;
					}
					virtual ULONG Release() override
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
					virtual void setWallpaper(IN const std::string& path)
					{
						SystemParametersInfoA(SPI_SETDESKWALLPAPER, 0, (PVOID)path.c_str(), SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);
					}
					virtual void downloadWallpaperAndSet(IN const std::string& url, IN const std::string path)
					{
						if (std::filesystem::exists(path))
						{
							LibError(std::domain_error("文件已存在"));
						}
						Experiment::Curl curl;
						curl.setUrl(url);
						curl.setOperater(Experiment::Curl::operater::Download);
						curl.init();
						CURLcode code = curl.sendDownloadRequest(Experiment::Curl::operation::GET,path.c_str());
						if (code != CURLE_OK)
						{
							LibError(std::logic_error(std::format("错误：{}",(int)code).c_str()));
						}
						curl.cleanup();
						return setWallpaper(path.c_str());
					}
					virtual void changeResolution(IN short length, IN short height)
					{

						CL()->info("准备修改分辨率");
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
					virtual void changeTheme(IN Theme theme)
					{

					}
					virtual BOOL fixSystem() override
					{
						return __cgFix::fixSystem();
					}
					virtual void fixFile(_In_ mode mode) override
					{
						return __cgFix::fixFile(mode);
					}
					virtual void resetGroupPolicy() override
					{
						return __cgFix::resetGroupPolicy();
					}
					virtual HRESULT repairGameFile() override
					{
						return __cgFix::repairGameFile();
					}
				private:
					ULONG ref = 0;
					__cgSystem(const __cgSystem& other) = delete;
					cgSystem& operator=(cgSystem& other) = delete;
					std::mutex mtx;
				};
				
				
			}
		}

		HRESULT createInstance(const GUID iid, void** ppv)
		{
			if (iid == __uuidof(cgFix))
			{
				std::unique_ptr<IUnknown> ptr = std::make_unique<__cgFix>();
				HRESULT hr = ptr->QueryInterface(iid,ppv);
				if (FAILED(hr))
				{
					*ppv = nullptr;
					return hr;
				}
				reinterpret_cast<IUnknown*>(*ppv)->AddRef();
				ptr.release();
			}
			else
			{
				*ppv = nullptr;
				return E_NOINTERFACE;
			}
			return S_OK;
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
		{__cgFix::origin,	"D:\\origin games_tran"},
		{__cgFix::epic,	"D:\\EpicGames_tran"},
		{__cgFix::steam,	"D:\\steamapps\\steamapps_tran"},
		{__cgFix::uplay,	"D:\\uplay_tran"}
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
	std::unique_lock<std::mutex> lock(mtx);
	namespace fs = std::filesystem;
	bool has_success = false;
	CL()->info("开始删除限制");
	CL()->info("准备启动事件总线监听...");
	EventBus bus;
	CL()->trace("准备监听reg_delete_failed事件...");
	int id = bus.subscribe("reg_delete_failed", [this](void* Data)
		{
			CL()->error("触发reg_delete_failed事件! 找到错误为：{}", formatWindowsErrorMessage(*(static_cast<long*>(Data))));
		});
	CL()->trace("已获取事件id: {}",id);
	std::vector<std::string_view> HKCU;
	CL()->info("开始入栈");
	CL()->info("开始向栈压入数据");
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
	CL()->info("入栈完成");
	CL()->trace("开始工作");
	cloudgameZero::Foundation::Tool::Regedit Reg(Infomation::HKCU);
	/* 线程只是负责在修复桌面的时候同时清理限制 */
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
	/* 我们需要时间来启动线程 */
	CL()->info("创建完成");
	CL()->trace("准备修复桌面事务，并运行剩下的指令");
	CL()->info("开始修复桌面...");
	if (fs::exists("E:\\Builds"))
	{
		CL()->info("尝试隐藏DesktopMgr64.exe");
		if (cloudgameZero::Foundation::Tool::isProcessExists("DesktopMgr64.exe"))
		{
			std::cout << "找到进程" << "\n";
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
				std::cout << "无法通过句柄隐藏DesktopMgr64.exe" << "\n";
				std::cout << "尝试强行介入..." << "\n";
				switch (cloudgameZero::Foundation::Tool::function::Terminate(L"DesktopMgr64.exe"))
				{
				case 1:
					std::cout << "完成终止!" << "\n";
					break;
				case 0:
					std::cout << "无法找到进程!" << "\n";
					break;
				case -1:
					std::cout << "无法拿到句柄!" << "\n";
					break;
				}
			}
		}
		else
		{
			std::cout << "DesktopMgr64不存在！" << "\n";
			std::cout << "跳过执行" << "\n";
		}
	}
	std::cout << "准备方案1..." << "\n";
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
	if (!coro.GetValue())
	{
		std::cout << "方案1失败!" << "\n";
		std::cout << "准备终止explorer.exe" << "\n";
		switch (cloudgameZero::Foundation::Tool::function::Terminate(L"explorer.exe"))
		{
		case 1:
			std::cout << "完成终止!" << "\n";
			has_success = true;
			break;
		case 0:
			std::cout << "无法找到进程!" << "\n";
			break;
		case -1:
			std::cout << "无法拿到句柄!" << "\n";
			break;
		}
	}
	else
	{
		std::cout << "事务完成" << "\n";
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
		std::cout << "开始修复文件关联" << "\n";
		std::cout << "创建注册表对象中..." << "\n";
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
	CL()->info("准备删除组策略的文件");
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
	else
	{
		return E_FAIL;
	}
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

