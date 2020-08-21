# Gather our source files in this directory.
set(
  calc_src_files
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/EvalVisitor.cpp"
)

# Build our executable from the source files.
add_executable(calc ${calc_src_files})
target_include_directories(calc PUBLIC ${ANTLR_GEN_DIR})

# Ensure that the antlr4-runtime is available.
add_dependencies(calc antlr)

# Add the antlr runtime and parser as libraries to link.
target_link_libraries(calc parser antlr4-runtime)

# Symbolic link our executable to the base directory so we don't have to go searching for it.
symlink_to_bin("calc")
