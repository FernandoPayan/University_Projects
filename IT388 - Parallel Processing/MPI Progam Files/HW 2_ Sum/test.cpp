
int main(int argc, char* argv[]) {
    int N, n_local, rank, nproc;;


    if (rank == 0)
    {
        // Manager processor scans input and computes n_local
        N = argv[1]; // Reads input (You need to check for errors for HW here. do MPI Abort)
        if (argc == 0)
        {
            printf("Bruh");
        }
        printf("N is: %s\n", argv[1]);
    }
}