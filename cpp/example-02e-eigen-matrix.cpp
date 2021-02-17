#include <h5pp/h5pp.h>
#include <iostream>
#include <fmt/format.h>

int main(int argc, char** argv) {
    
    int N = 5;
    int M = 5;
    if (argc >= 3) {
        N = atoi(argv[1]);
        M = atoi(argv[2]);
    }

    int L = 1;
    if (argc == 4) {
        L = atoi(argv[3]);
    }

    // Initialize a file
    h5pp::File file("exampledir/example-02e-eigen.h5", h5pp::FilePermission::REPLACE, 0);

#ifdef H5PP_EIGEN3
    // Initialize a 10x10 Eigen matrix with random complex entries
    Eigen::MatrixXcd m1 = Eigen::MatrixXcd::Random(N, M);

    // Write the matrix
    // Inside the file, the data will be stored in a dataset named "myEigenMatrix" under the group "myMatrixCollection"
    for (int i = 0; i < L; i++)
    {
        file.writeDataset(m1, fmt::format("myGroup/myEigenMatrix{:08}",i), H5D_CONTIGUOUS);
    }

    // Read it back in one line. Note that we pass the type as a template parameter
    auto m2 = file.readDataset<Eigen::MatrixXcd>("myGroup/myEigenMatrix00000000");
    
    std::cout << m2.block(0,0,5,5) << std::endl;
#endif
    return 0;
}
