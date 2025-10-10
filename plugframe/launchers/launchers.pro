TEMPLATE = subdirs

# ordered pour que le build soit réalisé dans l'ordre des déclarations des SUBDIRS !
CONFIG += ordered

SUBDIRS += \
    consolelauncher \
    guilauncher \
    qmllauncher
