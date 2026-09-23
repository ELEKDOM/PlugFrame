# cmake/plugframe_install_tools.cmake

##################################
# runtime installation lifecycle #
##################################

# pf_prepare_runtime_install
function(pf_prepare_runtime_install bin_dir backup_dir)

  message(STATUS "Preparing runtime installation")
  message(STATUS "  bin dir    : ${bin_dir}")
  message(STATUS "  backup dir : ${backup_dir}")

  # Recovery mode:
  # a backup already exists because a previous installation
  # did not complete successfully.
  if(EXISTS "${backup_dir}")

    message(STATUS
            "Previous incomplete runtime installation detected."
            " Existing backup will be preserved.")

    # The current runtime may be partially rebuilt and is therefore
    # considered inconsistent.
    if(EXISTS "${bin_dir}")
      file(REMOVE_RECURSE "${bin_dir}")
    endif()

    file(MAKE_DIRECTORY "${bin_dir}")

    return()
  endif()

  # Normal mode:
  # preserve the current valid runtime before rebuilding it.
  if(EXISTS "${bin_dir}")
    file(RENAME
         "${bin_dir}"
         "${backup_dir}")
  endif()

  file(MAKE_DIRECTORY "${bin_dir}")

endfunction()

# pf_restore_app_build_artifacts
function(pf_restore_app_build_artifacts app_dir backup_app_dir)

  if(NOT EXISTS "${backup_app_dir}")
    return()
  endif()

  file(GLOB _items "${backup_app_dir}/*")

  foreach(_item IN LISTS _items)

    # Only restore files located at the application root.
    # Runtime directories (bundles, conf, logs...) are rebuilt.
    if(NOT IS_DIRECTORY "${_item}")
      file(COPY "${_item}" DESTINATION "${app_dir}")
    endif()

  endforeach()

endfunction()

# pf_restore_runtime_data
function(pf_restore_runtime_data bin_dir backup_dir)

  message(STATUS "Restoring persistent runtime data")
  message(STATUS "  bin dir    : ${bin_dir}")
  message(STATUS "  backup dir : ${backup_dir}")

  if(NOT EXISTS "${backup_dir}")
    return()
  endif()

  # Browse applications present in the new runtime.
  file(GLOB _app_dirs
       LIST_DIRECTORIES true
       "${bin_dir}/*")

  foreach(_app_dir IN LISTS _app_dirs)

    if(NOT IS_DIRECTORY "${_app_dir}/bundles")
      continue()
    endif()

    get_filename_component(_app_name "${_app_dir}" NAME)

    # Browse bundles present in the new runtime.
    file(GLOB _bundle_dirs
         LIST_DIRECTORIES true
         "${_app_dir}/bundles/*")

    foreach(_bundle_dir IN LISTS _bundle_dirs)

      if(NOT IS_DIRECTORY "${_bundle_dir}")
        continue()
      endif()

      get_filename_component(_bundle_name "${_bundle_dir}" NAME)

      set(_old_data_dir
          "${backup_dir}/${_app_name}/bundles/${_bundle_name}/data")

      if(IS_DIRECTORY "${_old_data_dir}")
        message(STATUS
                "Restoring runtime data for ${_app_name}/${_bundle_name}")

        file(COPY
             "${_old_data_dir}"
             DESTINATION "${_bundle_dir}")
      endif()

    endforeach()

  endforeach()

endfunction()

# pf_finalize_runtime_install
function(pf_finalize_runtime_install backup_dir)

  message(STATUS "Finalizing runtime installation")
  message(STATUS "  backup dir : ${backup_dir}")

  if(EXISTS "${backup_dir}")
    file(REMOVE_RECURSE "${backup_dir}")
  endif()

endfunction()

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