project "PathTracer"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"

	targetdir "%{wks.location}/BUILD/bin/%{cfg.name}/%{prj.name}"
	objdir "%{wks.location}/BUILD/bin-int/%{cfg.name}/%{prj.name}"

	files {
		"src/**.cpp",
		"src/**.h"
	}

	includedirs {
		"src",
		"vendor/include"
	}
	
	filter "configurations:Debug"	
		defines {
			"DEBUG"
		}
		symbols "on"

	filter "configurations:Release"	
		defines {
			"NDEBUG"
		}
		optimize "full"
