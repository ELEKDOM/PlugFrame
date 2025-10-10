TEMPLATE    = subdirs

#get all projects directories
sd = $$files(*)
for(d, sd): \
    exists($$d/$${d}.pro): \
    SUBDIRS += $$d
