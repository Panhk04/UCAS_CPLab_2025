add_library(IRCodeGen)
add_library(ASTtoIRVisitor)

target_sources(
    ircodegen PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/IRCodeGenerator.h
                    ${CMAKE_CURRENT_SOURCE_DIR}/IRCodeGenerator.cpp)

target_sources(
    ASTtoIRVisitor PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/ASTtoIRVisitor.h
                            ${CMAKE_CURRENT_SOURCE_DIR}/ASTtoIRVisitor.cpp)

target_include_directories(ASTtoIRVisitor PUBLIC ${PROJECT_SOURCE_DIR}/grammar)
target_include_directories(IRCodeGen PUBLIC ${PROJECT_SOURCE_DIR}/grammar)
