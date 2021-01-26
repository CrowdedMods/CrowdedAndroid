CMAKE_MINIMUM_REQUIRED(VERSION 3.18)

SET(HOOK_SRC src)

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_ANDROID_NDK $ENV{NDK_ROOT}/platform)
SET(CMAKE_TOOLCHAIN_FILE $ENV{NDK_ROOT}/build/cmake/android.toolchain.cmake)
SET(ANDROID_ABI armeabi-v7a)
SET(ANDROID_PLATFORM 19)
# SET(ANDROID_STL c++_shared)

PROJECT(cmod)

include_directories(include)
SET(SOURCES 
    ${HOOK_SRC}/main.cpp
    ${HOOK_SRC}/structs/memory.cpp
    ${HOOK_SRC}/patches/meeting_hud.cpp
#    ${HOOK_SRC}/patches/custom_servers.cpp
    ${HOOK_SRC}/patches/generic.cpp
    ${HOOK_SRC}/gamedata/func.cpp
    ${HOOK_SRC}/gamedata/offsets.cpp
)

link_libraries("-llog")

ADD_LIBRARY(${CMAKE_PROJECT_NAME} SHARED ${SOURCES})

if(${ANDROID_ABI} STREQUAL "armeabi-v7a")
    target_link_libraries(${CMAKE_PROJECT_NAME} ${CMAKE_SOURCE_DIR}/lib/armv7/libdobby.a)
else()
    target_link_libraries(${CMAKE_PROJECT_NAME} ${CMAKE_SOURCE_DIR}/lib/arm64/libdobby.a)
endif()
