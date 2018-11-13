using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using ZedGraph;
using static OrbModUI.OrbMod_FormGraph;

namespace OrbModUI
{
    public abstract class AccPlot : Plot
    {
        //
        public AccPlot() {    }
        //
        public AccPlot(ZedGraphControl zg, string fname) : base(zg, fname) {   }
        //
    }
    //
    public class Acc1Plot : AccPlot
    {
        //
        public Acc1Plot() {       }
        //
        public Acc1Plot(ZedGraphControl zg, string fname) : base(zg, fname) {   }

        //
        public override void PlotData()
        {
            GraphPane pane = zg.GraphPane;
            pane.CurveList.Clear();
            int N_acc = Config.Instance.ColorsAcc.Length;
            PointPairList[] points = new PointPairList[N_acc];
            for (int i = 0; i < N_acc; i++)
                points[i] = new PointPairList();

                string[] AccNames = new string[N_acc];

            AccNames[0] = "Central body";
            AccNames[1] = "Hight gravity terms";
            AccNames[2] = "Sun";
            AccNames[3] = "Mercury";
            AccNames[4] = "Venus";
            AccNames[5] = "Earth+Moon";
            AccNames[6] = "Mars";
            AccNames[7] = "Jupiter";
            AccNames[8] = "Saturn";
            AccNames[9] = "Uranus";
            AccNames[10] = "Neptune";
            AccNames[11] = "Pluto";
            AccNames[12] =(Config.Instance.id_add[0]).ToString();
            AccNames[13] =(Config.Instance.id_add[1]).ToString();
            AccNames[14] = (Config.Instance.id_add[2]).ToString();
            AccNames[15] = (Config.Instance.id_add[3]).ToString();
            AccNames[16] = (Config.Instance.id_add[4]).ToString();
           
            AccNames[17] = "Hight gravity terms #" + (Config.Instance.id_add[4]).ToString();
            AccNames[18] = "SRP";
            AccNames[19] = "Atmospheric drug";
            AccNames[20] = "General rel. 1";
            AccNames[21] = "General rel. 2";


            using (StreamReader sr = new StreamReader(fileName))
            {
                while (sr.Peek() != -1)
                {
                    string line = sr.ReadLine();

                    if (ParseString(line, out DateTime dt, out double et, out string[] data) && data.Length >= N_acc)
                    {
                        for (int i = 0; i < N_acc; i++)
                        {
                            double.TryParse(data[i], out double val);
                            if (Config.Instance.UseAU)
                                val /= Consts.AUpDay2;

                            if (val > 0)
                                AddPoint(points[i], dt, et, val);
                            
                        }
                    }
                }        
            }
            EndDraw();
            for (int i = 0; i < N_acc; i++)
            {
                if (points[i].Count > 0)
                {
                    LineItem myCurve = pane.AddCurve(AccNames[i], points[i], Color.FromArgb(Config.Instance.ColorsAcc[i]), (SymbolType)Config.Instance.SymbolType);

                    myCurve.Symbol.Size = Config.Instance.SymbolSize;
                    myCurve.Symbol.Fill.Type = FillType.Solid;

                    myCurve.Line.IsVisible = Config.Instance.IsShowLines;
                    myCurve.Line.Width = Config.Instance.LineWidth;
                    myCurve.Line.IsSmooth = Config.Instance.isSmoothGraph;
                    myCurve.Line.SmoothTension = Config.Instance.Tension;
                }
            }
        }



        //
        public override void EndDraw_()
        {
            zg.GraphPane.YAxis.Type = AxisType.Log;
            string yT = "Accelerations, ";
            if (Config.Instance.UseAU)
                yT += "AU/day^2";
            else
                yT += "km/s^2";
            zg.GraphPane.YAxis.Title.Text = yT;
        }
    }
}
    
