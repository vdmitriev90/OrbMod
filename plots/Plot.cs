using System;
using System.IO;
using System.Windows.Forms;
using ZedGraph;
using static OrbModUI.OrbMod_FormGraph;

namespace OrbModUI
{
    public abstract class Plot
    {
        public Plot()
        {

        }
        //
        public Plot(ZedGraphControl zg, string fname)
        {
            this.zg = zg;
            FName = fname;
        }

        //
        protected ZedGraphControl zg;
        //
        protected string FName;
        //
        public abstract void PlotData();
        //
        public abstract void EndPlot();
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

            // Обновим данные об осях
            zg.AxisChange();

            // Обновляем график
            zg.Invalidate();
        }

    }
}
