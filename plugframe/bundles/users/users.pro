TEMPLATE    = subdirs

SUBDIRS	    = lib \
              plugin

plugin.depends = lib

OTHER_FILES += \
    bundle.ver \
    conf/users.ini \
    conf/users_example.ini
