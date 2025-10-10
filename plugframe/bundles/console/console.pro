TEMPLATE    = subdirs

SUBDIRS	    = lib \
              plugin

plugin.depends = lib

OTHER_FILES += \
    bundle.ver


