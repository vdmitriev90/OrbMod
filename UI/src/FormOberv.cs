using System;
using System.Windows.Forms;
using System.Linq;
using System.Collections.Generic;
using ZedGraph;
using OrbModCLRWrapper;

namespace OrbModUI
{
    public partial class OrbMod_FormOberv : Form
    {
        int labelsXfontSize = 12;
        int labelsYfontSize = 12;

        int titleXFontSize = 14;
        int titleYFontSize = 14;

        int legendFontSize = 12;

        int mainTitleFontSize = 16;

        GraphPane pane;

        bool IsShowLegend = false;

        public OrbMod_FormOberv()
        {
            InitializeComponent();
            pane = zg_ObsView.GraphPane;
           
           
        }

        //
        private void cb_IsShowLegend_CheckedChanged(object sender, EventArgs e)
        {
            IsShowLegend = cb_IsShowLegend.Checked;
            GraphPane  pane = zg_ObsView.GraphPane;
            pane.Legend.IsVisible = IsShowLegend;

            UpdateZedGraph();
        }

        //
        private void OrbMod_FormOberv_Load(object sender, EventArgs e)
        {
            cb_IsShowLegend.Checked = IsShowLegend;

            Config.Instance.ObsSet.DataToForm(pane, dgv_1);
            string totalObs = Config.Instance.ObsSet.TypeOfObserv();


            pane.YAxis.Title.Text = $"Observatory with {totalObs} obs.";
            pane.XAxis.Title.Text = "UTC";

            FormatZedGraph();

            ZgApplyFormatting();

            ChangeTimeFrame();
        }

        //
        private void bt_apply_Click(object sender, EventArgs e)
        {
            //Обсерватории, наблюдения которых будут использованы
            //for (int i = 0; i < Config.Instance.ObsSet.OservNumber; i++)
            foreach(DataGridViewRow row in dgv_1.Rows)
            {
                string s = Convert.ToString(row.Cells[2].Value);
                bool b = Convert.ToBoolean(row.Cells[1].Value);
                Config.Instance.ObsSet.SetUseObs(s, b);
            }

            Config.Instance.ObsSet.SetObservationToCore();
            Config.Instance.observeratories = Config.Instance.ObsSet.UsedObs2String();
        }

        //
        void ChangeTimeFrame()
        {
            var s1 = string.Empty;
            var s2 = string.Empty;
            Config.Instance.ObsSet.ChangeTimeFrame(pane, dgv_1, ref s1, ref s2, ref Config.Instance.obs_t0, ref Config.Instance.obs_te);

            tb_UTC_start.Text = s1;
            tb_UTC_finish.Text = s2;
            lb_numobs.Text = Config.Instance.ObsSet.getObsNum().ToString();
        }
       
        //
        private void zg_ObsView_ZoomEvent(ZedGraphControl sender, ZoomState oldState, ZoomState newState)
        {
            ChangeTimeFrame();
        }

        //
        private void tsmi_Check_Click(object sender, EventArgs e) => UpdateObservatories(true);
        //
        private void tsmi_UnCheck_Click(object sender, EventArgs e) => UpdateObservatories(false);

        private void UpdateObservatories(bool isUse)
        {
            foreach (DataGridViewRow row in dgv_1.SelectedRows)
                dgv_1.Rows[row.Index].Cells[1].Value = isUse;
        }

        private void ZgApplyFormatting()
        {
            pane.XAxis.Type = AxisType.Date;
            pane.Legend.IsVisible = IsShowLegend;

            pane.XAxis.Scale.MinAuto = true;
            pane.XAxis.Scale.MaxAuto = true;

            // Установим масштаб по умолчанию для оси Y
            pane.YAxis.Scale.MinAuto = true;
            pane.YAxis.Scale.MaxAuto = true;

            UpdateZedGraph();
        }

        private void UpdateZedGraph()
        {
            zg_ObsView.AxisChange();
            zg_ObsView.Invalidate();
        }

        private void FormatZedGraph()
        {
            zg_ObsView.IsShowPointValues = true;

            // Установим размеры шрифтов для меток вдоль осей
            pane.XAxis.Scale.FontSpec.Size = labelsXfontSize;
            pane.YAxis.Scale.FontSpec.Size = labelsYfontSize;

            // Установим размеры шрифтов для подписей по осям
            pane.XAxis.Title.FontSpec.Size = titleXFontSize;
            pane.YAxis.Title.FontSpec.Size = titleYFontSize;
            // Установим размеры шрифта для легенды
            pane.Legend.FontSpec.Size = legendFontSize;

            // Установим размеры шрифта для общего заголовка
            pane.Title.FontSpec.Size = mainTitleFontSize;

            //запрет на изменеие кегля
            pane.IsFontsScaled = true;

            //pane2.XAxis.MinorGrid.IsVisible =pane.XAxis.MinorGrid.IsVisible= true;
            //pane2.YAxis.MinorGrid.IsVisible =pane.YAxis.MinorGrid.IsVisible= true;

            pane.XAxis.MajorGrid.IsVisible = true;
            pane.YAxis.MajorGrid.IsVisible = true;

            pane.YAxis.MajorGrid.IsZeroLine = false;

            pane.Title.IsVisible = false;
            pane.Legend.IsVisible = true;
        }
    }
}
