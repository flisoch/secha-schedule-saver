set(APP_TARGET "TelegramBot")
add_executable(${APP_TARGET} main.cpp)


target_link_libraries(${APP_TARGET} PRIVATE
    LibScheduleSaver
)

add_custom_command(
        TARGET ${APP_TARGET} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${PROJECT_SOURCE_DIR}/src/web_root
                ${CMAKE_CURRENT_BINARY_DIR}/web_root
)

add_custom_command(
        TARGET ${APP_TARGET} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${PROJECT_SOURCE_DIR}/config.toml
                ${CMAKE_CURRENT_BINARY_DIR}/config.toml
)

set(INSTALL_PATH ${PROJECT_SOURCE_DIR}/deploy)
install(
        TARGETS ${APP_TARGET} 
        RUNTIME DESTINATION ${INSTALL_PATH}
)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/src/web_root/ DESTINATION ${INSTALL_PATH}/web_root)
install(FILES ${PROJECT_SOURCE_DIR}/config.toml DESTINATION ${INSTALL_PATH}/)
