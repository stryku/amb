
SET(current_root ${CMAKE_CURRENT_SOURCE_DIR})

SET(TEST_SRC_FILES ${TEST_SRC_FILES}  
    ${current_root}/RelativeRectTests.cpp
    ${current_root}/StructsTests.cpp
    ${current_root}/ObservableTests.cpp
    
    PARENT_SCOPE)
 