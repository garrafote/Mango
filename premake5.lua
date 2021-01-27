include "./vendor/premake/premake_customization/solution_items.lua"

workspace "Mango"
	architecture "x86_64"
	startproject "MangoEditor"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	solution_items
	{
		".editorconfig"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (Solution directory)
IncludeDir = {}
IncludeDir["GLFW"]       = "%{wks.location}/Mango/vendor/GLFW/include"
IncludeDir["Glad"]       = "%{wks.location}/Mango/vendor/Glad/include"
IncludeDir["ImGui"]      = "%{wks.location}/Mango/vendor/imgui"
IncludeDir["yaml_cpp"]   = "%{wks.location}/Mango/vendor/yaml-cpp/include"
IncludeDir["glm"]        = "%{wks.location}/Mango/vendor/glm"
IncludeDir["stb_image"]  = "%{wks.location}/Mango/vendor/stb_image"
IncludeDir["entt"]       = "%{wks.location}/Mango/vendor/entt/include"
IncludeDir["ImGuizmo"]   = "%{wks.location}/Mango/vendor/ImGuizmo"

group "Dependencies"
	include "vendor/premake"
	include "Mango/vendor/GLFW"
	include "Mango/vendor/Glad"
	include "Mango/vendor/imgui"
	include "Mango/vendor/yaml-cpp"

group ""

include "Mango"
include "MangoEditor"
include "Sandbox"

