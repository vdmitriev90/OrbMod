using System;
using System.IO;
using ZedGraph;
using MathLib;

namespace OrbModUI
{
    public class PlotX : PlotSingle
    {

        public PlotX(ZedGraphControl zg, string fname) 
            : base(zg, fname)
        { }
        //

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
        protected override bool ParseData(DateTime dt, double et, string[] data, PointPairList list)
        {
            double.TryParse(data[0], out double Val);
            if (Config.Instance.UseAU)
                Val /= Consts.AU;

            AddPoint(list, dt, et, Val);
            return true;

        }

    }
    public class PlotY : PlotSingle
    {
        //
        public PlotY(ZedGraphControl zg, string fname) : base(zg, fname) { }
        //
        public override void EndDraw_()
        {
            string yT = "Y, ";
            if (Config.Instance.UseAU)
                yT += "AU";
            else
                yT += "km";
            zg.GraphPane.YAxis.Title.Text = yT;
        }
        //
        protected override bool ParseData(DateTime dt, double et, string[] data, PointPairList list)
        {
            double.TryParse(data[1], out double Val);
            if (Config.Instance.UseAU)
                Val /= Consts.AU;

            AddPoint(list, dt, et, Val);
            return true;
        }

    }
    public class PlotZ : PlotSingle
    {

        public PlotZ(ZedGraphControl zg, string fname) 
            : base(zg, fname)
        {
        }

        //
       public override void EndDraw_()
        {
            
            string yT = "Z, ";
            if (Config.Instance.UseAU)
                yT += "AU";
            else
                yT += "km";
            zg.GraphPane.YAxis.Title.Text = yT;
        }
        //
        protected override bool ParseData(DateTime dt, double et, string[] data, PointPairList list)
        {
            double.TryParse(data[2], out double Val);
            if (Config.Instance.UseAU)
                Val /= Consts.AU;

            AddPoint(list, dt, et, Val);
            return true;
        }

    }
    public class PlotVx : PlotSingle
    {

        public PlotVx(ZedGraphControl zg, string fname) 
            : base(zg, fname)
        {

        }
        //
       public override void EndDraw_()
        {
            
            string yT = "Vx, ";
            if (Config.Instance.UseAU)
                yT += "AU/day";
            else
                yT += "km/s";
            zg.GraphPane.YAxis.Title.Text = yT;
        }
        //
        protected override bool ParseData(DateTime dt, double et, string[] data, PointPairList list)
        {
            double.TryParse(data[3], out double Val);
            if (Config.Instance.UseAU)
                Val /= Consts.AUpDay;
            AddPoint(list, dt, et, Val);
            return true;
        }

    }
    public class PlotVy : PlotSingle
    {

        public PlotVy(ZedGraphControl zg, string fname) : base(zg, fname)
        {

        }
        //
       public override void EndDraw_()
        {
            
            string yT = "Vy, ";
            if (Config.Instance.UseAU)
                yT += "AU/day";
            else
                yT += "km/s";
            zg.GraphPane.YAxis.Title.Text = yT;
        }
        //
        protected override bool ParseData(DateTime dt, double et, string[] data, PointPairList list)
        {
            double.TryParse(data[4], out double Val);
            if (Config.Instance.UseAU)
                Val /= Consts.AUpDay;
            AddPoint(list, dt, et, Val);
            return true;
        }

    }
    public class PlotVz : PlotSingle
    {

        public PlotVz(ZedGraphControl zg, string fname) : base(zg, fname)
        {

        }
        //
       public override void EndDraw_()
        {
            
            string yT = "Vz, ";
            if (Config.Instance.UseAU)
                yT += "AU/day";
            else
                yT += "km/s";
            zg.GraphPane.YAxis.Title.Text = yT;
        }
        //
        protected override bool ParseData(DateTime dt, double et, string[] data, PointPairList list)
        {
            double.TryParse(data[5], out double Val);
            if (Config.Instance.UseAU)
                Val /= Consts.AUpDay;
            AddPoint(list, dt, et, Val);
            return true;
        }

    }
    public class PlotVel : PlotSingle
    {

        public PlotVel(ZedGraphControl zg, string fname) : base(zg, fname)
        {

        }
        //
       public override void EndDraw_()
        {
            
            string yT = "velocity, ";
            if (Config.Instance.UseAU)
                yT += "AU/day";
            else
                yT += "km/s";
            zg.GraphPane.YAxis.Title.Text = yT;
        }
        //
        protected override bool ParseData(DateTime dt, double et, string[] data, PointPairList list)
        {

            double.TryParse(data[3], out double x);
            double.TryParse(data[4], out double y);
            double.TryParse(data[5], out double z);

            triple vel = new triple(x,y,z);
            double Val = vel.Abs;
            if (Config.Instance.UseAU)
                Val /= Consts.AUpDay;

            AddPoint(list, dt, et, Val);

            return true;
        }

    }
    public class PlotR : PlotSingle
    {

        public PlotR(ZedGraphControl zg, string fname) : base(zg, fname)
        {

        }
        //
       public override void EndDraw_()
        {
            
            string yT = "r, ";
            if (Config.Instance.UseAU)
                yT += "AU";
            else
                yT += "km";
            zg.GraphPane.YAxis.Title.Text = yT;
        }
        //
        protected override bool ParseData(DateTime dt, double et, string[] data, PointPairList list)
        {
            double.TryParse(data[0], out double x);
            double.TryParse(data[1], out double y);
            double.TryParse(data[2], out double z);

            triple R = new triple(x, y, z);
            double Val = R.Abs;

            if (Config.Instance.UseAU)
                Val /= Consts.AU;
            AddPoint(list, dt, et, Val);
            return true;
        }

    }
    public class PlotXoY : PlotSingle
    {

        public PlotXoY(ZedGraphControl zg, string fname) : base(zg, fname)
        {

        }
        //
       public override void EndDraw_()
        {
            
            string yT = "Y, ";
            string xT = "X, ";

            if (Config.Instance.UseAU)
            {
                xT += "AU";
                yT += "AU";
            }
            else
            {
                xT += "km";
                yT += "km";
            }

            zg.GraphPane.YAxis.Title.Text = yT;
            zg.GraphPane.XAxis.Title.Text = xT;
            zg.GraphPane.XAxis.Type = AxisType.Linear;

        }
        //
        protected override bool ParseData(DateTime dt, double et, string[] data, PointPairList list)
        {
            double.TryParse(data[0], out double x);
            double.TryParse(data[1], out double y);


            if (Config.Instance.UseAU)
            {
                x /= Consts.AU;
                y /= Consts.AU;
            }
            list.Add(x, y);

            return true;
        }
        //
        public override void zgStateChange()
        {
            SetEqualScale(this.zg);
        }

    }
    public class PlotXoZ : PlotSingle
    {

        public PlotXoZ(ZedGraphControl zg, string fname) : base(zg, fname) { }
        //
       public override void EndDraw_()
        {
            
            string yT = "X, ";
            string xT = "Z, ";

            if (Config.Instance.UseAU)
            {
                xT += "AU";
                yT += "AU";
            }
            else
            {
                xT += "km";
                yT += "km";
            }

            zg.GraphPane.YAxis.Title.Text = yT;
            zg.GraphPane.XAxis.Title.Text = xT;
            zg.GraphPane.XAxis.Type = AxisType.Linear;

        }
        //
        protected override bool ParseData(DateTime dt, double et, string[] data, PointPairList list)
        {
            double.TryParse(data[0], out double x);
            double.TryParse(data[2], out double z);


            if (Config.Instance.UseAU)
            {
                x /= Consts.AU;
                z /= Consts.AU;
            }
            list.Add(x, z);

            return true;
        }
        //
        public override void zgStateChange()
        {
            SetEqualScale(this.zg);
        }

    }
    public class PlotYoZ : PlotSingle
    {

        public PlotYoZ(ZedGraphControl zg, string fname) : base(zg, fname)
        {

        }
        //
       public override void EndDraw_()
        {
            
            string yT = "Y, ";
            string xT = "Z, ";

            if (Config.Instance.UseAU)
            {
                xT += "AU";
                yT += "AU";
            }
            else
            {
                xT += "km";
                yT += "km";
            }

            zg.GraphPane.YAxis.Title.Text = yT;
            zg.GraphPane.XAxis.Title.Text = xT;
            zg.GraphPane.XAxis.Type = AxisType.Linear;

        }
        //
        protected override bool ParseData(DateTime dt, double et, string[] data, PointPairList list)
        {
            double.TryParse(data[1], out double y);
            double.TryParse(data[2], out double z);


            if (Config.Instance.UseAU)
            {
                y /= Consts.AU;
                z /= Consts.AU;
            }
            list.Add(y, z);

            return true;
        }
        //
        public override void zgStateChange()
        {
            SetEqualScale(this.zg);
        }

    }
}