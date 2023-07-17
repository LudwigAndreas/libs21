FILE (GLOB_RECURSE project_SRCS
    s21_file_map_reader.cc
    s21_to_upper.cc
    s21_to_lower.cc
    s21_split.cc
    )

SET (project_MOC_HEADERS ../include/s21.h)
SET (project_LIBS )
SET (project_BIN ${PROJECT_NAME})

ADD_LIBRARY(${project_BIN} STATIC ${project_SRCS} PropertiesReader.cc PropertiesReader.h Logger.h LoggerThreading.h)
#ADD_EXECUTABLE(${project_BIN} ${project_SRCS} ${project_MOC_SRCS_GENERATED})
TARGET_LINK_LIBRARIES(${project_BIN} ${project_LIBS})
SET_TARGET_PROPERTIES(${project_BIN} PROPERTIES VERSION "${APPLICATION_VERSION_MAJOR}.${APPLICATION_VERSION_MINOR}" OUTPUT_NAME ${project_BIN} CLEAN_DIRECT_OUTPUT 1)
TARGET_INCLUDE_DIRECTORIES(${project_BIN} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

#INSTALL(TARGETS ${project_BIN} DESTINATION bin)
