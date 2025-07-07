# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\kontr_rab_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\kontr_rab_autogen.dir\\ParseCache.txt"
  "kontr_rab_autogen"
  )
endif()
