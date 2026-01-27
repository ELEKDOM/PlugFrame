set (LAUNCHER_NAME
     "plugframe_launcher-qt6"
)
message(STATUS "LAUNCHER_NAME = " ${LAUNCHER_NAME})

# Others File only for IDE
add_custom_target(PlugFrame_launcher_other_files
    SOURCES
      run-plugframe.sh
)

qt6_add_executable(${LAUNCHER_NAME}
    main.cpp
)

add_custom_command(TARGET ${LAUNCHER_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
          ${CMAKE_CURRENT_SOURCE_DIR}/run-plugframe.sh
          $<TARGET_FILE_DIR:${LAUNCHER_NAME}>/run-plugframe.sh
  VERBATIM
)

target_include_directories(${LAUNCHER_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE
        ${PF_CORE_LIB_INC_DIR}
)

target_link_libraries(${LAUNCHER_NAME}
  PRIVATE
    ${PF_CORE_LIB_NAME}
    Qt6::Core
)

target_compile_definitions(${LAUNCHER_NAME}
    PRIVATE
        QT_DEPRECATED_WARNINGS
        $<$<CONFIG:Release>:QT_NO_DEBUG_OUTPUT>
)

set_target_properties(${LAUNCHER_NAME} PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/plugframe"
)
