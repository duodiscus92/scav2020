cmake_minimum_required(VERSION 3.7.2)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#pass option to compiler
##set(CMAKE_CXX_FLAGS "-I/home/pi/scav2020/includes")

# set the project name
project(launcher)

# add the binary tree to the search path for include files
# so that we will find loader.h and inismngr.h
#target_include_directories(loader PUBLIC
#    "${PROJECT_SOURCE_DIR}/../loader"
#)
#target_include_directories(inimngr PUBLIC
#    "${PROJECT_SOURCE_DIR}/../inimngr"
#)
target_include_directories(parseini PUBLIC
    "${PROJECT_SOURCE_DIR}/../parseini"
    "${PROJECT_SOURCE_DIR}/../inimngr"
)
target_include_directories(modmngr PUBLIC
    "${PROJECT_SOURCE_DIR}/../modmngr"
)

#pass the version number to the source  code
#configure_file(tutorialConfig.h.in tutorialConfig.h)

#add_executable(tutorial $(SRCS) $(HEADERS))
add_executable(launcher launcher.cpp)

#pass option
set(CMAKE_CXX_FLAGS "-pthread")

#linkl to library
target_link_libraries(launcher PUBLIC modmngr confini)

#install in /usr/local/bin (on debian)
install (
   TARGETS launcher DESTINATION bin
)
