add_library(hasher SHARED hasher.c)

install(TARGETS hasher DESTINATION lib)

file(
   GLOB 
   headers
   *.h
)
