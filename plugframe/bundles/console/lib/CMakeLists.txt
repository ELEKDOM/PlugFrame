# Bundle implementation Sources
set(SOURCES
    console.cpp
    consolefactory.cpp
    consolelistener.cpp
    consoleexit.cpp
    terminal.cpp
    cmd/cmdprocessor.cpp
    cmd/helpcmdprocessor.cpp
    cmd/levelcmdprocessor.cpp
    cmd/loadedlistcmdprocessor.cpp
    cmd/quitcmdprocessor.cpp
    cmd/startedlistcmdprocessor.cpp
)

# Bundle implementation Headers
set(HEADERS
    console_forward.h
    console.h
    consolefactory.h
    consolelistener.h
    consoleexit.h
    terminal.h
    cmd/cmdprocessor.h
    cmd/helpcmdprocessor.h
    cmd/levelcmdprocessor.h
    cmd/loadedlistcmdprocessor.h
    cmd/quitcmdprocessor.h
    cmd/startedlistcmdprocessor.h
   )

qt_add_library(${BUNDLE_IMPL_NAME} STATIC ${SOURCES} ${HEADERS})

target_include_directories(${BUNDLE_IMPL_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE
        ${PF_LIB_INC_DIR}
)

target_link_libraries(${BUNDLE_IMPL_NAME} PUBLIC
    Qt6::Core
    ${PF_LIB_NAME}
)

target_compile_definitions(${BUNDLE_IMPL_NAME}
    PRIVATE
    $<$<CONFIG:Release>:QT_NO_DEBUG_OUTPUT>
)
