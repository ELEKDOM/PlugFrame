# Bundle implementation Sources
set(SOURCES
    tcpserver.cpp
    tcpserverfactory.cpp
    tcpserverbuilder.cpp
    tcpserverconnmanager.cpp
    tcpserverservice.cpp
)

# Bundle implementation Headers
set(HEADERS
    tcpserver_forward.h
    tcpserver_logchannel.h
    tcpserver.h
    tcpserverfactory.h
    tcpserverbuilder.h
    tcpserverconnmanager.h
    tcpserverservice.h
   )

qt_add_library(${BUNDLE_IMPL_NAME} STATIC ${SOURCES} ${HEADERS})

target_include_directories(${BUNDLE_IMPL_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE
        ${PF_CORE_LIB_INC_DIR}
)

target_link_libraries(${BUNDLE_IMPL_NAME} PUBLIC
    Qt6::Core
    Qt6::Network
    ${PF_CORE_LIB_NAME}
)

target_compile_definitions(${BUNDLE_IMPL_NAME}
    PUBLIC
    $<$<CONFIG:Release>:QT_NO_DEBUG_OUTPUT>
)
