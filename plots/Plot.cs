using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ZedGraph;

namespace OrbModUI
{
    abstract class Plot
    {
        public Plot()
        {

        }
        public Plot(ZedGraphControl zg)
        {
            this.zg = zg;
        }

        protected ZedGraphControl zg;
        protected string FName;

        public abstract void PlotData();
        public abstract void EndPlot();

        public abstract void Autoscale();
    }
}
