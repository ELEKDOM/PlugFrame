if(PF_BUILD_TEXT)
    add_subdirectory(consolelauncher)
endif()

if(PF_BUILD_GUI)
    add_subdirectory(guilauncher)
  #  add_subdirectory(qmllauncher)
endif()
