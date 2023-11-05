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

namespace cloudgameZero
{
	namespace Infomation
	{
		
	}

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

				class __WinNotification : public WinNotification
				{
				public:
					explicit __WinNotification() : _isInitialized(false), _hasCoInitialized(false) {}
					virtual ~__WinNotification();
					virtual HRESULT QueryInterface(const IID& iid, void** ppv) override;
					virtual ULONG AddRef() override;
					virtual ULONG Release() override;
					virtual bool Init(_Out_opt_ Enums::ToastError* error = nullptr) override;
					virtual bool hide(_In_ INT64 id) override;
					virtual INT64 show(_In_ ToastTemplate const& toast, _In_ ToastPlatformHandler* eventHandler, Enums::ToastError* error = nullptr) override;
					virtual void clear() override;
					virtual Enums::ShortcutResult createShortcut();
					virtual bool isInit() const	override										 { return this->_isInitialized; }
					virtual std::wstring const& getAppName() const override						 { return this->_appName; };
					virtual std::wstring const& getAppUserModelId() const override				 { return this->_aumi; };
					virtual void setAppUserModelId(_In_ std::wstring const& aumi) override		 { this->_aumi = aumi; }
					virtual void setAppName(_In_ std::wstring const& AppName) override			 { this->_appName = AppName; }
					virtual void setShortcutPolicy(_In_ Enums::ShortcutPolicy policy) override	 { this->_shortcutPolicy = policy; }
				private:
					ULONG ref;
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
								return;
							if (_previouslyTokenRemoved)
								return;
							if (!_notify.Get())
								return;
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
					inline void markAsReadyForDeletion(_In_ INT64 id);
					inline HRESULT validateShellLinkHelper(_Out_ bool& wasChanged);
					HRESULT createShellLinkHelper();
					ComPtr<IToastNotifier> notifier(_In_ bool* succeded) const;
					inline void setError(_Out_opt_ Enums::ToastError* error, _In_ Enums::ToastError value)
					{
						if (error) {
							*error = value;
						}
					}
				};

				extern std::unordered_map<std::string, delegate<void*>> registry = {
					{"{5DD98957-02FC-4583-A25C-14A69321F2F0}",[]() {return new __cgFix; }},
					{"{A3872F59-C8AF-467E-8BF5-DF19FB77149E}",[]() {return new __cgSystem; }},
					{"{15DD4DD4-3E31-4F13-8E40-D88609D80B06}",[]() {return new __WinNotification; }}
				};

				namespace helper
				{
					class ToastComponentHelper
					{
					public:
						ToastComponentHelper() = default;

						~ToastComponentHelper() = default;

						HRESULT setImageField(_In_ std::wstring const& path, _In_ bool isToastGeneric, _In_ bool isCropHintCircle)
						{
							using namespace cloudgameZero::Foundation::Warpper;
							assert(path.size() < MAX_PATH);
							wchar_t imagePath[MAX_PATH] = L"file:///";
							HRESULT hr = StringCchCatW(imagePath, MAX_PATH, path.c_str());
							do {
								if (FAILED(hr))
									break;
								ComPtr<IXmlNodeList> nodeList;
								hr = xml->GetElementsByTagName(HstringWrapper(L"image").Get(), &nodeList);
								if (FAILED(hr))
									break;
								ComPtr<IXmlNode> node;
								hr = nodeList->Item(0, &node);
								ComPtr<IXmlElement> imageElement;
								HRESULT hrImage = node.As(&imageElement);
								if (SUCCEEDED(hr) && SUCCEEDED(hrImage) && isToastGeneric)
								{
									hr = imageElement->SetAttribute(HstringWrapper(L"placement").Get(), HstringWrapper(L"appLogoOverride").Get());
									if (SUCCEEDED(hr) && isCropHintCircle)
										hr = imageElement->SetAttribute(HstringWrapper(L"hint-crop").Get(), HstringWrapper(L"circle").Get());
								}
								if (FAILED(hr))
									break;
								ComPtr<IXmlNamedNodeMap> attributes;
								hr = node->get_Attributes(&attributes);
								if (SUCCEEDED(hr))
								{
									ComPtr<IXmlNode> editedNode;
									hr = attributes->GetNamedItem(HstringWrapper(L"src"), &editedNode);
									if (SUCCEEDED(hr))
										Libray::Util::setNodeStringValue(imagePath, editedNode.Get(), xml.Get());
								}
							} while (false);
							return hr;
						}

						HRESULT addScenario(_In_ std::wstring const& scenario)
						{
							using namespace cloudgameZero::Foundation::Warpper;
							ComPtr<IXmlNodeList> nodeList;
							HRESULT hr = xml->GetElementsByTagName(HstringWrapper(L"toast"), &nodeList);
							if (FAILED(hr))
								return hr;
							UINT32 length;
							hr = nodeList->get_Length(&length);
							if (FAILED(hr))
								return hr;
							ComPtr<IXmlNode> toastNode;
							hr = nodeList->Item(0, &toastNode);
							if (FAILED(hr))
								return hr;
							ComPtr<IXmlElement> toastElement;
							hr = toastNode.As(&toastElement);
							if (SUCCEEDED(hr))
								hr = toastElement->SetAttribute(HstringWrapper(L"scenario"), HstringWrapper(scenario));
							return hr;
						}

						HRESULT addDuration(_In_ std::wstring const& duration)
						{
							using namespace cloudgameZero::Foundation::Warpper;
							ComPtr<IXmlNodeList> nodeList;
							HRESULT hr = xml->GetElementsByTagName(HstringWrapper(L"toast").Get(), &nodeList);
							if (FAILED(hr))
								return hr;
							UINT32 length;
							hr = nodeList->get_Length(&length);
							if (FAILED(hr))
								return hr;
							ComPtr<IXmlNode> toastNode;
							hr = nodeList->Item(0, &toastNode);
							if (FAILED(hr))
								return hr;
							ComPtr<IXmlElement> toastElement;
							hr = toastNode.As(&toastElement);
							if (SUCCEEDED(hr))
								hr = toastElement->SetAttribute(HstringWrapper(L"duration").Get(), HstringWrapper(duration).Get());
							return hr;
						}

						HRESULT addAction(_In_ std::wstring const& action, _In_ std::wstring const& arguments)
						{
							using namespace cloudgameZero::Foundation::Warpper;
							ComPtr<IXmlNodeList> nodeList;
							HRESULT hr = xml->GetElementsByTagName(HstringWrapper(L"actions").Get(), &nodeList);
							do {
								if (FAILED(hr))
									break;
								UINT32 length;
								hr = nodeList->get_Length(&length);
								if (FAILED(hr))
									break;
								ComPtr<IXmlNode> actionsNode;
								if (length > 0)
									hr = nodeList->Item(0, &actionsNode);
								else
								{
									do {
										hr = xml->GetElementsByTagName(HstringWrapper(L"toast").Get(), &nodeList);
										if (FAILED(hr))
											break;
										hr = nodeList->get_Length(&length);
										if (FAILED(hr))
											break;
										ComPtr<IXmlNode> toastNode;
										hr = nodeList->Item(0, &toastNode);
										if (FAILED(hr))
											break;
										ComPtr<IXmlElement> toastElement;
										hr = toastNode.As(&toastElement);
										if (SUCCEEDED(hr))
											hr = toastElement->SetAttribute(HstringWrapper(L"template").Get(), HstringWrapper(L"ToastGeneric").Get());
										if (SUCCEEDED(hr))
											hr = toastElement->SetAttribute(HstringWrapper(L"duration").Get(), HstringWrapper(L"long").Get());
										if (FAILED(hr))
											break;
										ComPtr<IXmlElement> actionsElement;
										hr = xml->CreateElement(HstringWrapper(L"actions").Get(), &actionsElement);
										if (FAILED(hr))
											break;
										hr = actionsElement.As(&actionsNode);
										if (FAILED(hr))
											break;
										ComPtr<IXmlNode> appendedChild;
										hr = toastNode->AppendChild(actionsNode.Get(), &appendedChild);
									} while (false);
								}
								if (SUCCEEDED(hr))
								{
									ComPtr<IXmlElement> actionElement;
									hr = xml->CreateElement(HstringWrapper(L"action").Get(), &actionElement);
									if (SUCCEEDED(hr))
										hr = actionElement->SetAttribute(HstringWrapper(L"content").Get(), HstringWrapper(action).Get());
									if (SUCCEEDED(hr))
										hr = actionElement->SetAttribute(HstringWrapper(L"arguments").Get(), HstringWrapper(arguments).Get());
									if (FAILED(hr))
										break;
									ComPtr<IXmlNode> actionNode;
									hr = actionElement.As(&actionNode);
									if (SUCCEEDED(hr))
									{
										ComPtr<IXmlNode> appendedChild;
										hr = actionsNode->AppendChild(actionNode.Get(), &appendedChild);
									}
								}
							} while (false);
							return hr;
						}

						HRESULT setAttributionTextField(_In_ std::wstring const& text)
						{
							using namespace cloudgameZero::Foundation::Warpper;
							Libray::Util::createElement(xml.Get(), L"binding", L"text", {L"placement"});
							ComPtr<IXmlNodeList> nodeList;
							HRESULT hr = xml->GetElementsByTagName(HstringWrapper(L"text").Get(), &nodeList);
							do {
								if (FAILED(hr))
									return hr;
								UINT32 nodeListLength;
								hr = nodeList->get_Length(&nodeListLength);
								if (FAILED(hr))
									break;
								for (UINT32 i = 0; i < nodeListLength; i++)
								{
									ComPtr<IXmlNode> textNode;
									hr = nodeList->Item(i, &textNode);
									if (FAILED(hr))
										continue;
									ComPtr<IXmlNamedNodeMap> attributes;
									hr = textNode->get_Attributes(&attributes);
									if (FAILED(hr))
										continue;
									ComPtr<IXmlNode> editedNode;
									if (FAILED(hr))
										continue;
									hr = attributes->GetNamedItem(HstringWrapper(L"placement").Get(), &editedNode);
									if (FAILED(hr) || !editedNode)
										continue;
									hr = Libray::Util::setNodeStringValue(L"attribution", editedNode.Get(), xml.Get());
									if (SUCCEEDED(hr))
										return setTextField(text, i);
								}
							} while (false);
							return hr;
						}

						HRESULT setTextField(_In_ std::wstring const& text, _In_ std::size_t pos)
						{
							ComPtr<IXmlNodeList> nodeList;
							HRESULT hr = xml->GetElementsByTagName(Foundation::Warpper::HstringWrapper(L"text").Get(), &nodeList);
							if (FAILED(hr))
								return hr;
							ComPtr<IXmlNode> node;
							hr = nodeList->Item(pos, &node);
							if (SUCCEEDED(hr))
								hr = Libray::Util::setNodeStringValue(text, node.Get(), xml.Get());
							return hr;
						}

						HRESULT setBindToastGeneric()
						{
							using namespace cloudgameZero::Foundation::Warpper;
							ComPtr<IXmlNodeList> nodeList;
							HRESULT hr = xml->GetElementsByTagName(HstringWrapper(L"binding").Get(), &nodeList);
							do {
								if (FAILED(hr))
									break;
								UINT32 length;
								hr = nodeList->get_Length(&length);
								if (FAILED(hr))
									break;
								ComPtr<IXmlNode> toastNode;
								hr = nodeList->Item(0, &toastNode);
								if (FAILED(hr))
									break;
								ComPtr<IXmlElement> toastElement;
								hr = toastNode.As(&toastElement);
								if (SUCCEEDED(hr))
									hr = toastElement->SetAttribute(HstringWrapper(L"template").Get(), HstringWrapper(L"ToastGeneric").Get());
							} while (false);
							return hr;
						}

						HRESULT setAudioField(_In_ std::wstring const& path, _In_opt_ Enums::AudioOption option = Enums::AudioOption::Default)
						{
							using namespace cloudgameZero::Foundation::Warpper;
							std::vector<std::wstring> attrs;
							if (!path.empty())
								attrs.push_back(L"src");
							if (option == Enums::AudioOption::Loop)
								attrs.push_back(L"loop");
							if (option == Enums::AudioOption::Silent)
								attrs.push_back(L"silent");
							Libray::Util::createElement(xml.Get(), L"toast", L"audio", attrs);
							ComPtr<IXmlNodeList> nodeList;
							HRESULT hr = xml->GetElementsByTagName(HstringWrapper(L"audio").Get(), &nodeList);
							do {
								if (FAILED(hr))
									break;
								ComPtr<IXmlNode> node;
								hr = nodeList->Item(0, &node);
								if (FAILED(hr))
									break;
								ComPtr<IXmlNamedNodeMap> attributes;
								hr = node->get_Attributes(&attributes);
								if (FAILED(hr))
									break;
								ComPtr<IXmlNode> editedNode;
								if (!path.empty())
								{
									if (SUCCEEDED(hr))
									{
										hr = attributes->GetNamedItem(HstringWrapper(L"src").Get(), &editedNode);
										if (SUCCEEDED(hr))
											hr = Libray::Util::setNodeStringValue(path, editedNode.Get(), xml.Get());
									}
								}
								if (FAILED(hr))
									break;
								switch (option)
								{
								case Enums::AudioOption::Loop:
									hr = attributes->GetNamedItem(HstringWrapper(L"loop").Get(), &editedNode);
									if (SUCCEEDED(hr))
										hr = Libray::Util::setNodeStringValue(L"true", editedNode.Get(), xml.Get());
									break;
								case Enums::AudioOption::Silent:
									hr = attributes->GetNamedItem(HstringWrapper(L"silent").Get(), &editedNode);
									if (SUCCEEDED(hr))
										hr = Libray::Util::setNodeStringValue(L"true", editedNode.Get(), xml.Get());
									break;
								default:
									break;
								}
							} while (false);
							return hr;
						}

						HRESULT setHeroImage(_In_ std::wstring const& path, _In_ bool isInlineImage)
						{
							using namespace cloudgameZero::Foundation::Warpper;
							ComPtr<IXmlNodeList> nodeList;
							HRESULT hr = xml->GetElementsByTagName(HstringWrapper(L"binding").Get(), &nodeList);
							do {
								if (FAILED(hr))
									break;
								UINT32 length;
								hr = nodeList->get_Length(&length);
								if (FAILED(hr))
									break;
								ComPtr<IXmlNode> bindingNode;
								if (length > 0)
									hr = nodeList->Item(0, &bindingNode);
								if (FAILED(hr))
									break;
								ComPtr<IXmlElement> imageElement;
								hr = xml->CreateElement(HstringWrapper(L"image").Get(), &imageElement);
								if (SUCCEEDED(hr) && isInlineImage == false)
									hr = imageElement->SetAttribute(HstringWrapper(L"placement").Get(), HstringWrapper(L"hero").Get());
								if (SUCCEEDED(hr))
									hr = imageElement->SetAttribute(HstringWrapper(L"src").Get(), HstringWrapper(path).Get());
								if (FAILED(hr))
									break;
								ComPtr<IXmlNode> actionNode;
								hr = imageElement.As(&actionNode);
								if (SUCCEEDED(hr))
								{
									ComPtr<IXmlNode> appendedChild;
									hr = bindingNode->AppendChild(actionNode.Get(), &appendedChild);
								}
							} while (false);
							return hr;
						}

						ComPtr<IXmlDocument> xml = nullptr;
					};


				}
			}

			inline namespace guid
			{
				extern const IID IID_CLOUDGAME_FIX_ZERO_IID_IcgFix = __uuidof(cgFix);
				extern const IID IID_CLOUDGAME_FIX_ZERO_IID_IcgSystem = __uuidof(cgSystem);
				extern const IID IID_CLOUDGAME_FIX_ZERO_IID_IcgToolA = __uuidof(cgToolA);
				extern const IID IID_CLOUDGAME_FIX_ZERO_IID_IcgToolW = __uuidof(cgToolW);
				extern const IID IID_CLOUDGAME_FIX_ZERO_IID_IcgToolA_s = __uuidof(__cgToolA_s);
				extern const IID IID_CLOUDGAME_FIX_ZERO_IID_IWinNotification = __uuidof(WinNotification);


				//This function is normally called by the createInstance function, which takes a uuid and compares it to the corresponding IUnknown pointer
				extern IUnknown* Query(_In_ const IID& iid)
				{
					LPOLESTR guid{};
					HRESULT hr = StringFromIID(iid, &guid);
					auto itr = registry.find(WideToMuti(guid));
					if (itr == registry.end()) {
						return nullptr;
					}
					return static_cast<IUnknown*>(itr->second());
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

bool cloudgameZero::Infomation::isSupportingModernFeatures()
{
	constexpr auto MinimumSupportedVersion = 6;
	return Libray::Util::getRealOSVersion().dwMajorVersion > MinimumSupportedVersion;
}

bool cloudgameZero::Infomation::isWin10AnniversaryOrHigher()
{
	return Libray::Util::getRealOSVersion().dwBuildNumber >= 14393;
}

#pragma region CGFIX
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
	/*API::ToastTemplate toast(Enums::ToastTemplateType::Text02);
	API::ToastNotification::instance()->setAppUserModelId(cloudgameZero::Infomation::AUMI);
	API::ToastNotification::instance()->setAppName(cloudgameZero::Infomation::APPNAME);
	API::ToastNotification::instance()->Init();*/
	/*toast.setSecondLine(L"出现此消息意味着程序完成了指令，并且函数已经完成");
	toast.setFirstLine(L"完成组策略重置指令");*/
	CL()->debug("准备删除组策略的文件");
	std::filesystem::remove_all("C:\\Windows\\System32\\GroupPolicy");
	std::filesystem::remove_all("C:\\Windows\\System32\\GroupPolicyUsers");
	CL()->info("开始执行重置指令");
	ShellExecuteA(NULL, "open", "cmd.exe", " /c gpupdate /force", NULL, SW_HIDE);
	CL()->info("成功完成调用");
	//API::ToastNotification::instance()->show(toast, new API::PreDefineHandler);
	//std::this_thread::sleep_for(std::chrono::milliseconds(100));
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
#pragma endregion

/*
cgFix接口结束
cgSystem接口开始
*/

#pragma region CGSYSTEM
HRESULT __cgSystem::QueryInterface(const IID& iid, void** ppv)
{
	if (iid == IID_CLOUDGAME_FIX_ZERO_IID_IcgFix){
		*ppv = dynamic_cast<cgFix*>(new __cgFix);
	}
	else if (iid == IID_CLOUDGAME_FIX_ZERO_IID_IcgSystem){
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
	if (this->ref--; this->ref == 0){
		delete this;
	}
	else{
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
#pragma endregion

extern void testNoti()
{
	API::notification* noti = new __WinNotification;
	API::ToastTemplate toast(Enums::ToastTemplateType::Text02);
	noti->setAppUserModelId(cloudgameZero::Infomation::AUMI);
	noti->setAppName(cloudgameZero::Infomation::APPNAME);
	noti->Init();
	noti->show(toast, new PreDefineHandler);
}

/* 通知实体类方法实现 */

#pragma region WINNOTIFICATION

HRESULT cloudgameZero::Interface::sigmaInterface::Implement::__WinNotification::QueryInterface(const IID& iid, void** ppv)
{
	if (iid == IID_CLOUDGAME_FIX_ZERO_IID_IWinNotification){
		*ppv = dynamic_cast<WinNotification*>(new __WinNotification);
	}
	else {
		return E_NOINTERFACE;
	}
	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return S_OK;
}

ULONG cloudgameZero::Interface::sigmaInterface::Implement::__WinNotification::AddRef()
{
	this->ref++;
	return this->ref;
}

ULONG cloudgameZero::Interface::sigmaInterface::Implement::__WinNotification::Release()
{
	if (this->ref--; this->ref == 0) {
		delete this;
	}
	else {
		return this->ref;
	}
	return NULL;
}

cloudgameZero::Interface::sigmaInterface::Implement::__WinNotification::~__WinNotification()
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

bool cloudgameZero::Interface::sigmaInterface::Implement::__WinNotification::Init(_Out_opt_ Enums::ToastError* error)
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
		if ((INT)createShortcut() < 0) {
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

bool cloudgameZero::Interface::sigmaInterface::Implement::__WinNotification::hide(_In_ INT64 id)
{
	if (!isInit())
	{
		Libray::Util::ToastPlatformLog()->error("发生错误在隐藏吐司的时候，你需要初始化实例才能使用");
		return false;
	}
	auto iter = _buffer.find(id);
	if (iter == _buffer.end())
		return false;
	auto succeded = false;
	auto notify = notifier(&succeded);
	if (!succeded)
		return false;
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

INT64 cloudgameZero::Interface::sigmaInterface::Implement::__WinNotification::show(_In_ ToastTemplate const& toast, _In_ ToastPlatformHandler* eventHandler, Enums::ToastError* error)
{
	using namespace cloudgameZero::Interface::sigmaInterface::Implement::helper;
	using namespace cloudgameZero::Foundation::Warpper;
	using namespace cloudgameZero::Foundation::dynamincLibrayFunc::function;
	std::shared_ptr<ToastPlatformHandler> handler(eventHandler);
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
	do {
		if (FAILED(hr))
			break;
		ComPtr<IToastNotifier> notifier;
		hr = notificationManager->CreateToastNotifierWithId(HstringWrapper(this->_aumi).Get(), &notifier);
		if (FAILED(hr))
			break;
		ComPtr<IToastNotificationFactory> notificationFactory;
		hr = Wrap_GetActivationFactory(HstringWrapper(RuntimeClass_Windows_UI_Notifications_ToastNotification).Get(), &notificationFactory);
		if (FAILED(hr))
			break;
		helper::ToastComponentHelper Dom;
		hr = notificationManager->GetTemplateContent(ABI::Windows::UI::Notifications::ToastTemplateType(toast.getType()), &Dom.xml);
		if (SUCCEEDED(hr) && toast.isToastGeneric())
			hr = Dom.setBindToastGeneric();
		UINT i = 0;
		for (auto& it : toast.getTextFields())
		{
			hr = Dom.setTextField(toast.getTextField(Enums::TextField(i)),i);
			i++;
		}
		if (!(SUCCEEDED(hr) && Infomation::isSupportingModernFeatures()))
		{
			Libray::Util::ToastPlatformLog()->warn(L"当前版本不支持该现代特性: -> (Actions/Sounds/Attributes)", Libray::Util::AsString(Dom.xml));
			break;
		}
		if (SUCCEEDED(hr) && !toast.getAttributionText().empty())
			hr = Dom.setAttributionTextField(toast.getAttributionText());
		std::array<WCHAR, 12> buf{};
		for (std::size_t i = 0, actionsCount = toast.getActionsCount(); i < actionsCount && SUCCEEDED(hr); i++)
		{
			_snwprintf_s(buf.data(), buf.size(), _TRUNCATE, L"%zd", i);
			hr = Dom.addAction(toast.getActionLabel(i), buf.data());
		}
		if (SUCCEEDED(hr))
			hr = (toast.getAudioPath().empty() && toast.getAudioOption() == Enums::AudioOption::Default) ? hr : Dom.setAudioField(toast.getAudioPath(),toast.getAudioOption());
		if (SUCCEEDED(hr) && toast.getDuration() != Enums::Duration::System)
			hr = Dom.addDuration((toast.getDuration() == Enums::Duration::Short) ? L"short" : L"long");
		if (SUCCEEDED(hr))
			hr = Dom.addScenario(toast.getScenario());
		if (FAILED(hr))
			break;
		bool isWin10AnniversaryOrAbove = Infomation::isWin10AnniversaryOrHigher();
		bool isCircleCropHint = isWin10AnniversaryOrAbove ? toast.isCropHintCircle() : false;
		hr = toast.hasImage() ? Dom.setImageField(toast.getImagePath(), toast.isToastGeneric(), isCircleCropHint) : hr;
		if (SUCCEEDED(hr) && isWin10AnniversaryOrAbove && toast.hasHeroImage())
			hr = Dom.setHeroImage(toast.getHeroImagePath(), toast.isInlineHeroImage());
		ComPtr<IToastNotification> notification;
		hr = notificationFactory->CreateToastNotification(Dom.xml.Get(), &notification);
		if (FAILED(hr))
			break;
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
		if (!(SUCCEEDED(hr) && SUCCEEDED(hrGuid)))
			break;
		hr = API::setEventHandler(notification.Get(), handler, expiration, activatedToken, dismissedToken, failedToken, [this, id]() { markAsReadyForDeletion(id); });
		if (FAILED(hr))
			this->setError(error, Enums::ToastError::InvalidHandler);
		if (FAILED(hr))
			break;
		this->_buffer.emplace(id, NotifyData(notification, activatedToken, dismissedToken, failedToken));
		Libray::Util::ToastPlatformLog()->info(L"构建Toast得到的XML内容: {}", Libray::Util::AsString(Dom.xml));
		hr = notifier->Show(notification.Get());
		if (FAILED(hr))
			this->setError(error, Enums::ToastError::NotDisplayed);
	} while (false);
	return FAILED(hr) ? -1 : id;
}

void cloudgameZero::Interface::sigmaInterface::Implement::__WinNotification::clear()
{
	auto succeded = false;
	auto notify = notifier(&succeded);
	if (!succeded)
		return;
	for (auto& data : _buffer)
	{
		auto& notifyData = data.second;
		notify->Hide(notifyData.notification());
		notifyData.RemoveTokens();
	}
	_buffer.clear();
}

Enums::ShortcutResult cloudgameZero::Interface::sigmaInterface::Implement::__WinNotification::createShortcut()
{
	if (this->_aumi.empty() || this->_appName.empty())
	{
		Libray::Util::ToastPlatformLog()->warn("错误：用户模型或用户名中，其中有一个为空");
		return Enums::ShortcutResult::SHORTCUT_MISSING_PARAMETERS;
	}
	if (!this->_hasCoInitialized)
	{
		do {
			HRESULT initHr = CoInitializeEx(nullptr, COINIT::COINIT_APARTMENTTHREADED);
			if (initHr == RPC_E_CHANGED_MODE)
				break;
			if (FAILED(initHr) && initHr != S_FALSE)
			{
				Libray::Util::ToastPlatformLog()->error("无法初始化COM库组件!");
				return Enums::ShortcutResult::SHORTCUT_COM_INIT_FAILURE;
			}
			else
				this->_hasCoInitialized = true;
		} while (false);
	}
	bool wasChanged;
	HRESULT hr = validateShellLinkHelper(wasChanged);
	if (SUCCEEDED(hr)) 
		return wasChanged ? Enums::ShortcutResult::SHORTCUT_WAS_CHANGED : Enums::ShortcutResult::SHORTCUT_UNCHANGED;
	return SUCCEEDED(createShellLinkHelper()) ? Enums::ShortcutResult::SHORTCUT_WAS_CREATED : Enums::ShortcutResult::SHORTCUT_CREATE_FAILED;
}

inline void cloudgameZero::Interface::sigmaInterface::Implement::__WinNotification::markAsReadyForDeletion(_In_ INT64 id)
{
	for (auto it = this->_buffer.begin(); it != this->_buffer.end();)
	{
		if (it->second.isReadyForDeletion())
		{
			it->second.RemoveTokens();
			it = this->_buffer.erase(it);
		}
		else
			it++;
	}
	auto const iter = _buffer.find(id);
	if (iter != _buffer.end())
		this->_buffer[id].markAsReadyForDeletion();
}

inline HRESULT cloudgameZero::Interface::sigmaInterface::Implement::__WinNotification::validateShellLinkHelper(_Out_ bool& wasChanged)
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
			break;
		ComPtr<IPersistFile> file;
		hr = IshellLinkptr.As(&file);
		if (FAILED(hr))
			break;
		hr = file->Load(path, STGM_READWRITE);
		if (FAILED(hr))
			break;
		ComPtr<IPropertyStore> store;
		hr = IshellLinkptr.As(&store);
		if (FAILED(hr))
			break;
		PROPVARIANT appIdPropVar;
		hr = store->GetValue(PKEY_AppUserModel_ID, &appIdPropVar);
		if (FAILED(hr))
			break;
		WCHAR AUMI[MAX_PATH];
		hr = cloudgameZero::Foundation::dynamincLibrayFunc::function::PropVariantToString(appIdPropVar, AUMI, MAX_PATH);
		wasChanged = false;
		if (FAILED(hr) || this->_aumi != AUMI)
		{
			if (this->_shortcutPolicy != Enums::ShortcutPolicy::SHORTCUT_POLICY_REQUIRE_CREATE)
				return E_FAIL;
			wasChanged = true;
			PropVariantClear(&appIdPropVar);
			hr = InitPropVariantFromString(_aumi.c_str(), &appIdPropVar);
			if (FAILED(hr))
				return hr;
			hr = store->SetValue(PKEY_AppUserModel_ID, appIdPropVar);
			if (FAILED(hr))
				break;
			hr = store->Commit();
			if (SUCCEEDED(hr) && SUCCEEDED(file->IsDirty()))
				hr = file->Save(path, TRUE);
		}
	} while (false);
	return hr;
}

HRESULT cloudgameZero::Interface::sigmaInterface::Implement::__WinNotification::createShellLinkHelper()
{
	if (_shortcutPolicy != Enums::ShortcutPolicy::SHORTCUT_POLICY_REQUIRE_CREATE)
		return E_FAIL;
	WCHAR exePath[MAX_PATH]{ L'\0' };
	WCHAR slPath[MAX_PATH]{ L'\0' };
	Libray::Util::defaultShellLinkPath(_appName, slPath);
	Libray::Util::defaultExecutablePath(exePath);
	HRESULT hr = NULL;
	do {
		if (hr = CoInitialize(NULL); FAILED(hr))
			return hr;
		ComPtr<IShellLinkW> IshellLinkptr;
		hr = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLinkW, (void**)&IshellLinkptr);
		if (FAILED(hr))
			break;
		ComPtr<IPersistFile> file;
		IshellLinkptr->SetPath(exePath);
		IshellLinkptr->SetWorkingDirectory(exePath);
		ComPtr<IPropertyStore> store;
		hr = IshellLinkptr.As(&store);
		if (FAILED(hr))
			break;
		PROPVARIANT appIdPropVar;
		hr = InitPropVariantFromString(this->_aumi.c_str(), &appIdPropVar);
		if (FAILED(hr))
			break;
		hr = store->SetValue(PKEY_AppUserModel_ID, appIdPropVar);
		if (FAILED(hr))
			break;
		hr = store->Commit();
		if (FAILED(hr))
			break;
		PropVariantClear(&appIdPropVar);
		hr = IshellLinkptr.As(&file);
		if (FAILED(hr))
			break;
		file->Save(slPath, TRUE);
		file->Release();
		IshellLinkptr->Release();
		CoUninitialize();
		return S_OK;
	} while (false);
	CoUninitialize();
	return hr;
}

ComPtr<IToastNotifier> cloudgameZero::Interface::sigmaInterface::Implement::__WinNotification::notifier(_In_ bool* succeded) const
{
	using namespace cloudgameZero::Foundation::dynamincLibrayFunc::function;
	using namespace cloudgameZero::Foundation::Warpper;
	ComPtr<IToastNotificationManagerStatics> notificationManager;
	ComPtr<IToastNotifier> notifier;
	HRESULT hr = Wrap_GetActivationFactory(HstringWrapper(RuntimeClass_Windows_UI_Notifications_ToastNotificationManager).Get(), &notificationManager);
	if (SUCCEEDED(hr))
		hr = notificationManager->CreateToastNotifierWithId(HstringWrapper(_aumi).Get(), &notifier);
	*succeded = SUCCEEDED(hr);
	return notifier;
}
#pragma endregion

extern void test()
{
	int* ptr = static_cast<int*>(registry["Test"]());
	std::cout << ptr << "\n";
	ptr = static_cast<int*>(registry["Test"]());
	std::cout << ptr << "\n";
}

#pragma warning(pop)