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
���ڱ��⣺
�˿����ṩ����������ϷWindowsϵͳ��C++���׳����
���ļ���װ��WinToast��jthread�ȿ⣬�������ӿ��ṩ֧��
ͬʱ�ṩ����־��¼��
ע��
�˿���Ҫ��װ�������⣬����ҪC++20��׼֧��
��Ҫ����vcpkg��װ
��ע��
WinToast�����֤�������������ռ�������ã��ڷַ�ʱ�豣�����������Ը�
*/
#pragma once
#ifndef CLOUDGAME_FIX_ZERO_H
#define CLOUDGAME_FIX_ZERO_H

#define WIN32_LEAN_AND_MEAN
/*
�˺������ڱ�ʶ���ļ��Ƿ񽫽ӿں������嵽Դ�ļ���
����ǿ���Դ����ĸ������˺꽫�ᱻע�ͣ��Ҵ󲿷ֺ�����ʹ�ö�̬���ӿ⣬�ҽ��Զ��������
*/
//#define OPEN_SOURCES_CLOUDGAMEFIXZERO_API

#define ENABLE_NOCRT_FUNC true

/* Windows SDK And C++ Standard Libray Files | Windows SDKĬ���ṩ�Ŀ��Լ�C++20�ṩ�ı�׼�� */
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
/* Third-party library references | �ӵ��������õĿ� */
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
#define EnableZeroLibrayExceptions true
#define EXPORT_ZERO

#ifndef EXPORT_ZERO
#define ZERO_BASEAPI __declspec(dllimport)
#else

#ifdef OPEN_SOURCES_CLOUDGAMEFIXZERO_API
#define ZERO_BASEAPI __declspec(dllexport)
#else
#define ZERO_BASEAPI __declspec(dllimport)
#endif

#endif

using namespace Microsoft::WRL;
using namespace ABI::Windows::Data::Xml::Dom;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::UI::Notifications;
using namespace Windows::Foundation;


#if _HAS_CXX20 && __has_include("rapidjson/writer.h") && __has_include("boost/stacktrace.hpp")
namespace cloudgameZero
{
	//�洢�˿��������Ϣ
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
		//���ں��ڿ�Ļ�����ȫ���ܴ���
		namespace Secutriy
		{
			static std::mutex mutexLock;
			static LPCSTR urlLinkRegex = "^(https://|http://|ftp://).+/.*";
			static LPCSTR lnkPathRegex = "^([a-z]|[A-Z]){1}:\\\\.*(.lnk)$";
			static LPCSTR lnkPathRegexNoEscape = "^([a-z]|[A-Z]){1}:/.+.(lnk)$";
		}
		/* Ϊcurl�ṩ�������ص���ʱ���� */
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
	/* cloudgameZero�ṩ�ĵ������������ʵ����־�⹦�� */
	static const HANDLE CONSOLE_OUTPUT_HANDLE = GetStdHandle(STD_OUTPUT_HANDLE);

	/*�����ض��������־�����ṩ�ļ��׺�����ͬʱ��ʶ��ǰ����ģʽ״̬ .*/
#ifdef NDEBUG
	static const bool IS_DEBUG = false;
	template<typename Ty>
	/**
	 * \brief �˲���д��2023/7/23.
	 * \brief ���棺���Ҫ��ʾ������־��Ϣ����ʹ��Debug����ģʽ������Realease
	 */
	inline void PrintError(Ty msg) noexcept {}
	/**
	 * \brief �˲���д��2023/7/23.
	 * \brief ���棺���Ҫ��ʾ������־��Ϣ����ʹ��Debug����ģʽ������Realease
	 */
	template<typename Ty>
	void inline DEBUG_MESSAGE(Ty str) noexcept {}
#else
	static const bool IS_DEBUG = true;
	/**
	 * \brief �˲���д��2023/7/23
	 * \brief ��������Ϣ��ӡ������̨��ͬʱ���������.
	 * \brief ��ע
	 * \brief �˺�����DEBUG_MESSAGEʹ�ö����������ڱ�����ʹ��std::wcerr
	 * \brief ���std::wostream�����Ķ������msg���������ͣ������ͨ�����������ʧ��
	 * \brief -----------------------���²���д��2023/8/5-------------------------------
	 * \brief �˺����ڴ�ӡ��ɺ󽫼����״̬��������𻵣���������ʱ����������ݣ�����localeΪchs��������´�ӡ����
	 * \brief ���ʹ����Foundation::Tool���ַ���ת�����������ܻᵼ�´������𻵵���std::wcout�����޸����ٴ�����ַ���
	 * \param msg һ�����Ͳ���
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
	 * \brief �˲���д��2023/7/23
	 * \brief ��������Ϣ��ӡ������̨��ͬʱ���������.
	 * \brief ��ע
	 * \brief �˺�����PrintErrorʹ�ö����������ڱ�����ʹ��std::wcout
	 * \brief ���std::wostream�����Ķ������msg���������ͣ������ͨ�����������ʧ��
	 * \brief -----------------------���²���д��2023/8/5-------------------------------
	 * \brief �˺����ڴ�ӡ��ɺ󽫼����״̬��������𻵣���������ʱ����������ݣ�����localeΪchs��������´�ӡ����
	 * \brief ���ʹ����Foundation::Tool���ַ���ת�����������ܻᵼ�´������𻵵���std::wcout�����޸����ٴ�����ַ���
	 * \param msg һ�����Ͳ���
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

	/* ����jthread��Windows API��װ���� */
	class ThreadPlatform
	{
	public:
		using native_handle_type = std::thread::native_handle_type;

		ThreadPlatform() = delete;

		/**
		 * \brief �˲���д��2023/7/25
		 * \brief �вι��캯��
		 * \brief ���ö���ĺ�������ʼ���߳�
		 *
		 * \param f һ��ָ�����⺯����ָ��
		 * \param args һ�������Ĳ����б�
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
		 * \brief �˲���д��2023/7/25
		 * \brief һ������ģ�壬�������ú���������״̬
		 * \brief ��ע:
		 * \brief �˺�����Ҫ���߳��ѽ�����ǰ���²�������
		 *
		 * \param f һ��ָ�����⺯����ָ��
		 * \param args һ�������Ĳ����б�
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
		 * \brief �˲���д��2023/7/23.
		 * \brief ��������󣬴˺��������������߳�
		 * \brief ע��
		 * \brief �˺�������Ѿ�ִ�У��������ٴε��ã�ֱ���û�����StopThread��Ա����������������̨��ӡһ�д�����Ϣ��ֱ��return�˳�Ա����
		 * \brief ͬʱ����һ��������ڿ����߳�
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
		 * \brief �˲���д��2023/7/23.
		 * \brief �˺���ΪStart��Ա���������ذ汾���˰汾�����û�������ʱ���˺����������첽�̣߳�����ʱ����ʱֱ�ӵ���Start���������߳�
		 * \brief ע��
		 * \brief �˺�������Ѿ�ִ�У��������ٴε��ã�ֱ���û�����StopThread��Ա����������������̨��ӡһ�д�����Ϣ��ֱ��return�˳�Ա����
		 * \param milliseconds ���ߵĺ���������������Ϊsize_t
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
		 * \brief �˲���д��2023/7/23.
		 * \brief �˺����������̷߳���
		 * \brief �̵߳���֮�󣬴��߳̾ͳ�Ϊ�ػ��̣߳�פ����̨���У���֮�������̶߳���ʧȥ��Ŀ���̵߳Ĺ������޷���ͨ���̶߳���ȡ�ø��̵߳Ŀ���Ȩ��
		 * \brief ���߳�������ִ����֮�󣬽��Զ�����
		 * \brief ��ע
		 * \brief �˺�������Ӱ�����³�Ա����
		 * \brief join(),StopThread(),get_id(),joinable()
		 * \brief �������Ϊ�ػ��̣߳�����ô˺��������������ʹ��
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
		 * \brief �˲���д��2023/7/23.
		 * \brief ��ȡ�ö�������̵߳�ԭ��ϵͳ���.
		 *
		 * \return ����߳������򷵻ظö�������̵߳�ԭ��ϵͳ��������򽫷���NULL
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
		 * \brief �˲���д��2023/7/23.
		 * \brief �˺�����ʹ�̺߳��������뵽���߳��У����߳̽���������ֱ���߳̽���
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
		 * \brief �˲���д��2023/7/26.
		 * \brief ��ֹ����������߳�
		 * \brief ��ע
		 * \brief ����û�������detach�������˺������ܻ�����쳣
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
		 * \brief �˲���д��2023/7/26.
		 * \brief �˺�������Ѹö��󱻹���Ĺ����ָ̻߳�
		 * \brief ����߳�û�п�����û�й��𽫻������̨��ӡ������Ϣ��return
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
		 * \brief �˲���д��2023/7/26.
		 * \brief �˺�������Ѹö�������Ľ��̹���
		 * \brief ����߳�û�п������Ѿ����𽫻������̨��ӡ������Ϣ��return
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

	/* cloudgamefixZero�Ļ����������ռ䣬����˳�����Ҫ�ĺ����ͳ������������������ʵ�ֲ��� */
	namespace Foundation
	{
		/* �洢���ڶ�̬���ӿ�ĺ����ͳ��� */
		namespace dynamincLibrayFunc
		{
			/* Ԥ���庯����� */
			static const HINSTANCE NTDLL = GetModuleHandleW(L"NTDLL.dll");
			static const HINSTANCE USER32 = LoadLibraryW(L"user32.dll");
			static const HINSTANCE KERNEL = LoadLibraryW(L"kernel32.dll");
			static const HINSTANCE COMBASE = LoadLibraryW(L"ComBase.dll");
			/* Ԥ����� */
#define WINUEAPI WINAPI
/* WINUEAPI��һ���꣬ȫ��WINDOWS_UN_EXTERN_API��������δ�ṩ������δ�ĵ����ĺ��� */

/**
 * \brief �˲���д��2023/7/25
 * \brief һ��ģ�庯�������ڽ���̬���ӿ�ĺ����������󶨵�����ָ��.
 * \param handle ��̬���ӿ�ľ��
 * \param FuncName ��������
 * \param pointer ����ָ��
 * \return ��������ɹ��򷵻�S_OK�������������򷵻�E_INVALIDARG�������������������޷���ȡ������ַ���򷵻�E_FAIL
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
						throw std::runtime_error("Can't load proc Address��Are you sure that the handles and functions are correct?");
#else
						PrintError("Can't load proc Address��Are you sure that the handles and functions are correct?");
#endif
						return E_FAIL;
					}
				}
			}

			/* �������ռ��ṩ��function�����ռ�ĺ���ָ������ */
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

			/* �������ռ��ṩ�˻���loadFunFromLib������װ��δ�ĵ���/δ�������� */
			namespace function
			{
				/**
				 * \brief �˲���д��2023/7/25.
				 * \brief �˺�������δ�ĵ���Windows API
				 * \brief
				 * \brief ��ȡWindows����ϵͳ�ڲ�ϵͳ�汾��
				 * \param dwMajor ָ��DWORD(32λ�޷�������)�ĵ�ַ�����ڽ���NT�ں˰汾
				 * \param dwMinor ָ��DWORD(32λ�޷�������)�ĵ�ַ
				 * \param dwBuilder ָ��DWORD(32λ�޷�������)�ĵ�ַ�����ڽ���Windows�����汾��
				 */
				ZERO_BASEAPI VOID WINAPI RtlGetNtVersionNumbers(_Inout_ DWORD* dwMajor, _Inout_ DWORD* dwMinor, _Inout_ DWORD* dwBuilder);

				/**
				 * \brief �˲���д��2023/7/25.
				 * \brief ��MessageBoxAԭ�еĹ������ṩ�˳�ʱ���ܣ�����ﵽ�û��������ʱ�䣬���Զ��ر�
				 * \brief ��ע��
				 * \brief ���²�����hWnd,lpText,lpCaption,uType����
				 * \brief ��ο���������:
				 * \brief https://learn.microsoft.com/zh-cn/windows/win32/api/winuser/nf-winuser-messageboxa
				 * \param hWnd �ο������ĵ�
				 * \param lpText �ο������ĵ�
				 * \param lpCaption �ο������ĵ�
				 * \param uType �ο������ĵ�
				 * \param wLanguageId ����ID��ͨ�������������ΪNULL����0����
				 * \param dwMilliseconds ��ʱʱ�䣬��λ����
				 * \return ����ֵͬMessageBoxA
				 */
				ZERO_BASEAPI int WINUEAPI MessageBoxTimeoutA(HWND hWnd, _In_ LPCSTR lpText, _In_ LPCSTR lpCaption, _In_ UINT uType, _In_ WORD wLanguageId, _In_ DWORD dwMilliseconds) noexcept;

				/**
				 * \brief �˲���д��2023/7/25.
				 * \brief ��MessageBoxWԭ�еĹ������ṩ�˳�ʱ���ܣ�����ﵽ�û��������ʱ�䣬���Զ��ر�
				 * \brief ��ע��
				 * \brief ���²�����hWnd,lpText,lpCaption,uType����
				 * \brief ��ο���������:
				 * \brief https://learn.microsoft.com/zh-cn/windows/win32/api/winuser/nf-winuser-messageboxw
				 * \param hWnd �ο������ĵ�
				 * \param lpText �ο������ĵ�
				 * \param lpCaption �ο������ĵ�
				 * \param uType �ο������ĵ�
				 * \param wLanguageId ����ID��ͨ�������������ΪNULL����0����
				 * \param dwMilliseconds ��ʱʱ�䣬��λ����
				 * \return ����ֵͬMessageBoxW
				 */
				ZERO_BASEAPI int WINUEAPI MessageBoxTimeoutW(_In_ HWND hWnd, _In_ LPCWSTR lpText, _In_ LPCWSTR lpCaption, _In_ UINT uType, _In_ WORD wLanguageId, _In_ DWORD dwMilliseconds) noexcept;

				/**
				 * \brief �˲���д��2023/7/25.
				 * \brief ����ָ�����ַ��������µ��ַ������á�
				 * \brief ��ע��
				 * \brief �˺�������δ�����������Ѿ��ĵ����������ĵ���Ϣ
				 * \brief ��ο��������ӣ�
				 * \brief https://learn.microsoft.com/zh-cn/windows/win32/api/winstring/nf-winstring-windowscreatestringreference
				 * \param sourceString
				 * \param һ���� null ��β���ַ����������� HSTRING ��Դ���������Ϊ 0���� NULL ֵ��ʾ���ַ����� Ӧ�ڶ�ջ֡�Ϸ���
				 * \param length
				 * \param SourceString �ĳ��ȣ��� Unicode �ַ�Ϊ��λ���� ��� sourceString Ϊ NULL�������Ϊ 0�� ������� 0�� sourceString ���������ֹ null �ַ�
				 * \param hstringHeader
				 * \param ָ��Windows ����ʱ�������ַ�����ʶΪ�ַ������û���ٴ����ַ����Ľṹ��ָ�롣
				 * \param string
				 * \param ָ���´������ַ�����ָ��;�����������,��Ϊ NULL,������ �ַ��� �е��κ���������,HSTRING �Ǳ�׼�������
				 * \returns �ɹ�
				 * \returns S_OK			�ѳɹ����� [**HSTRING**] (/windows/win32/winrt/hstring)
				 * \returns ʧ��
				 * \returns E_INVALIDARG	�ַ����� hstringHeader Ϊ NULL�������ַ���������null��β��
				 * \returns E_OUTOFMEMORY	δ�ܷ����µ� [**HSTRING**] (/windows/win32/winrt/hstring)
				 * \returns E_POINTER		sourceStringΪNULL,����Ϊ����
				 */
				ZERO_BASEAPI HRESULT FAR WINUEAPI WindowsCreateStringReference(PCWSTR sourceString, UINT32 length, HSTRING_HEADER* hstringHeader, HSTRING* string) noexcept;

				/**
				 * \brief �˲���д��2023/7/25.
				 * \brief ����ָ���ַ����ĺ�ܻ�������
				 * \brief ��ע��
				 * \brief �˺�������δ�����������Ѿ��ĵ����������ĵ���Ϣ
				 * \brief ��ο��������ӣ�
				 * \brief https://learn.microsoft.com/zh-cn/windows/win32/api/winstring/nf-winstring-windowsgetstringrawbuffer
				 * \param string ҪΪ��������˻������Ŀ�ѡ�ַ���,����Ϊ NULL
				 * \param length
				 * \param ָ��UINT32�Ŀ�ѡָ�롣���Ϊ���ȴ���NULL�������NULL
				 * \param ���������ָ��UINT32����Чָ�룬�����ַ�������Ч��HSTRING�����ڳɹ���ɺ󣬸ú����Ὣֵ����Ϊ�ַ������˻�������Unicode�ַ���(������Ƕ���null�ַ���������������ֹnull)
				 * \param ���length��ָ��UINT32����Чָ�룬�����ַ���ΪNULL���� ���� ָ���ֵ����Ϊ 0��
				 * \return ����ָ��Ϊ �ַ����ṩ��ܴ洢�Ļ�������ָ��;����ַ���ΪNULL����ַ�������Ϊ���ַ�����
				 */
				ZERO_BASEAPI PCWSTR FAR WINUEAPI WindowsGetStringRawBuffer(_In_ HSTRING string, UINT32* length) noexcept;

				/**
				 * \brief �˲���д��2023/7/25.
				 * \brief �ݼ��ַ��������������ü�����
				 * \brief ��ע��
				 * \brief �˺�������δ�����������Ѿ��ĵ����������ĵ���Ϣ
				 * \brief ��ο��������ӣ�
				 * \brief https://learn.microsoft.com/zh-cn/windows/win32/api/winstring/nf-winstring-windowsdeletestring
				 *
				 * \param string Ҫɾ�����ַ���
				 * \param ��� �ַ��� ���� WindowsCreateStringReference�����Ŀ��ٴ����ַ�����������ַ���ΪNULL��գ���ִ���κβ���������S_OK
				 * \return �˺���������αض��᷵��һ��S_OK
				 */
				ZERO_BASEAPI HRESULT FAR WINUEAPI WindowsDeleteString(_In_opt_ HSTRING string) noexcept;

				/**
				 * \brief ��PROPVARIANT��������ת��ΪPWSTR����.
				 *
				 * \param propvar
				 * \param psz
				 * \param cch
				 * \return
				 */
				ZERO_BASEAPI HRESULT FAR WINUEAPI PropVariantToString(_In_ REFPROPVARIANT propvar, PWSTR psz, _In_ UINT cch) noexcept;

				/**
				*
				 * �˺���RoGetActivationFactory�ķ�װ�����ڻ�ȡָ������ʱ��ļ������
				 * \brief ��ע��
				 * \brief �˺�������δ�����������Ѿ��ĵ����������ĵ���Ϣ
				 * \brief ��ο���������:
				 *
				 * \param activatableClassId �ɼ������GUID
				 * \param factory �����
				 * \return ����˺����ɹ�����������S_OK��������������HRESULT������롣
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
				 * �˺������ڻ�ȡϵͳ�汾��Ϣ.
				 * \brief ��ע��
				 * \brief �˺�������δ������δ�ĵ�������
				 *
				 * \return ��������ɹ���������������RTL_OSVERSIONINFOW�Ľṹ��
				 */
				ZERO_BASEAPI RTL_OSVERSIONINFOW FAR WINUEAPI RtlGetVersion() noexcept;

				/* �������ռ�洢�˿��ܻᵼ��������Ϊ��Windowsδ����API����ЩAPI������Ҫ�ĳ���. */
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
					 * \brief �������̵ķ���Ȩ��.
					 * \brief �˺���Ϊδ��������
					 *
					 * \param Privilege Ȩ��id
					 * \param bEnablePrivilege ���ΪTRUE,����Ȩ�ޣ���֮�ر�
					 * \param IsThreadPrivilege ���ΪTRUE,���������ǰ�߳�Ȩ�ޣ����������������̵�Ȩ��
					 * \param PreviousValue ���ԭ����ӦȨ�޵�״̬���� | �رգ�
					 * \return �ɺ���
					 */
					ZERO_BASEAPI UINT RtlAdjustPrivilege(ULONG Privilege, BOOL bEnablePrivilege, BOOL IsThreadPrivilege, PINT PreviousValue);
				}
			}
		}
		/* cloudgameZero�ṩ�ļ��׹��߼��� */
		namespace Tool
		{
			/* �ṩ�˼��׵ĺ������� */
			inline namespace function
			{
				/**
				 * �˺��������û���ȡWindows����������ֵ.
				 *
				 * \param PATH ��������ֵ��һ���ַ������ͣ���APPDATA
				 * \param len ���ȣ���ѡ��
				 * \return ���һ������������������һ��std::string���͵�����������洢���ǻ���������Ӧ��ֵ
				 */
				ZERO_BASEAPI std::string GetEnvironmentVariableA(const std::string PATH, DWORD len = MAX_PATH);

				/**
				 * �˺�������ע����л�ȡ���ڴ��������ַ���.
				 *
				 * \return ���һ��������������һ��CHAR*�ַ���
				 */
				ZERO_BASEAPI CHAR* GetProcesserFromRegistryA();

				/**
				 * �˺�������ע����л�ȡ���ڴ������Ŀ��ַ���.
				 *
				 * \return ���һ��������������һ��WCHAR*�ַ���
				 */
				ZERO_BASEAPI WCHAR* GetProcesserFromRegistryW();
				
				/**
				 * �˺�������ϵͳ�л�ȡ��ǰ��¼���û���.
				 *
				 * \return ���һ������������LPCSTR���͵�ָ�룬ָ��洢�����û���
				 */
				ZERO_BASEAPI LPCSTR GetUserA();

				/**
				 * �˺�������ϵͳ�л�ȡ��ǰ��¼���û���.
				 *
				 * \return ���һ������������LPCWSTR���͵�ָ�룬ָ��洢�����û���
				 */
				ZERO_BASEAPI LPCWSTR GetUserW();

				/**
				 * �˺�������Ϊ������pauseָ��.
				 *
				 * \param message ��ʾ��Ϣ�������ʾ��ϢΪNULL����ʲô������ӡ
				 * \param wrap �����Ƿ��У�Ĭ��Ϊtrue�����Ϊfalse������ӡ���з�
				 * \param ע�����messageΪNULL����wrap��ʹΪtrue����false�������ỻ��
				 *
				 */
				ZERO_BASEAPI void PRESSANYBOTTON(const char* message = "�밴���������...", bool wrap = true);

				/**
				 * ͨ����������ȡ�����̵Ľ���ID.
				 *
				 * \param processName ���ַ��������ڻ�ȡ
				 * \return ���ض�Ӧ���̵Ľ���id
				 */
				ZERO_BASEAPI DWORD GetProcessIdByName(LPCWSTR processName);

				/**
				 * ͨ������id��ȡ���ھ��.
				 *
				 * \param id ����id
				 * \return ���һ����������������������̵Ĵ��ھ��
				 */
				ZERO_BASEAPI HWND GetHwndById(DWORD id);

				/**
				 * \brief ͨ����������ӻ�ȡ����id����ȡ���ھ��.
				 * \brief
				 * \param processName ������
				 * \return ���һ����������������������̵ľ�������򷵻�һ����ָ��
				 */
				ZERO_BASEAPI HWND GetHwndByName(LPCWSTR processName);

				/**
				 * \brief ��ֹĳ������.
				 *
				 * \param processName ������
				 * \return ����SHORT�������ݣ�����3����������֮һ
				 * \return �������1���ʾ����ֹ
				 * \return �������0���ʾ�޷���ȡ��ʵ��
				 * \return �������-1��������ڳ��Ի�ȡ���ʱ����ʧ�ܣ�����Ȩ�޷��������
				 */
				ZERO_BASEAPI SHORT Terminate(LPCWSTR processName);

				/**
				 * \brief ͨ��chronoʱ�������һ��ʱ���ַ���.
				 *
				 * \param format ��ʽ���ַ�����ȡ��https://www.apiref.com/cpp-zh/cpp/io/manip/put_time.html
				 * \return ���ظ�ʽ������ַ���
				 */
				ZERO_BASEAPI inline std::string makeTimeStr(std::string format) noexcept;

				ZERO_BASEAPI std::string utf8ToGbk(std::string& convert) noexcept;

				ZERO_BASEAPI std::string gbkToUtf8(std::string& convert) noexcept;

				/* ʵ���ú��� */
				namespace Experiment
				{
					/**
					* \brief �˲���д��2023/8/1
					* \brief ��std::stringת��Ϊstd::wstring.
					* \brief ��ע
					* \brief �˺���ת���Ľ�����ܻᵼ��ostream�𻵣�������������;
					*
					* \param convert Ҫת�����ַ���
					* \return ����ת�����
					*/
					ZERO_BASEAPI _NODISCARD std::wstring MutiToWide(std::string convert);

					/**
					 * \brief �˲���д��2023/8/1
					 * \brief ��std::wstringת��Ϊstd::string.
					 * \brief ��ע
					 * \brief �˺���ת���Ľ�����ܻᵼ��ostream�𻵣�������������;
					 *
					 * \param convert Ҫת�����ַ���
					 * \return ����ת�����
					 */
					ZERO_BASEAPI _NODISCARD std::string WideToMuti(std::wstring convert);

					/**
					 * \brief �˲���д��2023/8/2.
					 * \brief ����WideToMuti��Ƶİ�ȫ�汾����
					 *
					 * \param str �����õ�std::wstring�ַ���
					 * \param buffer ����ת������Ļ�����
					 * \param size �������ַ����ĳ���
					 * \return ��������ַ���Ϊ�գ�����NULL�����sizeΪNULL�����᷵����Ҫ�ĳ��ȣ�����ɹ�����д����ַ���
					 */
					ZERO_BASEAPI size_t WideToMuti_S(const std::wstring& str, std::string& buffer, size_t size);

					/**
					 * \brief �˲���д��2023/8/2.
					 * \brief ����WideToMuti
					 *
					 * \param str �����õ�std::wstring�ַ���
					 * \param buffer ����ת������Ļ�����
					 * \param size �������ַ����ĳ���
					 * \return ��������ַ���Ϊ�գ�����NULL�����sizeΪNULL�����᷵����Ҫ�ĳ��ȣ�����ɹ�����д����ַ���
					 */
					static size_t MutiToWide_S(const std::wstring& str, std::string& buffer, size_t size);
				}

				typedef size_t(CALLBACK* curlCallBack)(char* ptr, size_t size, size_t nmemb, void* stream);

				/**
				 * \brief �˲���д��2023/8/18.
				 * \brief ��url�л�ȡ���ݣ���GET����ʽ
				 * \brief ��ע
				 * \brief ʹ��ʱ���ܻ�����curl�ڲ��쳣
				 *
				 * \param url
				 * \return ����ܻ�ȡ�����ݣ�����������GET���󣬷��򷵻�ֵΪ�յ�std::string
				 */
				ZERO_BASEAPI std::string getDataFromUrl(std::string url);

				ZERO_BASEAPI std::string postDataRequest(std::string url, std::string param);

				ZERO_BASEAPI CURLcode getDownload(std::string filename, std::string url);

				ZERO_BASEAPI CURLcode postDownload(std::string filename, std::string url, std::string param);
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
			�ṩ���ڲ��ֲ������û��Զ��������������ռ�
			Ĭ��������Tool�����ռ���
			�����ô������ռ��ṩ��������
			��ʹ�ã�
			using namespace cloudgameZero::Foundation::Tool;
			*/
			inline namespace Libteral
			{
				/**
				* \brief �˲���д��2023/8/5
				 *\brief �����ֽ�ת��Ϊ���ֽ�.
				 *
				 * \param str ��ת�����ַ���
				 * \param size ����Ҫ�Ĳ�����Ĭ��Ϊstr�ĳ���
				 * \return ����std::wstring������Ϊstr
				 */
				inline static _NODISCARD std::wstring operator"" _zw(const char* str, size_t size)
				{
					std::wstring ret = function::Experiment::MutiToWide(str);
					return ret;
				}

				/**
				 * \brief �˲���д��2023/8/5.
				 * \brief �����ֽ�ת��Ϊ���ֽ�
				 * \param str ��ת�����ַ���
				 * \param size ����Ҫ�Ĳ�����Ĭ��Ϊstr�ĳ���
				 * \return ����std::string������Ϊstr
				 */
				inline static _NODISCARD std::string operator"" _zs(const wchar_t* str, size_t size)
				{
					std::string ret = function::Experiment::WideToMuti(str);
					return ret;
				}

				/**
				 * \brief �˲���д��2023/8/5.
				 * \brief ���ض��ֽ��ַ����ĳ��ȣ��൱��strlen
				 * \str �ַ���
				 * \return �����ַ����ĳ���
				 */
				static _NODISCARD inline constexpr size_t operator"" _zsl(const char* str, size_t size)
				{
					return size;
				}

				/**
				 * \brief �˲���д��2023/8/5.
				 * \brief ���ؿ��ֽ��ַ����ĳ��ȣ��൱��strlen
				 * \str �ַ���
				 * \return �����ַ����ĳ���
				 */
				static _NODISCARD inline constexpr size_t operator"" _zwl(const wchar_t* str, size_t size)
				{
					return size;
				}

				/**
				 * \brief �˲���д��2023/8/5.
				 * \brief ��size_tת��Ϊstd::string
				 * \param num ��ת��������
				 * \return ����std::string
				 */
				static _NODISCARD inline std::string operator"" _zIS(size_t num)
				{
					return std::to_string(num);
				}

				/**
				 * \brief �˲���д��2023/8/5.
				 * \brief ���ַ���������ת��Ϊint.
				 *
				 * \return ��������쳣����������NULL������������������ؽ����õ�������
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
					/* �������ṩ��operator"" _zF()��operator"" _zWF�ĺ���ģ��*/
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
				 * \brief �˲���д��2023/8/5.
				 * \brief ��ʽ��һ���ַ������÷�����std::format.
				 *
				 * \return ����lambda���ʽ������(����Ϊ��Ҫ��ʽ���Ĳ���)
				 */
				template<structs::argsM a>
				static inline constexpr auto operator"" _zF() {
					return[=]<class ...T>(T... _args) { return std::format(a.str, _args...); };
				}

				/**
				 * \brief �˲���д��2023/8/5.
				 * \brief ��ʽ��һ���ַ������÷�����std::format.
				 *
				 * \return ����lambda���ʽ������(����Ϊ��Ҫ��ʽ���Ĳ���)
				 */
				template<structs::argsW a>
				static inline constexpr auto operator"" _zWF() {
					return[=]<class ...T>(T... _args) { return std::format(a.str, _args...); };
				}


				/**
				* \brief �˲���д��2023/8/20.
				 *\brief ���ڼ��������ʽ�Ƿ����ַ���ƥ��.
				 */
				template<structs::regexStruct rege>
				static inline constexpr auto operator"" _matches()
				{
					return [=](const char* regex) -> bool { return std::regex_match(rege.str, std::regex(regex)); };
				}

				/**
				 * \brief �˲���д��2023/8/20.
				 * \brief ���ڼ��������ʽ�Ƿ����ַ����д���ƥ����Ӵ�.
				 */
				template<structs::regexStruct rege>
				static inline constexpr auto operator"" _rsearch()
				{
					return [=](const char* regex) -> bool {return std::regex_search(rege.str, std::regex(regex)); };
				}
			}

			/* �������ռ�洢�˱�������õ�C��������ʱ���� */
			/* ���к�������C��������ʱ���е���
			 * ��ע�⣺
			 * ���������к�����Ϊ��ȫ�ģ�������ð�ȫ��飬�뾡����ʹ�ð�ȫ�汾�ĺ���
			 */
			namespace NOCRT_SAFEFUNC
			{
				ZERO_BASEAPI __inline char* __CRTDECL ctime(_In_ time_t const* const _Time);

				ZERO_BASEAPI __inline int __CRTDECL sprintf(char* const _Buffer, char const* const _Format, ...);

				ZERO_BASEAPI FILE* __CRTDECL fopen(_In_z_ char const* _FileName, _In_z_ char const* _Mode);
			}
		}
		namespace Warpper
		{
			/**
			 * ���ڽ�PCWSTRת��ΪHstring�İ�װ��.
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

			/* �������*/
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

	/* ��������cloudgamefixZero�ⶨ��Ľӿھ����Դ������ռ� .*/

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

		ZERO_BASEAPI void InitConfig(std::string filename);

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

		ZERO_BASEAPI void getLogDictionary(std::string& str);

		ZERO_BASEAPI std::string parseFileName()
		{
			try {
				if (!this->IsInit())
				{
					PrintError("��Ҫ��ʼ������");
					return std::string();
				}
				std::string file = this->_root["logToFile"]["File"]["filename"].GetString();
				if (this->_root["logToFile"]["File"]["format"].GetBool())
				{
					std::string fmt = this->_root["logToFile"]["File"]["filename"].GetString();
				}
				return file;
			}
			catch (...)
			{
				genDefaultSettings(this->files);
				return parseFileName();
			}
		}

		ZERO_BASEAPI int getMin();

		ZERO_BASEAPI _ostream getLogObjectType();

		ZERO_BASEAPI _wostream getWideOstreamType();

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

		ZERO_BASEAPI static void genDefaultSettings(std::string filename);

		ZERO_BASEAPI static void genFrameworkHelper(rapidjson::Document& Dom) noexcept;

		ZERO_BASEAPI static void genDefaultSettingsHelper(rapidjson::Document& Dom) noexcept;

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
		*  \brief �˲���д��2023/8/12
		 * \brief ��־�๹�캯��.
		 *
		 * \param init �����Ƿ��ڹ����ڼ��ʼ��
		 * \param file ������־ʹ�õ������ļ���
		 * \param CallBack ��ѡ�����ϣ�������н׶��޸����ã��˴�Ӧ�ṩһ���������ڻص������������÷�ʽ���д��ݣ������ϣ��ʹ����ָ����Ϊnullptr
		 * \param 	����ָ��ԭ�ͣ� typedef void(__stdcall* logConfCallBackFunc)(rapidjson::Document& Dom);
		 * \param mark ���ڱ����־��Դ����ѡ����ʾ�������Դ��
		 * \param server ���ڱ��ģ�飨��ѡ����ʾģ������
		 */
		explicit log(bool init, std::string file = "logConfig.json", logConfCallBackFunc CallBack = nullptr, std::string mark = "main", std::string server = "ZERO") : times(NULL), mark(mark), server(server)
		{
			if (!std::filesystem::exists(file))
			{
				DEBUG_MESSAGE("δ�ҵ������ļ�\n׼������һ��Ĭ������");
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
		 * ÿһ����־������Ƕ�һ�޶���ʵ������˿ղι���Ϳ��������Լ���ֵ������������ṩ���û�.
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

		void Init()
		{
			using namespace Foundation::Tool;
			rapidjson::Document& Dom = conf->getDocment();
			if (this->HasInit())
			{
				DEBUG_MESSAGE("���ʵ���Ѿ�����ʼ������");
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
				DEBUG_MESSAGE("Ϊʲô��Ҫ�����߶������õ�����½��г�ʼ�����������Ƿ��������Ϊ֮?");
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
					std::string filename = conf->getFileName();
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
					throw std::runtime_error("�޷����ļ����������쳣");
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
					throw std::runtime_error("�޷���ȡostream����");
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
					throw std::runtime_error("�޷���ȡostream����");
				}
				this->EnableTerminalOut.store(true);
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
		��־���ṩ�����������
		���������<<��������ʱ����ostream����֧��shared_ptr��unique_ptr��Ԫ����

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
		��־���ṩ��6���ȼ��ĳ�Ա�������ڼ�¼��־
		ÿ���ȼ�ӵ��2���ɱ����ģ���2����ͨ��Ա����
		���ڴ���std::string��std::wstring��������
		ģ�庯������ͨ��std::format�����ʽ���ַ���
		ע��
		logConfig�ĵȼ�������С��¼�ȼ�������ȼ����ΪTrace�������еȼ���־���ɼ�
		������ȼ�ΪInfo����Trace��Debug�����ᱻ��¼����ֻ�Ǳ���ʱ�洢��list����
		�������ΪDebugģʽ���⽫������һ����ͼ�¼�ȼ�ΪTrace�������ļ�����֮ΪInfo
		==================================================================*/

		/*================================================================
		| ������ʱ��Ҫ׷�ٵ���ʱ��ʹ�ô˳�Ա������ӡ��־
		| ��logConfig�ȼ�ΪTraceʱ���˳�Ա������ӡ����־������¼���ļ�����ӡ���ն�
		| ����ȼ�����Trace�������־����ʱ�洢��list������
		================================================================*/

		/**
		 * \brief ������д��2023/8/13.
		 * \brief ��ӡ�ȼ�ΪTrace����־
		 *
		 * \param message ��Ϣ����
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
		 * \brief ������д��2023/8/13.
		 * \brief ��ӡ�ȼ�ΪTrace����־
		 *
		 * \param message ��Ϣ����
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
		 * \brief ������д��2023/8/13.
		 * \brief �����ʽ���ַ�������ӡ�ȼ�ΪTrace����־
		 *
		 * \param fmt ����ʽ���ַ���
		 * \param args ��ʽ������
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
		 * \brief ������д��2023/8/13.
		 * \brief �����ʽ���ַ�������ӡ�ȼ�ΪTrace����־
		 *
		 * \param fmt ����ʽ���ַ���
		 * \param args ��ʽ������
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
		| ������ʱ�����ڵ���ʱ��ʹ�ô˳�Ա������ӡ��־
		| ��logConfig�ȼ�Ϊdebugʱ���˳�Ա������ӡ����־������¼���ļ�����ӡ���ն�
		| ����ȼ�����debug�������־����ʱ�洢��list������
		==================================================================*/

		/**
		 * \brief ������д��2023/8/13.
		 * \brief ��ӡ�ȼ�ΪDebug����־
		 *
		 * \param message ��Ϣ����
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
		 * \brief ������д��2023/8/13.
		 * \brief ��ӡ�ȼ�ΪDebug����־
		 *
		 * \param message ��Ϣ����
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
		 * \brief ������д��2023/8/13.
		 * \brief �����ʽ���ַ�������ӡ�ȼ�ΪDebug����־
		 *
		 * \param fmt ����ʽ���ַ���
		 * \param args ��ʽ������
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
		 * \brief ������д��2023/8/13.
		 * \brief �����ʽ���ַ�������ӡ�ȼ�ΪDebug����־
		 *
		 * \param fmt ����ʽ���ַ���
		 * \param args ��ʽ������
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
		| ���������ڼ�¼��������ʱ��ʹ�ô˳�Ա������ӡ��־
		| ��logConfig�ȼ�ΪInfoʱ���˳�Ա������ӡ����־������¼���ļ�����ӡ���ն�
		| ����ȼ���ΪInfo�������־����ʱ�洢��list������
		==============================================================*/

		/**
		 * \brief ������д��2023/8/13.
		 * \brief ��ӡ�ȼ�ΪInfo����־
		 *
		 * \param message ��Ϣ����
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
		 * \brief ������д��2023/8/13.
		 * \brief ��ӡ�ȼ�ΪInfo����־
		 *
		 * \param message ��Ϣ����
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
		 * \brief ������д��2023/8/13.
		 * \brief �����ʽ���ַ�������ӡ�ȼ�ΪInfo����־
		 *
		 * \param fmt ����ʽ���ַ���
		 * \param args ��ʽ������
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
		 * \brief ������д��2023/8/13.
		 * \brief �����ʽ���ַ�������ӡ�ȼ�ΪInfo����־
		 *
		 * \param fmt ����ʽ���ַ���
		 * \param args ��ʽ������
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
		| ���������ڼ�¼������С����ʱ��ʹ�ô˳�Ա������ӡ��־��������Ҫ�����stacktrace������ӡ���ö�ջ
		| �������޸ĵȼ���warn�����
		| ��Ϊɸѡ�������־���ܻᵼ�¿�ά���Խ���
		===============================================================================*/

		/**
		 * \brief ������д��2023/8/13.
		 * \brief ��ӡ�ȼ�ΪWarn����־
		 *
		 * \param message ��Ϣ����
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
		 * \brief ������д��2023/8/13.
		 * \brief ��ӡ�ȼ�ΪWarn����־
		 *
		 * \param message ��Ϣ����
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
		 * \brief ������д��2023/8/13.
		 * \brief �����ʽ���ַ�������ӡ�ȼ�ΪWarn����־
		 *
		 * \param fmt ����ʽ���ַ���
		 * \param args ��ʽ������
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
		 * \brief ������д��2023/8/13.
		 * \brief �����ʽ���ַ�������ӡ�ȼ�ΪWarn����־
		 *
		 * \param fmt ����ʽ���ַ���
		 * \param args ��ʽ������
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
		| ���������ڼ�¼�����Ĵ���ʱ��ʹ�ô˳�Ա������ӡ��־��������Ҫ�����stacktrace������ӡ���ö�ջ
		| �������޸ĵȼ���warn�����
		| ��Ϊɸѡ�������־���ܻᵼ�¿�ά���Խ���
		===============================================================================*/

		/**
		 * \brief ������д��2023/8/13.
		 * \brief ��ӡ�ȼ�ΪError����־
		 *
		 * \param message ��Ϣ����
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
		 * \brief ������д��2023/8/13.
		 * \brief ��ӡ�ȼ�ΪError����־
		 *
		 * \param message ��Ϣ����
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
		 * \brief ������д��2023/8/13.
		 * \brief �����ʽ���ַ�������ӡ�ȼ�ΪError����־
		 *
		 * \param fmt ����ʽ���ַ���
		 * \param args ��ʽ������
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
		 * \brief ������д��2023/8/13.
		 * \brief �����ʽ���ַ�������ӡ�ȼ�ΪError����־
		 *
		 * \param fmt ����ʽ���ַ���
		 * \param args ��ʽ������
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
		| ���������ڼ�¼��������ʱ�п��ܻ�����Ĵ���ʱ��ʹ�ô˳�Ա������ӡ��־��������Ҫ�����stacktrace������ӡ���ö�ջ
		| ǿ�Ҳ������޸ĵȼ����˵ȼ�
		| ��Ϊɸѡ�������־���ܻᵼ�¿�ά���Խ��ͣ��ҿ��ܻ��д�������Ϣ��©
		==============================================================================================*/

		/**
		 * \brief ������д��2023/8/13.
		 * \brief ��ӡ�ȼ�ΪFatal����־
		 *
		 * \param message ��Ϣ����
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
		 * \brief ������д��2023/8/13.
		 * \brief ��ӡ�ȼ�ΪFatal����־
		 *
		 * \param message ��Ϣ����
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
		 * \brief ������д��2023/8/13.
		 * \brief �����ʽ���ַ�������ӡ�ȼ�ΪFatal����־
		 *
		 * \param fmt ����ʽ���ַ���
		 * \param args ��ʽ������
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
		 * \brief ������д��2023/8/13.
		 * \brief �����ʽ���ַ�������ӡ�ȼ�ΪFatal����־
		 *
		 * \param fmt ����ʽ���ַ���
		 * \param args ��ʽ������
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
				throw std::invalid_argument("����Ĳ���");
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
		std::atomic_bool EnableTerminalOut;
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
#define ZERO_DEPRECATED_FUNC(reason) [[deprecated(reason)]]

		__interface Sha1 : public IUnknown
		{
		public:
			virtual void reset() = 0;
			virtual bool update(const BYTE* input, DWORD size) = 0;
			virtual bool update(const char* input) = 0;
			virtual void getDigest(BYTE* output) = 0;
			virtual void getDigestString(char* output, bool toUpperCase = false) = 0;
		};

		enum class InterfaceType
		{
			cgSystem,
			cgTool
		};

		/**
		* \brief �˲���д��2023/7/27
		* \brief �˺������ڻ�ȡcgSystem��cgFix��IUnknown�ӿ�
		* \brief �������ٶ�������ʼ����󷵻�ָ��sigmaInterface��װ��һ��ָ��.
		* \brief ע�⣺
		* \brief �˺�����ʵ�������ⲿ����ģ����ֱ��ʹ�ã����ᷢ��LNK���Ӵ���
		* \brief ��ע���˺�������IUnknown�ӿ��У���дQueryInterface�ķ����������ѯcgFix��cgSystem�ӿڵ�GUID
		* \brief ��ΪcgSystem�ӿ���cgFix�������࣬����ĳЩ�ӿ�ʵ��
		* \brief ����û���ѯʹ����cgFix��GUID
		* \brief �������cgFix��GUID�󶨵Ķ��󣬶�����cgSystem�ĺ����п�����ͨ������ȷ��Ϊ�ͳ�ҹ���Դ�ᴮ�ĳ�Ʊ
		*
		* \return ��������£�����������cgSystem��������ָ��
		* \return ��ʹ����ָ��ʱ����ص���Realease�����黹��Դ
		*/
		IUnknown* (CALLBACK* cgSystemCreateInstance)();

		/**
		* \brief �˲���д��2023/7/28
		* \brief �˺������ڻ�ȡcgTool��IUnknown�ӿ�
		* \brief �������ٶ�������ʼ����󷵻�ָ��sigmaInterface��װ��һ��ָ��.
		* \brief ע�⣺
		* \brief �˺�����ʵ�������ⲿ����ģ����ֱ��ʹ�ã����ᷢ��LNK���Ӵ���
		* \brief ��ע
		* \brief �˺���ʵ���ṩ��QueryInterface�ɲ�ѯcgTool��cgSoftware�Լ�asciiStyle�Լ�cgTool_s�Ľӿڣ���ͬ��
		* \brief ��ͬ�ӿڶԽӵõ��Ķ���������в������Լ��ķ���������Ȼ�п�����ͨ������ȷ��Ϊ�ͳ�ҹ���Դ�ᴮ�ĳ�Ʊ
		* \brief ��ʵ����QueryInterface����cgTool_s,cgTool,cgSoftware,asciiStyle����
		*
		* \return ��������£�����������cgTool��������ָ��
		* \return ��ʹ����ָ��ʱ����ص���Realease�����黹��Դ
		*/
		IUnknown* (CALLBACK* cgToolCreateInstance)();

		/**
		 * �����޸���������Ϸϵͳ�Ľӿ�.
		 */
		interface cgFix : public IUnknown
		{
			enum class mode { reserved, cloudgame, cloudpc };
			virtual BOOL fixSystem(_In_ mode mode) = 0;
			virtual void fixFile(_In_ mode mode) = 0;
			virtual void resetGroupPolicy() = 0;
			virtual HRESULT repairGameFile() = 0;
		};

		/* ���cgFix��cgSystem�ṩ�˸��๦�ܣ�ͬʱ֧�ֲ�ѯcgFix�ӿڣ����Կ����Ƕ�cgFix��ǿ���� */
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
			*  \brief �˲���д��2023/7/27
			 * \brief �˺��������������õ�ǰ�û��ı�ֽ.
			 *
			 * \param path ��ֽ��·��
			 */
			virtual void setWallpaper(IN const std::string& path) = 0;

			/**
			 * ��URL����ȡһ����ֽ��󲢸���.
			 *
			 * \param url url��·��
			 * \param path �����·��
			 */
			virtual void downloadWallpaperAndSet(IN const std::string& url, IN const std::string path) = 0;

			/**
			 * �޸�ϵͳ��ʾ�ķֱ���.
			 * \brief ptr->changeRe(1980,1080);
			 *
			 * \param length ����
			 * \param width ���
			 *
			 */
			virtual void changeResolution(IN short length, IN short width) = 0;

			/**
			 * ʹ��ö�����޸ķֱ��ʣ����changeRe����Ӱ�ȫ.
			 *
			 * \param resolution
			 */
			virtual void changeResolution_s(IN Resolution resolution) = 0;

			/**
			 * ��Windows������ѡ��һ����������.
			 *
			 * \param theme ��Theme�е�ö����ѡ��
			 */
			virtual void changeTheme(IN Theme theme) = 0;
		};


		/* �洢�ڲ��ӿڵ����� */
		namespace sigmaInterface
		{
			/* �洢������д�ľ���ʵ�֣�����cloudgameFixZero������cpp�ļ����ڴ������ռ������Լ�����,��cloudgamefix.hpp�������ṩ�йش������ռ�������κ����� */
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
			}

			/* �ӿ�id��������cloudgameFixZero�ӿڣ���ʹ�ô�id */
			namespace guid
			{
				extern "C++" const IID IID_CLOUDGAME_FIX_ZERO_CGFIX;	/* cgFix�ӿ�ID */
				extern "C++" const IID IID_CLOUDGAME_FIX_ZERO_CGSYSTEM;	/* cgSystem�ӿ�ID */
				extern "C++" const IID IID_CLOUDGAME_FIX_ZERO_CGTOOL;	/* cgTool�ӿ�ID */
				extern "C++" const IID IID_CLOUDGAME_FIX_ZERO_CGTOOLS;	/* ������ڰ�ȫ���ܵ�cgTool�ӿ�ID����cgToolһ���ṩ */
				extern "C++" const IID IID_CLOUDGAME_FIX_ZERO_CGSOFTWARE;	/* ��ƻ���cgTool��ȫ���ܵ������ӿ� */
				extern "C++" const IID IID_CLOUDGAME_FIX_ZERO_ASCIISTYLE;	/* ascii�ַ���Ԥ����ӿ� */
			}
		}
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
	/* �������ռ��ṩ�����ڵ���Windows֪ͨ�ĺ������࣬����WinToast���޸� */
	namespace ToastPlatform
	{
		/* API�����ռ�ͨ���������ռ��ȡö�ٳ��� */
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
		/* ���ڻ�ȡAPI */
		namespace API
		{
			/* �������ռ�洢������ʱ���ܱ�Ҫ�Ĺ��ߺͳ��� */
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

				/* �������ռ�洢��֪ͨ��Ҫ�ĺ��� */
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
						ToastPlatformLog()->info("Ĭ�ϵĿ�ִ���ļ�λ��Ϊ�� {}", Foundation::Tool::function::Experiment::WideToMuti(path));
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
							ToastPlatformLog()->info("Ĭ�ϵĿ�ݷ�ʽ�洢·��Ϊ�� {}", Foundation::Tool::function::Experiment::WideToMuti(path));
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
							ToastPlatformLog()->info("Ĭ�ϵĿ�ݷ�ʽ�ļ��洢·��Ϊ�� {}", Foundation::Tool::function::Experiment::WideToMuti(path));
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
			/* Toast�¼��ӿ� */
			namespace Event
			{
				/* ����ӿڣ�������֪ͨ����ʵ�ִ˽ӿ����еĳ��󷽷������� */
				__interface ToastPlatformHandler
				{
					virtual void Activated() const = 0;
					virtual void Activated(int actionIndex) const = 0;
					virtual void Dismissed(Enums::ToastDismissalReason state) const = 0;
					virtual void Failed() const = 0;
				};

				/* �ڵ���ʱshowToastʱ�����ᰲװ�¼� */
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

			/* Windows֪ͨ��ʹ�ô˽ṹ�� */
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
						Libray::Util::ToastPlatformLog()->info("��ѡ���Toastģ���֧�֣� {} ��", this->_textFields.size());
						return;
					}
					this->_textFields[position] = txt;
				}

				void setImagePath(_In_ std::wstring const& imgPath, _In_ Enums::CropHint cropHint = Enums::CropHint::Square)
				{
					Libray::Util::ToastPlatformLog()->info(L"����ͼ��·��Ϊ : {}", imgPath);
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
						PrintError("ToastNotification�������ִ���");
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
						DEBUG_MESSAGE(L"�����û�ģ��ID�ܳ��Ȳ�Ӧ�ó���127");
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
						Libray::Util::ToastPlatformLog()->warn("���棺����Ҫ��aumi����appname����һ�����ƣ�������ֱ�ӳ�ʼ��");
						return false;
					}
					if (_shortcutPolicy != Enums::ShortcutPolicy::SHORTCUT_POLICY_IGNORE)
					{
						if (createShortcut() < 0) {
							setError(error, Enums::ToastError::ShellLinkNotCreated);
							Libray::Util::ToastPlatformLog()->warn("���Ҫ����Toast֪ͨ���������ṩ��һ��Aumi��һ���ڿ�ʼ�˵��Ŀ�ݷ�ʽ(��Ӧ�ú��Դ���)");
							return false;
						}
					}
					if (FAILED(SetCurrentProcessExplicitAppUserModelID(_aumi.c_str())))
					{
						setError(error, Enums::ToastError::InvalidAppUserModelID);
						Libray::Util::ToastPlatformLog()->error("�޷�����aumi��ĳЩ���ÿ��ܳ����˴���");
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
						Libray::Util::ToastPlatformLog()->error("����������������˾��ʱ������Ҫ��ʼ��ʵ������ʹ��");
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
						Libray::Util::ToastPlatformLog()->info("������˾ʧ�ܣ�. ����: {}", result);
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
						Libray::Util::ToastPlatformLog()->warn("������֪ͨ��ʱ�����˴�����Ҫ��ʼ��ʵ����������");
						return id;
					}
					if (!handler)
					{
						this->setError(error, Enums::ToastError::InvalidHandler);
						Libray::Util::ToastPlatformLog()->error("��Ч���¼����������������Ϊ��ָ��");
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
								/* �˴����Ὺʼ����Toast xml�ļ� */
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
										Libray::Util::ToastPlatformLog()->warn(L"��ǰ�汾��֧�ָ��ִ�����: -> (Actions/Sounds/Attributes)", Libray::Util::AsString(xmlDocument));
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
														Libray::Util::ToastPlatformLog()->info(L"����Toast�õ���XML����: {}", Libray::Util::AsString(xmlDocument));
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
						Libray::Util::ToastPlatformLog()->warn("�����û�ģ�ͻ��û����У�������һ��Ϊ��");
						return Enums::ShortcutResult::SHORTCUT_MISSING_PARAMETERS;
					}
					if (!this->_hasCoInitialized)
					{
						HRESULT initHr = CoInitializeEx(nullptr, COINIT::COINIT_MULTITHREADED);
						if (initHr != RPC_E_CHANGED_MODE)
						{
							if (FAILED(initHr) && initHr != S_FALSE)
							{
								Libray::Util::ToastPlatformLog()->error("�޷���ʼ��COM�����!");
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
						DEBUG_MESSAGE(L"δ�ҵ���ݷ�ʽ�����Դ���һ��!");
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
				���º�������ʱ������C4267����Ϊsize_tת��UINT32����
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
					//�ڴ˲�����Ҫִ�е�ָ��
				}
				virtual void Activated(int actionIndex) const
				{
					//�ڴ˲�����Ҫִ�е�ָ��
				}
				virtual void Dismissed(Enums::ToastDismissalReason state) const
				{
					//�ڴ˲�����Ҫִ�е�ָ��
				}
				virtual void Failed() const
				{
					//�ڴ˲�����Ҫִ�е�ָ��
				}
			};
		}
	}
}
#ifndef OPEN_SOURCES_CLOUDGAMEFIXZERO_API
#pragma comment(lib,"cloudgamefix")
#endif
#else
#error cloudgameFixZero����Ҫ��װboost�Ķ�ջ׷�ٿ��Լ�rapidjson�⣬ͬʱ�˿��֧��C++20������
#endif // _HAS_CXX20
#endif // CLOUDGAME_FIX_ZERO_H