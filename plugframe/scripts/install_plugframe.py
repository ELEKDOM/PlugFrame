#!/usr/bin/python3

# This script install both bundles sets for console and gui console.
# It's useful for testing base plugframe framework.
# To launch after the makefile (or as customized step in QtCreator).
# projects_dirs must be defined into your dev env.
# Don't forget to update PYTHON PATH.

import install_functs as pf
import projects_dirs

# plugframe dirs
#===============
root_install_dir =  projects_dirs.build_dir + '/bin'
console_install_dir = root_install_dir + '/plugframe'
guiconsole_install_dir = root_install_dir + '/guiplugframe'
pf.create_pf_root_dir(root_install_dir)
pf.create_pf_dirs(console_install_dir)
pf.create_pf_dirs(guiconsole_install_dir)

# plugframe's lib
#================
pf_lib = projects_dirs.build_dir + '/plugframe/core-lib/libplugframe-core-qt6-1.0.0.so'
pf.install_pf_lib(root_install_dir,pf_lib)

# GUI launcher's properties
#==========================
properties_ini = projects_dirs.conf_dir + '/pf_gui_properties.ini'
stylesheet_qss = projects_dirs.conf_dir + '/pf_gui_elekdom.qss'
pf.install_pf_lauching_properties(guiconsole_install_dir,pf.CONF,properties_ini,'properties.ini')
pf.install_pf_lauching_properties(guiconsole_install_dir,pf.CONF,stylesheet_qss,'elekdom.qss')

# plugframe's bundles
#====================

# framework
#----------
pf_framework = projects_dirs.build_dir + '/plugframe/bundles/framework/plugin/libframework-qt6-1.0.0.so'
pf.install_pf_bundle(console_install_dir,'framework',pf_framework)
pf.install_pf_bundle(guiconsole_install_dir,'framework',pf_framework)

# logger
#-------
pf_logger = projects_dirs.build_dir + '/plugframe/bundles/logger/plugin/liblogger-qt6-1.0.0.so'
pf_logger_ini = projects_dirs.conf_dir + '/pf_log.ini'
pf.install_pf_bundle(console_install_dir,'logger',pf_logger)
pf.install_bundle_conf_file(console_install_dir,'logger',pf_logger_ini, 'log.ini')
pf_logger_ini = projects_dirs.conf_dir + '/pf_gui_log.ini'
pf.install_pf_bundle(guiconsole_install_dir,'logger',pf_logger)
pf.install_bundle_conf_file(guiconsole_install_dir,'logger',pf_logger_ini, 'log.ini')

# display
#--------
pf_display = projects_dirs.build_dir + '/plugframe/bundles/display/plugin/libdisplay-qt6-1.0.0.so'
pf.install_pf_bundle(console_install_dir,'display',pf_display)

# GUI display
#--------
pf_guidisplay = projects_dirs.build_dir + '/plugframe/bundles/guidisplay/plugin/libguidisplay-qt6-1.0.0.so'
pf.install_pf_bundle(guiconsole_install_dir,'guidisplay',pf_guidisplay)

# console
#--------
pf_console = projects_dirs.build_dir + '/plugframe/bundles/console/plugin/libconsole-qt6-1.0.0.so'
pf.install_pf_bundle(console_install_dir,'console',pf_console)

# GUI console
#------------
pf_guiconsole = projects_dirs.build_dir + '/plugframe/bundles/guiconsole/plugin/libguiconsole-qt6-1.0.0.so'
pf.install_pf_bundle(guiconsole_install_dir,'guiconsole',pf_guiconsole)
