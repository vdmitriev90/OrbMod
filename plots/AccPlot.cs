using System;
using System.Collections.Generic;
using ZedGraph;
using static OrbModUI.OrbMod_FormGraph;

namespace OrbModUI
{
    public abstract class AccPlot : Plot
    {
        //
        public AccPlot()
        {

        }
        //
        public AccPlot(ZedGraphControl zg, string fname) : base(zg, fname)
        {

        }
        //
    }
    //
    public class Acc1Plot : AccPlot
    {
        //
        public Acc1Plot()
        {

        }
        //
        public Acc1Plot(ZedGraphControl zg, string fname) : base(zg, fname)
        {

        }

        //
        public override void PlotData()
        {
            throw new NotImplementedException();
        }
        //
        public override void Autoscale()
        {
            throw new NotImplementedException();
        }
        //
        public override void EndPlot()
        {
            throw new NotImplementedException();
        }
    }
}
    
