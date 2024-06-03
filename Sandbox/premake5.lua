project "Sandbox"
    kind "ConsoleApp"
	language "C++"

    files
	{
		"src/**.h",
		"src/**.cpp",
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