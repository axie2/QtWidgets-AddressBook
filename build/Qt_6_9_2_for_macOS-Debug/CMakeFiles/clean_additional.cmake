# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/addressbook_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/addressbook_autogen.dir/ParseCache.txt"
  "addressbook_autogen"
  )
endif()
