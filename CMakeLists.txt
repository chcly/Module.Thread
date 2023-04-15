cmake_minimum_required(VERSION 3.15)
project(Tbb)

# Use C++-17 by default.
enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Set the module path to include scripts
# CMake - Contains project local modules.
#
# CMake/Modules - Contains project independent modules.
#   GitUpdate.cmake invokes python ${Tbb_SOURCE_DIR}/gitupdate.py
#   to pull all submodules and update to head.
#   If this fails, it will attempt to invoke git directly to pull 
#   submodules. 
list(APPEND CMAKE_MODULE_PATH 
  ${Tbb_SOURCE_DIR}/CMake 
  ${Tbb_SOURCE_DIR}/CMake/Modules
)
include(Configure)
if (NOT Configure_SUCCEEDED)
   return()
endif()



if (Tbb_ExternalTarget)
    set(TargetFolders ${Tbb_TargetFolders})
    set(TargetName    ${Tbb_TargetName})
    set(TargetGroup   ${Tbb_TargetGroup})
else()
    add_subdirectory(CMake)

    set(TargetFolders TRUE)
    set(TargetName Tbb)
    set(TargetGroup )

    set(Tbb_INCLUDE  ${Tbb_SOURCE_DIR})
    set(Tbb_LIBRARY  ${TargetName})
endif()

add_subdirectory(Source)

if (Tbb_BUILD_TEST)
    if (NOT Tbb_ExternalTarget)
        add_gtest_source(Extern/ThirdParty)
    endif()

    set(TargetGroup Units)
    add_subdirectory(Test)
endif()
