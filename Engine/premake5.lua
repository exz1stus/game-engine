project "Engine"
	kind "StaticLib"
	--kind "SharedLib"
	language "C++"

	targetdir("%{wks.location}/bin/" .. outputdir .."/%{prj.name}")
	objdir("%{wks.location}/bin-int/" .. outputdir .."/%{prj.name}")

	pchheader "engpch.h"
	pchsource "src/engpch.cpp"

	files
	{
		"src/**.h",
		"src/**.cpp",
	}

	includedirs
	{
		"dependencies/include",
		"vendor/spdlog/include",
		"vendor/benchmark/include",
		"vendor/glad/include",
		"vendor/glm",
		"src",
		"%{IncludeDir.GLFW}",
	}
	libdirs{
		"dependencies/lib"
	}

	links
	{
		"GLFW",
		"opengl32.lib",
		"vendor/glad/bin/" .. outputdir .. "/glad/glad.lib"
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