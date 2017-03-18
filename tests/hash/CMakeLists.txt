SET(current_root ${CMAKE_CURRENT_SOURCE_DIR})

SET(TEST_SRC_FILES ${TEST_SRC_FILES}
    ${src_dir}/hash/Hash.cpp
	
    ${current_root}/HashTests.cpp
    
    PARENT_SCOPE)
 