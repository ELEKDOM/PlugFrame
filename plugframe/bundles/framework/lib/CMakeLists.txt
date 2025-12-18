# Bundle implementation Sources
set(SOURCES
    framework.cpp
    frameworkfactory.cpp
    frameworkserviceimplementation.cpp
    frameworkstarter.cpp
    frameworkstarterlistener.cpp
    serviceregistry.cpp
    systemservice.cpp
)

# Bundle implementation Headers
set(HEADERS
    framework_forward.h
    framework.h
    frameworkfactory.h
    frameworkserviceimplementation.h
    frameworkstarter.h
    frameworkstarterlistener.h
    serviceregistry.h
    systemservice.h
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
    PUBLIC
    $<$<CONFIG:Release>:QT_NO_DEBUG_OUTPUT>
)
