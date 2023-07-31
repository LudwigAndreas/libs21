FILE (GLOB_RECURSE test_SRCS
    *.cc
    )

FILE (GLOB_RECURSE project_SRCS
    ../src/*.cc
    )

INCLUDE_DIRECTORIES(${MAINFOLDER}/include)

SET (test_LIBS ${GTest_Library})

SET (test_BIN ${PROJECT_NAME}-unittests)

ADD_EXECUTABLE(${test_BIN} ${project_SRCS} ${test_SRCS})
TARGET_LINK_LIBRARIES(${test_BIN} ${test_LIBS})
TARGET_INCLUDE_DIRECTORIES(${test_BIN} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

ADD_CUSTOM_TARGET(check ALL "${MAINFOLDER}/bin/${test_BIN}" DEPENDS ${test_BIN} COMMENT "Executing unit tests..." VERBATIM SOURCES ${test_SRCS} ${project_SRCS})
ADD_CUSTOM_TARGET(test "${MAINFOLDER}/bin/${test_BIN}" DEPENDS ${test_BIN} COMMENT "Executing unit tests..." VERBATIM SOURCES ${test_SRCS} ${project_SRCS})
