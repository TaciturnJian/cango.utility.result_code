cmake_minimum_required(VERSION 3.21)

project(cango.utility.result_code)

add_library(cango_utility_result_code INTERFACE)
add_library(cango::utility::result_code ALIAS cango_utility_result_code)
target_include_directories(cango_utility_result_code INTERFACE include)
set_target_properties(cango_utility_result_code PROPERTIES
	CXX_STANDARD 20
	CXX_STANDARD_REQUIRED ON
)

if (MSVC)
	add_compile_options(/utf-8)
endif()

if (PROJECT_IS_TOP_LEVEL)
	add_executable(cango_result_code_test test/test.cpp)
	target_link_libraries(cango_result_code_test PRIVATE cango::utility::result_code)
	set_target_properties(cango_result_code_test PROPERTIES
		CXX_STANDARD 20
		CXX_STANDARD_REQUIRED ON
	)
endif()

