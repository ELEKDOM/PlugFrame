# cmake/plugframe_runtime_install.cmake

# Default configurator installation

if(NOT DEFINED PF_RUNTIME_ROOT OR PF_RUNTIME_ROOT STREQUAL "")
  message(FATAL_ERROR "PF_RUNTIME_ROOT is not set")
endif()

################################
# runtime platform directories #
################################

set(PF_BIN_DIR    "${PF_RUNTIME_ROOT}/bin")
set(PF_LIBS_DIR   "${PF_BIN_DIR}/libs")
execute_process(COMMAND "${CMAKE_COMMAND}" -E make_directory "${PF_BIN_DIR}")
execute_process(COMMAND "${CMAKE_COMMAND}" -E make_directory "${PF_LIBS_DIR}")

# Only basic configurator is installed by default!
set(CONFIGURATOR_NAME "configurator")
set(PF_CONFIGURATOR_DIR "${PF_BIN_DIR}/${CONFIGURATOR_NAME}")
pf_create_app_subdirs(PF_CONFIGURATOR_DIR)

#####################
# libs installation #
#####################

# PLugFrame Libs
pf_copy_lib("${PF_LIBS_DIR}"
            "${PF_RUNTIME_ROOT}/plugframe/core-lib/libplugframe-core-qt6.so.1.0.0"
            "${PF_RUNTIME_ROOT}/plugframe/core-lib/libplugframe-core-qt6.so.1"
            "${PF_RUNTIME_ROOT}/plugframe/core-lib/libplugframe-core-qt6.so")

pf_copy_lib("${PF_LIBS_DIR}"
            "${PF_RUNTIME_ROOT}/plugframe/gui-lib/libplugframe-gui-qt6.so.1.0.0"
            "${PF_RUNTIME_ROOT}/plugframe/gui-lib/libplugframe-gui-qt6.so.1"
            "${PF_RUNTIME_ROOT}/plugframe/gui-lib/libplugframe-gui-qt6.so")

# Configurator Lib
pf_copy_lib("${PF_LIBS_DIR}"
            "${PF_RUNTIME_ROOT}/configurator/gui-lib/libconfigurator-gui-qt6.so.1.0.0"
            "${PF_RUNTIME_ROOT}/configurator/gui-lib/libconfigurator-gui-qt6.so.1"
            "${PF_RUNTIME_ROOT}/configurator/gui-lib/libconfigurator-gui-qt6.so")

##########

########################################################
# installation of basic configurator bundles (plugins) #
########################################################

# PlugFrame Bundles
pf_copy_bundle("${PF_CONFIGURATOR_DIR}"
               "framework"
               "${PF_RUNTIME_ROOT}/plugframe/bundles-core/framework/plugin/libframework-qt6.so")

pf_copy_bundle("${PF_CONFIGURATOR_DIR}"
               "guidisplay"
               "${PF_RUNTIME_ROOT}/plugframe/bundles-gui/guidisplay/plugin/libguidisplay-qt6.so")

# Configurator Bundles
pf_copy_bundle("${PF_CONFIGURATOR_DIR}"
               "guiconfiguratorengine"
               "${PF_RUNTIME_ROOT}/configurator/bundles/guiconfiguratorengine/plugin/libguiconfiguratorengine-qt6.so")

pf_copy_bundle("${PF_CONFIGURATOR_DIR}"
               "guidevelopermodectrl"
               "${PF_RUNTIME_ROOT}/configurator/bundles/guidevelopermodectrl/plugin/libguidevelopermodectrl-qt6.so")
