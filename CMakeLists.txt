cmake_minimum_required (VERSION 2.8.12)

set(PROJECT_NAME_STR Amb)

project(${PROJECT_NAME_STR})

set(EXT_PROJECTS_DIR ${PROJECT_SOURCE_DIR}/external_projects)

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

# OPTIONS
option(AMB_PRO_COMPILATION "compile healer module" ON)
if (AMB_PRO_COMPILATION)
    add_definitions(-DAMB_PRO_COMPILATION)
endif()

option(PREVENT_DEBUG "Add code to prevent debugging" OFF)
if (PREVENT_DEBUG)
    add_definitions(-DAMB_PREVENT_DEBUG)
endif()

option(USE_CLIPBOARD "Copy images to clipboard" OFF)
if (PREVENT_DEBUG)
    add_definitions(-DAMB_USE_CLIPBOARD)
endif()

# BOOST
set(BOOST_ROOT $ENV{BOOST_ROOT})
if(NOT BOOST_ROOT)
  message(FATAL_ERROR "Make sure that BOOST_ROOT environment variable is set.")
endif()

find_package(Boost REQUIRED)
if (NOT Boost_FOUND)
    message (ERROR "Boost not found!")
endif()
include_directories (${Boost_INCLUDE_DIRS})

# QT
set(QT $ENV{QT})
if(NOT QT)
  message(FATAL_ERROR "Make sure that QT environment variable is set.")
endif()

set( CMAKE_PREFIX_PATH ${QT})

set(AMB_VERSION "\"v0.4.0-tests\"" CACHE STRING "Version tag")
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


add_subdirectory(${EXT_PROJECTS_DIR}/gtest)
add_subdirectory(tests)  

install(TARGETS Amb DESTINATION  ${install_dir}/)
install(
    DIRECTORY ${resources_dir}/
    DESTINATION ${install_dir}
)

# CREATE LOGS DIRECTORY
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/logs)

# COPY RESOURCES
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/Debug)
file(COPY ${resources_dir}/platforms DESTINATION ${PROJECT_BINARY_DIR}/Debug)
file(COPY ${resources_dir}/Qt5Core.dll DESTINATION ${PROJECT_BINARY_DIR}/Debug)
file(COPY ${resources_dir}/Qt5Cored.dll DESTINATION ${PROJECT_BINARY_DIR}/Debug)
file(COPY ${resources_dir}/Qt5Gui.dll DESTINATION ${PROJECT_BINARY_DIR}/Debug)
file(COPY ${resources_dir}/Qt5Guid.dll DESTINATION ${PROJECT_BINARY_DIR}/Debug)
file(COPY ${resources_dir}/Qt5Widgets.dll DESTINATION ${PROJECT_BINARY_DIR}/Debug)
file(COPY ${resources_dir}/Qt5Widgetsd.dll DESTINATION ${PROJECT_BINARY_DIR}/Debug)
