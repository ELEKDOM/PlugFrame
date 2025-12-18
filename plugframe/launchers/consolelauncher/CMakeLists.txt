set (LAUNCHER_NAME
     "plugframe_launcher-qt6"
)
message(STATUS "LAUNCHER_NAME = " ${LAUNCHER_NAME})

qt6_add_executable(${LAUNCHER_NAME}
    main.cpp
)

target_include_directories(${LAUNCHER_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE
        ${PF_LIB_INC_DIR}
)

target_link_libraries(${LAUNCHER_NAME}
  PRIVATE
    ${PF_LIB_NAME}
    Qt6::Core
)

target_compile_definitions(${LAUNCHER_NAME}
    PRIVATE
        QT_DEPRECATED_WARNINGS
    PUBLIC
        $<$<CONFIG:Release>:QT_NO_DEBUG_OUTPUT>
)

set_target_properties(${LAUNCHER_NAME} PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/plugframe"
)
