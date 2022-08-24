# DIRS: Directories we need to build.
DIRS:=$(wildcard */*/)

# CMAKE: cmake command or executable
CMAKE:=cmake

.PHONY: all clean

# build all examples
all:
	$(foreach dir, $(DIRS), $(CMAKE) -S $(dir) -B $(dir)/build;)
	$(foreach dir, $(DIRS), $(MAKE) -C $(dir)/build;)

clean:
	$(foreach dir, $(DIRS), rm -rf $(dir)/build;)
	$(foreach dir, $(DIRS), rm -rf $(dir)/gen;)
	$(foreach dir, $(DIRS), rm -rf $(dir)/bin;)