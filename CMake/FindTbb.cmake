set(TBB_ROOT $ENV{TBB_DIR})

function(find_tbb_dist)

    find_path(
        TBB_SDK_INCLUDE
        NAMES oneapi/tbb.h
        HINTS "${TBB_ROOT}/include"
    )

   find_path(
        TBB_SDK_LIBRARY_PATH
        NAMES tbb.lib tbb12.lib tbbmalloc.lib
        HINTS "${TBB_ROOT}/lib"
    )


   find_path(
        TBB_SDK_BIN_PATH
        NAMES tbb.dll tbb12.dll tbbmalloc.dll
        HINTS "${TBB_ROOT}/bin"
    )


    set(TBB_FOUND TRUE PARENT_SCOPE)
    set(TBB_DIR ${TBB_ROOT} CACHE PATH "")

endfunction()


macro(add_import Name D1 R1)
    if (NOT ${Name}_IMPORTED)
        set(${Name}_IMPORTED TRUE PARENT_SCOPE)

        if (NOT EXISTS "${TBB_SDK_LIBRARY_PATH}/${D1}.lib")
            message("Build and install the source first!")
            return()
        endif()

        add_library(${Name} STATIC IMPORTED)

        set_property(
            TARGET ${Name} APPEND  PROPERTY 
            IMPORTED_CONFIGURATIONS RELEASE DEBUG MINSIZEREL RELWITHDEBINFO
        )
        set_target_properties(
            ${Name} 
            PROPERTIES
            IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG  "CXX"
            IMPORTED_LOCATION_DEBUG                  "${TBB_SDK_LIBRARY_PATH}/${D1}.lib"
            IMPORTED_LOCATION_RELEASE                "${TBB_SDK_LIBRARY_PATH}/${R1}.lib"
            MAP_IMPORTED_CONFIG_DEBUG                Debug
            MAP_IMPORTED_CONFIG_MINSIZEREL           Release
            MAP_IMPORTED_CONFIG_RELWITHDEBINFO       Release
            MAP_IMPORTED_CONFIG_RELEASE              Release
        )
    endif()
endmacro()

function(copy_dlls)

    if (TBB_SDK_BIN_PATH)

        file(GLOB DLL ${TBB_SDK_BIN_PATH}/*.dll)

        foreach(L1 ${DLL})
            get_filename_component(V1 ${L1} NAME)

            execute_process(COMMAND
                ${CMAKE_COMMAND} 
                    -E copy_if_different ${L1} ${CMAKE_BINARY_DIR}/${V1}
            )
        endforeach()

    endif()
endfunction()


function(import_targets)

    find_tbb_dist()
    add_import(TBB  tbb_debug tbb)
    add_import(TBBMalloc  tbbmalloc_debug tbbmalloc )
    add_import(TBB12  tbb12_debug tbb12)
    copy_dlls()

endfunction()

import_targets()


