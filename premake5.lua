workspace "Mango"
	architecture "x86_64"
	startproject "MangoEditor"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (Solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Mango/vendor/GLFW/include"
IncludeDir["Glad"] = "Mango/vendor/Glad/include"
IncludeDir["ImGui"] = "Mango/vendor/imgui"
IncludeDir["glm"] = "Mango/vendor/glm"
IncludeDir["stb_image"] = "Mango/vendor/stb_image"

group "Dependencies"
	include "Mango/vendor/GLFW"
	include "Mango/vendor/Glad"
	include "Mango/vendor/imgui"

group ""

project "Mango"
	location "Mango"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("intermediate/" .. outputdir .. "/%{prj.name}")

	pchheader "MangoPCH.h"
	pchsource "Mango/src/MangoPCH.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
		}

	filter "configurations:Debug"
		defines "MANGO_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "MANGO_RELEASE"
		runtime "Release"
		optimize "on"
	
	filter "configurations:Dist"
		defines "MANGO_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

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
		"Mango/vendor",
		"Mango/src",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Mango"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "MANGO_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "MANGO_RELEASE"
		runtime "Release"
		optimize "on"
	
	filter "configurations:Dist"
		defines "MANGO_DIST"
		runtime "Release"
		optimize "on"

project "MangoEditor"
	location "MangoEditor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

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
		"Mango/vendor",
		"Mango/src",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Mango"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "MANGO_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "MANGO_RELEASE"
		runtime "Release"
		optimize "on"
	
	filter "configurations:Dist"
		defines "MANGO_DIST"
		runtime "Release"
		optimize "on"
