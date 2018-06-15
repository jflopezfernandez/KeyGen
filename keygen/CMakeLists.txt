# CMakeList.txt : CMake project for keygen, include source and define
# project specific logic here.
#
CMAKE_MINIMUM_REQUIRED (VERSION 3.8)

ENABLE_TESTING ()

FIND_PACKAGE (GTest REQUIRED)
INCLUDE_DIRECTORIES (${GTEST_INCLUDE_DIRS})

#[==[ DISABLED glog FOR NOW
FIND_PACKAGE (glog REQUIRED)

IF (glog_FOUND)
	MESSAGE ("Successfully found glog")
ELSE ()
	MESSAGE (FATAL_ERROR "Could not find glog")
ENDIF ()
#]==]

FIND_PACKAGE (Boost 1.67.0 REQUIRED COMPONENTS program_options)

IF (Boost_FOUND)
	MESSAGE ("Successfully found Boost")
ELSE ()
	MESSAGE (FATAL_ERROR "Cannot find Boost")
ENDIF ()

IF (WIN32)
	MESSAGE ("Compiling on Windows platform...")
ENDIF ()

# TODO: Add source to this project's executable.
#ADD_EXECUTABLE (keygen keygen.cpp keygen.h)
ADD_EXECUTABLE (keygen keygen.cpp)

TARGET_LINK_LIBRARIES (keygen
	PRIVATE
		Boost::program_options
		#glog::glog
		GTest::Main
		GTest::GTest
)

# Non-interface properties define the build specification of the target
# Interface properties define the usage requirements of a target

TARGET_COMPILE_FEATURES (keygen
	PRIVATE
		cxx_std_11
)
