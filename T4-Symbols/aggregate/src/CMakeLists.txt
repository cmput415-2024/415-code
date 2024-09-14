# Gather our source files in this directory.
set(
  aggregate_src_files
    "${CMAKE_CURRENT_SOURCE_DIR}/AST.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/ASTBuilder.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/BaseScope.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/DefRef.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/MethodSymbol.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/StructSymbol.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/ScopedSymbol.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/SymbolTable.cpp"
)

# Build our executable from the source files.
add_executable(aggregate ${aggregate_src_files})
target_include_directories(aggregate PUBLIC ${ANTLR_GEN_DIR})

# Ensure that the antlr4-runtime is available.
add_dependencies(aggregate antlr)

# Add the antlr runtime and parser as libraries to link.
target_link_libraries(aggregate parser antlr4-runtime)

# Symbolic link our executable to the base directory so we don't have to go searching for it.
symlink_to_bin("aggregate")
