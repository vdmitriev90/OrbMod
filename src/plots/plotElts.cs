using System;
using System.IO;
using System.Windows.Forms;
using ZedGraph;
using static OrbModUI.OrbMod_FormGraph;

namespace OrbModUI
{
    public class PlotSMA : PlotSingle
    {

        public PlotSMA(ZedGraphControl zg, string fname) : base(zg, fname) { }
        //
        public override void EndDraw_()
        {

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
            if (data.Length < 2) return false;
            double peri, ecc;
            double.TryParse(data[0], out peri);
            double.TryParse(data[1], out ecc);
            double Val = peri / (1.0 - ecc);

            if (Config.Instance.UseAU)
                Val /= Consts.AU;
            if (Config.Instance.UseCalend)
                list.Add(new XDate(dt), Val);
            else
                list.Add(dTdays(et), Val);
            return true;
        }
    }
    
    public class PlotApo : PlotSingle
    {

        public PlotApo(ZedGraphControl zg, string fname) : base(zg, fname)      {    }
        //
        public override void EndDraw_()
        {
         
            string yT = "apocentric distance, ";
            if (Config.Instance.UseAU)
                yT += "AU";
            else
                yT += "km";
            zg.GraphPane.YAxis.Title.Text = yT;
        }
        //
        protected override bool AddPoint(DateTime dt, double et, string[] data, ref PointPairList list)
        {
            if (data.Length < 2) return false;
            double peri, ecc;
            double.TryParse(data[0], out peri);
            double.TryParse(data[1], out ecc);

            double Val = peri * ((1.0 + ecc) / (1.0 - ecc));

            if (Config.Instance.UseAU)
                Val /= Consts.AU;
            if (Config.Instance.UseCalend)
                list.Add(new XDate(dt), Val);
            else
                list.Add(dTdays(et), Val);
            return true;

        }
    }
    public class PlotPeri : PlotSingle
    {
        public PlotPeri(ZedGraphControl zg, string fname) : base(zg, fname) { }
        //
        public override void EndDraw_()
        {
         
            string yT = "pericentric distance, ";
            if (Config.Instance.UseAU)
                yT += "AU";
            else
                yT += "km";
            zg.GraphPane.YAxis.Title.Text = yT;
        }
        //
        protected override bool AddPoint(DateTime dt, double et, string[] data, ref PointPairList list)
        {
            if (data.Length < 1) return false;
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
    //
    public class PlotEcc : PlotSingle
    {

        public PlotEcc(ZedGraphControl zg, string fname) : base(zg, fname)
        {

        }
        //
        public override void EndDraw_()
        {
            string yT = "eccentrycity";

            zg.GraphPane.YAxis.Title.Text = yT;
        }
        //
        protected override bool AddPoint(DateTime dt, double et, string[] data, ref PointPairList list)
        {
            double Val;
            if (data.Length < 2) return false;
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
        public override void EndDraw_()
        {
         
            string yT = "inclination, deg";

            zg.GraphPane.YAxis.Title.Text = yT;
        }
        //
        protected override bool AddPoint(DateTime dt, double et, string[] data, ref PointPairList list)
        {
            if (data.Length < 3) return false;
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
        public override void EndDraw_()
        {
         
            string yT = "node, deg";

            zg.GraphPane.YAxis.Title.Text = yT;
        }
        //
        protected override bool AddPoint(DateTime dt, double et, string[] data, ref PointPairList list)
        {
            if (data.Length < 4) return false;
            double Val;
            double.TryParse(data[3], out Val);

            if (Config.Instance.UseCalend)
                list.Add(new XDate(dt), Val);
            else
                list.Add(dTdays(et), Val);
            return true;

        }
    }
    public class PlotW : PlotSingle
    {

        public PlotW(ZedGraphControl zg, string fname) : base(zg, fname)
        {

        }
        //
        public override void EndDraw_()
        {
         
            string yT = "argument of periapsis, deg";

            zg.GraphPane.YAxis.Title.Text = yT;
        }
        //
        protected override bool AddPoint(DateTime dt, double et, string[] data, ref PointPairList list)
        {
            if (data.Length < 5) return false;
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
        public override void EndDraw_()
        {
         
            string yT = "mean anomaly, deg";

            zg.GraphPane.YAxis.Title.Text = yT;
        }
        //
        protected override bool AddPoint(DateTime dt, double et, string[] data, ref PointPairList list)
        {
            if (data.Length < 6) return false;
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