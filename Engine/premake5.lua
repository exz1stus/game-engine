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
		"vendor/spdlog/include",
		"vendor/benchmark/include",
		"vendor/glfw/include",
		"vendor/glad/include",
		"vendor/glm",
		"vendor/imgui",
		"vendor/stb_image",
		"src",
	}
	libdirs{
		"vendor"
	}

	links
	{
		"GLFW",
		"opengl32.lib",
		"glad",
		"GLFW",
		"ImGui",
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