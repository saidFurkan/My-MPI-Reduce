# Reimplementation of MPI_Reduce

This specific Reduce function has two stages, and at each stage a specific
communication pattern is used.
1. Four processes receive messages from their neighbors. Those four
processes apply the defined operation on four pieces of data.
2. Three of those four processes send their partial result to the
fourth one (destination process). Finally, the destination process
applies the defined operation on four pieces of data to get the
final result (Reduction).

![mpi_reduce](https://user-images.githubusercontent.com/37874147/81065845-e7bf8f00-8ee4-11ea-8938-aee2dca9b595.png)


## Test Procedure
------------------------------------------------------------------------
Each process is tested both with the function I wrote and with MPI's own function, the results are printed on the screen.

output :

mpiexec -n 16 Mpi.exe

my_MPI_Reduce SUM : 120
my_MPI_Reduce PROD : 0
my_MPI_Reduce MAX : 15
myMPI_Reduce MIN : 0
MPI_Reduce SUM : 120
MPI_Reduce SUM : 0
MPI_Reduce SUM : 15
MPI_Reduce SUM : 0

------------------------------------------------------------------------

## Design Choices
------------------------------------------------------------------------
It is designed to work with 16 processors. All processors are divided into 4 groups.
4 tasks have been defined. Sum, Prod, Max, Min.
Each group communicates with MPI_Send and MPI_Recv among themselves. Each group completes its assigned task.
The leader of each group sends its results to the leader of all processors.
Here, processor 1, the leader of all processors, was chosen.
After all operations are completed, the results are printed to the console by the 1st processor.

Code was tested in Windows 32bit arthitecture.

------------------------------------------------------------------------

## How to Run:
------------------------------------------------------------------------
Download MS-MPI SDK and Redist installers and install them.
Setup property of Visual Studio
Additional Include directories 	: $(MSMPI_INC);$(MSMPI_INC)\x86
Additional dependencies 	: add msmpi.lib
Additional Library Directories 	: $(MSMPI_LIB32)
Build project in Visual Studio
Run from the console with "mpiexec -n 16 Mpi.exe" command.
