#include <vector>
#include <h5pp/h5pp.h>

struct ParticleV0 {
    double x = 0, y = 0, z = 0;
};

struct ParticleV1 {
    double x = 0, y = 0, z = 0, a = 0;
};

struct ParticleV2 {
    double x = 0, y = 0, z = 0, a = 0, b = 0;
};


void create_v1_file() {
    h5pp::File file("exampledir/particles_v1.h5", h5pp::FilePermission::REPLACE, 0);

    h5pp::hid::h5t H5_PARTICLE_V1 = H5Tcreate(H5T_COMPOUND, sizeof(ParticleV1));
    H5Tinsert(H5_PARTICLE_V1, "x", HOFFSET(ParticleV1, x), H5T_NATIVE_DOUBLE);
    H5Tinsert(H5_PARTICLE_V1, "y", HOFFSET(ParticleV1, y), H5T_NATIVE_DOUBLE);
    H5Tinsert(H5_PARTICLE_V1, "z", HOFFSET(ParticleV1, z), H5T_NATIVE_DOUBLE);
    H5Tinsert(H5_PARTICLE_V1, "a", HOFFSET(ParticleV1, a), H5T_NATIVE_DOUBLE);

    std::vector<ParticleV1> particles;
    for (double i = 0.0; i < 10; i += 1.0)
        particles.push_back({100+i, 200+i, 300+i, 400+i});

    file.writeDataset(particles, "particles", H5_PARTICLE_V1);
}

void read_v1_as_v0() {
    h5pp::File file("exampledir/particles_v1.h5", h5pp::FilePermission::READONLY, 0);

    h5pp::hid::h5t H5_PARTICLE_V0 = H5Tcreate(H5T_COMPOUND, sizeof(ParticleV0));
    H5Tinsert(H5_PARTICLE_V0, "x", HOFFSET(ParticleV0, x), H5T_NATIVE_DOUBLE);
    H5Tinsert(H5_PARTICLE_V0, "y", HOFFSET(ParticleV0, y), H5T_NATIVE_DOUBLE);
    H5Tinsert(H5_PARTICLE_V0, "z", HOFFSET(ParticleV0, z), H5T_NATIVE_DOUBLE);

    std::vector<ParticleV0> particles;

    // V0 Read.
    {    
        h5pp::Options options;
        options.linkPath = "particles";
        auto dsetInfo = file.getDatasetInfo("particles");
        dsetInfo.h5Type = H5_PARTICLE_V0;    
        file.readDataset(particles, dsetInfo, options);
    }

    h5pp::print("Read as V0: \n");
    for(auto &&p : particles) h5pp::print("x:{:.3f} y:{:.3f} z:{:.3f} \n",p.x,p.y,p.z);
}

void read_v1_as_v1() {
    h5pp::File file("exampledir/particles_v1.h5", h5pp::FilePermission::READONLY, 0);

    h5pp::hid::h5t H5_PARTICLE_V1 = H5Tcreate(H5T_COMPOUND, sizeof(ParticleV1));
    H5Tinsert(H5_PARTICLE_V1, "x", HOFFSET(ParticleV1, x), H5T_NATIVE_DOUBLE);
    H5Tinsert(H5_PARTICLE_V1, "y", HOFFSET(ParticleV1, y), H5T_NATIVE_DOUBLE);
    H5Tinsert(H5_PARTICLE_V1, "z", HOFFSET(ParticleV1, z), H5T_NATIVE_DOUBLE);
    H5Tinsert(H5_PARTICLE_V1, "a", HOFFSET(ParticleV1, a), H5T_NATIVE_DOUBLE);

    std::vector<ParticleV1> particles;

    // V1 Read.
    {    
        h5pp::Options options;
        options.linkPath = "particles";
        auto dsetInfo = file.getDatasetInfo("particles");
        dsetInfo.h5Type = H5_PARTICLE_V1;    
        file.readDataset(particles, dsetInfo, options);
    }

    h5pp::print("Read as V1: \n");
    for(auto &&p : particles) h5pp::print("x:{:.3f} y:{:.3f} z:{:.3f} a:{:.3f} \n",p.x,p.y,p.z,p.a);
}

void read_v1_as_v2() {
    h5pp::File file("exampledir/particles_v1.h5", h5pp::FilePermission::READONLY, 0);

    h5pp::hid::h5t H5_PARTICLE_V2 = H5Tcreate(H5T_COMPOUND, sizeof(ParticleV2));
    H5Tinsert(H5_PARTICLE_V2, "x", HOFFSET(ParticleV2, x), H5T_NATIVE_DOUBLE);
    H5Tinsert(H5_PARTICLE_V2, "y", HOFFSET(ParticleV2, y), H5T_NATIVE_DOUBLE);
    H5Tinsert(H5_PARTICLE_V2, "z", HOFFSET(ParticleV2, z), H5T_NATIVE_DOUBLE);
    H5Tinsert(H5_PARTICLE_V2, "a", HOFFSET(ParticleV2, a), H5T_NATIVE_DOUBLE);
    H5Tinsert(H5_PARTICLE_V2, "b", HOFFSET(ParticleV2, b), H5T_NATIVE_DOUBLE);

    std::vector<ParticleV2> particles;

    // V2 Read.
    {    
        h5pp::Options options;
        options.linkPath = "particles";
        auto dsetInfo = file.getDatasetInfo("particles");
        dsetInfo.h5Type = H5_PARTICLE_V2;    
        file.readDataset(particles, dsetInfo, options);
    }

    h5pp::print("Read as V2: \n");
    for(auto &&p : particles) h5pp::print("x:{:.3f} y:{:.3f} z:{:.3f} a:{:.3f} b:{:.3f}\n",p.x,p.y,p.z,p.a,p.b);
}

int main() {

    // Initialize a file
    create_v1_file();

    // Readback in V0.
    //   - V1 file is backwards compatible with V0 program, V0 program ignores A member.
    read_v1_as_v0();

    // Readback in V1.
    //   - V1 file and V1 program are compatible.
    read_v1_as_v1();

    // Readback in V2.
    //   - V1 file does not have B member so V2 program has default initialized b (0.0).
    read_v1_as_v2();

    return 0;
}
