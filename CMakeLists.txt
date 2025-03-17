cmake_minimum_required(VERSION 3.8)

if(1)
	get_filename_component(CURRENT_DIR_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
	set(ProjectName "${CURRENT_DIR_NAME}")

	include($ENV{cpp_lib_build_scripts_path}/cmake-module/setup.cmake)

	project(${ProjectName})
	enable_language(ASM)
	set(CMAKE_CXX_STANDARD 20)
	set(CMAKE_C_STANDARD 17)
endif()


include(target_import_boost)
include(target_import_ffmpeg_wrapper)
include(target_import_tsduck)
include(target_import_sdl2_wrapper)

add_executable(${ProjectName})
target_compile_definitions(${ProjectName} PRIVATE Predefine_ResourceDir="D:/video/视频开发测试")
target_import_src(${ProjectName})

target_link_libraries(${ProjectName} PUBLIC -Wl,--start-group)
target_import_boost_asio(${ProjectName} PUBLIC)
target_import_ffmpeg_wrapper(${ProjectName} PUBLIC)
target_import_tsduck(${ProjectName} PUBLIC)
target_import_sdl2_wrapper(${ProjectName} PUBLIC)
target_link_libraries(${ProjectName} PUBLIC -Wl,--end-group)
