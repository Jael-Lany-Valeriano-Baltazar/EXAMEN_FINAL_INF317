#include <stdio.h>
#include <stdlib.h>
#include </usr/lib/x86_64-linux-gnu/openmpi/include/mpi.h>
#include <math.h>

double calcular_termino(int i) {
    double termino = 1.0 / pow(16, i) * (4.0 / (8 * i + 1) - 2.0 / (8 * i + 4) - 1.0 / (8 * i + 5) - 1.0 / (8 * i + 6));
    return termino;
}

double calcular_pi(int num_terminos, int rank, int size) {
    double pi_local = 0.0;
    for (int i = rank; i < num_terminos; i += size) {
        double termino = calcular_termino(i);
        pi_local += termino;
    }

    double pi_global = 0.0;
    MPI_Reduce(&pi_local, &pi_global, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    return pi_global;
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int num_terminos = 1000;
    double pi = calcular_pi(num_terminos, rank, size);

    if (rank == 0) {
        printf("Valor de Pi calculado: %.15f\n", pi);
    }

    MPI_Finalize();
    return 0;
}
