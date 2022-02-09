workspace "Hickory"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Hickory/vendor/GLFW/include"
IncludeDir["Glad"] = "Hickory/vendor/Glad/include"
IncludeDir["ImGui"] = "Hickory/vendor/imgui"
IncludeDir["glm"] = "Hickory/vendor/glm"
IncludeDir["stb_image"] = "Hickory/vendor/stb_image"

include "Hickory/vendor/GLFW"
include "Hickory/vendor/Glad"
include "Hickory/vendor/imgui"



project "Hickory"
	location "Hickory"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "hkpch.h"
	pchsource "Hickory/src/hkpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"Dwmapi.lib",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"HK_PLATFORM_WINDOWS",
			"HK_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "HK_DEBUG"
		buildoptions "/MDd"
		symbols "on"

	filter "configurations:Release"
		defines "HK_RELEASE"
		buildoptions "/MD"
		optimize "on"

	filter "configurations:Dist"
		defines "HK_DIST"
		buildoptions "/MD"
		optimize "on"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Hickory/vendor/spdlog/include",
		"Hickory/src",
		"Hickory/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Hickory"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"HK_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "HK_DEBUG"
		buildoptions "/MDd"
		symbols "on"

	filter "configurations:Release"
		defines "HK_RELEASE"
		buildoptions "/MD"
		optimize "on"

	filter "configurations:Dist"
		defines "HK_DIST"
		buildoptions "/MD"
		optimize "on"