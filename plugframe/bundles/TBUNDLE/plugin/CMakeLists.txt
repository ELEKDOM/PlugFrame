qt_add_plugin(${BUNDLE_INT_NAME}
    #sources plugin
    ${BUNDLE_NAME}plugin.cpp
    ${BUNDLE_NAME}plugin.h
)

target_link_libraries(${BUNDLE_INT_NAME}
    PRIVATE
        ${BUNDLE_IMPL_NAME}
        Qt6::Core
)
