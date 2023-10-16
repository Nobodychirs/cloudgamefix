

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0628 */
/* at Tue Jan 19 11:14:07 2038
 */
/* Compiler settings for cloudgamefixcom.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0628 
    protocol : all , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __cloudgamefixcom_i_h__
#define __cloudgamefixcom_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef DECLSPEC_XFGVIRT
#if defined(_CONTROL_FLOW_GUARD_XFG)
#define DECLSPEC_XFGVIRT(base, func) __declspec(xfg_virtual(base, func))
#else
#define DECLSPEC_XFGVIRT(base, func)
#endif
#endif

/* Forward Declarations */ 

#ifndef __IcgFix_FWD_DEFINED__
#define __IcgFix_FWD_DEFINED__
typedef interface IcgFix IcgFix;

#endif 	/* __IcgFix_FWD_DEFINED__ */


#ifndef __IcgTool_FWD_DEFINED__
#define __IcgTool_FWD_DEFINED__
typedef interface IcgTool IcgTool;

#endif 	/* __IcgTool_FWD_DEFINED__ */


#ifndef __IcgSystem_FWD_DEFINED__
#define __IcgSystem_FWD_DEFINED__
typedef interface IcgSystem IcgSystem;

#endif 	/* __IcgSystem_FWD_DEFINED__ */


#ifndef __cgFix_FWD_DEFINED__
#define __cgFix_FWD_DEFINED__

#ifdef __cplusplus
typedef class cgFix cgFix;
#else
typedef struct cgFix cgFix;
#endif /* __cplusplus */

#endif 	/* __cgFix_FWD_DEFINED__ */


#ifndef __cgTool_FWD_DEFINED__
#define __cgTool_FWD_DEFINED__

#ifdef __cplusplus
typedef class cgTool cgTool;
#else
typedef struct cgTool cgTool;
#endif /* __cplusplus */

#endif 	/* __cgTool_FWD_DEFINED__ */


#ifndef __cgSystem_FWD_DEFINED__
#define __cgSystem_FWD_DEFINED__

#ifdef __cplusplus
typedef class cgSystem cgSystem;
#else
typedef struct cgSystem cgSystem;
#endif /* __cplusplus */

#endif 	/* __cgSystem_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "shobjidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IcgFix_INTERFACE_DEFINED__
#define __IcgFix_INTERFACE_DEFINED__

/* interface IcgFix */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IcgFix;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("fdf81ac2-b82f-4a86-b301-35bd3369a4bf")
    IcgFix : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE fixSystem( 
            /* [in] */ int mode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE fixFile( 
            /* [in] */ int mode) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IcgFixVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcgFix * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcgFix * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcgFix * This);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfoCount)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcgFix * This,
            /* [out] */ UINT *pctinfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfo)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcgFix * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetIDsOfNames)
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcgFix * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        DECLSPEC_XFGVIRT(IDispatch, Invoke)
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcgFix * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        DECLSPEC_XFGVIRT(IcgFix, fixSystem)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *fixSystem )( 
            IcgFix * This,
            /* [in] */ int mode);
        
        DECLSPEC_XFGVIRT(IcgFix, fixFile)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *fixFile )( 
            IcgFix * This,
            /* [in] */ int mode);
        
        END_INTERFACE
    } IcgFixVtbl;

    interface IcgFix
    {
        CONST_VTBL struct IcgFixVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcgFix_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IcgFix_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IcgFix_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IcgFix_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IcgFix_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IcgFix_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IcgFix_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IcgFix_fixSystem(This,mode)	\
    ( (This)->lpVtbl -> fixSystem(This,mode) ) 

#define IcgFix_fixFile(This,mode)	\
    ( (This)->lpVtbl -> fixFile(This,mode) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IcgFix_INTERFACE_DEFINED__ */


#ifndef __IcgTool_INTERFACE_DEFINED__
#define __IcgTool_INTERFACE_DEFINED__

/* interface IcgTool */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IcgTool;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3563176a-4ff6-4571-a486-1acfad2069ea")
    IcgTool : public IDispatch
    {
    public:
    };
    
    
#else 	/* C style interface */

    typedef struct IcgToolVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcgTool * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcgTool * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcgTool * This);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfoCount)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcgTool * This,
            /* [out] */ UINT *pctinfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfo)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcgTool * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetIDsOfNames)
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcgTool * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        DECLSPEC_XFGVIRT(IDispatch, Invoke)
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcgTool * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } IcgToolVtbl;

    interface IcgTool
    {
        CONST_VTBL struct IcgToolVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcgTool_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IcgTool_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IcgTool_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IcgTool_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IcgTool_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IcgTool_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IcgTool_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IcgTool_INTERFACE_DEFINED__ */


#ifndef __IcgSystem_INTERFACE_DEFINED__
#define __IcgSystem_INTERFACE_DEFINED__

/* interface IcgSystem */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IcgSystem;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3daa0403-1d46-44d2-95b4-46881bc7c4aa")
    IcgSystem : public IDispatch
    {
    public:
    };
    
    
#else 	/* C style interface */

    typedef struct IcgSystemVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IcgSystem * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IcgSystem * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IcgSystem * This);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfoCount)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IcgSystem * This,
            /* [out] */ UINT *pctinfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfo)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IcgSystem * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetIDsOfNames)
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IcgSystem * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        DECLSPEC_XFGVIRT(IDispatch, Invoke)
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IcgSystem * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } IcgSystemVtbl;

    interface IcgSystem
    {
        CONST_VTBL struct IcgSystemVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IcgSystem_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IcgSystem_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IcgSystem_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IcgSystem_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IcgSystem_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IcgSystem_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IcgSystem_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IcgSystem_INTERFACE_DEFINED__ */



#ifndef __cloudgamefixcomLib_LIBRARY_DEFINED__
#define __cloudgamefixcomLib_LIBRARY_DEFINED__

/* library cloudgamefixcomLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_cloudgamefixcomLib;

EXTERN_C const CLSID CLSID_cgFix;

#ifdef __cplusplus

class DECLSPEC_UUID("9727503a-899b-452a-b32a-6592a5eafb30")
cgFix;
#endif

EXTERN_C const CLSID CLSID_cgTool;

#ifdef __cplusplus

class DECLSPEC_UUID("81e7ab00-240d-4222-afb1-d346e59edd5f")
cgTool;
#endif

EXTERN_C const CLSID CLSID_cgSystem;

#ifdef __cplusplus

class DECLSPEC_UUID("860971a4-8453-4132-bda6-01813abf7381")
cgSystem;
#endif
#endif /* __cloudgamefixcomLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


