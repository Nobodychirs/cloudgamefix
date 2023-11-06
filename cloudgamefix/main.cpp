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
		if (fs::exists("E:\\Builds"))
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
				"2.云电脑系统管理",
				"3.关于此程序信息",
				"4.关于程序帮助",
				"5.退出",
			};
		}
		return views;
	}
();

int showMenu()
{
	namespace fs = std::filesystem;
	if (fs::exists("E:\\Builds"))
	{
		/* 你问这里在干啥？我不道啊 */
		for (auto& i : memu | std::views::all)
		{
			std::cout << i << "\n";
		}
		return 1;
	}
	else
	{
		for (auto& i : memu | std::views::all)
		{
			std::cout << i << "\n";
		}
	}
	return 0;
}

extern void test();

LRESULT __stdcall WindowProcedure(HWND window, unsigned int msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_DESTROY:
		printf("\ndestroying window\n");
		PostQuitMessage(0);
		return 0L;

	case WM_LBUTTONDOWN:
		printf("\nmouse left button down at (%d, %d)\n", LOWORD(lp), HIWORD(lp));
		__fallthrough;
	default:
		return DefWindowProc(window, msg, wp, lp);
	}
}

namespace Dism
{

}

int main(int argc, CHAR** argv)
{
	HANDLE INSTANCE_EVENT = CreateEventA(NULL, FALSE, FALSE, "cloudgameFixZero init process");
	/*std::jthread thread = std::jthread([]()
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(2000));
			exit(0);
		}
	);*/
	cloudgamePtr<cgSystem> ptr = nullptr;
	createInstance(ptr);
	PRESSANYBOTTON();
	if (INSTANCE_EVENT)
	{
		/*SetEvent(INSTANCE_EVENT);
		if (ERROR_ALREADY_EXISTS == GetLastError())
		{
			ToastPlatformAPI::ToastTemplate Toast(ToastPlatformEnums::ToastTemplateType::Text02);
			Toast.setFirstLine(L"错误!");
			Toast.setSecondLine(L"一个实例已经启动了，不能再运行第二个实例，请关闭已打开的实例!");
			INT64 wait = 5000;
			Toast.setExpiration(wait);
			ToastPlatformAPI::ToastNotification Notification;
			Notification.setAppName(L"cloudgameFixZero");
			Notification.setAppUserModelId(L"cloudgameFixZero");
			Notification.Init();
			Notification.show(Toast, new ToastPlatformAPI::PreDefineHandler);
			std::this_thread::sleep_for(std::chrono::milliseconds(wait));
			return 0xB;
		}*/
	}
	else
	{
		/*ToastPlatformAPI::ToastTemplate Toast(ToastPlatformEnums::ToastTemplateType::Text02);
		Toast.setFirstLine(L"错误!");
		Toast.setSecondLine(L"程序无法获取自己的实例!");
		INT64 wait = 5000;
		Toast.setExpiration(wait);
		ToastPlatformAPI::ToastNotification Notification;
		Notification.setAppName(L"cloudgameFixZero");
		Notification.setAppUserModelId(L"cloudgameFixZero");
		Notification.Init();
		Notification.show(Toast, new ToastPlatformAPI::PreDefineHandler);
		std::this_thread::sleep_for(std::chrono::milliseconds(wait));
		return 0xA;*/
	}
	auto list = Experiment::makeArgumentsView(argc, argv);
	WindowsHookA Hook;
	Hook.setCallBack([](int nCode, WPARAM wParam, LPARAM lParam) -> LRESULT
		{
			BOOL  caps = FALSE;
			SHORT capsShort = GetKeyState(VK_CAPITAL);
			std::string outPut;
			if (capsShort > 0)
			{
				//  如果大于0，则大写键按下，说明开启大写；反之小写
				caps = TRUE;
			}
			/*
			WH_KEYBOARD_LL uses the LowLevelKeyboardProc CallBack
			LINK = https://msdn.microsoft.com/zh-cn/library/windows/desktop/ms644985(v=vs.85).aspx
			*/
			KBDLLHOOKSTRUCT* p = (KBDLLHOOKSTRUCT*)lParam;
			if (wParam == WM_KEYDOWN)
			{
				if (GetKeyState(VK_CONTROL) && p->vkCode == 0x44)
				{
					std::cout << "程序被执行退出！" << "\n";
					exit(0);
				}
				if (GetKeyState(VK_TAB) && p->vkCode == VK_RETURN)
				{
					std::cout << "按下了TAB + ENTER" << "\n";
				}
			}
			return CallNextHookEx(NULL, nCode, wParam, lParam);
		});
	//Hook.startHook(cloudgameZero::InstallHookType::KEYBORAD_LL);
	std::this_thread::sleep_for(std::chrono::milliseconds(1));
	INT value{};
	unstable::RtlAdjustPrivilege(unstable::SeTakeOwnershipPrivilege, TRUE, FALSE, &value);
	
	//truested(L"cmd");

	/* 需要1毫秒时间来搭建线程并获取状态 */
	std::cout << "线程Id = " << Hook.getHookThreadId() << "\n";
	std::cout << "线程地址 = " << Hook.getThreadAddress() << "\n";
	std::unique_ptr<Regedit> reg = std::make_unique<Regedit>();
	//std::cout << std::boolalpha << reg->openKey(HKEY_LOCAL_MACHINE, "SOFTWARE") << "\n";
	//reg->addValue("", "TestBinaryVar", REG_BINARY, (const char*)&Hook, sizeof(WindowsHookA));
	//std::cout << reg->native_handle() << "\n";
	sectionBuffer collect;
	iniParser parser("version.ini", collect);
	//change(1600, 1200);
	parser.parse();
	parser.writer(parser.pretty);
	std::cout << collect.getString() << "\n";
	showMenu();
	/*std::shared_ptr<cgFix> ptr = nullptr;
	HRESULT hr = createInstance(IID_CLOUDGAME_FIX_ZERO_IID_IcgFix, reinterpret_cast<void**>(&ptr));
	if (FAILED(hr))
	{
		throw std::runtime_error("无法创建实例");
	}*/
	//std::cin >> hr;
	//CL()->info("Hello World");
	//Foundation::Tool::PRESSANYBOTTON();
	HANDLE INSTANCE_EVENT_CLOSE = CreateEventA(NULL, FALSE, FALSE, "cloudgameFixZero close process");
	if (INSTANCE_EVENT_CLOSE)
	{
		SetEvent(INSTANCE_EVENT_CLOSE);
	}
	return 0;
}