add_library(modmngr modmngr.cpp)

#link to library
target_link_libraries(modmngr PUBLIC parseini)

file(
   GLOB 
   headers
   *.h
)
