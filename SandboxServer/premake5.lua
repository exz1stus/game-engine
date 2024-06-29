project "SandboxServer"
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
		"%{wks.location}/Engine/src",
        "%{wks.location}/Engine/vendor/spdlog/include",
        "%{wks.location}/Engine/vendor/glm",
		"%{wks.location}/Engine/vendor/entt/single_include",
		"%{wks.location}/Engine/vendor/enet/include",
	}

    filter "system:windows"
    cppdialect "C++20"
    systemversion "latest"
    defines
    {
        "PLATFORM_WINDOWS;"
    }

    links
    {
    	"Engine",
    }

    filter "configurations:Debug"
        defines "ENG_DEBUG"
        symbols "On"
    filter "configurations:Release"
        defines "ENG_RELEASE"
        optimize "On"