project "App"
	kind "ConsoleApp"
	language "C++"

	targetdir("%{wks.location}/bin/" .. outputdir .."/%{prj.name}")
	objdir("%{wks.location}/bin-int/" .. outputdir .."/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp",
	}

	includedirs
	{
		"%{wks.location}/Engine/vendor/spdlog/include",
		"%{wks.location}/Engine/vendor/glm",
		"%{wks.location}/Engine/src/vendor/",
		"%{wks.location}/Engine/src",
		"%{wks.location}/Engine/src/core",
		"%{wks.location}/Engine/vendor/glad",
		"%{wks.location}/Engine/vendor/entt/single_include",
		"%{IncludeDir.imgui}",
	}

	libdirs
	{
		"%{wks.location}/Engine/bin/outputdir/",
		"%{IncludeDir.imgui}/bin/".. outputdir .."ImGui",
	}

	links
	{
		"Engine",
		"GLFW",
		"ImGui"
	}

	filter "system:windows"
		cppdialect "C++20"
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