set (BUNDLE_NAME
     "logger"
)
message(STATUS "BUNDLE_NAME = " ${BUNDLE_NAME})

# Bundle implementation name
string(CONCAT BUNDLE_IMPL_NAME ${BUNDLE_NAME} "-impl-qt6")
message(STATUS "BUNDLE_IMPL_NAME = " ${BUNDLE_IMPL_NAME})

# Bundle interface name
string(CONCAT BUNDLE_INT_NAME ${BUNDLE_NAME} "-qt6")
message(STATUS "BUNDLE_INT_NAME = " ${BUNDLE_INT_NAME})

# Bundle implementation
add_subdirectory(lib)

# Bundle interface
add_subdirectory(plugin)

# Non-compiled files associated with the bundle target (IDE)
string(CONCAT BUNDLE_META_FILE ${BUNDLE_NAME} "bundle.json")
target_sources(${BUNDLE_INT_NAME}
    PRIVATE
        ${BUNDLE_META_FILE}
        conf/log.ini
        conf/log_example.ini
)