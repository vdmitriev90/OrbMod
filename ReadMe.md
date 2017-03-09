# Brief description


OrbMod (Orbit Modeling ) - tools for numerical modeling of orbits. Orbit propagation and fitting to observations. Orbit modeling is implemented  within the perturbed  two-body problem, in Cartesian, Kustaanheimo-Stiefel (KS) and Sperling-Burdet (SB) variables. The flexible set of perturbations can be used:
 1. central body gravity as point mass
 2. central body gravity in spherical harmonics expansion
 3. third bodies gravity as point mass 
 4. spherical harmonics expansion of one of third bodies gravity field
 5. General relativity effects
 6. solar radiation pressure whithin 'cannon ball' model
 7. athmospheric drag whithin 'cannon ball' model
 
 
In this software, [SPICE](https://naif.jpl.nasa.gov/naif/)  routines and kernels are used for coorinate frames and time scales transformation, ephemeris computation. 

The graphic user interface (written on C#) for this software is available here: https://github.com/vdmitriev90/OrbMod_DotNET_UI 

Pre-build binaries for OrbMod as well as for UI, auxiliary libraris, all required SPICE kernels and input files are available here: https://github.com/vdmitriev90/OrbMod_bin
