using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ZedGraph;
using MathLib;
using static System.Math;

namespace OrbModUI
{
    public class PlotResRA:PlotSingle
    {
        private int i = 0;
        private double Mean, Var;

        public PlotResRA() { }
        public PlotResRA(ZedGraphControl zg, string fname) : base(zg, fname){ }
        public override void EndDraw_()
        {

            string yT = "Δα*cos(δ), asec";
            zg.GraphPane.Title.Text += " m= " + Mean.ToString("F3") + " σ= " + Math.Sqrt(Var).ToString("F3");

            zg.GraphPane.YAxis.Title.Text = yT;
        }
        //
        protected override bool AddPoint(DateTime dt, double et, string[] data, ref PointPairList list)
        {
            if (data.Length < 3) return false;
            double Val;
            double.TryParse(data[1], out Val);
            MathLib.Misc.RecMeanDisp(ref Mean, ref Var, ref i, Val);


            if (Config.Instance.UseCalend)
                list.Add(new XDate(dt), Val);
            else
                list.Add(dTdays(et), Val);
            return true;

        }
    }

    public class PlotResDec : PlotSingle
    {
        private int i=0;
        private double Mean, Var;

        public PlotResDec() { }
        public PlotResDec(ZedGraphControl zg, string fname) : base(zg, fname) { }
        public override void EndDraw_()
        {

            string yT = "Δδ, asec";
            zg.GraphPane.Title.Text += " m= " + Mean.ToString("F3") + " σ= " + Math.Sqrt(Var).ToString("F3");

            zg.GraphPane.YAxis.Title.Text = yT;
        }
        //
        protected override bool AddPoint(DateTime dt, double et, string[] data, ref PointPairList list)
        {

            if (data.Length < 3) return false;
            double Val;
            double.TryParse(data[2], out Val);
            Misc.RecMeanDisp(ref Mean, ref Var, ref i, Val);

            if (Config.Instance.UseCalend)
                list.Add(new XDate(dt), Val);
            else
                list.Add(dTdays(et), Val);
            return true;

        }

    }
    public class PlotResFull : PlotSingle
    {
        private int i = 0;
        private double Mean1, Var1;
        private double Mean2, Var2;

        public PlotResFull() { }
        public PlotResFull(ZedGraphControl zg, string fname) : base(zg, fname) { }
        public override void EndDraw_()
        {

            string yT = "sqrt(Δδ+Δα*cos(δ)), asec";
            zg.GraphPane.Title.Text += " σ= " + Math.Sqrt(Var1+ Var2).ToString("F3");

            zg.GraphPane.YAxis.Title.Text = yT;
        }
        //
        protected override bool AddPoint(DateTime dt, double et, string[] data, ref PointPairList list)
        {
            if (data.Length < 3) return false;
            double Val1, Val2;
            double.TryParse(data[1], out Val1);
            double.TryParse(data[2], out Val2);
            double Val = Sqrt(Val1 * Val1 + Val2 * Val2);

            Misc.RecMeanDisp(ref Mean1, ref Var1,  i, Val1);
            Misc.RecMeanDisp(ref Mean2, ref Var2,  i, Val2);
            i++;
            if (Config.Instance.UseCalend)
                list.Add(new XDate(dt), Val);
            else
                list.Add(dTdays(et), Val);
            return true;
        }

    }
}
