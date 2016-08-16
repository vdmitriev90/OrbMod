using System.Windows.Forms;
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

            }
            //
            public void SetInternalState(PlotSourceData sourse, int Type)
            {
                plot = Factory(sourse, Type);
            }
            private Plot Factory(PlotSourceData sourse, int Type)
            {
                switch(sourse)
                {
                    case PlotSourceData.Acc:
                        return PlotAccFactory(sourse, Type);
                    case PlotSourceData.Elts:

                    default:
                        return null;
                }
            }
            //
            public override void PlotData()
            {
                this.plot.PlotData();
            }
            //
            public override void EndPlot()
            {
                this.plot.EndPlot();
            }
            //
            public override void Autoscale()
            {
                this.plot.Autoscale();
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
                        return new Acc1Plot(this.zg, FName);
                    default:
                        return null;

                }
            }
        }
    }
}