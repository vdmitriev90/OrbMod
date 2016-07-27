// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

//#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#define _CRT_SECURE_NO_WARNINGS  

#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
#include <math.h>
#include <string>
#include<iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include<map>
#include "SpiceUsr.h"

#include"Parameters\constant.h"
#include"Parameters\Global.h"
#include"Parameters\config.h"


#include"Math\Algebra\Linear_Algebra\Matrix.h"
#include"Math\Algebra\Linear_Algebra\triple.h"
#include"Math\Algebra\Linear_Algebra\LinAlgAux.h"
#include"Math\Algebra\Linear_Algebra\LinearSystem.h"

#include"Math\Algebra\ComplexNum.h"
#include"Math\Algebra\SB.h"
#include"Math\Algebra\KS.h"

#include"Math\Astroynamics\Kepler.h"
#include"Math\Astroynamics\state.h"

#include"Math\Derivatives\Derivatives.h"

#include"Math\tform.h"

#include"Force\Perturbations\Cunningham.h"
#include"Force\Perturbations\atmosferic_drag.h"
#include"Force\Perturbations\SRP.h"

#include"Force\force.h"
#include"Force\ForceIzo.h"


#include"Misc\macroses.h"
#include"Misc\dateTime.h"
//#include"Misc\Marshaling.h"
#include"Misc\Misc.h"
#include"Misc\frame.h"
#include "Misc\visibility.h"


#include"Observations\Observatory.h"
#include"Observations\Obs.h"
#include"Observations\ObsSet.h"
#include"Observations\AstroObs.h"
#include"Observations\ModDistObs.h"
#include"Observations\ModAstroObs.h"
#include"Observations\ModAstroObs2.h"
#include"Observations\PreObrit.h"

#include"variables\Integrate.h"
#include"variables\var.h"

#include"Integration\Integration_.h"

#include"variables\debug\var_3D_izo2.h"
#include"variables\debug\var_KS_izo2.h"


#include"OrbFit\Abstract\OrbFit.h"

#include "OrbFit\batch_fitting\batchFitting.h"

#include "OrbFit\Filtering\XV\pureKalman_XV.h"
#include "OrbFit\Filtering\XV\hibridKalman_XV.h"
#include "OrbFit\Filtering\XV\seqLS.h"
#include"OrbFit\Filtering\XV\Filter_XV.h"
#include"OrbFit\Filtering\XV\batchFilter_XV.h"

#include"OrbFit\Filtering\KS\batchFilter_KS.h"
#include"OrbFit\Filtering\KS\seqLS_KS.h"

#include"OrbFit\FiniteDifference\OrbFit_FinDiff.h"

#include"OrbFit\OrbFit_XV.h"
#include"OrbFit\OrbFit_KS.h"
#include"OrbFit\OrbFit_SB.h"

#include"Interface\Interface.h"




// TODO: reference additional headers your program requires here
