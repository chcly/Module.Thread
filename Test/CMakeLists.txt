set(TestTargetName ${TargetName}Test)
include(TargetDebugOptions)

set(TestTarget_SRC
    Test1.cpp
)

include_directories(
    ${GTEST_INCLUDE}
    ${Utils_INCLUDE}
    ${Thread_INCLUDE}
)

add_executable(
    ${TestTargetName}
    ${TestTarget_SRC}
)

target_link_libraries(
    ${TestTargetName} 
    ${GTEST_LIBRARY}
    ${Thread_LIBRARY}
)

set_target_properties(
    ${TestTargetName} 
    PROPERTIES FOLDER "${TargetGroup}"
)

TARGET_DEBUG(${TestTargetName} ${CMAKE_BINARY_DIR} )

if (Thread_AUTO_RUN_TEST)
    run_test_indir(${TestTargetName} ${CMAKE_BINARY_DIR})
endif()
