# Nested

A translation of the symbol table for nested scopes from T4-Symbols.pptx to C++ and ANTLR4, in the assignment format.

# Usage
## Building
### Linux
  1. Install git, java (only the runtime is necessary), and cmake (>= v3.0).
     - Until now, cmake has found the dependencies without issues. If you
       encounter an issue, let Braedy know and we can fix it.
  1. Make a directory that you intend to build the project in and change into
     that directory.
  1. Run `cmake <path-to-project>`.
  1. Run `make`.
  1. Done.

## Running

After building, use the resulting binary in the `bin/` folder to run the examples.
Examples:
```
bin/nested t.cymbol
bin/nested t2.cymbol
```

