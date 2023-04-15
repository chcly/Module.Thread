include(GroupSet)


set_group(
    TargetName_SOURCE 
    Source:*.cpp
    Header:*.h
)


include_directories(
    ${TBB_SDK_INCLUDE}
    ${THREAD_INCLUDE}
    ${Utils_INCLUDE}
)


add_library(
    ${TargetName} 
    ${TargetName_SOURCE}
)


target_link_libraries(
    ${TargetName}  
    TBB 
    TBB12
    ${Utils_LIBRARY}
)

set_target_properties(
    ${TargetName} 
    PROPERTIES FOLDER "${TargetGroup}"
)
