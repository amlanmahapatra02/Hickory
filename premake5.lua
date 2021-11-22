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

include "Hickory/vendor/GLFW"
include "Hickory/vendor/Glad"
include "Hickory/vendor/imgui"


project "Hickory"
	location "Hickory"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "hkpch.h"
	pchsource "Hickory/src/hkpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
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
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"HK_PLATFORM_WINDOWS",
			"HK_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "HK_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "HK_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "HK_DIST"
		runtime "Release"
		optimize "On"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

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
		"%{IncludeDir.glm}"
	}

	links
	{
		"Hickory"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"HK_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "HK_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "HK_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "HK_DIST"
		runtime "Release"
		optimize "On"