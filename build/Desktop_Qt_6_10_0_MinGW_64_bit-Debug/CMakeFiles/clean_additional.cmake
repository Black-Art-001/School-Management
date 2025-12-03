# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\SchoolManagment_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\SchoolManagment_autogen.dir\\ParseCache.txt"
  "SchoolManagment_autogen"
  )
endif()
