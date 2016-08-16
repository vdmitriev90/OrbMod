﻿using System.Windows.Forms;
using ZedGraph;

namespace OrbModUI
{
    public partial class OrbMod_FormGraph : Form
    {

        public class PlotSpec : Plot
        {

            private Plot plot;
            public PlotSpec(ZedGraphControl zg, string fname)
            {
                this.zg = zg;
                this.FName = fname;

                plot = new PlotSMA(zg, fname);
            }
            //
            public void SetInternalState(PlotSourceData sourse, int Type)
            {
                plot = Factory(sourse, Type);
            }

            //
            public override void PlotData()
            {
                this.plot.PlotData();
            }
            //
            public override void EndDraw()
            {
                this.plot.EndDraw();
            }
            //
            public override void Autoscale()
            {
                this.plot.Autoscale();
            }
            //
            public override void zgStateChange()
            {
                this.plot.zgStateChange();
            }

            #region Object :Plot factory 
            //
            private Plot Factory(PlotSourceData sourse, int Type)
            {
                switch (sourse)
                {
                    case PlotSourceData.Acc:
                        return PlotAccFactory(sourse, Type);
                    case PlotSourceData.Elts:
                        return PlotEltsFactory(sourse, Type);
                    case PlotSourceData.SV:
                        return PlotSVFactory(sourse, Type);
                    default:
                        return null;
                }
            }
            //
            private Plot PlotAccFactory(PlotSourceData sourse, int Type)
            {
                switch ((Acc_vs_T)Type)
                {
                    case Acc_vs_T.Accelerations:
                        return new Acc1Plot(this.zg, FName);
                    default:
                        return null;

                }
            }
            //
            private Plot PlotEltsFactory(PlotSourceData sourse, int Type)
            {
                switch ((Elts_vs_T)Type)
                {
                    case Elts_vs_T.SMA:
                        return new PlotSMA(this.zg, FName);
                    case Elts_vs_T.PeriDistance:
                        return new PlotW(this.zg, FName);
                    case Elts_vs_T.ApoDistance:
                        return new PlotApo(this.zg, FName);
                    case Elts_vs_T.Ecc:
                        return new PlotEcc(this.zg, FName);
                    case Elts_vs_T.Inc:
                        return new PlotInc(this.zg, FName);
                    case Elts_vs_T.Node:
                        return new PlotNode(this.zg, FName);
                    case Elts_vs_T.W:
                        return new PlotW(this.zg, FName);
                    case Elts_vs_T.MeanAnomaly:
                        return new PlotMeanAn(this.zg, FName);
                    default:
                        return null;

                }
            }
            private Plot PlotSVFactory(PlotSourceData sourse, int Type)
            {
                switch ((SV_vs)Type)
                {
                    case SV_vs.X:
                        return new PlotX(this.zg, FName);
                    case SV_vs.Y:
                        return new PlotY(this.zg, FName);
                    case SV_vs.Z:
                        return new PlotZ(this.zg, FName);
                    case SV_vs.Vx:
                        return new PlotVx(this.zg, FName);
                    case SV_vs.Vy:
                        return new PlotVy(this.zg, FName);
                    case SV_vs.Vz:
                        return new PlotVz(this.zg, FName);
                    case SV_vs.R:
                        return new PlotR(this.zg, FName);
                    case SV_vs.Vel:
                        return new PlotVel(this.zg, FName);
                    case SV_vs.XoY:
                        return new PlotXoY(this.zg, FName);
                    case SV_vs.XoZ:
                        return new PlotXoZ(this.zg, FName);
                    case SV_vs.YoZ:
                        return new PlotYoZ(this.zg, FName);
                    default:
                        return null;

                }
            } 
            #endregion
        }
    }
}