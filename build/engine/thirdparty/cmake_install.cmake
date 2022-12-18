# Install script for directory: C:/Users/Qff/Desktop/axmol-dev1/thirdparty

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files/snake")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Users/Qff/Desktop/snake/build/engine/thirdparty/zlib/cmake_install.cmake")
  include("C:/Users/Qff/Desktop/snake/build/engine/thirdparty/png/cmake_install.cmake")
  include("C:/Users/Qff/Desktop/snake/build/engine/thirdparty/box2d/cmake_install.cmake")
  include("C:/Users/Qff/Desktop/snake/build/engine/thirdparty/chipmunk/cmake_install.cmake")
  include("C:/Users/Qff/Desktop/snake/build/engine/thirdparty/freetype/cmake_install.cmake")
  include("C:/Users/Qff/Desktop/snake/build/engine/thirdparty/recast/cmake_install.cmake")
  include("C:/Users/Qff/Desktop/snake/build/engine/thirdparty/bullet/cmake_install.cmake")
  include("C:/Users/Qff/Desktop/snake/build/engine/thirdparty/jpeg-turbo/cmake_install.cmake")
  include("C:/Users/Qff/Desktop/snake/build/engine/thirdparty/openssl/cmake_install.cmake")
  include("C:/Users/Qff/Desktop/snake/build/engine/thirdparty/webp/cmake_install.cmake")
  include("C:/Users/Qff/Desktop/snake/build/engine/thirdparty/pugixml/cmake_install.cmake")
  include("C:/Users/Qff/Desktop/snake/build/engine/thirdparty/xxhash/cmake_install.cmake")
  include("C:/Users/Qff/Desktop/snake/build/engine/thirdparty/lz4/cmake_install.cmake")
  include("C:/Users/Qff/Desktop/snake/build/engine/thirdparty/clipper2/cmake_install.cmake")
  include("C:/Users/Qff/Desktop/snake/build/engine/thirdparty/ConvertUTF/cmake_install.cmake")
  include("C:/Users/Qff/Desktop/snake/build/engine/thirdparty/poly2tri/cmake_install.cmake")
  include("C:/Users/Qff/Desktop/snake/build/engine/thirdparty/astc/cmake_install.cmake")
  include("C:/Users/Qff/Desktop/snake/build/engine/thirdparty/curl/cmake_install.cmake")
  include("C:/Users/Qff/Desktop/snake/build/engine/thirdparty/ogg/cmake_install.cmake")
  include("C:/Users/Qff/Desktop/snake/build/engine/thirdparty/glad/cmake_install.cmake")
  include("C:/Users/Qff/Desktop/snake/build/engine/thirdparty/glfw/cmake_install.cmake")
  include("C:/Users/Qff/Desktop/snake/build/engine/thirdparty/unzip/cmake_install.cmake")
  include("C:/Users/Qff/Desktop/snake/build/engine/thirdparty/llhttp/cmake_install.cmake")

endif()

