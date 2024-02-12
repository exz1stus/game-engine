workspace "Engine"
	architecture "x64"
	startproject "App"

	configurations
	{
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Engine/vendor/glfw/include"
IncludeDir["glad"] = "Engine/vendor/glad"

group "Core"
	include "App"
	include "Engine"

group "Dependencies"
	include "Engine/vendor/glfw"
	include "Engine/vendor/glad"