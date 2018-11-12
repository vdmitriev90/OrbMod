using System;
using System.Drawing;
using System.IO;
using ZedGraph;

namespace OrbModUI
{
    public abstract class PlotSingle : Plot
    {
        //
        public PlotSingle(){}
        //
        public PlotSingle(ZedGraphControl zg, string fname) : base(zg, fname){}
        //
        protected abstract bool ParseData(DateTime dt, double et, string[] data, PointPairList list);
        //
        public override void PlotData()
        {
            GraphPane pane = zg.GraphPane;
            pane.CurveList.Clear();

            PointPairList points = new PointPairList();
            using (StreamReader sr = new StreamReader(fileName))
            {

                while (sr.Peek() != -1)
                {
                    string line = sr.ReadLine();

                    if (!ParseString(line, out DateTime dateTime, out double et, out string[] data)) continue;

                    ParseData(dateTime, et, data, points);
                }

                //
                EndDraw();

                LineItem myCurve = pane.AddCurve("", points, Color.FromArgb(Config.Instance.col_Main), (SymbolType)Config.Instance.SymbolType);

                myCurve.Symbol.Size = Config.Instance.SymbolSize;
                myCurve.Symbol.Fill.Type = FillType.Solid;

                myCurve.Line.IsVisible = Config.Instance.IsShowLines;
                myCurve.Line.Width = Config.Instance.LineWidth;
                myCurve.Line.IsSmooth = Config.Instance.isSmoothGraph;
                myCurve.Line.SmoothTension = Config.Instance.Tension;
               
                //
                Autoscale();
            }
        }
    }
}