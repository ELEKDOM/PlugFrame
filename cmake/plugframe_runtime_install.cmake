# cmake/plugframe_runtime_install.cmake

message(STATUS "PF_RUNTIME_ROOT  = ${PF_RUNTIME_ROOT}")
message(STATUS "PF_PROFILES_ROOT_DIR = ${PF_PROFILES_ROOT_DIR}")
message(STATUS "PF_SELECTED_PROFILE_NAME = ${PF_SELECTED_PROFILE_NAME}")
message(STATUS "PF_BUILD_TEXT = ${PF_BUILD_TEXT}")
message(STATUS "PF_BUILD_GUI  = ${PF_BUILD_GUI}")
message(STATUS "PF_CORE_LIB_FILE = ${PF_CORE_LIB_FILE}")
message(STATUS "PF_CORE_LIB_SONAME = ${PF_CORE_LIB_SONAME}")
message(STATUS "PF_CORE_LIB_LINKER = ${PF_CORE_LIB_LINKER}")
message(STATUS "PF_PLUGIN_FRAMEWORK_FILE = ${PF_PLUGIN_FRAMEWORK_FILE}")
message(STATUS "PF_PLUGIN_LOGGER_FILE = ${PF_PLUGIN_LOGGER_FILE}")
message(STATUS "PF_PLUGIN_USERS_FILE = ${PF_PLUGIN_USERS_FILE}")

if(NOT DEFINED PF_RUNTIME_ROOT OR PF_RUNTIME_ROOT STREQUAL "")
  message(FATAL_ERROR "PF_RUNTIME_ROOT is not set")
endif()

if(NOT DEFINED PF_PROFILES_ROOT_DIR OR PF_PROFILES_ROOT_DIR STREQUAL "")
  message(FATAL_ERROR "PF_PROFILES_ROOT_DIR is empty. Set -DPF_PROFILES_ROOT_DIR=... at configure time.")
endif()

if(NOT DEFINED PF_SELECTED_PROFILE_NAME OR PF_SELECTED_PROFILE_NAME STREQUAL "")
  message(FATAL_ERROR "PF_SELECTED_PROFILE_NAME is empty. Set -DPF_SELECTED_PROFILE_NAME=... at configure time.")
endif()

if(NOT DEFINED PF_BUILD_TEXT)
  message(FATAL_ERROR "PF_BUILD_TEXT is not set. Must be set to ON or OFF")
endif()

if(NOT DEFINED PF_BUILD_GUI)
  message(FATAL_ERROR "PF_BUILD_GUI is not set. Must be set to ON or OFF")
endif()

if(NOT DEFINED PF_CORE_LIB_FILE OR PF_CORE_LIB_FILE STREQUAL "")
  message(FATAL_ERROR "PF_CORE_LIB_FILE is not set")
endif()

if(PF_BUILD_GUI)
  message(STATUS "PF_GUI_LIB_FILE = ${PF_GUI_LIB_FILE}")
  message(STATUS "PF_GUI_LIB_SONAME = ${PF_GUI_LIB_SONAME}")
  message(STATUS "PF_GUI_LIB_LINKER = ${PF_GUI_LIB_LINKER}")
  message(STATUS "PF_PLUGIN_GUIDISPLAY_FILE = ${PF_PLUGIN_GUIDISPLAY_FILE}")
  message(STATUS "PF_PLUGIN_GUICONSOLE_FILE = ${PF_PLUGIN_GUICONSOLE_FILE}")
  if(NOT DEFINED PF_GUI_LIB_FILE OR PF_GUI_LIB_FILE STREQUAL "")
    message(FATAL_ERROR "PF_GUI_LIB_FILE is not set (PF_BUILD_GUI=ON)")
  endif()
endif()

if(PF_BUILD_TEXT)
  message(STATUS "PF_PLUGIN_DISPLAY_FILE = ${PF_PLUGIN_DISPLAY_FILE}")
  message(STATUS "PF_PLUGIN_CONSOLE_FILE = ${PF_PLUGIN_CONSOLE_FILE}")
endif()

# runtime directories
#####################
set(PF_BIN_DIR    "${PF_RUNTIME_ROOT}/bin")
set(PF_LIBS_DIR    "${PF_BIN_DIR}/libs")
# runtime console plugframe directories
set(PF_DIR "${PF_BIN_DIR}/plugframe")
set(PF_BUNDLES_DIR "${PF_DIR}/bundles")
set(PF_CONF_DIR "${PF_DIR}/conf")
set(PF_LOGS_DIR "${PF_DIR}/logs")
# runtime guiconsole plugframe directories
set(GUIPF_DIR "${PF_BIN_DIR}/guiplugframe")
set(GUIPF_BUNDLES_DIR "${GUIPF_DIR}/bundles")
set(GUIPF_CONF_DIR "${GUIPF_DIR}/conf")
set(GUIPF_LOGS_DIR "${GUIPF_DIR}/logs")

# remove old configuration
##########################
if(NOT PF_BUILD_TEXT)
  file(REMOVE_RECURSE
    "${PF_LIBS_DIR}"
    "${PF_DIR}"
  )
endif()

if(NOT PF_BUILD_GUI)
  file(REMOVE_RECURSE
    "${PF_LIBS_DIR}"
    "${GUIPF_DIR}"
  )
endif()

# create all directories
########################
if(PF_BUILD_TEXT OR PF_BUILD_GUI)
  execute_process(COMMAND "${CMAKE_COMMAND}" -E make_directory "${PF_BIN_DIR}")
  execute_process(COMMAND "${CMAKE_COMMAND}" -E make_directory "${PF_LIBS_DIR}")
endif()

if(PF_BUILD_TEXT)
  execute_process(COMMAND "${CMAKE_COMMAND}" -E make_directory "${PF_BUNDLES_DIR}")
  execute_process(COMMAND "${CMAKE_COMMAND}" -E make_directory "${PF_CONF_DIR}")
  execute_process(COMMAND "${CMAKE_COMMAND}" -E make_directory "${PF_LOGS_DIR}")
endif()

if(PF_BUILD_GUI)
  execute_process(COMMAND "${CMAKE_COMMAND}" -E make_directory "${GUIPF_BUNDLES_DIR}")
  execute_process(COMMAND "${CMAKE_COMMAND}" -E make_directory "${GUIPF_CONF_DIR}")
  execute_process(COMMAND "${CMAKE_COMMAND}" -E make_directory "${GUIPF_LOGS_DIR}")
endif()

# bundles install tools
#######################
function(pf_copy_bundle dest bundle_name plugin_file)
  if(NOT EXISTS "${plugin_file}")
    message(FATAL_ERROR "Bundle '${bundle_name}' missing: ${plugin_file}")
  endif()

  if(dest STREQUAL "console" OR dest STREQUAL "both")
    set(dst_console "${PF_BIN_DIR}/plugframe/bundles/${bundle_name}")
    execute_process(COMMAND "${CMAKE_COMMAND}" -E make_directory "${dst_console}")
    execute_process(COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${plugin_file}" "${dst_console}")
  endif()

  if(dest STREQUAL "gui" OR dest STREQUAL "both")
    set(dst_gui "${PF_BIN_DIR}/guiplugframe/bundles/${bundle_name}")
    execute_process(COMMAND "${CMAKE_COMMAND}" -E make_directory "${dst_gui}")
    execute_process(COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${plugin_file}" "${dst_gui}")
  endif()

  if(NOT (dest STREQUAL "console" OR dest STREQUAL "gui" OR dest STREQUAL "both"))
    message(FATAL_ERROR "pf_copy_bundle(): invalid dest='${dest}' (use console|gui|both)")
  endif()
endfunction()

function(pf_copy_conf_file src_file dst_dir)
  if(NOT EXISTS "${src_file}")
    message(FATAL_ERROR "Missing conf file: ${src_file}")
  endif()

  execute_process(COMMAND "${CMAKE_COMMAND}" -E make_directory "${dst_dir}")
  execute_process(COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                  "${src_file}" "${dst_dir}")
endfunction()

# core-lib install
##################
if(PF_BUILD_TEXT OR PF_BUILD_GUI)
  execute_process(COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                  "${PF_CORE_LIB_FILE}" "${PF_LIBS_DIR}")

  # Linux specific
  if(PF_CORE_LIB_SONAME AND PF_CORE_LIB_LINKER)
    get_filename_component(_real_name   "${PF_CORE_LIB_FILE}" NAME)
    get_filename_component(_soname_name "${PF_CORE_LIB_SONAME}" NAME)
    get_filename_component(_linker_name "${PF_CORE_LIB_LINKER}" NAME)

    # soname -> real
    execute_process(COMMAND "${CMAKE_COMMAND}" -E create_symlink
                    "${_real_name}" "${PF_LIBS_DIR}/${_soname_name}")

    # linker -> soname
    execute_process(COMMAND "${CMAKE_COMMAND}" -E create_symlink
                    "${_soname_name}" "${PF_LIBS_DIR}/${_linker_name}")
  endif()
endif()

# gui-lib install
##################
if(PF_BUILD_GUI)
  execute_process(COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                  "${PF_GUI_LIB_FILE}" "${PF_LIBS_DIR}")
  # Linux specific
  if(PF_GUI_LIB_SONAME AND PF_GUI_LIB_LINKER)
    get_filename_component(_real_name   "${PF_GUI_LIB_FILE}" NAME)
    get_filename_component(_soname_name "${PF_GUI_LIB_SONAME}" NAME)
    get_filename_component(_linker_name "${PF_GUI_LIB_LINKER}" NAME)

    # soname -> real
    execute_process(COMMAND "${CMAKE_COMMAND}" -E create_symlink
                            "${_real_name}" "${PF_LIBS_DIR}/${_soname_name}")

    # linker -> soname
    execute_process(COMMAND "${CMAKE_COMMAND}" -E create_symlink
                            "${_soname_name}" "${PF_LIBS_DIR}/${_linker_name}")
  endif()
endif()

# bundles install
#################

if(PF_BUILD_TEXT)
  pf_copy_bundle("console" "framework"  "${PF_PLUGIN_FRAMEWORK_FILE}")
  pf_copy_bundle("console" "logger"     "${PF_PLUGIN_LOGGER_FILE}")
  pf_copy_bundle("console" "users"      "${PF_PLUGIN_USERS_FILE}")
  pf_copy_bundle("console" "display"    "${PF_PLUGIN_DISPLAY_FILE}")
  pf_copy_bundle("console" "console"    "${PF_PLUGIN_CONSOLE_FILE}")
endif()

if(PF_BUILD_GUI)
  pf_copy_bundle("gui" "framework"  "${PF_PLUGIN_FRAMEWORK_FILE}")
  pf_copy_bundle("gui" "logger"     "${PF_PLUGIN_LOGGER_FILE}")
  pf_copy_bundle("gui" "users"      "${PF_PLUGIN_USERS_FILE}")
  pf_copy_bundle("gui" "guidisplay" "${PF_PLUGIN_GUIDISPLAY_FILE}")
  pf_copy_bundle("gui" "guiconsole" "${PF_PLUGIN_GUICONSOLE_FILE}")
endif()

# bundles and launcher conf files
#################################

set(PF_PROFILE_DIR "${PF_PROFILES_ROOT_DIR}/${PF_SELECTED_PROFILE_NAME}")

# PlugFrame console
###################

if(PF_BUILD_TEXT)
# Logger bundle conf
  pf_copy_conf_file(
    "${PF_PROFILE_DIR}/plugframe/console/log.ini"
    "${PF_BIN_DIR}/plugframe/bundles/logger/conf"
  )
endif()

# PlugFrame gui
###############

if(PF_BUILD_GUI)
# Launcher conf properties.ini
  pf_copy_conf_file(
    "${PF_PROFILE_DIR}/plugframe/guiconsole/properties.ini"
    "${PF_BIN_DIR}/guiplugframe/conf"
  )

# Launcher conf elekdom.qss
  pf_copy_conf_file(
    "${PF_PROFILE_DIR}/plugframe/guiconsole/elekdom.qss"
    "${PF_BIN_DIR}/guiplugframe/conf"
  )

# Logger bundle conf
  pf_copy_conf_file(
    "${PF_PROFILE_DIR}/plugframe/guiconsole/log.ini"
    "${PF_BIN_DIR}/guiplugframe/bundles/logger/conf"
  )
endif()

# finished!
###########
message(STATUS "PlugFrame runtime installed at: ${PF_BIN_DIR}")
