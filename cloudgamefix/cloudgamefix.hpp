﻿/*
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
		__                __                        _____
  _____/ /___  __  ______/ /___ _____ _____ ___  __/__  /  ___  _________
 / ___/ / __ \/ / / / __  / __ `/ __ `/ __ `__ \/ _ \/ /  / _ \/ ___/ __ \
/ /__/ / /_/ / /_/ / /_/ / /_/ / /_/ / / / / / /  __/ /__/  __/ /  / /_/ /
\___/_/\____/\__,_/\__,_/\__, /\__,_/_/ /_/ /_/\___/____/\___/_/   \____/
						/____/
*/

/*
Chinese:
	关于本库：
	此库是提供给网易云游戏Windows系统的C++"简易"程序库，提供了大量工具集用于辅助开发(有没有一种可能，这个头文件有200kb左右)
	此文件封装了WinToast，jthread等库，向派生接口提供支持
	同时提供了日志库用于记录程序运行
	注：
	此库需要安装第三方库，且需要C++20标准支持
	需要配置vcpkg安装
	备注：
	WinToast的许可证声明已在命名空间上面放置，在分发时需保留，否则后果自负
	rapidjson同样!
EN:
	About the library:
	This library is a C++" easy "program library for NetEase Cloud game Windows system, which provides a large number of toolsets to assist development (is there a possibility, this header file is about 200kb)
	This file encapsulates libraries like WinToast, jthread to provide support to the derived interface
	At the same time, a log library is provided to record the execution of the program
	Note:
	This library requires third-party libraries to be installed and is supported by the C++20 standard
	vcpkg installation needs to be configured
	Remarks:
	The license statement for WinToast is placed on the namespace and must be retained when distributing at your own risk
	rapidjson too!
*/
#pragma once
#ifndef CLOUDGAME_FIX_ZERO_H
#define CLOUDGAME_FIX_ZERO_H
#define WIN32_LEAN_AND_MEAN

/*
Chinese:
	决定是否启用错误函数异常，如果禁用。
	每次编译时会发出警告，且出现错误时仅仅只会打印异常信息，甚至可能会导致不明确行为
	并且这样做并不会完全禁用异常，因为在运行期的标准库和来自API的异常仍然可以被激活
EN:
	Decide whether to enable error function exceptions, if disabled.
	A warning is issued every time it is compiled, and if there is an error, it simply prints an exception message, which may even result in unclear behavior
	And doing so doesn't completely disable exceptions, because the standard library and exceptions from the API can still be activated at runtime
*/
#define EnableZeroLibrayExceptions true
#define EnableZeroSAL true
#define DisableVisualStudio2019_Warn_cg false //If you're using Visual Studio 2019, set it to true, otherwise a warning will pop up every time you compile

/*
Chinese:
	关于编译检察域，我们将在编译前进行一些逻辑判断
	首先，我们将一些警告给禁用一下
	随后，我们检查上面的错误函数异常设置以及一些编译设置
	再然后，我们检查是否有安装依赖库，因为本库引用了一些第三方库
	随后，我们还要检查是否是MSVC编译器来编译这个库，因为使用了一些MSVC特有的库以及一些拓展
	最后，我们检查是否达到C++20标准，因为库使用了C++20的特性和库

	除了错误函数异常，其它都会通过静态断言来检查
EN:
	Regarding the compilation inspection domain, we will make some logical judgments before compilation
	First, let's disable some warnings
	Subsequently, we examine the error function exception Settings above as well as some compilation Settings
	Next, we check if any dependencies are installed, as this library references some third-party libraries
	Next, we check that the MSVC compiler is compiling the library, because it uses some MSVC-specific libraries and extensions
	Finally, we check whether the C++20 standard is met, since the library uses C++20 features and libraries
*/

/* The compilation check field begins */

/* Here we disable warnings */
#if defined(CLOUDGAME_FIX_ZERO_DISABLE_WARNING)
#undef CLOUDGAME_FIX_ZERO_DISABLE_WARNING
#endif // if defined(CLOUDGAME_FIX_ZERO_DISABLE_WARNING)
#ifndef CLOUDGAME_FIX_ZERO_DISABLE_WARNING
#define CLOUDGAME_FIX_ZERO_DISABLE_WARNING 4267 4101 26451 26819 33010 26495 6388 4305 4018 4244 6011 26493 26451 26439 5082 28193
#endif //ifndef CLOUDGAME_FIX_ZERO_DISABLE_WARNING

#pragma warning(push)
#pragma warning(disable : CLOUDGAME_FIX_ZERO_DISABLE_WARNING)

#ifndef CLOUDGAMEFIX_WARNING
#define CLOUDGAMEFIX_WARNING(MESSAGE) __pragma("Warning : " __FILE__ "(" _CRT_STRINGIZE(__LINE__) "): " MESSAGE)
#endif

#if !EnableZeroLibrayExceptions
#if EnableZeroSAL
#ifndef NO_ZEROLIBRAY_WARNING
CLOUDGAMEFIX_WARNING("If The Marco \"EnableZeroLibrayExceptions\" Not Enable,\
	This message will always warn you when you are trying to compile this file,\
	To Disable The Warning,Using NO_ZEROLIBRAY_WARNING Macro To Disable It Or Enable The Exception Macro\
")
#endif //ifndef NO_ZEROLIBRAY_WARNING
#endif //EnableZeroSAL
#endif //if !EnableZeroLibrayExceptions
/* Do not remove this row! */

#ifndef __Has_dependent_libfile_cg
#define __Has_dependent_libfile_cg __has_include("rapidjson/writer.h") && __has_include("boost/stacktrace.hpp") && __has_include("curl/curl.h")
#if __Has_dependent_libfile_cg
#define __Result_cg true
#else //__Has_dependent_libfile_cg
#define __Result_cg false
#endif //!__Has_dependent_libfile_cg
#endif //__Has_dependent_libfile_cg

static_assert(__Result_cg, "If You Want Compile This Libray,Please Install Dependent Libray: rapidjson & boost_stacktrace & libcurl");

#if !__has_include("cloudgamefix.cpp")
#ifndef __NO_CLODGAMEFIX_CPP_FILE
CLOUDGAMEFIX_WARNING("Although the total header file provides many functions, without an accompanying cpp file, parts of the interface may not be available (compilation fails).")
#endif
#endif

#if defined(_MSC_VER) // Using MSVC || 使用MSVC编译

#if _MSC_VER >= 1937 // Visual Studio 2022
#define __Is_MSVC_And_Support_cloudgame_juzi true
#else // Maybe Not Visual Studio 2022 || 可能不是Visual Studio 2022
#if _MSC_VER >= 1928 // Is Visual Studio 2019 || 使用了Visual Studio 2019
#if !DisableVisualStudio2019_Warn_cg
CLOUDGAMEFIX_WARNING("You're tring To Using Visual Studio 2019 To Compile This Project,But Visual Studio 2022 Are More Better")
#endif //DisableVisualStudio2019_Warn_cg
#define __Is_MSVC_And_Support true
#else // Visual Studio 2017 or lower
#define __Has_MSVC_And_Support false
#endif // !_MSC_VER >= 1928
#endif // !Visual Studio 2022
#else
#define __Is_MSVC_And_Support false
#endif // Not Using MSVC || 没有使用MSVC编译

static_assert(__Is_MSVC_And_Support_cloudgame_juzi, 
	"This Libray Need MSVC Compiler To Compile,"
	"Because This Libray Using Some Extended From MSVC And You Must Using Visual Studio 2019 or later"
);

#ifndef __Has_reached_cpp20_standard_cg
#if _MSVC_LANG > 201703L //C++17
#define __Has_reached_cpp20_standard_cg true
#else
#define __Has_reached_cpp20_standard_cg false
#endif
#endif

static_assert(__Has_reached_cpp20_standard_cg, "You Must Using C++20 Standard To Compile This Libray");

/* The compilation check field is over */

#define MakeCloudgameInterface(X) struct __declspec(uuid(X)) __declspec(novtable)

/* Start building the namespace framework */
namespace cloudgameZero
{
	#if !__Has_reached_cpp20_standard_cg
	void if_you_see_this_func_because_the_cxx20_is_must()
	{

	}
	#endif

	class ThreadPool;

	namespace Infomation
	{
		static const wchar_t* APPNAME = L"cloudgameFixZero";
		static const wchar_t* AUMI = L"cloudgameFixZero";

		namespace Secutriy
		{
		}
		
		namespace Event
		{
		}

		template<class Ty, class Other = Ty>
		constexpr Ty __builtin_exchange(Ty& _Val, Other&& _New_val) noexcept
		{
			Ty _Old_val = static_cast<Ty&&>(_Val);
			_Val = static_cast<Other&&>(_New_val);
			return _Old_val;
		}
	}
	namespace coro
	{
	}
	namespace Foundation
	{
		template <typename Ty>
		class cloudgamePtr
		{
		public:
			explicit cloudgamePtr() = default;

			cloudgamePtr(decltype(nullptr)) : ptr(nullptr){}

			template<class U>
			cloudgamePtr(U* other) : ptr(other){}

			cloudgamePtr(cloudgamePtr&& other) : ptr(nullptr)
			{
				if (this != reinterpret_cast<cloudgamePtr*>(&reinterpret_cast<unsigned char&>(other)))
					swap(other);
			}

			template<class U>
			cloudgamePtr(cloudgamePtr<U>&& other)
			{
				ptr = Infomation::__builtin_exchange(other.ptr, nullptr);
			}

			~cloudgamePtr()
			{
				release();
			}

			cloudgamePtr& operator=(decltype(__nullptr))
			{
				release();
				return *this;
			}

			cloudgamePtr& operator=(cloudgamePtr&& other)
			{
				cloudgamePtr(static_cast<cloudgamePtr&>(other)).swap(*this);
				return *this;
			}

			template<class U>
			cloudgamePtr& operator=(cloudgamePtr<U>&& other)
			{
				cloudgamePtr(static_cast<cloudgamePtr<U>&&>(other)).swap(*this);
				return *this;
			}

			inline void swap(cloudgamePtr&& r)
			{
				ptr = Infomation::__builtin_exchange(r.ptr, nullptr);
			}

			inline operator bool()
			{
				return get() != nullptr;
			}

			inline Ty* get()
			{
				return ptr;
			}

			inline Ty* operator->()
			{
				return ptr;
			}

			inline void reset()
			{
				return release();
			}

			inline void release()
			{
				if (ptr != nullptr)
					delete ptr;
				ptr = nullptr;
			}

		private:
			Ty* ptr = nullptr;
		};

		namespace dynamincLibrayFunc
		{
			namespace function
			{
				namespace unstable
				{
				}
			}
		}
		namespace Warpper
		{
		}
		namespace Tool
		{
			inline namespace function
			{
			}
			inline namespace Libteral
			{
				namespace structs
				{
				}
			}
			inline namespace WindowsZero
			{
				inline namespace TaskBar
				{
				}
				inline namespace Data
				{
				}
				inline namespace Event
				{
				}
			}
		}
	}
	namespace Interface
	{
		namespace sigmaInterface
		{
			namespace Implement
			{
			}
			inline namespace guid
			{
			}
		}
	}
	namespace ToastPlatform
	{
		namespace API
		{
			__interface ToastPlatformHandler;
			namespace Libray
			{
				namespace Util
				{
				}
			}
			class ToastTemplate;
		}
		namespace Enums
		{
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
	}
	namespace Experiment
	{
	}
}
/* If you compile with C++17 or below, the namespace will only show frames .*/

/* Windows SDK And C++ Standard Libray Files | Windows SDK默认提供的库以及C++20提供的标准库 */
#include <map>
#include <set>
#include <io.h>
#include <span>
#include <mutex>
#include <ctime>
#include <regex>
#include <array>
#include <queue>
#include <ranges>
#include <format>
#include <string>
#include <thread>
#include <future>
#include <vector>
#include <chrono>
#include <atomic>
#include <conio.h>
#include <sstream>
#include <roapi.h>
#include <cassert>
#include <variant>
#include <fstream>
#include <Psapi.h>
#include <atlstr.h>
#include <ShlObj.h>
#include <aclapi.h>
#include <iostream>
#include <windows.h>
#include <algorithm>
#include <stdexcept>
#include <coroutine>
#include <strsafe.h>
#include <shellapi.h>
#include <winternl.h>
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
#include <curl/curl.h>
#include <rapidjson/writer.h>
#include <boost/stacktrace.hpp>
#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/prettywriter.h>
#pragma comment(lib, "user32")
#pragma comment(lib, "shlwapi")
#pragma comment(lib, "ws2_32")

#ifndef CLOUDGAMEFIX_ASSERT
#define CLOUDGAMEFIX_ASSERT(x) assert(x)
#endif

/*
vcpkg:
	dynamic:
		rapidjson -> vcpkg install rapidjson:x64-windows
		boost-stacktrace -> vcpkg install boost-stacktrace:x64-windows
		curl -> vcpkg install curl:x64-windows
	static:
		rapidjson -> vcpkg install rapidjson:x64-windows-static
		boost-stacktrace -> vcpkg install boost-stacktrace:x64-windows-static
		curl -> vcpkg install curl:x64-windows-static

*/

using namespace Microsoft::WRL;
using namespace ABI::Windows::Data::Xml::Dom;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::UI::Notifications;
using namespace Windows::Foundation;

/**
 * 此库的所有注释文档和文档将采用英文来标记！
 * All comments and documentation for this library will be marked up in English!
 */

#if __Has_reached_cpp20_standard_cg
namespace cloudgameZero
{
	template<typename ret, typename... type>
	using delegate = std::function<ret(type...)>;

	template<typename T>
	static std::basic_string<T> format(std::basic_string<T> fmt, ...)
	{
		int _Result = -1;
		std::size_t _BufferCount = 512;
		std::basic_string<T> ret(_BufferCount, std::is_same_v<T, char> ? '0' : L'0');
		va_list _ArgList;
		__crt_va_start(_ArgList, fmt.c_str());
		if constexpr (std::is_same_v<T, char>)
		{
			_Result = _vsprintf_s_l(&ret[0], _BufferCount, fmt.c_str(), NULL, _ArgList);
		}
		else if constexpr (std::is_same_v<T, wchar_t>)
		{
			_Result = _vswprintf_s_l(&ret[0], _BufferCount, fmt.c_str(), NULL, _ArgList);
		}
		__crt_va_end(_ArgList);
		ret.resize(_Result < 0 ? -1 : _Result);
		return ret;
	}


	/*
	* The Infomation namespace stores basic information and variables of the library as well as some functions
	* These are referenced by functions and objects of the library, so this namespace acts as a basic global variable declaration
	*/
	namespace Infomation
	{
		static const HKEY HKCR = ((HKEY)(ULONG_PTR)((LONG)0x80000000));
		static const HKEY HKCU = ((HKEY)(ULONG_PTR)((LONG)0x80000001));
		static const HKEY HKLM = ((HKEY)(ULONG_PTR)((LONG)0x80000002));
		static const HKEY HKU  = ((HKEY)(ULONG_PTR)((LONG)0x80000003));
		static const HKEY HKCC = ((HKEY)(ULONG_PTR)((LONG)0x80000005));
		constexpr std::string_view authorConf = "juzi xiao";
		constexpr std::string_view versionConf = "cloudgamefix 2.10 release zero public sigma | The C++ Edition";
		constexpr std::string_view _USER_cloudpc = "netease";
		
		//It is used to handle the basic security functions of the later library
		namespace Secutriy
		{
			static std::mutex mutexLock;
			constexpr std::string_view urlLinkRegex = R"(^(https:\/\/|http:\/\/|ftp:\/\/).+(\/)?.+)";
			constexpr std::string_view lnkPathRegex = R"(^([a-z]|[A-Z]){1}:((\\\\)|(\\/)|(\\\\)).+(\.lnk)$)";
			constexpr std::string_view guidRe = R"(^\{([A-Z]|[0-9]){8}-([A-Z]|[0-9]){4}-([A-Z]|[0-9]){4}-([A-Z]|[0-9]){4}-([A-Z]|[0-9]){12}\}$)";
			constexpr std::string_view guidReSec = R"(^([A-Z]|[0-9]){8}-([A-Z]|[0-9]){4}-([A-Z]|[0-9]){4}-([A-Z]|[0-9]){4}-([A-Z]|[0-9]){12}$)";
		}
		
		/* Three callback temporary functions for curl */
		constexpr auto curlResponseCallBack = 
			[](char* ptr, size_t size, size_t nmemb, void* userdata)
			{
				((std::string*)userdata)->append(ptr, size * nmemb);
				return size * nmemb;
			};
		
		constexpr auto curlFileCallback = 
			[](char* ptr, size_t size, size_t nmemb, void* userdata) noexcept -> size_t
			{
				((std::fstream*)userdata)->write(ptr, size * nmemb);
				return size * nmemb;
			};

		constexpr auto progressCallback = [](void* progress_data, double t, double d, double ultotal, double ulnow)
			{
				static char bar[120];
				int i = 0;
				if (t) {
					i = static_cast<int>(d * 100.0 / t);
				}
				printf("Download Progress -> %d%%\r", i);
				i++;
				return 0;
			};
		
		static std::mutex curlLock;
		
		namespace Event
		{
			static std::unordered_map<std::string, std::unique_ptr<ThreadPool>> pools;
			static std::unordered_map<std::string, std::unordered_map<int, delegate<void,void*>>> subscribers;
			static std::mutex mutex;
		}
		
		/* Used to create a default log profile */
		constexpr std::string_view logconfig_json = R"(
		{
			"logFormatTime": "[%Ec %A]",
			"outToTerminal": {
				"Enable": true,
				"render": true,
				"showUser": true,
				"rootLogger": {
					"level": "trace",
					"ostream": "std::clog",
					"wostream": "std::wclog",
					"cleanBuffer": {
						"clean": true,
						"times": 10
					}
				}
			},
			"logToFile": {
				"Enable": true,
				"Dictionary": "${APPDATA}\\cloudgamefixZero\\logs",
				"File": {
					"format": true,
					"TimeFormat": "[%Y %m %d]",
					"filename": "${format}CloudGameFixZero.log"
				},
				"append": false
			},
			"EnableThreadSecurity": true,
			"Save":true
		})";

		template<typename T>
		concept number_string = !std::is_integral_v<T> && !std::is_enum_v<T>;

		template<typename T>
		concept stdexcept_ref = std::is_base_of_v<std::exception, T>&& std::is_class_v<T>;

		static const std::string_view Shell_TrayWnd = "Shell_TrayWnd";
		static const std::string_view Shell_SecondaryTrayWnd = "Shell_SecondaryTrayWnd";
		static const std::string_view DesktopMgr64 = "VirDestopWindow";
		static const std::string_view DesktopTaskBar64 = "VirTrayWindow";

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

		enum level
		{
			Reserved,
			Trace,
			Debug,
			Info,
			Warn,
			Error,
			Fatal
		};

		static const std::map<cloudgameZero::Infomation::level, std::string> levels = {
			{Reserved,	"ERROR"},
			{Trace,		"TRACE"},
			{Debug,		"DEBUG"},
			{Info,		"INFO"},
			{Warn,		"WARN"},
			{Error,		"ERROR"},
			{Fatal,		"FATAL"}
		};

		static const std::locale chs("chs");
		static const std::locale _Clocale("C");

		static std::map<std::string,std::set<std::string>> regMark;

		static const std::atomic_bool isCloudPC = !std::filesystem::exists("E:\\Builds");

		constexpr std::string_view wuauserv_str = "wuauserv";

		static bool isSupportingModernFeatures();

		static bool isWin10AnniversaryOrHigher();

		template<typename Ty>
		concept __cginterface = std::is_class_v<Ty> && std::is_base_of_v<IUnknown,Ty>;

		extern std::unordered_map<std::string, delegate<void*>> factoryMapping;
	}

	using logLevel = Infomation::level;

	/* A separate handle provided by cloudgameZero to implement the logging library functionality */
	static const HANDLE CONSOLE_OUTPUT_HANDLE = GetStdHandle(STD_OUTPUT_HANDLE);

	/* A simple function provided for a specific class of output log content, while identifying the current publication mode status.*/
	#ifdef NDEBUG
	
	constexpr bool IS_DEBUG = false;

	/**
	* \brief This part was written on 2023/7/23.
	* \brief Warning : If you want to display additional log information, use Debug release mode instead of Realease
	*/
	template<typename Ty>	
	inline void PrintError(Ty msg) {}
	
	/**
	* \brief This part was written on 2023/7/23.
	* \brief Warning : If you want to display additional log information, use Debug release mode instead of Realease
	*/
	template<typename Ty>
	void inline DEBUG_MESSAGE(Ty str) {}

	#else
	
	constexpr bool IS_DEBUG = true;

	/**
	* \brief This section was written on 2023/7/23.
	* \brief Print debug information to the console and clear the buffer.
	* \brief notes:
	* \brief This function differs from DEBUG_MESSAGE in that it uses std::wcerr.
	* \brief Compilation will pass if an object exported by std::wostream accepts the data type of 'msg'; otherwise, it will fail.
	* \brief -----------------------The following section was written on 2023/8/5-------------------------------
	* \brief This function checks the stream state after printing. If the stream is corrupted, it will temporarily clear the stream data, set the locale to 'chs', and then reprint the text.
	* \brief If Foundation::Tool's string conversion functions are used, it may trigger stream corruption, causing std::wcout to attempt to repair and output the string again.
	* \brief -----------------------The following section was written on 2023/9/14-------------------------------
	* \brief If the function is passed a std::exception, it will directly print the string content from LibError.
	* \brief -----------------------The following section was written on 2023/9/20-------------------------------
	* \brief This function does not check the state of the stream after printing
	* \tparam msg : A generic parameter.
	*/
	template<typename Ty>
	void PrintError(Ty msg)
	{
		std::unique_lock<std::mutex> lock(Infomation::Secutriy::mutexLock,std::defer_lock);
		if(lock.try_lock())
		{
			if constexpr (std::is_same_v<Ty, std::exception>) 
			{
				std::exception& err = msg;
				std::wcerr << err.what();
				std::wcerr.imbue(std::locale("C"));
				std::wcerr << std::endl;
			}
			else if constexpr (std::is_same_v<Ty, std::string>) 
			{
				std::string& err = msg;
				std::wcerr.imbue(std::locale("chs"));
				std::wcerr << err.c_str();
				std::wcerr.imbue(std::locale("C"));
				std::wcerr << std::endl;
			}
			else if constexpr (std::is_same_v<Ty, std::string_view>)
			{
				std::wcerr.imbue(std::locale("chs"));
				std::wcerr << msg.data();
				std::wcerr.imbue(std::locale("C"));
				std::wcerr << std::endl;
			}
			else 
			{
				std::wcerr << msg;
				std::wcerr.imbue(std::locale("C"));
				std::wcerr << std::endl;
			}
		}
		else 
		{
			throw std::exception("Can't Enable Thread Lock");
		}
	}

	/**
	* \brief This section was written on 2023/7/23
	* \brief prints debug information to the console and clears the buffer.
	* \brief notes
	* \brief The difference between this function and PrintError, which uses objects, is that it uses std::wcout
	* \brief std::wostream compiles if the exported object accepts the data type msg, otherwise it fails
	* \brief -----------------------The following section was written on 2023/8/5-------------------------------
	* \brief This function checks the state of the stream after printing, and if the stream is corrupted, it temporarily clears the stream data, sets the locale to chs, and reprints the text
	* \brief If Foundation::Tool's string conversion function is used, it may corrupt the trigger stream causing std::wcout to try to fix it and output the string again.
	* \brief -----------------------The following section was written on 2023/9/20-------------------------------
	* \brief This function does not check the state of the stream after printing
	* 
	* \tparam str : A generic argument
	*/
	template<class Ty>
	void DEBUG_MESSAGE(Ty str)
	{
		std::unique_lock<std::mutex> lock(Infomation::Secutriy::mutexLock);
		if constexpr (std::is_same_v<Ty, std::string>)
		{
			std::wclog.imbue(std::locale("chs"));
			std::wclog << str.c_str();
			std::wclog.imbue(std::locale("C"));
			std::wclog << std::endl;
		}
		else if constexpr (std::is_same_v<Ty, std::string_view>)
		{
			std::wclog.imbue(std::locale("chs"));
			std::wclog << str.data();
			std::wclog.imbue(std::locale("C"));
			std::wclog << std::endl;
		}
		else
		{
			std::wclog << str;
			std::wclog.imbue(std::locale("C"));
			std::wclog << std::endl;
		}
	}
	#endif //NDEBUG

	/**
	* \brief This section was written on 2023/9/24.
	* \brief Send exceptions raised by the library to this location.
	* \brief Comments:
	* \brief 'error' must be derived from std::exception, so most exceptions in this library use standard library exceptions.
	* \brief And only objects are allowed to be passed.
	*
	* \tparam error : The error to be thrown.
	*/
	template<Infomation::stdexcept_ref T>
	static void LibError(T error)
	{
	#if EnableZeroSAL
	static_assert(EnableZeroLibrayExceptions, "Exception detection is disabled. Please set the EnableZeroSAL macro to false to compile this code, or library functionality may be compromised.");
	/* Here, we use a static_assert to prevent users from disabling exceptions since library functions rely on them. */
	#endif
	#if EnableZeroLibrayExceptions
		throw error;
	#else
		std::exception err(error);
		PrintError(err);
	#endif
	}


	/**
	* \brief This section was written on 2023/9/24.
	* \brief Converts a character sequence to an integer.
	*
	* \tparam string : The character sequence to be converted.
	* \param idx : The index value of the first unconverted character.
	* \param base : The numeric base to be used.
	* \return Integer
	*/
	template<Infomation::number_string T>
	static inline int strToInt(const T& string, size_t* idx = nullptr, int base = 10)
	{
		static_assert(!std::is_integral_v<T>, "Using integers is not supported because this function is designed to convert strings to integers.");
		/* The template will determine the underlying data type forwarded to std::stoi */
		try
		{
			if (string[0] < '0' || string[0] > '9')
			{
				LibError(std::invalid_argument("To ensure proper parsing, please make sure the first character is a digit."));
			}
			int result = std::stoi(/* The constructor will be called here, and the version to use is selected through overloading. */ string, /* The remaining parameters are forwarded to the function as usual. */ idx, base);
			return result;
		}
		catch (std::exception& except)
		{
			// If an exception occurs, it's caught by reference here and then forwarded to the LibError function.
			LibError(except);
		}
		return -1;
	}

	/**
	 * \brief This section was written on 2023/9/24.
	 * \brief Converts a character sequence to an long
	 * 
	 * \tparam string : The character sequence to be converted.
	 * \param idx : The index value of the first unconverted character.
	 * \param base : The numeric base to be used.
	 * \return Long
	 */
	template<Infomation::number_string T>
	static inline long strToLong(const T string, size_t* idx = nullptr, int base = 10)
	{
		static_assert(!std::is_integral_v<T>, "Using integers is not supported because this function is designed to convert strings to integers.");
		/* The template will determine the underlying data type forwarded to std::stoi */
		try
		{
			if (string[0] < '0' || string[0] > '9')
			{
				LibError(std::invalid_argument("To ensure proper parsing, please make sure the first character is a digit."));
			}
			long result = std::stol(/* The constructor will be called here, and the version to use is selected through overloading. */ string, /* The remaining parameters are forwarded to the function as usual. */ idx, base);
			return result;
		}
		catch (std::exception& except)
		{
			// If an exception occurs, it's caught by reference here and then forwarded to the LibError function.
			LibError(except);
		}
		return -1;
	}

	/**
	 * \brief This section was written on 2023/9/24.
	 * \brief Converts a character sequence to an long long.
	 *
	 * \tparam string : The character sequence to be converted.
	 * \param idx : The index value of the first unconverted character.
	 * \param base : The numeric base to be used.
	 * \return Long Long
	 */
	template<Infomation::number_string T>
	static inline long long strToLongLong(const T string, size_t* idx = nullptr, int base = 10)
	{
		static_assert(!std::is_integral_v<T>, "Not supported for integers as this function is intended for converting strings to integers.");
		//The template will determine the underlying data type passed to std::stoi
		try
		{
			if (string[0] < '0' || string[0] > '9')
			{
				LibError(std::invalid_argument("To ensure proper parsing, please make sure the first character is a digit."));
			}
			long long result = std::stoll(
				/* Passed to the constructor here, selecting the version through overloading */
				string,
				/* The remaining parameters are forwarded to the function */idx, base);
			return result;
		}
		catch (std::exception& exception)
		{
			// If an exception occurs, it is caught by reference and then forwarded to the LibError function.
			LibError(exception);
		}
		return -1;
	}

	/**
	 * \brief A simple thread pool class for managing a group of worker threads to execute tasks in parallel.
	 *
	 * ThreadPool allows you to submit tasks and execute them asynchronously using a pool of threads. It maintains a
	 * thread queue, with each thread looping to perform tasks until the thread pool is destroyed.
	 *
	 * \note This thread pool class does not support thread cancellation or pausing. It is suitable for scenarios
	 * where parallel execution of tasks is needed.
	 *
	 * \param numThreads The number of worker threads to initialize the thread pool with.
	*/
	class ThreadPool
	{
	public:

	   /**
	   * \brief This section was written on 2023/9/10
	   * \brief Construct a thread pool object and initialize the specified number of worker threads.
	   *
	   * \param numThreads The number of worker threads to create.
	   */
		ThreadPool(int numThreads) : stop(false)
		{
			for (int i = 0; i < numThreads; i++)
			{
				this->Threads.emplace_back([this]
					{
						while (true)
						{
							std::unique_lock<std::mutex> lock(this->mutex);
							cond.wait(lock, [this]
								{
									return !tasks.empty() || stop;
								});
							if (stop)
							{
								return;
							}
							delegate<void> task(std::move(tasks.front()));
							tasks.pop();
							lock.unlock();
							task();
						}
					}
				);
			}
		}

		/**
		* \brief This section was written on 2023/9/10
		* \brief Destructor that destroys the thread pool object and waits for all threads to finish their tasks.
		*
		* The destructor sets the stop flag, notifies all worker threads to stop, and waits for them to complete their
		* current tasks and exit.
		*/
		~ThreadPool()
		{
			{
				std::unique_lock<std::mutex> lock(mutex);
				stop = true;
			}
			cond.notify_all();
			for (auto& t : Threads)
			{
				t.join();
			}
		}

		/**
		* \brief Submit a task to the thread pool and wait for a worker thread to execute it.
		*
		* \tparam Fn The type of the callable object, usually a function or lambda.
		* \tparam Args The types of the arguments.
		* \param Func The callable object to execute.
		* \param args The arguments for the callable object.
		*
		* After submitting a task, one of the worker threads in the pool will asynchronously execute the task.
		*/
		template<typename Fn, typename... Args>
		void submitTask(Fn&& Func, Args&&... args)
		{
			std::function<void()> Task = std::bind(std::forward<Fn>(Func), std::forward<Args>(args)...);
			{
				std::unique_lock<std::mutex> lock(mutex);
				this->tasks.emplace(std::move(Task));
			}
			cond.notify_one();
		}

	private:
		std::vector<std::jthread> Threads;
		std::queue<std::function<void()>> tasks;
		std::mutex mutex;
		std::condition_variable cond;
		std::atomic_bool stop;
	};

	static std::string formatWindowsErrorMessage(DWORD LastError)
	{
		std::string data;
		data.resize(256);
		FormatMessageA(
			FORMAT_MESSAGE_FROM_SYSTEM,
			NULL,
			LastError,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			&data[0],
			256,
			NULL
		);
		data = std::regex_replace(data, std::regex("\n"), "");
		return data;
	}

	/* 一个支持异步和线程安全的基本事件总线系统 */
	class EventBus
	{
	public:
		EventBus() = default;

		/**
		* \brief This section was written on 2023/10/1
		* \brief Constructor for subscribing to an event with a callback function.
		* \param eventName The name of the event.
		* \param func The callback function without additional data.
		* 
		*/
		EventBus(const std::string& eventName, delegate<void> func)
		{
			subscribe(eventName, func);
		}

		/**
		* \brief This section was written on 2023/10/1
	    * \brief Constructor for subscribing to an event with a callback function that takes additional data.
	    * \param eventName The name of the event.
	    * \param func The callback function with additional data.
	    */
		EventBus(const std::string& eventName, delegate<void, void*> func)
		{
			subscribe(eventName, func);
		}

		/*
		* \brief This section was written on 2023/10/5
		* \brief Create an event thread queue. The thread pool is expanded if the number of subscribers exceeds the pool's size.
		* \param eventName The name of the event.
		* \param size The size of the event queue.
		*/
		void createEvent(const std::string& eventName,size_t& size)
		{
			using namespace Infomation::Event;
			auto itr = subscribers.find(eventName);
			if (itr == subscribers.end())
			{
				// Create a new thread queue to execute the event if it's a new event.
				pools[eventName] = std::make_unique<ThreadPool>(static_cast<int>(size));
			}
			else
			{
				// If modifying the event size, check the number of subscribers. If it exceeds 'size,' expand the queue.
				if (subscribers[eventName].size() >= size)
				{
					// Release the existing thread pool.
					pools[eventName].release();
					while (subscribers[eventName].size() <= size)
					{
						size++; //Increase the queue capacity.
					}
					size *= 2;
					//Update the 'size' until it's less than the number of subscribers and create a new thread pool.
					pools[eventName] = std::make_unique<ThreadPool>(static_cast<int>(size));
				}
			}
		}

		/**
		* \brief This section was written on 2023/9/25
		* \brief Send an event to the system. If the event is present in the subscription list, execute the functions stored in the list asynchronously.
		* \param eventName The name of the event.
		* \param res A pointer to additional information (optional).
		*/
		void post(const std::string& eventName,void* res = nullptr)
		{
			using namespace Infomation::Event;
			std::unique_lock<std::mutex> lock(mutex);
			auto itr = subscribers.find(eventName);
			if (itr != subscribers.end())
			{
				thread = std::jthread([&]()
					{
						for (auto& fun : subscribers[eventName])
						{
							pools[eventName]->submitTask(fun.second,res);
						}
					});
				std::this_thread::sleep_for(std::chrono::milliseconds(1));
				thread.join();
			}
		}

		/**
		 * \brief This section was written on 2023/9/25
		 * \brief Subscribe to an event without additional data.
		 * \param eventName The name of the event.
		 * \param callback The callback function with the signature: void().
		 * \return The subscription ID.
		 */
		inline int subscribe(const std::string& eventName,delegate<void> callback)
		{
			return subscribe(eventName,
				[callback](void* data) 
				{
					return callback(); 
				}
			);
		}

		/**
		 * \brief 用于订阅事件并添加到事件队列.
		 *
		 * \param eventName 事件名
		 * \param callback 回调函数，函数签名为：void(void*)
		 * \return 返回存储id，如果不需要取消订阅，请忽略
		 */
		int subscribe(const std::string& eventName, delegate<void,void*> callback)
		{
			using namespace Infomation::Event;
			std::unique_lock lock(mutex);
			if (!callback) 
			{
				LibError(std::invalid_argument("Callback Can't Be null"));
			}
			size_t size = 15;
			createEvent(eventName, size);
			int id = static_cast<int>(subscribers[eventName].size() + 1);
			subscribers[eventName][id] = callback;
			return id;
		}

		/**
		 * \brief 去除某个订阅事件的id对应的Handler.
		 *
		 * \param eventName 事件名
		 * \param id 从subscribe返回
		 */
		void unsubscribe(const std::string& eventName, UINT id)
		{
			using namespace Infomation::Event;
			std::unique_lock lock(mutex);
			auto itr = subscribers.find(eventName);
			itr->second.erase(id);
		}

		/**
		 * \brief 此部分写于2023/10/2
		 * \brief 清除全部订阅者函数信息.
		 * 
		 * \param eventName 事件名
		 */
		inline void clearEventSubscribe(const std::string& eventName)
		{
			auto find = Infomation::Event::subscribers.find(eventName);
			if (find != Infomation::Event::subscribers.end())
			{
				find->second.clear();
			}
		}

	private:
		std::jthread thread{};
		HANDLE threadHandle{};
	};

	/* 基于jthread和Windows API封装的类 */
	class ThreadPlatform
	{
	public:
		using native_handle_type = std::thread::native_handle_type;

		explicit ThreadPlatform() = default;

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
			std::function<void()> func = std::bind(std::forward<Fn>(f), std::forward<Args>(args)...);
			this->func = [func]()
				{
					func();
				};
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
			if (this->_Start && !this->_suspend) 
			{
				SuspendThread(this->threadManager.native_handle());
			}
			else
			{
				if (!this->_Start)
				{
					PrintError("The thread did not start, is this intentional?");
				}
				else 
				{
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

	static DWORD getThreadId(std::thread& thread)
	{
		std::stringstream ss;
		ss << thread.get_id() << "\n";
		try
		{
			DWORD ID = static_cast<DWORD>(strToInt(ss.str()));
			return ID;
		}
		catch (...)
		{
			return 0;
		}
	}

	static DWORD getThreadId(std::jthread& thread)
	{
		std::stringstream ss;
		ss << thread.get_id() << "\n";
		try
		{
			DWORD ID = static_cast<DWORD>(strToInt(ss.str()));
			return ID;
		}
		catch (...)
		{
			return 0;
		}
	}

	/* 用于对C++20协程的简单支持.*/
	namespace coro
	{
		typedef void* Void;

		template<typename T>
		class coroutine
		{
		public:
			static_assert(!std::is_const_v<T>, "The C++ Standard forbids containers of const elements because allocator<const T> is ill-formed.");
			static_assert(!std::is_function_v<T>, "The C++ Standard forbids allocators for function element because of [allocator.requirements].");
			static_assert(!std::is_reference_v<T>, "The C++ Standard forbids allocators for reference elements because of [allocator.requirements].");

			struct promise_type
			{
				T value;

				auto get_return_object()
				{
					return coroutine{ handle::from_promise(*this) };
				}
				
				auto initial_suspend()
				{
					return std::suspend_always{};
				}
				
				auto final_suspend() noexcept
				{
					return std::suspend_always{};
				}
				
				void unhandled_exception()
				{
					return std::terminate();
				}
				
				auto yield_value(T value)
				{
					this->value = value;
					return std::suspend_always{};
				}

				inline void return_value(T value)
				{
					this->value = value;
				}
			};
			
			using handle = std::coroutine_handle<promise_type>;

			coroutine(coroutine&& other) noexcept
			{
				if (this == std::addressof(other))
				{
					return;
				}
				this->hCoroutine = std::exchange(other.hCoroutine, nullptr);
			}
			
			~coroutine()
			{
				if (hCoroutine)
				{
					hCoroutine.destroy();
				}
			}
			
			inline auto Get() noexcept
			{
				return hCoroutine;
			}

			inline void resume()
			{
				return hCoroutine.resume();
			}
		
			T GetValue() const noexcept
			{
				return hCoroutine.promise().value;
			}

			inline bool move()
			{
				this->hCoroutine.resume();
				return hCoroutine.done();
			}

		private:
			std::coroutine_handle<promise_type> hCoroutine;
			coroutine(std::coroutine_handle<promise_type> Handle) :hCoroutine(Handle) {}
		};

		template<typename T>
		class awaitable
		{
			static_assert(!std::is_const_v<T>, "The C++ Standard forbids containers of const elements because allocator<const T> is ill-formed.");
			static_assert(!std::is_function_v<T>, "The C++ Standard forbids allocators for function element because of [allocator.requirements].");
			static_assert(!std::is_reference_v<T>, "The C++ Standard forbids allocators for reference elements because of [allocator.requirements].");

			struct promise_type
			{
				auto get_return_object()
				{
					return awaitable{ std::coroutine_handle<promise_type>::from_promise(*this) };
				}

				auto initial_suspend()
				{
					return std::suspend_always{};
				}

				auto final_suspend() noexcept
				{
					return std::suspend_always{};
				}

				void unhandled_exception()
				{
					return std::terminate();
				}

				void return_value(T data)
				{
					this->data = data;
				}

				void yield_value(T data)
				{
					this->data = data;
				}
				
				T data;
			};

			bool await_ready()
			{
				return false;
			}

			void await_suspend(std::coroutine_handle<> h)
			{
				h.resume();
			}

			void await_resume()
			{
				return;
			}

			T getValue()
			{
				return hCoroutine.promise().data;
			}
		private:
			std::coroutine_handle<promise_type> hCoroutine;
			awaitable(std::coroutine_handle<promise_type> Handle) :hCoroutine(Handle) {}
		};
	}

	enum class InstallHookType : INT
	{
		CALLWNDPROC = WH_CALLWNDPROC,
		CALLWNDPROCRET = WH_CALLWNDPROCRET,
		CBT = WH_CBT,
		__DEBUG = WH_DEBUG,
		FOREGROUNDIDLE = WH_FOREGROUNDIDLE,
		GETMESSAGE = WH_GETMESSAGE,
		JOURNALPLAYBACK = WH_JOURNALPLAYBACK,
		JOURNALRECORD = WH_JOURNALRECORD,
		KEYBOARD = WH_KEYBOARD,
		KEYBORAD_LL = WH_KEYBOARD_LL,
		MOUSE = WH_MOUSE,
		MOUSE_LL = WH_MOUSE_LL,
		MSGFILTER = WH_MSGFILTER,
		SHELL = WH_MSGFILTER,
		SYSMSGFILTER = WH_SYSMSGFILTER
	};

	/* cloudgamefixZero的基础库命名空间，存放了程序需要的函数和常量，是最基础的依赖实现部分 */
	namespace Foundation
	{
		template<typename Ty, typename ... Args>
		cloudgamePtr<Ty> make(Args... args)
		{
			return cloudgamePtr<Ty>(new Ty(std::forward<Ty>(args...)));
		}

		/* 存储关于动态链接库的函数和常量 */
		namespace dynamincLibrayFunc
		{
			/* 预定义函数句柄 */
			static const HINSTANCE NTDLL = GetModuleHandleW(L"NTDLL.dll");
			static const HINSTANCE USER32 = LoadLibraryW(L"user32.dll");
			static const HINSTANCE KERNEL = LoadLibraryW(L"kernel32.dll");
			static const HINSTANCE COMBASE = LoadLibraryW(L"ComBase.dll");

			#define WINUEAPI WINAPI	// 预定义宏
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
				static_assert(!std::is_integral_v<Fn> && std::is_pointer_v<Fn> && !std::is_class_v<Fn>,"所以你是非要传个不合法的参数吗？");
				if (!handle)
				{
					return E_INVALIDARG;
				}
				else 
				{
					pointer = reinterpret_cast<Fn>(GetProcAddress(handle, FuncName));
					if (pointer != nullptr)
					{
						return S_OK;
					}
					else
					{
						LibError(std::runtime_error("Can't load proc Address，Are you sure that the handles and functions are correct?"));
						return E_FAIL;
					}
				}
			}

			/**
			 * \brief 此部分写于2023/9/12
			 * \brief 一个模板函数，用于将动态链接库的函数导出并绑定到函数对象.
			 * \brief 批注：
			 * \brief 此函数是loadFunFromLib的重载版本，此版本支持std::function
			 * \brief cloudgameZero命名空间下也提供了delegate引用，效果一致
			 * \param handle 动态链接库的句柄
			 * \param FuncName 函数名称
			 * \param pointer 函数对象，可使用delegate类型或std::function
			 * \return 如果函数成功则返回S_OK，如果句柄有误，则返回E_INVALIDARG，如果函数名称有误或无法获取函数地址，则返回E_FAIL
			 */
			template<typename T>
			static HRESULT WINAPI loadFunFromLib(HINSTANCE handle, LPCSTR FuncName, std::function<T>& std_function)
			{
				if (!handle) 
				{
					return E_INVALIDARG;
				}
				else 
				{
					FARPROC addr = GetProcAddress(handle, FuncName);
					if (addr != nullptr)
					{
						std_function = (T*)(addr);
						return S_OK;
					}
					else 
					{
						LibError(std::runtime_error("Can't load proc Address，Are you sure that the handles and functions are correct?"));
						return E_FAIL;
					}
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
				static VOID WINUEAPI RtlGetNtVersionNumbers(_Inout_ DWORD* dwMajor, _Inout_ DWORD* dwMinor, _Inout_ DWORD* dwBuilder)
				{
					delegate<VOID,DWORD*,DWORD*,DWORD*> func = nullptr;
					if (HRESULT hr = loadFunFromLib(NTDLL, "RtlGetNtVersionNumbers", func); SUCCEEDED(hr)) 
					{
						return func(dwMajor, dwMinor, dwBuilder);
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
					delegate<INT,HWND, LPCSTR, LPCSTR, UINT, WORD, DWORD> func = nullptr;
					if (HRESULT hr = loadFunFromLib(USER32, "MessageBoxTimeoutA",func); SUCCEEDED(hr))
					{
						if (!hWnd)
						{
							hWnd = GetForegroundWindow();
							return func(hWnd, lpText, lpCaption, uType, wLanguageId, dwMilliseconds);
						}
						else 
						{
							return func(hWnd, lpText, lpCaption, uType, wLanguageId, dwMilliseconds);
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
					delegate<INT,HWND, LPCWSTR, LPCWSTR, UINT, WORD, DWORD> func = nullptr;
					if (HRESULT hr = loadFunFromLib(USER32, "MessageBoxTimeoutW", func); SUCCEEDED(hr)) 
					{
						if (!hWnd) 
						{
							hWnd = GetForegroundWindow();
							return func(hWnd, lpText, lpCaption, uType, wLanguageId, dwMilliseconds);
						}
						else 
						{
							return func(hWnd, lpText, lpCaption, uType, wLanguageId, dwMilliseconds);
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
					delegate<HRESULT, PCWSTR, UINT32, HSTRING_HEADER*, HSTRING*> func = nullptr;
					if (HRESULT hr = loadFunFromLib(COMBASE, "WindowsCreateStringReference", func); SUCCEEDED(hr))
					{
						return func(sourceString, length, hstringHeader, string);
					}
					return E_FAIL;
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
				 * \brief 此部分写于2023/7/25.
				 * \brief 从 PROPVARIANT 结构中提取字符串值。
				 * \brief 批注：
				 * \brief 此函数属于未导出函数，已经文档化，关于文档信息
				 * \brief 请参考以下链接：
				 * \brief https://learn.microsoft.com/zh-cn/windows/win32/api/propvarutil/nf-propvarutil-propvarianttostring
				 * \param propvar 对源 PROPVARIANT 结构的引用。
				 * \param psz 指向字符串缓冲区。 当此函数返回时，使用 NULL 终止的 Unicode 字符串值初始化缓冲区。
				 * \param cch psz 指向的缓冲区的大小（以字符为单位）。
				 * \return 此函数可以返回其中一个值。
				 * \return S_OK 已提取值，结果缓冲区以 NULL 结尾。
				 * \return STRSAFE_E_INSUFFICIENT_BUFFER
				 * \return 由于缓冲区空间不足，复制操作失败。 目标缓冲区包含截断的、以 null 结尾的预期结果版本。 在可以接受截断的情况下，这可能不一定被视为故障条件。
				 * \return 其他一些错误值 : 由于其他原因，提取失败。
				 */
				static HRESULT FAR WINUEAPI PropVariantToString(_In_ REFPROPVARIANT propvar, PWSTR psz, _In_ UINT cch) noexcept
				{
					HRESULT(FAR WINAPI * f_PropVariantToString)(_In_ const PROPVARIANT & propvar, _Out_writes_(cch) PWSTR psz, _In_ UINT cch) = nullptr;
					HRESULT hr = loadFunFromLib(LoadLibraryA("PROPSYS.DLL"), "PropVariantToString", f_PropVariantToString);
					if (FAILED(hr))
					{
						return E_FAIL;
					}
					return f_PropVariantToString(propvar, psz, cch);
				}

				/**
				 * \brief 此部分写于2023/7/25
				 * \brief 函数RoGetActivationFactory的封装，用于获取指定运行时类的激活工厂。
				 * \brief 批注：
				 * \brief 此函数属于未导出函数，已经文档化，关于文档信息请查阅RoGetActivationFactory
				 * \param activatableClassId 可激活类的GUID
				 * \param factory 激活工厂
				 * \return 如果此函数成功，它将返回S_OK。否则，它将返回HRESULT错误代码。
				 */
				template<typename Factory>
				inline HRESULT FAR WINUEAPI Wrap_GetActivationFactory(_In_ HSTRING activatableClassId, _Inout_ Microsoft::WRL::Details::ComPtrRef<Factory> factory) noexcept 
				{
					HRESULT(FAR WINAPI * func)(HSTRING, const IID&, void**) = nullptr;
					HRESULT hr = loadFunFromLib(COMBASE, "RoGetActivationFactory", func);
					if (FAILED(hr))
					{
						return E_FAIL;
					}
					return func(activatableClassId, IID_INS_ARGS(factory.ReleaseAndGetAddressOf()));
				}

				/**
				*  \brief 此部分写于2023/7/25
				 * \brief 此函数用于获取系统版本信息.
				 * \brief 批注：
				 * \brief 此函数属于未导出，未文档化函数
				 *
				 * \return 如果函数成功，它将返回类型RTL_OSVERSIONINFOW的结构体
				 */
				static RTL_OSVERSIONINFOW FAR WINUEAPI RtlGetVersion() noexcept 
				{
					NTSTATUS(WINAPI * RtlGetVersionPtr)(PRTL_OSVERSIONINFOW) = nullptr;
					if (SUCCEEDED(loadFunFromLib(NTDLL, "RtlGetVersion", RtlGetVersionPtr)))
					{
						RTL_OSVERSIONINFOW rovi = { 0 };
						rovi.dwOSVersionInfoSize = sizeof(rovi);
						if (RtlGetVersionPtr(&rovi) == (0x00000000)) 
						{
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
					static UINT WINUEAPI RtlAdjustPrivilege(ULONG Privilege, BOOL bEnablePrivilege, BOOL IsThreadPrivilege, PINT PreviousValue)
					{
						delegate<UINT, ULONG, BOOL, BOOL, PINT> func;
						if (
							HRESULT hr = loadFunFromLib(NTDLL, "RtlAdjustPrivilege", func);
							SUCCEEDED(hr)
							)
						{
							return func(Privilege, bEnablePrivilege, IsThreadPrivilege, PreviousValue);
						}
						else {
							return -1;
						}
					}

					static NTSTATUS NtQueryInformationProcess(IN HANDLE ProcessHandle, IN PROCESSINFOCLASS ProcessInformationClass, OUT PVOID ProcessInformation, IN ULONG ProcessInformationLength, OUT PULONG ReturnLength)
					{
						delegate<NTSTATUS, HANDLE, PROCESSINFOCLASS, PVOID, ULONG, PULONG> func = nullptr;
						if (
							HRESULT hr = loadFunFromLib(NTDLL, "NtQueryInformationProcess", func);
							SUCCEEDED(hr)
							)
						{
							return func(ProcessHandle, ProcessInformationClass, ProcessInformation, ProcessInformationLength, ReturnLength);
						}
						else
						{
							return ERROR;
						}
					}
				}
			}
		}

		/* 存储封装了函数或类型的包装器 */
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
				
				~HstringWrapper() noexcept
				{
					dynamincLibrayFunc::function::WindowsDeleteString(hstring);
				}
				
				inline operator HSTRING() const noexcept
				{
					return this->hstring;
				}

				inline HSTRING Get() const noexcept
				{
					return this->hstring;
				}
			private:
				HSTRING hstring;
				HSTRING_HEADER header;
			};

			/* A Abstract Class From ABI::Windows::Foundation::DateTime */
			interface InternalDateTime : ABI::Windows::Foundation::IReference<ABI::Windows::Foundation::DateTime>
			{
				static INT64 Now(void)
				{
					FILETIME now{};
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

			/*
			 * This is a basic WindowsHook wrapper.
			 * This class has only one member function as a pure virtual function.
			 * To access Basic_WindowsHook, implementations are provided in cloudgameZero::Foundation::Tool::WindowsZero::Event.
			 *
			 * The interfaces provided by this class are only for message hooks, not function hooks.
			 * Callback functions need to adhere to the HOOKPROC prototype, and this library does not provide an implementation for that. You need to implement it yourself.
			 * For more information, please refer to:
			 * https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-setwindowshookexa
			 * and its associated documentation.
			 */
			class Basic_WindowsHook
			{
			public:
				virtual ~Basic_WindowsHook() = default;

				using InstallHookType = cloudgameZero::InstallHookType;

				/**
				 * \brief This section was written on 2023/10/05.
				 * \brief Attaches hook callback to the object.
				 *
				 * \param callback Callback function pointer.
				 */
				void setCallBack(HOOKPROC callback) throw()
				{
					std::lock_guard lock(mtx);
					if (!callback)
					{
						LibError(std::invalid_argument("Callback cannot be null."));
					}
					HOOKPROC_FUN = callback;
				}

				/**
				 * \brief This section was written on 2023/10/05.
				 * \brief Attaches module handle to the hook.
				 * \brief Note: If a module handle is not provided when starting the hook, it will automatically use the application's instance handle.
				 *
				 * \param Module By default, GetModuleHandle provides the instance of the application itself, but you can use it for other modules.
				 * \brief Note: The destructor calls endHook, which uses FreeLibrary to release resources, so be aware.
				 */
				inline void setModule(HMODULE Module = GetModuleHandle(NULL)) noexcept
				{
					this->Module = Module;
				}

				/**
				 * \brief This section was written on 2023/10/05.
				 * \brief Sets the identifier associated with the HOOK callback.
				 *
				 * \param id Identifier of the thread to associate with the HOOK callback. For desktop applications, if this parameter is zero, the hook procedure is associated with all existing threads running in the same desktop as the calling thread.
				 */
				inline void setThreadId(DWORD id = NULL) noexcept
				{
					Id = id;
				}

				/**
				 * \brief This section was written on 2023/10/05.
				 * \brief Installs the HOOK to listen within the thread.
				 *
				 * \param InstallType Taken from the enumeration InstallHookType, the type of HOOK callback to install.
				 */ 
				virtual void startHook(InstallHookType InstallType) throw() = 0;
				/**
				  * This method needs to be overridden. If you prefer not to override it, you can use the default WindowsHookA and WindowsHookW provided.
				  * Functionality to be implemented:
				  * Allows the function to call SetWindowsHookExA, assigns the return value to HOOK handle, listens to events, and installs the callback function.
				  */

				 /**
				  * \brief This section was written on 2023/10/05.
				  * \brief Determines whether to clean up the module.
				  * \brief If you want to release resources when ending HOOK listening, call this function with 'true'.
				  *
				  * \param free Default is 'false'. If 'true', endHook will clean up the module.
				  */
				inline void setFree(bool free = false)
				{
					this->free = free;
				}

				/**
				 * \brief This section was written on 2023/10/05.
				 * \brief Stops listening to the HOOK.
				 */
				inline void endHook() throw()
				{
					std::lock_guard lock(mtx);
					if (Handle)
					{
						UnhookWindowsHookEx(Handle);
						HANDLE ThreadHandle = thread.native_handle();
						thread.detach();
						SuspendThread(ThreadHandle);
						if (Module && free)
						{
							FreeLibrary(Module);
						}
						if (HOOKPROC_FUN)
						{
							HOOKPROC_FUN = nullptr;
						}
					}
				}

				/**
				 * \brief This section was written on 2023/10/05.
				 * \brief Retrieves the handle of the HOOK.
				 *
				 * \return Returns a read-only handle stored in the object.
				 */
				inline operator const HHOOK() noexcept
				{
					std::lock_guard lock(mtx);
					return Handle;
				}

				/**
				 * \brief This section was written on 2023/10/05.
				 * \brief Retrieves the handle of the HOOK.
				 *
				 * \return Returns a read-only handle stored in the object.
				 */
				inline const HHOOK getHook() noexcept
				{
					std::lock_guard lock(mtx);
					return Handle;
				}

				/**
				 * \brief This section was written on 2023/10/05.
				 * \brief Retrieves the thread's ID.
				 * \brief Note: If the thread is not running, it returns 0. When calling startHook, you need to wait for 1 millisecond to retrieve the ID.
				 *
				 * \return Returns the thread ID.
				 */
				inline DWORD getHookThreadId() noexcept
				{
					std::lock_guard lock(mtx);
					if (!running)
					{
						return 0;
					}
					return cloudgameZero::getThreadId(thread);
				}

				/**
				 * \brief This section was written on 2023/10/05.
				 * \brief Retrieves the thread's address.
				 * \brief Note: If the thread is not running, it returns nullptr. When calling startHook, you need to wait for 1 millisecond to retrieve the address.
				 *
				 * \return Returns the thread's address (as void*).
				 */
				inline void* getThreadAddress() noexcept
				{
					std::lock_guard lock(mtx);
					if (!running)
					{
						return nullptr;
					}
					return &thread;
				}

			protected:
				std::atomic_bool free = false;
				std::atomic_bool running = false;
				std::mutex mtx;
				DWORD Id{};
				HMODULE Module{};
				std::jthread thread;
				HHOOK Handle{};
				LRESULT(*HOOKPROC_FUN)(int code, WPARAM wParam, LPARAM lParam) = nullptr;
			};
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
				static inline std::string GetEnvironmentVariableA(const std::string PATH, DWORD len = MAX_PATH)
				{
					char* buf = new char[MAX_PATH];
					::GetEnvironmentVariableA(PATH.c_str(), buf, MAX_PATH);
					std::string ret(buf);
					delete[] buf;
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
				 * \return 如果一切正常，将返回一个std::string字符串
				 */
				static std::wstring GetProcesserFromRegistryW()
				{
					DWORD dwSize = 50;
					::RegGetValueW(HKEY_LOCAL_MACHINE, L"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0",L"ProcessorNameString", RRF_RT_ANY, NULL, nullptr, &dwSize);
					std::wstring data;
					data.resize(dwSize);
					::RegGetValueW(HKEY_LOCAL_MACHINE, L"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", L"ProcessorNameString", RRF_RT_ANY, NULL, &data[0], &dwSize);
					return data;
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
						do 
						{
							if (!wcscmp(processName, pe32.szExeFile))
							{
								return pe32.th32ProcessID;
							}
						} 
						while (Process32Next(hProcessSnapShot, &pe32));
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
						static INT value = 0;
						using namespace Foundation::dynamincLibrayFunc::function;
						unstable::RtlAdjustPrivilege(unstable::SeDebugPrivilege, TRUE, FALSE,&value);
						Handle = OpenProcess(PROCESS_TERMINATE, FALSE, pid);
						unstable::RtlAdjustPrivilege(unstable::SeDebugPrivilege, FALSE, FALSE, &value);
						if (!Handle)
						{
							return -1;
						}
					}
					TerminateProcess(Handle, 0);
					::CloseHandle(Handle);
					return 1;
				}

				static void cleanConsoleBuffer(HANDLE hConsole)
				{
					CONSOLE_SCREEN_BUFFER_INFO csbi;
					SMALL_RECT scrollRect;
					COORD scrollTarget;
					CHAR_INFO fill;
					if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
					{
						return;
					}
					scrollRect.Left = 0;
					scrollRect.Top = 0;
					scrollRect.Right = csbi.dwSize.X;
					scrollRect.Bottom = csbi.dwSize.Y;
					scrollTarget.X = 0;
					scrollTarget.Y = (SHORT)(0 - csbi.dwSize.Y);
					fill.Char.UnicodeChar = TEXT(' ');
					fill.Attributes = csbi.wAttributes;
					ScrollConsoleScreenBuffer(hConsole, &scrollRect, NULL, scrollTarget, &fill);
					csbi.dwCursorPosition.X = 0;
					csbi.dwCursorPosition.Y = 0;
					SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
				}

				/**
				 * \brief 通过chrono时间库生成一个时间字符串.
				 *
				 * \param format 格式化字符串，取自https://www.apiref.com/cpp-zh/cpp/io/manip/put_time.html
				 * \return 返回格式化后的字符串
				 */
				static inline std::string makeTimeStr(std::string& format) throw()
				{
					time_t tt = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
					tm time_tm;
					localtime_s(&time_tm, &tt);
					char strTime[50] = { 0 };
					strftime(strTime, 50, format.c_str(), &time_tm);
					return strTime;
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
				 * 用于计算多字节字符串或宽字节字符串的函数.
				 *
				 * \param str 字符串变量
				 * \return 如果合法，返回字符串长度（不包含'\0')，否则返回0
				 */
				template<typename T>
				inline std::size_t _strlen(T str)
				{
					std::size_t count = NULL;
					if constexpr (std::is_same_v<T, const char*> || std::is_same_v<T, char*>)
					{
						while (*str++ != '\0')
						{
							count++;
						}
						return count;
					}
					else if constexpr (std::is_same_v<T, const wchar_t*> || std::is_same_v<T, wchar_t*>) 
					{
						while (*str++ != '\0') 
						{
							count++;
						}
						return count;
					}
					return count;
				}

				static bool isProcessExists(std::string_view processName)
				{
					bool ret = false;
					HANDLE info_handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
					if (info_handle == INVALID_HANDLE_VALUE)
					{
						PrintError("CreateToolhelp32Snapshot fail!!");
						return false;
					}
					PROCESSENTRY32W program_info{};
					program_info.dwSize = sizeof(PROCESSENTRY32W);
					int bResult = Process32FirstW(info_handle, &program_info);
					if (!bResult)
					{
						PrintError("Process32FirstW fail!!");
						return false;
					}
					std::wstring argref = MutiToWide(processName.data());
					do
					{
						std::wstring pro_name = std::wstring(program_info.szExeFile);
						if (argref == pro_name)
						{
							ret = true;
							break;
						}
					} while (Process32Next(info_handle, &program_info));
					CloseHandle(info_handle);
					return ret;
				}
			}

			enum class CONSOLE : WORD
			{
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
					std::wstring ret = function::MutiToWide(str);
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
					std::string ret = function::WideToMuti(str);
					return ret;
				}

				/**
				 * \brief 此部分写于2023/8/5.
				 * \brief 返回多字节字符串的长度，相当于strlen
				 * \str 字符串
				 * \return 返回字符串的长度
				 */
				static _NODISCARD inline constexpr std::size_t operator"" _zsl(const char* str, std::size_t size)
				{
					return size;
				}

				/**
				 * \brief 此部分写于2023/8/5.
				 * \brief 返回宽字节字符串的长度，相当于strlen
				 * \str 字符串
				 * \return 返回字符串的长度
				 */
				static _NODISCARD inline constexpr std::size_t operator"" _zwl(const wchar_t* str, std::size_t size)
				{
					return size;
				}

				/**
				 * \brief 此部分写于2023/8/5.
				 * \brief 将size_t转换为std::string
				 * \param num 待转换的数据
				 * \return 返回std::string
				 */
				static _NODISCARD inline std::string operator"" _zIS(std::size_t num)
				{
					return std::to_string(num);
				}

				/**
				 * \brief 此部分写于2023/8/5.
				 * \brief 将字符串的数字转换为int.
				 *
				 * \return 如果出现异常，它将返回NULL，如果正常，它将返回解析得到的数字
				 */
				static _NODISCARD inline int operator""_zSI(const char* num, std::size_t size)
				{
					try 
					{
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
					return [=](const char* regex) -> bool
						{
							return std::regex_match(rege.str, std::regex(regex)); 
						};
				}

				/**
				 * \brief 此部分写于2023/8/20.
				 * \brief 用于检查正则表达式是否在字符串中存在匹配的子串.
				 */
				template<structs::regexStruct rege>
				static inline constexpr auto operator"" _rsearch()
				{
					return [=](const char* regex) -> bool 
						{
							return std::regex_search(rege.str, std::regex(regex));
						};
				}
			}

			/* Windows功能区 */
			inline namespace WindowsZero
			{
				inline namespace TaskBar
				{
					static NTSTATUS fakeToExplorer()
					{
						using namespace Foundation::dynamincLibrayFunc::function;
						// 获取explorer的路径
						WCHAR szwPath[MAX_PATH] = { 0 };
						auto Null = GetWindowsDirectoryW(szwPath, MAX_PATH);
						if (!Null)
						{
							PrintError(formatWindowsErrorMessage(GetLastError()));
							return ERROR;
						}
						wcscat_s(szwPath, L"\\Explorer.exe");
						// 查询当前程序的PEB信息
						PROCESS_BASIC_INFORMATION pbi = { 0 };
						NTSTATUS ret = unstable::NtQueryInformationProcess(GetCurrentProcess(), ProcessBasicInformation, &pbi, sizeof(pbi), NULL);
						if (!NT_SUCCESS(ret))
						{
							return ret;
						}
						// 检查当前程序路径缓冲区是否足够
						USHORT n = (USHORT)wcslen(szwPath);
						if (pbi.PebBaseAddress->ProcessParameters->ImagePathName.MaximumLength / 2 <= n)
						{
							return ERROR_INSUFFICIENT_BUFFER;
						}
						// 伪装成explorer路径，必须要有NULL结尾符
						memcpy(pbi.PebBaseAddress->ProcessParameters->ImagePathName.Buffer, szwPath, n * 2);
						pbi.PebBaseAddress->ProcessParameters->ImagePathName.Buffer[n] = NULL; // 结尾符
						pbi.PebBaseAddress->ProcessParameters->ImagePathName.Length = n * 2;
						return ERROR_SUCCESS;
					}

					static NTSTATUS PinToTaskbar(PCWSTR pFolder, PCWSTR pName)
					{
						if (!pFolder || !pName)
						{
							return ERROR_INVALID_PARAMETER;
						}
						// 初始化COM组件
						HRESULT hr = CoInitialize(NULL);
						if (FAILED(hr))
						{
							return ERROR;
						}
						// 获取shell的CLSID
						CLSID clsid = { 0 };
						hr = CLSIDFromProgID(L"Shell.Application", &clsid);
						if (FAILED(hr))
						{
							return HRESULT_CODE(hr);
						}
						// 获取右键菜单列表
						BSTR bs = NULL;
						VARIANT var = { VT_BSTR };
						//我们使用ComPtr管理接口，这样在函数完成的时候可以直接析构来清理接口
						ComPtr<IShellDispatch> pisd = nullptr;
						ComPtr<Folder> pf = nullptr;
						ComPtr<FolderItem> pfi = nullptr;
						ComPtr<FolderItemVerbs> pfivs = nullptr;
						ComPtr<FolderItemVerb> pfiv = nullptr;
						do
						{
							// 创建shell实例
							hr = CoCreateInstance(clsid, NULL, CLSCTX_INPROC_SERVER, IID_IDispatch, (void**)&pisd);
							if (FAILED(hr))
							{
								break;
							}
							// 处理文件路径
							var.bstrVal = SysAllocString(pFolder);
							if (!var.bstrVal)
							{
								break;
							}
							hr = pisd->NameSpace(var, &pf);
							if (FAILED(hr))
							{
								break;
							}
							// 处理文件名
							bs = SysAllocString(pName);
							if (!bs) { break; }
							hr = pf->ParseName(bs, &pfi);
							if (FAILED(hr))
							{
								break;
							}
							// 获取右键菜单列表
							hr = pfi->Verbs(&pfivs);
							if (FAILED(hr))
							{
								break;
							}
							long n = 0;
							hr = pfivs->get_Count(&n);
							if (FAILED(hr))
							{
								break;
							}
							// 循环遍历右键菜单列表
							BSTR name = NULL;
							BOOL bRet = FALSE;
							VARIANT i = { VT_I4 };
							for (i.lVal = 0; i.lVal < n; i.lVal++)
							{
								hr = pfivs->Item(i, &pfiv);
								if (FAILED(hr))
								{
									continue;
								}
								// 对比右键菜单项的名称
								hr = pfiv->get_Name(&name);
								if (SUCCEEDED(hr))
								{
									if (!wcscmp(name, L"Pin to tas&kbar") || !wcscmp(name, L"固定到任务栏(&K)"))
									{
										pfiv->DoIt();
										break;
									}
								}
								pfiv->Release();
								if (bRet)
								{
									break;
								}
							}
						} while (false);
						// 释放所用的数据
						if (bs)
						{
							SysFreeString(bs);
						}
						if (var.bstrVal)
						{
							SysFreeString(var.bstrVal);
						}
						return HRESULT_CODE(hr);
					}
				}

				inline namespace Data
				{
					class section
					{
					public:
						section(std::string section)
						{
							this->sections = section;
						}
						inline bool addKeyValue(std::string key, std::string value)
						{
							std::pair<std::string, std::string> p(key, value);
							mapKey.insert(p);
							return true;
						}
						inline std::string get(std::string name)
						{
							return mapKey[name];
						}
						inline std::string operator[](const char* name)
						{
							return mapKey[name];
						}
						friend class iniParser;
					private:
						std::string sections;
						std::map<std::string, std::string> mapKey;
					};

					class sectionBuffer
					{
					public:
						bool addSection(const std::string strSection)
						{
							std::pair<std::string, std::string> p(strSection, strSection);
							mapSection.insert(p);
							return true;
						}
						section& getSection(const std::string strSection)
						{
							auto it = mapSection.find(strSection);
							if (IS_DEBUG)
							{
								assert(it != mapSection.end());
							}
							else
							{
								if (it == mapSection.end())
								{
									throw std::invalid_argument("错误的参数");
								}
							}
							return ((*it).second);
						}
						inline section& operator[](std::string name)
						{
							return getSection(name);
						}
						inline std::string getString()
						{
							return ss.str();
						}
						sectionBuffer& operator=(sectionBuffer& buffer) = default;
						friend class iniParser;
					private:
						std::map<std::string, section> mapSection;
						std::stringstream ss;
					};

					class iniParser
					{
					public:
						enum mode
						{
							pretty,
							normal
						};
						
						iniParser(sectionBuffer& collect) : collect(collect) 
						{
						}
						
						iniParser(std::string strPath, sectionBuffer& collect) : strPath(strPath), collect(collect)
						{
						}
						
						void setPath(std::string path)
						{
							strPath = path;
						}

						void parse()
						{
							std::string strLine, strSection, strKey, strValue;
							section* pSection = nullptr;
							std::ifstream in(strPath.c_str());
							if (!in.is_open())
							{
								return;
							}
							while (!in.eof())
							{
								getline(in, strLine);
								Trim(strLine);
								if (strLine == "")
								{
									continue;
								}
								parseToGbk(strLine);
								strLine = std::regex_replace(strLine, std::regex("\t"), "");
								if (strLine[0] == '[') {
									strSection = getSection(strLine);
									collect.addSection(strSection);
									pSection = &collect.getSection(strSection);
								}
								if (strLine[0] != '[')
								{
									getPair(strLine, strKey, strValue);
									pSection->addKeyValue(strKey, strValue);
								}
							}
							in.close();
						}
						void parse(std::string str)
						{
							std::string strLine, strSection, strKey, strValue;
							section* pSection = nullptr;
							std::fstream f("temp", std::ios::app);
							if (!f.is_open())
							{
								return;
							}
							str = std::regex_replace(str.c_str(), std::regex("\t"), "");
							f << str;
							f.close();
							f.open("temp", std::ios::in);
							if (!f.is_open())
							{
								return;
							}
							while (!f.eof())
							{
								getline(f, strLine);
								Trim(strLine);
								if (strLine == "")
								{
									continue;
								}
								parseToGbk(strLine);
								strLine = std::regex_replace(strLine, std::regex("\t"), "");
								if (strLine[0] == '[') {
									strSection = getSection(strLine);
									collect.addSection(strSection);
									pSection = &collect.getSection(strSection);
								}
								if (strLine[0] != '[')
								{
									getPair(strLine, strKey, strValue);
									pSection->addKeyValue(strKey, strValue);
								}
							}
							f.close();
							std::filesystem::remove("temp");
						}

						void writer(mode mode = pretty)
						{
							for (auto it = collect.mapSection.rbegin(); it != collect.mapSection.rend(); it++)
							{
								collect.ss << "[" << (*it).second.sections << "]" << "\n";
								std::ranges::for_each(it->second.mapKey,
									[this,&mode](std::pair<std::string, std::string> p)
									{
										collect.ss << (mode == pretty ? "\t" : "") << p.first << "=" << p.second << "\n";
									});
							}
						}
						void writeToFile(std::ofstream& ofs, mode mode = pretty)
						{
							this->writer(mode);
							std::string write = collect.getString();
							parseToUtf8(write);
							if (ofs.is_open())
							{
								ofs << write;
							}
							else
							{
								LibError(std::runtime_error("必须打开文件才能输出"));
							}
						}
					private:
						void parseToGbk(std::string& strLine)
						{
							int len = MultiByteToWideChar(CP_UTF8, 0, strLine.c_str(), -1, NULL, 0);
							WCHAR* wszGBK = new WCHAR[len + 1];
							memset(wszGBK, 0, static_cast<size_t>(len) * 2 + 2);
							MultiByteToWideChar(CP_UTF8, 0, strLine.c_str(), -1, wszGBK, len);
							len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
							CHAR* szGBK = new CHAR[len + 1];
							memset(szGBK, 0, static_cast<size_t>(len) + 1);
							WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, szGBK, len, NULL, NULL);
							strLine = szGBK;
							delete[] wszGBK, szGBK;
						}
						void parseToUtf8(std::string& strLine)
						{
							int len = MultiByteToWideChar(CP_ACP, 0, strLine.c_str(), -1, NULL, 0);
							WCHAR* wstr = new WCHAR[len + 1];
							memset(wstr, 0, static_cast<size_t>(len) + 1);
							MultiByteToWideChar(CP_ACP, 0, strLine.c_str(), -1, wstr, len);
							len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
							CHAR* str = new CHAR[len + 1];
							memset(str, 0, static_cast<size_t>(len) + 1);
							WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
							strLine = str;
							delete[] wstr, str;
						}
						std::string getSection(std::string strText)
						{
							strText.erase(0, strText.find_first_not_of("["));
							strText.erase(strText.find_last_not_of("]") + 1);
							return strText;
						}
						void getPair(std::string strText, std::string& key, std::string& value) {
							int pos = static_cast<int>(strText.find("="));
							key = strText.substr(0, pos);
							value = strText.substr(pos + 1, strText.length() - pos - 1);
							Trim(key);
							Trim(value);
						}
						void Trim(std::string& s)
						{
							if (!s.empty())
							{
								s = std::regex_replace(s, std::regex(" "), "");
							}
						}
						std::string strPath;
						sectionBuffer& collect;
					};

					enum class Handle
					{
						_NULL,
						_HKEY_CLASSES_ROOT,
						_HKEY_CURRENT_USER,
						_HKEY_LOCAL_MACHINE,
						_HKEY_USERS,
						_HKEY_CURRENT_CONFIG
					};

					static const std::map<Handle, HKEY> mapping = {
						{Handle::_HKEY_LOCAL_MACHINE,	Infomation::HKLM},
						{Handle::_HKEY_CLASSES_ROOT,	Infomation::HKCR},
						{Handle::_HKEY_CURRENT_CONFIG,	Infomation::HKCC},
						{Handle::_HKEY_USERS,			Infomation::HKU },
						{Handle::_HKEY_CURRENT_USER,	Infomation::HKCU}
					};

					class Regedit
					{
					public:
						

						/**
						 * 默认构造函数.
						 */
						inline Regedit() = default;

						/**
						 * \brief 将该类枚举量映射的句柄导入到对象里.
						 * \brief 如果使用_NULL枚举量默认打开HKCU
						 *
						 * \param handle 枚举句柄
						 */
						inline Regedit(Handle handle)
						{
							openKey(handle);
						}

						/**
						 * \brief 将HKEY原生句柄导入到对象中管理.
						 * \brief 如果句柄无效，会调用错误函数，抛出错误
						 *
						 * \param Handle 本地句柄
						 */
						inline Regedit(HKEY Handle)
						{
							if (!Handle)
							{
								LibError(std::runtime_error("并不是一个有效的句柄"));
							}
							currentHandle = Handle;
						}

						/**
						 * \brief 此部分写于2023/9/25.
						 * \brief 构造函数重载
						 * \param handle 枚举句柄
						 * \param subkey 子项
						 */
						inline Regedit(Handle handle, std::string_view subkey)
						{
							openKey(handle, subkey);
						}

						/**
						 * \brief 此部分写于2023/9/25.
						 * \brief 此构造函数方式类似于原生函数，此处不展开赘述
						 *
						 * \param handle 本地句柄
						 * \param subkey 子项
						 */
						inline Regedit(HKEY Handle, std::string_view subkey)
						{
							LSTATUS error{};
							if (!Handle)
							{
								error = RegOpenKeyExA(HKEY_CURRENT_USER, subkey.data(), NULL, KEY_ALL_ACCESS, &this->currentHandle);
								return;
							}
							HKEY KEY_HANDLE = nullptr;
							error = RegOpenKeyExA(Handle, subkey.data(), NULL, KEY_ALL_ACCESS, &this->currentHandle);
							if (error != ERROR_SUCCESS)
							{
								error = RegOpenKeyExA(Handle, subkey.data(), NULL, KEY_READ, &this->currentHandle);
								if (error != ERROR_SUCCESS)
								{
									error = RegOpenKeyExA(Handle, subkey.data(), NULL, KEY_QUERY_VALUE, &this->currentHandle);
									if (error != ERROR_SUCCESS)
									{
										PrintError(formatWindowsErrorMessage(error));
									}
								}
							}
						}

						/**
						 * \brief 此部分写于2023/9/26.
						 * \brief 由于一个句柄只允许一个对象管理，因此拷贝操作强制使用移动构造.
						 *
						 * \param Left 右值
						 */
						Regedit(Regedit& Left) noexcept
						{
							this->swap(Left);
						}

						/**
						 * \brief 此部分写于2023/9/26.
						 * \brief 由于一个句柄只允许一个对象管理，因此拷贝操作强制使用移动构造.
						 *
						 * \param Right 右值
						 */
						Regedit(Regedit&& Right) noexcept
						{
							this->swap(Right);
						}

						/**
						 * \brief 此部分写于2023/9/26.
						 * \brief 由于一个句柄只允许一个对象管理，因此拷贝操作强制使用移动构造.
						 *
						 * \param Left 左值
						 * \return 返回this引用
						 */
						Regedit& operator=(Regedit& Left) noexcept
						{
							return this->swap(Left);
						}

						/**
						 * \brief 此部分写于2023/9/26.
						 * \brief 由于一个句柄只允许一个对象管理，因此拷贝操作强制使用移动构造.
						 *
						 * \param Right 右值
						 * \return 返回this引用
						 */
						Regedit& operator=(Regedit&& Right) noexcept
						{
							return this->swap(Right);
						}

						/**
						 * \brief 此部分写于2023/9/26.
						 * \brief 将右值的句柄移动到this下
						 *
						 * \param Right
						 */
						inline Regedit& swap(Regedit& Right)
						{
							if (!Right || this == std::addressof(Right))
							{
								return *this;
							}
							this->currentHandle = std::exchange(Right.currentHandle, nullptr);
							return *this;
						}

						/**
						 * \brief 此部分写于2023/9/25.
						 * \brief 将此句柄下的子键值进行遍历并传入回调
						 * \brief 如果回调无效，会调用函数抛出异常
						 *
						 * \param callback(char* name,LPCSTR value)
						 */
						inline std::string operator[](const std::string& query) const
						{
							return this->getValue(query);
						}

						/**
						 * \brief 此运算符返回对象保存的本地句柄.
						 *
						 * \return 返回句柄
						 */
						inline operator const HKEY() const
						{
							return this->native_handle();
						}

						/**
						 * \brief 此部分写于2023/9/25.
						 * \brief 将句柄置入对象里
						 *
						 * \param Handle HKEY句柄
						 */
						inline void operator<<(HKEY Handle)
						{
							openKey(Handle);
						}

						/**
						*  \brief 此部分写于2023/9/24
						 * \brief 返回这个对象保存的句柄.
						 *
						 * \return 返回常量句柄，仅可读
						 */
						inline const HKEY native_handle() const
						{
							return this->currentHandle;
						}

						/**
						 * \brief 析构函数将自动调用closeKey销毁句柄.
						 *
						 */
						~Regedit()
						{
							closeKey();
						}

						/**
						 * \brief 此部分写于2023/9/24.
						 * \brief 把Handle枚举的值转换为对应句柄并通过该句柄打开注册表
						 * \param Key 枚举
						 * \param subkey 子键
						 * \return 如果打开成功返回true，否则返回false
						 */
						bool openKey(Handle Key, std::string_view subkey = std::string_view("")) noexcept
						{
							LSTATUS error{};
							if (Key == Handle::_NULL)
							{
								error = RegOpenKeyExA(HKEY_CURRENT_USER, subkey.data(), NULL, KEY_ALL_ACCESS, &this->currentHandle);
								return true;
							}
							HKEY KEY_HANDLE = nullptr;
							KEY_HANDLE = mapping.find(Key)->second;
							error = RegOpenKeyExA(KEY_HANDLE, subkey.data(), NULL, KEY_ALL_ACCESS, &this->currentHandle);
							if (error != ERROR_SUCCESS)
							{
								error = RegOpenKeyExA(KEY_HANDLE, subkey.data(), NULL, KEY_READ, &this->currentHandle);
								if (error != ERROR_SUCCESS)
								{
									error = RegOpenKeyExA(KEY_HANDLE, subkey.data(), NULL, KEY_QUERY_VALUE, &this->currentHandle);
									if (error != ERROR_SUCCESS)
									{
										PrintError(formatWindowsErrorMessage(error));
										return false;
									}
								}
							}
							return true;
						}

						/**
						 * \brief 此部分写于2023/9/24.
						 *
						 * \param Hkey 句柄
						 * \param subkey 子项（可选）如果为空，将会打开当前句柄
						 * \return 如果成功，返回true否则为false，且会打印错误信息
						 */
						bool openKey(const HKEY Hkey, std::string_view subkey = std::string_view())
						{
							LSTATUS error = RegOpenKeyExA(Hkey, subkey.data(), NULL, KEY_ALL_ACCESS, &this->currentHandle);
							if (error != ERROR_SUCCESS)
							{
								error = RegOpenKeyExA(Hkey, subkey.data(), NULL, KEY_READ, &this->currentHandle);
								if (error != ERROR_SUCCESS)
								{
									error = RegOpenKeyExA(Hkey, subkey.data(), NULL, KEY_QUERY_VALUE, &this->currentHandle);
									if (error != ERROR_SUCCESS)
									{
										PrintError(formatWindowsErrorMessage(error));
										return false;
									}
								}
							}
							return true;
						}

						/**
						 * \brief 此部分写于2023/9/24.
						 * \brief 将此句柄下的子项进行遍历获取键值名.
						 * \brief 如果回调无效，会调用函数抛出异常.
						 *
						 * \param callback(int index,char* name)
						 * \param index 索引
						 * \param name 键值名
						 */
						void traverseTree(delegate<void, int, CHAR*> callback) const
						{
							if (!callback)
							{
								LibError(std::invalid_argument("需要提供回调"));
							}
							if (!this->currentHandle)
							{
								return;
							}
							DWORD dwIndexs = 0;
							CHAR keyName[MAX_PATH] = { 0 };
							DWORD charLength = MAX_PATH;
							while (RegEnumKeyExA(this->currentHandle, dwIndexs, keyName, &charLength, NULL, NULL, NULL, NULL) == ERROR_SUCCESS)
							{
								callback(dwIndexs, keyName);
								charLength = MAX_PATH;
								++dwIndexs;
							}
						}

						/**
						 * \brief 此部分写于2023/9/24.
						 * \brief 将此句柄下的子项保存到map容器里.
						 *
						 * \return 保存的子项和索引
						 */
						inline std::map<int, std::string> traverseTree() noexcept
						{
							std::map<int, std::string> list;
							this->traverseTree([&list](int index, char* name)
								{
									list.insert({ index,name });
								});
							return list;
						}

						/**
						 * \brief 此部分写于2023/9/25.
						 * \brief 将此句柄下的子键值进行遍历并传入回调
						 * \brief 如果回调无效，会调用函数抛出异常
						 *
						 * \param callback(char* name,LPCSTR value)
						 */
						void traverseValue(delegate<void, CHAR*, LPCSTR> callback) const
						{
							if (!callback)
							{
								LibError(std::invalid_argument("需要提供回调"));
							}
							if (!this->currentHandle)
							{
								return;
							}
							DWORD index = 0, dwSize = 0, LONGS = 0;
							CHAR keyName[1024] = { 0 };
							CHAR Data[1024] = { 0 };
							DWORD charLength = dwSize = sizeof(keyName) / sizeof(CHAR);
							DWORD count{ 0 };
							DWORD Type = RRF_RT_ANY;
							RegQueryInfoKeyA(currentHandle, NULL, NULL, NULL, NULL, NULL, NULL, &count, NULL, NULL, NULL, NULL); //我们拿到这个句柄下键值的count
							for (DWORD i = 0; i < count; i++) //通过for循环遍历拿到key的名字然后通过getValue函数获得到值
							{
								charLength = dwSize = sizeof(keyName) / sizeof(CHAR); //每次循环开始时重置Length，否则无法继续遍历
								LSTATUS error = RegEnumValueA(currentHandle, i, keyName, &charLength, NULL, &Type, nullptr, NULL); //通过这个函数拿到枚举的键值
								std::string data = getValue(keyName); //获取它
								callback(keyName, data.c_str());
							}
						}

						/**
						 * \brief 此部分写于2023/9/25.
						 * \brief 将此句柄下的子键值保存到map容器里.
						 *
						 * \return 保存的子项和对应的数据
						 */
						std::unordered_map<std::string, std::string> traverseValue() const
						{
							std::unordered_map<std::string, std::string> list;
							this->traverseValue([&list](CHAR* name, LPCSTR value)
								{
									list.insert({ name,value });
								});
							return list;
						}

						/**
						 * \brief 此部分写于2023/9/25.
						 * \brief 删除某个子键.
						 * \brief 批注：
						 * \brief 函数先会尝试调用RegDeleteKey删除，如果失败将会调用RegDeleteTree进行递归删除
						 *
						 * \param keyName 键值
						 * \return 如果删除成功返回true，否则false，如果句柄有效，会在debug模式下打印错误信息
						 */
						bool deleteKey(std::string_view keyName)
						{
							EventBus bus;
							if (!currentHandle)
							{
								return false;
							}
							if (keyName.empty())
							{
								LibError(std::invalid_argument("The Arguments keyName Can't Be Empty"));
							}
							LSTATUS err = RegDeleteKeyA(currentHandle, keyName.data());
							if (err != ERROR_SUCCESS)
							{
								err = RegDeleteTreeA(currentHandle, keyName.data());
								if (err != ERROR_SUCCESS)
								{
									PrintError(formatWindowsErrorMessage(err));
									static LSTATUS buf = err;
									bus.post("reg_delete_failed", &buf);
									return false;
								}
							}
							return true;
						}

						/**
						 * \brief 此部分写于2023/9/25.
						 * \brief 重命名某个键.
						 *
						 * \param keyName 旧名字
						 * \param newName 新名字
						 * \return 如果命名成功返回true，否则false
						 */
						bool renameKey(std::string_view keyName, std::string_view newName)
						{
							if (!currentHandle)
							{
								return false;
							}
							if (newName.empty())
							{
								LibError(std::invalid_argument("The Arguments newName Can't Be Empty"));
							}
							LSTATUS error = RegRenameKey(currentHandle, MutiToWide(keyName.data()).c_str(), MutiToWide(newName.data()).c_str());
							if (error != ERROR_SUCCESS)
							{
								PrintError(formatWindowsErrorMessage(error));
								return false;
							}
							return true;
						}

						/**
						 * \brief 此部分写于2023/9/26.
						 * \brief 添加某个项的键值.
						 * \brief 有个值得注意的点在于此函数的实现类似addValue，但是它会打开句柄修改，而addValue不会.
						 * \brief 如果无法打开，函数将会失败，而addValue不会，但如果只是设置键值，请使用此函数.
						 *
						 * \param subkey 子项
						 * \param keyname 值名称
						 * \param Type 这个值的数据类型
						 * \param data 要存储的数据
						 * \param count 如果要存储二进制数据，而此处就是二进制数据的大小
						 * \return 返回执行这个键值的句柄
						 */
						void addValue(std::string_view subkey, std::string_view keyname, DWORD Type, std::string data,DWORD count = 0) const
						{
							EventBus bus;
							HKEY Handle{};
							if (!this)
							{
								return;
							}
							LSTATUS error{ 0 };
							DWORD type{ 0 };
							error = RegQueryValueExA(currentHandle, keyname.data(), NULL, &type, NULL, NULL);
							if (error == ERROR_SUCCESS)
							{
								LibError(std::runtime_error("若要修改数据，请使用setValue"));
							}
							DWORD size = NULL;
							switch (Type)
							{
							case REG_DWORD:
								size = sizeof(REG_DWORD);
								break;
							case REG_QWORD:
								size = sizeof(REG_QWORD);
								break;
							case REG_NONE:
								size = data.size();
								break;
							default:
								if (Type == REG_MULTI_SZ)
								{
									data += "\0";
									size = data.size() + 1;
								}
								else if (Type == REG_SZ)
								{
									size = data.size() + 1;
								}
								else if (Type == REG_EXPAND_SZ)
								{
									size = data.size() + 1;
								}
								else if (Type == REG_BINARY)
								{
									size = count;
								}
								else
								{
									LibError(std::runtime_error("无法识别类型"));
								}
								break;
							}
							if (Type == REG_DWORD)
							{
								DWORD Data = static_cast<DWORD>(strToInt(data));
								error = RegSetValueExA(currentHandle, keyname.data(), NULL, Type, reinterpret_cast<LPBYTE>(&Data), size);
							}
							else if (Type == REG_QWORD)
							{
								LONGLONG Data{ 0 };
								long long ago = cloudgameZero::strToLongLong(data);
								error = RegSetValueExA(currentHandle, keyname.data(), NULL, Type, reinterpret_cast<LPBYTE>(&ago), size);
							}
							else if (type == REG_BINARY)
							{
								LPVOID Data = &data[0];
								error = RegSetValueExA(currentHandle, keyname.data(), NULL, Type, reinterpret_cast<LPBYTE>(Data), size);
							}
							else
							{
								error = RegSetValueExA(currentHandle, keyname.data(), NULL, Type, (LPBYTE)data.c_str(), size);
							}
							if (error != ERROR_SUCCESS)
							{
								static LSTATUS buf;
								buf = error;
								bus.post("reg_set_failed", &buf);
							}
							return;
						}

						/**
						 * \brief 此部分写于2023/9/25.
						 * \brief 设置某个项的数据.
						 * \brief 批注：
						 * \brief 有个值得注意的点在于此函数的实现类似addValue，但是此函数会查询是否存在键值，如果不存在，则会抛出异常，而addValue不会.
						 * \brief 如果无法打开，函数将会失败，而此函数不会，但如果只是添加键值，请使用此函数.
						 *
						 * \param keyname 值名称
						 * \param Type 这个值的数据类型
						 * \param data 要存储的数据
						 */
						void setValue(const std::string& keyname, DWORD Type, std::string data) const
						{
							EventBus bus;
							HKEY Handle{};
							if (!this)
							{
								return;
							}
							LSTATUS error{0};
							DWORD type{ 0 };
							error = RegQueryValueExA(currentHandle, keyname.c_str(), NULL,&type,NULL,NULL);
							if (error == ERROR_FILE_NOT_FOUND)
							{
								LibError(std::runtime_error("若要添加数据，请使用addValue"));
							}
							DWORD size = NULL;							
							switch (Type)
							{
							case REG_DWORD:
								size = sizeof(REG_DWORD);
								break;
							case REG_QWORD:
								size = sizeof(REG_QWORD);
								break;
							case REG_NONE:
								size = data.size();
								break;
							default:
								if (Type == REG_MULTI_SZ)
								{
									data += "\0";
									size = data.size() + 1;
								}
								else if (Type == REG_SZ)
									size = data.size() + 1;
								else if (Type == REG_EXPAND_SZ)
									size = data.size() + 1;
								else
									LibError(std::runtime_error("无法识别类型"));
								break;
							}
							if (Type == REG_DWORD)
							{
								DWORD Data = static_cast<DWORD>(strToInt(data));
								error = RegSetValueExA(currentHandle,keyname.c_str(), NULL, Type, reinterpret_cast<LPBYTE>(&Data), size);
							}
							else if(Type == REG_QWORD)
							{
								LONGLONG Data{0};
								StrToInt64ExA(&data[0], STIF_DEFAULT, &Data);
								error = RegSetValueExA(currentHandle, keyname.c_str(), NULL, Type, reinterpret_cast<LPBYTE>(&Data), size);
							}
							else
								error = RegSetValueExA(currentHandle, keyname.c_str(), NULL, Type, (LPBYTE)data.c_str(), size);
							if (error != ERROR_SUCCESS)
								bus.post("reg_set_failed",&error);
							return;
						}

						/**
						 * \brief 此部分写于2023/9/25.
						 * \brief 修改某个二进制值的数据.
						 * 
						 * \param keyname 键值
						 * \param data 二进制数据地址
						 * \param size 二进制数据的大小
						 */
						void setValue(const std::string& keyname,void* data,size_t size)
						{
							if (!data || !currentHandle)
							{
								LibError(std::runtime_error("对象句柄不能为空且输入数据也不能为空"));
							}
							else
							{
								EventBus bus;
								DWORD type;
								RegQueryValueExA(currentHandle, keyname.c_str(), NULL, &type, NULL, NULL);
								if (type != REG_BINARY)
								{
									LibError(std::runtime_error("如果要修改二进制数据，它的数据类型必须是二进制"));
								}
								LSTATUS error = RegSetValueExA(currentHandle, keyname.c_str(), NULL, REG_BINARY, reinterpret_cast<LPBYTE>(&data), size);
								if (error != ERROR_SUCCESS)
								{
									bus.post("reg_set_failed", &error);
								}
							}
						}

						/**
						 * \brief 此部分写于2023/9/25
						 * \brief 此函数可以在注册表创建一个键值
						 *
						 * \param hkey 句柄
						 * \param subkey 键值名称
						 * \return 返回指向这个键值的句柄
						 */
						HKEY addKey(HKEY hkey, const std::string& subkey)
						{
							HKEY Handle{};
							if (hkey && !subkey.empty())
							{
								LSTATUS error = RegCreateKeyA(hkey, subkey.c_str(), &Handle);
								if (error != ERROR_SUCCESS)
								{
									if (error == ERROR_ACCESS_DENIED)
									{
										PrintError("无法访问，请检查权限");
										return nullptr;
									}
									PrintError(formatWindowsErrorMessage(error));
									return nullptr;
								}
							}
							else
							{
								LibError(std::invalid_argument("无法接受此参数"));
								return nullptr;
							}
							return Handle;
						}

						/**
						 * \brief 此部分写于2023/9/25
						 * \brief 重载版本.
						 * \brief 此函数可以在注册表创建一个键值
						 * \brief 批注
						 * \brief 此重载版本使用对象保存的句柄操作.
						 *
						 * \param subkey 键值名称
						 * \return 返回指向这个键值的句柄
						 */
						inline HKEY addKey(const std::string& subkey)
						{
							if (subkey.empty())
							{
								LibError(std::invalid_argument("无法接受此参数"));
								return nullptr;
							}
							HKEY handle{};
							if (!currentHandle)
							{
								LibError(std::runtime_error("不允许对象使用空句柄"));
								return nullptr;
							}
							HKEY Handle = addKey(currentHandle, subkey.c_str());
							return Handle;
						}

						/**
						 * \brief 此部分写于2023/9/24.
						 * \brief 此函数将注册表句柄下的子键复制到对应键对应的句柄.
						 * \brief 批注：
						 * \brief 此函数采用事件系统，总共3个事件
						 * \brief reg_copy_accessDenied 拒绝访问，传参：DWORD类型变量地址，数据为Windows函数错误代码
						 * \brief reg_copy_failed 复制失败，传参：DWORD类型变量地址，数据为Windows函数错误代码
						 * \brief reg_copy_success 成功复制，无传参
						 *
						 * \param source 源句柄
						 * \param from 键的名称,此参数可以为空。
						 * \param to 目标句柄
						 */
						void copyReg(HKEY source, const std::string& from, HKEY to)
						{
							EventBus bus;
							if (!source || !to)
							{
								//在检查到参数无效时，我们委托LibError转发错误，它通过宏检查是否抛异常还是抛出exception
								LibError(std::invalid_argument("无效参数"));
								return;
							}
							LSTATUS error = RegCopyTreeA(source, from.c_str(), to);
							if (error != ERROR_SUCCESS)
							{
								PrintError(formatWindowsErrorMessage(error));
								if (error == ERROR_ACCESS_DENIED)
								{
									bus.post("reg_copy_accessDenied", &error);
									return;
								}
								bus.post("reg_copy_failed", &error);
								return;
							}
							bus.post("reg_copy_success");
						}

						/**
						 * \brief 此部分写于2023/9/24.
						 * \brief 重载版本
						 * \brief 此函数将注册表句柄下的子键复制到对应键对应的句柄.
						 * \brief 批注：
						 * \brief 此函数采用事件系统，总共3个事件
						 * \brief reg_copy_accessDenied 拒绝访问，传参：DWORD类型变量地址，数据为Windows函数错误代码
						 * \brief reg_copy_failed 复制失败，传参：DWORD类型变量地址，数据为Windows函数错误代码
						 * \brief reg_copy_success 成功复制，无传参
						 * \brief 此重载版本使用对象储存的句柄来工作
						 *
						 * \param from 键的名称,此参数可以为空。
						 * \param to 目标句柄
						 */
						inline void copyReg(const std::string& from, HKEY to)
						{
							copyReg(currentHandle, from, to);
						}

						/**
						 * \brief 此内容写于2023/9/25.
						 * \brief 将对应键值的数据返回给用户
						 * \brief 如果键值的数据无法识别，会抛出错误
						 * \brief 得到的数据中，Binary和QWORD都会进行格式化
						 *
						 * \param query 要查询的键值
						 * \param Type 用于接收的类型（可选）
						 * \return 返回这个键值对应的数据
						 */
						std::string getValue(const std::string& query, DWORD* Type = nullptr) const
						{
							LSTATUS error{};
							DWORD type{}, dwBufLen = 255;
							std::string ret;
							if (currentHandle)
							{
								error = RegQueryValueExA(currentHandle, query.c_str(), NULL, &type, NULL, NULL);
								if (error == ERROR_SUCCESS)
								{
									std::size_t size = MAX_PATH;
									if (type == REG_BINARY)
									{
										std::unique_ptr<char[]> Binary = std::make_unique<char[]>(MAX_PATH);
										error = RegQueryValueExA(currentHandle, query.c_str(), NULL, &type, (LPBYTE)Binary.get(), &dwBufLen);
										if (error != ERROR_SUCCESS)
										{
											Binary.release();
											std::string message = formatWindowsErrorMessage(error);
											LibError(std::runtime_error(message));
										}
										CStringA cstr;
										for (DWORD i = 0; i < dwBufLen; i++)
										{
											cstr.Empty();
											char buffer[MAX_PATH]{ 0 };
											UINT temp = 0;
											DWORD dwData = Binary[i];
											while (dwData > 0)
											{
												temp = dwData % 16;
												if (temp < 10)
												{
													cstr.AppendChar(temp + '0');
												}
												else
												{
													cstr.AppendChar('a' + temp - 10);
												}
												dwData = dwData >> 4;
											}
											cstr.AppendChar('0');
											cstr.AppendChar('0');
											cstr.MakeReverse();
											ret += cstr.Right(2) + " ";
										}
										Binary.release();
									}
									else if (type == REG_DWORD)
									{
										DWORD Dword{ 0 };
										error = RegQueryValueExA(currentHandle, query.c_str(), NULL, &type, (LPBYTE)&Dword, &dwBufLen);
										if (error != ERROR_SUCCESS)
										{
											std::string message = formatWindowsErrorMessage(error);
											LibError(std::runtime_error(message));
										}
										ret = std::to_string(Dword);
									}
									else if (type == REG_SZ || type == REG_EXPAND_SZ)
									{
										std::unique_ptr<char[]> reg_sz = std::make_unique<char[]>(MAX_PATH);
										error = RegQueryValueExA(currentHandle, query.c_str(), NULL, &type, (LPBYTE)reg_sz.get(), &dwBufLen);
										if (error != ERROR_SUCCESS)
										{
											std::string message = formatWindowsErrorMessage(error);
											LibError(std::runtime_error(message));
										}
										ret = reg_sz.get();
										reg_sz.release();
									}
									else if (type == REG_QWORD)
									{
										std::unique_ptr<char[]> Qword = std::make_unique<char[]>(MAX_PATH);
										error = RegQueryValueExA(currentHandle, query.c_str(), NULL, &type, (LPBYTE)Qword.get(), &dwBufLen);
										if (error != ERROR_SUCCESS)
										{
											std::string message = formatWindowsErrorMessage(error);
											LibError(std::runtime_error(message));
										}
										CStringA cstr;
										size_t i = 0;
										for (i = 0; i < dwBufLen; i++)
										{
											cstr.Empty();
											cstr.Format("%hx", Qword[i]);
											ret += cstr + " ";
										}
									}
									else if (type == REG_MULTI_SZ)
									{
										std::unique_ptr<char[]> Muti = std::make_unique<char[]>(MAX_PATH);
										error = RegQueryValueExA(currentHandle, query.c_str(), NULL, &type, (LPBYTE)Muti.get(), &dwBufLen);
										if (error != ERROR_SUCCESS)
										{
											std::string message = formatWindowsErrorMessage(error);
											LibError(std::runtime_error(message));
										}
										ret = Muti.get();
										Muti.release();
									}
									else
									{
										LibError(std::runtime_error("读取到未支持的数据类型"));
									}
									if (Type)
									{
										*Type = type;
									}
									/* 我们把这个键值的类型赋值给指针指向的变量 */
								}
							}
							return ret;
						}

						/**
						 * \brief 此部分写于2023/9/24.
						 * \brief 关闭当前对象存储的键值.
						 * \brief 注意：此对象保存的句柄如果已经被Close,而另一个句柄已经被Close的时候，可能会发生异常.
						 * \brief 如果你希望在closekey调用的时候不出现异常，可以不使用RegCloseKey，而是让析构函数调用这个函数清理.
						 */
						void closeKey() noexcept
						{
							try
							{
								if (currentHandle)
								{
									RegCloseKey(currentHandle);
								}
							}
							catch (...)
							{
								return;
							}
						}

						/**
						 * \brief 此部分写于2023/9/24.
						 * \brief 获取一个句柄
						 *
						 * \param PreDefH 预定义句柄
						 * \param subkey 子键
						 * \return
						 */
						static HKEY getHandle(HKEY PreDefH, const std::string& subkey)
						{
							if (PreDefH)
							{
								HKEY handle{};
								LSTATUS error = RegOpenKeyExA(PreDefH, subkey.c_str(), NULL, KEY_ALL_ACCESS, &handle);
								if (error != ERROR_SUCCESS)
								{
									error = RegOpenKeyExA(PreDefH, subkey.c_str(), NULL, KEY_READ, &handle);
									if (error != ERROR_SUCCESS)
									{
										error = RegOpenKeyExA(PreDefH, subkey.c_str(), NULL, KEY_QUERY_VALUE, &handle);
										if (error != ERROR_SUCCESS)
										{
											PrintError(formatWindowsErrorMessage(error));
											return nullptr;
										}
									}
								}
								return handle;
							}
							else
							{
								LibError(std::invalid_argument("不应为空句柄"));
								return nullptr;
							}
						}

						/**
						 * .
						 */
						void flushKey()
						{
							if (!this)
							{
								return;
							}
							RegFlushKey(currentHandle);
						}

					private:
						HKEY currentHandle = nullptr;
					};
				}

				inline namespace Event
				{
					class WindowsHookA : public cloudgameZero::Foundation::Warpper::Basic_WindowsHook
					{
					public:
						virtual ~WindowsHookA()
						{
							endHook();
						}

						/**
						 * \brief 此部分写于2023/10/05.
						 * \brief 将HOOK安装到线程中监听.
						 *
						 * \param InstallType 取自InstallHookType中的枚举，要安装的HOOK回调的类型
						 */
						virtual void startHook(InstallHookType InstallType) throw() override
						{
							std::unique_lock lock(mtx);
							if (this->HOOKPROC_FUN == nullptr)
							{
								LibError(std::runtime_error("回调不能为空"));
							}
							if (!Module)
							{
								setModule();
							}
							if (this->Id == 0)
							{
								setThreadId();
							}
							if (!running)
							{
								thread = std::jthread(
									[this, InstallType]()
									{
										Handle = SetWindowsHookExA((int)InstallType, HOOKPROC_FUN, Module, Id);
										if (!Handle)
										{
											LibError(std::runtime_error("无法成功安装HOOK"));
										}
										MSG Msg{};
										running = true;
										while (GetMessageA(&Msg, NULL, NULL, NULL) > 0)
										{
											TranslateMessage(&Msg);
											DispatchMessageA(&Msg);
										}
									}
								);
							}
						}
						/* End */
					};
					/* WindowsHookA */

					class WindowsHookW : public cloudgameZero::Foundation::Warpper::Basic_WindowsHook
					{
					public:
						virtual ~WindowsHookW()
						{
							endHook();
						}

						/**
						 * \brief 此部分写于2023/10/05.
						 * \brief 将HOOK安装到线程中监听.
						 *
						 * \param InstallType 取自InstallHookType中的枚举，要安装的HOOK回调的类型
						 */
						virtual void startHook(InstallHookType InstallType) throw() override
						{
							std::unique_lock lock(mtx);
							if (this->HOOKPROC_FUN == nullptr)
							{
								LibError(std::runtime_error("回调不能为空"));
							}
							if (!Module)
							{
								setModule();
							}
							if (!Id)
							{
								setThreadId();
							}
							if (!running)
							{
								thread = std::jthread(
									[this, InstallType]()
									{
										Handle = SetWindowsHookExW((int)InstallType, HOOKPROC_FUN, Module, Id);
										if (!Handle)
										{
											LibError(std::runtime_error("无法成功安装HOOK"));
										}
										running = true;
										MSG Msg{};
										while (GetMessageW(&Msg, NULL, NULL, NULL) > 0)
										{
											TranslateMessage(&Msg);
											DispatchMessageW(&Msg);
										}
									}
								);
							}
						}
					};
					/* WindowsHookW */

				}
			}
		}

		class logConfig
		{
		public:
			enum class _ostream
			{
				reserved,
				cerr,
				cout,
				clog
			};
			enum class _wostream
			{
				reserved,
				wcerr,
				wcout,
				wclog
			};

			~logConfig() = default;

			void InitConfig(std::string filename)
			{
				try
				{
					if (_isInit)
					{
						return;
					}
					parseHelper(filename);
				}
				catch (...)
				{
					genDefaultSettings(filename);
					parseHelper(filename);
				}
				try
				{
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
				try
				{
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
					if (std::regex_search(tmp, fmt, pattern))
					{
						std::string format = fmt.str();
						if (format == "${APPDATA}" || format == "${appdata}")
						{
							varible = cloudgameZero::Foundation::Tool::function::GetEnvironmentVariableA("APPDATA");
						}
						else if (format == "${userprofile}" || format == "${USERPROFILE}")
						{
							varible = cloudgameZero::Foundation::Tool::function::GetEnvironmentVariableA("userprofile");
						}
						else if (format == "${LOCAL}" || format == "${local}")
						{
							varible = cloudgameZero::Foundation::Tool::function::GetEnvironmentVariableA("userprofile");
							varible += "\\APPDATA\\Local";
						}
						else if (format == "${TEMP}" || format == "${TMP}")
						{
							varible = cloudgameZero::Foundation::Tool::function::GetEnvironmentVariableA("temp");
						}
						else if (format == "${format}" || format == "${}")
						{
							varible = cloudgameZero::Foundation::Tool::function::GetEnvironmentVariableA("APPDATA");
						}
						else
						{
							LibError(std::exception("无法找到环境变量，请问您设置的字符串格式化是否正确?"));
						}
						if (std::string _str = std::regex_replace(tmp, regex, varible); !_str.empty()) {
							str = _str;
							return;
						}
						else
						{
							LibError(std::runtime_error("无法替换正则"));
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
				try
				{
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
				try
				{
					static const std::map<std::string, int> levels = {
						{"trace",1},
						{"debug",2},
						{"info", 3},
						{"warn", 4},
						{"error",5},
						{"fatal",6}
					};
					std::string find = this->_root["outToTerminal"]["rootLogger"]["level"].GetString();
					std::ranges::transform(find, find.begin(), ::tolower);
					auto it = levels.find(find);
					CLOUDGAMEFIX_ASSERT(it != levels.end());
					return it->second;
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
				try
				{
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
				try
				{
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
				if (filename.empty())
				{
					LibError(std::invalid_argument("文件名不能为空"));
				}
				/* 开始构建Document */
				rapidjson::Document Dom;
				rapidjson::StringBuffer sb;
				rapidjson::PrettyWriter pw(sb);
				Dom.Parse(Infomation::logconfig_json.data());
				if(!IS_DEBUG) Dom["outToTerminal"]["rootLogger"]["level"].SetString("Info");
				Dom.Accept(pw);
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
					else
					{
						f.close();
						f.open(filename, std::ios::out | std::ios::trunc);
					}
				}
				else
					f.open(filename, std::ios::out | std::ios::trunc);
				if (!f.is_open())
					LibError(std::runtime_error("无法打开文件"));
				f << sb.GetString();
				f.close();
			}

			void saveSettings(std::string_view filename)
			{
				auto& Dom = this->_root;
				if (Dom.IsNull())
					return;
				rapidjson::StringBuffer sb;
				rapidjson::PrettyWriter pw(sb);
				Dom.Accept(pw);
				std::fstream f;
				if (std::filesystem::exists(filename.data()))
				{
					f.open(filename, std::ios::in);
					f.peek();
					if (f.eof())
					{
						f.close();
						std::cout << "检测到空文件\n";
						f.open(filename, std::ios::app);
					}
					else
					{
						f.close();
						f.open(filename, std::ios::out | std::ios::trunc);
					}
				}
				else
				{
					f.open(filename, std::ios::out | std::ios::trunc);
				}
				if (!f.is_open())
				{
					LibError(std::runtime_error("无法打开文件"));
				}
				f << sb.GetString();
				f.close();
			}

		private:
			bool parseHelper(std::string filename)
			{
				if (filename.empty())
				{
					LibError(std::invalid_argument("字符串不能为空"));
				}
				std::ifstream reader(filename);
				if (!reader.is_open())
				{
					LibError(std::invalid_argument("无法打开文件"));
				}
				reader >> std::noskipws;
				std::string json_content((std::istream_iterator<char>(reader)), std::istream_iterator<char>());
				reader.close();
				if (!this->_root.Parse(json_content.c_str()).HasParseError())
				{
					return true;
				}
				else
				{
					LibError(std::exception("无法解析json"));
					return false;
				}
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

		template<typename type>
		concept string = std::is_same_v<type, char> || std::is_same_v<type, wchar_t>;

		template<string type>
		struct msg
		{
			constexpr msg() noexcept = default;
			constexpr msg(msg&& other) noexcept = default;
			constexpr msg(Infomation::level level, std::basic_string_view<type> msg) : level(level), _msg(msg)
			{
			}
			Infomation::level level{};
			std::basic_string_view<type> _msg{};
			std::basic_string<type> buffer{};
		};

		template<string type>
		class zeroLogT
		{
		public:
			/**
			 * \brief 此部分写于2023/8/12
			 * \brief 日志类构造函数.
			 *
			 * \param init 决定是否在构造期间初始化
			 * \param file 决定日志使用的配置文件名
			 * \param CallBack 可选，如果希望在运行阶段修改配置，此处应提供一个函数用于回调，它将以引用方式进行传递，如果不希望使用请指定其为nullptr
			 * \param 委托原型： typedef void(__stdcall* logConfCallBackFunc)(rapidjson::Document& Dom);
			 * \param mark 用于标记日志来源（可选，表示输出的来源）
			 * \param server 用于标记模块（可选，表示模块名）
			 */
			explicit zeroLogT(
				_In_opt_ std::string_view profile,
				_In_opt_ std::string_view mark = "main",
				_In_opt_ std::string_view server = "ZERO",
				_In_opt_ delegate<void, rapidjson::Document&> CallBack = nullptr
			) : times(NULL), mark(mark), server(server), time(NULL)
			{
				fs.imbue(std::locale("chs"));
				EventBus bus;
				auto mainKey = Infomation::regMark.find(mark.data());
				if (mainKey == Infomation::regMark.end()) {
					Infomation::regMark.insert({ mark.data(),{server.data()} });
				}
				else
				{
					auto it = mainKey->second.find(server.data());
					if (it != mainKey->second.end())
					{
						PrintError("无法注册对象，因为每个模块是独立的，除非拿到那个模块名称的日志对象被关闭或者被析构!");
						bus.post("registry_object_failed");
						return;
					}
					mainKey->second.insert(server.data());
				}
				conf = std::make_unique<Foundation::logConfig>();
				if (!std::filesystem::exists(profile))
				{
					DEBUG_MESSAGE("未找到配置文件\n准备生成一个默认配置");
					conf->InitConfig(profile.data());
					if (CallBack)
						CallBack(conf->getDocment());
				}
				conf->InitConfig(profile.data());
				if (CallBack)
					CallBack(conf->getDocment());
				if(conf->getDocment()["Save"].GetBool())
					conf->saveSettings(profile);
				this->minLevel = conf->getMin();
				init();
			}

			using message = msg<type>;


			/**
			 * Each log class object is a unique instance, so the empty argument and copy constructs and assignment operators will not be provided to the user.
			 */
			zeroLogT() = delete;
			zeroLogT& operator=(zeroLogT<type>& other) = delete;
			zeroLogT(zeroLogT<type>& other) = delete;

			~zeroLogT()
			{
				this->close();
			}

			void init()
			{
				using namespace Foundation;
				using namespace Foundation::Tool;
				rapidjson::Document& Dom = conf->getDocment();
				if (this->hasInit())
				{
					DEBUG_MESSAGE("这个实例已经被初始化过了");
					return;
				}
				if (!Dom["logToFile"]["Enable"].GetBool() && !Dom["logToFile"]["Enable"].GetBool())
				{
					DEBUG_MESSAGE("为什么你要在两者都不启用的情况下进行初始化，请问这是否是有意而为之?");
					return;
				}
				if (Dom["logToFile"]["Enable"].GetBool())
				{
					do {
						std::string dict;
						if (this->file.empty())
						{
							conf->getLogDictionary(dict);
							if (!std::filesystem::exists(dict))
								std::filesystem::create_directories(dict);
							std::string filename = conf->parseFileName();
							dict += filename;
						}
						else
							dict = this->file;
						if (Dom["logToFile"]["append"].GetBool())
							fs.open(dict, std::ios::app);
						else
							fs.open(dict, std::ios::out);
						if (!fs.is_open())
							throw std::runtime_error("无法打开文件，出现了异常");
						this->file = dict;
						this->EnableFileOut = true;
					} while (false);
				}
				if (Dom["outToTerminal"]["Enable"].GetBool())
				{
					this->EnableTerminalOut = true;
				}
				this->logTimeFormat = Dom["logFormatTime"].GetString();
				this->render = Dom["outToTerminal"]["render"].GetBool();
				this->cleanBuffer = Dom["outToTerminal"]["rootLogger"]["cleanBuffer"]["clean"].GetBool();
				this->times = Dom["outToTerminal"]["rootLogger"]["cleanBuffer"]["times"].GetUint();
				this->showUser = Dom["outToTerminal"]["showUser"].GetBool();
				this->EnableThreadSecurity = Dom["EnableThreadSecurity"].GetBool();
				this->has_init = true;
			}

			inline const bool hasInit() noexcept
			{
				return this->has_init;
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

			/**
			 * \brief 此内容写于2023/8/13.
			 * \brief 打印等级为Trace的日志
			 *
			 * \param message 消息内容
			 */
			void trace(const std::basic_string_view<type> message) throw()
			{
				using namespace Infomation;
				static level lev = Trace;
				//Here we enable thread locks to prevent resource contention issues
				std::unique_lock<std::mutex> lock(this->mutex);
				if (!this->hasInit())
					//We check if the object is initialized, and if not, we initialize it for it
					this->init();
				//Here we generate a log and forward it to the write method to print out the log messages
				auto logs = this->makeLogs(lev, message.data());
				this->write(lev, logs);
			}

			/**
			 * \brief 此内容写于2023/8/13.
			 * \brief 格式化日志消息并打印等级为Trace的日志
			 *
			 * \param fmt 要格式化的内容
			 * \param ...args 要格式化的参数
			 */
			template<typename... Args>
			void trace(const std::basic_string_view<type> fmt, Args... args) throw()
			{
				using namespace Infomation;
				static level lev = Trace;
				if (!this->hasInit())
					//We check if the object is initialized, and if not, we initialize it for it
					this->init();
				std::unique_lock<std::mutex> lock(this->mutex);
				//Here we make a format strings then generate a log and forward it to the write method to print out the log messages
				auto alraedy = Infomation::makeFormat(fmt, args...);
				auto logs = this->makeLogs(lev, alraedy);
				this->write(lev, logs);
			}

			/**
			 * \brief 此内容写于2023/8/13.
			 * \brief 打印等级为debug的日志
			 *
			 * \param message 消息内容
			 */
			void debug(const std::basic_string_view<type> message) throw()
			{
				using namespace Infomation;
				static level lev = Debug;
				//Here we enable thread locks to prevent resource contention issues
				std::unique_lock<std::mutex> lock(this->mutex);
				if (!this->hasInit())
					//We check if the object is initialized, and if not, we initialize it for it
					this->init();
				//Here we generate a log and forward it to the write method to print out the log messages
				auto logs = this->makeLogs(lev, message.data());
				this->write(lev, logs);
			}

			/**
			 * \brief 此内容写于2023/8/13.
			 * \brief 格式化日志消息并打印等级为debug的日志
			 *
			 * \param fmt 要格式化的内容
			 * \param ...args 要格式化的参数
			 */
			template<typename... Args>
			void debug(const std::basic_string_view<type> fmt, Args... args) throw()
			{
				using namespace Infomation;
				static level lev = Debug;
				if (!this->hasInit())
					//We check if the object is initialized, and if not, we initialize it for it
					this->init();
				std::unique_lock<std::mutex> lock(this->mutex);
				//Here we make a format strings then generate a log and forward it to the write method to print out the log messages
				auto alraedy = Infomation::makeFormat(fmt, args...);
				auto logs = this->makeLogs(lev, alraedy);
				this->write(lev, logs);
			}

			/**
			 * \brief 此内容写于2023/8/13.
			 * \brief 打印等级为Info的日志
			 *
			 * \param message 消息内容
			 */
			void info(const std::basic_string_view<type> message) throw()
			{
				using namespace Infomation;
				static level lev = Info;
				//Here we enable thread locks to prevent resource contention issues
				std::unique_lock<std::mutex> lock(this->mutex);
				if (!this->hasInit())
					//We check if the object is initialized, and if not, we initialize it for it
					this->init();
				//Here we generate a log and forward it to the write method to print out the log messages
				auto logs = this->makeLogs(lev, message.data());
				this->write(lev, logs);
			}

			/**
			 * \brief 此内容写于2023/8/13.
			 * \brief 格式化日志消息并打印等级为Info的日志
			 *
			 * \param fmt 要格式化的内容
			 * \param ...args 要格式化的参数
			 */
			template<typename... Args>
			void info(const std::basic_string_view<type> fmt, Args... args) throw()
			{
				using namespace Infomation;
				static level lev = Info;
				if (!this->hasInit())
					//We check if the object is initialized, and if not, we initialize it for it
					this->init();
				std::unique_lock<std::mutex> lock(this->mutex);
				//Here we make a format strings then generate a log and forward it to the write method to print out the log messages
				auto alraedy = Infomation::makeFormat(fmt, args...);
				auto logs = this->makeLogs(lev, alraedy);
				this->write(lev, logs);
			}

			/**
			 * \brief 此内容写于2023/8/13.
			 * \brief 打印等级为Warn的日志
			 *
			 * \param message 消息内容
			 */
			void warn(const std::basic_string_view<type> message) throw()
			{
				using namespace Infomation;
				static level lev = Warn;
				//Here we enable thread locks to prevent resource contention issues
				std::unique_lock<std::mutex> lock(this->mutex);
				if (!this->hasInit())
					//We check if the object is initialized, and if not, we initialize it for it
					this->init();
				//Here we generate a log and forward it to the write method to print out the log messages
				auto logs = this->makeLogs(lev, message.data());
				this->write(lev, logs);
			}

			/**
			 * \brief 此内容写于2023/8/13.
			 * \brief 格式化日志消息并打印等级为Warn的日志
			 *
			 * \param fmt 要格式化的内容
			 * \param ...args 要格式化的参数
			 */
			template<typename... Args>
			void warn(const std::basic_string_view<type> fmt, Args... args) throw()
			{
				using namespace Infomation;
				static level lev = Warn;
				if (!this->hasInit())
					//We check if the object is initialized, and if not, we initialize it for it
					this->init();
				std::unique_lock<std::mutex> lock(this->mutex);
				//Here we make a format strings then generate a log and forward it to the write method to print out the log messages
				auto alraedy = Infomation::makeFormat(fmt, args...);
				auto logs = this->makeLogs(lev, alraedy);
				this->write(lev, logs);
			}

			/**
			 * \brief 此内容写于2023/8/13.
			 * \brief 打印等级为Error的日志
			 *
			 * \param message 消息内容
			 */
			void error(const std::basic_string_view<type> message) throw()
			{
				using namespace Infomation;
				static level lev = Infomation::Error;
				//Here we enable thread locks to prevent resource contention issues
				std::unique_lock<std::mutex> lock(this->mutex);
				if (!this->hasInit())
					//We check if the object is initialized, and if not, we initialize it for it
					this->init();
				//Here we generate a log and forward it to the write method to print out the log messages
				auto logs = this->makeLogs(lev, message.data());
				this->write(lev, logs);
			}

			/**
			 * \brief 此内容写于2023/8/13.
			 * \brief 格式化日志消息并打印等级为Error的日志
			 *
			 * \param fmt 要格式化的内容
			 * \param ...args 要格式化的参数
			 */
			template<typename... Args>
			void error(const std::basic_string_view<type> fmt, Args... args) throw()
			{
				using namespace Infomation;
				static level lev = Infomation::Error;
				if (!this->hasInit())
					//We check if the object is initialized, and if not, we initialize it for it
					this->init();
				std::unique_lock<std::mutex> lock(this->mutex);
				//Here we make a format strings then generate a log and forward it to the write method to print out the log messages
				auto alraedy = Infomation::makeFormat(fmt, args...);
				auto logs = this->makeLogs(lev, alraedy);
				this->write(lev, logs);
			}

			/**
			 * \brief 此内容写于2023/8/13.
			 * \brief 打印等级为Fatal的日志
			 *
			 * \param message 消息内容
			 */
			void fatal(const std::basic_string_view<type> message) throw()
			{
				using namespace Infomation;
				static level lev = Fatal;
				//Here we enable thread locks to prevent resource contention issues
				std::unique_lock<std::mutex> lock(this->mutex);
				if (!this->hasInit())
					//We check if the object is initialized, and if not, we initialize it for it
					this->init();
				//Here we generate a log and forward it to the write method to print out the log messages
				auto logs = this->makeLogs(lev, message.data());
				this->write(lev, logs);
			}

			/**
			 * \brief 此内容写于2023/8/13.
			 * \brief 格式化日志消息并打印等级为Fatal的日志
			 *
			 * \param fmt 要格式化的内容
			 * \param ...args 要格式化的参数
			 */
			template<typename... Args>
			void fatal(const std::basic_string_view<type> fmt, Args... args) throw()
			{
				using namespace Infomation;
				static level lev = Fatal;
				if (!this->hasInit())
					//We check if the object is initialized, and if not, we initialize it for it
					this->init();
				std::unique_lock<std::mutex> lock(this->mutex);
				//Here we make a format strings then generate a log and forward it to the write method to print out the log messages
				auto alraedy = Infomation::makeFormat(fmt, args...);
				auto logs = this->makeLogs(lev, alraedy);
				this->write(lev, logs);
			}

			static friend inline zeroLogT<type>& operator<<(zeroLogT<type>& object, const message&& msg) throw()
			{
				using namespace Infomation;
				//Here we enable thread locks to prevent resource contention issues
				std::unique_lock<std::mutex> lock(this->mutex);
				if (!object.hasInit())
					//We check if the object is initialized, and if not, we initialize it for it
					object.init();
				/* Create a temporary variable to accept log information returned from makeLogs in the zeroLogT<type> instance object */
				std::basic_string<type> logs;
				if (msg.level == Reserved)
					//For Reserved, we treat it as Info, because Reserved has no value and is used only to filter log messages
					logs = this->makeLogs(Info, msg._msg.data());
				else
					logs = this->makeLogs(msg.level, msg._msg.data());
				object.write(msg.level == Reserved ? Info : msg.level, logs);
				//Here we call the write method in the instance object of zeroLogT<type>. At the log level, we use a ternary expression to process Reserved information and then write out the log information
				return object; //Finally, we return a reference to the object
			}

			static friend inline zeroLogT<type>& operator>>(zeroLogT<type>& object, msg<type>& msg) throw()
			{
				using namespace Infomation;
				//Here we enable thread locks to prevent resource contention issues
				std::unique_lock<std::mutex> lock(this->mutex);
				if (!object.hasInit())
					//We check if the object is initialized, and if not, we initialize it for it
					object.init();
				if (msg.level == Reserved)
					//For Reserved, we treat it as Info, because Reserved has no value and is used only to filter log messages
					msg.buffer = object.makeLogs(Info, msg._msg.data());
				else
					msg.buffer = object.makeLogs(msg.level, msg._msg.data());
					//When we get the log information, we directly assign it to the msg buffer
				return object; //Finally, we return a reference to the object
			}

			void stackTrace()
			{
				using namespace Infomation;
				using namespace Foundation::Tool;
				//Here we enable thread locks to prevent resource contention issues
				std::unique_lock<std::mutex> lock(this->mutex);
				if (!this->hasInit())
					//We check if the object is initialized, and if not, we initialize it for it
					this->init();
				std::string logs = this->makeLogs(Warn, std::format("\nHere Is The StackTrace's Content: \n{}", boost::stacktrace::to_string(boost::stacktrace::stacktrace())));
				this->write(Warn, logs);
			}

			inline void close()
			{
				if (!this->hasInit())
					return;
				this->has_init = false;
				auto it = Infomation::regMark.find(mark.data());
				/* 我们这里要做取消注册的工作 */
				if (it != Infomation::regMark.end())
					it->second.erase(server.data());
			}

		private:
			inline static void renderTerminal(Infomation::level levels)
			{
				using namespace Infomation;
				using CONSOLE = Foundation::Tool::CONSOLE;
				switch (levels)
				{
				case level::Trace:
					SetConsoleTextAttribute(CONSOLE_OUTPUT_HANDLE, (WORD)CONSOLE::CONSOLE_COLOR_BLUE | (WORD)CONSOLE::CONSOLE_COLOR_GREEN);
					break;
				case level::Info:
					break;
				case level::Debug:
					SetConsoleTextAttribute(CONSOLE_OUTPUT_HANDLE, (WORD)CONSOLE::CONSOLE_COLOR_GREEN);
					break;
				case level::Warn:
					SetConsoleTextAttribute(CONSOLE_OUTPUT_HANDLE, (WORD)CONSOLE::CONSOLE_COLOR_YELLOW);
					break;
				case level::Error:
					SetConsoleTextAttribute(CONSOLE_OUTPUT_HANDLE, (WORD)CONSOLE::CONSOLE_COLOR_LIGHTRED);
					break;
				case level::Fatal:
					SetConsoleTextAttribute(CONSOLE_OUTPUT_HANDLE, (WORD)CONSOLE::CONSOLE_COLOR_RED);
					break;
				}
			}

			inline std::basic_string<type> makeLogs(Infomation::level report, std::basic_string<type> already)
			{
				using namespace Infomation;
				using namespace Foundation::Tool;
				using namespace Foundation::Tool::function;
				if constexpr (std::is_same_v<type, char>)
				{
					std::basic_string<type> logs = "{} [{}/{}]: {} {} {}"_zF(
						makeTimeStr(this->logTimeFormat),
						this->mark.data(),
						getMappingIndex(report),
						strcmp(this->mark.data(), "main") ? std::format("[{}]", this->server) : "",
						this->showUser ? Foundation::Tool::function::GetUserA() : "",
						already
					);
					return logs;
				}
				else if constexpr (std::is_same_v<type, wchar_t>)
				{
					std::basic_string<type> logs = L"{} [{}/{}]: {} {} {}"_zWF(
						MutiToWide(makeTimeStr(this->logTimeFormat)),
						MutiToWide(this->mark.data()),
						MutiToWide(getMappingIndex(report)),
						MutiToWide(strcmp(this->mark.data(), "main") ? std::format("[{}]", this->server) : ""),
						this->showUser ? Foundation::Tool::function::GetUserW() : L"",
						already
					);
					return logs;
				}
			}

			inline LPCSTR getMappingIndex(Infomation::level report)
			{
				using namespace Infomation;
				switch (report)
				{
				case level::Trace:
					return "TRACE";
				case level::Info:
					return "INFO";
				case level::Debug:
					return "DEBUG";
				case level::Warn:
					return "WARN";
				case level::Error:
					return "ERROR";
				case level::Fatal:
					return "FATAL";
				}
				return "\0";
			}

			inline void write(Infomation::level report, std::basic_string<type> logs)
			{
				// Check if the specified log level meets the minimum log level requirement.
				using namespace Infomation;
				if (this->minLevel > report)
					return;// If not, do not log the message and exit the function.
				// If terminal output is enabled, process the log message for terminal output.
				if (this->EnableTerminalOut)
				{
					// If rendering is required, call the 'renderTerminal' function.
					if (this->render)
						renderTerminal(report);
					// Write the log message to the terminal stream, depending on the character type.
					if constexpr (std::is_same_v<type, char>)
						std::cout << logs;
					else
					{
						std::locale old = std::wcout.imbue(Infomation::chs);
						std::wcout << logs;
						std::wcout.imbue(old);
					}
					// Control message separation in terminal output based on 'cleanBuffer' and 'times'.
					if (cleanBuffer && time < times) {
						std::wcout.put(L'\n');
						// If we don't need the actual number of cleanups to be less than the set number of cleanups, we just wrap the lines
						time++;
					}
					else if (cleanBuffer && time >= times) {
						// Simply clean up with std::endl, then reset it
						std::wcout << std::endl;
						time = 0;
					}
					else
						std::wclog.put(L'\n');
				}
				SetConsoleTextAttribute(CONSOLE_OUTPUT_HANDLE, (WORD)Foundation::Tool::CONSOLE::CONSOLE_COLOR_WHITE);
				if (this->EnableFileOut)
				{
					if constexpr (std::is_same_v<type, char>)
						fs << Tool::MutiToWide(logs) << "\n";
					else if constexpr (std::is_same_v<type, wchar_t>)
						fs << logs << "\n";
				}
			}

			int time;
			int minLevel;
			int times;
			bool render;
			bool has_init;
			bool EnableFileOut;
			bool EnableTerminalOut;
			bool cleanBuffer;
			bool showUser;
			bool EnableThreadSecurity;
			std::mutex mutex;
			std::string logTimeFormat;
			std::unique_ptr<Foundation::logConfig> conf;
			std::wfstream fs;
			std::string_view file;
			std::string_view mark;
			std::string_view server;
		};

		using zeroLogA = zeroLogT<char>;
		using zeroLogW = zeroLogT<wchar_t>;
		using msgA = zeroLogA::message;
		using msgW = zeroLogW::message;				
	}

	static inline Foundation::zeroLogA* CL(void)
	{
		static Foundation::zeroLogA INSTANCE("cloudgame_comp.json", "helper", "ZERO", [](rapidjson::Document& Dom) 
			{
				Dom["logToFile"]["File"]["filename"].SetString("${format}cloudgamefix_comp.log");
				Dom["Save"].SetBool(false);
			});
		return &INSTANCE;
	}

	#pragma endregion

	/* 所有来自cloudgamefixZero库定义的接口均来自此命名空间. */
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
		 * 用于修复网易云游戏系统的接口.
		 */
		MakeCloudgameInterface("5DD98957-02FC-4583-A25C-14A69321F2F0")
		cgFix : public IUnknown
		{
		public:
			enum class mode { cloudgame, cloudpc };
			virtual BOOL fixSystemRestriction() = 0;
			virtual void fixFileExt(_In_ mode mode) = 0;
			virtual void resetGroupPolicy() = 0;
			virtual HRESULT repairGameFile() = 0;
			virtual void fixUpdateFiles(_In_ std::string manifest, _In_opt_ BOOL useGetRequest = FALSE) = 0;
			virtual void fixUpdateService() = 0;
		};

		/* 相比cgFix，cgSystem提供了更多功能，同时支持查询cgFix接口，可以看作是对cgFix的强化版 */
		MakeCloudgameInterface("A3872F59-C8AF-467E-8BF5-DF19FB77149E")
		cgSystem : public cgFix
		{
		public:
			enum class Theme { Default, white, windows, flower };
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
			 * 从Windows主题中选择一个加载主题.
			 *
			 * \param theme 从Theme中的枚举量选择
			 */
			virtual void changeTheme(IN Theme theme) = 0;

			virtual bool changeServiceStartupType(_In_ std::string servicesName, _In_ DWORD startupType) = 0;

			virtual bool startService(_In_ std::string servicesName) = 0;

			virtual bool startService(_In_ std::string servicesName, _In_opt_ DWORD argc, _In_opt_ LPCSTR* argv) = 0;
		};

		MakeCloudgameInterface("46A0DDA0-A59A-4557-8F18-6F359CD9B3D8")
		cgToolA : public IUnknown
		{
		public:
			virtual HRESULT makeShortcut(_In_ const std::string_view target,_In_ const std::string_view save) = 0;
			
			virtual HRESULT startDownload(_In_ const std::string& url, _In_ const std::string save) = 0;
			
			virtual HRESULT getSpecialFolderLocation(_In_ int cisdl,_Out_ std::string& out) = 0;
		};

		MakeCloudgameInterface("4C5CCB25-C16D-49DF-AB82-DC47CBBFFAD7")
		cgToolW : public IUnknown
		{
		public:
			virtual HRESULT makeShortcut(_In_ const std::wstring_view target,_In_ const std::wstring_view save) = 0;
			
			virtual HRESULT startDownload(_In_ const std::wstring& url,_In_ const std::wstring save) = 0;

			virtual HRESULT getSpecialFolderLocation(_In_ int cisdl,_Out_ std::wstring& out) = 0;
		};

		MakeCloudgameInterface("B3560A33-4427-4BD4-BA76-808C6FAA2442")
		repo
		{
		public:
			virtual int setRepoFilestream() = 0;
		};

		MakeCloudgameInterface("15DD4DD4-3E31-4F13-8E40-D88609D80B06")
		WinNotification : public IUnknown
		{
		public:
			
			virtual bool Init(_Out_opt_ ToastPlatform::Enums::ToastError * error = nullptr) = 0;
			virtual bool isInit() const = 0;
			virtual std::wstring const& getAppName() const = 0;
			virtual std::wstring const& getAppUserModelId() const = 0;
			virtual void setAppUserModelId(_In_ std::wstring const& aumi) = 0;
			virtual void setAppName(_In_ std::wstring const& AppName) = 0;
			virtual void setShortcutPolicy(_In_ ToastPlatform::Enums::ShortcutPolicy policy) = 0;
			virtual bool hide(_In_ INT64 id) = 0;

			/**
			 * 
			 * Shows a Toast notification.
			 * \param toast The ToastTemplate containing notification data.
			 * \param eventHandler The event handler for the notification.
			 * \param error Pointer to store error code if an error occurs.
			 * \return The ID of the displayed notification, or -1 if an error occurs.
			 */
			virtual INT64 show(_In_ ToastPlatform::API::ToastTemplate const& toast, _In_ ToastPlatform::API::ToastPlatformHandler* eventHandler, _In_opt_ ToastPlatform::Enums::ToastError* error = nullptr) = 0;

			
			virtual void clear() = 0;
		};

		/* 存储内部接口的声明 */
		namespace sigmaInterface
		{
			/* 存储子类重写的具体实现，所有cloudgameFixZero派生的cpp文件将在此命名空间声明自己的对应类 */
			namespace Implement
			{
				/* 
				这是一个用于派发实例的容器，键值通常为GUID，带{}，如: {XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX}
				而映射项为一个委托函数，委托函数应返回GUID对应实例的子类地址
				注：
				为了方便注册实例，在Interface命名空间下提供了registryInterface函数用于注册实例
				*/
				extern std::unordered_map<std::string, delegate<void*>> registry;

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
						}num{};
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

							std::size_t index = 0;
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
							if (!isBigEnd) 
							{
								for (int i = 0; i < 4; i++) k[i] = bigMode(k[i]);
							}
							WORD sub_group[80] = { 0 };
							WORD* temp_sub_group = (WORD*)(data);
							for (int j = 0; j < 80; j++) {
								if (j < 16)
								{
									sub_group[j] = temp_sub_group[j];
								}
								else 
								{
									WORD temp = sub_group[j - 3] ^ sub_group[j - 8] ^ sub_group[j - 14] ^ sub_group[j - 16];
									temp = isBigEnd ? temp : bigMode(temp);
									sub_group[j] = isBigEnd ? temp << 1 | temp >> 31 : bigMode(temp << 1 | temp >> 31);
								}
							}
							WORD a = A, b = B, c = C, d = D, e = E;
							for (int j = 0; j < 80; j++) 
							{
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

			/* 接口id，若调用cloudgameFixZero接口，请使用此id */
			inline namespace guid
			{
				extern const IID IID_CLOUDGAME_FIX_ZERO_IID_IcgFix;
				extern const IID IID_CLOUDGAME_FIX_ZERO_IID_IcgSystem;
				extern const IID IID_CLOUDGAME_FIX_ZERO_IID_IcgToolA;
				extern const IID IID_CLOUDGAME_FIX_ZERO_IID_IcgToolW;
				extern const IID IID_CLOUDGAME_FIX_ZERO_IID_IcgToolA_s;
				extern const IID IID_CLOUDGAME_FIX_ZERO_IID_IWinNotification;
				//extern "C++" const IID IID_CLOUDGAME_FIX_ZERO_CGTOOL;	/* cgTool接口ID */
				//extern "C++" const IID IID_CLOUDGAME_FIX_ZERO_CGTOOLS;	/* 设计用于安全功能的cgTool接口ID，与cgTool一起提供 */
				//extern "C++" const IID IID_CLOUDGAME_FIX_ZERO_CGSOFTWARE;	/* 设计基于cgTool安全功能的软件类接口 */
				//extern "C++" const IID IID_CLOUDGAME_FIX_ZERO_ASCIISTYLE;	/* ascii字符画预定义接口 */

				inline IUnknown* Query(_In_ const IID& iid)
				{
					LPOLESTR guid{};
					HRESULT hr = StringFromIID(iid, &guid);
					auto itr = Implement::registry.find(Foundation::Tool::WideToMuti(guid));
					if (itr == Implement::registry.end()) {
						return nullptr;
					}
					return static_cast<IUnknown*>(itr->second());
				}
			}
		}

		template<Infomation::__cginterface interfaceTy>
		static void registryInterface(_In_ const IID& iid)
		{
			using namespace Foundation::Tool;
			static EventBus bus;
			static HRESULT _hr = 0;
			LPOLESTR guid{};
			HRESULT hr = StringFromIID(iid, &guid);
			if (FAILED(hr)) {
				_hr = hr;
				bus.post("error_iid",&_hr);
				return;
			}
			if (sigmaInterface::Implement::registry.find(WideToMuti(guid)) != sigmaInterface::Implement::registry.end())
			{
				bus.post("iid_already_exists");
				return;
			}
			sigmaInterface::Implement::registry.insert({ WideToMuti(guid),[]() {return new interfaceTy; }});
		}

		template<Infomation::__cginterface interfaceTy>
		static void registryInterface(_In_ std::string guid)
		{
			using namespace Foundation::Tool;
			static EventBus bus;
			static HRESULT _hr = 0;
			bool notMatch = true;
			if (guid.size() != 38 || guid.size() != 36)
				return;
			if (std::regex_match(guid, std::regex(Infomation::Secutriy::guidRe.data())))
				notMatch = false;
			else if (std::regex_match(guid, std::regex(Infomation::Secutriy::guidReSec.data()))){
				guid = "{" + guid + "}";
				notMatch = false;
			}
			if (notMatch) 
			{
				bus.post("invalid_args");
				return;
			}
			if (sigmaInterface::Implement::registry.find(guid) != sigmaInterface::Implement::registry.end())
			{
				bus.post("iid_already_exists");
				return;
			}
			sigmaInterface::Implement::registry.insert({ guid,[]() {return new interfaceTy; } });
		}

		/**
		 * \brief This section was written on 2023/10/28.
		 * \brief Get the mapped cloudgamefix instance from the guid provided by the cloudgamefix library
		 *
		 * \param iid Interface provided by the guid namespace
		 * \param ppv Accepts a pointer to hold the address of the instance
		 * \return S_OK is returned on success, E_NOINTERFACE is returned if no interface is found, or some other error code is returned otherwise
		 */
		static HRESULT createInstance(_In_ const GUID iid, _Out_ void** ppv)
		{
			IUnknown* ptr = sigmaInterface::Query(iid);
			if (!ptr)
			{
				*ppv = nullptr;
				return E_NOINTERFACE; // No such interface is available.
			}
			HRESULT hr = ptr->QueryInterface(iid, ppv); // Query for the requested interface using QueryInterface method.
			if (FAILED(hr))
			{
				*ppv = nullptr;
				return hr; // Failed to obtain the requested interface.
			}
			reinterpret_cast<IUnknown*>(*ppv)->AddRef();// Increase the reference count of the obtained interface to manage its lifetime.
			ptr->Release();	// Release the initial IUnknown pointer to avoid memory leaks.
			return S_OK;	// Success, the interface has been created and is ready for use.
		}

		template<typename Ty>
		concept cloudgameInstance = std::is_abstract_v<Ty> && std::is_class_v<Ty> && std::is_base_of_v<IUnknown, Ty>;
		//To create an instance, an abstract class is required and it must be a derived class of the IUnknown class.

		/**
		 * \brief This section was writeen on 2023/10/28.
		 * \brief Create an instance by taking the guid of the class map
		 * 
		 * \param ppv Accepts a pointer to hold the address of the instance
		 * \return 
		 */
		template<cloudgameInstance Ty> requires requires(Ty T) { __uuidof(T); }
		inline HRESULT createInstance(_Out_ Ty** ppv)
		{
			return createInstance(__uuidof(Ty), (void**)ppv);
		}

		/**
		 * \brief This section was writeen on 2023/10/28.
		 * \brief Create an instance by taking the guid of the class map
		 *
		 * \param ppv Accepts a unique_ptr to hold the address of the instance
		 * \return
		 */
		template<cloudgameInstance Ty> requires requires(Ty T) { __uuidof(T); }
		inline HRESULT createInstance(_Out_ std::unique_ptr<Ty>& ppv)
		{
			return createInstance(__uuidof(Ty), (void**)&ppv);
		}

		/**
		 * \brief This section was writeen on 2023/10/28.
		 * \brief Create an instance by taking the guid of the class map
		 *
		 * \param ppv Accepts a shared_ptr to hold the address of the instance
		 * \return
		 */
		template<cloudgameInstance Ty> requires requires(Ty T) { __uuidof(T); }
		inline HRESULT createInstance(_Out_ std::shared_ptr<Ty>& ppv)
		{
			return createInstance(__uuidof(Ty), (void**)&ppv);
		}

		/**
		 * \brief This section was writeen on 2023/10/28.
		 * \brief Create an instance by taking the guid of the class map
		 *
		 * \param ppv Accepts a ComPtr to hold the address of the instance
		 * \return 
		 */
		template<cloudgameInstance Ty>
		inline HRESULT createInstance(_Out_ ComPtr<Ty>& ppv)
		{
			return createInstance(__uuidof(Ty), (void**)&ppv);
		}

		template<cloudgameInstance Ty> requires requires(Ty T){__uuidof(T);}
		inline HRESULT createInstance(_Out_ Foundation::cloudgamePtr<Ty>& ppv)
		{
			return createInstance(__uuidof(Ty), (void**)&ppv);
		}

		namespace factory
		{
			constexpr LPCSTR eventAlreadyExists = "mapping_already_exists";
			constexpr LPCSTR eventNotFound = "mapping_not_found";
			constexpr LPCSTR eventErrorInstance = "error_factory_instance";

			template<typename Ty, typename... Args>
			void registry(std::string mapping, Args... args)
			{
				static_assert(std::is_class_v<Ty>, "To register a factory, use a class, not a normal data type!");
				EventBus bus;
				if (Infomation::factoryMapping.find(mapping) != Infomation::factoryMapping.end()) {
					bus.post(eventAlreadyExists);
					return;
				}
				Infomation::factoryMapping.insert({ mapping,[]() -> void* {return new Ty(args...); } });
			}

			template<typename Ty>
			inline static Ty* getInstance(std::string mapping)
			{
				static_assert(std::is_class_v<Ty> && std::is_abstract_v<Ty>, "To get a factory instance, the accepted data type must be an abstract class!");
				EventBus bus;
				if (Infomation::factoryMapping.find(mapping) == Infomation::factoryMapping.end()) {
					bus.post(eventNotFound);
					return nullptr;
				}
				return reinterpret_cast<Ty*>(Infomation::factoryMapping[mapping]());
			}

			template<typename Ty, typename Derived>
			inline static Ty* getInstance(std::string mapping)
			{
				static_assert(std::is_base_of_v<Ty, Derived>, "To retrieve the factory instance, Ty must be a base class of Derived");
				EventBus bus;
				if (Infomation::factoryMapping.find(mapping) == Infomation::factoryMapping.end()) {
					bus.post(eventNotFound);
					return nullptr;
				}
				try
				{
					Ty* ptr = Infomation::factoryMapping[mapping]();
					return ptr;
				}
				catch (...)
				{
					bus.post(eventErrorInstance);
					return nullptr;
				}
			}

			template<typename Ty>
			inline static void releaseInstance(Ty* ptr)
			{
				static_assert(std::is_class_v<Ty>, "This function is only used to free the instance of the factory");
				if (!ptr)
					return;
				return ::operator delete(ptr);
			}
		}
	}

	/* 用于制作Sha1接口的实例 */
	inline void makeSha1Instance(std::unique_ptr<Interface::Sha1>& abstract_ptr)
	{
		abstract_ptr = std::make_unique<Interface::sigmaInterface::Implement::sha1::__Sha1>();
	}

	static std::string getFileSha1(std::string filename)
	{
		std::ifstream fin;
		fin.open(filename, std::ios::binary | std::ios::ate);
		if (!fin.is_open())
		{
			return "";
		}
		std::unique_ptr<Interface::Sha1> s = nullptr;
		try
		{
			makeSha1Instance(s);
			if (!s)
			{
				throw std::runtime_error("无法制作实例");
			}
		}
		catch (std::runtime_error error)
		{
			LibError(error);
		}
		catch (...)
		{
			LibError(std::exception("发生未知错误"));
		}
		DWORD size = fin.tellg();
		fin.seekg(0, std::ios::beg);
		char buffer[512];
		for (int i = 0; i < size / 512; i++)
		{
			fin.read(buffer, 512);
			s->update((unsigned char*)buffer, 512);
		}
		fin.read(buffer, size % 512);
		fin.close();
		s->update((unsigned char*)buffer, size % 512);
		char* result = new char[40];
		s->getDigestString(result);
		std::string str(result);
		delete[] result;
		std::regex no("\\w+");
		std::regex_iterator itr(str.begin(), str.end(), no);
		std::string news = (*itr)[0].str();
		auto ret = news.substr(0, 40);
		return ret;
	}

	/**
	 * 用于快速验证sha1校验和.
	 * 
	 * \param filename 要检验的文件名
	 * \param sha1 要比较的sha1值
	 * \return 如果无法制作实例，如果编译中指定启用异常，则自动抛出
	 */
	static inline bool checkFileSha1(std::string filename, std::string sha1)
	{
		std::string real = filename;
		return sha1 == real;
	}



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
	//请保留此许可证声明，否则请后果自负
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
					static cloudgameZero::Foundation::zeroLogW* ToastPlatformLog()
					{
						static cloudgameZero::Foundation::zeroLogW INSTANCE("cloudgame_comp.json","Main", "WinToastPlatform", 
							[](rapidjson::Document& Dom)
							{
								Dom["logToFile"]["File"]["filename"].SetString("cloudgame_comp_noti.log");
								if (IS_DEBUG)
								{
									Dom["outToTerminal"]["render"].SetBool(false);
									Dom["outToTerminal"]["rootLogger"]["level"].SetString("Info");
								}
								else {
									Dom["outToTerminal"]["Enable"].SetBool(false);
								}
								Dom["Save"].SetBool(false);
							});
						return &INSTANCE;
					}
					inline RTL_OSVERSIONINFOW getRealOSVersion()
					{
						return cloudgameZero::Foundation::dynamincLibrayFunc::function::RtlGetVersion();
					}

					static HRESULT defaultExecutablePath(_In_ WCHAR* path, _In_ DWORD nSize = MAX_PATH)
					{
						DWORD written = ::GetModuleFileNameExW(GetCurrentProcess(), nullptr, path, nSize);
						ToastPlatformLog()->info(L"默认的可执行文件位置为： {}", path);
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
							ToastPlatformLog()->info(L"默认的快捷方式存储路径为： {}", path);
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
							ToastPlatformLog()->info(L"默认的快捷方式文件存储路径为： {}", path);
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
							return cloudgameZero::Foundation::dynamincLibrayFunc::function::WindowsGetStringRawBuffer(xml, nullptr);
						return nullptr;
					}

					inline PCWSTR AsString(_In_ HSTRING hstring)
					{
						return cloudgameZero::Foundation::dynamincLibrayFunc::function::WindowsGetStringRawBuffer(hstring, nullptr);
					}

					static HRESULT setNodeStringValue(_In_ std::wstring const& string, _Out_opt_ IXmlNode* node, _Out_ IXmlDocument* xml) {
						ComPtr<IXmlText> textNode;
						HRESULT hr = xml->CreateTextNode(cloudgameZero::Foundation::Warpper::HstringWrapper(string).Get(), &textNode);
						do {
							if (FAILED(hr))
								break;
							ComPtr<IXmlNode> stringNode;
							hr = textNode.As(&stringNode);
							if (FAILED(hr))
								break;
							ComPtr<IXmlNode> appendedChild;
							hr = node->AppendChild(stringNode.Get(), &appendedChild);
						} while (false);
						return hr;
					}

					static HRESULT addAttribute(_In_ IXmlDocument* xml, std::wstring const& name, IXmlNamedNodeMap* attributeMap)
					{
						ComPtr<ABI::Windows::Data::Xml::Dom::IXmlAttribute> srcAttribute;
						HRESULT hr = xml->CreateAttribute(cloudgameZero::Foundation::Warpper::HstringWrapper(name).Get(), &srcAttribute);
						do {
							if (FAILED(hr))
								break;
							ComPtr<IXmlNode> node;
							hr = srcAttribute.As(&node);
							if (FAILED(hr))
								break;
							ComPtr<IXmlNode> pNode;
							hr = attributeMap->SetNamedItem(node.Get(), &pNode);
						} while (false);
						return hr;
					}

					static HRESULT createElement(_In_ IXmlDocument* xml, _In_ std::wstring const& root_node, _In_ std::wstring const& element_name,
						_In_ std::vector<std::wstring> const& attribute_names)
					{
						ComPtr<IXmlNodeList> rootList;
						HRESULT hr = xml->GetElementsByTagName(cloudgameZero::Foundation::Warpper::HstringWrapper(root_node).Get(), &rootList);
						do {
							if (FAILED(hr))
								break;
							ComPtr<IXmlNode> root;
							hr = rootList->Item(0, &root);
							if (FAILED(hr))
								break;
							ComPtr<IXmlElement> audioElement;
							hr = xml->CreateElement(cloudgameZero::Foundation::Warpper::HstringWrapper(element_name).Get(), &audioElement);
							if (FAILED(hr))
								break;
							ComPtr<IXmlNode> audioNodeTmp;
							hr = audioElement.As(&audioNodeTmp);
							if (FAILED(hr))
								break;
							ComPtr<IXmlNode> audioNode;
							hr = root->AppendChild(audioNodeTmp.Get(), &audioNode);
							if (FAILED(hr))
								break;
							ComPtr<IXmlNamedNodeMap> attributes;
							hr = audioNode->get_Attributes(&attributes);
							if (FAILED(hr))
								break;
							for (auto const& it : attribute_names)
								hr = addAttribute(xml, it, attributes.Get());
						} while (false);
						return hr;
					}

				}
			}

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
						do {
							if (FAILED(hr))
								break;
							HSTRING argumentsHandle;
							hr = activatedEventArgs->get_Arguments(&argumentsHandle);
							if (FAILED(hr))
								break;
							PCWSTR arguments = Libray::Util::AsString(argumentsHandle);
							if (arguments && *arguments)
							{
								eventHandler->Activated(static_cast<int>(wcstol(arguments, nullptr, 10)));
								cloudgameZero::Foundation::dynamincLibrayFunc::function::WindowsDeleteString(argumentsHandle);
								markAsReadyForDeletionFunc();
								return S_OK;
							}
							cloudgameZero::Foundation::dynamincLibrayFunc::function::WindowsDeleteString(argumentsHandle);
							eventHandler->Activated();
							markAsReadyForDeletionFunc();
						} while (false);
						return S_OK;
					};

				auto dismissed = [eventHandler, expirationTime, markAsReadyForDeletionFunc](IToastNotification* notify, IToastDismissedEventArgs* e)
					{
						ToastDismissalReason reason;
						do {
							if (FAILED(e->get_Reason(&reason)))
								break;
							if (reason == ToastDismissalReason_UserCanceled && expirationTime && cloudgameZero::Foundation::Warpper::InternalDateTime::Now() >= expirationTime)
								reason = ToastDismissalReason_TimedOut;
							eventHandler->Dismissed(static_cast<Enums::ToastDismissalReason>(reason));
							markAsReadyForDeletionFunc();
						} while (false);
						return S_OK;
					};

				auto failed = [eventHandler, markAsReadyForDeletionFunc](IToastNotification* notify, IToastFailedEventArgs* e)
					{
						eventHandler->Failed();
						markAsReadyForDeletionFunc();
						return S_OK;
					};
				HRESULT hr = notification->add_Activated(Callback<Implements<RuntimeClassFlags<ClassicCom>, ITypedEventHandler<ToastNotification*, IInspectable*>>>(activated).Get(), &activatedToken);
				do {
					if (FAILED(hr))
						break;
					hr = notification->add_Dismissed(Callback<Implements<RuntimeClassFlags<ClassicCom>, ITypedEventHandler<ToastNotification*, ToastDismissedEventArgs*>>>(dismissed).Get(), &dismissedToken);
					if (SUCCEEDED(hr))
						hr = notification->add_Failed(Callback<Implements<RuntimeClassFlags<ClassicCom>, ITypedEventHandler<ToastNotification*, ToastFailedEventArgs*>>>(failed).Get(), &failedToken);
				} while (false);
				return hr;

			}

			/* Windows通知将使用此类 */
			class ToastTemplate {
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
						Libray::Util::ToastPlatformLog()->info(L"您选择的Toast模板仅支持： {} 行", this->_textFields.size());
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
						this->_scenario = L"Alarm";
						break;
					case Enums::Scenario::IncomingCall:
						this->_scenario = L"IncomingCall";
						break;
					case Enums::Scenario::Reminder:
						this->_scenario = L"Reminder";
						break;
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
				std::wstring _scenario{ L"Default" };
				INT64 _expiration = NULL;
				Enums::AudioOption _audioOption = Enums::AudioOption::Default;
				Enums::ToastTemplateType _type = Enums::ToastTemplateType::Text01;
				Enums::Duration _duration = Enums::Duration::System;
				Enums::CropHint _cropHint = Enums::CropHint::Square;
			};

			using notification = Interface::WinNotification;

			class PreDefineHandler : public API::ToastPlatformHandler
			{
			public:
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

			static std::wstring configureAUMI(_In_ std::wstring const& companyName, _In_ std::wstring const& productName, _In_opt_ std::wstring const& subProduct = std::wstring(), _In_opt_ std::wstring const& versionInformation = std::wstring())
			{
				std::wstring aumi = companyName;
				aumi += L"." + productName;
				if (subProduct.length() > 0)
				{
					aumi += L"." + subProduct;
					if (versionInformation.length() > 0)
						aumi += L"." + versionInformation;
				}
				if (aumi.length() > SCHAR_MAX)
					DEBUG_MESSAGE(L"错误：用户模型ID总长度不应该超过127");
				return aumi;
			}

			static std::wstring const& getToastErrorMessage(_In_ Enums::ToastError error)
			{
				auto const iter = Libray::ToastErrors.find(error);
				assert(iter != Libray::ToastErrors.end());
				return iter->second;
			}
		}
	}

	class Curl
	{
	public:
		using curl_handle_type = CURL*;
		typedef size_t(CALLBACK* curlCallBack)(char* ptr, size_t size, size_t nmemb, void* stream);
		typedef int(*progressCallBack)(void* clientp, double dltotal, double dlnow, double ultotal, double ulnow);

		enum class operation
		{
			GET,
			POST
		};

		enum class operater
		{
			Download,
			Request
		};

		~Curl()
		{
			cleanup();
		}

		inline void init()
		{
			std::unique_lock<std::mutex> lock(mtx);
			this->Handle = curl_easy_init();
			if (!Handle)
			{
				LibError(std::runtime_error("无法获取实例对象"));
			}
			isInit = true;
		}

		template<typename... Args>
		inline void setCurl(_In_ const CURLoption option, _In_ Args&&... args)
		{
			if (!isInit)
			{
				return;
			}
			std::unique_lock<std::mutex> lock(mtx);
			curl_easy_setopt(Handle, option, args...);
		}

		inline void setUrl(_In_ const std::string& url)
		{
			if (!isInit)
			{
				return;
			}
			std::unique_lock<std::mutex> lock(mtx);
			curl_easy_setopt(Handle, CURLOPT_URL, url.c_str());
		}

		inline void setOperater(_In_ operater __operater)
		{
			if (!isInit)
			{
				return;
			}
			std::unique_lock<std::mutex> lock(mtx);
			this->_operater = __operater;
		}

		_NODISCARD rapidjson::Document getJsonDomByRequest(_In_ operation method)
		{
			rapidjson::Document Dom;
			if (!isInit)
			{
				return Dom;
			}
			std::string data = sendRequest(method);
			Dom.Parse(data.c_str());
			if (Dom.HasParseError())
			{
				LibError(std::runtime_error("无法解析DOM!"));
			}
			return Dom;
		}

		std::string sendRequest(_In_ operation method)
		{
			if (!isInit)
			{
				return std::string();
			}
			std::unique_lock<std::mutex> lock(mtx);
			if (_operater != operater::Request)
			{
				LibError(std::bad_function_call());
			}
			std::string response;
			curlCallBack callback = Infomation::curlResponseCallBack;
			//curl_easy_setopt(Handle, CURLOPT_REFERER, "http://www.baidu.com");
			curl_easy_setopt(Handle, CURLOPT_SSL_VERIFYPEER, false);
			curl_easy_setopt(Handle, CURLOPT_SSL_VERIFYHOST, false);
			curl_easy_setopt(Handle, CURLOPT_WRITEFUNCTION, callback);
			curl_easy_setopt(Handle, CURLOPT_WRITEDATA, (void*)&response);
			curl_easy_setopt(Handle, CURLOPT_FOLLOWLOCATION, 1);
			if (method == operation::POST)
			{
				if (postfileds.empty())
				{
					LibError(std::runtime_error("如果要使用POST请求，字段必须附上"));
				}
				curl_easy_setopt(Handle, CURLOPT_POST, true);
				std::string post = cloudgameZero::Foundation::Tool::gbkToUtf8(postfileds);
				curl_easy_setopt(Handle, CURLOPT_POSTFIELDS, post);
			}
			curl_easy_setopt(Handle, CURLOPT_CONNECTTIMEOUT, 30);
			curl_easy_setopt(Handle, CURLOPT_TIMEOUT, 30);
			curl_easy_perform(Handle);
			response = cloudgameZero::Foundation::Tool::function::utf8ToGbk(response);
			return response;
		}

		CURLcode sendDownloadRequest(_In_ operation _operation, _In_ std::string filename, _In_opt_ bool cover = true)
		{
			if (!isInit)
			{
				return CURLcode::CURLE_NOT_BUILT_IN;
			}
			std::unique_lock<std::mutex> lock(mtx);
			if (this->_operater != operater::Download)
			{
				/* 我们在此处判断函数设置的请求是不是Download */
				LibError(std::bad_function_call());
			}
			namespace fs = std::filesystem;
			std::fstream ref;
			if (fs::exists(filename))
			{
				if (cover)
				{
					fs::remove(filename);
					ref.open(filename, std::ios::binary | std::ios::out);
					if (!ref.is_open())
					{
						LibError(std::runtime_error("无法创建文件"));
					}
				}
				else
				{
					return CURLE_OBSOLETE44;
				}
			}
			else
			{
				ref.open(filename, std::ios::binary | std::ios::out);
				if (!ref.is_open())
				{
					LibError(std::runtime_error("无法创建文件"));
				}
			}
			curlCallBack callback = Infomation::curlFileCallback;
			curl_easy_setopt(Handle, CURLOPT_REFERER, "http://www.baidu.com");
			curl_easy_setopt(Handle, CURLOPT_WRITEFUNCTION, callback);
			curl_easy_setopt(Handle, CURLOPT_WRITEDATA, (void*)&ref);
			if (_operation == operation::POST)
			{
				if (postfileds.empty())
				{
					LibError(std::runtime_error("如果要使用POST请求，字段必须附上"));
				}
				curl_easy_setopt(Handle, CURLOPT_POST, true);
				curl_easy_setopt(Handle, CURLOPT_POSTFIELDS, postfileds.c_str());
			}
			curl_easy_setopt(Handle, CURLOPT_FOLLOWLOCATION, true);
			curl_easy_setopt(Handle, CURLOPT_CONNECTTIMEOUT, 360);
			curl_easy_setopt(Handle, CURLOPT_TIMEOUT, 360);
			CURLcode code = curl_easy_perform(Handle);
			if (enableProgress)
			{
				printf("\n");
			}
			ref.close();
			return code;
		}

		inline void showProgress()
		{
			if (!isInit)
			{
				return;
			}
			progressCallBack Callback = Infomation::progressCallback;
			curl_easy_setopt(Handle, CURLOPT_NOPROGRESS, false);
			curl_easy_setopt(Handle, CURLOPT_PROGRESSFUNCTION, Callback);
			enableProgress = true;
		}

		inline void disableProgress()
		{
			if (!isInit)
			{
				return;
			}
			curl_easy_setopt(Handle, CURLOPT_NOPROGRESS, true);
			curl_easy_setopt(Handle, CURLOPT_PROGRESSFUNCTION, nullptr);
			enableProgress = false;
		}

		inline operator curl_handle_type()
		{
			std::unique_lock<std::mutex> lock(mtx);
			return Handle;
		}

		inline curl_handle_type native_handle()
		{
			std::unique_lock<std::mutex> lock(mtx);
			return Handle;
		}

		inline void cleanup()
		{
			std::unique_lock<std::mutex> lock(mtx);
			if (Handle && isInit)
			{
				curl_easy_cleanup(Handle);
			}
			isInit = false;
		}

	private:
		curl_handle_type Handle = nullptr;
		operater _operater{};
		std::string postfileds{};
		std::mutex mtx;
		bool isInit;
		bool enableProgress;
	};

	template<class Type1, class Type2>
	static constexpr bool isSameData(Type1&& one, Type2&& two)
	{
		if (sizeof(Type1) != sizeof(Type2)) 
		{
			return false;
		}
		BYTE* _ptr1 = (BYTE*)&one;
		BYTE* _ptr2 = (BYTE*)&two;
		for (int iter = 0; iter < (int)sizeof(one); iter++)
		{
			if (*_ptr1 != *_ptr2) 
			{
				return false;
			}
			_ptr1 = _ptr2 += 1;
		}
		return true;
	}

	namespace Experiment
	{
		static std::vector<std::string> makeArgumentsView(int argc, CHAR** argv)
		{
			std::span<char*> span(argv, argc);
			std::vector<std::string> vector = std::vector<std::string>(argc);
			int i = 0;
			for (auto& itr : span) 
			{
				vector.push_back(itr);
				i++;
			}
			return vector;
		}

		using Curl = ::cloudgameZero::Curl;

		static void copy(std::string_view from, std::string_view to)
		{
			namespace fs = std::filesystem;
			#if NDEBUG
			if (from.empty() || to.empty())
			{
				throw std::runtime_error("The String Can't Be Empty");
			}
			#else
			assert(!(from.empty() && to.empty()));
			#endif
			try
			{
				if (fs::exists(from))
				{
					if (fs::is_directory(from))
					{
						std::filesystem::copy(from, to);
					}
					else if (fs::is_symlink(from))
					{
						fs::copy_symlink(from, to);
					}
					else
					{
						if (fs::is_directory(to))
						{
							fs::copy(from, to);
							return;
						}
						else if (fs::is_symlink(to) || fs::is_block_file(to) || fs::is_socket(to))
						{
							LibError(std::runtime_error(std::format("The {} File Is Is Not Safe", to).c_str()));
						}
						fs::copy_file(from, to);
					}
					return;
				}
				PrintError("Can't Found Files");
			}
			catch (std::exception& error)
			{
				/* 转发异常给LibError，由Client处理 */
				LibError(error);
			}
		}

		static std::list<std::string> TraverseFolder(_In_ std::string_view floder)
		{
			namespace fs = std::filesystem;
			#if NDEBUG
			if (floder.empty())
			{
				throw std::runtime_error("The String Can't Be Empty");
			}
			#else
			assert(!(floder.empty()));
			#endif
			std::list<std::string> list; //创建链表
			if (fs::exists(floder) && fs::is_directory(floder)) //我们检查这个目录是否存在
			{
				fs::directory_iterator entry(floder); //创建访问这个目录的实例
				for (auto& itr : entry)
				{
					list.emplace_back(itr.path().string()); //每次遍历的时候把数据推送给链表存储
				}
				return list;
			}
			try
			{
				if (!fs::exists(floder)) //我们检查一下这是否是个文件且是不是存在的
				{
					//看来函数返回了false，说明它找不到，我们直接return掉就行了
					return list;
				}
				fs::path view(floder); //创建这个路径的实例，如果不存在目录的情况下
				std::string parent_path = view.parent_path().string(); //我们拿到它的父目录来遍历
				if (std::filesystem::is_directory(parent_path)) //检查这个父目录是不是真目录
				{
					fs::directory_iterator entry(parent_path); //随后创建实例再次遍历
					for (auto& itr : entry)
					{
						list.emplace_back(itr.path().string());
					}
				}
			}
			catch (std::exception& error)
			{
				/* 转发异常给LibError，由Client处理 */
				LibError(error);
			}
			return list; //无轮如何都会被返回
		}


		namespace json
		{
			class JObject;

			enum Type
			{
				J_null,
				J_boolean,
				J_int,
				J_double,
				J_string,
				J_list,
				J_dict
			};

			using null_t = char*;
			using int_t = int32_t;
			using bool_t = bool;
			using double_t = double;
			using string_t = std::basic_string<char>;
			using list_t = std::vector<JObject>;
			using dict_t = std::map<std::string, JObject>;

			template<class T>
			constexpr bool is_basic_type()
			{
				if constexpr (
					std::is_same_v(T, string_t) ||
					std::is_same_v(T, bool_t) ||
					std::is_same_v(T, double_t) ||
					std::is_same_v(T, int_t)
				)
				{
					return true;
				}
				return false;
			}

			class JObject
			{
			public:
				using value_t = std::variant<bool_t,int_t,double_t,string_t,list_t,dict_t>;

				JObject()
				{
					type = J_null;
					_value = "null";
				}

				JObject(int_t value)
				{
					Int(value);
				}

				JObject(bool_t value)
				{
					Bool(value);
				}

				JObject(double_t value)
				{
					Double(value);
				}

				JObject(string_t const& value)
				{
					String(value);
				}

				JObject(list_t value)
				{
					List(std::move(value));
				}

				JObject(dict_t value)
				{
					Dict(std::move(value));
				}

				void Null()
				{
					type = J_null;
					_value = "null";
				}

				void Int(int_t value)
				{
					_value = value;
					type = J_int;
				}

				void Bool(bool_t value)
				{
					_value = value;
					type = J_boolean;
				}

				void Double(double_t value)
				{
					_value = value;
					type = J_double;
				}

				void String(std::string_view value)
				{
					_value = std::string(value);
					type = J_string;
				}

				void List(list_t value)
				{
					_value = std::move(value);
					type = J_list;
				}

				void Dict(dict_t value)
				{
					_value = std::move(value);
					type = J_dict;
				}

				inline void THROW_GET_ERROR(std::string erron)
				{
					#if EnableZeroLibrayExceptions
					throw std::logic_error(std::format("type error in get {} value!",erron).data());
					#else
					PrintError(std::format("type error in get {} value!", erron));
					abort();
					#endif
				}

				inline const char* getString()
				{
					__CLOUDGAMEJSONASSERT(J_string);
					void* ret = value;
					return static_cast<const char*>(ret);
				}

				inline bool getBoolean()
				{
					__CLOUDGAMEJSONASSERT(J_boolean);
					void* ret = value;
					return *(reinterpret_cast<bool*>(ret));
				}

				inline int getInt()
				{
					__CLOUDGAMEJSONASSERT(J_int);
					void* ret = value;
					return *(reinterpret_cast<int*>(ret));
				}

				inline double getDouble()
				{
					__CLOUDGAMEJSONASSERT(J_double);
					void* ret = value;
					return *(reinterpret_cast<double*>(ret));
				}

				inline list_t& getArray()
				{
					__CLOUDGAMEJSONASSERT(J_list);
					void* ret = value;
					return *(reinterpret_cast<list_t*>(ret));
				}

				inline dict_t& getDict()
				{
					__CLOUDGAMEJSONASSERT(J_dict);
					void* ret = value;
					return *(reinterpret_cast<dict_t*>(ret));
				}

				void addArrayMember(JObject item)
				{
					if (type == J_list)
					{
						auto& list = getArray();
						list.push_back(std::move(item));
						return;
					}
					LibError(std::logic_error("not a list type! JObjcct::push_back()"));
				}

				void popBack()
				{
					if (type == J_list)
					{
						auto& list = getArray();
						list.pop_back();
						return;
					}
					LibError(std::logic_error("not list type! JObjcct::pop_back()"));
				}

				JObject& operator[](std::string key)
				{
					if (type == J_dict)
					{
						auto& dict = getDict();
						return dict[key];
					}
					LibError(std::logic_error("not dict type! JObject::opertor[]()"));
				}

			private:
				void __CLOUDGAMEJSONASSERT(Type type,std::string_view info = "")
				{
					#if NDEBUG
					if (this->type != type)
					{
						throw std::logic_error(info.data());
					}
					#else
					CLOUDGAMEFIX_ASSERT(this->type == type);
					#endif
				}
				Type type;
				value_t _value;
				void* value;
			};

			class Document
			{
			public:
				JObject parse(char* const json)
				{
					str = json;
					char token = moveNext();
					if (token == 'n')
					{
						return parseNull();
					}
					if (token == 't' || token == 'f')
					{
						//return parseBool();
					}
					if (token == '-' || std::isdigit(token))
					{
						//return parseNumber();
					}
					if (token == '\"')
					{
						//return parseString();
					}
					if (token == '[')
					{
						//return parseList();
					}
					if (token == '{')
					{
						//return parseDict();
					}
					throw std::logic_error("unexpected character in parse json");
				}



			private:
				JObject parseNull()
				{
					if (str.compare(idx, 4, "null") == 0)
					{
						idx += 4;
						return {};
					}
					throw std::logic_error("parse null error");
				}



				JObject parseNumber()
				{
					auto pos = idx;
					//integer part
					if (str[idx] == '-')
					{
						idx++;
					}
					if (std::isdigit(str[idx])) 
					{
						while (std::isdigit(str[idx]))
						{
							idx++;
						}
					}
					else
					{
						throw std::logic_error("invalid character in number");
					}
					if (str[idx] != '.')
					{
						return static_cast<int>(strtol(str.c_str() + pos, nullptr, 10));
					}
					//decimal part
					if (str[idx] == '.')
					{
						idx++;
						if (!std::isdigit(str[idx]))
						{
							throw std::logic_error("at least one digit required in parse float part!");
						}
						while (std::isdigit(str[idx]))
						{
							idx++;
						}
					}
					return strtod(str.c_str() + pos, nullptr);
				}
				char moveNext()
				{
					while (std::isspace(str[idx])) idx++;
					if (idx >= str.size())
					{
						throw std::logic_error("unexpected character in parse json");
					}
					//如果是注释，记得跳过
					skipComment();
					return str[idx];
				}
				void skipComment()
				{
					if (str.compare(idx, 2, R"(//)"))
					{
						while (true)
						{
							auto next_pos = str.find('\n', idx);
							if (next_pos == std::string::npos)
							{
								throw std::logic_error("invalid comment area!");
							}
							//查看下一行是否还是注释
							idx = next_pos + 1;
							while (isspace(str[idx]))
								idx++;
							if (str.compare(idx, 2, R"(//)") != 0)
								//结束注释
								return;
						}
					}
				}
				JObject object;
				string_t str;
				size_t idx;
			};
		}
	}
}

namespace leanCloudgameZero 
{
	using cloudgameZero::Foundation::dynamincLibrayFunc::loadFunFromLib;
	using cloudgameZero::checkFileSha1;
	using cloudgameZero::DEBUG_MESSAGE;
	using namespace cloudgameZero::Infomation;
	using namespace cloudgameZero::Foundation::Tool;
	using namespace cloudgameZero::Foundation::dynamincLibrayFunc::function;
	namespace GUID = cloudgameZero::Interface::sigmaInterface::guid;
	namespace WinToastNotification = cloudgameZero::ToastPlatform::API;
}
#endif
#pragma warning(pop)
#endif // CLOUDGAME_FIX_ZERO_H