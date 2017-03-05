## OrbMod_DotNET_UI
C# GUI for [OrbMod software](https://github.com/vdmitriev90/OrbMod)

##  brief description

## Main menu

Here you able to specify:

1. central body
2. processing mode (orbit propagation or fitting orbit to observations)
3. Variables
4. intial conditions, its type, coordinates and time frame
5. integraion setting (step, order, tolerance and so on)

![Alt-текст](https://github.com/vdmitriev90/OrbMod_DotNET_UI/blob/master/MainWindow.png )

## Force model menu
Here you able to specify the set of perturbation forces:

1. Non-central part of central body's gravitation (via spherical harmonics approach). NB: tidal perturbations currently is disable .
2. big planets + Pluto as point masses
3. 5 additional bodies, whith IDs according to SPICE nomenclature (example: 3==Earth-Moon baricenter, 301== Moon, 499 == Mars, etc.)
3. Non-central part  of additional body #5  attraction (via spherical harmonics approach)
4. General relativity effects
5. Solar radiation pressure whithin 'cannon ball' model
5. athmospheric drag whithin 'cannon ball' model

![Alt-текст](https://github.com/vdmitriev90/OrbMod_DotNET_UI/blob/master/ForceModel.png)

## Observations view  

![Alt-текст](https://github.com/vdmitriev90/OrbMod_DotNET_UI/blob/master/ObservationsView.png)
