# Bundle implementation Sources
set(SOURCES
    logdevice.cpp
    logdisplay.cpp
    logfile.cpp
    logfilter.cpp
    logger.cpp
    loggerfactory.cpp
)

# Bundle implementation Headers
set(HEADERS
    logger_forward.h
    logger.h
    loggerfactory.h
    logdevice.h
    logdisplay.h
    logfile.h
    logfilter.h
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
