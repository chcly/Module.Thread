option(Thread_USE_TBB "Build with Intell Thread Building Blocks." OFF)

if (Thread_USE_TBB)
    include(${Thread_SOURCE_DIR}/CMake/findTBB.cmake)
    # Note: Dependent on where Thread_INCLUDE and Thread_LIBRARY are defined,
    # Standalone: Toplevel CMakeLists.txt
    # SubModule:  DefineExternalTargetEx -> include this file...
    if (TBB_DIR)
        set(Thread_DEFINITIONS -DUSE_ONEAPI)
        
        if (ExternalTarget_LOG)
            message("APPENDING ${TBB_SDK_INCLUDE} -> ${Thread_INCLUDE}" )
        endif()

        list(APPEND Thread_INCLUDE ${TBB_SDK_INCLUDE})

        if (ExternalTarget_LOG)
            message("APPENDING TBB -> ${Thread_LIBRARY}" )
        endif()

        list(APPEND Thread_LIBRARY TBB)


        if (ExternalTarget_LOG)
            message("APPENDING Global definitions ${Thread_DEFINITIONS}" )
        endif()

        add_definitions(${Thread_DEFINITIONS})
   endif()
endif()
