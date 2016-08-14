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
      public  Plot()
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
     abstract class SingePlot : Plot
    {
        public SingePlot()
        {

        }
        public SingePlot(ZedGraphControl zg): base(zg)
        {

        }
        protected abstract bool AddPoint(string str, PointPairList list);

        public override void PlotData()
        {
            GraphPane pane = zg.GraphPane;
            PointPairList points = new PointPairList();

            using (StringReader sr = new StringReader(FName))
            {
                while(sr.Peek()!=-1)
                {
                    string line = sr.ReadLine();
                    AddPoint(line, points);
                }
                EndPlot();
            }
        }

    }
}
