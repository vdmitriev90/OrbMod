using System;
using System.IO;
using System.Windows.Forms;
using ZedGraph;

namespace OrbModUI
{
    public abstract class Plot
    {
        public Plot()
        {

        }
        //
        public Plot(ZedGraphControl zg, string fname)
        {
            this.zg = zg;
            FName = fname;
        }
        //
        protected ZedGraphControl zg;
        //
        protected string FName;
        //
        public abstract void PlotData();
        //
        public abstract void EndPlot();
        //
        public abstract void Autoscale();
    }
}
