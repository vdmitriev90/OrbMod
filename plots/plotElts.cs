using System;
using System.IO;
using System.Windows.Forms;
using ZedGraph;
using static OrbModUI.OrbMod_FormGraph;

namespace OrbModUI
{
        public class PlotSMA : PlotSingle
        {

            public PlotSMA(ZedGraphControl zg, string fname) :base(zg, fname)
            {
                
            }
        //
        public override void EndDraw()
        {
            base.EndDraw();
            string yT = "Semimajor axis, ";
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


        //

    }
    public class PlotEcc : PlotSingle
    {

        public PlotEcc(ZedGraphControl zg, string fname) : base(zg, fname)
        {

        }
        //
        public override void EndDraw()
        {
            base.EndDraw();
            string yT = "eccentrycity";

            zg.GraphPane.YAxis.Title.Text = yT;
        }
        //
        protected override bool AddPoint(DateTime dt, double et, string[] data, ref PointPairList list)
        {
            double Val;
            double.TryParse(data[1], out Val);

            if (Config.Instance.UseCalend)
                list.Add(new XDate(dt), Val);
            else
                list.Add(dTdays(et), Val);
            return true;

        }
    }
    public class PlotInc : PlotSingle
    {

        public PlotInc(ZedGraphControl zg, string fname) : base(zg, fname)
        {

        }
        //
        public override void EndDraw()
        {
            base.EndDraw();
            string yT = "inclination, deg";

            zg.GraphPane.YAxis.Title.Text = yT;
        }
        //
        protected override bool AddPoint(DateTime dt, double et, string[] data, ref PointPairList list)
        {
            double Val;
            double.TryParse(data[2], out Val);

            if (Config.Instance.UseCalend)
                list.Add(new XDate(dt), Val);
            else
                list.Add(dTdays(et), Val);
            return true;

        }
    }
    public class PlotNode : PlotSingle
    {

        public PlotNode(ZedGraphControl zg, string fname) : base(zg, fname)
        {

        }
        //
        public override void EndDraw()
        {
            base.EndDraw();
            string yT = "node, deg";

            zg.GraphPane.YAxis.Title.Text = yT;
        }
        //
        protected override bool AddPoint(DateTime dt, double et, string[] data, ref PointPairList list)
        {
            double Val;
            double.TryParse(data[3], out Val);

            if (Config.Instance.UseCalend)
                list.Add(new XDate(dt), Val);
            else
                list.Add(dTdays(et), Val);
            return true;

        }
    }
    public class PlotPeri : PlotSingle
    {

        public PlotPeri(ZedGraphControl zg, string fname) : base(zg, fname)
        {

        }
        //
        public override void EndDraw()
        {
            base.EndDraw();
            string yT = "argument of periapsis, deg";

            zg.GraphPane.YAxis.Title.Text = yT;
        }
        //
        protected override bool AddPoint(DateTime dt, double et, string[] data, ref PointPairList list)
        {
            double Val;
            double.TryParse(data[4], out Val);

            if (Config.Instance.UseCalend)
                list.Add(new XDate(dt), Val);
            else
                list.Add(dTdays(et), Val);
            return true;

        }
    }
    public class PlotMeanAn : PlotSingle
    {

        public PlotMeanAn(ZedGraphControl zg, string fname) : base(zg, fname)
        {

        }
        //
        public override void EndDraw()
        {
            base.EndDraw();
            string yT = "mean anomaly, deg";

            zg.GraphPane.YAxis.Title.Text = yT;
        }
        //
        protected override bool AddPoint(DateTime dt, double et, string[] data, ref PointPairList list)
        {
            double Val;
            double.TryParse(data[5], out Val);

            if (Config.Instance.UseCalend)
                list.Add(new XDate(dt), Val);
            else
                list.Add(dTdays(et), Val);
            return true;
        }
    }

}