#!/usr/bin/python3

# Some tools for creating a binary plugframe platform

import os
import shutil

LIBS = 'libs'
BUNDLES = 'bundles'
LOGS = 'logs'
CONF = 'conf'

def create_dir(dir_name):
    if not os.path.exists(dir_name):
        os.mkdir(dir_name)

def install_file(dir_name, file_path):
    create_dir(dir_name)
    shutil.copy2(file_path,dir_name)

def install_file2(dest_dir, src_file, dest_name):
    create_dir(dest_dir)
    dest_file = dest_dir + '/' + dest_name
    shutil.copy2(src_file, dest_file)

def remove_file(file) :
    if os.path.exists(file):
        os.remove(file)

def remove_lib(dir_name, basename):
    file=dir_name + '/' + basename
    remove_file(file)
    remove_file(file + '.1')
    remove_file(file + '.1.0')
    remove_file(file + '.1.0.0')

def install_lib(dir_name, lib_path):
    create_dir(dir_name)
    remove_lib(dir_name, os.path.basename(lib_path))
    shutil.copy2(lib_path,dir_name, follow_symlinks=False)
    shutil.copy2(lib_path + '.1',dir_name, follow_symlinks=False)
    shutil.copy2(lib_path + '.1.0',dir_name, follow_symlinks=False)
    shutil.copy2(lib_path + '.1.0.0',dir_name, follow_symlinks=False)

def create_pf_root_dir(root_target):
    create_dir(root_target)

def create_pf_dirs(root_target):
    create_dir(root_target)
    os.chdir(root_target)
    create_dir(BUNDLES)
    create_dir(LOGS)

def install_pf_lib(root_target,lib):
    os.chdir(root_target)
    install_lib(LIBS, lib)

def install_pf_bundle(root_target,bundle_name,bundle):
    os.chdir(root_target);os.chdir(BUNDLES)
    install_file(bundle_name,bundle)

def install_pf_lauching_properties(root_target,properties_ini_dir,properties_ini,dest_file):
    os.chdir(root_target)
    install_file2(properties_ini_dir,properties_ini,dest_file)

def install_bundle_conf_file(root_target,bundle_name,conf_file,dest_file):
    os.chdir(root_target)
    os.chdir(BUNDLES)
    os.chdir(bundle_name)
    install_file2(CONF, conf_file, dest_file)
