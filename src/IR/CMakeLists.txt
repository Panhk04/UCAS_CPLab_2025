add_library(IRCodeGen)
add_library(ASTtoIRVisitor)

target_sources(
    ircodegen PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/IRCodeGenerator.h
                    ${CMAKE_CURRENT_SOURCE_DIR}/IRCodeGenerator.cpp)

target_sources(
    ASTtoIRVisitor PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/ASTtoIRVisitor.h
                            ${CMAKE_CURRENT_SOURCE_DIR}/ASTtoIRVisitor.cpp)

# Add all IR source files to a common IR library
add_library(IR 
    IRConstant.cpp
    IRValue.cpp
    IRModule.cpp
    IRInstruction.cpp
    IRType.cpp
    IRGlobalVariable.cpp
    IRFunction.cpp
    IRUser.cpp
    IRGlobalValue.cpp
    IRUse.cpp
    IRArgument.cpp
    IRDerivedTypes.cpp
)

target_include_directories(ASTtoIRVisitor PUBLIC ${PROJECT_SOURCE_DIR}/grammar)
target_include_directories(IRCodeGen PUBLIC ${PROJECT_SOURCE_DIR}/grammar)
target_include_directories(IR PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
