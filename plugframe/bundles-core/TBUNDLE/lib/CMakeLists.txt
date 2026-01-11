# Bundle implementation Sources
set(SOURCES
    TBUNDLE.cpp
    TBUNDLEfactory.cpp
    TBUNDLEbuilder.cpp
    TBUNDLEservice.cpp
)

# Bundle implementation Headers
set(HEADERS
    TBUNDLE.h
    TBUNDLE_forward.h
    TBUNDLEfactory.h
    TBUNDLEservice.h
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
