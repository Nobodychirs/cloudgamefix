#pragma once
#include"cgTool.h"

using namespace cloudgameZero;
using namespace cloudgameZero::ToastPlatform;
using namespace cloudgameZero::ToastPlatform::API;
using namespace cloudgameZero::Interface;
using namespace cloudgameZero::Interface::Exceptions;
using namespace cloudgameZero::Interface::sigmaInterface;
using namespace cloudgameZero::Interface::sigmaInterface::guid;
using namespace cloudgameZero::Interface::sigmaInterface::Implement;

static const char* installPath = "E:\\CloudGameFixZero\\Downloads\\";

static const std::vector<std::pair<cgSoftware::packageType, LPCSTR>> fileTypeConvert = {
	{cgSoftware::packageType::_appx,"appx"},
	{cgSoftware::packageType::_msi,"msi"},
	{cgSoftware::packageType::_exe,"exe"},
	{cgSoftware::packageType::_reserved,"\0"}
};

namespace cloudgameZero
{
	namespace Interface
	{
		namespace sigmaInterface
		{
			namespace Implement
			{
				class __cgTool : virtual public cgTool
				{
				public:
					__cgTool() : ref(NULL) {}
					virtual ~__cgTool() = default;
					virtual HRESULT QueryInterface(const IID& iid, void** ppv) override;
					virtual ULONG AddRef() override;
					virtual ULONG Release() override;
					virtual std::string download(IN const std::string& url, IN const std::string& path) override;
					virtual HRESULT createLnkA(IN const std::string& path, IN const std::string& save) override;
					virtual HRESULT createLnkW(IN std::wstring path, IN std::wstring save) override;
					virtual std::string deleteLnk(IN std::string path) override;
				private:
					ULONG ref;
				};

				class __cgTool_s : virtual public __cgTool
				{
				public:
					__cgTool_s() : ref(NULL) {}
					virtual ~__cgTool_s() = default;
					virtual HRESULT QueryInterface(const IID& iid, void** ppv) override;
					virtual ULONG AddRef() override;
					virtual ULONG Release() override;
					virtual std::string download(IN const std::string& url, IN const std::string& path) override;
					virtual HRESULT createLnkA(IN const std::string& path, IN const std::string& save) override;
					virtual HRESULT createLnkW(IN std::wstring path, IN std::wstring save) override;
					virtual std::string deleteLnk(IN std::string path) override;
				private:
					ULONG ref;
				};

				class __cgSoftware : virtual public cgSoftware,__cgTool_s
				{
				public:
					__cgSoftware() : ref(NULL) {}
					virtual HRESULT QueryInterface(const IID& iid, void** ppv) override;
					virtual ULONG AddRef() override;
					virtual ULONG Release() override;
					virtual HRESULT installPackage(packageType fileType) override;
					virtual HRESULT downloadPackage(const std::string packageUrl, packageType fileType) override;
					virtual HRESULT downloadSoftware(software software) override;
					virtual std::string download(IN const std::string& url, IN const std::string& path) override {
						return __cgTool_s::download(url, path);
					}
					virtual HRESULT createLnkA(IN const std::string& path, IN const std::string& save) override {
						return __cgTool_s::createLnkA(path, save);
					}
					virtual HRESULT createLnkW(IN std::wstring path, IN std::wstring save) override{
						return __cgTool_s::createLnkW(path, save);
					}
					virtual std::string deleteLnk(IN std::string path) override{
						return __cgTool_s::deleteLnk(path);
					}
				private:
					ULONG ref;
				};

				class __WindowsHelper : virtual public WindowsHelper
				{
				public:
					__WindowsHelper() : ref(NULL) {}
					virtual HRESULT QueryInterface(const IID& iid, void** ppv) override {
						return E_ABORT;
					}
					virtual ULONG AddRef() override {
						this->ref++;
						return this->ref;
					}
					virtual ULONG Release() override{
						if (this->ref--; this->ref == 0) {
							delete this;
						}
						else{
							return this->ref;
						}
						return NULL;
					}
					virtual void openSettings(LPCSTR location) override
					{
						if (location == NULL)
						{
							location = "controlcenter";
						}
						ShellExecuteA(NULL, "open", std::format("ms-settings:{}", location).c_str(), NULL, NULL, SW_SHOW);
					}
					virtual void useStore(StoreOperatorion operatorion, std::string args = std::string())
					{
						std::string url = "ms-windows-store://";
						switch (operatorion)
						{
						case reserved:{
							throw cloudgameZero::Interface::Exceptions::reservedArgs("保留值传参是不能使用的");
							break;
						}
						case Home:{
							url += "home";
							break;
							}
						case Query: {
							if (args.empty()) {
								args = "TranslucentTB";
							}
							url += std::format("search/?query={}",args);
							break;
						}
						case QueryTags: {
							if (args.empty()) {
								args = "Game";
							}
							url += std::format("assoc/?Tags={}", args);
							break;
						}
						case QueryPublisher:{
							if (args.empty()) {
								args = "Microsoft";
							}
						}
						case OpenWithProductId: {
							if (args.empty()) {
								args = "9MTCFHS560NG";
							}
							std::regex regex("[A-Z0-9]{12}");
							std::string str;
							if (std::regex_search(args,regex))
							{
								std::sregex_iterator iter(args.begin(), args.end(), regex);
								str = (*iter)[0];
							}
							url += std::format("pdp/?ProductId={}", str);
						}
						}
						ShellExecuteA(NULL, "open", url.c_str(), NULL, NULL, SW_SHOW);
					}


				private:
					ULONG ref;
				};

			}

			namespace guid
			{
				extern "C++" const IID IID_CLOUDGAME_FIX_ZERO_CGTOOL = { 0x44565a35, 0x575, 0x4613, { 0x81, 0x3b, 0xb7, 0xe0, 0x47, 0xb3, 0x53, 0x86 } };
				extern "C++" const IID IID_CLOUDGAME_FIX_ZERO_CGTOOLS = { 0xa10bcdaa, 0x75bc, 0x40b8, { 0xb2, 0xb0, 0x3c, 0x6d, 0xcd, 0x1c, 0x22, 0xc } };
				extern "C++" const IID IID_CLOUDGAME_FIX_ZERO_CGSOFTWARE = { 0x1117c83d, 0xf4f, 0x4926, { 0x86, 0xe1, 0xfe, 0xd7, 0x14, 0xd5, 0xc9, 0xbc } };
				extern "C++" const IID IID_CLOUDGAME_FIX_ZERO_ASCIISTYLE = { 0x2e31376, 0xa850, 0x4fbb, { 0x8c, 0xb8, 0xd4, 0xe6, 0xf6, 0x0, 0x14, 0xbf } };
				extern "C++" const IID IID_CLOUDGAME_FIX_ZERO_WINSET = { 0xb77329a, 0x251e, 0x4608, { 0x88, 0x21, 0x66, 0x89, 0xf0, 0x87, 0xd4, 0xeb } };
			}
		}

		extern "C++" IUnknown * cgToolCreateInstance()
		{
			IUnknown* ptr = dynamic_cast<cgTool*>(new __cgTool);
			ptr->AddRef();
			return ptr;
		}
	}
}

HRESULT __cgTool::QueryInterface(const IID& iid, void** ppv)
{
	if (iid == IID_CLOUDGAME_FIX_ZERO_CGTOOL) {
		*ppv = dynamic_cast<cgTool*>(new __cgTool);
	}
	else if (iid == IID_CLOUDGAME_FIX_ZERO_CGTOOLS) {
		*ppv = dynamic_cast<cgTool*>(new __cgTool_s);
	}
	else if (iid == IID_CLOUDGAME_FIX_ZERO_CGSOFTWARE) {
		*ppv = dynamic_cast<cgSoftware*>(new __cgSoftware);
	}
	else if (iid == IID_CLOUDGAME_FIX_ZERO_ASCIISTYLE){
		
	}
	else if (iid == IID_CLOUDGAME_FIX_ZERO_WINSET) {
		*ppv = dynamic_cast<WindowsHelper*>(new __WindowsHelper);
	}
	else {
		*ppv = NULL;
		return E_NOINTERFACE;
	}
	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return S_OK;
}

ULONG cloudgameZero::Interface::sigmaInterface::Implement::__cgTool::AddRef()
{
	this->ref++;
	return this->ref;
}

ULONG cloudgameZero::Interface::sigmaInterface::Implement::__cgTool::Release()
{
	if (this->ref--; this->ref == 0) {
		delete this;
	}
	else {
		return this->ref;
	}
	return NULL;
}

HRESULT cloudgameZero::Interface::sigmaInterface::Implement::__cgSoftware::QueryInterface(const IID& iid, void** ppv)
{
	return E_NOTIMPL;
}

ULONG __cgSoftware::AddRef()
{
	this->ref++;
	return this->ref;
}

ULONG __cgSoftware::Release()
{
	if (this->ref--; this->ref == 0) {
		delete this;
	}
	else {
		return this->ref;
	}
	return NULL;
}

std::string __cgTool_s::deleteLnk(IN std::string path)
{
	return std::string();
}

HRESULT cloudgameZero::Interface::sigmaInterface::Implement::__cgSoftware::installPackage(packageType fileType)
{
	return E_NOTIMPL;
}

HRESULT cloudgameZero::Interface::sigmaInterface::Implement::__cgSoftware::downloadPackage(const std::string packageUrl, packageType fileType)
{
	try {
		if (fileType == cgSoftware::packageType::_reserved){
			throw Exceptions::reservedArgs("保留值是不可使用的");
		}
		std::string ext;
		for (auto& i : fileTypeConvert)
		{
			if(fileType == i.first){
				ext = i.second;
				break;
			}
		}
		std::string path = __cgTool_s::download(packageUrl,std::format("{}tempPackage.{}", installPath,ext));
		if(path.empty()){
			DEBUG_MESSAGE("检测到参数是空值");
			return E_INVALIDARG;
		}
	}
	catch (Exceptions::reservedArgs except) {
		zeroLog::Instance()->write(logLevel::FATAL, except.what());
		return E_INVALIDARG;
	}
	
	return S_OK;
}

HRESULT cloudgameZero::Interface::sigmaInterface::Implement::__cgSoftware::downloadSoftware(software software)
{
	return E_NOTIMPL;
}

std::string cloudgameZero::Interface::sigmaInterface::Implement::__cgTool::download(IN const std::string& url, IN const std::string& path)
{
	return std::string();
}

HRESULT cloudgameZero::Interface::sigmaInterface::Implement::__cgTool::createLnkW(IN std::wstring path, IN std::wstring save)
{
	HRESULT hr = NULL;
	if (hr = CoInitialize(NULL); SUCCEEDED(hr))
	{
		IShellLinkW* IshellLinkptr = nullptr;
		hr = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLinkW, (void**)&IshellLinkptr);
		if (SUCCEEDED(hr))
		{
			IPersistFile* file = nullptr;
			IshellLinkptr->SetPath(path.c_str());
			hr = IshellLinkptr->QueryInterface(IID_IPersistFile, (void**)&file);
			if (SUCCEEDED(hr))
			{
				file->Save(save.c_str(), FALSE);
				file->Release();
				IshellLinkptr->Release();
				CoUninitialize();
				return S_OK;
			}
		}
	}
	CoUninitialize();
	return hr;
}

#pragma warning(push)
#pragma warning(disable : 4267)
HRESULT cloudgameZero::Interface::sigmaInterface::Implement::__cgTool::createLnkA(IN const std::string& path, IN const std::string& save)
{
	int size = ::MultiByteToWideChar(CP_ACP, NULL, save.c_str(), std::strlen(save.c_str()), NULL, 0);
	WCHAR* widechar = new WCHAR[size + 1];
	::MultiByteToWideChar(CP_ACP, NULL, save.c_str(), std::strlen(save.c_str()), widechar, size);
	widechar[size] = L'\0';
	HRESULT hr = CoInitialize(NULL);
	if(hr == S_FALSE){
		DEBUG_MESSAGE("已经初始化COM库");
	}
	if(SUCCEEDED(hr))
	{
		IShellLinkA* IshellLinkptr = nullptr;
		hr = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLinkA, (void**)&IshellLinkptr);
		if (SUCCEEDED(hr))
		{
			IPersistFile* file = nullptr;
			IshellLinkptr->SetPath(path.c_str());
			hr = IshellLinkptr->QueryInterface(IID_IPersistFile, (void**)&file);
			if (SUCCEEDED(hr))
			{
				file->Save(widechar, FALSE);
				file->Release();
				IshellLinkptr->Release();
				CoUninitialize();
				delete[] widechar;
				return S_OK;
			}
		}
	}
	CoUninitialize();
	delete[] widechar;
	return hr;
}

HRESULT __cgTool_s::createLnkW(IN std::wstring path, IN std::wstring save)
{
	DEBUG_MESSAGE("用户调用了安全版本函数");
	if (path.empty() || save.empty()){
		throw Exceptions::nullPointer("检测到参数有空");
	}
	int size = WideCharToMultiByte(CP_ACP, NULL, save.c_str(), lstrlenW(save.c_str()), NULL, 0, NULL, NULL);
	CHAR* mutiByte = new CHAR[size + 1];
	WideCharToMultiByte(CP_ACP, NULL, save.c_str(), lstrlenW(save.c_str()), mutiByte, size, NULL, NULL);
	mutiByte[size] = '\0';
	std::string str = mutiByte;
	delete[] mutiByte;
	if (std::regex_match(str, std::regex(cloudgameZero::Infomation::Secutriy::lnkPathRegex))) {
		return __cgTool::createLnkW(path, save);
	}
	else if (std::regex_match(str, std::regex(cloudgameZero::Infomation::Secutriy::lnkPathRegexNoEscape))) {
		return __cgTool::createLnkW(path, save);
	}
	else {
	}
	return E_FAIL;
}

#pragma warning(pop)

std::string cloudgameZero::Interface::sigmaInterface::Implement::__cgTool::deleteLnk(IN std::string path)
{
	return std::string();
}

HRESULT cloudgameZero::Interface::sigmaInterface::Implement::__cgTool_s::QueryInterface(const IID& iid, void** ppv)
{
	return E_NOTIMPL;
}

ULONG __cgTool_s::AddRef()
{
	this->ref++;
	return this->ref;
}

ULONG __cgTool_s::Release()
{
	if (this->ref--; this->ref == 0) {
		delete this;
	}
	else {
		return this->ref;
	}
	return NULL;
}

std::string __cgTool_s::download(IN const std::string& url,IN const std::string& path)
{
	DEBUG_MESSAGE("用户调用了安全版本函数");
	if (std::regex_match(url, std::regex(Infomation::Secutriy::urlLinkRegex))){
		return __cgTool::download(url,path);
	}
	else {
	}
	return std::string();
}

HRESULT __cgTool_s::createLnkA(IN const std::string& path, IN const std::string& save)
{
	DEBUG_MESSAGE("用户调用了安全版本函数");
	if (path.empty() || save.empty()) {
	}
	if (std::regex_match(save,std::regex(Infomation::Secutriy::lnkPathRegex))){
		return __cgTool::createLnkA(path, save);
	}
	else if (std::regex_match(save, std::regex(cloudgameZero::Infomation::Secutriy::lnkPathRegexNoEscape))){
		return __cgTool::createLnkA(path, save);
	}
	else {
	}
	return E_FAIL;
}

