#include "mpi.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

void myMPI_Reduce(void*, void*, int, MPI_Datatype, MPI_Op, int, MPI_Comm);
void Sum(void* sendbuf, void* recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int target, MPI_Comm comm, int myRank);
void Prod(void* sendbuf, void* recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int target, MPI_Comm comm, int myRank);
void Max(void* sendbuf, void* recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int target, MPI_Comm comm, int myRank);
void Min(void* sendbuf, void* recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int target, MPI_Comm comm, int myRank);

int main(int argc, char* argv[]) {
	int myRank;
	int size;
	int local_value;
	int return_value = -1;

	/* initialize MPI */
	MPI_Init(&argc, &argv);
	/* get my rank and the size of the communicator */
	MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	// each processor data has its own rank
	local_value = myRank;
	MPI_Barrier(MPI_COMM_WORLD);


	//Test

	myMPI_Reduce(&local_value, &return_value, 1, MPI_INT, MPI_SUM, 1, MPI_COMM_WORLD);
	if (myRank == 1) 	cout << "my_MPI_Reduce SUM : " << return_value << endl;
	
	myMPI_Reduce(&local_value, &return_value, 1, MPI_INT, MPI_PROD, 1, MPI_COMM_WORLD);
	if (myRank == 1) 	cout << "my_MPI_Reduce PROD : " << return_value << endl;
	
	myMPI_Reduce(&local_value, &return_value, 1, MPI_INT, MPI_MAX, 1, MPI_COMM_WORLD);
	if (myRank == 1) 	cout << "my_MPI_Reduce MAX : " << return_value << endl;
	
	myMPI_Reduce(&local_value, &return_value, 1, MPI_INT, MPI_MIN, 1, MPI_COMM_WORLD);
	if (myRank == 1) 	cout << "myMPI_Reduce MIN : " << return_value << endl << endl;
	


	MPI_Reduce(&local_value, &return_value, 1, MPI_INT, MPI_SUM, 1, MPI_COMM_WORLD);
	if (myRank == 1) 	cout << "MPI_Reduce SUM : " << return_value << endl;

	MPI_Reduce(&local_value, &return_value, 1, MPI_INT, MPI_PROD, 1, MPI_COMM_WORLD);
	if (myRank == 1) 	cout << "MPI_Reduce SUM : " << return_value << endl;

	MPI_Reduce(&local_value, &return_value, 1, MPI_INT, MPI_MAX, 1, MPI_COMM_WORLD);
	if (myRank == 1)	cout << "MPI_Reduce SUM : " << return_value << endl;

	MPI_Reduce(&local_value, &return_value, 1, MPI_INT, MPI_MIN, 1, MPI_COMM_WORLD);
	if (myRank == 1) 	cout << "MPI_Reduce SUM : " << return_value << endl;

	

	MPI_Finalize();
	return 0;
}


void myMPI_Reduce(void* sendbuf, void* recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int target, MPI_Comm comm) {
	int myRank;
	MPI_Comm_rank(MPI_COMM_WORLD, &myRank);

	if (op == MPI_SUM) {
		Sum(sendbuf, recvbuf, count,  datatype,  op,  target,  comm,  myRank);
	}
	else if (op == MPI_PROD) {
		Prod(sendbuf, recvbuf, count, datatype, op, target, comm, myRank);
	}
	else if (op == MPI_MAX) {
		Max(sendbuf, recvbuf, count, datatype, op, target, comm, myRank);
	}
	else if (op == MPI_MIN) {
		Min(sendbuf, recvbuf, count, datatype, op, target, comm, myRank);
	}


	if (myRank == 0) {
		MPI_Send(sendbuf, count, datatype, 1, 0, comm);
	}
	else if (myRank == 2) {
		MPI_Send(sendbuf, count, datatype, 1, 2, comm);
	}
	else if (myRank == 5) {
		MPI_Send(sendbuf, count, datatype, 1, 5, comm);
	}

	else if (myRank == 3) {
		MPI_Send(sendbuf, count, datatype, 7, 3, comm);
	}
	else if (myRank == 6) {
		MPI_Send(sendbuf, count, datatype, 7, 6, comm);
	}
	else if (myRank == 11) {
		MPI_Send(sendbuf, count, datatype, 7, 11, comm);
	}

	else if (myRank == 4) {
		MPI_Send(sendbuf, count, datatype, 8, 4, comm);
	}
	else if (myRank == 9) {
		MPI_Send(sendbuf, count, datatype, 8, 9, comm);
	}
	else if (myRank == 12) {
		MPI_Send(sendbuf, count, datatype, 8, 12, comm);
	}

	else if (myRank == 10) {
		MPI_Send(sendbuf, count, datatype, 14, 10, comm);
	}
	else if (myRank == 13) {
		MPI_Send(sendbuf, count, datatype, 14, 13, comm);
	}
	else if (myRank == 15) {
		MPI_Send(sendbuf, count, datatype, 14, 15, comm);
	}


}

void Sum(void* sendbuf, void* recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int target, MPI_Comm comm, int myRank) {
	if (myRank == 1) {
		int local_value = *(int*)sendbuf;
		for (int i : {0, 2, 5}) {
			MPI_Recv(recvbuf, count, datatype, i, i, comm, MPI_STATUS_IGNORE);
			local_value += *(int*)recvbuf;
		}
		for (int i : {7, 8, 14}) {
			MPI_Recv(recvbuf, count, datatype, i, i, comm, MPI_STATUS_IGNORE);
			local_value += *(int*)recvbuf;
		}
		*(int*)recvbuf = local_value;
	}
	else if (myRank == 7) {
		int local_value = *(int*)sendbuf;
		for (int i : {3, 6, 11}) {
			MPI_Recv(recvbuf, count, datatype, i, i, comm, MPI_STATUS_IGNORE);
			local_value += *(int*)recvbuf;
		}
		MPI_Send(&local_value, count, datatype, 1, 7, comm);

	}
	else if (myRank == 8) {
		int local_value = *(int*)sendbuf;
		for (int i : {4, 9, 12}) {
			MPI_Recv(recvbuf, count, datatype, i, i, comm, MPI_STATUS_IGNORE);
			local_value += *(int*)recvbuf;
		}
		MPI_Send(&local_value, count, datatype, 1, 8, comm);
	}
	else if (myRank == 14) {
		int local_value = *(int*)sendbuf;
		for (int i : {10, 13, 15}) {
			MPI_Recv(recvbuf, count, datatype, i, i, comm, MPI_STATUS_IGNORE);
			local_value += *(int*)recvbuf;
		}
		MPI_Send(&local_value, count, datatype, 1, 14, comm);
	}
}

void Prod(void* sendbuf, void* recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int target, MPI_Comm comm, int myRank) {
	if (myRank == 1) {
		int local_value = *(int*)sendbuf;
		for (int i : {0, 2, 5}) {
			MPI_Recv(recvbuf, count, datatype, i, i, comm, MPI_STATUS_IGNORE);
			local_value *= *(int*)recvbuf;
		}
		for (int i : {7, 8, 14}) {
			MPI_Recv(recvbuf, count, datatype, i, i, comm, MPI_STATUS_IGNORE);
			local_value *= *(int*)recvbuf;
		}
		*(int*)recvbuf = local_value;
	}
	else if (myRank == 7) {
		int local_value = *(int*)sendbuf;
		for (int i : {3, 6, 11}) {
			MPI_Recv(recvbuf, count, datatype, i, i, comm, MPI_STATUS_IGNORE);
			local_value *= *(int*)recvbuf;
		}
		MPI_Send(&local_value, count, datatype, 1, 7, comm);

	}
	else if (myRank == 8) {
		int local_value = *(int*)sendbuf;
		for (int i : {4, 9, 12}) {
			MPI_Recv(recvbuf, count, datatype, i, i, comm, MPI_STATUS_IGNORE);
			local_value *= *(int*)recvbuf;
		}
		MPI_Send(&local_value, count, datatype, 1, 8, comm);
	}
	else if (myRank == 14) {
		int local_value = *(int*)sendbuf;
		for (int i : {10, 13, 15}) {
			MPI_Recv(recvbuf, count, datatype, i, i, comm, MPI_STATUS_IGNORE);
			local_value *= *(int*)recvbuf;
		}
		MPI_Send(&local_value, count, datatype, 1, 14, comm);
	}
}

void Max(void* sendbuf, void* recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int target, MPI_Comm comm, int myRank) {
	if (myRank == 1) {
		int local_value = *(int*)sendbuf;
		for (int i : {0, 2, 5}) {
			MPI_Recv(recvbuf, count, datatype, i, i, comm, MPI_STATUS_IGNORE);
			if (local_value < *(int*)recvbuf) {
				local_value = *(int*)recvbuf;
			}
		}
		for (int i : {7, 8, 14}) {
			MPI_Recv(recvbuf, count, datatype, i, i, comm, MPI_STATUS_IGNORE);
			if (local_value < *(int*)recvbuf) {
				local_value = *(int*)recvbuf;
			}
		}
		*(int*)recvbuf = local_value;
	}
	else if (myRank == 7) {
		int local_value = *(int*)sendbuf;
		for (int i : {3, 6, 11}) {
			MPI_Recv(recvbuf, count, datatype, i, i, comm, MPI_STATUS_IGNORE);
			if (local_value < *(int*)recvbuf) {
				local_value = *(int*)recvbuf;
			}
		}
		MPI_Send(&local_value, count, datatype, 1, 7, comm);

	}
	else if (myRank == 8) {
		int local_value = *(int*)sendbuf;
		for (int i : {4, 9, 12}) {
			MPI_Recv(recvbuf, count, datatype, i, i, comm, MPI_STATUS_IGNORE);
			if (local_value < *(int*)recvbuf) {
				local_value = *(int*)recvbuf;
			}
		}
		MPI_Send(&local_value, count, datatype, 1, 8, comm);
	}
	else if (myRank == 14) {
		int local_value = *(int*)sendbuf;
		for (int i : {10, 13, 15}) {
			MPI_Recv(recvbuf, count, datatype, i, i, comm, MPI_STATUS_IGNORE);
			if (local_value < *(int*)recvbuf) {
				local_value = *(int*)recvbuf;
			}
		}
		MPI_Send(&local_value, count, datatype, 1, 14, comm);
	}
}

void Min(void* sendbuf, void* recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int target, MPI_Comm comm, int myRank) {
	if (myRank == 1) {
		int local_value = *(int*)sendbuf;
		for (int i : {0, 2, 5}) {
			MPI_Recv(recvbuf, count, datatype, i, i, comm, MPI_STATUS_IGNORE);
			if (local_value > *(int*)recvbuf) {
				local_value = *(int*)recvbuf;
			}
		}
		for (int i : {7, 8, 14}) {
			MPI_Recv(recvbuf, count, datatype, i, i, comm, MPI_STATUS_IGNORE);
			if (local_value > *(int*)recvbuf) {
				local_value = *(int*)recvbuf;
			}
		}
		*(int*)recvbuf = local_value;
	}
	else if (myRank == 7) {
		int local_value = *(int*)sendbuf;
		for (int i : {3, 6, 11}) {
			MPI_Recv(recvbuf, count, datatype, i, i, comm, MPI_STATUS_IGNORE);
			if (local_value > *(int*)recvbuf) {
				local_value = *(int*)recvbuf;
			}
		}
		MPI_Send(&local_value, count, datatype, 1, 7, comm);

	}
	else if (myRank == 8) {
		int local_value = *(int*)sendbuf;
		for (int i : {4, 9, 12}) {
			MPI_Recv(recvbuf, count, datatype, i, i, comm, MPI_STATUS_IGNORE);
			if (local_value > *(int*)recvbuf) {
				local_value = *(int*)recvbuf;
			}
		}
		MPI_Send(&local_value, count, datatype, 1, 8, comm);
	}
	else if (myRank == 14) {
		int local_value = *(int*)sendbuf;
		for (int i : {10, 13, 15}) {
			MPI_Recv(recvbuf, count, datatype, i, i, comm, MPI_STATUS_IGNORE);
			if (local_value > *(int*)recvbuf) {
				local_value = *(int*)recvbuf;
			}
		}
		MPI_Send(&local_value, count, datatype, 1, 14, comm);
	}
}
