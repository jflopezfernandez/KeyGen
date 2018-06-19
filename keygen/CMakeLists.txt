
#==============================================================================
#
#
#                            KEYGEN PASSWORD GENERATOR
#
#
#==============================================================================

CMAKE_MINIMUM_REQUIRED (VERSION 3.8 FATAL_ERROR)

SET (PROJECT_NAME KeyGen)

PROJECT (${PROJECT_NAME}
	VERSION
		0.2.0
	DESCRIPTION
		"Cross-platform password generator"
	LANGUAGES
		CXX
)

FIND_PATH (GSL_INCLUDE_DIR gsl/gsl)

SET (SOURCE_HEADERS
	include/keygen.h
	include/password.h
)

SET (SOURCE_TESTS
    tests/password-generation.cpp
)

SET (SOURCE_FILES
	${SOURCE_HEADERS}
	${SOURCE_TESTS}
	keygen.cpp
)

ADD_EXECUTABLE (${PROJECT_NAME}
	${SOURCE_FILES}
)

TARGET_INCLUDE_DIRECTORIES (${PROJECT_NAME} BEFORE
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}
		${CMAKE_CURRENT_SOURCE_DIR}/include
		${GSL_INCLUDE_DIR}
)

SET_TARGET_PROPERTIES (${PROJECT_NAME}
    PROPERTIES
		CXX_STANDARD 17
		CXX_STANDARD_REQUIRED ON
		CXX_EXTENSIONS OFF
)

TARGET_COMPILE_FEATURES (${PROJECT_NAME}
	PUBLIC
		cxx_attributes
		cxx_defaulted_functions
		cxx_deleted_functions
		cxx_final
)
