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

namespace comp
{
	static const auto memu =
		[]() -> std::vector<std::string_view>
		{
			std::vector<std::string_view> views;
			if (Infomation::isCloudPC)
			{
				views = {
					"1.修复系统",
					"2.修复更新",
					"3.关于此程序信息",
					"4.退出",
				};
			}
			else
			{
				views = {
					"1.修复系统",
					"2.修复更新",
					"3.修复游戏文件",
					"4.关于此程序信息",
					"5.退出",
				};
			}
			return views;
		}
	();

	void showMenu()
	{
		for (const std::string_view& i : comp::memu)
		{
			std::cout << i << "\n";
		}
	}

	void printHelp()
	{
		cleanConsoleBuffer(cloudgameZero::CONSOLE_OUTPUT_HANDLE);
		std::cout << R"(关于本程序：
这是使用库cloudgamefix开发的应用程序
关于cloudgamefix：
cloudgamefix是一个使用C++开发的库，提供了Windows Notification调用，日志系统，事件系统，Windows部分原生API封装
同时提供了ini文件解析器的实现

本程序是完全免费开源的

引用的第三方库：
	rapidjson
	boost-stacktrace
	libcurl

cloudgamefix仓库：
	gitee: https://gitee.com/eGlhb2p1emk/cloudgamefix
	github: https://github.com/Nobodychirs/cloudgamefix
)"
	<< std::format("程序编译日期： {} {} \n作者：{}\n版本：{}",__DATE__,__TIME__, Infomation::authorConf,Infomation::versionConf)
		<< "\n";
		PRESSANYBOTTON("按任意键返回...");
		cleanConsoleBuffer(cloudgameZero::CONSOLE_OUTPUT_HANDLE);
	}
}

template <class _Ty, size_t _Size>
class arrayConstIterator
{
public:
	using iterator_concept = std::contiguous_iterator_tag;
	using iterator_category = std::random_access_iterator_tag;
	using value_type = _Ty;
	using difference_type = ptrdiff_t;
	using pointer = const _Ty*;
	using reference = const _Ty&;

	enum { _EEN_SIZE = _Size }; // helper for expression evaluator

	constexpr arrayConstIterator() noexcept : _Ptr(), _Idx(0) {}

	constexpr explicit arrayConstIterator(pointer _Parg, size_t _Off = 0) noexcept : _Ptr(_Parg), _Idx(_Off) {}

	_NODISCARD constexpr reference operator*() const noexcept {
		return *operator->();
	}

	_NODISCARD constexpr pointer operator->() const noexcept {
		_STL_VERIFY(_Ptr, "cannot dereference value-initialized array iterator");
		_STL_VERIFY(_Idx < _Size, "cannot dereference out of range array iterator");
		return _Ptr + _Idx;
	}

	constexpr arrayConstIterator& operator++() noexcept {
		_STL_VERIFY(_Ptr, "cannot increment value-initialized array iterator");
		_STL_VERIFY(_Idx < _Size, "cannot increment array iterator past end");
		++_Idx;
		return *this;
	}

	constexpr arrayConstIterator operator++(int) noexcept {
		arrayConstIterator _Tmp = *this;
		++*this;
		return _Tmp;
	}

	constexpr arrayConstIterator& operator--() noexcept {
		_STL_VERIFY(_Ptr, "cannot decrement value-initialized array iterator");
		_STL_VERIFY(_Idx != 0, "cannot decrement array iterator before begin");
		--_Idx;
		return *this;
	}

	constexpr arrayConstIterator operator--(int) noexcept {
		arrayConstIterator _Tmp = *this;
		--*this;
		return _Tmp;
	}

	constexpr arrayConstIterator& operator+=(const ptrdiff_t _Off) noexcept {
		_Verify_offset(_Off);
		_Idx += static_cast<size_t>(_Off);
		return *this;
	}

	constexpr arrayConstIterator& operator-=(const ptrdiff_t _Off) noexcept {
		return *this += -_Off;
	}

	_NODISCARD constexpr ptrdiff_t operator-(const arrayConstIterator& _Right) const noexcept {
		_Compat(_Right);
		return static_cast<ptrdiff_t>(_Idx - _Right._Idx);
	}

	_NODISCARD constexpr reference operator[](const ptrdiff_t _Off) const noexcept {
		return *(*this + _Off);
	}

	_NODISCARD constexpr bool operator==(const arrayConstIterator& _Right) const noexcept {
		_Compat(_Right);
		return _Idx == _Right._Idx;
	}

	_NODISCARD constexpr std::strong_ordering operator<=>(const arrayConstIterator& _Right) const noexcept {
		_Compat(_Right);
		return _Idx <=> _Right._Idx;
	}

	constexpr void _Compat(const arrayConstIterator& _Right) const noexcept { // test for compatible iterator pair
		_STL_VERIFY(_Ptr == _Right._Ptr, "array iterators incompatible");
	}

	using _Prevent_inheriting_unwrap = arrayConstIterator;

	_NODISCARD constexpr pointer _Unwrapped() const noexcept {
		return _Ptr + _Idx;
	}

	constexpr void _Verify_with(const arrayConstIterator& _Last) const noexcept {
		// note _Compat check inside operator<=
		_STL_VERIFY(*this <= _Last, "array iterator range transposed");
	}

	constexpr void _Seek_to(pointer _It) noexcept {
		_Idx = static_cast<size_t>(_It - _Ptr);
	}

	_NODISCARD constexpr arrayConstIterator operator+(const ptrdiff_t _Off) const noexcept {
		arrayConstIterator _Tmp = *this;
		_Tmp += _Off;
		return _Tmp;
	}

	_NODISCARD constexpr arrayConstIterator operator-(const ptrdiff_t _Off) const noexcept {
		arrayConstIterator _Tmp = *this;
		_Tmp -= _Off;
		return _Tmp;
	}

	_NODISCARD_FRIEND constexpr arrayConstIterator operator+(
		const ptrdiff_t _Off, arrayConstIterator _Next) noexcept {
		_Next += _Off;
		return _Next;
	}
private:
	constexpr void _Verify_offset(const ptrdiff_t _Off) const noexcept {
		if (_Off != 0) {
			_STL_VERIFY(_Ptr, "cannot seek value-initialized array iterator");
		}

		if (_Off < 0) {
			_STL_VERIFY(_Idx >= size_t{ 0 } - static_cast<size_t>(_Off), "cannot seek array iterator before begin");
		}

		if (_Off > 0) {
			_STL_VERIFY(_Size - _Idx >= static_cast<size_t>(_Off), "cannot seek array iterator after end");
		}
	}

	pointer _Ptr;
	size_t _Idx;
};

template <class _Ty, size_t _Size>
class arrayIterator : public arrayConstIterator<_Ty, _Size> {
public:
	using _Mybase = arrayConstIterator<_Ty, _Size>;
	using iterator_concept = std::contiguous_iterator_tag;
	using iterator_category = std::random_access_iterator_tag;
	using value_type = _Ty;
	using difference_type = ptrdiff_t;
	using pointer = _Ty*;
	using reference = _Ty&;

	enum { _EEN_SIZE = _Size }; // helper for expression evaluator

	constexpr arrayIterator() noexcept {}

	constexpr explicit arrayIterator(pointer _Parg, size_t _Off = 0) noexcept : _Mybase(_Parg, _Off) {}

	_NODISCARD constexpr reference operator*() const noexcept {
		return const_cast<reference>(_Mybase::operator*());
	}

	_NODISCARD constexpr pointer operator->() const noexcept {
		return const_cast<pointer>(_Mybase::operator->());
	}

	constexpr arrayIterator& operator++() noexcept {
		_Mybase::operator++();
		return *this;
	}

	constexpr arrayIterator operator++(int) noexcept {
		arrayIterator _Tmp = *this;
		_Mybase::operator++();
		return _Tmp;
	}

	constexpr arrayIterator& operator--() noexcept {
		_Mybase::operator--();
		return *this;
	}

	constexpr arrayIterator operator--(int) noexcept {
		arrayIterator _Tmp = *this;
		_Mybase::operator--();
		return _Tmp;
	}

	constexpr arrayIterator& operator+=(const ptrdiff_t _Off) noexcept {
		_Mybase::operator+=(_Off);
		return *this;
	}

	_NODISCARD constexpr arrayIterator operator+(const ptrdiff_t _Off) const noexcept {
		arrayIterator _Tmp = *this;
		_Tmp += _Off;
		return _Tmp;
	}

	_NODISCARD_FRIEND constexpr arrayIterator operator+(const ptrdiff_t _Off, arrayIterator _Next) noexcept {
		_Next += _Off;
		return _Next;
	}

	constexpr arrayIterator& operator-=(const ptrdiff_t _Off) noexcept {
		_Mybase::operator-=(_Off);
		return *this;
	}

	using _Mybase::operator-;

	_NODISCARD constexpr arrayIterator operator-(const ptrdiff_t _Off) const noexcept {
		arrayConstIterator _Tmp = *this;
		_Tmp -= _Off;
		return _Tmp;
	}

	_NODISCARD constexpr reference operator[](const ptrdiff_t _Off) const noexcept {
		return const_cast<reference>(_Mybase::operator[](_Off));
	}

	using _Prevent_inheriting_unwrap = arrayIterator;

	_NODISCARD constexpr pointer _Unwrapped() const noexcept {
		return const_cast<pointer>(_Mybase::_Unwrapped());
	}
};

template<typename Ty,size_t size>
class array
{
public:
	using iterator = arrayIterator<Ty,size>;
	using const_iterator = arrayIterator<Ty, 0>;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

	constexpr array() = default;

	constexpr ~array() = default;

	constexpr iterator begin() noexcept
	{
		return iterator(arr, 0);
	}

	constexpr const_iterator cbegin() const noexcept
	{
		return begin();
	}

	constexpr reverse_iterator rbegin() noexcept
	{
		return reverse_iterator(end());
	}

	constexpr const_reverse_iterator crebgin() const noexcept
	{
		return rbegin();
	}

	constexpr iterator end() noexcept
	{
		return iterator(arr, size);
	}

	constexpr const_iterator cend() const noexcept
	{
		return end();
	}

	constexpr reverse_iterator rend() noexcept
	{
		return reverse_iterator(begin());
	}

	constexpr const_reverse_iterator crend() const noexcept
	{
		return rend();
	}

	constexpr void fill(const Ty& value) noexcept
	{
		std::fill_n(arr, size, value);
	}

	constexpr void swap(array& other) noexcept
	{
		_Swap_ranges_unchecked(arr, arr + size, other.arr);
	}

	constexpr Ty* get() noexcept
	{
		return arr;
	}

	constexpr const Ty* get() const noexcept
	{
		return arr;
	}

	constexpr Ty& at(std::size_t index) noexcept
	{
		static_assert(index < size, "array subscript out of range");
		return arr[index];
	}

	constexpr const Ty& at(std::size_t index) noexcept
	{
		static_assert(index < size, "array subscript out of range");
		return arr[index];
	}

	_NODISCARD constexpr std::size_t size()
	{
		return size;
	}

	constexpr Ty& operator[](std::size_t index) noexcept
	{
		return at(index);
	}

	constexpr const Ty& operator[](std::size_t index) const noexcept
	{
		return at(index);
	}

	Ty arr[size];
};

int main(int argc, CHAR** argv)
{
	std::cout << "准备初始化实例" << "\n";
	/* Init Process Start */
	std::cout << "正在调用：std::ios::sync_with_stdio(false);" << "\n";
	std::ios::sync_with_stdio(false);
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
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
			logger->stackTrace();
			throw std::exception("检测到错误在创建实例函数（cloudgameZero::Interface::createInstance）上，");
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
	bool exit = false;
	SetConsoleTitleA(std::format("{} : {}", Infomation::versionConf, Infomation::isCloudPC ? "云电脑模式" : "云游戏模式").c_str());
	if(Infomation::isCloudPC)
	{
		logger->info("检测到云电脑，准备切换为云电脑模式!");
		int choice = 0;
		std::string trim;
		while (true) {
			cleanConsoleBuffer(cloudgameZero::CONSOLE_OUTPUT_HANDLE);
			std::cout << "cloudgamefix主菜单" << "\n\n";
			comp::showMenu();
			std::cout << "在下面输入你的选择：" << "\n";
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
						std::cout << "错误的输入!您必须输入一个整型(数字)" << "\n";
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
				notification->Init();
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
			case 3:
				comp::printHelp();
				break;
			case 4:
				exit = true;
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
			comp::showMenu();
			std::cout << "cloudgamefix主菜单" << "\n\n";
			comp::showMenu();
			std::cout << "在下面输入你的选择：" << "\n";
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
						std::cout << "错误的输入!您必须输入一个整型(数字)" << "\n";
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
				notification->Init();
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
			case 3:
				cleanConsoleBuffer(cloudgameZero::CONSOLE_OUTPUT_HANDLE);
				std::cout << "正在准备事务..." << "\n";
				cgfix->repairGameFile();
				std::cout << "事务完成" << "\n";
				cleanConsoleBuffer(cloudgameZero::CONSOLE_OUTPUT_HANDLE);
				break;
			case 4:
				comp::printHelp();
				break;
			case 5:
				exit = true;
				break;
			default:
				break;
			}
			if (exit)
				break;
		}
	}
	/* clean */
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	logger->info("开始清理cloudgamefix库中的对象");
	try {
		cgfix->Release();
		cgsystem->Release();
		notification->Release();
	}
	catch (...) {
		logger->stackTrace();
		logger->fatal("在清理对象时可能发生非法内存问题！");
		std::abort();
	}
}