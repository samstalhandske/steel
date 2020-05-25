
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

	include "Steel/ThirdParty/glfw"
	include "Steel/ThirdParty/glad"
	include "Steel/ThirdParty/imgui"

project "Steel"
	location "Steel"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" ..outputdir.. "/%{prj.name}")
	objdir ("bin int/" ..outputdir.. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "steel/Source/pch.cpp"

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
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.ImGui}"

	}

	links
	{
		"GLFW",
		"glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"STEEL_PLATFORM_WINDOWS",
			"STEEL_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Game")
		}


	filter "configurations:Debug"
		defines "STEEL_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "STEEL_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Retail"
		defines "STEEL_RETAIL"
		buildoptions "/MD"
		optimize "On"




project "Game"
	location "Game"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" ..outputdir.. "/%{prj.name}")
	objdir ("bin int/" ..outputdir.. "/%{prj.name}")

	files
	{
		"%{prj.name}/Source/**.h",
		"%{prj.name}/Source/**.hpp",
		"%{prj.name}/Source/**.cpp"
	}

	includedirs
	{
		"Steel/ThirdParty/spdlog/include",
		"Steel/Source"
	}

	links
	{
		"Steel"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"STEEL_PLATFORM_WINDOWS"
		}
		
	filter "configurations:Debug"
		defines "STEEL_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "STEEL_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Retail"
		defines "STEEL_RETAIL"
		buildoptions "/MD"
		optimize "On"