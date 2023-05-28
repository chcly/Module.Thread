option(Thread_USE_TBB "Build with Intell Thread Building Blocks." OFF)

if (Thread_USE_TBB)
    if (Thread_DIRECTORY)
        include(${Thread_DIRECTORY}/CMake/FindTBB.cmake)
    elseif(Thread_SOURCE_DIR)
        include(${Thread_SOURCE_DIR}/CMake/FindTBB.cmake)
    endif()    
    # Note: Dependent on where Thread_INCLUDE and Thread_LIBRARY are defined,
    # Standalone: Toplevel CMakeLists.txt
    # SubModule:  DefineExternalTargetEx -> include this file...
    if (TBB_DIR)
        set(Thread_DEFINITIONS -DUSE_ONEAPI)
        
        if (ExternalTarget_LOG)
            message(STATUS "APPENDING ${TBB_SDK_INCLUDE} -> ${Thread_INCLUDE}" )
        endif()

        list(APPEND Thread_INCLUDE ${TBB_SDK_INCLUDE})

        if (ExternalTarget_LOG)
            message(STATUS "APPENDING TBB -> ${Thread_LIBRARY}" )
        endif()

        list(APPEND Thread_LIBRARY TBB)


        if (ExternalTarget_LOG)
            message(STATUS "APPENDING Global definitions ${Thread_DEFINITIONS}" )
        endif()

        add_definitions(${Thread_DEFINITIONS})
   endif()
endif()
