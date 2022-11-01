set(APP_TARGET "AppScheduleSaver")
add_executable(${APP_TARGET} main.cpp)


target_link_libraries(${APP_TARGET} PRIVATE
    LibScheduleSaver
)