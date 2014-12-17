cmake_minimum_required(VERSION 2.8)

find_package(Mono)
set_package_properties(Mono PROPERTIES DESCRIPTION "An open source implementation the CLR" URL "www.mono-project.com")
set_package_properties(Mono PROPERTIES TYPE RECOMMENDED PURPOSE "Enables the NumCIL package")

if(MONO_FOUND)

  # Enumerate over all .tt files and apply T4 to them
  SET(numcil_tt_outputs)
  FILE(GLOB files NumCIL/*.tt NumCIL.Unsafe/*.tt)

  FOREACH(file ${files})
    SET(src ${file})
    GET_FILENAME_COMPONENT(basename ${file} NAME_WE)
    GET_FILENAME_COMPONENT(targetfolder ${file} PATH)
    SET(dst ${targetfolder}/${basename}.cs)
    ADD_CUSTOM_COMMAND(
      OUTPUT ${dst}
      DEPENDS ${file}
      COMMAND ${MONO_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/buildsupport/TextTransform.exe --out=${dst} ${src}
    )
    SET(numcil_tt_outputs ${numcil_tt_outputs} ${dst})
  ENDFOREACH(file)

  file(GLOB sln_sources NumCIL/*.cs NumCIL/*.csproj NumCIL.Unsafe/*.cs NumCIL.Unsafe/*.csproj)
  set(numcil_binaries ${CMAKE_CURRENT_BINARY_DIR}/bin/Release/NumCIL.dll ${CMAKE_CURRENT_BINARY_DIR}/bin/Release/NumCIL.Unsafe.dll)
  add_custom_command(
      OUTPUT ${numcil_binaries}
      COMMAND ${XBUILD_EXECUTABLE} /property:Configuration=Release /property:OutputPath=${CMAKE_CURRENT_BINARY_DIR}/bin/Release ${CMAKE_CURRENT_SOURCE_DIR}/NumCIL.sln
      DEPENDS ${sln_sources} ${numcil_tt_outputs}
  )

  # Re-usable simple name for NumCIL target
  add_custom_target(
    numcil ALL
    DEPENDS ${numcil_binaries}
  )

  install(FILES ${numcil_binaries} DESTINATION lib COMPONENT bohrium-numcil)

else()
  message("Cannot build NumCIL as Mono or xbuild is missing")
endif()