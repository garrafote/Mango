#pragma once

#include <string>

namespace Mango {

	class FileDialogs
	{
	public:

		// Return empty string if cancelled
		static std::string OpenFile(const char* filter);
		
		// Return empty string if cancelled
		static std::string SaveFile(const char* filter);
	};

}
