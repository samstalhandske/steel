
workspace "Steel Engine"
	architecture "x64"
	
	configurations
	{
		"Debug",
		"Release",
		"Retail"
	}

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	-- Include directories relative to root folder (solution dir)
	IncludeDir = {}
	IncludeDir["GLFW"] = "Steel/ThirdParty/glfw/include"
	IncludeDir["glad"] = "Steel/ThirdParty/glad/include"
	IncludeDir["ImGui"] = "Steel/ThirdParty/imgui"
	IncludeDir["glm"] = "Steel/ThirdParty/glm"


	include "Steel/ThirdParty/glfw"
	include "Steel/ThirdParty/glad"
	include "Steel/ThirdParty/imgui"

project "Steel"
	location "Steel"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" ..outputdir.. "/%{prj.name}")
	objdir ("bin-int/" ..outputdir.. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "steel/Source/pch.cpp"

	files
	{
		"%{prj.name}/Source/**.h",
		"%{prj.name}/Source/**.hpp",
		"%{prj.name}/Source/**.cpp",
		"%{prj.name}/ThirdParty/glm/glm/**.hpp",
		"%{prj.name}/ThirdParty/glm/glm/**.inl"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"Steel/Source",
		"Steel/ThirdParty/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"STEEL_PLATFORM_WINDOWS",
			"STEEL_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}


	filter "configurations:Debug"
		defines "STEEL_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "STEEL_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Retail"
		defines "STEEL_RETAIL"
		runtime "Release"
		optimize "on"




project "Game"
	location "Game"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" ..outputdir.. "/%{prj.name}")
	objdir ("bin-int/" ..outputdir.. "/%{prj.name}")

	files
	{
		"%{prj.name}/Source/**.h",
		"%{prj.name}/Source/**.hpp",
		"%{prj.name}/Source/**.cpp"
	}

	includedirs
	{
		"Steel/ThirdParty/spdlog/include",
		"Steel/Source",
		"Steel/ThirdParty",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Steel"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"STEEL_PLATFORM_WINDOWS"
		}
		
	filter "configurations:Debug"
		defines "STEEL_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "STEEL_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Retail"
		defines "STEEL_RETAIL"
		runtime "Release"
		optimize "on"