set (LAUNCHER_NAME
     "plugframe_guilauncher-qt6"
)
message(STATUS "LAUNCHER_NAME = " ${LAUNCHER_NAME})

# Others File only for IDE
add_custom_target(PlugFrame_guilauncher_other_files
    SOURCES
      run-guiplugframe.sh
)

qt6_add_executable(${LAUNCHER_NAME}
    main.cpp
)

add_custom_command(TARGET ${LAUNCHER_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
          ${CMAKE_CURRENT_SOURCE_DIR}/run-guiplugframe.sh
          $<TARGET_FILE_DIR:${LAUNCHER_NAME}>/run-guiplugframe.sh
  VERBATIM
)

target_include_directories(${LAUNCHER_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE
        ${PF_CORE_LIB_INC_DIR}
        ${PF_GUI_LIB_INC_DIR}
)

target_link_libraries(${LAUNCHER_NAME}
  PRIVATE
    ${PF_CORE_LIB_NAME}
    ${PF_GUI_LIB_NAME}
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)

# Resources:
set(guilauncher_resources_resource_files
    "img/elekdom_logo.png"
)

qt6_add_resources(${LAUNCHER_NAME} "guilauncher_resources"
    PREFIX
        "/"
    FILES
        ${guilauncher_resources_resource_files}
)

target_compile_definitions(${LAUNCHER_NAME}
    PRIVATE
        QT_DEPRECATED_WARNINGS
        $<$<CONFIG:Release>:QT_NO_DEBUG_OUTPUT>
)

set_target_properties(${LAUNCHER_NAME} PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/guiplugframe"
)

