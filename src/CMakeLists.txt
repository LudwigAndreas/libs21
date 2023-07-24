FILE (GLOB_RECURSE project_SRCS
    s21_file_map_reader.cc
    s21_to_upper.cc
    s21_to_lower.cc
    s21_split.cc
    FormattingInfo.cc
    PatternParser.cc
    PropertiesReader.cc

    ../include/logger/Logger.h
    ../include/logger/LoggerThreading.h
    ../include/logger/IThreading.h
    ../include/logger/LoggerInitializer.h
    ../include/logger/parse/PatternParser.h
    ../include/logger/parse/LoggingEvent.h
    ../include/logger/parse/PatternLayout.h
    ../include/logger/parse/converters/PatternConverter.h
    ../include/logger/parse/converters/LiteralPatternConverter.h
    ../include/logger/parse/converters/LoggerPatternConverter.h
    ../include/logger/parse/converters/ClassNamePatternConverter.h
    ../include/logger/parse/converters/ColorStartPatternConverter.h
    ../include/logger/parse/converters/ColorEndPatternConverter.h
    ../include/logger/parse/converters/DatePatternConverter.h
    ../include/logger/parse/converters/ShortFileLocationPatternConverter.h
    ../include/logger/parse/converters/FileLocationPatternConverter.h
    ../include/logger/parse/converters/FullLocationPatternConverter.h
    ../include/logger/parse/converters/LineSeparatorPatternConverter.h
    ../include/logger/parse/converters/MethodLocationPatternConverter.h
    ../include/logger/parse/converters/LevelPatternConverter.h
    ../include/logger/parse/converters/RelativeTimePatternConverter.h
    ../include/logger/parse/converters/ThreadPatternConverter.h
    ../include/logger/parse/converters/PropertiesPatternConverter.h
    ../include/logger/parse/converters/LineLocationPatternConverter.h
    ../include/logger/parse/converters/MessagePatternConverter.h
    LineSeparatorPatternConverter.cc
    MethodLocationPatternConverter.cc
    LevelPatternConverter.cc
    RelativeTimePatternConverter.cc
    ThreadPatternConverter.cc
    PropertiesPatternConverter.cc
    LoggingEvent.cc
    LoggerInitializer.cc
    MessagePatternConverter.cc
    PatternConverter.cc
    LiteralPatternConverter.cc
    LoggerPatternConverter.cc
    ClassNamePatternConverter.cc
    ColorStartPatternConverter.cc
    ColorEndPatternConverter.cc
    DatePatternConverter.cc
    ShortFileLocationPatternConverter.cc
    FileLocationPatternConverter.cc
    FullLocationPatternConverter.cc
    LineLocationPatternConverter.cc
    )

INCLUDE_DIRECTORIES(${MAINFOLDER}/include)

SET (project_MOC_HEADERS ../include)
SET (project_LIBS )
SET (project_BIN ${PROJECT_NAME})

ADD_LIBRARY(${project_BIN} STATIC ${project_SRCS})

#ADD_EXECUTABLE(${project_BIN}
#    ${project_SRCS}
#    logger/Logger.h
#    logger/threading/LoggerThreading.h
#    logger/threading/IThreading.h
#    logger/main.cc
#    )

TARGET_LINK_LIBRARIES(${project_BIN} ${project_LIBS})
SET_TARGET_PROPERTIES(${project_BIN} PROPERTIES VERSION "${APPLICATION_VERSION_MAJOR}.${APPLICATION_VERSION_MINOR}" OUTPUT_NAME ${project_BIN} CLEAN_DIRECT_OUTPUT 1)
TARGET_INCLUDE_DIRECTORIES(${project_BIN} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

#INSTALL(TARGETS ${project_BIN} DESTINATION bin)
