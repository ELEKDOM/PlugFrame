TEMPLATE    = subdirs

SUBDIRS	    = lib \
              plugin

plugin.depends = lib

OTHER_FILES += \
    conf/log.ini \
    conf/log_example.ini \
    bundle.ver


