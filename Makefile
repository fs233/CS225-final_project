# Executable names:
EXE = final_project
TEST = test

# Add all object files needed for compiling:
EXE_OBJ = main.o
OBJS = graph.o main.o graph_algorithms.o edge.o

# Generated files
CLEAN_RM = images/Out.png

# Use the cs225 makefile template:
include cs225/cs225.mk