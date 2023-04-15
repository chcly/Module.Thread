include(GroupSet)


set_group(
    TargetName_SOURCE 
    Source:*.cpp
    Header:*.h
)


include_directories(
    ${TBB_SDK_INCLUDE}
    ${Thread_INCLUDE}
    ${Utils_INCLUDE}
)


add_library(
    ${TargetName} 
    ${TargetName_SOURCE}
)


target_link_libraries(
    ${TargetName}  
    ${Utils_LIBRARY}
)

if (Thread_USE_TBB)
    target_link_libraries(
        ${TargetName}  
        TBB 
        TBB12
    )
endif()

set_target_properties(
    ${TargetName} 
    PROPERTIES FOLDER "${TargetGroup}"
)
