cmake_minimum_required(VERSION 3.20)

project("doublependulum")

add_executable(${PROJECT_NAME}
  "bob.cpp"
  "bob.h"
  "constaints.h"
  "doublependulum.cpp"
  "doublependulum.h"
  "main.cpp"
  "normalization.cpp"
  "normalization.h"
  "trail.cpp"
  "trail.h"
  ${IMGUI_SOURCES}
)

target_link_libraries(${PROJECT_NAME}
  PUBLIC
    sfml-graphics
    sfml-window
)
