## OrbMod Software
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

There is a GUI (C#) for this software.

Pre-build binaries for OrbMod as well as for UI, auxiliary libraris, all required SPICE kernels and input files are available here: https://github.com/vdmitriev90/OrbMod_bin

## Main menu

Here you able to specify:

1. central body
2. processing mode (orbit propagation or fitting orbit to observations)
3. Variables
4. intial conditions, its type, coordinates and time frame
5. integraion setting (step, order, tolerance and so on)

![](https://github.com/vdmitriev90/OrbMod_DotNET_UI/blob/master/MainWindow.png )

## Force model menu
Here you able to specify the set of perturbation forces:

1. Non-central part of central body's gravitation (via spherical harmonics approach). NB: tidal perturbations currently is disable .
2. big planets + Pluto as point masses
3. 5 additional bodies, whith IDs according to SPICE nomenclature (example: 3==Earth-Moon baricenter, 301== Moon, 499 == Mars, etc.)
3. Non-central part  of additional body #5  attraction (via spherical harmonics approach)
4. General relativity effects
5. Solar radiation pressure whithin 'cannon ball' model
5. athmospheric drag whithin 'cannon ball' model

![](https://github.com/vdmitriev90/OrbMod_DotNET_UI/blob/master/ForceModel.png)

## Process settings menu
Here you can manage the parameters of fitting orbit to observations:

1. Orbit fiting mode

 1. (LS) - Ordinary batch least squares adjustment. It means, that full set of observations will process in each iteration
 1. (batch_LS_filer) - adjustment orbit to observations using  sequential least squares flter. Please, see [here](https://www.researchgate.net/publication/310503329_Application_of_recursive_approaches_to_differential_orbit_correction_of_near_Earth_asteroids) for detaials.
 1. (pure_Kalman) - Extended Kalman filter(EKF) for detains see (O. Montenbruckand, E. Gil  - 2000)
 1. (hybrid_Kalman) - Software will try to estimate state vector and covariance using few first epochs via batch least squares, after that standart EKF algorithm will be used.

2. Outliers rejection - rejection epoch with bad observations
3. Settings of sequential least squares flter
4. Settings of EKF

 
 ![](https://github.com/vdmitriev90/OrbMod_DotNET_UI/blob/master/Process%20settings.png)
 
 
## Output settings menu
Here you able to specify the data whichkind of data wil be store in files during processing, and rate of output streams

![](https://github.com/vdmitriev90/OrbMod_DotNET_UI/blob/master/Output%20settings.png)

## Tools menus


![](https://github.com/vdmitriev90/OrbMod_DotNET_UI/blob/master/Tools.png)

Here you able to:
### Load observation
Load astrometric observation  from text file (in MPC format) to intrnal storage (item "Load observations")


### Observations view  
View and manage amount of observations to be proceesed. You can change time frames  and include/exclude all observation from specific observatory.
On pictuer below are shown example for obsevations of Apophis asteroid. 

![](https://github.com/vdmitriev90/OrbMod_DotNET_UI/blob/master/ObservationsView.png)

### Plot graphs
Visualize result of orbit propagation or fiiting (Plot graphs)
There are two examples of such graphs.

Graph  of different source of accelerations for asteroid Apophis from 2005 to 2015

![](https://github.com/vdmitriev90/OrbMod_DotNET_UI/blob/master/Plot_acc.png)

Graph of post fit residuals (right ascension) for observations of Apophis asteroid  from 2005 to 2015, obtained in this software

![](https://github.com/vdmitriev90/OrbMod_DotNET_UI/blob/master/ResidualsRA.png)





