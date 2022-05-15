cmake_minimum_required(VERSION 3.20)

project("project")

add_definitions(-Wall -pedantic -std=gnu++20)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  include(CTest)
endif()

include(FetchContent)

# googletest
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)

FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
  FetchContent_Populate(googletest)
  add_subdirectory(
    ${googletest_SOURCE_DIR}
    ${googletest_BINARY_DIR}
  )
endif()

# sfml
set(BUILD_SHARED_LIBS false)

FetchContent_Declare(
  sfml
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG        2.5.1
)

FetchContent_GetProperties(sfml)
if(NOT sfml_POPULATED)
  if(LINK_DEPS_STATIC)
    set(SFML_STATIC_LIBRARIES CACHE BOOL TRUE)
  endif()

  FetchContent_Populate(sfml)
  add_subdirectory(
    ${sfml_SOURCE_DIR}
    ${sfml_BINARY_DIR}
  )
endif()

# imgui
set(imgui_SOURCE_DIR "${CMAKE_SOURCE_DIR}/imgui-sfml")
set(IMGUI_SOURCES
  "${imgui_SOURCE_DIR}/imconfig-SFML.h"
  "${imgui_SOURCE_DIR}/imconfig.h"
  "${imgui_SOURCE_DIR}/imgui-SFML.cpp"
  "${imgui_SOURCE_DIR}/imgui-SFML.h"
  "${imgui_SOURCE_DIR}/imgui-SFML_export.h"
  "${imgui_SOURCE_DIR}/imgui.cpp"
  "${imgui_SOURCE_DIR}/imgui.h"
  "${imgui_SOURCE_DIR}/imgui_draw.cpp"
  "${imgui_SOURCE_DIR}/imgui_internal.h"
  "${imgui_SOURCE_DIR}/imgui_tables.cpp"
  "${imgui_SOURCE_DIR}/imgui_widgets.cpp"
  "${imgui_SOURCE_DIR}/imstb_rectpack.h"
  "${imgui_SOURCE_DIR}/imstb_textedit.h"
  "${imgui_SOURCE_DIR}/imstb_truetype.h"
)
include_directories(${imgui_SOURCE_DIR})

add_subdirectory("code")
