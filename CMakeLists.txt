cmake_minimum_required (VERSION 2.8.12)
project (AMB)

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


option(MODULE_COMPILE_HEALER "compile healer module" ON)
if (MODULE_COMPILE_HEALER)
    add_definitions(-DMODULE_COMPILE_HEALER)
endif()

option(MODULE_COMPILE_LOOTER "compile looter module" ON)
if (MODULE_COMPILE_LOOTER)
    add_definitions(-DMODULE_COMPILE_LOOTER)
endif()

set(BOOST_ROOT C:/moje/libs/boost/boost_1_61_0)
find_package(Boost REQUIRED)
if (NOT Boost_FOUND)
    message (ERROR "Boost not found!")
endif()
include_directories (${Boost_INCLUDE_DIRS})

set( CMAKE_PREFIX_PATH C:/Qt/Qt5.7.0/5.7/msvc2015/)

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

add_executable(AMB ${AMB_src_qt}
						  ${AMB_inc_qt}
						  ${AMB_src}
						  ${AMB_inc} 
						  $<TARGET_OBJECTS:AMBMocObjects>)
						  
target_link_libraries (AMB Qt5::Widgets Qt5::UiTools ${ZMQ_LIBRARIES})


install(TARGETS AMB DESTINATION  ${install_dir}/)
install(
    DIRECTORY ${resources_dir}/
    DESTINATION ${install_dir}
)
