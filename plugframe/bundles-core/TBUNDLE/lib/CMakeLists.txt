# Bundle implementation Sources
set(SOURCES
    TBUNDLE.cpp
    TBUNDLEfactory.cpp
    TBUNDLEbuilder.cpp
    TBUNDLEservice.cpp
)

# Bundle implementation Headers
set(HEADERS
    TBUNDLE_forward.h
    TBUNDLE.h
    TBUNDLEfactory.h
    TBUNDLEbuilder.h
    TBUNDLEservice.h
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
    ${PF_CORE_LIB_NAME}
)

target_compile_definitions(${BUNDLE_IMPL_NAME}
    PUBLIC
    $<$<CONFIG:Release>:QT_NO_DEBUG_OUTPUT>
)
