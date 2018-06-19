
#==============================================================================
#
#
#                            KEYGEN PASSWORD GENERATOR
#
#
#==============================================================================

CMAKE_MINIMUM_REQUIRED (VERSION 3.8 FATAL_ERROR)

PROJECT (KeyGen
	VERSION
		0.2.0
	DESCRIPTION
		"Cross-platform password generator"
	LANGUAGES
		CXX
)

MESSAGE (STATUS "Project Source Directory: ${PROJECT_SOURCE_DIR}")

IF (NOT ${CMAKE_BUILD_TYPE})
    SET (CMAKE_BUILD_TYPE DEBUG)
ENDIF ()

MESSAGE (STATUS "Build Type: ${CMAKE_BUILD_TYPE}")

FIND_PATH (GSL_INCLUDE_DIR gsl/gsl)

CONFIGURE_FILE (${PROJECT_SOURCE_DIR}/generated/version.h.in ${PROJECT_SOURCE_DIR}/include/version.h)

ADD_EXECUTABLE (keygen
	${PROJECT_SOURCE_DIR}/src/keygen.cpp
	${CMAKE_CURRENT_BINARY_DIR}/version.h
)

ADD_EXECUTABLE (Application::KeyGen ALIAS keygen)

TARGET_INCLUDE_DIRECTORIES (keygen
	PUBLIC
	    ${GSL_INCLUDE_DIR}
		${PROJECT_SOURCE_DIR}/include
)

TARGET_COMPILE_DEFINITIONS (keygen
    PRIVATE
	    SRC_DIR=${KeyGen_SOURCE_DIR}
)

SET_TARGET_PROPERTIES (keygen
    PROPERTIES
		CXX_STANDARD 17
		CXX_STANDARD_REQUIRED ON
		CXX_EXTENSIONS OFF
)

TARGET_COMPILE_FEATURES (keygen
	PUBLIC
		cxx_attributes
		cxx_defaulted_functions
		cxx_deleted_functions
		cxx_final
)

# This command will create a new text file called 'test-file.txt' in the 
# project source directory.
# FILE (WRITE "test-file.txt" "hello!")

# This command will download the file at the url and name it as the third line.
# The dot and backslashes mean that the file should be placed in the current
# directory, the double backslash is the usual method of escaping a special
# character, in this case another backslash.
# FILE (DOWNLOAD
#     https://bit.ly/2K3mXyl
#     ".\\Serious Cryptography - Practical Introduction to Modern Encryption (No Start Press, 2018).pdf"
# )
