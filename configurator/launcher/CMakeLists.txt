set (LAUNCHER_NAME
     "configurator_launcher-qt6"
)
message(STATUS "LAUNCHER_NAME = " ${LAUNCHER_NAME})

qt6_add_executable(${LAUNCHER_NAME})

add_custom_command(TARGET ${LAUNCHER_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
          ${CMAKE_CURRENT_SOURCE_DIR}/run-configurator.sh
          $<TARGET_FILE_DIR:${LAUNCHER_NAME}>/run-configurator.sh
  VERBATIM
)

target_sources(${LAUNCHER_NAME}
  PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}/../../plugframe/launchers/guilauncher/main.cpp"
)

target_include_directories(${LAUNCHER_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${LAUNCHER_NAME}
  PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    plugframe-core-qt6
    plugframe-gui-qt6
    ${CONFIGURATOR_GUI_LIB_NAME}
)

target_compile_definitions(${LAUNCHER_NAME}
    PRIVATE
        QT_DEPRECATED_WARNINGS
        $<$<CONFIG:Release>:QT_NO_DEBUG_OUTPUT>
)

set_target_properties(${LAUNCHER_NAME} PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/configurator"
)

# Others File only for IDE
add_custom_target(configurator_launcher_other_files
    SOURCES
      run-configurator.sh
)

# Resources:
set(configurator_resources_files
    "img/app_icon16.png"
    "img/app_icon32.png"
    "img/app_icon48.png"
    "img/app_icon128.png"
    "img/elekdom_logo.png"
  )

qt6_add_resources(${LAUNCHER_NAME} "configurator_resources"
    PREFIX
       "/"
    FILES
        ${configurator_resources_files}
)