set(APP_TARGET "AuthServer")
add_executable(${APP_TARGET} main.cpp)


target_link_libraries(${APP_TARGET} PRIVATE
    LibScheduleSaver
)