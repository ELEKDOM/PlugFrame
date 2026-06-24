# cmake/plugframe_install_tools.cmake

#########################
# bundles install tools #
#########################

# pf_copy_bundle
function(pf_copy_bundle app_dest_dir bundle_name plugin_file)

  if(NOT EXISTS "${plugin_file}")
    message(FATAL_ERROR "Bundle '${bundle_name}' missing: ${plugin_file}")
  endif()

  set(dst_bundle "${app_dest_dir}/bundles/${bundle_name}")
  execute_process(COMMAND "${CMAKE_COMMAND}" -E make_directory "${dst_bundle}")
  execute_process(COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${plugin_file}" "${dst_bundle}")

endfunction()

# pf_copy_conf_file
function(pf_copy_conf_file src_file dst_dir)

  if(NOT EXISTS "${src_file}")
    message(FATAL_ERROR "Missing conf file: ${src_file}")
  endif()

  execute_process(COMMAND "${CMAKE_COMMAND}" -E make_directory "${dst_dir}")
  execute_process(COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${src_file}" "${dst_dir}")

endfunction()

# pf_copy_lib
# lib_soname & lib_linker are 4 Linux only
function(pf_copy_lib libs_dest_dir lib_file lib_soname lib_linker)

  if(NOT EXISTS "${lib_file}")
    message(FATAL_ERROR "Missing lib file: ${lib_file}")
  endif()

  execute_process(COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${lib_file}" "${libs_dest_dir}")

  # Linux specific
  ################
  if(lib_soname AND lib_linker)
    get_filename_component(_real_name   "${lib_file}" NAME)
    get_filename_component(_soname_name "${lib_soname}" NAME)
    get_filename_component(_linker_name "${lib_linker}" NAME)

    # soname -> real
    execute_process(COMMAND "${CMAKE_COMMAND}" -E create_symlink
                    "${_real_name}" "${libs_dest_dir}/${_soname_name}")

    # linker -> soname
    execute_process(COMMAND "${CMAKE_COMMAND}" -E create_symlink
                    "${_soname_name}" "${libs_dest_dir}/${_linker_name}")
  endif()

endfunction()

# pf_create_app_subdirs
function(pf_create_app_subdirs app_dir)

  execute_process(COMMAND "${CMAKE_COMMAND}" -E make_directory "${app_dir}/bundles")
  execute_process(COMMAND "${CMAKE_COMMAND}" -E make_directory "${app_dir}/conf")
  execute_process(COMMAND "${CMAKE_COMMAND}" -E make_directory "${app_dir}/logs")

endfunction()