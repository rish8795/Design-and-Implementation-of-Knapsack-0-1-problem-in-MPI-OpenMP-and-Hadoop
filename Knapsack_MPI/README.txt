
**** README for running MPI version on Linux ****


1. Compile the MPI program using: 
	$ mpicc knapsack_mpi.c -o knapsack_mpi

2. Run the object file by giving parameters 
	$  mpiexec -n <number of node> ./knapsack_mpi <max capacity weight> <number of items> <seed>



**************************************************************
