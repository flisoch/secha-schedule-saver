set(LIB_TARGET "LibScheduleSaver")
add_library(${LIB_TARGET} ScheduleSaver.cpp)

find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Boost REQUIRED COMPONENTS system)
find_package(CURL CONFIG REQUIRED)

find_library(TGBOT_CPP_LIBRARY TgBot)
target_link_libraries(
        ${LIB_TARGET} PRIVATE
        ${TGBOT_CPP_LIBRARY}
        CURL::libcurl
        Threads::Threads
        ${Boost_LIBRARIES}
        OpenSSL::SSL OpenSSL::Crypto
)

add_custom_command(
        TARGET ${LIB_TARGET} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${PROJECT_SOURCE_DIR}/src/GCalendar/python/
                ${CMAKE_CURRENT_BINARY_DIR}/
)
