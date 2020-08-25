# Col

A translation of the Col.java application from T3-ActionsPredicatesModes.pptx to C++ and the assignment format.

Authors: Braedy Kuzma (braedy@ualberta.ca), Deric Cheung (dacheung@ualberta.ca)

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

After building, use one of the following commands to run the example.
```
./bin/col t.rows 1
./bin/col t.rows 2
./bin/col t.rows 3
```
