using System;
using System.Windows.Forms;
using ZedGraph;
using OrbModCLRWrapper;

namespace OrbModUI
{
    public partial class OrbMod_FormOberv : Form
    {
        int N = 0;
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

            zg_ObsView.AxisChange();
            zg_ObsView.Invalidate();
        }
        //
        private void OrbMod_FormOberv_Load(object sender, EventArgs e)
        {
            cb_IsShowLegend.Checked = IsShowLegend;

            #region zg
            zg_ObsView.IsShowPointValues = true;
            zg_assist(pane);
            #endregion

            Config.Instance.ObsSet.DataToForm(pane, dgv_1);
            string toobs = Config.Instance.ObsSet.TypeOfObserv();
            this.N = Config.Instance.ObsSet.N;

            #region zg
            pane.YAxis.Title.Text = "Observatory with " + toobs + " obs.";
            pane.XAxis.Title.Text = "time, UTC";
            pane.Legend.IsVisible = IsShowLegend;

            pane.XAxis.Type = AxisType.Date;

            pane.XAxis.Scale.MinAuto = true;
            pane.XAxis.Scale.MaxAuto = true;

            // Установим масштаб по умолчанию для оси Y
            pane.YAxis.Scale.MinAuto = true;
            pane.YAxis.Scale.MaxAuto = true;

            // Обновим данные об осях
            zg_ObsView.AxisChange();

            // Обновляем график
            zg_ObsView.Invalidate();
            #endregion

        }
        //
        private void bt_apply_Click(object sender, EventArgs e)
        {
            //Обсерватории наблюдения которых будут использованы
            for (int i = 0; i < N; i++)
            {
                string s = Convert.ToString(dgv_1.Rows[i].Cells[2].Value);
                bool b = Convert.ToBoolean(dgv_1.Rows[i].Cells[1].Value);
                Config.Instance.ObsSet.SetUseObs(s, b);

            }
            Config.Instance.ObsSet.SetObservationToCore();

            Config.Instance.observeratories = Config.Instance.ObsSet.UsedObs2String();
        }
        //
        void ChangeTimeFrame()
        {
            string s1 = "", s2 = "";
            Config.Instance.ObsSet.ChangeTimeFrame(pane, dgv_1, ref s1, ref s2, ref Config.Instance.obs_t0, ref Config.Instance.obs_te);
            tb_UTC_start.Text = s1; tb_UTC_finish.Text = s2;
            lb_numobs.Text = Config.Instance.ObsSet.getObsNum().ToString();
        }
        //
        private void zg_ObsView_ZoomEvent(ZedGraphControl sender, ZoomState oldState, ZoomState newState)
        {
            ChangeTimeFrame();
        }
        //
        private void tsmi_Check_Click(object sender, EventArgs e)
        {
            for (int i = 0; i < dgv_1.SelectedRows.Count; i++)
            {
                int j = dgv_1.SelectedRows[i].Index;
                dgv_1.Rows[j].Cells[1].Value = true;
            }
        }
        //
        private void tsmi_UnCheck_Click(object sender, EventArgs e)
        {
            for (int i = 0; i < dgv_1.SelectedRows.Count; i++)
            {
                int j = dgv_1.SelectedRows[i].Index;
                dgv_1.Rows[j].Cells[1].Value = false;
            }
        }
        //
        void zg_assist(GraphPane  pane)
        {
            int labelsXfontSize = 12;
            int labelsYfontSize = 12;

            int titleXFontSize = 14;
            int titleYFontSize = 14;

            int legendFontSize = 12;

            int mainTitleFontSize = 16;
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
