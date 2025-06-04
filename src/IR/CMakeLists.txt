add_library(IRCodeGen)

target_sources(
    ircodegen PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/IRCodeGenerator.h
                    ${CMAKE_CURRENT_SOURCE_DIR}/IRCodeGenerator.cpp)