workspace "Mango"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (Solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Mango/vendor/GLFW/include"

include "Mango/vendor/GLFW"

project "Mango"
	location "Mango"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("intermediate/" .. outputdir .. "/%{prj.name}")

	pchheader "MangoPCH.h"
	pchsource "Mango/src/MangoPCH.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}"
	}

	links
	{
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"MANGO_PLATFORM_WINDOWS",
			"MANGO_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "MANGO_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "MANGO_RELEASE"
		buildoptions "/MD"
		optimize "On"
	
	filter "configurations:Dist"
		defines "MANGO_DIST"
		buildoptions "/MD"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("intermediate/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Mango/vendor/spdlog/include",
		"Mango/src"
	}

	links
	{
		"Mango"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"MANGO_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "MANGO_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "MANGO_RELEASE"
		buildoptions "/MD"
		optimize "On"
	
	filter "configurations:Dist"
		defines "MANGO_DIST"
		buildoptions "/MD"
		optimize "On"

