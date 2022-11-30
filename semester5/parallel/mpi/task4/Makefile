TARGET = out
SOURCE = main.cpp my_mpi.cpp
PROCS  = 4
NUMS   = 1000


build:
	rm -f $(TARGET)
	mpic++ $(SOURCE) -o $(TARGET) -g3 -ggdb

run:
	mpirun --mca opal_warn_on_missing_libcuda 0 -n $(PROCS) ./$(TARGET) $(NUMS)

