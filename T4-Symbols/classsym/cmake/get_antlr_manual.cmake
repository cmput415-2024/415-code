# Another method to obtain the ANTLR C++ runtime. This will clone the github repository for ANTLR
# and build its own copy of the runtime to use (roughly .5-.75GB extra space). Completely swappable
# with finding your person install of ANTLR.

# CMake module that downloads the antlr source and builds the C++ runtime required when linking
# a generated lexer/parser. Creates the variable ANTLR_INCLUDE_DIRS to add to your target's
# include directories, adds the antlr library path to the project, allows your target to link
# against antlr4-runtime, creates ANTLR_JAR for generating grammars, and creates an antlr target
# that you can add via add_dependencies to make sure everything has happened already.

# Set the directory for binaries.
file(TO_CMAKE_PATH "${CMAKE_BINARY_DIR}/bin" BIN_DIR) # Join dir.
set(BIN_DIR ${BIN_DIR} CACHE PATH "ANTLR jar directory.") # Set for internal use.

# Download ANTLR executable, saves us from ensuring people have java build tools (e.g. Maven)...
file(TO_CMAKE_PATH "${BIN_DIR}/antlr.jar" ANTLR_JAR)
if (NOT EXISTS "${ANTLR_JAR}")
  message(STATUS "Downloading ANTLR generator...")
  file(
    DOWNLOAD
    http://www.antlr.org/download/antlr-4.7.1-complete.jar
    "${ANTLR_JAR}"
    SHOW_PROGRESS
  )
  file(TO_NATIVE_PATH "${BIN_DIR}" BIN_DIR_NATIVE) # Transform for display.
  message(STATUS "Downloaded ANTLR jar destination: ${BIN_DIR_NATIVE}")
endif()

# Download ANTLR source to get the runtime...
# Turn on logging as necessary.
ExternalProject_Add(
  antlr

  # Set up custom paths.
  PREFIX "${CMAKE_BINARY_DIR}"
  TMP_DIR "${CMAKE_BINARY_DIR}/antlr-tmp"
  STAMP_DIR "${CMAKE_BINARY_DIR}/antlr-stamp"
  DOWNLOAD_DIR "${CMAKE_BINARY_DIR}"
  SOURCE_DIR "${CMAKE_BINARY_DIR}/antlr"
  BINARY_DIR "${CMAKE_BINARY_DIR}/antlr-build"
  INSTALL_DIR "${CMAKE_BINARY_DIR}/antlr-install"

  # ANTLR repository and tag.
  GIT_REPOSITORY https://github.com/antlr/antlr4.git
  GIT_TAG "4.10.1"
  UPDATE_COMMAND ""
  PATCH_COMMAND ""
  TIMEOUT 10
  #LOG_DOWNLOAD ON

  # Modify the configure command to always build release mode, both shared and static libs, notify
  # of jar location, and then set custom paths for the build and install.
  CONFIGURE_COMMAND
  ${CMAKE_COMMAND}
  -DCMAKE_BUILD_TYPE=Release
  -DBUILD_SHARED_LIBS=ON -BUILD_TESTS=OFF
  -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
  <SOURCE_DIR>/runtime/Cpp
  #LOG_CONFIGURE ON

  # No need to edit the build command, the autogenerated one works perfectly.
  #LOG_BUILD ON

  # No need to edit the install command, the autogenerated one works perfectly.
  #LOG_INSTALL ON
)

# Grab the install directory so we can get the include directories and built libs.
ExternalProject_Get_Property(antlr INSTALL_DIR)

# Create includes paths.
list(APPEND ANTLR_INCLUDE_DIRS ${INSTALL_DIR}/include/antlr4-runtime)
foreach(src_path misc atn dfa tree support)
  list(APPEND ANTLR_INCLUDE_DIRS ${INSTALL_DIR}/include/antlr4-runtime/${src_path})
endforeach(src_path)

# Create libs path and then add it to the linker paths.
set(_ANTLR_LIB_DIRS "${INSTALL_DIR}/lib")
link_directories("${_ANTLR_LIB_DIRS}")
