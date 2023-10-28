#include "cloudgamefix.hpp"
#include <winsvc.h>
#include<Userenv.h>
#include <CommCtrl.h>
#pragma comment(lib,"Userenv.lib")
#pragma comment(lib,"comctl32.lib")

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



template<typename type>
concept string = std::is_same_v<type,char> || std::is_same_v<type,wchar_t>;

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
	using message = msg<type>;

	/**
	*  \brief 此部分写于2023/8/12
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
		bool init,
		std::string_view file = "logConfig.json",
		delegate<void, rapidjson::Document&> CallBack = nullptr,
		std::string_view mark = "main",
		std::string_view server = "ZERO"
	) : times(NULL), mark(mark), server(server),fs(Infomation::logFileStream),time(NULL)
	{
		if (!Infomation::logSession)
		{
			startLoggerSession();
		}
		conf = std::make_unique<logConfig>();
		if (!std::filesystem::exists(file))
		{
			DEBUG_MESSAGE("未找到配置文件\n准备生成一个默认配置");
			conf->InitConfig(file.data());
			if (CallBack)
			{
				CallBack(conf->getDocment());
			}
		}
		conf->InitConfig(file.data());
		if (CallBack)
		{
			CallBack(conf->getDocment());
		}
		conf->saveSettings(file);
		this->minLevel = conf->getMin();
		if (init)
		{
			this->init();
		}
	}

	/**
	 * 每一个日志类对象是独一无二的实例，因此空参构造和拷贝构造以及赋值运算符将不会提供给用户.
	 */
	zeroLogT() = delete;
	zeroLogT& operator=(zeroLog& other) = delete;
	zeroLogT(zeroLog& other) = delete;

	~zeroLogT()
	{
		this->close();
	}

	void init()
	{
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
				if (fs == nullptr)
				{
					fs = new std::fstream;
				}
				if (fs->is_open())
				{
					break;
				}
				std::string dict;
				if (this->file.empty())
				{
					conf->getLogDictionary(dict);
					if (!std::filesystem::exists(dict))
					{
						std::filesystem::create_directories(dict);
					}
					std::string filename = conf->parseFileName();
					dict += filename;
				}
				else
				{
					dict = this->file;
				}
				if (Dom["logToFile"]["append"].GetBool())
				{
					fs->open(dict, std::ios::app);
				}
				else
				{
					fs->open(dict, std::ios::out);
				}
				if (!fs->is_open())
				{
					throw std::runtime_error("无法打开文件，出现了异常");
				}
				this->file = dict;
				this->EnableFileOut = true;
			} while (false);
		}
		if (Dom["outToTerminal"]["Enable"].GetBool())
		{
			DEBUG_MESSAGE("准备获取ostream对象");
			switch (conf->getLogObjectType())
			{
			case logConfig::_ostream::clog:
			{
				this->object = &std::clog;
				break;
			}
			case logConfig::_ostream::cout:
			{
				this->object = &std::cout;
				break;
			}
			case logConfig::_ostream::cerr:
			{
				this->object = &std::cerr;
				break;
			}
			default:
			{
				LibError(std::runtime_error("无法获取对象"));
			}
			}
			DEBUG_MESSAGE("准备获取wostream对象");
			switch (conf->getWideOstreamType())
			{
			case logConfig::_wostream::wclog:
			{
				this->wobject = &std::wclog;
				break;
			}
			case logConfig::_wostream::wcout:
			{
				this->wobject = &std::wcout;
				break;
			}
			case logConfig::_wostream::wcerr:
			{
				this->wobject = &std::wcerr;
				break;
			}
			default:
			{
				LibError(std::runtime_error("无法获取对象"));
			}
			}
			wobject->imbue(Infomation::chs);
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
		{
			//We check if the object is initialized, and if not, we initialize it for it
			this->init();
		}
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
		{
			//We check if the object is initialized, and if not, we initialize it for it
			this->init();
		}
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
		{
			//We check if the object is initialized, and if not, we initialize it for it
			this->init();
		}
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
		{
			//We check if the object is initialized, and if not, we initialize it for it
			this->init();
		}
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
		{
			//We check if the object is initialized, and if not, we initialize it for it
			this->init();
		}
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
	void info(const std::basic_string_view<type> fmt,Args... args) throw()
	{
		using namespace Infomation;
		static level lev = Info;
		if (!this->hasInit())
		{
			//We check if the object is initialized, and if not, we initialize it for it
			this->init();
		}
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
		{
			//We check if the object is initialized, and if not, we initialize it for it
			this->init();
		}
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
		{
			//We check if the object is initialized, and if not, we initialize it for it
			this->init();
		}
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
		{
			//We check if the object is initialized, and if not, we initialize it for it
			this->init();
		}
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
		{
			//We check if the object is initialized, and if not, we initialize it for it
			this->init();
		}
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
		{
			//We check if the object is initialized, and if not, we initialize it for it
			this->init();
		}
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
		{
			//We check if the object is initialized, and if not, we initialize it for it
			this->init();
		}
		std::unique_lock<std::mutex> lock(this->mutex);
		//Here we make a format strings then generate a log and forward it to the write method to print out the log messages
		auto alraedy = Infomation::makeFormat(fmt, args...);
		auto logs = this->makeLogs(lev, alraedy);
		this->write(lev, logs);
	}

	static friend inline zeroLogT<type>& operator<<(zeroLogT<type>& object,const message&& msg) throw()
	{
		using namespace Infomation;
		//Here we enable thread locks to prevent resource contention issues
		std::unique_lock<std::mutex> lock(this->mutex);
		if (!object.hasInit())
		{
			//We check if the object is initialized, and if not, we initialize it for it
			object.init();
		}
		/* Create a temporary variable to accept log information returned from makeLogs in the zeroLogT<type> instance object */
		std::basic_string<type> logs;
		if (msg.level == Reserved)
		{
			//For Reserved, we treat it as Info, because Reserved has no value and is used only to filter log messages
			logs = this->makeLogs(Info, msg._msg.data());
		}
		else
		{
			logs = this->makeLogs(msg.level, msg._msg.data());
		}
		object.write(msg.level == Reserved ? Info : msg.level,logs); 
		//Here we call the write method in the instance object of zeroLogT<type>. At the log level, we use a ternary expression to process Reserved information and then write out the log information
		return object; //Finally, we return a reference to the object
	}

	static friend inline zeroLogT<type>& operator>>(zeroLogT<type>& object,msg<type>& msg) throw()
	{
		using namespace Infomation;
		//Here we enable thread locks to prevent resource contention issues
		std::unique_lock<std::mutex> lock(this->mutex);
		if (!object.hasInit())
		{
			//We check if the object is initialized, and if not, we initialize it for it
			object.init();
		}
		if (msg.level == Reserved)
		{
			//For Reserved, we treat it as Info, because Reserved has no value and is used only to filter log messages
			msg.buffer = object.makeLogs(Info, msg._msg.data());
		}
		else
		{
			msg.buffer = object.makeLogs(msg.level, msg._msg.data()); 
			//When we get the log information, we directly assign it to the msg buffer
		}
		return object; //Finally, we return a reference to the object
	}

	void stackTrace()
	{
		using namespace Infomation;
		using namespace Foundation::Tool;
		//Here we enable thread locks to prevent resource contention issues
		std::unique_lock<std::mutex> lock(this->mutex);
		if (!this->hasInit())
		{
			//We check if the object is initialized, and if not, we initialize it for it
			this->init();
		}
		std::string logs = this->makeLogs(Warn,std::format("\n Here Is The StackTrace's Content: \n{}",boost::stacktrace::to_string(boost::stacktrace::stacktrace())));
		this->write(Warn, logs);
	}

	inline void close()
	{
		if (!this->hasInit())
		{
			return;
		}
		wobject->imbue(Infomation::_Clocale);
		this->wobject = nullptr;
		this->has_init = false;
		fs = nullptr;
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
		{
			return;// If not, do not log the message and exit the function.
		}
		// If terminal output is enabled, process the log message for terminal output.
		if (this->EnableTerminalOut)
		{
			// If rendering is required, call the 'renderTerminal' function.
			if (this->render)
			{
				renderTerminal(report);
			}
			// Write the log message to the terminal stream, depending on the character type.
			if constexpr (std::is_same_v<type, char>)
			{
				/* Due to the lack of support for inserting std::string in wostream, the c_str method is called here for output. */
				(*object) << logs;
			}
			else
			{
				/* wchar t doesn't need to be processed, so just output it */
				(*wobject) << logs;
			}
			// Control message separation in terminal output based on 'cleanBuffer' and 'times'.
			if (cleanBuffer && time < times)
			{
				wobject->put(L'\n');
				// If we don't need the actual number of cleanups to be less than the set number of cleanups, we just wrap the lines
				time++;
			}
			else if (cleanBuffer && time >= times)
			{
				// Simply clean up with std::endl, then reset it
				(*wobject) << std::endl;
				time = 0;
			}
			else
			{
				wobject->put(L'\n');
			}
		}
		SetConsoleTextAttribute(CONSOLE_OUTPUT_HANDLE, (WORD)Foundation::Tool::CONSOLE::CONSOLE_COLOR_WHITE);
		if (this->EnableFileOut)
		{
			if constexpr (std::is_same_v<type, char>)
			{
				(*fs) << logs << "\n";
			}
			else if constexpr (std::is_same_v<type, wchar_t>)
			{
				(*fs) << WideToMuti(logs) << "\n";
			}
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
	std::unique_ptr<logConfig> conf;
	std::ostream* object = nullptr;
	std::wostream* wobject = nullptr;
	std::fstream* fs;
	std::string_view file;
	std::string_view mark;
	std::string_view server;
};

using zeroLogA = zeroLogT<char>;
using zeroLogW = zeroLogT<wchar_t>;
using msgA = zeroLogA::message;
using msgW = zeroLogW::message;

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

namespace window
{
	class Window
	{
	public:
		~Window()
		{
			thread.request_stop();
		}
		
		void create()
		{
			CLASS.cbSize = sizeof(WNDCLASSEXW);
			CLASS.hInstance = Instance;
			CLASS.lpfnWndProc = callback;
			if (RegisterClassExW(&CLASS) == NULL)
			{
				std::cout << "无法注册" << "\n";
				return;
			}
			hwnd = CreateWindowExW(
				NULL,
				className.c_str(),
				title.empty() ? L"Window" : title.c_str(),
				WS_OVERLAPPEDWINDOW,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				NULL,
				NULL,
				Instance,
				NULL
			);
			if (!hwnd)
			{
				std::cout << "无法创建窗口" << "\n";
				return;
			}
		}
		
		void start()
		{
			if (!hwnd)
			{
				return;
			}
			MSG msg{};
			ShowWindow(this->hwnd, SW_SHOW);
			while (GetMessageW(&msg, 0, 0, 0))
			{
				DispatchMessageW(&msg);
			}
			return;
		}
		
		inline void startWithAsyhc()
		{
			thread = std::jthread([this]() 
				{
					create();
					start();
				});
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
		
		inline void setTitle(std::wstring title)
		{
			this->title = std::move(title);
		}
		
		inline void setClassName(std::wstring className)
		{
			this->className = className;
			CLASS.lpszClassName = className.c_str();
		}

		inline void setCallBack(WNDPROC callback)
		{
			this->callback = callback;
		}
		
		inline void setInstance(HINSTANCE Instance)
		{
			this->Instance = Instance;
		}
	private:
		WNDPROC callback = nullptr;
		WNDCLASSEXW CLASS = {};
		std::wstring title;
		std::wstring className;
		HINSTANCE Instance{};
		HWND hwnd{};
		std::jthread thread;
	};
}

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

		// fall thru
		__fallthrough;
	default:
		return DefWindowProc(window, msg, wp, lp);
	}
}

int main(int argc, CHAR** argv)
{
	zeroLogW wlog(true);
	zeroLogA log(true);
	std::cout << sizeof(zeroLog) << "\n";
	std::cout << sizeof(zeroLogA) << "\n";
	HANDLE INSTANCE_EVENT = CreateEventA(NULL, FALSE, FALSE, "cloudgameFixZero init process");
	/*std::jthread thread = std::jthread([]()
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(2000));
			exit(0);
		}
	);*/
	ComPtr<cgFix> pt = nullptr;
	HRESULT hr = createInstance(&pt);
	if (SUCCEEDED(hr))
	{
		std::cout << "成功创建实例" << "\n";
	}
	if (INSTANCE_EVENT)
	{
		SetEvent(INSTANCE_EVENT);
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
		}
	}
	else
	{
		ToastPlatformAPI::ToastTemplate Toast(ToastPlatformEnums::ToastTemplateType::Text02);
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
		return 0xA;
	}
	PRESSANYBOTTON();
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
	window::Window window;
	window.setCallBack(WindowProcedure);
	window.setInstance(GetModuleHandleA(NULL));
	window.setClassName(L"My_Simple_ClassWindow");
	//window.startWithAsyhc();
	//window.create();
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
	coro::coroutine_void<int> fun = []() -> coro::coroutine_void<int>
		{
			std::cout << "协程开始" << "\n";
			co_yield 1;
			co_return;
		}
	();
	while (fun.move())
	{
		std::cout << fun.getYieldValue() << "\n";
	}
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