
SET(current_root ${CMAKE_CURRENT_SOURCE_DIR})

SET(TEST_SRC_FILES ${TEST_SRC_FILES}
    ${current_root}/modules/healer/HealRuleTests.cpp
    ${src_dir}/ui/modules/healer/HealRule.cpp
    
    ${current_root}/updaters/details/MainWindowTitleBuilderTests.cpp
    ${src_dir}/ui/updaters/details/MainWindowTitleBuilder.cpp
    
    PARENT_SCOPE)
 