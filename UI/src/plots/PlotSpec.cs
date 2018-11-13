using System.Windows.Forms;
using ZedGraph;

namespace OrbModUI
{
    public partial class OrbMod_FormGraph : Form
    {

        public class PlotSpec : Plot
        {
            public static string FileSelected{ set; get; }

            private Plot plot;
            public PlotSpec(ZedGraphControl zg, string fname)
            {
                this.zg = zg;
                this.fileName = fname;

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
            public override void EndDraw_()
            {
                this.plot.EndDraw_();
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
                    case PlotSourceData.Residuals:
                        return PlotResFactory(sourse, Type);
                    default:
                        return null;
                }
            }
            //
            private Plot PlotAccFactory(PlotSourceData sourse, int Type)
            {
                switch ((Accelerations)Type)
                {
                    case Accelerations.Accelerations:
                        return new Acc1Plot(this.zg, fileName);
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
                        return new PlotSMA(this.zg, fileName);
                    case Elts_vs_T.PeriDistance:
                        return new PlotPeri(this.zg, fileName);
                    case Elts_vs_T.ApoDistance:
                        return new PlotApo(this.zg, fileName);
                    case Elts_vs_T.Ecc:
                        return new PlotEcc(this.zg, fileName);
                    case Elts_vs_T.Inc:
                        return new PlotInc(this.zg, fileName);
                    case Elts_vs_T.Node:
                        return new PlotNode(this.zg, fileName);
                    case Elts_vs_T.W:
                        return new PlotW(this.zg, fileName);
                    case Elts_vs_T.MeanAnomaly:
                        return new PlotMeanAn(this.zg, fileName);
                    default:
                        return null;
                }
            }
            private Plot PlotSVFactory(PlotSourceData sourse, int Type)
            {
                switch ((SV_vs)Type)
                {
                    case SV_vs.X:
                        return new PlotX(this.zg, fileName);
                    case SV_vs.Y:
                        return new PlotY(this.zg, fileName);
                    case SV_vs.Z:
                        return new PlotZ(this.zg, fileName);
                    case SV_vs.Vx:
                        return new PlotVx(this.zg, fileName);
                    case SV_vs.Vy:
                        return new PlotVy(this.zg, fileName);
                    case SV_vs.Vz:
                        return new PlotVz(this.zg, fileName);
                    case SV_vs.R:
                        return new PlotR(this.zg, fileName);
                    case SV_vs.Vel:
                        return new PlotVel(this.zg, fileName);
                    case SV_vs.XoY:
                        return new PlotXoY(this.zg, fileName);
                    case SV_vs.XoZ:
                        return new PlotXoZ(this.zg, fileName);
                    case SV_vs.YoZ:
                        return new PlotYoZ(this.zg, fileName);
                    default:
                        return null;

                }
            } 
            private Plot PlotResFactory(PlotSourceData sourse, int Type)
            {
                switch ((Residuals)Type)
                {
                    case Residuals.RightAccention:
                        return new PlotResRA(this.zg, fileName);
                    case Residuals.Declination:
                        return new PlotResDec(this.zg, fileName);
                    case Residuals.RAandDec:
                        return new PlotResFull(this.zg, fileName);
                    case Residuals.RAbyObservatory:
                        return new PlotResbyObsRA(this.zg, fileName);
                    case Residuals.DecbyObservatory:
                        return new PlotResbyObsDec(this.zg, fileName);
                    default:
                        return null;
                }
            }

            #endregion
        }
    }
}