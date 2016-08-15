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
            //private Plot Factory(ZedGraphControl zg, string fname)
            //{
            //    return new Plo
            //}
            public override void PlotData()
            {
                this.plot.PlotData();
            }
            public override void EndPlot()
            {
                this.plot.EndPlot();
            }
            public override void Autoscale()
            {
                this.plot.Autoscale();
            }

        }
    }
}