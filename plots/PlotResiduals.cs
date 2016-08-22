using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ZedGraph;
using MathLib;
using static System.Math;
using System.IO;

namespace OrbModUI
{
    public class PlotResRA : PlotSingle
    {
        private int i = 0;
        private double Mean, Var;

        public PlotResRA() { }
        public PlotResRA(ZedGraphControl zg, string fname) : base(zg, fname) { }
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
        private int i = 0;
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
    //
    public class PlotResFull : PlotSingle
    {
        private int i = 0;
        private double Mean1, Var1;
        private double Mean2, Var2;

        public PlotResFull() { }
        public PlotResFull(ZedGraphControl zg, string fname) : base(zg, fname) { }
        public override void EndDraw_()
        {

            string yT = "sqrt(Δδ^2+(Δα*cosδ)^2), asec";
            zg.GraphPane.Title.Text += " σ= " + Math.Sqrt(Var1 + Var2).ToString("F3");

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

            Misc.RecMeanDisp(ref Mean1, ref Var1, i, Val1);
            Misc.RecMeanDisp(ref Mean2, ref Var2, i, Val2);
            i++;
            if (Config.Instance.UseCalend)
                list.Add(new XDate(dt), Val);
            else
                list.Add(dTdays(et), Val);
            return true;
        }

    }

    public abstract class PlotResbyObs : Plot
    {

        protected struct stat
        {

            public double Mean;
            public double Variance;
            public uint counter;

            public stat(uint i)
            {
                counter = i;
                Mean = Variance = 0;
            }
        }

        protected int i = 0;
        protected double Mean1, Var1;
        protected double Mean2, Var2;

        public PlotResbyObs() { }
        public PlotResbyObs(ZedGraphControl zg, string fname) : base(zg, fname) { }
        protected abstract bool AddPoint(string[] Data, ref PointPairList Points, ref stat Stati);

        public override void PlotData()
        {

            GraphPane pane = zg.GraphPane;
            pane.CurveList.Clear();

            Dictionary<string, PointPairList> pLists = new Dictionary<string, PointPairList>();
            Dictionary<string, stat> Stat = new Dictionary<string, stat>();

            using (StreamReader sr = new StreamReader(FName))
            {
                DateTime dt = new DateTime();
                double et = 0;
                string[] data = new string[1];


                while (sr.Peek() != -1)
                {
                    string line = sr.ReadLine();

                    if (!ParseString(line, ref dt, ref et, ref data)) continue;

                    if (data.Length != 3) continue;

                    PointPairList pList;

                    if (!pLists.TryGetValue(data[0], out pList))
                    {
                        pList = new PointPairList();
                        pLists.Add(data[0], pList);
                        stat st = new stat(0);
                        Stat.Add(data[0], st);
                    }
                    else
                    {
                        pList = pLists[data[0]];

                    }
                    AddPoint(data, ref )


                }
            }

        }


    }


}
