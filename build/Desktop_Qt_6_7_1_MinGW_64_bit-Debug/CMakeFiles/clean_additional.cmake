# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\bookManagement_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\bookManagement_autogen.dir\\ParseCache.txt"
  "bookManagement_autogen"
  )
endif()
