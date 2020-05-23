
workspace "Steel Engine"
	architecture "x64"
	
	configurations
	{
		"Debug",
		"Release",
		"Retail"
	}

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

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
		"Steel/Source"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"STEEL_PLATFORM_WINDOWS",
			"STEEL_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Game")
		}


	filter "configurations:Debug"
		defines "STEEL_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "STEEL_RELEASE"
		optimize "On"

	filter "configurations:Retail"
		defines "STEEL_RETAIL"
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
		symbols "On"

	filter "configurations:Release"
		defines "STEEL_RELEASE"
		optimize "On"

	filter "configurations:Retail"
		defines "STEEL_RETAIL"
		optimize "On"