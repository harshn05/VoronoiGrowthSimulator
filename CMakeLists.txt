cmake_minimum_required(VERSION 3.5)
project(VoronoiGrowthSimulator)

if(MINGW)
	set(CMAKE_EXE_LINKER_FLAGS "-static")
endif()

# first we can indicate the documentation build as an option and set it to ON by default
option(BUILD_DOCUMENTATION "Build Documentation" ON)
if(BUILD_DOCUMENTATION)
	# check if Doxygen is installed
	find_package(Doxygen)
	if (DOXYGEN_FOUND)
		# set input and output files
		set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)
		set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

		# request to configure the file
		configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
		message("Doxygen build started")

		# note the option ALL which allows to build the docs together with the application
		add_custom_target(Documentation ALL
			COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
			WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
			COMMENT "Generating API documentation with Doxygen"
			VERBATIM )
	else (DOXYGEN_FOUND)
	  message("Doxygen need to be installed to generate the doxygen documentation")
	endif (DOXYGEN_FOUND)
endif(BUILD_DOCUMENTATION)


add_library(MTEngine MTEngine/MTEngine.cpp)
FIND_PACKAGE(OpenMP)
add_library(Voronoi Voronoi.hpp Voronoi.cpp)
target_link_libraries(Voronoi PRIVATE MTEngine OpenMP::OpenMP_CXX)
add_executable(VoronoiGrowthSimulator example.cpp)
target_link_libraries(VoronoiGrowthSimulator PRIVATE Voronoi MTEngine)
FILE(COPY showvoronoi.py DESTINATION ${CMAKE_CURRENT_BINARY_DIR})