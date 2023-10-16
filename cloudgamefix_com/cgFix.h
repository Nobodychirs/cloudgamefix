#pragma once
#include "resource.h"
#include "cloudgamefixcom_i.h"
#include "pch.h"

using namespace ATL;

enum game_file_m { origin, epic, steam, uplay };
enum mode {
	cloudgame,
	cloudpc
};
class ATL_NO_VTABLE CcgFix :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CcgFix, &CLSID_cgFix>,
	public IDispatchImpl<IcgFix, &IID_IcgFix, &LIBID_cloudgamefixcomLib, 0>
{
public:
	CcgFix();

	DECLARE_REGISTRY_RESOURCEID(107)

	BEGIN_COM_MAP(CcgFix)
		COM_INTERFACE_ENTRY(IcgFix)
		COM_INTERFACE_ENTRY(IUnknown)
	END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:
	STDMETHODIMP fixSystem(int mode);
	STDMETHODIMP fixFile(int mode);
	STDMETHODIMP resetGroupPolicy();
	STDMETHODIMP repairGameFile();
private:
	std::map<int, std::string> path;
	std::map<int, std::string> path_Tran;
	std::map<int, std::string> path_After;
};

OBJECT_ENTRY_AUTO(__uuidof(cgFix), CcgFix)
