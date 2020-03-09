workspace "Vantus_Engine"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Vantus_Engine"
	location "Vantus_Engine"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "vpch.h"
	pchsource "Vantus_Engine/src/vpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include/"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

	defines
	{
		"VANTUS_PLATFORM_WINDOWS",
		"VANTUS_BUILD_DLL"
	}
	
	postbuildcommands
	{
		("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
	}

	filter "configurations:Debug"
		defines "VANTUS_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "VANTUS_RELEASE"
		optimize "On"
		
	filter "configurations:Dist"
		defines "VANTUS_DIST"
		optimize "On"


	project "Sandbox"
		location "Sandbox"
		kind "ConsoleApp"
		language "C++"

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
			"Vantus_Engine/src"
		}

		links
		{
			"Vantus_Engine"
		}

		filter "system:windows"
			cppdialect "C++17"
			staticruntime "On"
			systemversion "latest"

		defines
		{
			"VANTUS_PLATFORM_WINDOWS"
		}

		filter "configurations:Debug"
			defines "VANTUS_DEBUG"
			symbols "On"

		filter "configurations:Release"
			defines "VANTUS_RELEASE"
			optimize "On"
		
		filter "configurations:Dist"
			defines "VANTUS_DIST"
			optimize "On"