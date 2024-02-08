workspace "Engine"
	architecture "x64"

	startproject "App"

	configurations
	{
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

--Include dirs relative to root folder (solution direction)
IncludeDir = {}
IncludeDir["GLFW"] = "Engine/vendor/glfw/include"
IncludeDir["glad"] = "Engine/vendor/glad"



--GLFW prj
include "Engine/vendor/glfw"

project "Engine"
	location "Engine"
	kind "StaticLib"
	--kind "SharedLib"
	language "C++"

	targetdir("bin/" .. outputdir .."/%{prj.name}")
	objdir("bin-int/" .. outputdir .."/%{prj.name}")

	--pchheader "engpch.h"
	--pchsource "Engine/src/engpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"%{prj.name}/dependecies/include",
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/vendor/benchmark/include",
		"%{prj.name}/vendor/glm",
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glad}"
	}
	libdirs{
		"%{prj.name}/dependencies/lib"
	}

	links
	{
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"PLATFORM_WINDOWS;",
		}

	filter "configurations:Debug"
		defines "ENG_DEBUG"
		symbols "On"
	filter "configurations:Release"
		defines "ENG_RELEASE"
		optimize "On"



project "App"
	location "App"
	kind "ConsoleApp"
	language "C++"

	targetdir("bin/" .. outputdir .."/%{prj.name}")
	objdir("bin-int/" .. outputdir .."/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"Engine/vendor/spdlog/include",
		"Engine/src/vendor/",
		"Engine/src",
		"%{IncludeDir.glad}"
	}

	libdirs
	{
		"%{prj.name}/dependencies/lib",
		"Engine/bin/outputdir/"
	}

	ignoredefaultlibraries
	{
		"LIBCMTD"
	}

	links
	{
		"Engine"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"PLATFORM_WINDOWS;"
		}

	filter "configurations:Debug"
		defines "ENG_DEBUG"
		symbols "On"
	filter "configurations:Release"
		defines "ENG_RELEASE"
		optimize "On"

