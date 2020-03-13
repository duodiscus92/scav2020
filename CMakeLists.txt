cmake_minimum_required(VERSION 3.7.2)

# pass the version number to the source code
configure_file(src/scav.h.in src/scav.h)

# the current version is a release
set(CMAKE_BUILD_TYPE Release)

#ths is a virtuel project as there is no executable with this name
project(scav2020)

#pass option to compiler
##set(CMAKE_CXX_FLAGS "-I/home/pi/scav2020/includes")


# subdir for the hashlib
add_subdirectory(src/hasher)
# subdir for the paseinilib
add_subdirectory(src/parser)
# subdir for printlib
add_subdirectory(src/print)
# subdir of the modmngrlib
add_subdirectory(src/modmngr)
# subdir of the loader
add_subdirectory(src/loader)
# subdir of the launcher
add_subdirectory(src/launcher)
# subdir of the modcalc module
add_subdirectory(src/modcalc)
# subdir of the camera module
add_subdirectory(src/modcam)
#subdir of the obstacle detection modul
add_subdirectory(src/modobs)

# the following lines a required to buil an installer
include(InstallRequiredSystemLibraries)
#set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${scav2020_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${scav2020_VERSION_MINOR}")
include(CPack)
