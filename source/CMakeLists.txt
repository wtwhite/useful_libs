PROJECT(useful_libs)

CMAKE_MINIMUM_REQUIRED(VERSION 2.4)

SET(SRCS
	procargs.c
	fileops.c
)

STRING(COMPARE EQUAL ${CMAKE_SYSTEM_NAME} Linux LINUX)

IF(WIN32)
	SET(SRCS ${SRCS} timing_win.c)
ELSEIF(LINUX)
	SET(SRCS ${SRCS} timing_linux.c)
ELSE(WIN32)
	MESSAGE("Warning: no timing_XXX.c file for this platform!")
ENDIF(WIN32)

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/../include)
# The cmake docs were unhelpful about LIBRARY_OUTPUT_PATH, which is needed for cmake <= 2.4...  On >= 2.6, you can use CMAKE_ARCHIVE_OUTPUT_DIRECTORY instead.
SET(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/../lib CACHE FILEPATH "Location to place built library")		# Can be overridden, e.g. if you want to name the lib dir architecture-specifically
FILE(MAKE_DIRECTORY ${LIBRARY_OUTPUT_PATH})
ADD_LIBRARY(useful STATIC ${SRCS})
