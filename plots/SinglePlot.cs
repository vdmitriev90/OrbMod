using System.IO;
using ZedGraph;

namespace OrbModUI
{
    abstract class SingePlot : Plot
    {
        public SingePlot()
        {

        }
        public SingePlot(ZedGraphControl zg) : base(zg)
        {

        }
        protected abstract bool AddPoint(string str, PointPairList list);

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