#! [0]
TEMPLATE    = subdirs

SUBDIRS	    = core-lib \
              #core-tests \
              bundles \
              launchers

bundles.depends = core-lib
launchers.depends += bundles

OTHER_FILES += \
    scripts/install_functs.py \
    scripts/install_plugframe.py
