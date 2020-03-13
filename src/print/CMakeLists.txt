add_library(print print.cpp)

#pass option to compiler
set(CMAKE_CXX_FLAGS "-I/home/pi/scav2020/includes")

#link to library
target_link_libraries(print PUBLIC parseini)

file(
   GLOB 
   headers
   *.h
)
