cmake_minimum_required(VERSION 3.20)

project("testproject")

add_executable(${PROJECT_NAME}
  "main.cpp"
  ${IMGUI_SOURCES}
)

target_link_libraries(${PROJECT_NAME}
  PUBLIC
    sfml-graphics
    sfml-window
)
