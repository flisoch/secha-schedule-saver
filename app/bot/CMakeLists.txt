set(APP_TARGET "TelegramBot")
add_executable(${APP_TARGET} main.cpp)


target_link_libraries(${APP_TARGET} PRIVATE
    LibScheduleSaver
)