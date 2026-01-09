set (BUNDLE_NAME
     "users"
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

# Others File only for IDE
string(CONCAT BUNDLE_META_FILE_TARGET ${BUNDLE_NAME} "-meta-file-bundle")
string(CONCAT BUNDLE_META_FILE ${BUNDLE_NAME} "bundle.json")
add_custom_target(${BUNDLE_META_FILE_TARGET}
    SOURCES
    ${BUNDLE_META_FILE}
)
