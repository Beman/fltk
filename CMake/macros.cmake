#
# "$Id$"
#
# macros.cmake defines macros used by the build system
# Written by Michael Surette
#
# Copyright 1998-2015 by Bill Spitzak and others.
#
# This library is free software. Distribution and use rights are outlined in
# the file "COPYING" which should have been included with this file.  If this
# file is missing or damaged, see the license at:
#
#     http://www.fltk.org/COPYING.php
#
# Please report all bugs and problems on the following page:
#
#     http://www.fltk.org/str.php
#

#######################################################################
# macros used by the build system
#######################################################################
macro(FL_ADD_LIBRARY LIBNAME LIBTYPE LIBFILES)

    if(${LIBTYPE} STREQUAL "SHARED")
        set(LIBRARY_NAME ${LIBNAME}_SHARED)
    else()
        set(LIBRARY_NAME ${LIBNAME})
    endif(${LIBTYPE} STREQUAL "SHARED")

    add_library(${LIBRARY_NAME} ${LIBTYPE} ${LIBFILES})

    set_target_properties(${LIBRARY_NAME}
        PROPERTIES
        OUTPUT_NAME ${LIBNAME}
        DEBUG_OUTPUT_NAME "${LIBNAME}d"
        CLEAN_DIRECT_OUTPUT TRUE
        COMPILE_DEFINITIONS "FL_LIBRARY"
        )

    if(${LIBTYPE} STREQUAL "SHARED")
    set_target_properties(${LIBRARY_NAME}
        PROPERTIES
        VERSION ${FLTK_VERSION_FULL}
        SOVERSION ${FLTK_VERSION_MAJOR}.${FLTK_VERSION_MINOR}
        PREFIX "lib"    # for MSVC static/shared coexistence
        )
    endif(${LIBTYPE} STREQUAL "SHARED")

    if(MSVC)
        if(OPTION_LARGE_FILE)
            set_target_properties(${LIBNAME}
                PROPERTIES
                LINK_FLAGS /LARGEADDRESSAWARE
                )
        endif(OPTION_LARGE_FILE)

        if(${LIBTYPE} STREQUAL "SHARED")
            set_target_properties(${LIBRARY_NAME}
                PROPERTIES
                COMPILE_DEFINITIONS "FL_DLL"
                )
            endif(${LIBTYPE} STREQUAL "SHARED")
    endif(MSVC)

    install(TARGETS ${LIBRARY_NAME}
        EXPORT FLTK-Targets
        RUNTIME DESTINATION ${FLTK_BINDIR}
        LIBRARY DESTINATION ${FLTK_LIBDIR}
        ARCHIVE DESTINATION ${FLTK_LIBDIR}
        )

    list(APPEND FLTK_LIBRARIES "${LIBRARY_NAME}")
    set(FLTK_LIBRARIES ${FLTK_LIBRARIES} PARENT_SCOPE)

endmacro(FL_ADD_LIBRARY LIBNAME LIBTYPE LIBFILES)

#######################################################################
# USAGE: FLTK_RUN_FLUID TARGET_NAME "FLUID_SOURCE [.. FLUID_SOURCE]"
function(FLTK_RUN_FLUID TARGET SOURCES)
    set(CXX_FILES)
    foreach(src ${SOURCES})
        if("${src}" MATCHES "\\.fl$")
	    string(REGEX REPLACE "(.*).fl" \\1 basename ${src})
	    add_custom_command(
		OUTPUT "${basename}.cxx" "${basename}.h"
		COMMAND fluid -c ${CMAKE_CURRENT_SOURCE_DIR}/${src}
		)
	    list(APPEND CXX_FILES "${basename}.cxx")
        endif("${src}" MATCHES "\\.fl$")
        set(${TARGET} ${CXX_FILES} PARENT_SCOPE)
	endforeach(src)
endfunction(FLTK_RUN_FLUID TARGET SOURCES)

#######################################################################
macro(CREATE_EXAMPLE NAME SOURCES LIBRARIES)

    set(srcs)			# source files
    set(flsrcs)			# fluid source files

    set(tname ${NAME})		# target name
    set(oname ${NAME})		# output (executable) name

    # rename reserved target name "help" (CMake 2.8.12 and later)
    if(${tname} MATCHES "^help$")
        set(tname "test_help")
    endif(${tname} MATCHES "^help$")

    foreach(src ${SOURCES})
        if("${src}" MATCHES "\\.fl$")
            list(APPEND flsrcs ${src})
        else()
            list(APPEND srcs ${src})
        endif("${src}" MATCHES "\\.fl$")
    endforeach(src)

    set(FLUID_SOURCES)
    if(flsrcs)
	FLTK_RUN_FLUID(FLUID_SOURCES "${flsrcs}")
    endif(flsrcs)

    if(APPLE AND NOT OPTION_APPLE_X11)
      unset(RESOURCE_PATH)
      if(${tname} STREQUAL "blocks" OR ${tname} STREQUAL "checkers" OR ${tname} STREQUAL "sudoku")
        set( ICON_NAME ${tname}.icns )
        set( RESOURCE_PATH "${PROJECT_SOURCE_DIR}/test/${tname}.app/Contents/Resources/${ICON_NAME}" )
      elseif(${tname} STREQUAL "demo")
        set( RESOURCE_PATH "${PROJECT_SOURCE_DIR}/test/demo.menu" )
      endif(${tname} STREQUAL "blocks" OR ${tname} STREQUAL "checkers" OR ${tname} STREQUAL "sudoku")

      if(DEFINED RESOURCE_PATH)
        add_executable(${tname} MACOSX_BUNDLE ${srcs} ${FLUID_SOURCES} ${RESOURCE_PATH})
        if(${tname} STREQUAL "demo")
          target_compile_definitions(demo PUBLIC USING_XCODE)
        endif(${tname} STREQUAL "demo")
      else()
        add_executable(${tname} MACOSX_BUNDLE ${srcs} ${FLUID_SOURCES})
      endif(DEFINED RESOURCE_PATH)
    else()
      add_executable(${tname} WIN32 ${srcs} ${FLUID_SOURCES})
    endif(APPLE AND NOT OPTION_APPLE_X11)

    set_target_properties(${tname}    
      PROPERTIES OUTPUT_NAME ${oname}
    )
    if(APPLE AND DEFINED RESOURCE_PATH)    
      if(NOT ${tname} STREQUAL "demo")
        set_target_properties(${tname} PROPERTIES MACOSX_BUNDLE_ICON_FILE ${ICON_NAME})
      endif(NOT ${tname} STREQUAL "demo")
      set_target_properties(${tname} PROPERTIES RESOURCE ${RESOURCE_PATH})
    endif(APPLE AND DEFINED RESOURCE_PATH)
    if(APPLE AND (NOT OPTION_APPLE_X11) AND ${tname} STREQUAL "editor")
      set_target_properties("editor" PROPERTIES MACOSX_BUNDLE_INFO_PLIST "${PROJECT_SOURCE_DIR}/ide/Xcode4/plists/editor-Info.plist" )
    endif(APPLE AND (NOT OPTION_APPLE_X11) AND ${tname} STREQUAL "editor")
    
    target_link_libraries(${tname} ${LIBRARIES})

    # link in optional libraries
    if(USE_XFT)
        target_link_libraries(${tname} ${X11_Xft_LIB})
    endif(USE_XFT)

    if(HAVE_XINERAMA)
        target_link_libraries(${tname} ${X11_Xinerama_LIB})
    endif(HAVE_XINERAMA)

    if(HAVE_XRENDER)
        target_link_libraries(${tname} ${X11_Xrender_LIB})
    endif(HAVE_XRENDER)

endmacro(CREATE_EXAMPLE NAME SOURCES LIBRARIES)

#######################################################################
