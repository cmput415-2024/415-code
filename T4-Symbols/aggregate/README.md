# Aggregate

A translation of the symbol table for aggregate symbols from T4-Symbols.pptx to C++ and ANTLR4, in the assignment format.

# Usage
## Building
### Linux
  1. Install git, java (only the runtime is necessary), and cmake (>= v3.0).
     - Until now, cmake has found the dependencies without issues. If you
       encounter an issue, let Braedy know and we can fix it.
  2. Make a directory that you intend to build the project in and change into
     that directory.
  3. Run `cmake <path-to-project>`.
  4. Run `make`.
  5. Done.

## Running

After building, use the resulting binary in the `bin/` folder to run the examples.
Examples:
```
bin/aggregate t.cymbol
bin/aggregate t2.cymbol
```

