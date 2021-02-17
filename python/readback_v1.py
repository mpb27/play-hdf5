#
# This example creates an HDF5 file compound.h5 and an empty datasets /DSC in it.
#
import h5py
import numpy as np

file = h5py.File('compound.h5', 'r')
dataset = file["DSC"]
print("Reading Orbit and Location fields...")
orbit = dataset['Orbit']
print("Orbit: ", orbit)
location = dataset['Location']
print("Location: ", location)
data = dataset[...]
print("Reading all records:")
print(data)
print("Second element of the third record:", dataset[2, 'Location'])
file.close()

