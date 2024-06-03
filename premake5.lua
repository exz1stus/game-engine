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
IncludeDir["ImGui"] = "Engine/vendor/imgui"

group "Core"
	include "App"
	include "Engine"
	include "Sandbox"

group "Dependencies"
	include "Engine/vendor/glfw"
	include "Engine/vendor/imgui"
	include "Engine/vendor/glad"