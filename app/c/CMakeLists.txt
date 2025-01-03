cmake_minimum_required(VERSION 3.30.5)

project(test_player VERSION 1.0.0 LANGUAGES C)

add_library(
  test_player SHARED main.c
)

target_link_libraries(
  test_player PRIVATE
  android
  log
  OpenSLES
)
