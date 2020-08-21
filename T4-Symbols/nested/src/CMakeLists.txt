# Gather our source files in this directory.
set(
  nested_src_files
    "${CMAKE_CURRENT_SOURCE_DIR}/AST.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/ASTBuilder.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/BaseScope.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/BuiltInTypeSymbol.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/DefRef.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/GlobalScope.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/LocalScope.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/MethodSymbol.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Scope.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Symbol.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/SymbolTable.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Type.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/VariableSymbol.cpp"
)

# Build our executable from the source files.
add_executable(nested ${nested_src_files})
target_include_directories(nested PUBLIC ${ANTLR_GEN_DIR})

# Ensure that the antlr4-runtime is available.
add_dependencies(nested antlr)

# Add the antlr runtime and parser as libraries to link.
target_link_libraries(nested parser antlr4-runtime)

# Symbolic link our executable to the base directory so we don't have to go searching for it.
symlink_to_bin("nested")
