add_library(modmngr modmngr.cpp)

#pass option to compiler
set(CMAKE_CXX_FLAGS "-I/home/pi/scav2020/includes")

#link to library
target_link_libraries(modmngr PUBLIC parseini)

file(
   GLOB 
   headers
   *.h
)
