solution ("expression_" .. _ACTION)
	configurations { "Debug", "Release" }
	
	configuration "Debug"
		defines { "DEBUG" }
		flags { "Symbols" }

	configuration "Release"
		defines { "NDEBUG" }
		flags { "Optimize" }

	-- Vector dot product project
	project ("dot_product_" .. _ACTION)
		language "C++"
		kind "ConsoleApp"
		files 
		{
			-- Header Files
			"*.hpp",

			-- Source Files
			"main.cpp",
			"timer.cpp",
			"test_dot_product.cpp"
		}

	-- Vector length project
	project ("vector_length_" .. _ACTION)
		language "C++"
		kind "ConsoleApp"
		files 
		{
			-- Header Files
			"*.hpp",

			-- Source Files
			"main.cpp",
			"timer.cpp",
			"test_vector_length.cpp"
		}
