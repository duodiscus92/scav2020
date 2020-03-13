cmake_minimum_required(VERSION 3.7.2)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# set the project name
project(loader)

# add the binary tree to the search path for include files
# so that we will find hasher.h
 target_include_directories(hasher PUBLIC
 #   "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/../hasher"
 )

#pass the version number to the source  code
#configure_file(tutorialConfig.h.in tutorialConfig.h)

#pass option to compiler
set(CMAKE_CXX_FLAGS "-I/home/pi/scav2020/includes")


#add_executable(tutorial $(SRCS) $(HEADERS))
add_executable(mul mul.c)
add_executable(mdl mdl.c)

#link to library
target_link_libraries(mul PUBLIC hasher mhash)
target_link_libraries(mdl PUBLIC hasher mhash)
#target_link_libraries(mul PUBLIC )
#target_link_libraries(mdl PUBLIC hasher)

#install in /usr/local/bin (on debian)
install (
   TARGETS mul mdl DESTINATION bin
)
