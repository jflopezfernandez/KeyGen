
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
		0.2.0.0
	DESCRIPTION
		"Cross-platform password generator written in C++."
	LANGUAGES
		CXX
)

MESSAGE (STATUS "Project Source Directory: ${PROJECT_SOURCE_DIR}")

FIND_PACKAGE (Doxygen
	REQUIRED
		dot
	OPTIONAL_COMPONENTS
		mscgen
		dia
)

###############################################################################
#
#                      Doxygen Configuration Variables
#
###############################################################################
#
#                           Microsoft Windows
#
###############################################################################

IF (WIN32)
	SET (DOXYGEN_PERL_PATH "C:\\Perl64\\bin\\perl.exe")
	SET (DOXYGEN_DIA_PATH "C:\\Program Files (x86)\\Dia\\bin\\dia.exe")
	SET (DOXYGEN_DOT_PATH "C:\\Program Files (x86)\\Graphviz2.38\\bin\\dot.exe")
ELSE ()
	SET (DOXYGEN_PERL_PATH "/usr/bin/perl")
	SET (DOXYGEN_DIA_PATH "/usr/bin/dia")
	SET (DOXYGEN_DOT_PATH "/usr/bin/dot")
ENDIF (WIN32)

SET (DOXYGEN_EXTRACT_ALL YES)
SET (DOXYGEN_EXTRACT_PACKAGE YES)
SET (DOXYGEN_EXTRACT_STATIC YES)
SET (DOXYGEN_EXTRACT_LOCAL_METHODS YES)
SET (DOXYGEN_CASE_SENSE_NAMES YES)
SET (DOXYGEN_HIDE_SCOPE_NAMES NO)
SET (DOXYGEN_INLINE_SOURCES YES)
SET (DOXYGEN_GENERATE_HTML YES)
SET (DOXYGEN_GENERATE_TREEVIEW YES)
SET (DOXYGEN_UML_LOOK YES)
SET (DOXYGEN_CALL_GRAPH YES)

DOXYGEN_ADD_DOCS (
	doxygen
	${PROJECT_SOURCE_DIR}
	COMMENT
		"Automate project documentation generation process"
)

IF (Doxygen_FOUND)
	MESSAGE (STATUS "Found doxygen module")
ENDIF (Doxygen_FOUND)

FIND_PATH (GSL_INCLUDE_DIR gsl/gsl)

# Generate customized Project Configuration file
CONFIGURE_FILE ("generators/config.h.in" "a/config.h")


ADD_EXECUTABLE (keygen	
	src/keygen.cpp
	include/config.h
)

ADD_EXECUTABLE (KeyGen::KeyGen ALIAS keygen)

TARGET_INCLUDE_DIRECTORIES (keygen
	PUBLIC
	    ${PROJECT_SOURCE_DIR}/include
		${CMAKE_CURRENT_BINARY_DIR}
		${GSL_INCLUDE_DIR}
		${PROJECT_SOURCE_DIR}/src
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

# This command generates a text file called 'test.log' with the expression
# 'hello!' inside. It is created in the current configuration build directory.
# ADD_CUSTOM_COMMAND (
#     TARGET
# 	      keygen
# 	  COMMAND
# 	      echo hello! > test.log
# 	  COMMENT
# 	      "Executing custom command..."
# 	  USES_TERMINAL
# 	      TRUE
#   )

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

# This command creates a custom function that can be later invoked just like 
# any other function in the CMake Standard Library
# FUNCTION (PrintBuildConfiguration InvocationNumber)
#     MESSAGE (STATUS "\n\n\t\tINVOCATION NUMBER: ${InvocationNumber}\n\n")
# 
#     MESSAGE (STATUS "Compiler: ${CMAKE_CXX_COMPILER}")
#     MESSAGE (STATUS "Compiler ID: ${CMAKE_CXX_COMPILER_ID}")
#     MESSAGE (STATUS "Compiler Version: ${CMAKE_CXX_COMPILER_VERSION}")
#     MESSAGE (STATUS "Compiler Debug Flags: ${CMAKE_CXX_FLAGS_DEBUG}")
#     MESSAGE (STATUS "Compiler Release Flags: ${CMAKE_CXX_FLAGS_RELEASE}")
# 
# 	MESSAGE (STATUS "\n\n")
# ENDFUNCTION (PrintBuildConfiguration)
# 
# PrintBuildConfiguration (1)
# PrintBuildConfiguration (2)
# PrintBuildConfiguration (3)
