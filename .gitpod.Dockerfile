FROM gitpod/workspace-full

RUN sudo apt-get update && \
    sudo apt-get install -y hdf5-tools && \
    sudo rm -rf /var/lib/apt/lists/*

RUN pip install h5py pytest numpy

RUN brew install conan
