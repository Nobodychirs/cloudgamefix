#pragma once
#include "cloudgamefix.hpp"

namespace cloudgameZero
{
	namespace Foundation
	{
		extern "C++" const std::map<int, std::string> settingsMapping;
	}
	namespace Interface
	{
		/* cgTool封装的简易工具类 */
		interface cgTool : public IUnknown
		{
			virtual ~cgTool() = default;
			virtual std::string download(IN const std::string& url,IN const std::string& path) = 0;
			virtual HRESULT createLnkW(IN std::wstring path,IN std::wstring save) = 0;
			virtual HRESULT createLnkA(IN const std::string& path,IN const std::string& save) = 0;
			virtual std::string deleteLnk(IN std::string path) = 0;
		};

		/* 基于cgTool_s封装的helper，用于简易部署 */
		interface cgSoftware : public cgTool
		{
			enum class software
			{
				reserved,
				netease_cloud_music,
				m_7zip,
				firefox,
				QQ,
				OBS
			};
			enum class packageType
			{
				_reserved,
				_msi,
				_appx,
				_exe
			};
			virtual ~cgSoftware() = default;
			virtual HRESULT installPackage(packageType fileType) = 0;
			virtual HRESULT downloadPackage(const std::string packageUrl,packageType fileType) = 0;
			virtual HRESULT downloadSoftware(software software) = 0;
		};

		/* 用于方便应用程序打开WIndows设置,Microsoft Store的helper */
		interface WindowsHelper : public IUnknown
		{
			enum StoreOperatorion {
				reserved, //保留
				Home, //主页
				navigatetopage_Home, //跳转至主页
				navigatetopage_Gaming, //跳转至游戏页
				navigatetopage_Productivity, //跳转至应用
				Query, //执行查询
				QueryTags, //执行查询标签
				QueryPublisher, //执行查询开发者
				QueryFileExt, //执行查询文件拓展名
				QueryProtocol, //执行查询与协议关联的产品
				ReviewProductId, //通过产品ID到达评论区
				ReviewPFN, //通过PFN到达评论区
				RevieeAppid, //通过appid到达评论区
				OpenWithProductId, //通过产品ID打开页面
				OpenWithMini, //通过产品ID打开页面并使用Mini模式打开
				OpenWithPFN, //通过产品PFN打开页面
				OpenWithAppld, //通过appId打开页面
				DownloadAndUpdates, //打开下载和更新
				Settings //打开商店设置
			};
			virtual void openSettings(LPCSTR location) = 0;

			/**
			 * \brief 此函数将拼接一个字符串并转发打开Microsoft Store.
			 * 
			 * \brief 批注：
			 * \brief PFN为product family name，例如Microsoft.Office.OneNote_8wekyb3d8bbwe
			 * \brief appId是一个GUID,类似：f022389f-f3a6-417e-ad23-704fbdf57117
			 * \brief ProductId是从网址中获取的
			 * https://apps.microsoft.com/store/detail/watt-toolkit/9MTCFHS560NG?hl=zh-cn&gl=cn&cid=msft_web_appsforwindows_chart
			 * 
			 * \param operatorion 从StoreOperatorion中选取一个枚举值进行操作
			 * \param args 如果参数带有Query,Review,OpenWith字样，此处则为对应操作需要的参数
			 * \param 备注，args如果为空，将自动提供一个参数并填入
			 */
			virtual void useStore(StoreOperatorion operatorion,std::string args = std::string()) = 0;
		};

		/* 简易的ASCII字符画 */
		interface asciiStyle : public IUnknown
		{
			enum class style
			{
				reserved,
				welcome,
				cloudgame_fix,
				error,
				Done,
				bye
			};
			virtual void show(style style) = 0;
			virtual std::string get(style style) = 0;
		};

		namespace sigmaInterface
		{
			namespace guid
			{
				extern "C++" const IID IID_CLOUDGAME_FIX_ZERO_CGTOOL;
				extern "C++" const IID IID_CLOUDGAME_FIX_ZERO_CGTOOLS;
				extern "C++" const IID IID_CLOUDGAME_FIX_ZERO_CGSOFTWARE;
				extern "C++" const IID IID_CLOUDGAME_FIX_ZERO_ASCIISTYLE;
				extern "C++" const IID IID_CLOUDGAME_FIX_ZERO_WINSET;
			}
		}
	}
}
