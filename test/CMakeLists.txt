set(TARGET tests)
set(TARGET_SRC maintest.cpp ScheduleTest.cpp ConfigTest.cpp)

add_executable(tests ${TARGET_SRC})

find_package(GTest CONFIG REQUIRED)
target_link_libraries(
  ${TARGET} PRIVATE GTest::gmock GTest::gtest GTest::gmock_main
                    GTest::gtest_main ScheduleSaver)

add_custom_command(
  TARGET ${TARGET}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/config.toml
          ${CMAKE_CURRENT_BINARY_DIR}/config.toml)

add_custom_command(
  TARGET ${TARGET}
  POST_BUILD
  COMMAND
    ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/src/WebScraper/schedule.csv
    ${CMAKE_CURRENT_BINARY_DIR}/schedule.csv)
