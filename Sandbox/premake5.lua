project "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/intermediate/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs
	{
		"%{wks.location}/Mango/vendor/spdlog/include",
		"%{wks.location}/Mango/vendor",
		"%{wks.location}/Mango/src",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}"
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

