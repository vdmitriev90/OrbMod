using System;
using System.IO;
using System.Windows.Forms;
using System.Drawing;
using ZedGraph;
using static OrbModUI.OrbMod_FormGraph;
using static System.Math;


namespace OrbModUI
{
    public abstract class Plot
    {
        protected int _EpochCounter;
        protected ZedGraphControl zg;
        //
        protected string FName;
        protected double t0;

        //
        public Plot()
        {


            _EpochCounter = 0;
        }
        //
        public Plot(ZedGraphControl zg, string fname)
        {
            this.zg = zg;
            FName = fname;
            GraphPane pane = zg.GraphPane;
            pane.CurveList.Clear();
            pane.GraphObjList.Clear();

            _EpochCounter = 0;
       }

        protected double dTdays(double et)
        {
            return (et - t0) / 86400.0;
        }

        protected virtual bool ParseString(string input, ref DateTime dt, ref double et, ref string[] data)
        {

            string[] strs = input.Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
            if (strs.Length < 6) return false;

            string s_dt = "";
            for (int i = 0; i < 4; i++)
                s_dt += strs[i] + " ";

            if (!DateTime.TryParse(s_dt, out dt)) return false;
            double.TryParse(strs[4], out et);
            data = new string[strs.Length - 5];

            for (int i = 0; i < data.Length; i++)
                data[i] = strs[i + 5];

            if (_EpochCounter == 0) t0 = et;
            _EpochCounter++;

            return true;
        }
        //

        public abstract void PlotData();
        public abstract void EndDraw_();
        //
        public virtual void EndDraw()
        {
            zg.GraphPane.YAxis.Type = AxisType.Linear;
            zg.GraphPane.Title.Text = Path.GetFileNameWithoutExtension(this.FName);
            if (Config.Instance.UseCalend)
            {
                zg.GraphPane.XAxis.Title.Text = "";
                zg.GraphPane.XAxis.Type = AxisType.Date;
            }
            else
            {
                zg.GraphPane.XAxis.Title.Text = "Time, days";
                zg.GraphPane.XAxis.Type = AxisType.Linear;
            }
            EndDraw_();


        }

        //
        public virtual void Autoscale()
        {
            GraphPane  pane = zg.GraphPane;

            // Установим масштаб по умолчанию для оси X
            pane.XAxis.Scale.MinAuto = true;
            pane.XAxis.Scale.MaxAuto = true;

            // Установим масштаб по умолчанию для оси Y
            pane.YAxis.Scale.MinAuto = true;
            pane.YAxis.Scale.MaxAuto = true;

            zgStateChange();

        }
        //
        //
        
        //
        public virtual void zgStateChange()
        {
            // Обновим данные об осях
            zg.AxisChange();

            // Обновляем график
            zg.Invalidate();
        }
        //
        protected static void SetEqualScale(ZedGraphControl zg)
        {
            GraphPane pane = zg.GraphPane;

            #region 1 variant
            //double Xmin = pane.XAxis.Scale.Min;
            //double Xmax = pane.XAxis.Scale.Max;

            //double Ymin = pane.YAxis.Scale.Min;
            //double Ymax = pane.YAxis.Scale.Max;

            //PointF PointMin = pane.GeneralTransform(Xmin, Ymin, CoordType.AxisXYScale);
            //PointF PointMax = pane.GeneralTransform(Xmax, Ymax, CoordType.AxisXYScale);
            //double dX = Abs(Xmax - Xmin);
            //double dY = Abs(Ymax - Ymin);

            //double Kx = dX / Abs(PointMax.X - PointMin.X);
            //double Ky = dY / Abs(PointMax.Y - PointMin.Y);

            //double K = Kx / Ky;

            //if (K > 1.0)
            //{
            //    pane.YAxis.Scale.Min = pane.YAxis.Scale.Min - dY * (K - 1.0) / 2.0;
            //    pane.YAxis.Scale.Max = pane.YAxis.Scale.Max + dY * (K - 1.0) / 2.0;
            //}
            //else
            //{
            //    K = 1.0 / K;
            //    pane.XAxis.Scale.Min = pane.XAxis.Scale.Min - dX * (K - 1.0) / 2.0;
            //    pane.XAxis.Scale.Max = pane.XAxis.Scale.Max + dX * (K - 1.0) / 2.0;

            //}
            #endregion

            #region 2 variant

            double Xmin = pane.XAxis.Scale.Min;
            double Xmax = pane.XAxis.Scale.Max;
            double Xaver = (Xmin + Xmax) / 2.0;

            double Ymin = pane.YAxis.Scale.Min;
            double Ymax = pane.YAxis.Scale.Max;
            double Yaver = (Ymin + Ymax) / 2.0;

            PointF PointMin = pane.GeneralTransform(Xmin, Ymin, CoordType.AxisXYScale);
            PointF PointMax = pane.GeneralTransform(Xmax, Ymax, CoordType.AxisXYScale);
            double dX = Math.Abs(Xmax - Xmin);
            double dY = Math.Abs(Ymax - Ymin);

            double DX = Math.Abs(PointMax.X - PointMin.X);
            double DY = Math.Abs(PointMax.Y - PointMin.Y);

            double Kx = dX / DX;
            double Ky = dY / DY;

            double K = (Kx + Ky) / 2.0;
            pane.YAxis.Scale.Min = Yaver - K * DY / 2.0;
            pane.YAxis.Scale.Max = Yaver + K * DY / 2.0;

            pane.XAxis.Scale.Min = Xaver - K * DX / 2.0;
            pane.XAxis.Scale.Max = Xaver + K * DX / 2.0; 
            #endregion

            // Обновим данные об осях
            zg.AxisChange();
            // Обновляем график
            zg.Invalidate();
        }

    }
}
