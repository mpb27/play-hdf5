#include <h5pp/h5pp.h>

int main() {
    // Initialize a file
    h5pp::File file("exampledir/example-01a-int.h5", h5pp::FilePermission::REPLACE);

    int writeInt = 42;                          // Initialize an int
    file.writeDataset(writeInt, "integerData"); // Write data to file in dataset named "integerData"

    int readInt;                              // Allocate for a new int
    file.readDataset(readInt, "integerData"); // Read data

    // Or, read by assignment
    auto readInt_alt = file.readDataset<int>("integerData");

    h5pp::print("Wrote dataset: {}\n", writeInt);
    h5pp::print("Read  dataset: {} | alt: {}\n", readInt, readInt_alt);
    return 0;
}
