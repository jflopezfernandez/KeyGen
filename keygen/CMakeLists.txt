
#==============================================================================
#
#
#                            KEYGEN PASSWORD GENERATOR
#
#
#==============================================================================

CMAKE_MINIMUM_REQUIRED (VERSION 3.8)

ENABLE_TESTING ()

OPTION (DEBUG_BUILD "Build with extra debug messages and assertions.")

IF (DEBUG_BUILD)
	MESSAGE ("Debug mode enabled...")
ENDIF ()

FIND_PACKAGE (GTest REQUIRED)

FIND_PACKAGE (Boost 1.67.0 REQUIRED COMPONENTS program_options)

IF (Boost_FOUND)
	MESSAGE ("Successfully found Boost")
ELSE ()
	MESSAGE (FATAL_ERROR "Cannot find Boost")
ENDIF ()

IF (WIN32)
	MESSAGE ("Compiling on Windows platform...")
ENDIF ()

SET (SOURCE_FILES
	keygen.cpp
)

SET (SOURCE_HEADERS
	include/keygen/keygen.h
)

ADD_EXECUTABLE (keygen ${SOURCE_FILES} ${SOURCE_HEADERS})

TARGET_INCLUDE_DIRECTORIES (keygen PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/include/keygen
	${GTEST_INCLUDE_DIRS}
)

TARGET_LINK_LIBRARIES (keygen
	PRIVATE
		Boost::program_options
		GTest::Main
		GTest::GTest
)

# Non-interface properties define the build specification of the target
# Interface properties define the usage requirements of a target

TARGET_COMPILE_FEATURES (keygen
	PRIVATE
		cxx_std_11
)
