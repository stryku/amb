cmake_minimum_required (VERSION 2.8.12)

set(PROJECT_NAME_STR Amb)

project(${PROJECT_NAME_STR})


set(EXT_PROJECTS_DIR ${PROJECT_SOURCE_DIR}/external_projects)

add_subdirectory(${EXT_PROJECTS_DIR}/gtest)

add_definitions(${MSVC_COMPILER_DEFS})
enable_testing()
set(PROJECT_TEST_NAME ${PROJECT_NAME_STR}_tests)

include_directories(${GTEST_INCLUDE_DIRS} ${GMOCK_INCLUDE_DIRS} ${COMMON_INCLUDES})


include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX14)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
elseif(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules")
set (HOST_LIBS_DIR "C:/moje/libs/lib/x86")
set (HOST_INC_DIR "C:/moje/libs/include")


option(AMB_PRO_COMPILATION "compile healer module" ON)
if (AMB_PRO_COMPILATION)
    add_definitions(-DAMB_PRO_COMPILATION)
endif()

option(PREVENT_DEBUG "Add code to prevent debugging" OFF)
if (PREVENT_DEBUG)
    add_definitions(-DAMB_PREVENT_DEBUG)
endif()

set(BOOST_ROOT C:/moje/libs/boost/boost_1_61_0)
find_package(Boost REQUIRED)
if (NOT Boost_FOUND)
    message (ERROR "Boost not found!")
endif()
include_directories (${Boost_INCLUDE_DIRS})

set( CMAKE_PREFIX_PATH C:/Qt/Qt5.7.0/5.7/msvc2015/)

set(AMB_VERSION "v0.3.2-beta" CACHE STRING "Version tag")
add_definitions(-DAMB_VERSION=${AMB_VERSION})

set (program_name "Almost Manual Bot")


find_package (Qt5Widgets)
find_package (Qt5UiTools REQUIRED)

set (src_root ${CMAKE_CURRENT_SOURCE_DIR})
set (src_dir_qt ${src_root}/gui/AlmostManualBot)
set (inc_dir_qt ${src_root}/gui/AlmostManualBot)
set (src_dir ${src_root}/sources/src)
set (inc_dir ${src_root}/sources/inc)
set (ui_dir ${src_root}/gui/AlmostManualBot)
set (resources_dir ${src_root}/resources)
set (install_dir ${src_root}/bin)
set (test_src_dir ${src_root}/tests)
set (test_inc_dir ${test_src_dir}/details)

message (${program_name} " will be installed in:")
message (${install_dir})

include_directories (${inc_dir} 
                     ${inc_dir_qt}
                     ${Qt5UiTools_INCLUDE_DIRS})
           
set (AMB_src_qt	${src_dir_qt}/main.cpp
                        ${src_dir_qt}/mainwindow.cpp)
					
set (AMB_inc_qt ${inc_dir_qt}/mainwindow.h)
					

add_subdirectory(sources)                    
             

                     
                     
set (AMB_hdr ${inc_dir_qt}/mainwindow.h)
set (AMB_ui  ${ui_dir}/mainwindow.ui)
set (AMB_gui_src ${src_dir_qt}/main.cpp)

qt5_wrap_cpp(AMB_hdr_moc ${AMB_hdr})
qt5_wrap_ui (AMB_ui_moc  ${AMB_ui})

include_directories (${PROJECT_SOURCE_DIR})
include_directories (${PROJECT_BINARY_DIR})

add_library (AMBMocObjects OBJECT 
    ${AMB_hdr_moc}
    ${AMB_ui_moc}  
)

add_executable(Amb ${AMB_src_qt}
						  ${AMB_inc_qt}
						  ${AMB_src}
						  ${AMB_inc} 
						  $<TARGET_OBJECTS:AMBMocObjects>)
						  
target_link_libraries (Amb Qt5::Widgets Qt5::UiTools ${ZMQ_LIBRARIES} ntdll.lib)


set( TEST_SRC_FILES ${test_src_dir}/main.cpp)
                    
set (TEST_INC_FILES )

add_executable(${PROJECT_TEST_NAME} ${TEST_SRC_FILES} ${TEST_INC_FILES})
add_dependencies(${PROJECT_TEST_NAME} googletest googlemock)

if(NOT WIN32 OR MINGW)
    target_link_libraries(${PROJECT_TEST_NAME}
        ${GTEST_LIBS_DIR}/libgtest.a
        ${GTEST_LIBS_DIR}/libgtest_main.a
        ${GMOCK_LIBS_DIR}/libgmock.a
        ${GMOCK_LIBS_DIR}/libmock_main.a
        )
else()
    target_link_libraries(${PROJECT_TEST_NAME}
        debug ${GTEST_LIBS_DIR}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_FIND_LIBRARY_SUFFIXES}
        optimized ${GTEST_LIBS_DIR}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_FIND_LIBRARY_SUFFIXES}
        debug ${GMOCK_LIBS_DIR}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gmock${CMAKE_FIND_LIBRARY_SUFFIXES}
        optimized ${GMOCK_LIBS_DIR}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gmock${CMAKE_FIND_LIBRARY_SUFFIXES}
        )
    target_link_libraries(${PROJECT_TEST_NAME}
        debug ${GTEST_LIBS_DIR}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES}
        optimized ${GTEST_LIBS_DIR}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES}
        debug ${GMOCK_LIBS_DIR}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gmock_main${CMAKE_FIND_LIBRARY_SUFFIXES}
        optimized ${GMOCK_LIBS_DIR}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gmock_main${CMAKE_FIND_LIBRARY_SUFFIXES}
        )
endif()

target_link_libraries(${PROJECT_TEST_NAME} ${CMAKE_THREAD_LIBS_INIT})

install(TARGETS Amb DESTINATION  ${install_dir}/)
install(
    DIRECTORY ${resources_dir}/
    DESTINATION ${install_dir}
)
