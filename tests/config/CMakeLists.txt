SET(current_root ${CMAKE_CURRENT_SOURCE_DIR})

SET(TEST_SRC_FILES ${TEST_SRC_FILES}
    
    ${current_root}/ConfigFileManagerTests.cpp
    ${src_dir}/config/ConfigFileManager.cpp
    
    PARENT_SCOPE)
 