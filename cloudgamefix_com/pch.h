/*
MIT License

Copyright (c) 2023 eGlhb2p1emk

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
/*
关于本库：
此库是提供给网易云游戏Windows系统的C++简易程序库
此文件封装了WinToast，jthread等库，向派生接口提供支持
同时提供了日志记录库
注：
此库需要安装第三方库，且需要C++20标准支持
需要配置vcpkg安装
备注：
WinToast的许可证声明已在命名空间上面放置，在分发时需保留，否则后果自负
*/
#pragma once
#ifndef CLOUDGAME_FIX_ZERO_H
#define CLOUDGAME_FIX_ZERO_H

#define WIN32_LEAN_AND_MEAN

#define ENABLE_NOCRT_FUNC true

/* Windows SDK And C++ Standard Libray Files | Windows SDK默认提供的库以及C++20提供的标准库 */
#include <map>
#include <io.h>
#include <stack>
#include <mutex>
#include <ctime>
#include <regex>
#include <array>
#include <format>
#include <string>
#include <thread>
#include <string>
#include <vector>
#include <chrono>
#include <atomic>
#include <conio.h>
#include <sstream>
#include <roapi.h>
#include <fstream>
#include <Psapi.h>
#include <ShlObj.h>
#include <iostream>
#include <assert.h>
#include <iostream>
#include <Windows.h>
#include <algorithm>
#include <stdexcept>
#include <strsafe.h>
#include <shellapi.h>
#include <ShObjIdl.h>
#include <functional>
#include <TlHelp32.h>
#include <filesystem>
#include <wrl/event.h>
#include <yvals_core.h>
#include <propvarutil.h>
#include <source_location>
#include <wrl/implements.h>
#include <condition_variable>
#include <functiondiscoverykeys.h>
#include <windows.ui.notifications.h>
/* Third-party library references | 从第三方引用的库 */
#pragma warning(push)
#pragma warning(disable : 26451)
#pragma warning(disable : 26819)
#pragma warning(disable : 33010)
#pragma warning(disable : 26495)
#pragma warning(disable : 6388)
#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/writer.h>
#include <rapidjson/prettywriter.h>
#include <boost/stacktrace.hpp>
#include <curl/curl.h>
#pragma warning(pop)
/*
vcpkg:

rapidjson -> vcpkg install rapidjson:x64-windows
boost-stacktrace -> vcpkg install boost-regex:x64-windows
curl -> vcpkg install curl

*/
#pragma comment(lib, "user32")
#pragma comment(lib, "shlwapi")
#pragma push_macro("new")

/* ATL Support */
#if __has_include("framework.h")
#include"framework.h"
#endif

#define EnableZeroLibrayExceptions true
#define EXPORT_ZERO

using namespace Microsoft::WRL;
using namespace ABI::Windows::Data::Xml::Dom;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::UI::Notifications;
using namespace Windows::Foundation;


#if _HAS_CXX20 && __has_include("rapidjson/writer.h") && __has_include("boost/stacktrace.hpp")
namespace cloudgameZero
{
	//存储此库基本的信息
	namespace Infomation
	{
		static const HKEY HKCU = ((HKEY)(ULONG_PTR)((LONG)0x80000001));
		static const HKEY HKLM = ((HKEY)(ULONG_PTR)((LONG)0x80000002));
		static const HKEY HKCR = ((HKEY)(ULONG_PTR)((LONG)0x80000000));
		static LPCSTR author_Conf = "juzi xiao";
		static LPCSTR version_Conf = "cloudgame-fix_zero 2.05 pre-build zero Private | The C++ Edition";
		static LPCSTR __cg_Instance__ = "cloudgame-fix_zero 2.05 pre-build zero Private Instance : ";
		static LPCSTR versionConf = "cloudgame-fix_zero 2.10 pre-build zero Private sigma | The C++ Edition";
		static LPCSTR _USER_cloudpc = "netease";
		static LPCWSTR APPNAME = L"cloudgameFixZero";
		static LPCWSTR AUMI = L"cloudgameFixZero";
		//用于后期库的基本安全功能处理
		namespace Secutriy
		{
			static std::mutex mutexLock;
			static LPCSTR urlLinkRegex = "^(https://|http://|ftp://).+/.*";
			static LPCSTR lnkPathRegex = "^([a-z]|[A-Z]){1}:\\\\.*(.lnk)$";
			static LPCSTR lnkPathRegexNoEscape = "^([a-z]|[A-Z]){1}:/.+.(lnk)$";
		}
		/* 为curl提供的两个回调临时函数 */
		constexpr auto curlResponseCallBack = [](char* ptr, size_t size, size_t nmemb, void* userdata) {
			std::string* str = (std::string*)userdata;
			str->append(ptr, size * nmemb);
			return size * nmemb;
			};
		constexpr auto curlFileCallback = [](char* ptr, size_t size, size_t nmemb, void* userdata) noexcept -> size_t {
			auto* f = (std::fstream*)userdata;
			f->write(ptr, size * nmemb);
			return size * nmemb;
			};
		static std::mutex curlLock;
	}
	/* cloudgameZero提供的单独句柄，用于实现日志库功能 */
	static const HANDLE CONSOLE_OUTPUT_HANDLE = GetStdHandle(STD_OUTPUT_HANDLE);

	/*用于特定类输出日志内容提供的简易函数，同时标识当前发布模式状态 .*/
#ifdef NDEBUG
	static const bool IS_DEBUG = false;
	template<typename Ty>
	/**
	 * \brief 此部分写于2023/7/23.
	 * \brief 警告：如果要显示额外日志信息，请使用Debug发布模式而不是Realease
	 */
	inline void PrintError(Ty msg) noexcept {}
	/**
	 * \brief 此部分写于2023/7/23.
	 * \brief 警告：如果要显示额外日志信息，请使用Debug发布模式而不是Realease
	 */
	template<typename Ty>
	void inline DEBUG_MESSAGE(Ty str) noexcept {}
#else
	static const bool IS_DEBUG = true;
	/**
	 * \brief 此部分写于2023/7/23
	 * \brief 将调试信息打印到控制台，同时清除缓冲区.
	 * \brief 批注
	 * \brief 此函数与DEBUG_MESSAGE使用对象区别在于本函数使用std::wcerr
	 * \brief 如果std::wostream导出的对象接受msg的数据类型，则编译通过，否则编译失败
	 * \brief -----------------------以下部分写于2023/8/5-------------------------------
	 * \brief 此函数在打印完成后将检测流状态，如果流损坏，它将会临时清除流的数据，设置locale为chs，随后重新打印文字
	 * \brief 如果使用了Foundation::Tool的字符串转换函数，可能会导致触发流损坏导致std::wcout尝试修复并再次输出字符串
	 * \param msg 一个泛型参数
	 */
	template<typename Ty>
	void PrintError(Ty msg) noexcept
	{
		std::unique_lock<std::mutex> lock(Infomation::Secutriy::mutexLock);
		std::wcerr.clear();
		std::wcerr.imbue(std::locale("chs"));
		std::wcerr << msg;
		std::wcerr.imbue(std::locale("C"));
		std::wcerr << std::endl;
	}
	/**
	 * \brief 此部分写于2023/7/23
	 * \brief 将调试信息打印到控制台，同时清除缓冲区.
	 * \brief 批注
	 * \brief 此函数与PrintError使用对象区别在于本函数使用std::wcout
	 * \brief 如果std::wostream导出的对象接受msg的数据类型，则编译通过，否则编译失败
	 * \brief -----------------------以下部分写于2023/8/5-------------------------------
	 * \brief 此函数在打印完成后将检测流状态，如果流损坏，它将会临时清除流的数据，设置locale为chs，随后重新打印文字
	 * \brief 如果使用了Foundation::Tool的字符串转换函数，可能会导致触发流损坏导致std::wcout尝试修复并再次输出字符串
	 * \param msg 一个泛型参数
	 */
	template<class Ty>
	void DEBUG_MESSAGE(Ty str) noexcept
	{
		std::unique_lock<std::mutex> lock(Infomation::Secutriy::mutexLock);
		std::wcout.clear();
		std::wcout.imbue(std::locale("chs"));
		std::wcout << str;
		std::wcout.imbue(std::locale("C"));
		std::wcout << std::endl;
	}

#endif //NDEBUG

	/* 基于jthread和Windows API封装的类 */
	class ThreadPlatform
	{
	public:
		using native_handle_type = std::thread::native_handle_type;

		ThreadPlatform() = delete;

		/**
		 * \brief 此部分写于2023/7/25
		 * \brief 有参构造函数
		 * \brief 设置对象的函数并初始化线程
		 *
		 * \param f 一个指向任意函数的指针
		 * \param args 一个不定的参数列表
		 */
		template <typename Fn, typename... Args>
		explicit ThreadPlatform(Fn&& f, Args &&...args) : _suspend(true), Stop(false), _Start(false)
		{
			std::function<decltype(f(args...))()> func = std::bind(std::forward<Fn>(f), std::forward<Args>(args)...);
			this->func = [func]() {func(); };
		}

		virtual ~ThreadPlatform()
		{
			this->threadManager.request_stop();
			if (!this->alreadyJoin)
			{
				SuspendThread(this->native_handle());
				this->threadManager.detach();
			}
		}

		/**
		 * \brief 此部分写于2023/7/25
		 * \brief 一个函数模板，用于设置函数并重置状态
		 * \brief 批注:
		 * \brief 此函数需要在线程已结束的前提下才能运行
		 *
		 * \param f 一个指向任意函数的指针
		 * \param args 一个不定的参数列表
		 */
		template<typename Fn, typename ... Args>
		void LoadFunc(Fn&& f, Args && ...args)
		{
			if (this->_Start)
			{
				PrintError("An error was detected because the thread was running and the function could not be reloaded!");
				return;
			}
			std::function<decltype(f(args...))()> func = std::bind(std::forward<Fn>(f), std::forward<Args>(args)...);
			this->func = [func]()
				{
					func();
				};
			this->_suspend = true;
			this->Stop = false;
			this->_Start = false;
		}

		/**
		 * \brief 此部分写于2023/7/23.
		 * \brief 创建对象后，此函数将立即启动线程
		 * \brief 注意
		 * \brief 此函数如果已经执行，将不可再次调用，直到用户调用StopThread成员函数，否则会向控制台打印一行错误消息并直接return此成员函数
		 * \brief 同时保存一个句柄用于控制线程
		 *
		 */
		inline void Start()
		{
			if (this->_Start)
			{
				PrintError("An error has occurred! The thread has already started!");
				return;
			}
			this->threadManager = std::jthread(this->func);
			this->_Start = true;
			this->_suspend = false;
		}

		/**
		 * \brief 此部分写于2023/7/23.
		 * \brief 此函数为Start成员函数的重载版本，此版本允许用户设置延时，此函数将调用异步线程，在延时结束时直接调用Start函数开启线程
		 * \brief 注意
		 * \brief 此函数如果已经执行，将不可再次调用，直到用户调用StopThread成员函数，否则会向控制台打印一行错误消息并直接return此成员函数
		 * \param milliseconds 休眠的毫秒数，数据类型为size_t
		 */
		inline void Start(size_t milliseconds)
		{
			if (this->_Start) {
				PrintError("An error has occurred! The thread has already started!");
				return;
			}
			std::jthread tmp([this, milliseconds]() {
				std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
				this->Start();
				});
			tmp.detach();
		}

		/**
		 * \brief 此部分写于2023/7/23.
		 * \brief 此函数将与主线程分离
		 * \brief 线程调用之后，此线程就成为守护线程，驻留后台运行，与之关联的线程对象将失去对目标线程的关联，无法再通过线程对象取得该线程的控制权。
		 * \brief 当线程主函数执行完之后，将自动清理。
		 * \brief 批注
		 * \brief 此函数还会影响以下成员函数
		 * \brief join(),StopThread(),get_id(),joinable()
		 * \brief 如果仅作为守护线程，请调用此函数，否则请谨慎使用
		 */
		inline void detach()
		{
			if (!this->_Start)
			{
				this->Start();
			}
			this->threadManager.detach();
			this->Detach = true;
		}

		/**
		 * \brief 此部分写于2023/7/23.
		 * \brief 获取该对象关联线程的原生系统句柄.
		 *
		 * \return 如果线程启动则返回该对象关联线程的原生系统句柄，否则将返回NULL
		 */
		_NODISCARD native_handle_type native_handle() noexcept
		{
			if (this->_Start) {
				return this->threadManager.native_handle();
			}
			else {
				return NULL;
			}
		}

		/**
		 * \brief 此部分写于2023/7/23.
		 * \brief 此函数将使线程合流，插入到主线程中，主线程将持续阻塞直到线程结束
		 */
		inline void join()
		{
			if (!this->_Start)
			{
				this->Start();
			}
			this->threadManager.join();
			this->alreadyJoin = true;
		}

		/**
		 * \brief 此部分写于2023/7/26.
		 * \brief 终止对象关联的线程
		 * \brief 批注
		 * \brief 如果用户运行了detach函数，此函数可能会出现异常
		 */
		void StopThread()
		{
			if (this->_Start) {
				this->threadManager.request_stop();
				SuspendThread(this->native_handle());
				this->Stop = true;
				this->_Start = false;
			}
			else {
				PrintError("You must start the thread before you stop!");
			}
		}

		/**
		 * \brief 此部分写于2023/7/26.
		 * \brief 此函数将会把该对象被挂起的关联线程恢复
		 * \brief 如果线程没有开启或没有挂起将会向控制台打印错误消息并return
		 */
		inline void Resume() noexcept
		{
			if (this->_Start && !this->_suspend) {
				SuspendThread(this->threadManager.native_handle());
			}
			else {
				if (!this->_Start) {
					PrintError("The thread did not start, is this intentional?");
				}
				else {
					PrintError("The thread is not suspend, is this intentional?");
				}
				return;
			}
		}

		/**
		 * \brief 此部分写于2023/7/26.
		 * \brief 此函数将会把该对象关联的进程挂起
		 * \brief 如果线程没有开启或已经挂起将会向控制台打印错误消息并return
		 */
		inline void Suspend() noexcept
		{
			if (this->_Start && !this->_suspend) {
				SuspendThread(this->threadManager.native_handle());
			}
			else {
				if (!this->_Start) {
					PrintError("The thread did not start, is this intentional?");
				}
				else {
					PrintError("The thread is not suspend, is this intentional?");
				}
				return;
			}
		}
		inline std::jthread& Get() noexcept { return this->threadManager; }
		inline bool joinable() noexcept { return threadManager.joinable(); }
		inline bool is_Stop() noexcept { return this->Stop; }
		inline std::jthread::id get_id() noexcept { return this->threadManager.get_id(); }
	private:
		std::jthread threadManager;
		std::function<void()> func;
		std::atomic_bool Stop;
		std::atomic_bool _suspend;
		std::atomic_bool Detach;
		std::atomic_bool alreadyJoin;
		std::atomic_bool _Start;
	};

	/* cloudgamefixZero的基础库命名空间，存放了程序需要的函数和常量，是最基础的依赖实现部分 */
	namespace Foundation
	{
		/* 存储关于动态链接库的函数和常量 */
		namespace dynamincLibrayFunc
		{
			/* 预定义函数句柄 */
			static const HINSTANCE NTDLL = GetModuleHandleW(L"NTDLL.dll");
			static const HINSTANCE USER32 = LoadLibraryW(L"user32.dll");
			static const HINSTANCE KERNEL = LoadLibraryW(L"kernel32.dll");
			static const HINSTANCE COMBASE = LoadLibraryW(L"ComBase.dll");
			/* 预定义宏 */
#define WINUEAPI WINAPI
/* WINUEAPI是一个宏，全称WINDOWS_UN_EXTERN_API，即代表未提供声明或未文档化的函数 */

/**
 * \brief 此部分写于2023/7/25
 * \brief 一个模板函数，用于将动态链接库的函数导出并绑定到函数指针.
 * \param handle 动态链接库的句柄
 * \param FuncName 函数名称
 * \param pointer 函数指针
 * \return 如果函数成功则返回S_OK，如果句柄有误，则返回E_INVALIDARG，如果函数名称有误或无法获取函数地址，则返回E_FAIL
 */
			template<typename Fn>
			static HRESULT WINAPI loadFunFromLib(HINSTANCE handle, LPCSTR FuncName, Fn& pointer)
			{
				if (!handle) {
					return E_INVALIDARG;
				}
				else {
					pointer = reinterpret_cast<Fn>(GetProcAddress(handle, FuncName));
					if (pointer != nullptr) {
						return S_OK;
					}
					else {
#if EnableZeroLibrayExceptions
						throw std::runtime_error("Can't load proc Address，Are you sure that the handles and functions are correct?");
#else
						PrintError("Can't load proc Address，Are you sure that the handles and functions are correct?");
#endif
						return E_FAIL;
					}
				}
			}

			/* 此命名空间提供了function命名空间的函数指针类型 */
			namespace typePtr
			{
				typedef VOID(WINUEAPI* type_RtlGetNtVersionNumbers)(_Inout_ DWORD* dwMajor, _Inout_ DWORD* dwMinor, _Inout_ DWORD* dwBuilder);
				typedef HRESULT(FAR WINUEAPI* type_SetCurrentProcessExplicitAppUserModelID)(__in PCWSTR AppID);
				typedef HRESULT(FAR WINUEAPI* type_PropVariantToString)(_In_ REFPROPVARIANT propvar, _Out_writes_(cch) PWSTR psz, _In_ UINT cch);
				typedef HRESULT(FAR WINUEAPI* type_RoGetActivationFactory)(_In_ HSTRING activatableClassId, _In_ REFIID iid, _COM_Outptr_ void** factory);
				typedef HRESULT(FAR WINUEAPI* type_WindowsCreateStringReference)(_In_reads_opt_(length + 1) PCWSTR sourceString, UINT32 length, _Out_ HSTRING_HEADER* hstringHeader, _Outptr_result_maybenull_ _Result_nullonfailure_ HSTRING* string);
				typedef INT(WINUEAPI* type_MessageBoxTimeoutA)(HWND hWnd, _In_ LPCSTR lpText, _In_ LPCSTR lpCaption, _In_ UINT uType, _In_ WORD wLanguageId, _In_ DWORD dwMilliseconds);
				typedef INT(WINUEAPI* type_MessageBoxTimeoutW)(HWND hWnd, _In_ LPCWSTR lpText, _In_ LPCWSTR lpCaption, _In_ UINT uType, _In_ WORD wLanguageId, _In_ DWORD dwMilliseconds);
				typedef NTSTATUS(WINAPI* type_RtlGetVersion)(PRTL_OSVERSIONINFOW);
				typedef PCWSTR(FAR WINUEAPI* type_WindowsGetStringRawBuffer)(_In_ HSTRING string, _Out_opt_ UINT32* length);
				typedef HRESULT(FAR WINUEAPI* type_WindowsDeleteString)(_In_opt_ HSTRING string);
				namespace unstable
				{
					typedef UINT(WINUEAPI* type_RtlAdjustPrivilege)(ULONG Privilege, BOOL bEnablePrivilege, BOOL IsThreadPrivilege, PINT PreviousValue);
				}
			}

			/* 此命名空间提供了基于loadFunFromLib函数封装的未文档化/未导出函数 */
			namespace function
			{
				/**
				 * \brief 此部分写于2023/7/25.
				 * \brief 此函数属于未文档化Windows API
				 * \brief
				 * \brief 获取Windows操作系统内部系统版本号
				 * \param dwMajor 指向DWORD(32位无符号整数)的地址，用于接收NT内核版本
				 * \param dwMinor 指向DWORD(32位无符号整数)的地址
				 * \param dwBuilder 指向DWORD(32位无符号整数)的地址，用于接收Windows构建版本号
				 */
				static VOID WINAPI RtlGetNtVersionNumbers(_Inout_ DWORD* dwMajor, _Inout_ DWORD* dwMinor, _Inout_ DWORD* dwBuilder)
				{
					void(WINAPI * func)(DWORD*, DWORD*, DWORD*) = nullptr;
					if (HRESULT hr = loadFunFromLib(NTDLL, "RtlGetNtVersionNumbers", func); SUCCEEDED(hr)) {
						func(dwMajor, dwMinor, dwBuilder);
					}
				}
				/**
				 * \brief 此部分写于2023/7/25.
				 * \brief 在MessageBoxA原有的功能上提供了超时功能，如果达到用户传入参数时间，则自动关闭
				 * \brief 批注：
				 * \brief 以下参数中hWnd,lpText,lpCaption,uType参数
				 * \brief 请参考以下链接:
				 * \brief https://learn.microsoft.com/zh-cn/windows/win32/api/winuser/nf-winuser-messageboxa
				 * \param hWnd 参考链接文档
				 * \param lpText 参考链接文档
				 * \param lpCaption 参考链接文档
				 * \param uType 参考链接文档
				 * \param wLanguageId 语言ID，通常情况下请设置为NULL或者0即可
				 * \param dwMilliseconds 超时时间，单位毫秒
				 * \return 返回值同MessageBoxA
				 */
				static int WINUEAPI MessageBoxTimeoutA(HWND hWnd, _In_ LPCSTR lpText, _In_ LPCSTR lpCaption, _In_ UINT uType, _In_ WORD wLanguageId, _In_ DWORD dwMilliseconds) noexcept
				{
					int (WINAPI * MessageBoxTimeOut_)(HWND, LPCSTR, LPCSTR, UINT, WORD, DWORD) = nullptr;
					if (HRESULT hr = loadFunFromLib(USER32, "MessageBoxTimeoutA", MessageBoxTimeOut_); SUCCEEDED(hr)) {
						if (hWnd == NULL) {
							hWnd = GetForegroundWindow();
							return MessageBoxTimeOut_(hWnd, lpText, lpCaption, uType, wLanguageId, dwMilliseconds);
						}
						else {
							return MessageBoxTimeOut_(hWnd, lpText, lpCaption, uType, wLanguageId, dwMilliseconds);
						}
					}
					DEBUG_MESSAGE("Failed To Load");
					return NULL;
				}

				/**
				 * \brief 此部分写于2023/7/25.
				 * \brief 在MessageBoxW原有的功能上提供了超时功能，如果达到用户传入参数时间，则自动关闭
				 * \brief 批注：
				 * \brief 以下参数中hWnd,lpText,lpCaption,uType参数
				 * \brief 请参考以下链接:
				 * \brief https://learn.microsoft.com/zh-cn/windows/win32/api/winuser/nf-winuser-messageboxw
				 * \param hWnd 参考链接文档
				 * \param lpText 参考链接文档
				 * \param lpCaption 参考链接文档
				 * \param uType 参考链接文档
				 * \param wLanguageId 语言ID，通常情况下请设置为NULL或者0即可
				 * \param dwMilliseconds 超时时间，单位毫秒
				 * \return 返回值同MessageBoxW
				 */
				static int WINUEAPI MessageBoxTimeoutW(_In_ HWND hWnd, _In_ LPCWSTR lpText, _In_ LPCWSTR lpCaption, _In_ UINT uType, _In_ WORD wLanguageId, _In_ DWORD dwMilliseconds) noexcept
				{
					int (WINAPI * MessageBoxTimeOut_)(HWND, LPCWSTR, LPCWSTR, UINT, WORD, DWORD) = nullptr;
					if (HRESULT hr = loadFunFromLib(USER32, "MessageBoxTimeoutW", MessageBoxTimeOut_); SUCCEEDED(hr)) {
						if (hWnd == NULL) {
							hWnd = GetForegroundWindow();
							return MessageBoxTimeOut_(hWnd, lpText, lpCaption, uType, wLanguageId, dwMilliseconds);
						}
						else {
							return MessageBoxTimeOut_(hWnd, lpText, lpCaption, uType, wLanguageId, dwMilliseconds);
						}
					}
					return -1;
				}

				/**
				 * \brief 此部分写于2023/7/25.
				 * \brief 基于指定的字符串创建新的字符串引用。
				 * \brief 批注：
				 * \brief 此函数属于未导出函数，已经文档化，关于文档信息
				 * \brief 请参考以下链接：
				 * \brief https://learn.microsoft.com/zh-cn/windows/win32/api/winstring/nf-winstring-windowscreatestringreference
				 * \param sourceString
				 * \param 一个以 null 结尾的字符串，用作新 HSTRING 的源。如果长度为 0，则 NULL 值表示空字符串。 应在堆栈帧上分配
				 * \param length
				 * \param SourceString 的长度（以 Unicode 字符为单位）。 如果 sourceString 为 NULL，则必须为 0。 如果大于 0， sourceString 必须具有终止 null 字符
				 * \param hstringHeader
				 * \param 指向Windows 运行时用来将字符串标识为字符串引用或快速传递字符串的结构的指针。
				 * \param string
				 * \param 指向新创建的字符串的指针;如果发生错误,则为 NULL,将覆盖 字符串 中的任何现有内容,HSTRING 是标准句柄类型
				 * \returns 成功
				 * \returns S_OK			已成功创建 [**HSTRING**] (/windows/win32/winrt/hstring)
				 * \returns 失败
				 * \returns E_INVALIDARG	字符串或 hstringHeader 为 NULL，或者字符串不是以null结尾的
				 * \returns E_OUTOFMEMORY	未能分配新的 [**HSTRING**] (/windows/win32/winrt/hstring)
				 * \returns E_POINTER		sourceString为NULL,长度为非零
				 */
				static HRESULT FAR WINUEAPI WindowsCreateStringReference(PCWSTR sourceString, UINT32 length, HSTRING_HEADER* hstringHeader, HSTRING* string) noexcept
				{
					HRESULT(FAR WINAPI * f_WindowsCreateStringReference)(PCWSTR, UINT32, _Out_ HSTRING_HEADER*, HSTRING*) = nullptr;
					loadFunFromLib(COMBASE, "WindowsCreateStringReference", f_WindowsCreateStringReference);
					return f_WindowsCreateStringReference(sourceString, length, hstringHeader, string);
				}

				/**
				 * \brief 此部分写于2023/7/25.
				 * \brief 检索指定字符串的后盾缓冲区。
				 * \brief 批注：
				 * \brief 此函数属于未导出函数，已经文档化，关于文档信息
				 * \brief 请参考以下链接：
				 * \brief https://learn.microsoft.com/zh-cn/windows/win32/api/winstring/nf-winstring-windowsgetstringrawbuffer
				 * \param string 要为其检索后退缓冲区的可选字符串,可以为 NULL
				 * \param length
				 * \param 指向UINT32的可选指针。如果为长度传递NULL，则忽略NULL
				 * \param 如果长度是指向UINT32的有效指针，并且字符串是有效的HSTRING，则在成功完成后，该函数会将值设置为字符串后退缓冲区中Unicode字符数(（包括嵌入的null字符），但不包括终止null)
				 * \param 如果length是指向UINT32的有效指针，并且字符串为NULL，则按 长度 指向的值设置为 0。
				 * \return 返回指向为 字符串提供后盾存储的缓冲区的指针;如果字符串为NULL或空字符串，则为空字符串。
				 */
				static PCWSTR FAR WINUEAPI WindowsGetStringRawBuffer(_In_ HSTRING string, UINT32* length) noexcept
				{
					PCWSTR(FAR WINAPI * f_WindowsGetStringRawBuffer)(_In_ HSTRING string, _Out_opt_ UINT32 * length);
					loadFunFromLib(COMBASE, "WindowsGetStringRawBuffer", f_WindowsGetStringRawBuffer);
					return f_WindowsGetStringRawBuffer(string, length);
				}

				/**
				 * \brief 此部分写于2023/7/25.
				 * \brief 递减字符串缓冲区的引用计数。
				 * \brief 批注：
				 * \brief 此函数属于未导出函数，已经文档化，关于文档信息
				 * \brief 请参考以下链接：
				 * \brief https://learn.microsoft.com/zh-cn/windows/win32/api/winstring/nf-winstring-windowsdeletestring
				 *
				 * \param string 要删除的字符串
				 * \param 如果 字符串 是由 WindowsCreateStringReference创建的快速传递字符串或者如果字符串为NULL或空，则不执行任何操作并返回S_OK
				 * \return 此函数无论如何必定会返回一个S_OK
				 */
				static HRESULT FAR WINUEAPI WindowsDeleteString(_In_opt_ HSTRING string) noexcept
				{
					HRESULT(FAR WINAPI * f_WindowsDeleteString)(_In_opt_ HSTRING string);
					HINSTANCE Handle = LoadLibraryW(L"Combase.dll");
					if (Handle) {
						loadFunFromLib(Handle, "WindowsDeleteString", f_WindowsDeleteString);
						FreeLibrary(Handle);
						return f_WindowsDeleteString(string);
					}
					return S_FALSE;
				}

				/**
				 * \brief 将PROPVARIANT数据类型转换为PWSTR类型.
				 *
				 * \param propvar
				 * \param psz
				 * \param cch
				 * \return
				 */
				static HRESULT FAR WINUEAPI PropVariantToString(_In_ REFPROPVARIANT propvar, PWSTR psz, _In_ UINT cch) noexcept
				{
					HRESULT(FAR WINAPI * f_PropVariantToString)(_In_ const PROPVARIANT & propvar, _Out_writes_(cch) PWSTR psz, _In_ UINT cch) = nullptr;
					HRESULT hr = loadFunFromLib(COMBASE, "WindowsDeleteString", f_PropVariantToString);
					if (FAILED(hr))
					{
						return E_FAIL;
					}
					return f_PropVariantToString(propvar, psz, cch);
				}

				/**
				*
				 * 此函数RoGetActivationFactory的封装，用于获取指定运行时类的激活工厂。
				 * \brief 批注：
				 * \brief 此函数属于未导出函数，已经文档化，关于文档信息
				 * \brief 请参考以下链接:
				 *
				 * \param activatableClassId 可激活类的GUID
				 * \param factory 激活工厂
				 * \return 如果此函数成功，它将返回S_OK。否则，它将返回HRESULT错误代码。
				 */
				template<typename Factory>
				inline HRESULT FAR WINUEAPI Wrap_GetActivationFactory(_In_ HSTRING activatableClassId, _Inout_ Microsoft::WRL::Details::ComPtrRef<Factory> factory) noexcept {
					HRESULT(FAR WINAPI * func)(HSTRING, const IID&, void**) = nullptr;
					HRESULT hr = loadFunFromLib(COMBASE, "RoGetActivationFactory", func);
					if (FAILED(hr))
					{
						return E_FAIL;
					}
					return func(activatableClassId, IID_INS_ARGS(factory.ReleaseAndGetAddressOf()));
				}

				/**
				 * 此函数用于获取系统版本信息.
				 * \brief 批注：
				 * \brief 此函数属于未导出，未文档化函数
				 *
				 * \return 如果函数成功，它将返回类型RTL_OSVERSIONINFOW的结构体
				 */
				static RTL_OSVERSIONINFOW FAR WINUEAPI RtlGetVersion() noexcept {
					NTSTATUS(WINAPI * RtlGetVersionPtr)(PRTL_OSVERSIONINFOW) = nullptr;
					if (SUCCEEDED(loadFunFromLib(NTDLL, "RtlGetVersion", RtlGetVersionPtr)))
					{
						RTL_OSVERSIONINFOW rovi = { 0 };
						rovi.dwOSVersionInfoSize = sizeof(rovi);
						if (RtlGetVersionPtr(&rovi) == (0x00000000)) {
							return rovi;
						}
					}
					RTL_OSVERSIONINFOW rovi = { 0 };
					return rovi;
				}

				/* 此命名空间存储了可能会导致敏感行为的Windows未导出API和这些API可能需要的常量. */
				namespace unstable
				{
					enum SePrivilege : ULONG
					{
						SeUnsolicitedInputPrivilege = 0x00,
						SeUnknownInvalidPrivilege = 0x01,
						SeCreateTokenPrivilege = 0x02,
						SeAssignPrimaryTokenPrivilege = 0x03,
						SeLockMemoryPrivilege = 0x04,
						SeIncreaseQuotaPrivilege = 0x05,
						SeMachineAccountPrivilege = 0x06,
						SeTcbPrivilege = 0x07,
						SeSecurityPrivilege = 0x08,
						SeTakeOwnershipPrivilege = 0x09,
						SeLoadDriverPrivilege = 0x0A,
						SeSystemProfilePrivilege = 0x0B,
						SeSystemtimePrivilege = 0x0C,
						SeProfileSingleProcessPrivilege = 0x0D,
						SeIncreaseBasePriorityPrivilege = 0x0E,
						SeCreatePagefilePrivilege = 0x0F,
						SeCreatePermanentPrivilege = 0x10,
						SeBackupPrivilege = 0x11,
						SeRestorePrivilege = 0x12,
						SeShutdownPrivilege = 0x13,
						SeDebugPrivilege = 0x14,
						SeAuditPrivilege = 0x15,
						SeSystemEnvironmentPrivilege = 0x16,
						SeChangeNotifyPrivilege = 0x17,
						SeRemoteShutdownPrivilege = 0x18,
						SeUndockPrivilege = 0x19,
						SeSyncAgentPrivilege = 0x1A,
						SeEnableDelegationPrivilege = 0x1B,
						SeManageVolumePrivilege = 0x1C,
						SeImpersonatePrivilege = 0x1D,
						SeCreateGlobalPrivilege = 0x1E,
						SeTrustedCredManAccessPrivilege = 0x1F,
						SeRelabelPrivilege = 0x20,
						SeIncreaseWorkingSetPrivilege = 0x21,
						SeTimeZonePrivilege = 0x22,
						SeCreateSymbolicLinkPrivilege = 0x23,
						SeDelegateSessionUserImpersonatePrivilege = 0x24
					};

					/**
					 * \brief 提升进程的访问权限.
					 * \brief 此函数为未公开函数
					 *
					 * \param Privilege 权限id
					 * \param bEnablePrivilege 如果为TRUE,则开启权限，反之关闭
					 * \param IsThreadPrivilege 如果为TRUE,则仅提升当前线程权限，否则提升整个进程的权限
					 * \param PreviousValue 输出原来相应权限的状态（打开 | 关闭）
					 * \return 可忽略
					 */
					static UINT RtlAdjustPrivilege(ULONG Privilege, BOOL bEnablePrivilege, BOOL IsThreadPrivilege, PINT PreviousValue)
					{
						UINT(CALLBACK * f_RtlAdjustPrivilege)(ULONG, BOOL, BOOL, PINT) = nullptr;
						if (HRESULT hr = loadFunFromLib(NTDLL, "RtlAdjustPrivilege", f_RtlAdjustPrivilege); SUCCEEDED(hr)) {
							return f_RtlAdjustPrivilege(Privilege, bEnablePrivilege, IsThreadPrivilege, PreviousValue);
						}
						else {
							return -1;
						}
					}
				}
			}
		}
		/* cloudgameZero提供的简易工具集合 */
		namespace Tool
		{
			/* 提供了简易的函数工具 */
			inline namespace function
			{
				/**
				 * 此函数运行用户获取Windows环境变量的值.
				 *
				 * \param PATH 环境变量值，一个字符串类型，如APPDATA
				 * \param len 长度（可选）
				 * \return 如果一切正常，函数将返回一个std::string类型的容器，里面存储的是环境变量对应的值
				 */
				static std::string GetEnvironmentVariableA(const std::string PATH, DWORD len = MAX_PATH)
				{
					char* buf = {};
					len = ::GetEnvironmentVariableA(PATH.c_str(), buf, 0);
					char* buffer = new char[len];
					*buffer = { '\0' };
					::GetEnvironmentVariableA(PATH.c_str(), buffer, len);
					std::string ret = buffer;
					*buffer = NULL;
					delete[] buffer;
					return ret;
				}

				/**
				 * 此函数将从注册表中获取关于处理器的字符串.
				 *
				 * \return 如果一切正常，将返回一个CHAR*字符串
				 */
				static CHAR* GetProcesserFromRegistryA()
				{
					HKEY HANDLES;
					RegOpenKeyExA(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", NULL, KEY_ALL_ACCESS, &HANDLES);
					char* lpbuffer = new char[50];
					DWORD dwSize = 50;
					RegGetValueA(HANDLES, NULL, "ProcessorNameString", RRF_RT_ANY, NULL, lpbuffer, &dwSize);
					RegCloseKey(HANDLES);
					return lpbuffer;
				}

				/**
				 * 此函数将从注册表中获取关于处理器的宽字符串.
				 *
				 * \return 如果一切正常，将返回一个WCHAR*字符串
				 */
				static WCHAR* GetProcesserFromRegistryW()
				{
					HKEY HANDLES;
					RegOpenKeyExA(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", NULL, KEY_ALL_ACCESS, &HANDLES);
					WCHAR* lpbuffer = new WCHAR[50];
					DWORD dwSize = 50;
					RegGetValueW(HANDLES, NULL, L"ProcessorNameString", RRF_RT_ANY, NULL, lpbuffer, &dwSize);
					RegCloseKey(HANDLES);
					return lpbuffer;
				}

				/**
				 * 此函数将从系统中获取当前登录的用户名.
				 *
				 * \return 如果一切正常将返回LPCSTR类型的指针，指针存储的是用户名
				 */
				static LPCSTR GetUserA()
				{
					static char username[1024];
					DWORD usernameLength = sizeof(username);
					GetUserNameA(username, &usernameLength);
					return username;
				}

				/**
				 * 此函数将从系统中获取当前登录的用户名.
				 *
				 * \return 如果一切正常将返回LPCWSTR类型的指针，指针存储的是用户名
				 */
				static LPCWSTR GetUserW()
				{
					static wchar_t username[1024];
					DWORD usernameLength = 1024;
					GetUserNameW(username, &usernameLength);
					return username;
				}

				/**
				 * 此函数的行为类似于pause指令.
				 *
				 * \param message 提示信息，如果提示信息为NULL，则什么都不打印
				 * \param wrap 决定是否换行，默认为true，如果为false将不打印换行符
				 * \param 注：如果message为NULL，则wrap即使为true或者false，都不会换行
				 *
				 */
				static void PRESSANYBOTTON(const char* message = "请按任意键继续...", bool wrap = true)
				{
					if (message == NULL)
					{
						std::cout << "";
						int tmp = _getch();
						return;
					}
					else
					{
						std::cout << message;
					}
					int tmp = _getch();
					if (wrap)
					{
						std::cout.put('\n');
					}
					return;
				}

				/**
				 * 通过进程名获取到进程的进程ID.
				 *
				 * \param processName 宽字符串，用于获取
				 * \return 返回对应进程的进程id
				 */
				static DWORD GetProcessIdByName(LPCWSTR processName)
				{
					HANDLE hProcessSnapShot = NULL;
					PROCESSENTRY32 pe32 = { 0 };

					hProcessSnapShot = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

					if (hProcessSnapShot == (HANDLE)-1) {
						return NULL;
					}
					pe32.dwSize = sizeof(PROCESSENTRY32);

					if (Process32First(hProcessSnapShot, &pe32))
					{
						do {
							if (!wcscmp(processName, pe32.szExeFile)) return pe32.th32ProcessID;
						} while (Process32Next(hProcessSnapShot, &pe32));
					}
					else
					{
						::CloseHandle(hProcessSnapShot);
					}
					return NULL;
				}

				/**
				 * 通过进程id获取窗口句柄.
				 *
				 * \param id 进程id
				 * \return 如果一切正常，它将返回这个进程的窗口句柄
				 */
				static HWND GetHwndById(DWORD id)
				{
					HWND handle = GetTopWindow(0);
					HWND ret = NULL;
					while (handle)
					{
						DWORD pid = 0;
						DWORD dwTheardId = GetWindowThreadProcessId(handle, &pid);
						if (dwTheardId != 0)
						{
							if (pid == id && GetParent(handle) == NULL && ::IsWindowVisible(handle))
							{
								ret = handle;    //会有多个相等值
							}
						}
						handle = GetNextWindow(handle, GW_HWNDNEXT);
					}
					return ret;
				}

				/**
				 * \brief 通过进程名间接获取进程id随后获取窗口句柄.
				 * \brief
				 * \param processName 进程名
				 * \return 如果一切正常，它将返回这个进程的句柄，否则返回一个空指针
				 */
				static HWND GetHwndByName(LPCWSTR processName)
				{
					DWORD Id = GetProcessIdByName(processName);
					if (Id) {
						return GetHwndById(Id);
					}
					else {
						return nullptr;
					}
				}

				/**
				 * \brief 终止某个进程.
				 *
				 * \param processName 进程名
				 * \return 返回SHORT类型数据，返回3个数据其中之一
				 * \return 如果返回1则表示已终止
				 * \return 如果返回0则表示无法获取到实例
				 * \return 如果返回-1则代表函数在尝试获取句柄时出现失败，且提权无法解决问题
				 */
				static SHORT Terminate(LPCWSTR processName)
				{
					DWORD pid = GetProcessIdByName(processName);
					if (pid == NULL)
					{
						return 0;
					}
					HANDLE Handle = OpenProcess(PROCESS_TERMINATE, FALSE, pid);
					if (!Handle)
					{
						using namespace Foundation::dynamincLibrayFunc::function::unstable;
						RtlAdjustPrivilege(SeDebugPrivilege, TRUE, FALSE, [] { static INT value = 0; return &value; }());
						Handle = OpenProcess(PROCESS_TERMINATE, FALSE, pid);
						if (!Handle)
						{
							return -1;
						}
					}
					TerminateProcess(Handle, 0);
					::CloseHandle(Handle);
					return 1;
				}

				/**
				 * \brief 通过chrono时间库生成一个时间字符串.
				 *
				 * \param format 格式化字符串，取自https://www.apiref.com/cpp-zh/cpp/io/manip/put_time.html
				 * \return 返回格式化后的字符串
				 */
				static inline std::string makeTimeStr(std::string format) noexcept
				{
					std::time_t tt = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
					std::tm tms;
					gmtime_s(&tms, &tt);
					localtime_s(&tms, &tt);
					std::stringstream stream;
					stream << std::put_time(&tms, format.c_str());
					std::string time = stream.str();
					return time;
				}

				static std::string utf8ToGbk(std::string& convert) noexcept
				{
					int len = MultiByteToWideChar(CP_UTF8, 0, convert.c_str(), -1, NULL, 0);
					WCHAR* wszGBK = new WCHAR[len + 1];
					memset(wszGBK, 0, static_cast<size_t>(len) * 2 + 2);
					MultiByteToWideChar(CP_UTF8, 0, convert.c_str(), -1, wszGBK, len);
					len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
					CHAR* szGBK = new CHAR[len + 1];
					memset(szGBK, 0, static_cast<size_t>(len) + 1);
					WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, szGBK, len, NULL, NULL);
					std::string strTemp(szGBK);
					delete[] wszGBK, szGBK;
					return strTemp;
				}

				static std::string gbkToUtf8(std::string& convert) noexcept
				{
					int len = MultiByteToWideChar(CP_ACP, 0, convert.c_str(), -1, NULL, 0);
					WCHAR* wstr = new WCHAR[len + 1];
					memset(wstr, 0, static_cast<size_t>(len) + 1);
					MultiByteToWideChar(CP_ACP, 0, convert.c_str(), -1, wstr, len);
					len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
					CHAR* str = new CHAR[len + 1];
					memset(str, 0, static_cast<size_t>(len) + 1);
					WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
					std::string strTemp = str;
					delete[] wstr, str;
					return strTemp;
				}

				/* 实验用函数 */
				namespace Experiment
				{
					/* 由于转换字符串会导致出现C4267，因此此处临时禁用 */
#pragma warning(push)
#pragma warning(disable : 4267)


/**
* \brief 此部分写于2023/8/1
* \brief 将std::string转换为std::wstring.
* \brief 批注
* \brief 此函数转换的结果可能会导致ostream损坏，仅用于特殊用途
*
* \param convert 要转换的字符串
* \return 返回转换结果
*/
					static _NODISCARD std::wstring MutiToWide(std::string convert)
					{
						size_t size = strlen(convert.c_str());
						int len = ::MultiByteToWideChar(CP_ACP, NULL, convert.c_str(), size, NULL, 0);
						WCHAR* widechar = new WCHAR[static_cast<int>(len + 1)];
						::MultiByteToWideChar(CP_ACP, NULL, convert.c_str(), size, widechar, len);
						widechar[len] = L'\0';
						std::wstring ret = widechar;
						delete[] widechar;
						return ret;
					}

					/**
					 * \brief 此部分写于2023/8/1
					 * \brief 将std::wstring转换为std::string.
					 * \brief 批注
					 * \brief 此函数转换的结果可能会导致ostream损坏，仅用于特殊用途
					 *
					 * \param convert 要转换的字符串
					 * \return 返回转换结果
					 */
					static _NODISCARD std::string WideToMuti(std::wstring convert)
					{
						int len = WideCharToMultiByte(CP_ACP, NULL, convert.c_str(), lstrlenW(convert.c_str()), NULL, 0, NULL, NULL);
						CHAR* mutiByte = new CHAR[static_cast<int>(len + 1)];
						WideCharToMultiByte(CP_ACP, NULL, convert.c_str(), lstrlenW(convert.c_str()), mutiByte, len, NULL, NULL);
						mutiByte[len] = '\0';
						std::string ret = mutiByte;
						delete[] mutiByte;
						return ret;
					}

					/**
					 * \brief 此部分写于2023/8/2.
					 * \brief 基于WideToMuti设计的安全版本函数
					 *
					 * \param str 被引用的std::wstring字符串
					 * \param buffer 接收转换结果的缓冲区
					 * \param size 被引用字符串的长度
					 * \return 如果引用字符串为空，返回NULL，如果size为NULL，将会返回需要的长度，如果成功返回写入的字符数
					 */
					static size_t WideToMuti_S(const std::wstring& str, std::string& buffer, size_t size)
					{
						if (str.empty())
						{
							return NULL;
						}
						size_t len = static_cast<size_t>(lstrlenW(str.c_str()));
						if (size == NULL)
						{
							return len;
						}
						CHAR* mutiByte = new CHAR[static_cast<int>(len + 1)];
						int tmp = std::stoi(std::to_string(len));
						size_t write = WideCharToMultiByte(CP_ACP, NULL, str.c_str(), tmp, mutiByte, static_cast<int>(len), NULL, NULL);
						buffer = mutiByte;
						delete[] mutiByte;
						return write;
					}

					/**
					 * \brief 此部分写于2023/8/2.
					 * \brief 基于WideToMuti
					 *
					 * \param str 被引用的std::wstring字符串
					 * \param buffer 接收转换结果的缓冲区
					 * \param size 被引用字符串的长度
					 * \return 如果引用字符串为空，返回NULL，如果size为NULL，将会返回需要的长度，如果成功返回写入的字符数
					 */
					static size_t MutiToWide_S(const std::wstring& str, std::string& buffer, size_t size)
					{
						if (str.empty())
						{
							return NULL;
						}
						size_t len = static_cast<size_t>(lstrlenW(str.c_str()));
						if (size == NULL)
						{
							return len;
						}
						CHAR* mutiByte = new CHAR[static_cast<int>(len + 1)];
						int tmp = std::stoi(std::to_string(len));
						size_t write = WideCharToMultiByte(CP_ACP, NULL, str.c_str(), tmp, mutiByte, static_cast<int>(len), NULL, NULL);
						buffer = mutiByte;
						delete[] mutiByte;
						return write;
					}
				}

				typedef size_t(CALLBACK* curlCallBack)(char* ptr, size_t size, size_t nmemb, void* stream);

				/**
				 * \brief 此部分写于2023/8/18.
				 * \brief 从url中获取数据，以GET请求方式
				 * \brief 批注
				 * \brief 使用时可能会引发curl内部异常
				 *
				 * \param url
				 * \return 如果能获取到数据，则代表已完成GET请求，否则返回值为空的std::string
				 */
				static std::string getDataFromUrl(std::string url)
				{
					CURL* curl = curl_easy_init();
					std::string response;
					CURLcode res{};
					if (!curl)
					{
						std::cerr << "Can't Create Instance For Curl\n";
						return response;
					}
					url = gbkToUtf8(url);
					curlCallBack callback = Infomation::curlResponseCallBack;
					curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
					curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, true);
					curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);
					curl_easy_setopt(curl, CURLOPT_REFERER, "http://www.baidu.com");
					curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
					curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&response);
					curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 30);
					curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30);
					res = curl_easy_perform(curl);
					curl_easy_cleanup(curl);
					response = cloudgameZero::Foundation::Tool::function::utf8ToGbk(response);
					return response;
				}

				static std::string postDataRequest(std::string url, std::string param)
				{
					CURL* curl = curl_easy_init();
					CURLcode code;
					std::string response;
					url = gbkToUtf8(url);
					param = gbkToUtf8(param);
					curlCallBack callback = Infomation::curlResponseCallBack;
					curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, true);
					curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);
					curl_easy_setopt(curl, CURLOPT_REFERER, "http://www.baidu.com");
					curl_easy_setopt(curl, CURLOPT_POST, 1);
					curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
					curl_easy_setopt(curl, CURLOPT_POSTFIELDS, param.c_str());
					curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
					curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&response);
					curl_easy_setopt(curl, CURLOPT_POST, 1);
					curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
					curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 30);
					curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30);
					code = curl_easy_perform(curl);
					if (code != CURLE_OK)
					{
						return std::string();
					}
					response = cloudgameZero::Foundation::Tool::function::utf8ToGbk(response);
					return response;
				}

				static CURLcode getDownload(std::string filename, std::string url)
				{
					std::fstream file;
					url = gbkToUtf8(url);
					file.open(filename, std::ios::binary | std::ios::out);
					CURL* curl = curl_easy_init();
					CURLcode code;
					curlCallBack callback = Infomation::curlFileCallback;
					curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
					curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
					curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
					curl_easy_setopt(curl, CURLOPT_REFERER, "http://www.baidu.com");
					curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&file);
					curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 30);
					curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30);
					code = curl_easy_perform(curl);
					return code;
				}

				static CURLcode postDownload(std::string filename, std::string url, std::string param)
				{
					std::FILE* file;
					url = gbkToUtf8(url);
					param = gbkToUtf8(param);
					fopen_s(&file, filename.c_str(), "wb");
					CURL* curl = curl_easy_init();
					CURLcode code;
					curlCallBack callback = Infomation::curlFileCallback;
					curl_easy_setopt(curl, CURLOPT_POST, 1);
					curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
					curl_easy_setopt(curl, CURLOPT_POSTFIELDS, param.c_str());
					curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
					curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
					curl_easy_setopt(curl, CURLOPT_REFERER, "http://www.baidu.com");
					curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
					curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 30);
					curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30);
					code = curl_easy_perform(curl);
					return code;
				}
			}

			namespace CONSOLE
			{
				enum : WORD {
					CONSOLE_COLOR_BLACK = 0x0000,
					CONSOLE_COLOR_BLUE = 0x0001,
					CONSOLE_COLOR_GREEN = 0x0002,
					CONSOLE_COLOR_AQUA = 0x0003,
					CONSOLE_COLOR_RED = 0x0004,
					CONSOLE_COLOR_PURPLE = 0x0005,
					CONSOLE_COLOR_YELLOW = 0x0006,
					CONSOLE_COLOR_WHITE = 0x0007,
					CONSOLE_COLOR_GRAY = 0x0008,
					CONSOLE_COLOR_LIGHTBULE = 0x0009,
					CONSOLE_COLOR_LIGHTGREEN = 0xA,
					CONSOLE_COLOR_LIGHTAQUA = 0xB,
					CONSOLE_COLOR_LIGHTRED = 0xC,
					CONSOLE_COLOR_LIGHTPURPLE = 0xD,
					CONSOLE_COLOR_LIGHTYELLOW = 0xE,
					CONSOLE_COLOR_BRIGHTWHITE = 0xF
				};
			}

			/*
			提供用于部分操作的用户自定义字面量命名空间
			默认内联到Tool命名空间中
			若调用此命名空间提供的字面量
			请使用：
			using namespace cloudgameZero::Foundation::Tool;
			*/
			inline namespace Libteral
			{
				/**
				* \brief 此部分写于2023/8/5
				 *\brief 将多字节转换为宽字节.
				 *
				 * \param str 待转换的字符串
				 * \param size 不需要的参数，默认为str的长度
				 * \return 返回std::wstring，内容为str
				 */
				inline static _NODISCARD std::wstring operator"" _zw(const char* str, size_t size)
				{
					std::wstring ret = function::Experiment::MutiToWide(str);
					return ret;
				}

				/**
				 * \brief 此部分写于2023/8/5.
				 * \brief 将宽字节转换为多字节
				 * \param str 待转换的字符串
				 * \param size 不需要的参数，默认为str的长度
				 * \return 返回std::string，内容为str
				 */
				inline static _NODISCARD std::string operator"" _zs(const wchar_t* str, size_t size)
				{
					std::string ret = function::Experiment::WideToMuti(str);
					return ret;
				}

				/**
				 * \brief 此部分写于2023/8/5.
				 * \brief 返回多字节字符串的长度，相当于strlen
				 * \str 字符串
				 * \return 返回字符串的长度
				 */
				static _NODISCARD inline constexpr size_t operator"" _zsl(const char* str, size_t size)
				{
					return size;
				}

				/**
				 * \brief 此部分写于2023/8/5.
				 * \brief 返回宽字节字符串的长度，相当于strlen
				 * \str 字符串
				 * \return 返回字符串的长度
				 */
				static _NODISCARD inline constexpr size_t operator"" _zwl(const wchar_t* str, size_t size)
				{
					return size;
				}

				/**
				 * \brief 此部分写于2023/8/5.
				 * \brief 将size_t转换为std::string
				 * \param num 待转换的数据
				 * \return 返回std::string
				 */
				static _NODISCARD inline std::string operator"" _zIS(size_t num)
				{
					return std::to_string(num);
				}

				/**
				 * \brief 此部分写于2023/8/5.
				 * \brief 将字符串的数字转换为int.
				 *
				 * \return 如果出现异常，它将返回NULL，如果正常，它将返回解析得到的数字
				 */
				static _NODISCARD inline int operator""_zSI(const char* num, size_t size)
				{
					try {
						int number = std::stoi(num);
						return number;
					}
					catch (...)
					{
						return NULL;
					}
				}

				namespace structs
				{
					/* 仅用于提供给operator"" _zF()和operator"" _zWF的函数模板*/
					struct argsM
					{
						constexpr argsM(const char* s) : str(s) {}
						const char* str;
					};

					struct argsW
					{
						constexpr argsW(const wchar_t* s) : str(s) {}
						const wchar_t* str;
					};

					struct regexStruct
					{
						constexpr regexStruct(const char* str) : str(str) {};
						const char* str;
					};
				}

				/**
				 * \brief 此部分写于2023/8/5.
				 * \brief 格式化一个字符串，用法类似std::format.
				 *
				 * \return 返回lambda表达式并调用(参数为将要格式化的参数)
				 */
				template<structs::argsM a>
				static inline constexpr auto operator"" _zF() {
					return[=]<class ...T>(T... _args) { return std::format(a.str, _args...); };
				}

				/**
				 * \brief 此部分写于2023/8/5.
				 * \brief 格式化一个字符串，用法类似std::format.
				 *
				 * \return 返回lambda表达式并调用(参数为将要格式化的参数)
				 */
				template<structs::argsW a>
				static inline constexpr auto operator"" _zWF() {
					return[=]<class ...T>(T... _args) { return std::format(a.str, _args...); };
				}


				/**
				* \brief 此部分写于2023/8/20.
				 *\brief 用于检查正则表达式是否与字符串匹配.
				 */
				template<structs::regexStruct rege>
				static inline constexpr auto operator"" _matches()
				{
					return [=](const char* regex) -> bool { return std::regex_match(rege.str, std::regex(regex)); };
				}

				/**
				 * \brief 此部分写于2023/8/20.
				 * \brief 用于检查正则表达式是否在字符串中存在匹配的子串.
				 */
				template<structs::regexStruct rege>
				static inline constexpr auto operator"" _rsearch()
				{
					return [=](const char* regex) -> bool {return std::regex_search(rege.str, std::regex(regex)); };
				}
			}

			/* 此命名空间存储了被标记启用的C语言运行时函数 */
			/* 所有函数均从C语言运行时库中导出
			 * 请注意：
			 * 并不是所有函数均为安全的，如果启用安全检查，请尽可能使用安全版本的函数
			 */
			namespace NOCRT_SAFEFUNC
			{
				static __inline char* __CRTDECL ctime(_In_ time_t const* const _Time)
				{
					HINSTANCE Handle = LoadLibraryA("C:\\Windows\\SYSTEM32\\msvcrt.dll");
					if (!Handle)
					{
						return NULL;
					}
					char* (__CRTDECL * func)(_In_ time_t const* const _Time);
					HRESULT hr = cloudgameZero::Foundation::dynamincLibrayFunc::loadFunFromLib(Handle, "ctime", func);
					if (SUCCEEDED(hr))
					{
						return func(_Time);
					}
					return NULL;
				}

				static __inline int __CRTDECL sprintf(char* const _Buffer, char const* const _Format, ...)
				{
					HINSTANCE Handle = LoadLibraryA("C:\\Windows\\SYSTEM32\\msvcrt.dll");
					if (!Handle)
					{
						return NULL;
					}
					int(__CRTDECL * func)(char* const _Buffer, char const* const _Format, _locale_t   const _Locale, va_list _ArgList);
					int _Result;
					va_list _ArgList;
					__crt_va_start(_ArgList, _Format);
					HRESULT hr = cloudgameZero::Foundation::dynamincLibrayFunc::loadFunFromLib(Handle, "_vsprintf_l", func);
					if (SUCCEEDED(hr))
					{
						_Result = func(_Buffer, _Format, NULL, _ArgList);
						__crt_va_end(_ArgList);
						return _Result;
					}
					return NULL;
				}

				static FILE* __CRTDECL fopen(_In_z_ char const* _FileName, _In_z_ char const* _Mode)
				{
					HINSTANCE Handle = LoadLibraryA("C:\\Windows\\SYSTEM32\\msvcrt.dll");
					if (!Handle)
					{
						return nullptr;
					}
					FILE* (__CRTDECL * func)(char const* _FileName, char const* _Mode);
					HRESULT hr = cloudgameZero::Foundation::dynamincLibrayFunc::loadFunFromLib(Handle, "fopen", func);
					if (SUCCEEDED(hr)) {
						return func(_FileName, _Mode);
					}
					return nullptr;
				}
			}
		}
		namespace Warpper
		{
			/**
			 * 用于将PCWSTR转换为Hstring的包装类.
			 */
			class HstringWrapper
			{
			public:
				HstringWrapper(_In_reads_(length) PCWSTR stringRef, _In_ UINT32 length) noexcept
				{
					HRESULT hr = dynamincLibrayFunc::function::WindowsCreateStringReference(stringRef, length, &this->header, &this->hstring);
					if (!SUCCEEDED(hr)) {
						RaiseException(static_cast<DWORD>(STATUS_INVALID_PARAMETER), EXCEPTION_NONCONTINUABLE, 0, nullptr);
					}
				}
				HstringWrapper(_In_ std::wstring const& stringRef) noexcept
				{
					HRESULT hr = dynamincLibrayFunc::function::WindowsCreateStringReference(stringRef.c_str(), static_cast<UINT32>(stringRef.length()), &this->header, &this->hstring);
					if (FAILED(hr)) {
						RaiseException(static_cast<DWORD>(STATUS_INVALID_PARAMETER), EXCEPTION_NONCONTINUABLE, 0, nullptr);
					}
				}
				~HstringWrapper() noexcept { dynamincLibrayFunc::function::WindowsDeleteString(hstring); }
				inline HSTRING Get() const noexcept { return this->hstring; }
			private:
				HSTRING hstring;
				HSTRING_HEADER header;
			};

			/* 抽象基类*/
			interface InternalDateTime : ABI::Windows::Foundation::IReference<ABI::Windows::Foundation::DateTime>
			{
				static INT64 Now() {
					FILETIME now;
					GetSystemTimeAsFileTime(&now);
					return ((((INT64)now.dwHighDateTime) << 32) | now.dwLowDateTime);
				}
				virtual operator INT64() = 0;
				virtual HRESULT STDMETHODCALLTYPE get_Value(ABI::Windows::Foundation::DateTime* dateTime) = 0;
				virtual HRESULT STDMETHODCALLTYPE QueryInterface(const IID& riid, void** ppvObject) = 0;
				virtual ULONG STDMETHODCALLTYPE Release() = 0;
				virtual ULONG STDMETHODCALLTYPE AddRef() = 0;
				virtual HRESULT STDMETHODCALLTYPE GetIids(ULONG*, IID**) = 0;
				virtual HRESULT STDMETHODCALLTYPE GetRuntimeClassName(HSTRING*) = 0;
				virtual inline HRESULT STDMETHODCALLTYPE GetTrustLevel(TrustLevel*) = 0;
			};
		}
	}

	/* 所有来自cloudgamefixZero库定义的接口均来自此命名空间 .*/

	class logConfig
	{
	public:
		enum class _ostream {
			reserved,
			cerr,
			cout,
			clog
		};
		enum class _wostream {
			reserved,
			wcerr,
			wcout,
			wclog
		};

		~logConfig() = default;

		void InitConfig(std::string filename)
		{
			try {
				parseHelper(filename);
			}
			catch (...)
			{
				genDefaultSettings(filename);
				parseHelper(filename);
			}
			try {
				this->files = filename;
				this->Render = this->_root["outToTerminal"]["render"].GetBool();
				std::string tmpfile = this->_root["logToFile"]["File"]["filename"].GetString();
				std::string format = this->_root["logToFile"]["File"]["TimeFormat"].GetString();
				bool needFormatFile = this->_root["logToFile"]["File"]["format"].GetBool();
				if (std::regex_search(tmpfile, std::regex(R"(\$\{format\})")) && needFormatFile)
				{
					std::time_t tt = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
					std::tm tms;
					gmtime_s(&tms, &tt);
					localtime_s(&tms, &tt);
					std::stringstream stream;
					stream << "\\" << std::put_time(&tms, format.c_str());
					std::string time = stream.str();

					this->filename = std::regex_replace(tmpfile, std::regex(R"(\$\{format\})"), time);
				}
				this->_isInit = true;
			}
			catch (...)
			{
				genDefaultSettings(filename);
				InitConfig(filename);
			}
		}

		operator std::string()
		{
			rapidjson::StringBuffer buf;
			rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buf);
			this->_root.Accept(writer);
			return buf.GetString();
		}

		operator const char* ()
		{
			rapidjson::StringBuffer buf;
			rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buf);
			this->_root.Accept(writer);
			return buf.GetString();
		}

		inline bool IsInit()
		{
			return this->_isInit;
		}

		void getLogDictionary(std::string& str)
		{
			try {
				if (!this->IsInit())
				{
					PrintError("需要初始化配置");
					return;
				}
				std::regex pattern(R"(\$\{(\w+){1,20}\})");
				std::regex regex(R"(\$\{(\w+){1}\})");
				std::string tmp = this->_root["logToFile"]["Dictionary"].GetString();
				std::string varible{};
				std::smatch fmt{};
				if (std::regex_search(tmp, fmt, pattern)) {
					std::string format = fmt.str();
					if (format == "${APPDATA}" || format == "${appdata}") {
						varible = cloudgameZero::Foundation::Tool::function::GetEnvironmentVariableA("APPDATA");
					}
					else if (format == "${userprofile}" || format == "${USERPROFILE}") {
						varible = cloudgameZero::Foundation::Tool::function::GetEnvironmentVariableA("userprofile");
					}
					else if (format == "${LOCAL}" || format == "${local}") {
						varible = cloudgameZero::Foundation::Tool::function::GetEnvironmentVariableA("userprofile");
						varible += "\\APPDATA\\Local";
					}
					else if (format == "${TEMP}" || format == "${TMP}") {
						varible = cloudgameZero::Foundation::Tool::function::GetEnvironmentVariableA("temp");
					}
					else if (format == "${format}" || format == "${}") {
						varible = cloudgameZero::Foundation::Tool::function::GetEnvironmentVariableA("APPDATA");
					}
					else {
						throw std::exception("无法找到环境变量，请问您设置的字符串格式化是否正确?");
					}
					if (std::string _str = std::regex_replace(tmp, regex, varible); !_str.empty()) {
						str = _str;
						return;
					}
					else {
						throw std::runtime_error("无法替换正则");
					}
				}
				str = tmp;
			}
			catch (...)
			{
				genDefaultSettings(this->files);
				getLogDictionary(str);
			}
		}

		std::string parseFileName()
		{
			try {
				if (!this->IsInit())
				{
					PrintError("需要初始化配置");
					return std::string();
				}
				std::string format = this->_root["logToFile"]["File"]["TimeFormat"].GetString();
				std::string file = this->_root["logToFile"]["File"]["filename"].GetString();
				if (this->_root["logToFile"]["File"]["format"].GetBool())
				{
					std::time_t tt = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
					std::tm tms;
					gmtime_s(&tms, &tt);
					localtime_s(&tms, &tt);
					std::stringstream stream;
					stream << "\\" << std::put_time(&tms, format.c_str());
					std::string time = stream.str();
					this->filename = std::regex_replace(file, std::regex(R"(\$\{format\})"), time);
				}
				return this->filename;
			}
			catch (...)
			{
				genDefaultSettings(this->files);
				return parseFileName();
			}
		}

		int getMin()
		{
			try {
				std::string find = this->_root["outToTerminal"]["rootLogger"]["level"].GetString();
				static const std::map<std::string, int> levels = {
					{"Trace",1},
					{"Debug",2},
					{"Info", 3},
					{"Warn", 4},
					{"Error",5},
					{"Fatal",6}
				};
				auto itr = levels.find(find);
				return itr->second;
			}
			catch (...)
			{
				genDefaultSettings(this->files);
				return getMin();
			}
		}

		_ostream getLogObjectType()
		{
			if (!this->IsInit())
			{
				PrintError("无法解析终端设置");
				return _ostream::reserved;
			}
			static const std::map<std::string, logConfig::_ostream> ostreamobject = {
			   {"std::cout",logConfig::_ostream::cout},
			   {"std::cerr",logConfig::_ostream::cerr},
			   {"std::clog",logConfig::_ostream::clog},
			   {"stdcout",logConfig::_ostream::cout},
			   {"stdcerr",logConfig::_ostream::cerr},
			   {"stdclog",logConfig::_ostream::clog},
			   {"cout",logConfig::_ostream::cout},
			   {"cerr",logConfig::_ostream::cerr},
			   {"clog",logConfig::_ostream::clog},
			   {"null",logConfig::_ostream::reserved}
			};
			try {
				if (!this->_root.HasMember("outToTerminal") && !this->_root["outToTerminal"].IsObject())
				{
					PrintError("无法解析终端设置");
					return _ostream::reserved;
				}
				if (!this->_root["outToTerminal"].HasMember("rootLogger") && !this->_root["outToTerminal"]["rootLogger"].IsObject())
				{
					PrintError("无法解析rootLogger对象");
					return _ostream::reserved;
				}
				if (!this->_root["outToTerminal"]["rootLogger"].HasMember("ostream") && !this->_root["outToTerminal"]["rootLogger"]["wostream"].IsObject())
				{
					PrintError("无法解析ostream对象");
					return _ostream::reserved;
				}
				std::string os = this->_root["outToTerminal"]["rootLogger"]["ostream"].GetString();
				auto itr = ostreamobject.find(os);
				assert(itr != ostreamobject.end());
				return itr->second;
			}
			catch (...)
			{
				genDefaultSettings(this->files);
				return getLogObjectType();
			}
		}

		_wostream getWideOstreamType()
		{
			if (!this->IsInit())
			{
				PrintError("无法解析终端设置");
				return _wostream::reserved;
			}
			static const std::map<std::string, logConfig::_wostream> wostreamobject = {
			   {"std::wcout",logConfig::_wostream::wcout},
			   {"std::wcerr",logConfig::_wostream::wcerr},
			   {"std::wclog",logConfig::_wostream::wclog},
			   {"stdwcout",logConfig::_wostream::wcout},
			   {"stdwcerr",logConfig::_wostream::wcerr},
			   {"stdwclog",logConfig::_wostream::wclog},
			   {"wcout",logConfig::_wostream::wcout},
			   {"wcerr",logConfig::_wostream::wcerr},
			   {"wclog",logConfig::_wostream::wclog},
			   {"null",logConfig::_wostream::reserved}
			};
			try {
				if (!this->_root.HasMember("outToTerminal") && !this->_root["outToTerminal"].IsObject())
				{
					PrintError("无法解析终端设置");
					return _wostream::reserved;
				}
				if (!this->_root["outToTerminal"].HasMember("rootLogger") && !this->_root["outToTerminal"]["rootLogger"].IsObject())
				{
					PrintError("无法解析rootLogger对象");
					return _wostream::reserved;
				}
				if (!this->_root["outToTerminal"]["rootLogger"].HasMember("ostream") && !this->_root["outToTerminal"]["rootLogger"]["ostream"].IsObject())
				{
					PrintError("无法解析ostream对象");
					return _wostream::reserved;
				}
				std::string os = this->_root["outToTerminal"]["rootLogger"]["wostream"].GetString();
				auto itr = wostreamobject.find(os);
				assert(itr != wostreamobject.end());
				return itr->second;
			}
			catch (...)
			{
				genDefaultSettings(filename);
				return getWideOstreamType();
			}
		}

		inline _NODISCARD bool needRender() noexcept
		{
			return this->Render;
		}

		inline _NODISCARD rapidjson::Document& getDocment() noexcept
		{
			return this->_root;
		}

		inline _NODISCARD std::string getFileName() noexcept
		{
			return this->filename;
		}

		static void genDefaultSettings(std::string filename)
		{
			if (filename.empty()) {
#if EnableZeroLibrayExceptions
				throw std::invalid_argument("文件名不能为空");
#else
				PrintError("文件名不能为空");
#endif
			}
			/* 开始构建Document */
			rapidjson::Document Dom;
			rapidjson::Document::AllocatorType& Allocator = Dom.GetAllocator();
			genFrameworkHelper(Dom); //Dom作为引用传入genFrameworkHelper函数以生成基本框架
			genDefaultSettingsHelper(Dom);
			rapidjson::StringBuffer buf;
			rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buf);
			Dom.Accept(writer);
			std::fstream f;
			if (std::filesystem::exists(filename))
			{
				f.open(filename, std::ios::in);
				f.peek();
				if (f.eof())
				{
					f.close();
					std::cout << "检测到空文件\n";
					f.open(filename, std::ios::app);
				}
				else {
					f.close();
					f.open(filename, std::ios::out | std::ios::trunc);
				}
			}
			else {
				f.open(filename, std::ios::out | std::ios::trunc);
			}
			if (!f.is_open())
			{
#if EnableZeroLibrayExceptions
				throw std::runtime_error("无法打开文件");
#else
				PrintError("无法打开文件");
#endif
			}
			f << buf.GetString();
			f.close();
		}

	private:
		bool parseHelper(std::string filename)
		{
			if (filename.empty())
			{
#if EnableZeroLibrayExceptions
				throw std::invalid_argument("字符串不能为空");
#else
				PrintError("字符串不能为空");
#endif
			}
			std::ifstream reader(filename);
			if (!reader.is_open()) {
#if EnableZeroLibrayExceptions
				throw std::invalid_argument("无法打开文件");
#else
				PrintError("无法打开文件");
#endif
			}
			reader >> std::noskipws;
			std::string json_content((std::istream_iterator<char>(reader)), std::istream_iterator<char>());
			reader.close();
			if (!this->_root.Parse(json_content.c_str()).HasParseError())
			{
				return true;
			}
			else {
#if EnableZeroLibrayExceptions
				throw std::exception("无法解析json");
#else
				PrintError("无法解析json");
#endif
				return false;
			}
		}

		static void genFrameworkHelper(rapidjson::Document& Dom) noexcept
		{
			Dom.SetObject();
			rapidjson::Document::AllocatorType& Allocator = Dom.GetAllocator();
			Dom.AddMember("logFormatTime", rapidjson::kStringType, Allocator);
			Dom["logFormatTime"].SetString("[%Ec %A]");
			Dom.AddMember("outToTerminal", rapidjson::kObjectType, Allocator);
			Dom.AddMember("logToFile", rapidjson::kObjectType, Allocator);
			Dom.AddMember("EnableThreadSecurity", rapidjson::kTrueType, Allocator);
			/* 声明句柄 */
			auto& outToTerminal = Dom["outToTerminal"];
			auto& logToFile = Dom["logToFile"];
			/* 设置outToTerminal句柄 */
			outToTerminal.AddMember("Enable", rapidjson::kTrueType, Allocator);
			outToTerminal.AddMember("render", rapidjson::kTrueType, Allocator);
			outToTerminal.AddMember("showUser", rapidjson::kTrueType, Allocator);
			outToTerminal.AddMember("rootLogger", rapidjson::kObjectType, Allocator);
			outToTerminal["rootLogger"].AddMember("level", rapidjson::kStringType, Allocator);
			outToTerminal["rootLogger"].AddMember("ostream", rapidjson::kStringType, Allocator);
			outToTerminal["rootLogger"].AddMember("wostream", rapidjson::kStringType, Allocator);
			outToTerminal["rootLogger"].AddMember("cleanBuffer", rapidjson::kObjectType, Allocator);
			outToTerminal["rootLogger"]["cleanBuffer"].AddMember("clean", rapidjson::kTrueType, Allocator);
			outToTerminal["rootLogger"]["cleanBuffer"].AddMember("times", rapidjson::kNumberType, Allocator);
			/* 设置logToFile句柄 */
			logToFile.AddMember("Enable", rapidjson::kTrueType, Allocator);
			logToFile.AddMember("Dictionary", rapidjson::kStringType, Allocator);
			logToFile.AddMember("File", rapidjson::kObjectType, Allocator);
			logToFile.AddMember("append", rapidjson::kFalseType, Allocator);
			logToFile["File"].AddMember("format", rapidjson::kTrueType, Allocator);
			logToFile["File"].AddMember("TimeFormat", rapidjson::kStringType, Allocator);
			logToFile["File"].AddMember("filename", rapidjson::kStringType, Allocator);
		}

		static void genDefaultSettingsHelper(rapidjson::Document& Dom) noexcept
		{
			/* outToTerminal */
			auto& outToTerminal = Dom["outToTerminal"];
			auto& rootLogger = outToTerminal["rootLogger"];
			auto& cleanBuffer = rootLogger["cleanBuffer"];
			/* 设置outToTerminal */
#ifndef NDEBUG
			rootLogger["level"].SetString("Trace");
#else
			rootLogger["level"].SetString("Info");
#endif
			rootLogger["ostream"].SetString("std::clog");
			rootLogger["wostream"].SetString("std::wclog");
			cleanBuffer["times"].SetInt(10);
			/* logToFile */
			auto& logToFile = Dom["logToFile"];
			auto& File = logToFile["File"];
			/* 设置logToFile */
			logToFile["Enable"].SetBool(true);
			logToFile["Dictionary"].SetString("${APPDATA}\\cloudgamefixZero\\logs");
			File["TimeFormat"].SetString("[%Y %m %d]");
			File["filename"].SetString("${format}CloudGameFixZero.log");
		}

		rapidjson::Document _root;
		std::string filename;
		std::string files;
		bool _isInit = false;
		bool Enable = true;
		bool OutPut = true;
		bool Save = true;
		bool NoPreOutPut = false;
		bool showDetail = true;
		bool ShowTime = true;
		bool ShowUser = true;
		bool Render = true;
	};

	typedef std::list<std::string> logList;
	typedef void(CALLBACK* logConfCallBackFunc)(rapidjson::Document& Dom);

#pragma region zeroLog
	class log
	{
	public:
		/**
		*  \brief 此部分写于2023/8/12
		 * \brief 日志类构造函数.
		 *
		 * \param init 决定是否在构造期间初始化
		 * \param file 决定日志使用的配置文件名
		 * \param CallBack 可选，如果希望在运行阶段修改配置，此处应提供一个函数用于回调，它将以引用方式进行传递，如果不希望使用请指定其为nullptr
		 * \param 	函数指针原型： typedef void(__stdcall* logConfCallBackFunc)(rapidjson::Document& Dom);
		 * \param mark 用于标记日志来源（可选，表示输出的来源）
		 * \param server 用于标记模块（可选，表示模块名）
		 */
		explicit log(bool init, std::string file = "logConfig.json", logConfCallBackFunc CallBack = nullptr, std::string mark = "main", std::string server = "ZERO") : times(NULL), mark(mark), server(server)
		{
			if (!std::filesystem::exists(file))
			{
				DEBUG_MESSAGE("未找到配置文件\n准备生成一个默认配置");
				logConfig::genDefaultSettings("logConfig.json");
			}
			conf = std::make_unique<logConfig>();
			conf->InitConfig("logConfig.json");
			this->minLevel = conf->getMin();
			if (CallBack)
			{
				CallBack(conf->getDocment());
			}
			if (init)
			{
				this->Init();
			}
		}

		/**
		 * 每一个日志类对象是独一无二的实例，因此空参构造和拷贝构造以及赋值运算符将不会提供给用户.
		 */
		log() = delete;
		log& operator=(log& other) = delete;
		log(log& other) = delete;

		~log()
		{
			this->close();
		}

		inline void editServerName(std::string server)
		{
			if (server.empty())
			{
				return;
			}
			this->server = server;
		}

		inline void editMark(std::string mark)
		{
			if (mark.empty())
			{
				return;
			}
			this->server = mark;
		}

		inline void setPath(std::string path)
		{
			if (path.empty())
			{
				return;
			}
			this->file = path;
		}

		void Init()
		{
			using namespace Foundation::Tool;
			rapidjson::Document& Dom = conf->getDocment();
			if (this->HasInit())
			{
				DEBUG_MESSAGE("这个实例已经被初始化过了");
				return;
			}
			this->levels = {
				{Trace,		"TRACE"},
				{Debug,		"DEBUG"},
				{Info,		"INFO"},
				{Warn,		"WARN"},
				{Error,		"ERROR"},
				{Fatal,		"FATAL"},
			};
			if (!Dom["logToFile"]["Enable"].GetBool() && !Dom["logToFile"]["Enable"].GetBool())
			{
				DEBUG_MESSAGE("为什么你要在两者都不启用的情况下进行初始化，请问这是否是有意而为之?");
				return;
			}
			if (Dom["logToFile"]["Enable"].GetBool())
			{
				std::string dict;
				if (this->file.empty())
				{
					conf->getLogDictionary(dict);
					if (!std::filesystem::exists(dict)) {
						std::filesystem::create_directories(dict);
					}
					std::string filename = conf->parseFileName();
					dict += filename;
				}
				else {
					dict = this->file;
				}
				if (Dom["logToFile"]["append"].GetBool())
				{
					this->fs.open(dict, std::ios::app);
				}
				else {
					this->fs.open(dict, std::ios::out);
				}
				if (!fs.is_open())
				{
					throw std::runtime_error("无法打开文件，出现了异常");
				}
				this->file = dict;
				this->EnableFileOut.store(true);
			}
			if (Dom["outToTerminal"]["Enable"].GetBool())
			{
				if (logConfig::_ostream ostream = conf->getLogObjectType(); ostream != logConfig::_ostream::reserved)
				{
					switch (ostream)
					{
					case logConfig::_ostream::clog: {
						this->object = &std::clog;
						break;
					}
					case logConfig::_ostream::cout: {
						this->object = &std::cout;
						break;
					}
					case logConfig::_ostream::cerr: {
						this->object = &std::cerr;
						break;
					}
					}
				}
				else {
					throw std::runtime_error("无法获取ostream对象");
				}
				if (logConfig::_wostream ostream = conf->getWideOstreamType(); ostream != logConfig::_wostream::reserved)
				{
					switch (ostream)
					{
					case logConfig::_wostream::wclog: {
						this->wobject = &std::wclog;
						break;
					}
					case logConfig::_wostream::wcout: {
						this->wobject = &std::wcout;
						break;
					}
					case logConfig::_wostream::wcerr: {
						this->wobject = &std::wcerr;
						break;
					}
					}
				}
				else {
					throw std::runtime_error("无法获取ostream对象");
				}
				this->EnableTerminalOut = true;
			}
			this->logTimeFormat = Dom["logFormatTime"].GetString();
			this->render = Dom["outToTerminal"]["render"].GetBool();
			this->cleanBuffer = Dom["outToTerminal"]["rootLogger"]["cleanBuffer"]["clean"].GetBool();
			this->times = Dom["outToTerminal"]["rootLogger"]["cleanBuffer"]["times"].GetUint();
			this->showUser = Dom["outToTerminal"]["showUser"].GetBool();
			this->has_init.store(true);
		}

		inline bool HasInit()
		{
			return this->has_init;
		}

		/*================================================================
		日志库提供的运算符重载
		左移运算符<<用于运行时更换ostream对象，支持shared_ptr和unique_ptr友元重载

		================================================================*/

		inline void operator<<(std::ostream& object)
		{
			this->object = &object;
		}

		inline friend void operator<<(std::unique_ptr<log>& ptr, std::ostream& ostream)
		{
			ptr->object = &ostream;
		}

		inline friend void operator<<(std::shared_ptr<log>& ptr, std::ostream& ostream)
		{
			ptr->object = &ostream;
		}

		inline void operator>>(std::string_view filename)
		{
			this->close();
			this->getFilePath() = filename;
			this->Init();
		}

		inline friend void operator>>(std::unique_ptr<log>& ptr, std::string_view filename)
		{
			ptr->close();
			ptr->getFilePath() = filename;
			ptr->Init();
		}

		inline friend void operator>>(std::shared_ptr<log>& ptr, std::string_view filename)
		{
			ptr->close();
			ptr->file = filename;
			ptr->Init();
		}

		/*=================================================================
		日志类提供了6个等级的成员函数用于记录日志
		每个等级拥有2个可变参数模板和2个普通成员函数
		用于处理std::string和std::wstring数据类型
		模板函数用于通过std::format处理格式化字符串
		注：
		logConfig的等级代表最小记录等级，例如等级如果为Trace，则所有等级日志都可见
		但如果等级为Info，则Trace和Debug将不会被记录，而只是被临时存储到list容器
		如果编译为Debug模式，库将会生成一个最低记录等级为Trace的配置文件，反之为Info
		==================================================================*/

		/*================================================================
		| 当调试时需要追踪调试时，使用此成员函数打印日志
		| 当logConfig等级为Trace时，此成员函数打印的日志将被记录到文件并打印到终端
		| 如果等级大于Trace，则此日志仅临时存储在list容器中
		================================================================*/

		/**
		 * \brief 此内容写于2023/8/13.
		 * \brief 打印等级为Trace的日志
		 *
		 * \param message 消息内容
		 */
		void trace(const std::string message)
		{
			if (!this->HasInit())
			{
				this->Init();
			}
			std::unique_lock<std::mutex> lock(this->mutex);
			std::string logs = this->makeLogs(Trace, message);
			this->write(Trace, logs);
			this->pushList(logs);
		}

		/**
		 * \brief 此内容写于2023/8/13.
		 * \brief 打印等级为Trace的日志
		 *
		 * \param message 消息内容
		 */
		void trace(const std::wstring message)
		{
			if (!this->HasInit())
			{
				this->Init();
			}
			std::unique_lock<std::mutex> lock(this->mutex);
			std::wstring logs = this->makeLogs(Trace, message);
			this->write(Trace, logs);
			this->pushList(logs);
		}

		/**
		 * \brief 此内容写于2023/8/13.
		 * \brief 处理格式化字符串并打印等级为Trace的日志
		 *
		 * \param fmt 待格式化字符串
		 * \param args 格式化参数
		*/
		template<typename... Types>
		void trace(const std::string_view fmt, Types&&... args)
		{
			using namespace Foundation::Tool;
			if (!this->HasInit())
			{
				this->Init();
			}
			std::unique_lock<std::mutex> lock(this->mutex);
			std::string already = this->makeFormat(fmt, args...);
			std::string logs = this->makeLogs(Trace, already);
			this->write(Trace, logs);
			this->pushList(logs);
		}

		/**
		 * \brief 此内容写于2023/8/13.
		 * \brief 处理格式化字符串并打印等级为Trace的日志
		 *
		 * \param fmt 待格式化字符串
		 * \param args 格式化参数
		*/
		template<typename... Types>
		void trace(const std::wstring_view fmt, Types&&... args)
		{
			using namespace Foundation::Tool;
			if (!this->HasInit())
			{
				this->Init();
			}
			std::unique_lock<std::mutex> lock(this->mutex);
			std::wstring already = this->makeFormat(fmt, args...);
			std::wstring logs = this->makeLogs(Trace, already);
			this->write(Trace, logs);
			this->pushList(logs);
		}

		/*==================================================================
		| 当调试时运行在调试时，使用此成员函数打印日志
		| 当logConfig等级为debug时，此成员函数打印的日志将被记录到文件并打印到终端
		| 如果等级大于debug，则此日志仅临时存储在list容器中
		==================================================================*/

		/**
		 * \brief 此内容写于2023/8/13.
		 * \brief 打印等级为Debug的日志
		 *
		 * \param message 消息内容
		 */
		void debug(const std::string message)
		{
			if (!this->HasInit())
			{
				this->Init();
			}
			std::unique_lock<std::mutex> lock(this->mutex);
			std::string logs = this->makeLogs(Debug, message);
			this->write(Debug, logs);
			this->pushList(logs);
		}

		/**
		 * \brief 此内容写于2023/8/13.
		 * \brief 打印等级为Debug的日志
		 *
		 * \param message 消息内容
		 */
		void debug(const std::wstring message)
		{
			if (!this->HasInit())
			{
				this->Init();
			}
			std::unique_lock<std::mutex> lock(this->mutex);
			std::wstring logs = this->makeLogs(Debug, message);
			this->write(Debug, logs);
			this->pushList(logs);
		}

		/**
		 * \brief 此内容写于2023/8/13.
		 * \brief 处理格式化字符串并打印等级为Debug的日志
		 *
		 * \param fmt 待格式化字符串
		 * \param args 格式化参数
		*/
		template<typename... Types>
		void debug(const std::string_view fmt, Types&&... args)
		{
			using namespace Foundation::Tool;
			if (!this->HasInit())
			{
				this->Init();
			}
			std::unique_lock<std::mutex> lock(this->mutex);
			std::string already = this->makeFormat(fmt, args...);
			std::string logs = this->makeLogs(Debug, already);
			this->write(Debug, logs);
			this->pushList(logs);
		}

		/**
		 * \brief 此内容写于2023/8/13.
		 * \brief 处理格式化字符串并打印等级为Debug的日志
		 *
		 * \param fmt 待格式化字符串
		 * \param args 格式化参数
		*/
		template<typename... Types>
		void debug(const std::wstring_view fmt, Types&&... args)
		{
			using namespace Foundation::Tool;
			if (!this->HasInit())
			{
				this->Init();
			}
			std::unique_lock<std::mutex> lock(this->mutex);
			std::wstring already = this->makeFormat(fmt, args...);
			std::wstring logs = this->makeLogs(Debug, already);
			this->write(Debug, logs);
			this->pushList(logs);
		}

		/*==============================================================
		| 当程序用于记录正常运行时，使用此成员函数打印日志
		| 当logConfig等级为Info时，此成员函数打印的日志将被记录到文件并打印到终端
		| 如果等级不为Info，则此日志仅临时存储在list容器中
		==============================================================*/

		/**
		 * \brief 此内容写于2023/8/13.
		 * \brief 打印等级为Info的日志
		 *
		 * \param message 消息内容
		 */
		void info(const std::string message)
		{
			if (!this->HasInit())
			{
				this->Init();
			}
			std::unique_lock<std::mutex> lock(this->mutex);
			std::string logs = this->makeLogs(Info, message);
			this->write(Info, logs);
			this->pushList(logs);
		}

		/**
		 * \brief 此内容写于2023/8/13.
		 * \brief 打印等级为Info的日志
		 *
		 * \param message 消息内容
		 */
		void info(const std::wstring message)
		{
			if (!this->HasInit())
			{
				this->Init();
			}
			std::unique_lock<std::mutex> lock(this->mutex);
			std::wstring logs = this->makeLogs(Info, message);
			this->write(Info, logs);
			this->pushList(logs);
		}

		/**
		 * \brief 此内容写于2023/8/13.
		 * \brief 处理格式化字符串并打印等级为Info的日志
		 *
		 * \param fmt 待格式化字符串
		 * \param args 格式化参数
		*/
		template<typename... Types>
		void info(const std::string_view fmt, Types&&... args)
		{
			using namespace Foundation::Tool;
			if (!this->HasInit())
			{
				this->Init();
			}
			std::unique_lock<std::mutex> lock(this->mutex);
			std::string already = this->makeFormat(fmt, args...);
			std::string logs = this->makeLogs(Info, already);
			this->write(Info, logs);
			this->pushList(logs);
		}

		/**
		 * \brief 此内容写于2023/8/13.
		 * \brief 处理格式化字符串并打印等级为Info的日志
		 *
		 * \param fmt 待格式化字符串
		 * \param args 格式化参数
		*/
		template<typename... Types>
		void info(const std::wstring_view fmt, Types&&... args)
		{
			using namespace Foundation::Tool;
			if (!this->HasInit())
			{
				this->Init();
			}
			std::unique_lock<std::mutex> lock(this->mutex);
			std::wstring already = this->makeFormat(fmt, args...);
			std::wstring logs = this->makeLogs(Info, already);
			this->write(Info, logs);
			this->pushList(logs);
		}

		/*===============================================================================
		| 当程序用于记录发生的小错误时，使用此成员函数打印日志，如有需要可配合stacktrace函数打印调用堆栈
		| 不建议修改等级到warn或更高
		| 因为筛选过多的日志可能会导致可维护性降低
		===============================================================================*/

		/**
		 * \brief 此内容写于2023/8/13.
		 * \brief 打印等级为Warn的日志
		 *
		 * \param message 消息内容
		 */
		void warn(const std::string message)
		{
			if (!this->HasInit())
			{
				this->Init();
			}
			std::unique_lock<std::mutex> lock(this->mutex);
			std::string logs = this->makeLogs(Warn, message);
			this->write(Warn, logs);
			this->pushList(logs);
		}

		/**
		 * \brief 此内容写于2023/8/13.
		 * \brief 打印等级为Warn的日志
		 *
		 * \param message 消息内容
		 */
		void warn(const std::wstring message)
		{
			if (!this->HasInit())
			{
				this->Init();
			}
			std::unique_lock<std::mutex> lock(this->mutex);
			std::wstring logs = this->makeLogs(Warn, message);
			this->write(Warn, logs);
			this->pushList(logs);
		}

		/**
		 * \brief 此内容写于2023/8/13.
		 * \brief 处理格式化字符串并打印等级为Warn的日志
		 *
		 * \param fmt 待格式化字符串
		 * \param args 格式化参数
		*/
		template<typename... Types>
		void warn(const std::string_view fmt, Types&&... args)
		{
			using namespace Foundation::Tool;
			if (!this->HasInit())
			{
				this->Init();
			}
			std::unique_lock<std::mutex> lock(this->mutex);
			std::string already = this->makeFormat(fmt, args...);
			std::string logs = this->makeLogs(Warn, already);
			this->write(Warn, logs);
			this->pushList(logs);
		}

		/**
		 * \brief 此内容写于2023/8/13.
		 * \brief 处理格式化字符串并打印等级为Warn的日志
		 *
		 * \param fmt 待格式化字符串
		 * \param args 格式化参数
		*/
		template<typename... Types>
		void warn(const std::wstring_view fmt, Types&&... args)
		{
			using namespace Foundation::Tool;
			if (!this->HasInit())
			{
				this->Init();
			}
			std::unique_lock<std::mutex> lock(this->mutex);
			std::wstring already = this->makeFormat(fmt, args...);
			std::wstring logs = this->makeLogs(Warn, already);
			this->write(Warn, logs);
			this->pushList(logs);
		}

		/*==============================================================================
		| 当程序用于记录发生的错误时，使用此成员函数打印日志，如有需要可配合stacktrace函数打印调用堆栈
		| 不建议修改等级到warn或更高
		| 因为筛选过多的日志可能会导致可维护性降低
		===============================================================================*/

		/**
		 * \brief 此内容写于2023/8/13.
		 * \brief 打印等级为Error的日志
		 *
		 * \param message 消息内容
		 */
		void error(const std::string message)
		{
			if (!this->HasInit())
			{
				this->Init();
			}
			std::unique_lock<std::mutex> lock(this->mutex);
			std::string logs = this->makeLogs(Error, message);
			this->write(Error, logs);
			this->pushList(logs);
		}

		/**
		 * \brief 此内容写于2023/8/13.
		 * \brief 打印等级为Error的日志
		 *
		 * \param message 消息内容
		 */
		void error(const std::wstring message)
		{
			if (!this->HasInit())
			{
				this->Init();
			}
			std::unique_lock<std::mutex> lock(this->mutex);
			std::wstring logs = this->makeLogs(Error, message);
			this->write(Error, logs);
			this->pushList(logs);
		}

		/**
		 * \brief 此内容写于2023/8/13.
		 * \brief 处理格式化字符串并打印等级为Error的日志
		 *
		 * \param fmt 待格式化字符串
		 * \param args 格式化参数
		*/
		template<typename... Types>
		void error(const std::string_view fmt, Types&&... args)
		{
			using namespace Foundation::Tool;
			if (!this->HasInit())
			{
				this->Init();
			}
			std::unique_lock<std::mutex> lock(this->mutex);
			std::string already = this->makeFormat(fmt, args...);
			std::string logs = this->makeLogs(Error, already);
			this->write(Error, logs);
			this->pushList(logs);
		}

		/**
		 * \brief 此内容写于2023/8/13.
		 * \brief 处理格式化字符串并打印等级为Error的日志
		 *
		 * \param fmt 待格式化字符串
		 * \param args 格式化参数
		*/
		template<typename... Types>
		void error(const std::wstring_view fmt, Types&&... args)
		{
			using namespace Foundation::Tool;
			if (!this->HasInit())
			{
				this->Init();
			}
			std::unique_lock<std::mutex> lock(this->mutex);
			std::wstring already = this->makeFormat(fmt, args...);
			std::wstring logs = this->makeLogs(Error, already);
			this->write(Error, logs);
			this->pushList(logs);
		}

		/*=============================================================================================
		| 当程序用于记录发生的随时有可能会崩溃的错误时，使用此成员函数打印日志，如有需要可配合stacktrace函数打印调用堆栈
		| 强烈不建议修改等级到此等级
		| 因为筛选过多的日志可能会导致可维护性降低，且可能会有大量的信息疏漏
		==============================================================================================*/

		/**
		 * \brief 此内容写于2023/8/13.
		 * \brief 打印等级为Fatal的日志
		 *
		 * \param message 消息内容
		 */
		void fatal(const std::string message)
		{
			if (!this->HasInit())
			{
				this->Init();
			}
			std::unique_lock<std::mutex> lock(this->mutex);
			std::string logs = this->makeLogs(Fatal, message);
			this->write(Fatal, logs);
			this->pushList(logs);
		}

		/**
		 * \brief 此内容写于2023/8/13.
		 * \brief 打印等级为Fatal的日志
		 *
		 * \param message 消息内容
		 */
		void fatal(const std::wstring message)
		{
			if (!this->HasInit())
			{
				this->Init();
			}
			std::unique_lock<std::mutex> lock(this->mutex);
			std::wstring logs = this->makeLogs(Fatal, message);
			this->write(Fatal, logs);
			this->pushList(logs);
		}


		/**
		 * \brief 此内容写于2023/8/13.
		 * \brief 处理格式化字符串并打印等级为Fatal的日志
		 *
		 * \param fmt 待格式化字符串
		 * \param args 格式化参数
		*/
		template<typename... Types>
		void fatal(const std::string_view fmt, Types&&... args)
		{
			using namespace Foundation::Tool;
			if (!this->HasInit())
			{
				this->Init();
			}
			std::unique_lock<std::mutex> lock(this->mutex);
			std::wstring already = this->makeFormat(fmt, args...);
			std::wstring logs = this->makeLogs(Fatal, already);
			this->write(Fatal, logs);
			this->pushList(logs);
		}

		/**
		 * \brief 此内容写于2023/8/13.
		 * \brief 处理格式化字符串并打印等级为Fatal的日志
		 *
		 * \param fmt 待格式化字符串
		 * \param args 格式化参数
		*/
		template<typename... Types>
		void fatal(const std::wstring_view fmt, Types&&... args)
		{
			using namespace Foundation::Tool;
			if (!this->HasInit())
			{
				this->Init();
			}
			std::unique_lock<std::mutex> lock(this->mutex);
			std::wstring already = this->makeFormat(fmt, args...);
			std::wstring logs = this->makeLogs(Fatal, already);
			this->write(Fatal, logs);
			this->pushList(logs);
		}

		void stackTrace()
		{
			using namespace Foundation::Tool;
			if (!this->HasInit())
			{
				this->Init();
			}
			std::unique_lock<std::mutex> lock(this->mutex);
			std::string logs = this->makeLogs(Warn, std::format("\n Here Is The StackTrace's Content: \n{}", boost::stacktrace::to_string(boost::stacktrace::stacktrace())));
			this->write(Warn, logs);
			this->pushList(logs);
		}

		inline void close()
		{
			if (!this->HasInit())
			{
				return;
			}
			this->fs.close();
			this->object = nullptr;
			this->levels.clear();
			this->logList.clear();
			this->has_init = false;
		}

		inline std::string getLastLog()
		{
			return this->buffer;
		}

		inline void operator=(std::string server)
		{
			this->server = server;
		}

		int selectLog(int level, bool show = true)
		{
			if (level < Trace || level > Fatal)
			{
				throw std::invalid_argument("错误的参数");
			}
			using std::regex;
			using std::regex_search;
			static std::vector<regex> re = {
				{regex("TRACE")},
				{regex("DEBUG")},
				{regex("INFO")},
				{regex("WARN")},
				{regex("ERROR")},
				{regex("FATAL")},
			};
			int find = 0;
			for (auto& iterator : this->logList)
			{
				if (regex_search(iterator, re[level]))
				{
					if (show)
					{
						*this->object << iterator << "\n";
					}
					find++;
				}
			}
			return find;
		}

		inline size_t size()
		{
			return this->logList.size();
		}

		inline std::string& getFilePath()
		{
			return this->file;
		}

	private:
		enum level {
			Reserved,
			Trace,
			Debug,
			Info,
			Warn,
			Error,
			Fatal
		};
		inline static void renderTerminal(level levels)
		{
			using namespace Foundation::Tool::CONSOLE;
			switch (levels)
			{
			case level::Trace:
				SetConsoleTextAttribute(CONSOLE_OUTPUT_HANDLE, CONSOLE_COLOR_BLUE | CONSOLE_COLOR_GREEN);
				break;
			case level::Info:
				break;
			case level::Debug:
				SetConsoleTextAttribute(CONSOLE_OUTPUT_HANDLE, CONSOLE_COLOR_GREEN);
				break;
			case level::Warn:
				SetConsoleTextAttribute(CONSOLE_OUTPUT_HANDLE, CONSOLE_COLOR_YELLOW);
				break;
			case level::Error:
				SetConsoleTextAttribute(CONSOLE_OUTPUT_HANDLE, CONSOLE_COLOR_LIGHTRED);
				break;
			case level::Fatal:
				SetConsoleTextAttribute(CONSOLE_OUTPUT_HANDLE, CONSOLE_COLOR_RED);
				break;
			}
		}
		inline std::string makeLogs(level report, std::string already)
		{
			using namespace Foundation::Tool;
			using namespace Foundation::Tool::function;
			using namespace Foundation::Tool::function::Experiment;
			auto it = this->levels.find(report);
			assert(it != this->levels.end());
			std::string logs = "{} [{}/{}]: {} {} {}"_zF(
				makeTimeStr(this->logTimeFormat),
				this->mark,
				it->second,
				this->mark != "main" ? std::format("[{}]", this->server) : "",
				this->showUser ? Foundation::Tool::function::GetUserA() : "",
				already
			);
			return logs;
		}
		inline std::wstring makeLogs(level report, std::wstring already)
		{
			using namespace Foundation::Tool;
			using namespace Foundation::Tool::function;
			using namespace Foundation::Tool::function::Experiment;
			auto it = this->levels.find(report);
			assert(it != this->levels.end());
			std::wstring logs = L"{} [{}/{}]: {} {} {}"_zWF(
				MutiToWide(makeTimeStr(this->logTimeFormat)),
				MutiToWide(this->mark),
				MutiToWide(it->second),
				MutiToWide(this->mark != "main" ? std::format("[{}]", this->server) : ""),
				this->showUser ? Foundation::Tool::function::GetUserW() : L"",
				already
			);
			return logs;
		}
		template<typename... Args>
		inline std::string makeFormat(std::string_view fmt, Args&&... args)
		{
			auto fmtArgs = std::make_format_args(args...);
			std::string fmts = std::vformat(fmt, fmtArgs);
			return fmts;
		}
		template<typename... Args>
		inline std::wstring makeFormat(std::wstring_view fmt, Args&&... args)
		{
			auto fmtArgs = std::make_wformat_args(args...);
			std::wstring fmts = std::vformat(fmt, fmtArgs);
			return fmts;
		}
		void write(level report, std::string logs)
		{
			if (this->minLevel > report)
			{
				return;
			}
			if (this->EnableTerminalOut)
			{
				if (this->render)
				{
					renderTerminal(report);
				}
				if (cleanBuffer && times <= 10) {
					*this->object << logs << "\n";
					this->times++;
				}
				else {
					*this->object << logs << std::endl;
					this->times = 0;
				}
				SetConsoleTextAttribute(CONSOLE_OUTPUT_HANDLE, Foundation::Tool::CONSOLE::CONSOLE_COLOR_WHITE);
			}
			if (this->EnableFileOut)
			{
				this->fs << logs << "\n";
			}
		}
		void write(level report, std::wstring logs)
		{
			if (this->minLevel > report)
			{
				return;
			}
			if (this->EnableTerminalOut)
			{
				if (this->render)
				{
					renderTerminal(report);
				}
				if (cleanBuffer && times <= 10) {
					(*this->wobject).imbue(std::locale("chs"));
					(*this->wobject) << logs;
					(*this->wobject).imbue(std::locale("C"));
					(*this->wobject).clear();
					(*this->wobject) << "\n";
					this->times++;
				}
				else {
					(*this->wobject).imbue(std::locale("chs"));
					(*this->wobject) << logs;
					(*this->wobject).imbue(std::locale("C"));
					(*this->wobject).clear();
					(*this->wobject) << std::endl;
					this->times = 0;
				}
				SetConsoleTextAttribute(CONSOLE_OUTPUT_HANDLE, Foundation::Tool::CONSOLE::CONSOLE_COLOR_WHITE);
			}
			if (this->EnableFileOut)
			{
				this->fs << Foundation::Tool::function::Experiment::WideToMuti(logs) << "\n";
			}
		}
		void pushList(std::string push) noexcept
		{
			if (this->logList.size() >= 750)
			{
				this->logList.clear();
			}
			this->logList.push_back(push);
		}
		void pushList(std::wstring push) noexcept
		{
			if (this->logList.size() >= 750)
			{
				this->logList.clear();
			}
			this->logList.push_back(Foundation::Tool::function::Experiment::WideToMuti(push));
		}
		int times;
		std::string logTimeFormat;
		std::unique_ptr<logConfig> conf;
		std::unordered_map<level, std::string> levels;
		std::ostream* object = nullptr;
		std::wostream* wobject = nullptr;
		std::ofstream fs;
		std::string file;
		std::string mark;
		std::string server;
		std::string MakeFormat;
		std::atomic_bool render;
		std::atomic_bool has_init;
		std::atomic_bool EnableFileOut;
		bool EnableTerminalOut;
		std::atomic_bool cleanBuffer;
		std::atomic_bool showUser;
		std::string buffer;
		std::mutex mutex;
		logList logList;
		int minLevel;
	};

	static log* CL()
	{
		static log INSTANCE(true);
		return &INSTANCE;
	}
#pragma endregion

	namespace Interface
	{
		interface Sha1 : public IUnknown
		{
			virtual void reset() = 0;
			virtual bool update(const unsigned char* input, unsigned long long size) = 0;
			virtual bool update(const char* input) = 0;
			virtual void getDigest(unsigned char* output) = 0;
			virtual void getDigestString(char* output, bool toUpperCase = false) = 0;
		};

		enum class InterfaceType
		{
			cgSystem,
			cgTool
		};

		/**
		* \brief 此部分写于2023/7/27
		* \brief 此函数用于获取cgSystem和cgFix的IUnknown接口
		* \brief 它将开辟堆区并初始化随后返回指向sigmaInterface封装的一个指针.
		* \brief 注意：
		* \brief 此函数的实现是在外部定义的，如果直接使用，将会发生LNK链接错误
		* \brief 备注，此函数返回IUnknown接口中，重写QueryInterface的方法是允许查询cgFix和cgSystem接口的GUID
		* \brief 因为cgSystem接口是cgFix的派生类，用于某些接口实现
		* \brief 如果用户查询使用了cgFix的GUID
		* \brief 则仅返回cgFix的GUID绑定的对象，而运行cgSystem的函数有可能是通往不明确行为和彻夜调试大会串的车票
		*
		* \return 正常情况下，函数将返回cgSystem子类对象的指针
		* \return 当使用完指针时请务必调用Realease函数归还资源
		*/
		static IUnknown* (CALLBACK* cgSystemCreateInstance)();

		/**
		* \brief 此部分写于2023/7/28
		* \brief 此函数用于获取cgTool的IUnknown接口
		* \brief 它将开辟堆区并初始化随后返回指向sigmaInterface封装的一个指针.
		* \brief 注意：
		* \brief 此函数的实现是在外部定义的，如果直接使用，将会发生LNK链接错误
		* \brief 批注
		* \brief 此函数实例提供的QueryInterface可查询cgTool和cgSoftware以及asciiStyle以及cgTool_s的接口，但同样
		* \brief 不同接口对接得到的对象如果运行不属于自己的方法，这仍然有可能是通往不明确行为和彻夜调试大会串的车票
		* \brief 此实例的QueryInterface将供cgTool_s,cgTool,cgSoftware,asciiStyle共享
		*
		* \return 正常情况下，函数将返回cgTool子类对象的指针
		* \return 当使用完指针时请务必调用Realease函数归还资源
		*/
		static IUnknown* (CALLBACK* cgToolCreateInstance)();

		MIDL_INTERFACE("fdf81ac2-b82f-4a86-b301-35bd3369a4bf")
			IcgFix : public IDispatch
		{
		public:
			virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE fixSystem(/* [in] */ int mode) = 0;

		};

		/**
		 * 用于修复网易云游戏系统的接口.
		 */
		interface cgFix : public IUnknown
		{
			enum class mode { reserved, cloudgame, cloudpc };
			virtual BOOL fixSystem(_In_ mode mode) = 0;
			virtual void fixFile(_In_ mode mode) = 0;
			virtual void resetGroupPolicy() = 0;
			virtual HRESULT repairGameFile() = 0;
		};

		/* 相比cgFix，cgSystem提供了更多功能，同时支持查询cgFix接口，可以看作是对cgFix的强化版 */
		interface cgSystem : public cgFix
		{
			enum class Theme { reserved, Default, white, windows, flower };
			enum class Resolution {
				reserved,
				_3480x2160,
				_2560x1440,
				_1920x1080,
				_1600x900,
				_1280x720
			};
			/**
			*  \brief 此部分写于2023/7/27
			 * \brief 此函数可以用于设置当前用户的壁纸.
			 *
			 * \param path 壁纸的路径
			 */
			virtual void setWallpaper(IN const std::string& path) = 0;

			/**
			 * 从URL中拉取一个壁纸随后并更换.
			 *
			 * \param url url的路径
			 * \param path 保存的路径
			 */
			virtual void downloadWallpaperAndSet(IN const std::string& url, IN const std::string path) = 0;

			/**
			 * 修改系统显示的分辨率.
			 * \brief ptr->changeRe(1980,1080);
			 *
			 * \param length 长度
			 * \param width 宽度
			 *
			 */
			virtual void changeResolution(IN short length, IN short width) = 0;

			/**
			 * 使用枚举量修改分辨率，相比changeRe会更加安全.
			 *
			 * \param resolution
			 */
			virtual void changeResolution_s(IN Resolution resolution) = 0;

			/**
			 * 从Windows主题中选择一个加载主题.
			 *
			 * \param theme 从Theme中的枚举量选择
			 */
			virtual void changeTheme(IN Theme theme) = 0;
		};


		/* 存储内部接口的声明 */
		namespace sigmaInterface
		{
			/* 存储子类重写的具体实现，所有cloudgameFixZero派生的cpp文件将在此命名空间声明自己的类 */
			namespace Implement
			{
				class __InternalDateTime : virtual public cloudgameZero::Foundation::Warpper::InternalDateTime
				{
				public:
					__InternalDateTime(ABI::Windows::Foundation::DateTime dateTime) : _dateTime(dateTime)
					{
						this->AddRef();
					}
					__InternalDateTime(INT64 millisecondsFromNow)
					{
						this->_dateTime.UniversalTime = Now() + millisecondsFromNow * 10000;
					}
					virtual ~__InternalDateTime() = default;
					virtual operator INT64() override { return _dateTime.UniversalTime; }
					virtual HRESULT STDMETHODCALLTYPE get_Value(ABI::Windows::Foundation::DateTime* dateTime) override {
						*dateTime = _dateTime;
						return S_OK;
					}
					virtual HRESULT STDMETHODCALLTYPE QueryInterface(const IID& riid, void** ppvObject) override {
						if (!ppvObject)
						{
							return E_POINTER;
						}
						if (riid == __uuidof(IReference<ABI::Windows::Foundation::DateTime>))
						{
							*ppvObject = dynamic_cast<IUnknown*>(dynamic_cast<IReference<ABI::Windows::Foundation::DateTime>*>(this));
							return S_OK;
						}
						return E_NOINTERFACE;
					}
					virtual ULONG STDMETHODCALLTYPE Release() override {
						if (this->ref--; this->ref == 0) {
							delete this;
						}
						else {
							return this->ref;
						}
						return NULL;
					}

					virtual ULONG STDMETHODCALLTYPE AddRef() override { this->ref++; return this->ref; }
					virtual HRESULT STDMETHODCALLTYPE GetIids(ULONG*, IID**) override { return E_NOTIMPL; }
					virtual HRESULT STDMETHODCALLTYPE GetRuntimeClassName(HSTRING*) override { return E_NOTIMPL; }
					virtual inline HRESULT STDMETHODCALLTYPE GetTrustLevel(TrustLevel*) override { return E_NOTIMPL; }
				protected:
					ABI::Windows::Foundation::DateTime _dateTime;
					ULONG ref = NULL;
				};

				namespace sha1
				{
					typedef unsigned char BYTE;
					typedef unsigned int WORD;
					typedef unsigned long long DWORD;

					static bool isBigEndian() {
						union {
							int a;
							char b;
						}num;
						num.a = 0x1234;
						if (num.b == 0x12) {
							return true;
						}
						return false;
					}

					static WORD bigMode(WORD value) {
						return (value & 0x000000FFU) << 24 | (value & 0x0000FF00U) << 8 | (value & 0x00FF0000U) >> 8 | (value & 0xFF000000U) >> 24;
					}

					static DWORD bigMode(DWORD value) {
						DWORD high_uint64 = (DWORD)bigMode((WORD)value);
						DWORD low_uint64 = (DWORD)bigMode((WORD)(value >> 32));
						return (high_uint64 << 32) + low_uint64;
					}

					class __Sha1 : public cloudgameZero::Interface::Sha1
					{
					public:
						__Sha1()
						{
							this->isBigEnd = isBigEndian();
							this->reset();
						}
						virtual HRESULT QueryInterface(const IID& riid, void** ppvObject)
						{
							if (!ppvObject)
							{
								return E_POINTER;
							}
							if (riid == __uuidof(IReference<ABI::Windows::Foundation::DateTime>))
							{
								*ppvObject = dynamic_cast<IUnknown*>(dynamic_cast<IReference<ABI::Windows::Foundation::DateTime>*>(this));
								return S_OK;
							}
							return E_NOINTERFACE;
						}
						virtual ULONG STDMETHODCALLTYPE Release() override {
							if (this->ref--; this->ref == 0) {
								delete this;
							}
							else {
								return this->ref;
							}
							return NULL;
						}
						virtual ULONG STDMETHODCALLTYPE AddRef() override
						{
							this->ref++;
							return this->ref;
						}
						void reset() override
						{
							this->A = isBigEnd ? 0x67452301 : bigMode((WORD)0x67452301);
							this->B = isBigEnd ? 0xEFCDAB89 : bigMode((WORD)0xEFCDAB89);
							this->C = isBigEnd ? 0x98BADCFE : bigMode((WORD)0x98BADCFE);
							this->D = isBigEnd ? 0x10325476 : bigMode((WORD)0x10325476);
							this->E = isBigEnd ? 0xC3D2E1F0 : bigMode((WORD)0xC3D2E1F0);

							this->isFinish = false;
							memset(data, 0, 64);
							data_size = 0;
							total_size = 0;
						}
						bool update(const BYTE* input, DWORD size) override
						{
							if (isFinish) return false;
							DWORD index = 0;
							while (data_size + size > 64) {
								memcpy(data + data_size, input + index, 64 - data_size);
								computerOneBlock();
								size -= 64 - data_size;
								index += 64 - data_size;
								total_size += 64 - data_size;
								data_size = 0;
							}
							memcpy(data + data_size, input + index, size);
							data_size += size;
							total_size += size;
							if (data_size == 64) {
								computerOneBlock();
								data_size = 0;
							}
							return true;
						}
						inline bool update(const char* input) override
						{
							return update((const BYTE*)input, strlen(input));
						}
						void getDigest(BYTE* output) override
						{
							if (!isFinish) {
								padingDataBlock();
								computerOneBlock();
							}

							*(WORD*)output = A;
							*(WORD*)(output + 4) = B;
							*(WORD*)(output + 8) = C;
							*(WORD*)(output + 12) = D;
							*(WORD*)(output + 16) = E;
						}
						void getDigestString(char* output, bool toUpperCase = false) override
						{
							BYTE origin_output[20];
							getDigest(origin_output);

							size_t index = 0;
							for (BYTE c : origin_output) {
								char high = c / 16, low = c % 16;
								output[index] = high < 10 ? '0' + high : (toUpperCase ? 'A' : 'a' + high - 10);
								output[index + 1] = low < 10 ? '0' + low : (toUpperCase ? 'A' : 'a' + low - 10);
								index += 2;
							}
						}
					private:
						ULONG ref;
						WORD A, B, C, D, E;
						bool isBigEnd;
						bool isFinish;
						BYTE data[64];
						DWORD data_size;
						DWORD total_size;
						bool computerOneBlock()
						{
							WORD k[4] = { 0x5A827999, 0x6ED9EBA1, 0x8F1BBCDC, 0xCA62C1D6 };
							if (!isBigEnd) {
								for (int i = 0; i < 4; i++) k[i] = bigMode(k[i]);
							}

							WORD sub_group[80] = { 0 };
							WORD* temp_sub_group = (WORD*)(data);
							for (int j = 0; j < 80; j++) {
								if (j < 16) sub_group[j] = temp_sub_group[j];
								else {
									WORD temp = sub_group[j - 3] ^ sub_group[j - 8] ^ sub_group[j - 14] ^ sub_group[j - 16];
									temp = isBigEnd ? temp : bigMode(temp);
									sub_group[j] = isBigEnd ? temp << 1 | temp >> 31 : bigMode(temp << 1 | temp >> 31);
								}
							}

							WORD a = A, b = B, c = C, d = D, e = E;

							for (int j = 0; j < 80; j++) {
								WORD temp, temp2 = isBigEnd ? a << 5 | a >> 27 : bigMode(bigMode(a) << 5 | bigMode(a) >> 27);
								switch (j / 20)
								{
								case 0:
									temp = (b & c) | ((~b) & d);
									temp = isBigEnd ? k[0] + temp : bigMode(bigMode(k[0]) + bigMode(temp));
									break;
								case 1:
									temp = (b ^ c ^ d);
									temp = isBigEnd ? k[1] + temp : bigMode(bigMode(k[1]) + bigMode(temp));
									break;
								case 2:
									temp = (b & c) | (b & d) | (c & d);
									temp = isBigEnd ? k[2] + temp : bigMode(bigMode(k[2]) + bigMode(temp));
									break;
								case 3:
									temp = (b ^ c ^ d);
									temp = isBigEnd ? k[3] + temp : bigMode(bigMode(k[3]) + bigMode(temp));
									break;
								}
								temp = isBigEnd ? temp + temp2 + e + sub_group[j] : bigMode(bigMode(temp) + bigMode(temp2) + bigMode(e) + bigMode(sub_group[j]));
								e = d;
								d = c;
								c = isBigEnd ? b << 30 | b >> 2 : bigMode(bigMode(b) << 30 | bigMode(b) >> 2);
								b = a;
								a = temp;
							}
							A = isBigEnd ? A + a : bigMode(bigMode(a) + bigMode(A));
							B = isBigEnd ? B + b : bigMode(bigMode(b) + bigMode(B));
							C = isBigEnd ? C + c : bigMode(bigMode(c) + bigMode(C));
							D = isBigEnd ? D + d : bigMode(bigMode(d) + bigMode(D));
							E = isBigEnd ? E + e : bigMode(bigMode(e) + bigMode(E));

							return true;
						}
						bool padingDataBlock()
						{
							if (isFinish) return false;
							if (data_size != 56) {
								DWORD pad_size = (64 + 56 - data_size) % 64;
								if (data_size + pad_size < 64) {
									data[data_size] = 0x80;
									memset(data + data_size + 1, 0x0, pad_size - 1);
								}
								else {
									data[data_size] = 0x80;
									memset(data + data_size + 1, 0x0, 64 - data_size - 1);
									computerOneBlock();
									memset(data, 0x0, 56);
								}
							}

							*(DWORD*)(data + 56) = isBigEnd ? total_size * 8 : bigMode(total_size * 8);
							isFinish = true;
							return true;
						}
					};
				}
			}
			namespace clsid
			{
				const CLSID CLOUDGAME_FIX_ZERO_CLSID_cgFix = { 0x9727503a, 0x899b, 0x452a, 0xb3, 0x2a, 0x65, 0x92, 0xa5, 0xea, 0xfb, 0x30 };
			}

			/* 接口id，若调用cloudgameFixZero接口，请使用此id */
			namespace guid
			{
				const IID IID_CLOUDGAME_FIX_ZERO_IID_IcgFix = { 0xfdf81ac2, 0xb82f, 0x4a86, 0xb3, 0x01, 0x35, 0xbd, 0x33, 0x69, 0xa4, 0xbf };
				//
				//extern "C++" const IID IID_CLOUDGAME_FIX_ZERO_CGFIX;	/* cgFix接口ID */
				//extern "C++" const IID IID_CLOUDGAME_FIX_ZERO_CGSYSTEM;	/* cgSystem接口ID */
				//extern "C++" const IID IID_CLOUDGAME_FIX_ZERO_CGTOOL;	/* cgTool接口ID */
				//extern "C++" const IID IID_CLOUDGAME_FIX_ZERO_CGTOOLS;	/* 设计用于安全功能的cgTool接口ID，与cgTool一起提供 */
				//extern "C++" const IID IID_CLOUDGAME_FIX_ZERO_CGSOFTWARE;	/* 设计基于cgTool安全功能的软件类接口 */
				//extern "C++" const IID IID_CLOUDGAME_FIX_ZERO_ASCIISTYLE;	/* ascii字符画预定义接口 */
			}
			const IID LIBID_cloudgamefixcomLib = { 0xc55af5fa, 0xa083, 0x4f62, 0xbc, 0x44, 0x07, 0x45, 0x85, 0xb0, 0x95, 0xef };
		}
	}
#pragma warning(push)
#pragma warning(disable : 4244)
#pragma warning(disable : 4018)
#pragma warning(disable : 4305)

	static bool checkFileSha1(std::string filename, std::string sha1)
	{
		std::ifstream fin;
		fin.open(filename, std::ios::binary | std::ios::ate);
		if (!fin.is_open())
		{
			return -1;
		}
		Interface::Sha1* s = new Interface::sigmaInterface::Implement::sha1::__Sha1;
		DWORD size = fin.tellg();
		fin.seekg(0, std::ios::beg);
		char buffer[512];
		for (int i = 0; i < size / 512; i++) {
			fin.read(buffer, 512);
			s->update((unsigned char*)buffer, 512);
		}
		fin.read(buffer, size % 512);
		fin.close();
		s->update((unsigned char*)buffer, size % 512);
		char* result = new char[40];
		s->getDigestString(result);
		std::string str(result);
		std::regex no("\\w+");
		std::regex_iterator itr(str.begin(), str.end(), no);
		std::string news = (*itr)[0].str();
		for (int i = 0; i < 40; i++)
		{
			news[i] = news[i];
		}
		return sha1 == news;
	}
#pragma warning(pop)

	/* WinToastLib */
	/*
	 * MIT License
	*
	 * Copyright (C) 2016-2023 WinToast v1.3.0 - Mohammed Boujemaoui <mohabouje@gmail.com>
	 *
	 * Permission is hereby granted, free of charge, to any person obtaining a copy of
	 * this software and associated documentation files (the "Software"), to deal in
	 * the Software without restriction, including without limitation the rights to
	 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
	 * the Software, and to permit persons to whom the Software is furnished to do so,
	 * subject to the following conditions:
	 *
	 * The above copyright notice and this permission notice shall be included in all
	 * copies or substantial portions of the Software.
	 *
	 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
	 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
	 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
	 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
	 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
	*/
	/* 此命名空间提供了用于调用Windows通知的函数和类，基于WinToast库修改 */
	namespace ToastPlatform
	{
		/* API命名空间通过此命名空间获取枚举常量 */
		namespace Enums
		{
			enum class ToastDismissalReason : INT
			{
				UserCanceled = ABI::Windows::UI::Notifications::ToastDismissalReason::ToastDismissalReason_UserCanceled,
				ApplicationHidden = ABI::Windows::UI::Notifications::ToastDismissalReason::ToastDismissalReason_ApplicationHidden,
				TimedOut = ABI::Windows::UI::Notifications::ToastDismissalReason::ToastDismissalReason_TimedOut
			};
			enum class Scenario { Default, Alarm, IncomingCall, Reminder };
			enum class Duration { System, Short, Long };
			enum class AudioOption { Default, Silent, Loop };
			enum class TextField { FirstLine, SecondLine, ThirdLine };
			enum class ToastTemplateType
			{
				ImageAndText01 = ABI::Windows::UI::Notifications::ToastTemplateType::ToastTemplateType_ToastImageAndText01,
				ImageAndText02 = ABI::Windows::UI::Notifications::ToastTemplateType::ToastTemplateType_ToastImageAndText02,
				ImageAndText03 = ABI::Windows::UI::Notifications::ToastTemplateType::ToastTemplateType_ToastImageAndText03,
				ImageAndText04 = ABI::Windows::UI::Notifications::ToastTemplateType::ToastTemplateType_ToastImageAndText04,
				Text01 = ABI::Windows::UI::Notifications::ToastTemplateType::ToastTemplateType_ToastText01,
				Text02 = ABI::Windows::UI::Notifications::ToastTemplateType::ToastTemplateType_ToastText02,
				Text03 = ABI::Windows::UI::Notifications::ToastTemplateType::ToastTemplateType_ToastText03,
				Text04 = ABI::Windows::UI::Notifications::ToastTemplateType::ToastTemplateType_ToastText04
			};

			enum class AudioSystemFile : INT
			{
				DefaultSound, IM,
				Mail, Reminder,
				SMS, Alarm,
				Alarm2, Alarm3,
				Alarm4, Alarm5,
				Alarm6, Alarm7,
				Alarm8, Alarm9,
				Alarm10, Call,
				Call1, Call2,
				Call3, Call4,
				Call5, Call6,
				Call7, Call8,
				Call9, Call10,
			};
			enum class CropHint { Square, Circle };

			enum class ToastError
			{
				NoError,
				NotInitialized,
				SystemNotSupported,
				ShellLinkNotCreated,
				InvalidAppUserModelID,
				InvalidParameters,
				InvalidHandler,
				NotDisplayed,
				UnknownError
			};

			enum ShortcutResult
			{
				SHORTCUT_UNCHANGED = 0,
				SHORTCUT_WAS_CHANGED = 1,
				SHORTCUT_WAS_CREATED = 2,
				SHORTCUT_MISSING_PARAMETERS = -1,
				SHORTCUT_INCOMPATIBLE_OS = -2,
				SHORTCUT_COM_INIT_FAILURE = -3,
				SHORTCUT_CREATE_FAILED = -4
			};

			enum class ShortcutPolicy
			{
				SHORTCUT_POLICY_IGNORE,
				SHORTCUT_POLICY_REQUIRE_NO_CREATE,
				SHORTCUT_POLICY_REQUIRE_CREATE,
			};
		}
		/* 用于获取API */
		namespace API
		{
			/* 此命名空间存储了运行时可能必要的工具和常量 */
			namespace Libray
			{
				static const std::map<Enums::AudioSystemFile, std::wstring> AudioFiles =
				{
					{Enums::AudioSystemFile::DefaultSound, L"ms-winsoundevent:Notification.Default"        },
					{Enums::AudioSystemFile::IM,           L"ms-winsoundevent:Notification.IM"             },
					{Enums::AudioSystemFile::Mail,         L"ms-winsoundevent:Notification.Mail"           },
					{Enums::AudioSystemFile::Reminder,     L"ms-winsoundevent:Notification.Reminder"       },
					{Enums::AudioSystemFile::SMS,          L"ms-winsoundevent:Notification.SMS"            },
					{Enums::AudioSystemFile::Alarm,        L"ms-winsoundevent:Notification.Looping.Alarm"  },
					{Enums::AudioSystemFile::Alarm2,       L"ms-winsoundevent:Notification.Looping.Alarm2" },
					{Enums::AudioSystemFile::Alarm3,       L"ms-winsoundevent:Notification.Looping.Alarm3" },
					{Enums::AudioSystemFile::Alarm4,       L"ms-winsoundevent:Notification.Looping.Alarm4" },
					{Enums::AudioSystemFile::Alarm5,       L"ms-winsoundevent:Notification.Looping.Alarm5" },
					{Enums::AudioSystemFile::Alarm6,       L"ms-winsoundevent:Notification.Looping.Alarm6" },
					{Enums::AudioSystemFile::Alarm7,       L"ms-winsoundevent:Notification.Looping.Alarm7" },
					{Enums::AudioSystemFile::Alarm8,       L"ms-winsoundevent:Notification.Looping.Alarm8" },
					{Enums::AudioSystemFile::Alarm9,       L"ms-winsoundevent:Notification.Looping.Alarm9" },
					{Enums::AudioSystemFile::Alarm10,      L"ms-winsoundevent:Notification.Looping.Alarm10"},
					{Enums::AudioSystemFile::Call,         L"ms-winsoundevent:Notification.Looping.Call"   },
					{Enums::AudioSystemFile::Call1,        L"ms-winsoundevent:Notification.Looping.Call1"  },
					{Enums::AudioSystemFile::Call2,        L"ms-winsoundevent:Notification.Looping.Call2"  },
					{Enums::AudioSystemFile::Call3,        L"ms-winsoundevent:Notification.Looping.Call3"  },
					{Enums::AudioSystemFile::Call4,        L"ms-winsoundevent:Notification.Looping.Call4"  },
					{Enums::AudioSystemFile::Call5,        L"ms-winsoundevent:Notification.Looping.Call5"  },
					{Enums::AudioSystemFile::Call6,        L"ms-winsoundevent:Notification.Looping.Call6"  },
					{Enums::AudioSystemFile::Call7,        L"ms-winsoundevent:Notification.Looping.Call7"  },
					{Enums::AudioSystemFile::Call8,        L"ms-winsoundevent:Notification.Looping.Call8"  },
					{Enums::AudioSystemFile::Call9,        L"ms-winsoundevent:Notification.Looping.Call9"  },
					{Enums::AudioSystemFile::Call10,       L"ms-winsoundevent:Notification.Looping.Call10" },
				};

				static const std::map<Enums::ToastError, std::wstring> ToastErrors = {
					{Enums::ToastError::NoError,               L"No error. The process was executed correctly"												},
					{Enums::ToastError::NotInitialized,        L"The library has not been initialized"														},
					{Enums::ToastError::SystemNotSupported,    L"The OS does not support ToastNotification"													},
					{Enums::ToastError::ShellLinkNotCreated,   L"The library was not able to create a Shell Link for the app"								},
					{Enums::ToastError::InvalidAppUserModelID, L"The AUMI is not a valid one"																},
					{Enums::ToastError::InvalidParameters,     L"Invalid parameters, please double-check the AUMI or App Name"								},
					{Enums::ToastError::NotDisplayed,          L"The toast was created correctly but ToastNotification was not able to display the toast"	},
					{Enums::ToastError::UnknownError,          L"Unknown error"																				}
				};

				static std::map<Enums::Scenario, std::wstring> Scenario =
				{
					{Enums::Scenario::Default,				L"Default"},
					{Enums::Scenario::Alarm,				L"Alarm"},
					{Enums::Scenario::IncomingCall,			L"IncomingCall"},
					{Enums::Scenario::Reminder,				L"Reminder"}
				};

				/* 此命名空间存储了通知需要的函数 */
				namespace Util
				{
					static cloudgameZero::log* ToastPlatformLog()
					{
						static cloudgameZero::log INSTANCE(true, "logConfig.json",
							[](rapidjson::Document& Dom) noexcept -> void
							{
								Dom["outToTerminal"]["render"].SetBool(false);
								Dom["outToTerminal"]["rootLogger"]["level"].SetString("Info");
							}
						, "WinToastPlatform", "Main");
						return &INSTANCE;
					}
					inline RTL_OSVERSIONINFOW getRealOSVersion()
					{
						return cloudgameZero::Foundation::dynamincLibrayFunc::function::RtlGetVersion();
					}

					static HRESULT defaultExecutablePath(_In_ WCHAR* path, _In_ DWORD nSize = MAX_PATH)
					{
						DWORD written = ::GetModuleFileNameExW(GetCurrentProcess(), nullptr, path, nSize);
						ToastPlatformLog()->info("默认的可执行文件位置为： {}", Foundation::Tool::function::Experiment::WideToMuti(path));
						return (written > 0) ? S_OK : E_FAIL;
					}

					static HRESULT defaultShellLinksDirectory(_In_ WCHAR* path, _In_ DWORD nSize = MAX_PATH)
					{
						DWORD written = GetEnvironmentVariableW(L"APPDATA", path, nSize);
						HRESULT hr = written > 0 ? S_OK : E_INVALIDARG;
						if (SUCCEEDED(hr))
						{
							errno_t result = wcscat_s(path, nSize, L"\\Microsoft\\Windows\\Start Menu\\Programs\\");
							hr = (result == 0) ? S_OK : E_INVALIDARG;
							ToastPlatformLog()->info("默认的快捷方式存储路径为： {}", Foundation::Tool::function::Experiment::WideToMuti(path));
						}
						return hr;
					}

					static HRESULT defaultShellLinkPath(_In_ std::wstring const& appname, _In_ WCHAR* path, _In_ DWORD nSize = MAX_PATH)
					{
						HRESULT hr = defaultShellLinksDirectory(path, nSize);
						if (SUCCEEDED(hr)) {
							const std::wstring appLink(appname + L".lnk");
							errno_t result = wcscat_s(path, nSize, appLink.c_str());
							hr = (result == 0) ? S_OK : E_INVALIDARG;
							ToastPlatformLog()->info("默认的快捷方式文件存储路径为： {}", Foundation::Tool::function::Experiment::WideToMuti(path));
						}
						return hr;
					}

					static PCWSTR AsString(_In_ ComPtr<IXmlDocument>& xmlDocument)
					{
						HSTRING xml;
						ComPtr<IXmlNodeSerializer> ser;
						HRESULT hr = xmlDocument.As<IXmlNodeSerializer>(&ser);
						hr = ser->GetXml(&xml);
						if (SUCCEEDED(hr))
						{
							return cloudgameZero::Foundation::dynamincLibrayFunc::function::WindowsGetStringRawBuffer(xml, nullptr);
						}
						return nullptr;
					}

					inline PCWSTR AsString(_In_ HSTRING hstring)
					{
						return cloudgameZero::Foundation::dynamincLibrayFunc::function::WindowsGetStringRawBuffer(hstring, nullptr);
					}

					static HRESULT setNodeStringValue(_In_ std::wstring const& string, _Out_opt_ IXmlNode* node, _Out_ IXmlDocument* xml) {
						ComPtr<IXmlText> textNode;
						HRESULT hr = xml->CreateTextNode(cloudgameZero::Foundation::Warpper::HstringWrapper(string).Get(), &textNode);
						if (SUCCEEDED(hr))
						{
							ComPtr<IXmlNode> stringNode;
							hr = textNode.As(&stringNode);
							if (SUCCEEDED(hr))
							{
								ComPtr<IXmlNode> appendedChild;
								hr = node->AppendChild(stringNode.Get(), &appendedChild);
							}
						}
						return hr;
					}

					static HRESULT addAttribute(_In_ IXmlDocument* xml, std::wstring const& name, IXmlNamedNodeMap* attributeMap)
					{
						ComPtr<ABI::Windows::Data::Xml::Dom::IXmlAttribute> srcAttribute;
						HRESULT hr = xml->CreateAttribute(cloudgameZero::Foundation::Warpper::HstringWrapper(name).Get(), &srcAttribute);
						if (SUCCEEDED(hr))
						{
							ComPtr<IXmlNode> node;
							hr = srcAttribute.As(&node);
							if (SUCCEEDED(hr))
							{
								ComPtr<IXmlNode> pNode;
								hr = attributeMap->SetNamedItem(node.Get(), &pNode);
							}
						}
						return hr;
					}

					static HRESULT createElement(_In_ IXmlDocument* xml, _In_ std::wstring const& root_node, _In_ std::wstring const& element_name,
						_In_ std::vector<std::wstring> const& attribute_names)
					{
						ComPtr<IXmlNodeList> rootList;
						HRESULT hr = xml->GetElementsByTagName(cloudgameZero::Foundation::Warpper::HstringWrapper(root_node).Get(), &rootList);
						if (SUCCEEDED(hr))
						{
							ComPtr<IXmlNode> root;
							hr = rootList->Item(0, &root);
							if (SUCCEEDED(hr))
							{
								ComPtr<ABI::Windows::Data::Xml::Dom::IXmlElement> audioElement;
								hr = xml->CreateElement(cloudgameZero::Foundation::Warpper::HstringWrapper(element_name).Get(), &audioElement);
								if (SUCCEEDED(hr))
								{
									ComPtr<IXmlNode> audioNodeTmp;
									hr = audioElement.As(&audioNodeTmp);
									if (SUCCEEDED(hr))
									{
										ComPtr<IXmlNode> audioNode;
										hr = root->AppendChild(audioNodeTmp.Get(), &audioNode);
										if (SUCCEEDED(hr))
										{
											ComPtr<IXmlNamedNodeMap> attributes;
											hr = audioNode->get_Attributes(&attributes);
											if (SUCCEEDED(hr))
											{
												for (auto const& it : attribute_names)
												{
													hr = addAttribute(xml, it, attributes.Get());
												}
											}
										}
									}
								}
							}
						}
						return hr;
					}

				}
			}
			/* Toast事件接口 */
			namespace Event
			{
				/* 抽象接口，若调用通知，请实现此接口所有的抽象方法并传入 */
				__interface ToastPlatformHandler
				{
					virtual void Activated() const = 0;
					virtual void Activated(int actionIndex) const = 0;
					virtual void Dismissed(Enums::ToastDismissalReason state) const = 0;
					virtual void Failed() const = 0;
				};

				/* 在调用时showToast时，将会安装事件 */
				template<typename FunctorT>
				HRESULT setEventHandler(
					_In_ ABI::Windows::UI::Notifications::IToastNotification* notification,
					_In_ std::shared_ptr<ToastPlatformHandler> eventHandler,
					_In_ INT64 expirationTime,
					_Out_ EventRegistrationToken& activatedToken,
					_Out_ EventRegistrationToken& dismissedToken,
					_Out_ EventRegistrationToken& failedToken,
					_In_ FunctorT&& markAsReadyForDeletionFunc
				)
				{
					auto activated = [eventHandler, markAsReadyForDeletionFunc](IToastNotification* notify, IInspectable* inspectable)
						{
							ComPtr<IToastActivatedEventArgs> activatedEventArgs;
							HRESULT hr = inspectable->QueryInterface(activatedEventArgs.GetAddressOf());
							if (SUCCEEDED(hr))
							{
								HSTRING argumentsHandle;
								hr = activatedEventArgs->get_Arguments(&argumentsHandle);
								if (SUCCEEDED(hr))
								{
									PCWSTR arguments = Libray::Util::AsString(argumentsHandle);
									if (arguments && *arguments)
									{
										eventHandler->Activated(static_cast<int>(wcstol(arguments, nullptr, 10)));
										cloudgameZero::Foundation::dynamincLibrayFunc::function::WindowsDeleteString(argumentsHandle);
										markAsReadyForDeletionFunc();
										return S_OK;
									}
									cloudgameZero::Foundation::dynamincLibrayFunc::function::WindowsDeleteString(argumentsHandle);
								}
							}
							eventHandler->Activated();
							markAsReadyForDeletionFunc();
							return S_OK;
						};

					auto dismissed = [eventHandler, expirationTime, markAsReadyForDeletionFunc](IToastNotification* notify, IToastDismissedEventArgs* e)
						{
							ToastDismissalReason reason;
							if (SUCCEEDED(e->get_Reason(&reason)))
							{
								if (reason == ToastDismissalReason_UserCanceled && expirationTime && cloudgameZero::Foundation::Warpper::InternalDateTime::Now() >= expirationTime)
								{
									reason = ToastDismissalReason_TimedOut;
								}
								eventHandler->Dismissed(static_cast<Enums::ToastDismissalReason>(reason));
							}
							markAsReadyForDeletionFunc();
							return S_OK;
						};

					auto failed = [eventHandler, markAsReadyForDeletionFunc](IToastNotification* notify, IToastFailedEventArgs* e)
						{
							eventHandler->Failed();
							markAsReadyForDeletionFunc();
							return S_OK;
						};

					HRESULT hr = notification->add_Activated(Callback<Implements<RuntimeClassFlags<ClassicCom>, ITypedEventHandler<ToastNotification*, IInspectable*>>>(activated).Get(), &activatedToken);
					if (SUCCEEDED(hr))
					{
						hr = notification->add_Dismissed(Callback<Implements<RuntimeClassFlags<ClassicCom>, ITypedEventHandler<ToastNotification*, ToastDismissedEventArgs*>>>(dismissed).Get(), &dismissedToken);
						if (SUCCEEDED(hr))
						{
							hr = notification->add_Failed(Callback<Implements<RuntimeClassFlags<ClassicCom>, ITypedEventHandler<ToastNotification*, ToastFailedEventArgs*>>>(failed).Get(), &failedToken);
						}
					}
					return hr;
				}
			}

			/* Windows通知将使用此结构体 */
			__STRUCT__ ToastTemplate{
			public:
				ToastTemplate(_In_ Enums::ToastTemplateType type = Enums::ToastTemplateType::ImageAndText02) : _type(type)
				{
					constexpr static std::size_t TextFieldsCount[] = { 1, 2, 2, 3, 1, 2, 2, 3 };
					this->_textFields = std::vector<std::wstring>(TextFieldsCount[int(type)]);
				}

				~ToastTemplate()
				{
					this->_textFields.clear();
				}

				void setTextField(_In_ std::wstring const& txt, _In_ Enums::TextField pos)
				{
					auto const position = static_cast<std::size_t>(pos);
					if (position >= _textFields.size())
					{
						Libray::Util::ToastPlatformLog()->info("您选择的Toast模板仅支持： {} 行", this->_textFields.size());
						return;
					}
					this->_textFields[position] = txt;
				}

				void setImagePath(_In_ std::wstring const& imgPath, _In_ Enums::CropHint cropHint = Enums::CropHint::Square)
				{
					Libray::Util::ToastPlatformLog()->info(L"设置图像路径为 : {}", imgPath);
					this->_imagePath = imgPath;
					this->_cropHint = cropHint;
				}

				void setAudioPath(_In_ Enums::AudioSystemFile file)
				{
					auto const iter = Libray::AudioFiles.find(file);
					assert(iter != Libray::AudioFiles.end());
					_audioPath = iter->second;
				}

				void setScenario(_In_ Enums::Scenario scenario)
				{
					switch (scenario)
					{
					case Enums::Scenario::Default:
						this->_scenario = L"Default";
						break;
					case Enums::Scenario::Alarm:
					{
						this->_scenario = L"Alarm";
						break;
					}
					case Enums::Scenario::IncomingCall:
					{
						this->_scenario = L"IncomingCall";
					}   break;
					case Enums::Scenario::Reminder:
					{
						this->_scenario = L"Reminder";
						break;
					}
					}
					return;
				}

				std::wstring const& getTextField(_In_ Enums::TextField pos) const
				{
					auto const position = static_cast<std::size_t>(pos);
					assert(position < _textFields.size());
					return this->_textFields[position];
				}

				std::wstring const& getActionLabel(_In_ std::size_t pos) const
				{
					assert(pos < _actions.size());
					return this->_actions[pos];
				}

				void setFirstLine(_In_ std::wstring const& text) { this->setTextField(text, Enums::TextField::FirstLine); }
				void setSecondLine(_In_ std::wstring const& text) { this->setTextField(text, Enums::TextField::SecondLine); }
				void setThirdLine(_In_ std::wstring const& text) { this->setTextField(text, Enums::TextField::ThirdLine); }
				void setAttributionText(_In_ std::wstring const& attributionText) { this->_attributionText = attributionText; }
				void setHeroImagePath(_In_ std::wstring const& imgPath, _In_ bool inlineImage = false) { this->_heroImagePath = imgPath; this->_inlineHeroImage = inlineImage; }
				void setAudioPath(_In_ std::wstring const& audioPath) { this->_audioPath = audioPath; }
				void setAudioOption(_In_ Enums::AudioOption audioOption) { this->_audioOption = audioOption; }
				void setDuration(_In_ Enums::Duration duration) { this->_duration = duration; }
				void setExpiration(_In_ INT64 millisecondsFromNow) { this->_expiration = millisecondsFromNow; }
				void addAction(_In_ std::wstring const& label) { this->_actions.push_back(label); }
				std::size_t getActionsCount() const { return this->_actions.size(); }
				bool isToastGeneric() const { return this->hasHeroImage() || this->_cropHint == Enums::CropHint::Circle; }
				bool isInlineHeroImage() const { return this->_inlineHeroImage; }
				bool hasImage() const { return this->_type < Enums::ToastTemplateType::Text01; }
				bool hasHeroImage() const { return hasImage() && !this->_heroImagePath.empty(); }
				std::vector<std::wstring> const& getTextFields() const { return this->_textFields; }
				std::size_t getTextFieldsCount() const { return this->_textFields.size(); }
				std::wstring const& getImagePath() const { return this->_imagePath; }
				std::wstring const& getHeroImagePath() const { return this->_heroImagePath; }
				std::wstring const& getAudioPath() const { return this->_audioPath; }
				std::wstring const& getAttributionText() const { return this->_attributionText; }
				INT64 getExpiration() const { return this->_expiration; }
				std::wstring const& getScenario() const { return this->_scenario; }
				bool isCropHintCircle() const { return this->_cropHint == Enums::CropHint::Circle; }
				Enums::ToastTemplateType getType() const { return this->_type; }
				Enums::AudioOption getAudioOption() const { return this->_audioOption; }
				Enums::Duration getDuration() const { return this->_duration; }
			private:
				std::vector<std::wstring> _textFields{};
				std::vector<std::wstring> _actions{};
				std::wstring _imagePath{};
				std::wstring _heroImagePath{};
				bool _inlineHeroImage{ false };
				std::wstring _audioPath{};
				std::wstring _attributionText{};
				std::wstring _scenario{L"Default"};
				INT64 _expiration = NULL;
				Enums::AudioOption _audioOption = Enums::AudioOption::Default;
				Enums::ToastTemplateType _type = Enums::ToastTemplateType::Text01;
				Enums::Duration _duration = Enums::Duration::System;
				Enums::CropHint _cropHint = Enums::CropHint::Square;
			};

			class ToastNotification {
			public:
				explicit ToastNotification() : _isInitialized(false), _hasCoInitialized(false) {}
				virtual ~ToastNotification()
				{
					try {
						this->clear();
						if (_hasCoInitialized) {
							CoUninitialize();
						}
					}
					catch (...)
					{
						PrintError("ToastNotification析构出现错误");
						return;
					}
				}

				static ToastNotification* instance()
				{
					static ToastNotification INSTANCE;
					return &INSTANCE;
				}

				static bool isSupportingModernFeatures()
				{
					constexpr auto MinimumSupportedVersion = 6;
					return Libray::Util::getRealOSVersion().dwMajorVersion > MinimumSupportedVersion;
				}

				static bool isWin10AnniversaryOrHigher()
				{
					return Libray::Util::getRealOSVersion().dwBuildNumber >= 14393;
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

				virtual bool Init(_Out_opt_ Enums::ToastError* error = nullptr)
				{
					_isInitialized = false;
					setError(error, Enums::ToastError::NoError);
					if (_aumi.empty() || _appName.empty())
					{
						setError(error, Enums::ToastError::InvalidParameters);
						Libray::Util::ToastPlatformLog()->warn("警告：你需要给aumi或者appname设置一个名称，而不是直接初始化");
						return false;
					}
					if (_shortcutPolicy != Enums::ShortcutPolicy::SHORTCUT_POLICY_IGNORE)
					{
						if (createShortcut() < 0) {
							setError(error, Enums::ToastError::ShellLinkNotCreated);
							Libray::Util::ToastPlatformLog()->warn("如果要触发Toast通知：您必须提供了一个Aumi和一个在开始菜单的快捷方式(不应该忽略创建)");
							return false;
						}
					}
					if (FAILED(SetCurrentProcessExplicitAppUserModelID(_aumi.c_str())))
					{
						setError(error, Enums::ToastError::InvalidAppUserModelID);
						Libray::Util::ToastPlatformLog()->error("无法设置aumi，某些设置可能出现了错误");
						return false;
					}
					this->_isInitialized = true;
					return this->_isInitialized;
				}

				virtual bool isInit() const { return this->_isInitialized; }
				std::wstring const& getAppName() const { return this->_appName; };
				std::wstring const& getAppUserModelId() const { return this->_aumi; };
				void setAppUserModelId(_In_ std::wstring const& aumi) { this->_aumi = aumi; }
				void setAppName(_In_ std::wstring const& AppName) { this->_appName = AppName; }
				void setShortcutPolicy(_In_ Enums::ShortcutPolicy policy) { this->_shortcutPolicy = policy; }

				virtual bool hide(_In_ INT64 id)
				{
					if (!isInit())
					{
						Libray::Util::ToastPlatformLog()->error("发生错误在隐藏吐司的时候，你需要初始化实例才能使用");
						return false;
					}
					auto iter = _buffer.find(id);
					if (iter == _buffer.end())
					{
						return false;
					}
					auto succeded = false;
					auto notify = notifier(&succeded);
					if (!succeded)
					{
						return false;
					}
					auto& notifyData = iter->second;
					auto result = notify->Hide(notifyData.notification());
					if (FAILED(result))
					{
						Libray::Util::ToastPlatformLog()->info("隐藏吐司失败！. 代码: {}", result);
						return false;
					}
					notifyData.RemoveTokens();
					_buffer.erase(iter);
					return SUCCEEDED(result);
				}

				virtual INT64 show(_In_ ToastTemplate const& toast, _In_ Event::ToastPlatformHandler* eventHandler, Enums::ToastError* error = nullptr)
				{
					using namespace cloudgameZero::Foundation::Warpper;
					using namespace cloudgameZero::Foundation::dynamincLibrayFunc::function;
					std::shared_ptr<Event::ToastPlatformHandler> handler(eventHandler);
					this->setError(error, Enums::ToastError::NoError);
					INT64 id = -1;
					if (!isInit())
					{
						this->setError(error, Enums::ToastError::NotInitialized);
						Libray::Util::ToastPlatformLog()->warn("在启动通知的时候发生了错误，需要初始化实例才能启动");
						return id;
					}
					if (!handler)
					{
						this->setError(error, Enums::ToastError::InvalidHandler);
						Libray::Util::ToastPlatformLog()->error("无效的事件处理句柄，句柄不能为空指针");
						return id;
					}
					ComPtr<IToastNotificationManagerStatics> notificationManager;
					HRESULT hr = Wrap_GetActivationFactory(HstringWrapper(RuntimeClass_Windows_UI_Notifications_ToastNotificationManager).Get(), &notificationManager);
					if (SUCCEEDED(hr))
					{
						ComPtr<IToastNotifier> notifier;
						hr = notificationManager->CreateToastNotifierWithId(HstringWrapper(this->_aumi).Get(), &notifier);
						if (SUCCEEDED(hr))
						{
							ComPtr<IToastNotificationFactory> notificationFactory;
							hr = Wrap_GetActivationFactory(HstringWrapper(RuntimeClass_Windows_UI_Notifications_ToastNotification).Get(), &notificationFactory);
							if (SUCCEEDED(hr))
							{
								/* 此处将会开始构建Toast xml文件 */
								ComPtr<IXmlDocument> xmlDocument;
								hr = notificationManager->GetTemplateContent(ToastTemplateType(toast.getType()), &xmlDocument);
								if (SUCCEEDED(hr) && toast.isToastGeneric())
								{
									hr = this->setBindToastGenericHelper(xmlDocument.Get());
								}
								if (SUCCEEDED(hr))
								{
									UINT i = 0;
									for (auto& it : toast.getTextFields())
									{
										hr = this->setTextFieldHelper(xmlDocument.Get(), toast.getTextField(Enums::TextField(i)), i);
										i++;
									}
									// Modern feature are supported Windows > Windows 10
									if (SUCCEEDED(hr) && isSupportingModernFeatures())
									{
										// Note that we do this *after* using toast.textFieldsCount() to
										// iterate/fill the template's text fields, since we're adding yet another text field.
										if (SUCCEEDED(hr) && !toast.getAttributionText().empty())
										{
											hr = setAttributionTextFieldHelper(xmlDocument.Get(), toast.getAttributionText());
										}
										std::array<WCHAR, 12> buf{};
										for (std::size_t i = 0, actionsCount = toast.getActionsCount(); i < actionsCount && SUCCEEDED(hr); i++)
										{
											_snwprintf_s(buf.data(), buf.size(), _TRUNCATE, L"%zd", i);
											hr = addActionHelper(xmlDocument.Get(), toast.getActionLabel(i), buf.data());
										}
										if (SUCCEEDED(hr))
										{
											hr = (toast.getAudioPath().empty() && toast.getAudioOption() == Enums::AudioOption::Default) ? hr : setAudioFieldHelper(xmlDocument.Get(), toast.getAudioPath(), toast.getAudioOption());
										}
										if (SUCCEEDED(hr) && toast.getDuration() != Enums::Duration::System)
										{
											hr = addDurationHelper(xmlDocument.Get(), (toast.getDuration() == Enums::Duration::Short) ? L"short" : L"long");
										}
										if (SUCCEEDED(hr))
										{
											hr = addScenarioHelper(xmlDocument.Get(), toast.getScenario());
										}
									}
									else
									{
										Libray::Util::ToastPlatformLog()->warn(L"当前版本不支持该现代特性: -> (Actions/Sounds/Attributes)", Libray::Util::AsString(xmlDocument));
									}
									if (SUCCEEDED(hr))
									{
										bool isWin10AnniversaryOrAbove = ToastNotification::isWin10AnniversaryOrHigher();
										bool isCircleCropHint = isWin10AnniversaryOrAbove ? toast.isCropHintCircle() : false;
										hr = toast.hasImage() ? setImageFieldHelper(xmlDocument.Get(), toast.getImagePath(), toast.isToastGeneric(), isCircleCropHint) : hr;
										if (SUCCEEDED(hr) && isWin10AnniversaryOrAbove && toast.hasHeroImage())
										{
											hr = setHeroImageHelper(xmlDocument.Get(), toast.getHeroImagePath(), toast.isInlineHeroImage());
										}
										if (SUCCEEDED(hr))
										{
											ComPtr<IToastNotification> notification;
											hr = notificationFactory->CreateToastNotification(xmlDocument.Get(), &notification);
											if (SUCCEEDED(hr))
											{
												INT64 expiration = 0, relativeExpiration = toast.getExpiration();
												if (relativeExpiration > 0)
												{
													InternalDateTime* expirationDateTime =
														dynamic_cast<InternalDateTime*>(
															new Interface::sigmaInterface::Implement::__InternalDateTime(relativeExpiration));
													expiration = *expirationDateTime;
													hr = notification->put_ExpirationTime(expirationDateTime);
													expirationDateTime->Release();
												}
												EventRegistrationToken activatedToken{}, dismissedToken{}, failedToken{};
												GUID guid;
												HRESULT hrGuid = CoCreateGuid(&guid);
												id = guid.Data1;
												if (SUCCEEDED(hr) && SUCCEEDED(hrGuid))
												{
													hr = Event::setEventHandler(notification.Get(), handler, expiration, activatedToken, dismissedToken,
														failedToken, [this, id]() { markAsReadyForDeletion(id); });
													if (FAILED(hr))
													{
														this->setError(error, Enums::ToastError::InvalidHandler);
													}
												}
												if (SUCCEEDED(hr))
												{
													if (SUCCEEDED(hr))
													{
														this->_buffer.emplace(id, NotifyData(notification, activatedToken, dismissedToken, failedToken));
														Libray::Util::ToastPlatformLog()->info(L"构建Toast得到的XML内容: {}", Libray::Util::AsString(xmlDocument));
														hr = notifier->Show(notification.Get());
														if (FAILED(hr))
														{
															this->setError(error, Enums::ToastError::NotDisplayed);
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
					return FAILED(hr) ? -1 : id;
				}

				virtual void clear()
				{
					auto succeded = false;
					auto notify = notifier(&succeded);
					if (!succeded)
					{
						return;
					}
					for (auto& data : _buffer)
					{
						auto& notifyData = data.second;
						notify->Hide(notifyData.notification());
						notifyData.RemoveTokens();
					}
					_buffer.clear();
				}

				virtual Enums::ShortcutResult createShortcut()
				{
					if (this->_aumi.empty() || this->_appName.empty())
					{
						Libray::Util::ToastPlatformLog()->warn("错误：用户模型或用户名中，其中有一个为空");
						return Enums::ShortcutResult::SHORTCUT_MISSING_PARAMETERS;
					}
					if (!this->_hasCoInitialized)
					{
						HRESULT initHr = CoInitializeEx(nullptr, COINIT::COINIT_MULTITHREADED);
						if (initHr != RPC_E_CHANGED_MODE)
						{
							if (FAILED(initHr) && initHr != S_FALSE)
							{
								Libray::Util::ToastPlatformLog()->error("无法初始化COM库组件!");
								return Enums::ShortcutResult::SHORTCUT_COM_INIT_FAILURE;
							}
							else
							{
								this->_hasCoInitialized = true;
							}
						}
					}

					bool wasChanged;
					HRESULT hr = validateShellLinkHelper(wasChanged);
					if (SUCCEEDED(hr)) {
						return wasChanged ? Enums::ShortcutResult::SHORTCUT_WAS_CHANGED : Enums::ShortcutResult::SHORTCUT_UNCHANGED;
					}

					hr = createShellLinkHelper();
					return SUCCEEDED(hr) ? Enums::ShortcutResult::SHORTCUT_WAS_CREATED : Enums::ShortcutResult::SHORTCUT_CREATE_FAILED;
				}
			protected:
				interface NotifyData
				{
					explicit NotifyData() = default;
					explicit NotifyData(
						_In_ ComPtr<IToastNotification> notify,
						_In_ EventRegistrationToken activatedToken,
						_In_ EventRegistrationToken dismissedToken,
						_In_ EventRegistrationToken failedToken
					) : _notify(notify), _activatedToken(activatedToken), _dismissedToken(dismissedToken), _failedToken(failedToken) {}
					~NotifyData() { RemoveTokens(); }
					void markAsReadyForDeletion() { _readyForDeletion = true; }
					bool isReadyForDeletion() const { return _readyForDeletion; }
					IToastNotification* notification() { return _notify.Get(); }
					inline void RemoveTokens()
					{
						if (!_readyForDeletion)
						{
							return;
						}
						if (_previouslyTokenRemoved)
						{
							return;
						}
						if (!_notify.Get())
						{
							return;
						}
						_notify->remove_Activated(_activatedToken);
						_notify->remove_Dismissed(_dismissedToken);
						_notify->remove_Failed(_failedToken);
						_previouslyTokenRemoved = true;
					}
				private:
					ComPtr<IToastNotification> _notify = nullptr;
					EventRegistrationToken _activatedToken{};
					EventRegistrationToken _dismissedToken{};
					EventRegistrationToken _failedToken{};
					bool _readyForDeletion = false;
					bool _previouslyTokenRemoved = false;
				};

				bool _isInitialized = false;
				bool _hasCoInitialized = false;
				Enums::ShortcutPolicy _shortcutPolicy = Enums::ShortcutPolicy::SHORTCUT_POLICY_REQUIRE_CREATE;
				std::wstring _appName;
				std::wstring _aumi;
				std::map<INT64, NotifyData> _buffer{};
				inline void markAsReadyForDeletion(_In_ INT64 id)
				{
					for (auto it = this->_buffer.begin(); it != this->_buffer.end();)
					{
						if (it->second.isReadyForDeletion())
						{
							it->second.RemoveTokens();
							it = this->_buffer.erase(it);
						}
						else
						{
							it++;
						}
					}
					auto const iter = _buffer.find(id);
					if (iter != _buffer.end())
					{
						this->_buffer[id].markAsReadyForDeletion();
					}
				}
				inline HRESULT validateShellLinkHelper(_Out_ bool& wasChanged)
				{
					WCHAR path[MAX_PATH] = { L'\0' };
					Libray::Util::defaultShellLinkPath(_appName, path);
					DWORD attr = GetFileAttributesW(path);
					if (attr >= 0xFFFFFFF)
					{
						DEBUG_MESSAGE(L"未找到快捷方式，尝试创建一个!");
						return E_FAIL;
					}
					ComPtr<IShellLinkW> IshellLinkptr;
					HRESULT hr = CoCreateInstance(CLSID_ShellLink, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&IshellLinkptr));
					do {
						if (FAILED(hr))
						{
							break;
						}
						ComPtr<IPersistFile> file;
						hr = IshellLinkptr.As(&file);
						if (FAILED(hr))
						{
							break;
						}
						hr = file->Load(path, STGM_READWRITE);
						if (FAILED(hr))
						{
							break;
						}
						else {
							ComPtr<IPropertyStore> store;
							hr = IshellLinkptr.As(&store);
							if (FAILED(hr))
							{
								break;
							}
							PROPVARIANT appIdPropVar;
							hr = store->GetValue(PKEY_AppUserModel_ID, &appIdPropVar);
							if (FAILED(hr))
							{
								break;
							}
							WCHAR AUMI[MAX_PATH];
							hr = cloudgameZero::Foundation::dynamincLibrayFunc::function::PropVariantToString(appIdPropVar, AUMI, MAX_PATH);
							wasChanged = false;
							if (FAILED(hr) || this->_aumi != AUMI)
							{
								if (this->_shortcutPolicy != Enums::ShortcutPolicy::SHORTCUT_POLICY_REQUIRE_CREATE)
								{
									return E_FAIL;
								}
								wasChanged = true;
								PropVariantClear(&appIdPropVar);
								hr = InitPropVariantFromString(_aumi.c_str(), &appIdPropVar);
								if (FAILED(hr))
								{
									return hr;
								}
								hr = store->SetValue(PKEY_AppUserModel_ID, appIdPropVar);
								if (FAILED(hr))
								{
									break;
								}
								hr = store->Commit();
								if (SUCCEEDED(hr) && SUCCEEDED(file->IsDirty()))
								{
									hr = file->Save(path, TRUE);
								}
							}
						}
					} while (false);
					return hr;
				}

				HRESULT createShellLinkHelper()
				{
					if (_shortcutPolicy != Enums::ShortcutPolicy::SHORTCUT_POLICY_REQUIRE_CREATE)
					{
						return E_FAIL;
					}
					WCHAR exePath[MAX_PATH]{ L'\0' };
					WCHAR slPath[MAX_PATH]{ L'\0' };
					Libray::Util::defaultShellLinkPath(_appName, slPath);
					Libray::Util::defaultExecutablePath(exePath);
					HRESULT hr = NULL;
					if (hr = CoInitialize(NULL); SUCCEEDED(hr))
					{
						return hr;
					}
					do {
						ComPtr<IShellLinkW> IshellLinkptr;
						hr = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLinkW, (void**)&IshellLinkptr);
						if (SUCCEEDED(hr))
						{
							ComPtr<IPersistFile> file;
							IshellLinkptr->SetPath(exePath);
							IshellLinkptr->SetWorkingDirectory(exePath);
							ComPtr<IPropertyStore> store;
							hr = IshellLinkptr.As(&store);
							if (FAILED(hr))
							{
								break;
							}
							else
							{
								PROPVARIANT appIdPropVar;
								hr = InitPropVariantFromString(this->_aumi.c_str(), &appIdPropVar);
								if (FAILED(hr))
								{
									break;
								}
								hr = store->SetValue(PKEY_AppUserModel_ID, appIdPropVar);
								if (FAILED(hr))
								{
									break;
								}
								hr = store->Commit();
								if (FAILED(hr))
								{
									break;
								}
								PropVariantClear(&appIdPropVar);
								hr = IshellLinkptr.As(&file);
								if (SUCCEEDED(hr))
								{
									file->Save(slPath, TRUE);
									file->Release();
									IshellLinkptr->Release();
									CoUninitialize();
									return S_OK;
								}
							}
						}
					} while (false);
					CoUninitialize();
					return hr;
				}

				HRESULT setImageFieldHelper(_In_ IXmlDocument* xml, _In_ std::wstring const& path, _In_ bool isToastGeneric, bool isCropHintCircle)
				{
					using namespace cloudgameZero::Foundation::Warpper;
					assert(path.size() < MAX_PATH);
					wchar_t imagePath[MAX_PATH] = L"file:///";
					HRESULT hr = StringCchCatW(imagePath, MAX_PATH, path.c_str());
					if (SUCCEEDED(hr))
					{
						ComPtr<IXmlNodeList> nodeList;
						HRESULT hr = xml->GetElementsByTagName(HstringWrapper(L"image").Get(), &nodeList);
						if (SUCCEEDED(hr))
						{
							ComPtr<IXmlNode> node;
							hr = nodeList->Item(0, &node);
							ComPtr<IXmlElement> imageElement;
							HRESULT hrImage = node.As(&imageElement);
							if (SUCCEEDED(hr) && SUCCEEDED(hrImage) && isToastGeneric)
							{
								hr = imageElement->SetAttribute(HstringWrapper(L"placement").Get(), HstringWrapper(L"appLogoOverride").Get());
								if (SUCCEEDED(hr) && isCropHintCircle)
								{
									hr = imageElement->SetAttribute(HstringWrapper(L"hint-crop").Get(), HstringWrapper(L"circle").Get());
								}
							}
							if (SUCCEEDED(hr))
							{
								ComPtr<IXmlNamedNodeMap> attributes;
								hr = node->get_Attributes(&attributes);
								if (SUCCEEDED(hr))
								{
									ComPtr<IXmlNode> editedNode;
									hr = attributes->GetNamedItem(HstringWrapper(L"src").Get(), &editedNode);
									if (SUCCEEDED(hr))
									{
										Libray::Util::setNodeStringValue(imagePath, editedNode.Get(), xml);
									}
								}
							}
						}
					}
					return hr;
				}

				HRESULT setHeroImageHelper(_In_ IXmlDocument* xml, _In_ std::wstring const& path, _In_ bool isInlineImage)
				{
					using namespace cloudgameZero::Foundation::Warpper;
					ComPtr<IXmlNodeList> nodeList;
					HRESULT hr = xml->GetElementsByTagName(HstringWrapper(L"binding").Get(), &nodeList);
					if (SUCCEEDED(hr))
					{
						UINT32 length;
						hr = nodeList->get_Length(&length);
						if (SUCCEEDED(hr))
						{
							ComPtr<IXmlNode> bindingNode;
							if (length > 0)
							{
								hr = nodeList->Item(0, &bindingNode);
							}
							if (SUCCEEDED(hr))
							{
								ComPtr<IXmlElement> imageElement;
								hr = xml->CreateElement(HstringWrapper(L"image").Get(), &imageElement);
								if (SUCCEEDED(hr) && isInlineImage == false)
								{
									hr = imageElement->SetAttribute(HstringWrapper(L"placement").Get(), HstringWrapper(L"hero").Get());
								}
								if (SUCCEEDED(hr))
								{
									hr = imageElement->SetAttribute(HstringWrapper(L"src").Get(), HstringWrapper(path).Get());
								}
								if (SUCCEEDED(hr))
								{
									ComPtr<IXmlNode> actionNode;
									hr = imageElement.As(&actionNode);
									if (SUCCEEDED(hr))
									{
										ComPtr<IXmlNode> appendedChild;
										hr = bindingNode->AppendChild(actionNode.Get(), &appendedChild);
									}
								}
							}
						}
					}
					return hr;
				}

				HRESULT setBindToastGenericHelper(_In_ IXmlDocument* xml)
				{
					using namespace cloudgameZero::Foundation::Warpper;
					ComPtr<IXmlNodeList> nodeList;
					HRESULT hr = xml->GetElementsByTagName(HstringWrapper(L"binding").Get(), &nodeList);
					if (SUCCEEDED(hr))
					{
						UINT32 length;
						hr = nodeList->get_Length(&length);
						if (SUCCEEDED(hr))
						{
							ComPtr<IXmlNode> toastNode;
							hr = nodeList->Item(0, &toastNode);
							if (SUCCEEDED(hr))
							{
								ComPtr<IXmlElement> toastElement;
								hr = toastNode.As(&toastElement);
								if (SUCCEEDED(hr))
								{
									hr = toastElement->SetAttribute(HstringWrapper(L"template").Get(), HstringWrapper(L"ToastGeneric").Get());
								}
							}
						}
					}
					return hr;
				}

				HRESULT setAudioFieldHelper(_In_ IXmlDocument* xml, _In_ std::wstring const& path, _In_opt_ Enums::AudioOption option = Enums::AudioOption::Default)
				{
					using namespace cloudgameZero::Foundation::Warpper;
					std::vector<std::wstring> attrs;
					if (!path.empty())
					{
						attrs.push_back(L"src");
					}
					if (option == Enums::AudioOption::Loop)
					{
						attrs.push_back(L"loop");
					}
					if (option == Enums::AudioOption::Silent)
					{
						attrs.push_back(L"silent");
					}
					Libray::Util::createElement(xml, L"toast", L"audio", attrs);
					ComPtr<IXmlNodeList> nodeList;
					HRESULT hr = xml->GetElementsByTagName(HstringWrapper(L"audio").Get(), &nodeList);
					if (SUCCEEDED(hr))
					{
						ComPtr<IXmlNode> node;
						hr = nodeList->Item(0, &node);
						if (SUCCEEDED(hr))
						{
							ComPtr<IXmlNamedNodeMap> attributes;
							hr = node->get_Attributes(&attributes);
							if (SUCCEEDED(hr))
							{
								ComPtr<IXmlNode> editedNode;
								if (!path.empty())
								{
									if (SUCCEEDED(hr))
									{
										hr = attributes->GetNamedItem(HstringWrapper(L"src").Get(), &editedNode);
										if (SUCCEEDED(hr))
										{
											hr = Libray::Util::setNodeStringValue(path, editedNode.Get(), xml);
										}
									}
								}
								if (SUCCEEDED(hr))
								{
									switch (option)
									{
									case Enums::AudioOption::Loop:
									{
										hr = attributes->GetNamedItem(HstringWrapper(L"loop").Get(), &editedNode);
										if (SUCCEEDED(hr))
										{
											hr = Libray::Util::setNodeStringValue(L"true", editedNode.Get(), xml);
										}
										break;
									}
									case Enums::AudioOption::Silent:
									{
										hr = attributes->GetNamedItem(HstringWrapper(L"silent").Get(), &editedNode);
										if (SUCCEEDED(hr))
										{
											hr = Libray::Util::setNodeStringValue(L"true", editedNode.Get(), xml);
										}
										break;
									}
									default:
									{
										break;
									}
									}
								}
							}
						}
					}
					return hr;
				}
				/*
				以下函数中暂时禁用了C4267，因为size_t转到UINT32导致
				*/
#pragma warning(push)
#pragma warning(disable : 4267)
				HRESULT setTextFieldHelper(_In_ IXmlDocument* xml, _In_ std::wstring const& text, _In_ size_t pos)
				{
					ComPtr<IXmlNodeList> nodeList;
					HRESULT hr = xml->GetElementsByTagName(Foundation::Warpper::HstringWrapper(L"text").Get(), &nodeList);
					if (SUCCEEDED(hr))
					{
						ComPtr<IXmlNode> node;
						hr = nodeList->Item(pos, &node);
						if (SUCCEEDED(hr))
						{
							hr = Libray::Util::setNodeStringValue(text, node.Get(), xml);
						}
					}
					return hr;
				}
#pragma warning(pop)

				HRESULT setAttributionTextFieldHelper(_In_ IXmlDocument* xml, _In_ std::wstring const& text)
				{
					using namespace cloudgameZero::Foundation::Warpper;
					Libray::Util::createElement(xml, L"binding", L"text", { L"placement" });
					ComPtr<IXmlNodeList> nodeList;
					HRESULT hr = xml->GetElementsByTagName(HstringWrapper(L"text").Get(), &nodeList);
					if (SUCCEEDED(hr))
					{
						UINT32 nodeListLength;
						hr = nodeList->get_Length(&nodeListLength);
						if (SUCCEEDED(hr)) {
							for (UINT32 i = 0; i < nodeListLength; i++)
							{
								ComPtr<IXmlNode> textNode;
								hr = nodeList->Item(i, &textNode);
								if (SUCCEEDED(hr))
								{
									ComPtr<IXmlNamedNodeMap> attributes;
									hr = textNode->get_Attributes(&attributes);
									if (SUCCEEDED(hr))
									{
										ComPtr<IXmlNode> editedNode;
										if (SUCCEEDED(hr))
										{
											hr = attributes->GetNamedItem(HstringWrapper(L"placement").Get(), &editedNode);
											if (FAILED(hr) || !editedNode)
											{
												continue;
											}
											hr = Libray::Util::setNodeStringValue(L"attribution", editedNode.Get(), xml);
											if (SUCCEEDED(hr))
											{
												return setTextFieldHelper(xml, text, i);
											}
										}
									}
								}
							}
						}
					}
					return hr;
				}

				inline HRESULT addActionHelper(_In_ IXmlDocument* xml, _In_ std::wstring const& action, _In_ std::wstring const& arguments)
				{
					using namespace cloudgameZero::Foundation::Warpper;
					ComPtr<IXmlNodeList> nodeList;
					HRESULT hr = xml->GetElementsByTagName(HstringWrapper(L"actions").Get(), &nodeList);
					if (SUCCEEDED(hr))
					{
						UINT32 length;
						hr = nodeList->get_Length(&length);
						if (SUCCEEDED(hr))
						{
							ComPtr<IXmlNode> actionsNode;
							if (length > 0)
							{
								hr = nodeList->Item(0, &actionsNode);
							}
							else
							{
								hr = xml->GetElementsByTagName(HstringWrapper(L"toast").Get(), &nodeList);
								if (SUCCEEDED(hr)) {
									hr = nodeList->get_Length(&length);
									if (SUCCEEDED(hr))
									{
										ComPtr<IXmlNode> toastNode;
										hr = nodeList->Item(0, &toastNode);
										if (SUCCEEDED(hr))
										{
											ComPtr<IXmlElement> toastElement;
											hr = toastNode.As(&toastElement);
											if (SUCCEEDED(hr))
											{
												hr = toastElement->SetAttribute(HstringWrapper(L"template").Get(), HstringWrapper(L"ToastGeneric").Get());
											}
											if (SUCCEEDED(hr))
											{
												hr = toastElement->SetAttribute(HstringWrapper(L"duration").Get(), HstringWrapper(L"long").Get());
											}
											if (SUCCEEDED(hr))
											{
												ComPtr<IXmlElement> actionsElement;
												hr = xml->CreateElement(HstringWrapper(L"actions").Get(), &actionsElement);
												if (SUCCEEDED(hr))
												{
													hr = actionsElement.As(&actionsNode);
													if (SUCCEEDED(hr))
													{
														ComPtr<IXmlNode> appendedChild;
														hr = toastNode->AppendChild(actionsNode.Get(), &appendedChild);
													}
												}
											}
										}
									}
								}
							}
							if (SUCCEEDED(hr))
							{
								ComPtr<IXmlElement> actionElement;
								hr = xml->CreateElement(HstringWrapper(L"action").Get(), &actionElement);
								if (SUCCEEDED(hr))
								{
									hr = actionElement->SetAttribute(HstringWrapper(L"content").Get(), HstringWrapper(action).Get());
								}
								if (SUCCEEDED(hr))
								{
									hr = actionElement->SetAttribute(HstringWrapper(L"arguments").Get(), HstringWrapper(arguments).Get());
								}
								if (SUCCEEDED(hr))
								{
									ComPtr<IXmlNode> actionNode;
									hr = actionElement.As(&actionNode);
									if (SUCCEEDED(hr))
									{
										ComPtr<IXmlNode> appendedChild;
										hr = actionsNode->AppendChild(actionNode.Get(), &appendedChild);
									}
								}
							}
						}
					}
					return hr;
				}

				HRESULT addDurationHelper(_In_ IXmlDocument* xml, _In_ std::wstring const& duration)
				{
					using namespace cloudgameZero::Foundation::Warpper;
					ComPtr<IXmlNodeList> nodeList;
					HRESULT hr = xml->GetElementsByTagName(HstringWrapper(L"toast").Get(), &nodeList);
					if (SUCCEEDED(hr))
					{
						UINT32 length;
						hr = nodeList->get_Length(&length);
						if (SUCCEEDED(hr))
						{
							ComPtr<IXmlNode> toastNode;
							hr = nodeList->Item(0, &toastNode);
							if (SUCCEEDED(hr))
							{
								ComPtr<IXmlElement> toastElement;
								hr = toastNode.As(&toastElement);
								if (SUCCEEDED(hr))
								{
									hr = toastElement->SetAttribute(HstringWrapper(L"duration").Get(), HstringWrapper(duration).Get());
								}
							}
						}
					}
					return hr;
				}

				HRESULT addScenarioHelper(_In_ IXmlDocument* xml, _In_ std::wstring const& scenario)
				{
					using namespace cloudgameZero::Foundation::Warpper;
					ComPtr<IXmlNodeList> nodeList;
					HRESULT hr = xml->GetElementsByTagName(HstringWrapper(L"toast").Get(), &nodeList);
					if (SUCCEEDED(hr))
					{
						UINT32 length;
						hr = nodeList->get_Length(&length);
						if (SUCCEEDED(hr))
						{
							ComPtr<IXmlNode> toastNode;
							hr = nodeList->Item(0, &toastNode);
							if (SUCCEEDED(hr))
							{
								ComPtr<IXmlElement> toastElement;
								hr = toastNode.As(&toastElement);
								if (SUCCEEDED(hr))
								{
									hr = toastElement->SetAttribute(HstringWrapper(L"scenario").Get(), HstringWrapper(scenario).Get());
								}
							}
						}
					}
					return hr;
				}

				ComPtr<IToastNotifier> notifier(_In_ bool* succeded) const
				{
					using namespace cloudgameZero::Foundation::dynamincLibrayFunc::function;
					using namespace cloudgameZero::Foundation::Warpper;
					ComPtr<IToastNotificationManagerStatics> notificationManager;
					ComPtr<IToastNotifier> notifier;
					HRESULT hr = Wrap_GetActivationFactory(HstringWrapper(RuntimeClass_Windows_UI_Notifications_ToastNotificationManager).Get(), &notificationManager);
					if (SUCCEEDED(hr))
					{
						hr = notificationManager->CreateToastNotifierWithId(HstringWrapper(_aumi).Get(), &notifier);
					}
					*succeded = SUCCEEDED(hr);
					return notifier;
				}

				inline void setError(_Out_opt_ Enums::ToastError* error, _In_ Enums::ToastError value)
				{
					if (error) {
						*error = value;
					}
				}

			};

			class PreDefineHandler : public API::Event::ToastPlatformHandler
			{
				virtual void Activated() const
				{
					//在此插入需要执行的指令
				}
				virtual void Activated(int actionIndex) const
				{
					//在此插入需要执行的指令
				}
				virtual void Dismissed(Enums::ToastDismissalReason state) const
				{
					//在此插入需要执行的指令
				}
				virtual void Failed() const
				{
					//在此插入需要执行的指令
				}
			};
		}
	}
}
#else
#error cloudgameFixZero库需要安装boost的堆栈追踪库以及rapidjson库，同时此库仅支持C++20及以上
#endif // _HAS_CXX20
#endif // CLOUDGAME_FIX_ZERO_H