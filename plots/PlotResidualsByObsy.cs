using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ZedGraph;
using MathLib;
using static System.Math;
using System.IO;
using System.Drawing;

namespace OrbModUI
{
    //Plot residuals on ZedGraphControl by observatory
    //
    public abstract class PlotResbyObs : Plot
    {
        //intermnal class for storage statistic by observatory
        // 
        protected class statbyObs
        {
            public string ID;
            public double Mean;
            public double sigma;
            public uint counter;
            
            //
            public statbyObs()
            {
                counter = 0;
                Mean = sigma = 0;
            }
            //
            public statbyObs(uint i)
            {
                counter = i;
                Mean = sigma = 0;
            }
            //
            public string ToString(string format, string delim)
            {
                return (ID + delim + counter + delim + Mean.ToString(format) + delim + (sigma).ToString(format));
            }
        }

        public PlotResbyObs() { }
        public PlotResbyObs(ZedGraphControl zg, string fname) : base(zg, fname) { }
        protected abstract bool AddPoint(DateTime dt, double et, string[] Data, ref PointPairList Points);
       
        //
        public override void PlotData()
        {
            Random rand = new Random();

            GraphPane pane = zg.GraphPane;

            Dictionary<string, PointPairList> pLists = new Dictionary<string, PointPairList>();
            Dictionary<string, statbyObs> Stat = new Dictionary<string, statbyObs>();

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
                        //create and add new points list by Obseravatory
                        pList = new PointPairList();
                        pLists.Add(data[0], pList);

                    }
                    else
                    {
                        pList = pLists[data[0]];
                    }
                    //
                    AddPoint(dt, et, data, ref pList);
                }
                //
                int N_obsy = pLists.Count;
                statbyObs[] stats = new statbyObs[N_obsy];

                //Calculate mean by observatory
                int i_ = 0;
                foreach (var it in pLists)
                {
                    stats[i_] = new statbyObs(0);
                    stats[i_].ID = it.Key;
                    foreach (var it2 in it.Value)
                    {
                        stats[i_].Mean += it2.Y;
                        stats[i_].counter++;
                    }
                    //
                    stats[i_].Mean /= stats[i_].counter;
                    i_++;
                }
                //
                i_ = 0;

                foreach (var it in pLists)
                {
                    // Calculate standard deviation by observatory
                    #region stdev

                    foreach (var it2 in it.Value)
                    {
                        stats[i_].sigma += Misc.SQR((it2.Y - stats[i_].Mean));
                    }
                    // standard deviation
                    stats[i_].sigma = Sqrt(stats[i_].sigma / (stats[i_].counter - 1));

                    #endregion

                    // random color
                    Color col = Color.FromArgb(rand.Next(0, 255), rand.Next(0, 255), rand.Next(0, 255));

                    //add line
                    var list_ = it.Value;
                    LineItem myCurve = pane.AddCurve("", list_, col, (SymbolType)Config.Instance.SymbolType);

                    //line formatting
                    myCurve.Symbol.Size = Config.Instance.SymbolSize;
                    myCurve.Symbol.Fill.Type = FillType.Solid;
                    myCurve.Line.Width = Config.Instance.LineWidth;
                    
                    //label
                    string LabelText = stats[i_].ToString("F2", " ");
                    TextObj Label = new TextObj(LabelText, list_[0].X, list_[0].Y);
                    Label.FontSpec.Fill.Type = FillType.None;
                    Label.FontSpec.FontColor = col;
                    Label.FontSpec.IsBold = true;
                    Label.FontSpec.Border.IsVisible = false;
                    // add label to graph pane
                    pane.GraphObjList.Add(Label);

                    i_++;
                }
            }
            EndDraw();
        }

    }
    //
    public class PlotResbyObsRA : PlotResbyObs
    {
        public PlotResbyObsRA() { }
        public PlotResbyObsRA(ZedGraphControl zg, string fname) : base(zg, fname) { }
        protected override bool AddPoint(DateTime dt, double et, string[] data, ref PointPairList Points)
        {

            if (data.Length < 3) return false;
            double Val;
            double.TryParse(data[1], out Val);

            if (Config.Instance.UseCalend)
                Points.Add(new XDate(dt), Val);
            else
                Points.Add(dTdays(et), Val);
            return true;
        }
        public override void EndDraw_()
        {

            string yT = "Δα*cos(δ), asec";

            zg.GraphPane.YAxis.Title.Text = yT;
        }
    }
    //
    public class PlotResbyObsDec : PlotResbyObs
    {
        //
        public PlotResbyObsDec() { }
        //
        public PlotResbyObsDec(ZedGraphControl zg, string fname) : base(zg, fname) { }
        //
        protected override bool AddPoint(DateTime dt, double et, string[] data, ref PointPairList Points)
        {
            //
            if (data.Length < 3) return false;
            double Val;
            double.TryParse(data[2], out Val);

            if (Config.Instance.UseCalend)
                Points.Add(new XDate(dt), Val);
            else
                Points.Add(dTdays(et), Val);
            return true;
        }
        public override void EndDraw_()
        {
            string yT = "Δδ, asec";
            zg.GraphPane.YAxis.Title.Text = yT;
        }
    }
}
