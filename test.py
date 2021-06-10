from mpi4py import MPI

# mpirun -n 4 python3 test.py

def parallel():
    comm = MPI.COMM_WORLD
    rank = comm.Get_rank()
    size = comm.Get_size()

    print("I am rank", rank, "of", size)


parallel()