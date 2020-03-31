workspace "Vantus_Engine"
	architecture "x86_64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Vantus_Engine/vendor/GLFW/include"
IncludeDir["Glad"] = "Vantus_Engine/vendor/Glad/include"
IncludeDir["ImGui"] = "Vantus_Engine/vendor/imgui"
IncludeDir["glm"] = "Vantus_Engine/vendor/glm"

group "Dependencies"
	include "Vantus_Engine/vendor/GLFW/"
	include "Vantus_Engine/vendor/Glad/"
	include "Vantus_Engine/vendor/imgui/"

group ""

project "Vantus_Engine"
	location "Vantus_Engine"
	kind "StaticLib"
	language "C++"
	staticruntime "on"
	cppdialect "C++17"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "vpch.h"
	pchsource "Vantus_Engine/src/vpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/venfor/glm/glm/**.hpp",
		"%{prj.name}/venfor/glm/glm/**.inl"
	}
	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}
	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include/",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
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
		"VANTUS_PLATFORM_WINDOWS",
		"VANTUS_BUILD_DLL",
		"GLFW_INCLUDE_NONE"
	}

	filter "configurations:Debug"
		defines "VANTUS_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "VANTUS_RELEASE"
		runtime "Release"
		optimize "on"
		
	filter "configurations:Dist"
		defines "VANTUS_DIST"
		runtime "Release"
		optimize "on"

	project "Sandbox"
		location "Sandbox"
		kind "ConsoleApp"
		language "C++"
		cppdialect "C++17"
		staticruntime "on"

		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

		files
		{
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp"
		}

		includedirs
		{
			"Vantus_Engine/vendor/spdlog/include",
			"Vantus_Engine/src",
			"%{IncludeDir.glm}"
		}

		links
		{
			"Vantus_Engine"
		}

		filter "system:windows"
			systemversion "latest"

		defines
		{
			"VANTUS_PLATFORM_WINDOWS"
		}

		filter "configurations:Debug"
			defines "VANTUS_DEBUG"
			runtime "Debug"
			symbols "on"

		filter "configurations:Release"
			defines "VANTUS_RELEASE"
			runtime "Release"
			optimize "on"
		
		filter "configurations:Dist"
			defines "VANTUS_DIST"
			runtime "Release"
			optimize "on"