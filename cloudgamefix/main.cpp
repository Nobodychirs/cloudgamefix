#include "cloudgamefix.hpp"

using namespace cloudgameZero;
using namespace cloudgameZero::Foundation;
using namespace cloudgameZero::Foundation::Tool;
using namespace cloudgameZero::Foundation::dynamincLibrayFunc::function;
using namespace cloudgameZero::Interface;
using namespace cloudgameZero::Interface::sigmaInterface::guid;
namespace ToastPlatformAPI = cloudgameZero::ToastPlatform::API;
namespace ToastPlatformEnums = cloudgameZero::ToastPlatform::Enums;

/**
 * ┌───┐   ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┐
 * │Esc│   │ F1│ F2│ F3│ F4│ │ F5│ F6│ F7│ F8│ │ F9│F10│F11│F12│ │P/S│S L│P/B│  ┌┐    ┌┐    ┌┐
 * └───┘   └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┘  └┘    └┘    └┘
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐ ┌───┬───┬───┐ ┌───┬───┬───┬───┐
 * │~ `│! 1│@ 2│# 3│$ 4│% 5│^ 6│& 7│* 8│( 9│) 0│_ -│+ =│ BacSp │ │Ins│Hom│PUp│ │N L│ / │ * │ - │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤ ├───┼───┼───┤ ├───┼───┼───┼───┤
 * │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │{ [│} ]│ | \ │ │Del│End│PDn│ │ 7 │ 8 │ 9 │   │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤ └───┴───┴───┘ ├───┼───┼───┤ + │
 * │ Caps │ A │ S │ D │ F │ G │ H │ J │ K │ L │: ;│" '│ Enter  │               │ 4 │ 5 │ 6 │   │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤     ┌───┐     ├───┼───┼───┼───┤
 * │ Shift  │ Z │ X │ C │ V │ B │ N │ M │< ,│> .│? /│  Shift   │     │ ↑ │     │ 1 │ 2 │ 3 │   │
 * ├─────┬──┴─┬─┴──┬┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤ ┌───┼───┼───┐ ├───┴───┼───┤ E││
 * │ Ctrl│    │Alt │         Space         │ Alt│    │    │Ctrl│ │ ← │ ↓ │ → │ │   0   │ . │←─┘│
 * └─────┴────┴────┴───────────────────────┴────┴────┴────┴────┘ └───┴───┴───┘ └───────┴───┴───┘
 */

extern void testNoti();

static const auto memu = 
[]() -> std::vector<std::string_view>
	{
		namespace fs = std::filesystem;
		std::vector<std::string_view> views;
		if (Infomation::isCloudPC)
		{
			views = {
				"1.修复系统",
				"2.修复微软商店",
				"3.修复游戏文件",
				"4.关于此程序信息",
				"5.关于程序帮助",
				"6.退出",
			};
		}
		else
		{
			views = {
				"1.修复系统",
				"2.修复微软商店",
				"3.关于此程序信息",
				"4.关于程序帮助",
				"5.退出",
			};
		}
		return views;
	}
();

void showMenu()
{
	for (const std::string_view& i : memu)
	{
		std::cout << i << "\n";
	}
}

extern void test();

int main(int argc, CHAR** argv)
{
	std::cout << "准备初始化实例" << "\n";
	/* Init Process Start */
	std::ios::sync_with_stdio(false);
	auto* logger = new Foundation::zeroLogA("logConfig.json","main","MAIN");
	logger->trace("准备创建cloudgamefix实例");
	logger->info("开始准备接口...");
	cloudgamePtr<Interface::cgFix> cgfix;
	cloudgamePtr<Interface::cgSystem> cgsystem;
	cloudgamePtr<Interface::WinNotification> notification;
	try {
		logger->debug("开始创建实例");
		if (FAILED(createInstance(cgfix)) || FAILED(createInstance(cgsystem)) || FAILED(createInstance(notification))) {
			logger->fatal("无法创建cloudgamefix实例!");
			throw std::exception("检测到错误在创建实例上");
		}
	}
	catch (std::exception& e) {
		std::cout << e.what() << "\n";
		return -1;
	}
	logger->info("准备Hook钩子...");
	WindowsHookA Hook;
	Hook.setCallBack([](int nCode, WPARAM wParam, LPARAM lParam) -> LRESULT
		{			
			KBDLLHOOKSTRUCT* p = (KBDLLHOOKSTRUCT*)lParam;
			if (wParam == WM_KEYDOWN)
			{
				if (GetKeyState(VK_CONTROL) && p->vkCode == 0x44)
				{
					std::cout << "程序被执行退出！" << "\n";
					exit(0);
				}
			}
			return CallNextHookEx(NULL, nCode, wParam, lParam);
		});
	Hook.startHook(cloudgameZero::InstallHookType::KEYBORAD_LL);
	std::this_thread::sleep_for(std::chrono::milliseconds(1));
	logger->info("The Hook Thread Address = {} & Hook Thread Id = {}",Hook.getThreadAddress(), Hook.getHookThreadId());
	notification->setAppName(Infomation::APPNAME);
	notification->setAppUserModelId(Infomation::AUMI);
	/* Init Process End */
	std::cout << "所有组件初始化完成!" << "\n";
	std::cout << "如果想要强制关闭该应用程序，您可以按Ctrl+D来关闭这个程序!" << "\n";
	Curl curl;
	curl.init();
	curl.setUrl("https://ghproxy.net/https://raw.githubusercontent.com/Nobodychirs/cloudgamefix/develop/static/wuaueng.dll");
	curl.setOperater(Curl::operater::Download);
	curl.showProgress();
	curl.sendDownloadRequest(Curl::operation::GET,"D:\\wuaueng.dll");
	curl.cleanup();
	bool exit = false;
	if(Infomation::isCloudPC)
	{
		logger->info("检测到云电脑，准备切换为云电脑模式!");
		int choice = 0;
		std::string trim;
		while (true) {
			cleanConsoleBuffer(cloudgameZero::CONSOLE_OUTPUT_HANDLE);
			showMenu();
			try
			{
				std::cin >> trim;
				choice = cloudgameZero::strToInt(trim);
			}
			catch (...)
			{
				while (true)
				{
					try {
						std::cout << "错误的输入!您必须输入一个整型" << "\n";
						std::cin >> trim;
						choice = cloudgameZero::strToInt(trim);
						break;
					}
					catch (...)
					{
						continue;
					}
				}
			}
			switch (choice)
			{
			case 1:
			{
				cleanConsoleBuffer(cloudgameZero::CONSOLE_OUTPUT_HANDLE);
				ToastPlatformAPI::ToastTemplate Toast(ToastPlatformEnums::ToastTemplateType::Text02);
				Toast.setFirstLine(L"成功完成了cloudgamefix的修复事务!");
				Toast.setSecondLine(L"此通知仅在启用了通知功能的情况下可见，但是，所有事务基本已经完成了，恭喜！如果想修复额外的功能，请修复微软商店！");
				Toast.setExpiration(5000);
				std::cout << "正在准备事务..." << "\n";
				std::cout << "准备修复程序..." << "\n";
				cgfix->fixSystemRestriction();
				std::cout << "准备修复额外限制..." << "\n";
				cgfix->fixFileExt(cgFix::mode::cloudpc);
				std::cout << "事务已完成!" << "\n";
				notification->show(Toast, new ToastPlatformAPI::PreDefineHandler);
				PRESSANYBOTTON();
				cleanConsoleBuffer(cloudgameZero::CONSOLE_OUTPUT_HANDLE);
				break;
			}
			case 2:
				cleanConsoleBuffer(cloudgameZero::CONSOLE_OUTPUT_HANDLE);
				std::cout << "正在准备事务..." << "\n";
				cgfix->fixUpdateFiles("https://gitee.com/eGlhb2p1emk/cloudgamefix/blob/develop/static/cloudgame.json", TRUE);
				std::cout << "文件恢复事务完成!" << "\n";
				std::cout << "准备修复服务" << "\n";
				cgfix->fixUpdateService();
				PRESSANYBOTTON();
				cleanConsoleBuffer(cloudgameZero::CONSOLE_OUTPUT_HANDLE);
				break;
			default:
				break;
			}
			if (exit)
				break;
		}
	}
	else
	{
		logger->info("检测到云游戏，准备切换为云游戏模式!");
		std::string trim;
		int choice = 0;
		while (true) {
			cleanConsoleBuffer(cloudgameZero::CONSOLE_OUTPUT_HANDLE);
			showMenu();
			try
			{
				std::cin >> trim;
				choice = cloudgameZero::strToInt(trim);
			}
			catch (...)
			{
				while (true)
				{
					try {
						std::cout << "错误的输入!您必须输入一个整型" << "\n";
						std::cin >> trim;
						choice = cloudgameZero::strToInt(trim);
						break;
					}
					catch (...)
					{
						continue;
					}
				}
			}
			switch (choice)
			{
			case 1:
			{
				cleanConsoleBuffer(cloudgameZero::CONSOLE_OUTPUT_HANDLE);
				ToastPlatformAPI::ToastTemplate Toast(ToastPlatformEnums::ToastTemplateType::Text02);
				Toast.setFirstLine(L"成功完成了cloudgamefix的修复事务!");
				Toast.setSecondLine(L"此通知仅在启用了通知功能的情况下可见，但是，所有事务基本已经完成了，恭喜！如果想修复额外的功能，请修复微软商店！");
				Toast.setExpiration(5000);
				std::cout << "正在准备事务..." << "\n";
				std::cout << "准备修复程序..." << "\n";
				cgfix->fixSystemRestriction();
				std::cout << "准备修复额外限制..." << "\n";
				cgfix->fixFileExt(cgFix::mode::cloudgame);
				std::cout << "事务已完成!" << "\n";
				notification->show(Toast, new ToastPlatformAPI::PreDefineHandler);
				PRESSANYBOTTON();
				cleanConsoleBuffer(cloudgameZero::CONSOLE_OUTPUT_HANDLE);
				break;
			}
			case 2:
				cleanConsoleBuffer(cloudgameZero::CONSOLE_OUTPUT_HANDLE);
				std::cout << "正在准备事务..." << "\n";
				cgfix->fixUpdateFiles("https://gitee.com/eGlhb2p1emk/cloudgamefix/blob/develop/static/cloudgame.json", TRUE);
				std::cout << "文件恢复事务完成!" << "\n";
				std::cout << "准备修复服务" << "\n";
				cgfix->fixUpdateService();
				PRESSANYBOTTON();
				cleanConsoleBuffer(cloudgameZero::CONSOLE_OUTPUT_HANDLE);
				break;
			default:
				break;
			}
			if (exit)
				break;
		}
	}
}
