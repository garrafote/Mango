#pragma once

#include <string>
#include <chrono>
#include <algorithm>
#include <fstream>

#include <thread>

namespace Mango {

	struct ProfileResult
	{
		std::string Name;
		long long Start, End;
		std::thread::id ThreadID;
	};

	struct InstrumentationSession
	{
		std::string Name;
	};

	class Instrumentor
	{
	private:
		InstrumentationSession* m_CurrentSession;
		std::ofstream m_OutputStream;
		int m_ProfileCount;
	public:
		Instrumentor()
			: m_CurrentSession(nullptr), m_ProfileCount(0)
		{
		}

		void BeginSession(const std::string& name, const std::string& filepath = "results.json")
		{
			m_OutputStream.open(filepath);
			WriteHeader();
			m_CurrentSession = new InstrumentationSession{ name };
		}

		void EndSession()
		{
			WriteFooter();
			m_OutputStream.close();
			delete m_CurrentSession;
			m_CurrentSession = nullptr;
			m_ProfileCount = 0;
		}

		void WriteProfile(const ProfileResult& result)
		{
			if (m_ProfileCount++ > 0)
				m_OutputStream << ",";

			std::string name = result.Name;
			std::replace(name.begin(), name.end(), '"', '\'');

			m_OutputStream << "{";
			m_OutputStream << "\"cat\":\"function\",";
			m_OutputStream << "\"dur\":" << (result.End - result.Start) << ',';
			m_OutputStream << "\"name\":\"" << name << "\",";
			m_OutputStream << "\"ph\":\"X\",";
			m_OutputStream << "\"pid\":0,";
			m_OutputStream << "\"tid\":" << std::hash<std::thread::id>{}(result.ThreadID) << ",";
			m_OutputStream << "\"ts\":" << result.Start;
			m_OutputStream << "}";

			m_OutputStream.flush();
		}

		void WriteHeader()
		{
			m_OutputStream << "{\"otherData\": {},\"traceEvents\":[";
			m_OutputStream.flush();
		}

		void WriteFooter()
		{
			m_OutputStream << "]}";
			m_OutputStream.flush();
		}

		static Instrumentor& Get()
		{
			static Instrumentor instance;
			return instance;
		}
	};

	class InstrumentationTimer
	{
	public:
		InstrumentationTimer(const char* name)
			: m_Name(name), m_Stopped(false)
		{
			m_StartTimepoint = std::chrono::high_resolution_clock::now();
		}

		~InstrumentationTimer()
		{
			if (!m_Stopped)
				Stop();
		}

		void Stop()
		{
			auto endTimepoint = std::chrono::high_resolution_clock::now();

			long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
			long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();
			Instrumentor::Get().WriteProfile({ m_Name, start, end, std::this_thread::get_id() });

			m_Stopped = true;
		}
	private:
		const char* m_Name;
		std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
		bool m_Stopped;
	};
}

#define MANGO_PROFILE 1
#if MANGO_PROFILE
	// Resolve which function signature macro will be used. Note that this only
	// is resolved when the (pre)compiler starts, so the syntax highlighting
	// could mark the wrong one in your editor!
	#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
		#define __MGO_FUNCSIG__ __PRETTY_FUNCTION__
	#elif defined(__DMC__) && (__DMC__ >= 0x810)
		#define __MGO_FUNCSIG__ __PRETTY_FUNCTION__
	#elif defined(__FUNCSIG__)
		#define __MGO_FUNCSIG__ __FUNCSIG__
	#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
		#define __MGO_FUNCSIG__ __FUNCTION__
	#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
		#define __MGO_FUNCSIG__ __FUNC__
	#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
		#define __MGO_FUNCSIG__ __func__
	#elif defined(__cplusplus) && (__cplusplus >= 201103)
		#define __MGO_FUNCSIG__ __func__
	#else
		#define __MGO_FUNCSIG__ "__MGO_FUNCSIG__ unknown!"
	#endif

	#define __MGO_TOKEN_PASTE__(x, y) x##y
	#define __MGO_TOKEN_EVALUATE__(x, y) __MGO_TOKEN_PASTE__(x, y)

	#define MGO_PROFILE_BEGIN_SESSION(name, filepath) ::Mango::Instrumentor::Get().BeginSession(name, filepath)
	#define MGO_PROFILE_END_SESSION() ::Mango::Instrumentor::Get().EndSession() 
	#define MGO_PROFILE_SCOPE(name) ::Mango::InstrumentationTimer __MGO_TOKEN_EVALUATE__(__timer,__COUNTER__)(name);
	#define MGO_PROFILE_FUNCTION() MGO_PROFILE_SCOPE(__MGO_FUNCSIG__)
#else
	#define MGO_PROFILE_BEGIN_SESSION(name, filepath)
	#define MGO_PROFILE_END_SESSION()
	#define MGO_PROFILE_SCOPE(name)
	#define MGO_PROFILE_FUNCTION()
#endif