cmake_minimum_required(VERSION 3.7.2)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# set the project name
project(modcam)

# add the binary tree to the search path for include files
# so that we will find modmngr.h
 target_include_directories(modmngr PUBLIC
 #   "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/../modmngr"
 )

#pass the version number to the source  code
#configure_file(tutorialConfig.h.in tutorialConfig.h)

#add_executable(tutorial $(SRCS) $(HEADERS))
add_executable(modcam modcam.cpp)

#pass option
set(CMAKE_CXX_FLAGS "-pthread")

#libnkl to library
target_link_libraries(modcam PUBLIC modmngr confini)

#install in /usr/local/bin (on debian)
install (
   TARGETS modcam DESTINATION bin
)
