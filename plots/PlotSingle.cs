using System.IO;
using ZedGraph;

namespace OrbModUI
{
   public  abstract class PlotSingle : Plot
    {
        //
        public PlotSingle()
        {

        }
        //
        public PlotSingle(ZedGraphControl zg, string fname) : base(zg,fname)
        {

        }
        //
        protected abstract bool AddPoint(string str, PointPairList list);
        //
        public override void PlotData()
        {
            GraphPane pane = zg.GraphPane;
            PointPairList points = new PointPairList();

            using (StringReader sr = new StringReader(FName))
            {
                while (sr.Peek() != -1)
                {
                    string line = sr.ReadLine();

                    AddPoint(line, points);
                }
                EndPlot();
            }
        }
    }
  
    }