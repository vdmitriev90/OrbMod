using System;
using System.Drawing;
using System.IO;
using ZedGraph;

namespace OrbModUI
{
   public  abstract class PlotSingle : Plot
    {
        //
        public PlotSingle()
        {

        }
        //
        public PlotSingle(ZedGraphControl zg, string fname) : base(zg,fname)
        {

        }
        //
        protected abstract bool AddPoint(DateTime dt,double et, string[] data, ref PointPairList list);
        //
        public override void PlotData()
        {
            GraphPane pane = zg.GraphPane;
            pane.CurveList.Clear();

            PointPairList points = new PointPairList();

            using (StreamReader sr = new StreamReader(FName))
            {
                DateTime dt = new DateTime();
                double et = 0;
                string[] data = new string[1];

                while (sr.Peek() != -1)
                {
                    string line = sr.ReadLine();

                    if (!ParseString(line, ref dt, ref et, ref data)) continue;

                    AddPoint(dt, et, data, ref points);
                }
            }
            EndDraw();

            LineItem myCurve = pane.AddCurve("", points, Color.FromArgb(Config.Instance.col_Main), (SymbolType)Config.Instance.SymbolType);
            myCurve.Symbol.Size = Config.Instance.SymbolSize;
            myCurve.Symbol.Fill.Type = FillType.Solid;
            myCurve.Line.Width = Config.Instance.LineWidth;
            myCurve.Line.IsSmooth = Config.Instance.isSmoothGraph;
            myCurve.Line.SmoothTension = Config.Instance.Tension;

            Autoscale();
        }
    }
  
    }