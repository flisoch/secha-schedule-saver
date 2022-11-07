set(LIB_TARGET "LibScheduleSaver")
add_library(${LIB_TARGET} 
        ScheduleSaverBot.cpp
        WebServer.cpp
        Auth.cpp
)

find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Boost REQUIRED COMPONENTS system)
find_package(CURL CONFIG REQUIRED)
find_package(cpr CONFIG REQUIRED)

find_package(unofficial-mongoose CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

find_library(TGBOT_CPP_LIBRARY TgBot)
target_link_libraries(
        ${LIB_TARGET} PRIVATE
        ${TGBOT_CPP_LIBRARY}
        CURL::libcurl
        cpr::cpr
        Threads::Threads
        ${Boost_LIBRARIES}
        OpenSSL::SSL OpenSSL::Crypto
        unofficial::mongoose::mongoose
        nlohmann_json::nlohmann_json
)

add_custom_command(
        TARGET ${LIB_TARGET} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${PROJECT_SOURCE_DIR}/src/WebScraper/schedule.csv
                ${PROJECT_BINARY_DIR}/schedule.csv
)
