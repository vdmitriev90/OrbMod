using System;
using System.IO;
using ZedGraph;

namespace OrbModUI
{
    public abstract class PlotX : PlotSingle
    {
        //
        public PlotX()
        {

        }
        //
        public PlotX(ZedGraphControl zg, string fname) : base(zg, fname)
        {

        }
        protected override bool AddPoint(string str, PointPairList list)
        {
            
        }
    }

}