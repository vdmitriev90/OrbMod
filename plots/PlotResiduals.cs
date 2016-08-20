using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ZedGraph;

namespace OrbModUI
{
    public class PlotResRA:PlotSingle
    {
        public PlotResRA() { }
        public PlotResRA(ZedGraphControl zg, string fname) : base(zg, fname){ }
        public override void EndDraw_()
        {

            string yT = "X, ";
            if (Config.Instance.UseAU)
                yT += "AU";
            else
                yT += "km";
            zg.GraphPane.YAxis.Title.Text = yT;
        }
        //
        protected override bool AddPoint(DateTime dt, double et, string[] data, ref PointPairList list)
        {
            double Val;
            double.TryParse(data[0], out Val);
            if (Config.Instance.UseAU)
                Val /= Consts.AU;
            if (Config.Instance.UseCalend)
                list.Add(new XDate(dt), Val);
            else
                list.Add(dTdays(et), Val);
            return true;

        }
    }
}
