add_library(parseini parseini.c inimngr.cpp)

#pass option to compiler
set(CMAKE_CXX_FLAGS "-I/home/pi/scav2020/includes")

file(
   GLOB 
   headers
   *.h
)
