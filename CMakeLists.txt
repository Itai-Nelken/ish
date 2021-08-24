cmake_minimum_required(VERSION 3.16)
set(CMAKE_C_COMPILER gcc)
project(ish VERSION 0.2 LANGUAGES C)

add_executable(ish src/main.c)
if(APPLE)
	message(FATAL_ERROR "ish doesn't compile on MacOS yet because of the readline library")
else()
	target_link_libraries(ish readline)
endif()

#install target
install(
	TARGETS ish
	DESTINATION /usr/local/bin
)

execute_process(
    COMMAND bash "-c" "echo $(od -An -t x1 -j 4 -N 1 \"$(readlink -f /sbin/init)\") | tr -d '\n'" 
    OUTPUT_VARIABLE ARCH
)
if(${ARCH} STREQUAL 02)
	set(TARGET_ARCH "aarch64")
elseif(${ARCH} STREQUAL 01)
	set(TARGET_ARCH "armv7l")
endif()

if(NOT CPACK_GENERATOR)
       set(CPACK_GENERATOR "STGZ")
endif()
set(CPACK_PACKAGE_NAME "ish")
set(CPACK_PACKAGE_CONTACT "itainelken@gmail.com")
set(CPACK_PACKAGE_DESCRIPTION "A simple shell written in C")
set(CPACK_DEBIAN_PACKAGE_DEPENDS readline)
set(CPACK_VERSION_MAJOR ${CMAKE_PROJECT_VERSION_MAJOR})
set(CPACK_VERSION_MINOR ${CMAKE_PROJECT_VERSION_MINOR})
set(CPACK_VERSION_PATCH ${CMAKE_PROJECT_VERSION_PATCH})
set(CPACK_PACKAGE_VERSION ${CMAKE_PROJECT_VERSION})
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}_Linux-${TARGET_ARCH}")
include(CPack)
