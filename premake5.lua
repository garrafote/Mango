workspace "Mango"
	architecture "x64"
	startproject "Sandbox"

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
IncludeDir["Glad"] = "Mango/vendor/Glad/include"
IncludeDir["imgui"] = "Mango/vendor/imgui"

group "Dependencies"
	include "Mango/vendor/GLFW"
	include "Mango/vendor/Glad"
	include "Mango/vendor/imgui"

group ""

project "Mango"
	location "Mango"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

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
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.imgui}"
	}

	links
	{
		"GLFW",
		"Glad",
		"imgui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"MANGO_PLATFORM_WINDOWS",
			"MANGO_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "MANGO_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "MANGO_RELEASE"
		runtime "Release"
		optimize "On"
	
	filter "configurations:Dist"
		defines "MANGO_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

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
		systemversion "latest"

		defines
		{
			"MANGO_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "MANGO_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "MANGO_RELEASE"
		runtime "Release"
		optimize "On"
	
	filter "configurations:Dist"
		defines "MANGO_DIST"
		runtime "Release"
		optimize "On"

