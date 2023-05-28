cmake_minimum_required(VERSION 3.15)
project(Thread)

# Use C++-17 by default.
enable_language(CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Set the module path to include scripts
# CMake - Contains project local modules.
#
# CMake/Modules - Contains project independent modules.
#   GitUpdate.cmake invokes python ${Thread_SOURCE_DIR}/gitupdate.py
#   to pull all submodules and update to head.
#   If this fails, it will attempt to invoke git directly to pull 
#   submodules. 
list(APPEND CMAKE_MODULE_PATH 
  ${Thread_SOURCE_DIR}/CMake 
  ${Thread_SOURCE_DIR}/CMake/Modules
)
include(Configure)
if (NOT Configure_SUCCEEDED)
   return()
endif()



if (Thread_ExternalTarget)
    set(TargetFolders ${Thread_TargetFolders})
    set(TargetName    ${Thread_TargetName})
    set(TargetGroup   ${Thread_TargetGroup})
else()
    add_subdirectory(CMake)
    add_subdirectory(Internal/Utils)
    include(${Utils_SOURCE_DIR}/CMake/Locals.cmake)

    set(TargetFolders TRUE)
    set(TargetName Thread)
    set(TargetGroup )

    set(Thread_INCLUDE  ${Thread_SOURCE_DIR})
    set(Thread_LIBRARY  ${TargetName})

    if (Thread_USE_TBB)
        include(${Thread_SOURCE_DIR}/CMake/Globals.cmake)
    endif()
endif()


add_subdirectory(Thread)

if (Thread_BUILD_TEST)
    if (NOT Thread_ExternalTarget)
        add_gtest_source(Extern/ThirdParty)
    endif()

    set(TargetGroup Units)
    add_subdirectory(Test)
endif()
