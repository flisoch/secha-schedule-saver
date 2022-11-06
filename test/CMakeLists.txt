set(TARGET tests)
set(TARGET_SRC
    maintest.cpp
    ScheduleTest.cpp
)

add_executable( tests ${TARGET_SRC} )

find_package(GTest CONFIG REQUIRED)
target_link_libraries(${TARGET} PRIVATE 
    GTest::gmock 
    GTest::gtest 
    GTest::gmock_main 
    GTest::gtest_main
    LibScheduleSaver
    )