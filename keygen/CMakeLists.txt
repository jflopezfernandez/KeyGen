
#==============================================================================
#
#
#                            KEYGEN PASSWORD GENERATOR
#
#
#==============================================================================
#
# WriteCompilerDetectionHeader: Disabled - 18-June-2018 (7:41 PM)
# 
# The point of this string view build feature is to test whether the current
# compiler includes support for C++17. However, the module has been a pain to
# get working on both Windows and Linux, so I will be disabling it indefinitely
# until I can get a better handle on the API.
#
#==============================================================================

CMAKE_MINIMUM_REQUIRED (VERSION 3.8 FATAL_ERROR)

SET (PROJECT_NAME KeyGen)

PROJECT (${PROJECT_NAME}
	VERSION
		0.1.0
	DESCRIPTION
		"Cross-platform password generator"
	LANGUAGES
		CXX
)

MESSAGE ("Current Source Dir: ${CMAKE_CURRENT_SOURCE_DIR}")

ENABLE_TESTING ()

#INCLUDE (WriteCompilerDetectionHeader)

#SET (GEN_INCLUDE ${CMAKE_CURRENT_BINARY_DIR}/generated/)

#WRITE_COMPILER_DETECTION_HEADER (
#	FILE
#		${GEN_INCLUDE}/keygen_compiler_detection.h
#	PREFIX
#		${PROJECT_NAME}
#	COMPILERS
#		Clang
#		GNU
#		MSVC
#	FEATURES
#		cxx_std_17
#)

OPTION (DEBUG_BUILD "Build with extra debug messages and assertions.")

IF (DEBUG_BUILD)
	MESSAGE ("Debug mode enabled...")
ENDIF ()

FIND_PACKAGE (GTest REQUIRED)

SET (Boost_USE_STATIC_LIBS OFF)
SET (Boost_USE_MULTITHREADED ON)
SET (Boost_USE_STATIC_RUNTIME OFF)

FIND_PACKAGE (Boost 1.67.0 REQUIRED program_options)

IF (WIN32)
	MESSAGE ("Compiling on Windows platform...")
ENDIF ()

SET (SOURCE_HEADERS
	include/keygen.h
)

SET (SOURCE_FILES
	${SOURCE_HEADERS}
	keygen.cpp
)

ADD_EXECUTABLE (${PROJECT_NAME}
	${SOURCE_FILES}
	${WITH_STRING_VIEW}
	${SOURCE_HEADERS}
	${GTEST_INCLUDE_DIRS}
	${Boost_INCLUDE_DIRS}
)

IF (Boost_FOUND)
	MESSAGE ("Successfully found Boost")
	MESSAGE ("Boost Include Dirs: ${Boost_INCLUDE_DIRS}")
	MESSAGE ("Boost Libraries: ${Boost_LIBRARIES}")
ELSE ()
	MESSAGE (FATAL_ERROR "Cannot find Boost")
ENDIF ()

SET (BOOST_OPTIONAL_INCLUDE_DIR
	"C:\\Source-Code\\vcpkg\\packages\\boost-optional_x64-windows\\include\\"
)

#ADD_LIBRARY (StrView INTERFACE)
#SET (WITH_STRING_VIEW ${CMAKE_CURRENT_SOURCE_DIR}/WITH_STRING_VIEW)
#SET (NO_STRING_VIEW ${CMAKE_CURRENT_SOURCE_DIR}/NO_STRING_VIEW)

#TARGET_INCLUDE_DIRECTORIES (StrView
#	INTERFACE
#		"$<$<COMPILE_FEATURES:cxx_std_17>:${with_string_view}>"
#		"$<$<NOT:$<COMPILE_FEATURES:cxx_std_17>>:${no_string_view}>"
#)

TARGET_INCLUDE_DIRECTORIES (${PROJECT_NAME} BEFORE
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/include
		${Boost_INCLUDE_DIRS}
		${BOOST_OPTIONAL_INCLUDE_DIR}
		${GTEST_INCLUDE_DIRS}
		#"$<BUILD_INTERFACE:${GEN_INCLUDE}>"
)

TARGET_LINK_LIBRARIES (${PROJECT_NAME}
	PUBLIC
		#StrView
		${Boost_LIBRARIES}
		GTest::Main
		GTest::GTest
)

# Non-interface properties define the build specification of the target
# Interface properties define the usage requirements of a target

SET_TARGET_PROPERTIES (${PROJECT_NAME}
    PROPERTIES
		CXX_STANDARD 17
)

#ADD_EXECUTABLE (KeyGenNoStrView
#	${SOURCE_FILES}
#	${NO_STRING_VIEW}
#	${SOURCE_HEADERS}
#)

#TARGET_LINK_LIBRARIES (KeyGenNoStrView StrView)

#SET_TARGET_PROPERTIES (KeyGenNoStrView
#	PROPERTIES
#		CXX_STANDARD 17
#)

TARGET_COMPILE_FEATURES (${PROJECT_NAME}
	PUBLIC
		cxx_attributes
		cxx_defaulted_functions
		cxx_deleted_functions
		cxx_final
)

#INSTALL (
#	FILES
#		"${CMAKE_CURRENT_BINARY_DIR}/keygen_compiler_detection.h"
#	DESTINATION
#		include
#)

#INSTALL (
#	FILES
#		${support_files}
#	DESTINATION
#		include/compilers
#)
