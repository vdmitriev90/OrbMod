using System;
using System.IO;
using System.Collections.Generic;

using static System.Math;

namespace OrbModUI
{
    public enum Variables { SODE_XV = 0, FODE_2D, FODE_3D, FODE_KS, FODE_SB, IZO_3D, IZO_KS, IZO_SB, FinDiff };
    public enum ProcessMode { Propagation = 0, bw_fw_test, Adjust, Debug };
    public enum FitMode { LS = 0, batch_LS_filer, pure_Kalman, hybrid_Kalman, };
    public enum TypeOfObs { mDist = 0, mAstro, mAstro2, Astro };
    public enum TypeOfIC { OrbitalElements = 0, StateVector };
    public enum FrameOfIC { Equator_and_Equinox_J2000 = 0, Ecliptic_and_Equinox_J2000 };
    public enum TimeFormat { UTC_Calendar_format = 0, TDB_Seconds_past_J2000, TDB_Calendar_format, TT_Calendar_format };

    public enum EarthFixFrame { IAU_EARTH = 0, ITRF93, ITRF2008 };

    public class Config
    {
        //
        private delegate string Par2Str();
        private delegate bool Str2Par(string str);

        private Dictionary<string, Str2Par> Parser;
        private Par2Str[] Formatters;

        //
        private Config()
        {
            initDict();
        }

        private static readonly Lazy<Config> instanceHolder =  new Lazy<Config>(() => new Config());

        public static Config Instance
        {
            get { return instanceHolder.Value; }
        }
        #region Fields
        public OrbModCLRWrapper.OrbModWrap OrbModWr;

        public int IDC;
        public Variables var;
        public ProcessMode mode;
        public FitMode fitMode;
        public TypeOfObs ObsType;
        public EarthFixFrame EarthFrame;
        public TypeOfIC ICType;
        public FrameOfIC ICFrame;
        public OrbModUI.TimeFormat Tframe;

        public bool IsUsePeriTime;
        //state
        public string[] SV = new string[6];
        public string observeratories;
        //integrator settings
        public int NOr;
        public double Local_eps;
        public double Step;
        public bool IsAutoStep;

        public double discr;
        //maxnum of iterations
        public double niter;


        //Outliers rejection
        public bool isRejOuts;
        public float OutlsThresh;
        public bool isMemOuts;

        //Filter settings
        public int maxIterPerBatch;
        public double arcLength;
        public int MinObsinBatch;
        public double ObsSigma;
        public double PosRMS;
        public double VelRMS;

        public double Qnoise;
        //
        public double OrbFitEps;
        public int OrbFitMaxIter;
        public string s_t0, s_te;
        //perturbations by planets; b_pl[10] == Sun
        public bool[] b_pl = new bool[10];
        public bool[] b_add = new bool[5];
        public int[] id_add = new int[5];

        public bool b_add5Cnm;
        public string add5_FileModel;
        public int add5_N;

        public bool b_CB_Cnm;
        public string CB_FileModel;
        public int CB_N;

        public bool b_rel;
        public bool b_rel_LT;


        public bool b_SRP;
        public double SRP_albedo;
        public double SRP_S;
        public double SRP_Mass;

        //Output
        public bool b_out_sv_J2000;
        public bool b_out_el_J2000;
        public bool b_out_sv_ECLIPJ2000;
        public bool b_out_el_ECLIPJ2000;
        public bool b_out_sv_IAUPlanet;
        public bool b_out_acc;
        public bool b_out_BL;
        public bool b_3_BFF_sv;
        //
        public int ID_3_BFF_num;
        //
        public int col_Main;
        public int[] ColorsAcc = new int[22];
        //
        public string ObsPath;
        public double obs_t0, obs_te;
        //
        //line
        public int LineWidth;
        public int SymbolType;
        public int SymbolSize;

        public bool UseAU = false;
        public bool UseCalend = false;

        public bool isSmoothGraph = false;
        public float Tension = 0;
        //
        public bool isLogRes;

#endregion

        private void initDict()
        {
            Parser = new Dictionary<string, Str2Par>()
            {
        { "Mode", ProcessMode },
        { "FittingMode", FittingMode },
        { "Obs", Obs },
        { "MinObsInbatch", MinObsInbatch },
        { "ArcLength", ArcLength },
        { "NmNr", NmNr },
        { "IDC", CB },
        { "Integrator", Int },
        { "Variables", Var },
        { "NOR", NOR },
        { "Step", step },
        { "Eps", eps},
        { "OrbFitEps", orbFitEps },
        { "IsAutoStep", Autostep },
        { "Niter", Niter },
        { "OrbFitNiter", orbFitNiter },
        { "orbFitNiterPerBatch", orbFitNiterPerBatch },
        { "orbFitRejOuts", orbFitRejOuts },
        { "T_start", t0 },
        { "T_end", te },
        { "Frame", frame },
        { "EarthFixedFrame", EarthFixedFrame },
        { "Time_scale", tscale },
        { "Type_of_IC", TypeIC },
        { "UsePeriTime",UsePeriTime },
        { "IC", IC },
        { "PerturbationsByPlanets", BigPlanets },
        { "PerturbationsBySpecificBodies", AddBodies },
        { "AddBody5HT", AddBody5HT },
        { "CBHterms", CBHterms },
        { "Rel", Rel },
        { "SRP", SRP },
        { "Discr", Discr },
        { "Out", Out },
        { "BFFID", BFFID },
        { "Colors", Colors },
        { "useObservatoris", useObs },
        { "ObservationsPath", ObservationsPath },
        { "ObsTimeFrame", ObsTimeFrame },

        { "IsLogResiduals", IsLogResiduals },
        { "aprioriRMS", aprioriRMS },
        { "processNoise", processNoise }
            };
            Formatters = new Par2Str[]
            {
        ProcessMode,FittingMode,
        Obs, MinObsInbatch,ArcLength,
        NmNr, CB,Int, Var, NOR,
         step, Eps, orbFitEps,
        AutoStep ,Niter, orbFitNiter,
        orbFitNiterPerBatch,orbFitRejOuts,
         T_start ,  T_end ,  Frame ,EarthFixedFrame,
         Time_scale, TypeIC, UsePeriTime, IC,
        BigPlanets,  AddBodies,AddBody5HT, CBHterms, Rel, SRP,
        Discr, Out,BFFID, Colors,
                useObs,ObservationsPath,ObsTimeFrame,
       lineWidth,symbolSize, symbolType,  IsLogResiduals,
        aprioriRMS,processNoise
            };
        }

        public bool LoadConfig(string Path)
        {

                using (StreamReader sr = new StreamReader(Path))
                {
                    while (sr.Peek() != -1)
                    {
                        string line = sr.ReadLine();
                        string[] _v = line.Split(new char[] { ':' },2);
                        if (_v.Length < 2) continue;
                        Str2Par del;
                        if (Parser.TryGetValue(_v[0], out del))
                            del(_v[1]);
                    }
                }
            

            return true;
        }

        public bool SaveConfig(string fileName)
        {
            try
            {
                using (StreamWriter sw = new StreamWriter(fileName))
                {
                    foreach (var it in Formatters)
                        sw.WriteLine(it());

                    sw.Close();
                }
            }
            catch (Exception ex)
            {
                return false;
            }
            return true;
        }

        #region Parsers
            bool NmNr(string s)
        {
            //  NameNr = (NameOrNumber)int.Parse(s);
            return true;
        }
        //
        bool ProcessMode(string s)
        {
             mode = (ProcessMode)int.Parse(s);
            return true;
        }
        //
        bool FittingMode(string s)
        {
            fitMode = (FitMode)int.Parse(s);
            return true;
        }
        //
        bool Obs(string s)
        {
            ObsType = (TypeOfObs)int.Parse(s);
            return true;
        }
        //
        bool ArcLength(string s)
        {
            arcLength = double.Parse(s);
            return true;
        }
        //
        bool MinObsInbatch(string s)
        {
            MinObsinBatch = int.Parse(s);
            return true;
        }
        //
        bool CB(string s)
        {
            IDC = int.Parse(s);
            return true;
        }
        //
        bool Int(string s)
        {
            // = int.Parse(s);
            return true;
        }
        bool Var(string s)
        {
            var = (Variables)int.Parse(s);
            return true;
        }
        //
        bool NOR(string s)
        {
            NOr = int.Parse(s);
            return true;
        }
        //
        bool step(string s)
        {
            Step = double.Parse(s);
            return true;
        }
        //
        bool eps(string s)
        {
            Local_eps =float.Parse(s);
            return true;
        }
        //
        bool orbFitEps(string s)
        {
            OrbFitEps = Math.Pow(10, -float.Parse(s));
            return true;
        }
        //
        bool Autostep(string s)
        {
            IsAutoStep =Convert.ToBoolean(int.Parse(s));
            return true;
        }
        //
        bool Niter(string s)
        {
            niter = int.Parse(s);
            return true;
        }
        //
        bool orbFitNiter(string s)
        {
            OrbFitMaxIter = int.Parse(s);
            return true;
        }
        //
        bool orbFitNiterPerBatch(string s)
        {
            maxIterPerBatch = int.Parse(s);
            return true;
        }
        //
        bool orbFitRejOuts(string s)
        {
            string[] strs = s.Split(new char[] { ';' }, StringSplitOptions.RemoveEmptyEntries);
            if (strs.Length < 2) return false;
            isRejOuts = Convert.ToBoolean(int.Parse(strs[0]));
            OutlsThresh = float.Parse(strs[1]);
            return true;
        }
        //
        bool t0(string s)
        {
            s_t0 = s;
            return true;
        }
        //
        bool te(string s)
        {
            s_te = s;
            return true;
        }
        //
        bool frame(string s)
        {
            ICFrame = (FrameOfIC)int.Parse(s);
            return true;
        }
        //
        bool EarthFixedFrame(string s)
        {
            EarthFrame = (EarthFixFrame)int.Parse(s);
            return true;
        }
        //
        bool tscale(string s)
        {
            Tframe = (OrbModUI.TimeFormat)int.Parse(s);
            return true;
        }
        //
        bool TypeIC(string s)
        {
            ICType = (TypeOfIC)int.Parse(s);
            return true;
        }
        bool UsePeriTime(string s)
        {
            IsUsePeriTime = Convert.ToBoolean(int.Parse(s));
            return true;
        }
        bool IC(string s)
        {
            string[] strs = s.Split(new char[] { ';' }, StringSplitOptions.RemoveEmptyEntries);
            if (strs.Length < 6) return false;

            for (int i = 0; i < 6; i++) SV[i] = strs[i];
            //OrbModCLRWrapper.OrbModWrap.setIC(IC,)
            return true;
        }
        bool BigPlanets(string s)
        {
            string[] strs = s.Split(new char[] { ';' }, StringSplitOptions.RemoveEmptyEntries);
            if (strs.Length < 10) return false;
            for (int i = 0; i < 10; i++)
                b_pl[i] = Convert.ToBoolean(int.Parse(strs[i]));

            return true;
        }
        bool AddBodies(string s)
        {
            string[] strs = s.Split(new char[] { ';' }, StringSplitOptions.RemoveEmptyEntries);
            if (strs.Length < 10) return false;
            int j = 0;
            for (int i = 0; i < 10; i = i + 2)
            {
                b_add[j] = Convert.ToBoolean(int.Parse(strs[i+1]));
                id_add[j] = int.Parse(strs[i ]);
                j++;
            }
            return true;
        }
        //
        bool AddBody5HT(string s)
        {
            string[] strs = s.Split(new char[] { ';' }, StringSplitOptions.RemoveEmptyEntries);
            if (strs.Length < 3) return false;

            b_add5Cnm = Convert.ToBoolean(int.Parse(strs[0]));
            add5_N = (int.Parse(strs[1]));
            add5_FileModel = strs[2];
            return true;
        }
        //
        bool CBHterms(string s)
        {
            string[] strs = s.Split(new char[] { ';' }, StringSplitOptions.RemoveEmptyEntries);
            if (strs.Length < 3) return false;

            b_CB_Cnm = Convert.ToBoolean(int.Parse(strs[0]));
            CB_N = (int.Parse(strs[1]));
            CB_FileModel = strs[2];

            return true;
        }
        bool Rel(string s)
        {
            string[] strs = s.Split(new char[] { ';' }, StringSplitOptions.RemoveEmptyEntries);
            if (strs.Length < 2) return false;
            b_rel = Convert.ToBoolean(int.Parse(strs[0]));
            b_rel_LT = Convert.ToBoolean(int.Parse(strs[1]));

            return true;
        }
        bool SRP(string s)
        {
            string[] strs = s.Split(new char[] { ';' }, StringSplitOptions.RemoveEmptyEntries);
            if (strs.Length < 4) return false;

            b_SRP =  Convert.ToBoolean(int.Parse(strs[0]));
            SRP_albedo = double.Parse(strs[1]);
            SRP_S = double.Parse(strs[2]);
            SRP_Mass = double.Parse(strs[3]);

            return true;
        }
        bool Discr(string s)
        {
            discr = double.Parse(s);
            return true;
        }
        bool Out(string s)
        {
            string[] strs = s.Split(new char[] { ';' }, StringSplitOptions.RemoveEmptyEntries);
            if (strs.Length < 8) return false;

            b_out_sv_J2000 =  Convert.ToBoolean(int.Parse(strs[0]));
            b_out_el_J2000 =  Convert.ToBoolean(int.Parse(strs[1]));
            b_out_sv_ECLIPJ2000 =  Convert.ToBoolean(int.Parse(strs[2]));
            b_out_el_ECLIPJ2000 =  Convert.ToBoolean(int.Parse(strs[3]));
            b_out_sv_IAUPlanet =  Convert.ToBoolean(int.Parse(strs[4]));
            b_out_acc =  Convert.ToBoolean(int.Parse(strs[5]));
            b_out_BL =  Convert.ToBoolean(int.Parse(strs[6]));
            b_3_BFF_sv =  Convert.ToBoolean(int.Parse(strs[7]));
            return true;
        }
        //
        bool BFFID(string s)
        {
            ID_3_BFF_num = int.Parse(s);
            return true;
        }
        bool Colors(string s)
        {
            string[] strs = s.Split(new char[] { ';' }, StringSplitOptions.RemoveEmptyEntries);
            if (strs.Length < 23) return false;

            col_Main = int.Parse(strs[0]);
            for (int i = 0; i < 22; i++)
                ColorsAcc[i] = int.Parse(strs[i + 1]);

            return true;
        }
        bool useObs(string s)
        {
            //try
            //{
            //    string[] strs = s.Split(new char[] { ';' }, StringSplitOptions.RemoveEmptyEntries);

            //    foreach (var it in strs)
            //    {
            //        if (it.Length < 5) return false;
            //        string key = it.Substring(0, 3);
            //        int val = int.Parse(it.Substring(4, 1));
            //        if (!ObsSet::Instance().tryAddObs(key, val)) ObsSet::Instance().isUseObs[key] = val;
            //    }
            //}
            //catch (Exception ex)
            //{
            //    return false;
            //}
            return true;
        }
        //
        bool ObsTimeFrame(string s)
        {
            string[] strs = s.Split(new char[] { ';' }, StringSplitOptions.RemoveEmptyEntries);
            if (strs.Length < 2) return false;

            obs_t0 = double.Parse( strs[0]);
            obs_te = double.Parse(strs[1]);
            return true;
        }
        //
        bool ObservationsPath(string s)
        {
            ObsPath = s;
            return true;
        }
        //
        bool lineWidth(string s)
        {
            LineWidth = int.Parse(s);
            return true;
        }
        bool symbolType(string s)
        {
            SymbolType = int.Parse(s);
            return true;
        }
        //
        bool symbolSize(string s)
        {
            SymbolSize = int.Parse(s);
            return true;
        }
        //
        bool IsLogResiduals(string s)
        {
            isLogRes =  Convert.ToBoolean(int.Parse(s));
            return true;
        }
        bool aprioriRMS(string s)
        {
            string[] strs = s.Split(new char[] { ';' }, StringSplitOptions.RemoveEmptyEntries);
            if (strs.Length < 3) return false;
            ObsSigma = double.Parse(strs[0]);
            PosRMS = double.Parse(strs[1]);
            VelRMS = double.Parse(strs[2]);

            return true;
        }
        //
        bool processNoise(string s)
        {
            string[] strs = s.Split(new char[] { ';' }, StringSplitOptions.RemoveEmptyEntries);
            Qnoise = double.Parse(strs[0]);
            return true;
        }

        #endregion


        #region Formatters

        string  NmNr()
        {
            string str = "NmNr:1";
            //str += Convert.ToString((int) NameNr);
            return str;
        }
        //
        string  ProcessMode()
        {
            string str = "Mode:";
            str += Convert.ToString((int) mode);
            return str;
        }
        string  FittingMode()
        {
            string str = "FittingMode:";
            str += Convert.ToString((int) fitMode);
            return str;
        }
        //
        string  Obs()
        {
            string str = "Obs:";
            str += Convert.ToString((int) ObsType);
            return str;
        }
        //
        string  MinObsInbatch()
        {
            string str = "MinObsInbatch:";
            str += Convert.ToString( MinObsinBatch);
            return str;
        }
        //
        string  ArcLength()
        {
            string str = "ArcLength:";
            str += Convert.ToString( arcLength);
            return str;
        }
        //
        string  CB()
        {
            string str = "IDC:";
            str += Convert.ToString( IDC);
            return str;
        }
        //
        string  Int()
        {
            return "Integrator:0";
        }
        //
        string  Var()
        {
            string str = "Variables:";
            str += Convert.ToString( (int)var);
            return str;
        }
        string  NOR()
        {
            string str = "NOR:";
            str += Convert.ToString( NOr);
            return str;
        }
        string  step()
        {
            string str = "Step:";

            str += Step.ToString("F12");
            return str;
        }
        string  Eps()
        {
            string str = "Eps:";
            str += Convert.ToString(Local_eps);
            return str;
        }
        string  orbFitEps()
        {
            string str = "OrbFitEps:";
            str += Convert.ToString(Abs(Log10(OrbFitEps)));
            return str;
        }
        string  AutoStep()
        {
            string str = "IsAutoStep:";
            str += Convert.ToString(Convert.ToInt32( IsAutoStep));
            return str;
        }
        //
        string  Niter()
        {
            string str = "Niter:";
            str += Convert.ToString( niter);
            return str;
        }
        //
        string  orbFitNiter()
        {
            string str = "OrbFitNiter:";
            str += Convert.ToString(OrbFitMaxIter);
            return str;
        }
        //
        string  orbFitNiterPerBatch()
        {
            string str = "orbFitNiterPerBatch:";
            str += Convert.ToString(maxIterPerBatch);

            return str;
        }
        //
        string  orbFitRejOuts()
        {
            string str = "orbFitRejOuts:";
            str += Convert.ToString(Convert.ToInt32(isRejOuts)) + ";";
            str += Convert.ToString(OutlsThresh);

            return str;
        }
        string  T_start()
        {
            string str = "T_start:";
            str +=  s_t0;
            return str;
        }
        string  T_end()
        {
            string str = "T_end:";
            str +=  s_te;
            return str;
        }
        //
        string  Frame()
        {
            string str = "Frame:";
            str += Convert.ToString( (int)ICFrame);
            return str;
        }
        //
        string  EarthFixedFrame()
        {
            string str = "EarthFixedFrame:";
            str += Convert.ToString((int) EarthFrame);
            return str;
        }
        //
        string  Time_scale()
        {
            string str = "Time_scale:";
            str += Convert.ToString((int) Tframe);
            return str;
        }
        string  TypeIC()
        {
            string str = "Type_of_IC:";
            str += Convert.ToString( (int)ICType);
            return str;
        }
        string  UsePeriTime()
        {
            string str = "UsePeriTime:";
            str += Convert.ToString("0");
            return str;
        }
        string  IC()
        {
            string str = "IC:";
            for (int i = 0; i < 6; i++)
            {
                str += SV[i];
                str += ';';
            }
            return str;
        }
        string  BigPlanets()
        {
            string str = "PerturbationsByPlanets:";
            foreach (var it in b_pl)
                str += Convert.ToString(Convert.ToUInt32(it))+";";

            return str;
        }
        //
        string  AddBodies()
        {
            string str = "PerturbationsBySpecificBodies:";
            for (int i = 0; i< b_add.Length; i++)
            {
                str += Convert.ToString(id_add[i]) + ";" + Convert.ToString(Convert.ToInt32(b_add[i])) +";" ;
            }
            return str;
        }
        //
        string  CBHterms()
        {
            string str = "CBHterms:";
               str += Convert.ToString(Convert.ToInt32( b_CB_Cnm)) + ";" + Convert.ToString( CB_N) + ';' +  CB_FileModel;

            return str;
        }
        //
        string  AddBody5HT()
        {
            string str = "AddBody5HT:";
            str += Convert.ToString(Convert.ToInt32(b_add5Cnm)) + ";" + Convert.ToString(add5_N) + ';' + add5_FileModel;
            return str;
        }
        //
        string  Rel()
        {
            string str = "Rel:";
            str += Convert.ToString(Convert.ToInt32(b_rel)) + ";" + Convert.ToString(Convert.ToInt32(b_rel_LT));

            return str;
        }
        //
        string  SRP()
        {
            string str = "SRP:";
            str += Convert.ToString(Convert.ToInt32(b_SRP)) + ';' + Convert.ToString( SRP_albedo) + ';';
            str += Convert.ToString((int) SRP_S) + ';' + Convert.ToString((int) SRP_Mass);

            return str;
        }
        //
        string  Discr()
        {
            string str = "Discr:";
            str += Convert.ToString( discr);

            return str;
        }
        //
        string  Out()
        {
            string str = "Out:";
            str += Convert.ToString( Convert.ToInt32( b_out_sv_J2000) )+ ";";
            str += Convert.ToString( Convert.ToInt32(b_out_el_J2000)) + ";";
            str += Convert.ToString( Convert.ToInt32(b_out_sv_ECLIPJ2000)) + ";";
            str += Convert.ToString( Convert.ToInt32(b_out_el_ECLIPJ2000)) + ";";
            str += Convert.ToString( Convert.ToInt32(b_out_sv_IAUPlanet)) + ";";
            str += Convert.ToString( Convert.ToInt32(b_out_acc)) + ";";
            str += Convert.ToString( Convert.ToInt32(b_out_BL)) + ";";
            str += Convert.ToString( Convert.ToInt32(b_3_BFF_sv)) + ";";

            return str;
        }
        //
        string  BFFID()
        {
            string str = "BFFID:";
            str += Convert.ToString( ID_3_BFF_num);
            return str;
        }
        //
        string  Colors()
        {
            string str = "Colors:";
            str += Convert.ToString( col_Main) + ';';
            for (int i = 0; i < 22; i++)
                str += Convert.ToString( ColorsAcc[i]) + ';';
            return str;
        }
        //
        string  useObs()
        {
            string str = "useObservatoris:"+observeratories;

            return str;
        }
        //
        string  ObservationsPath()
        {
            string str = "ObservationsPath:";
            str += ObsPath;
            return str;
        }
        string ObsTimeFrame()
        {
            string str = "ObsTimeFrame:";
            str += obs_t0.ToString("F4")+";";
            str += obs_te.ToString("F4") + ";";
            return str;
        }
        //
        string  IsLogResiduals()
        {
            string str = "IsLogResiduals:";
            str += Convert.ToString(Convert.ToInt32( isLogRes));
            return str;
        }
        //
        string  aprioriRMS()
        {
            string str = "aprioriRMS:";

            str += ObsSigma.ToString("E8")+";";
            str += PosRMS.ToString("E8") + ";";
            str += VelRMS.ToString("E8") + ";";

            return str;
        }
        //
        string  processNoise()
        {
            string str = "processNoise:";
            str += Qnoise.ToString("E8") ;

            return str;
        }
        string lineWidth()
        {
            string str = "lineWidth:";
            str += LineWidth.ToString();

            return str;
        }
        string symbolSize()
        {
            string str = "symbolSize:";
            str += SymbolSize.ToString();

            return str;
        }
        string symbolType()
        {
            string str = "symbolType:";
            str += SymbolType.ToString();

            return str;
        }
        #endregion

    }
}
