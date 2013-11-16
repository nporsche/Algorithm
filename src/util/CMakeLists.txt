
MESSAGE(STATUS "Begin build util.lib")
SET(LIBRARY_OUTPUT_PATH ${Algorithm_SOURCE_DIR}/lib)

aux_source_directory(. DIR_SRCS)

MESSAGE(STATUS "Source file under util:" ${DIR_SRCS})

SET(SRC_LIST ${DIR_SRCS}) 

INCLUDE_DIRECTORIES(${Algorithm_SOURCE_DIR}/include)

ADD_LIBRARY(util STATIC ${SRC_LIST})
