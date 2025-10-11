#! [0]
TEMPLATE    = subdirs

SUBDIRS	    = plugframe \
              applications

applications.depends = plugframe

OTHER_FILES += README.md
