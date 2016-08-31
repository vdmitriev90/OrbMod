using System;
using System.IO;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using ZedGraph;

namespace OrbModUI
{

    public partial class OrbMod_FormGraph : Form
    {

        public enum PlotSourceData {Acc = 0, SV, Elts, Visi,Inegrator,_3_bodyFixFrame , Residuals, NotDefined};
        public enum Acc_vs_T { Accelerations = 0 };
        public enum SV_vs { X = 0, Y , Z, Vx, Vy, Vz, R, Vel ,XoY, XoZ, YoZ };
        public enum Elts_vs_T { SMA = 0,Ecc,Inc, Node,W,MeanAnomaly, PeriDistance, ApoDistance };
        public enum Integ_vs_T { StepSize = 0, ItNum };
        public enum _3body_vs_T { X = 0, Y, Z, Vx, Vy, Vz, R ,V };
        public enum Residuals { RightAccention,Declination, RAandDec,RAbyObservatory, DecbyObservatory };

        private PlotSpec currGraph;
        private string[] OutFiles;
        private PlotSourceData currSource;

        //
        private Dictionary<PlotSourceData, Type> Source2GraphCmb = new Dictionary<PlotSourceData, Type>()
        {
               {PlotSourceData.Acc, (Acc_vs_T.Accelerations).GetType() },
               {PlotSourceData.SV, (SV_vs.R).GetType() },
               {PlotSourceData.Elts, (Elts_vs_T.SMA).GetType() },
               {PlotSourceData.Inegrator, (Integ_vs_T.StepSize).GetType() },
               {PlotSourceData._3_bodyFixFrame, (_3body_vs_T.X).GetType() },
                 {PlotSourceData.Residuals, (Residuals.Declination).GetType() }

        };
        //
        private Dictionary<string, PlotSourceData> str2PSD = new Dictionary<string, PlotSourceData>()
        {
            {"sv", PlotSourceData.SV },
            {"elts", PlotSourceData.Elts },
            {"acc", PlotSourceData.Acc },
            {"integ", PlotSourceData.Inegrator },
            {"3body_", PlotSourceData._3_bodyFixFrame },
             {"residuals", PlotSourceData.Residuals }
        };
        string AppDir;
        public OrbMod_FormGraph()
        {
            InitializeComponent();
        }
        //
        private void butt_plot_Click(object sender, EventArgs e)
        {
            FormGraph_SetConfig();

            currGraph.SetInternalState(currSource, cmb_PlotType.SelectedIndex);

            currGraph.PlotData();
            currGraph.Autoscale();
        }
        //
        private void OrbMod_FormGraph_Load(object sender, EventArgs e)
        {
            FormGraphInit();
            cmb_fileInit();

        }
        //
        private void cmb_fileInit()
        {
            string AppPath = System.Reflection.Assembly.GetExecutingAssembly().Location;
            AppDir = Path.GetDirectoryName(AppPath);
            OutFiles = Directory.GetFiles(AppDir, "*.out");

            foreach (string it in OutFiles)
            {
                cmb_file.Items.Add(Path.GetFileNameWithoutExtension(it));
            }

            if (cmb_file.Items.Count > 0)
                cmb_file.SelectedIndex = 0;
        }
        //
        private bool str2PlotSourceData(string str, ref PlotSourceData psd)
        {
            foreach (var it in str2PSD)
            {
                if (str.Contains(it.Key))
                {
                    psd = it.Value;
                    return true;
                }
            }
            return false;
        }
        //
        private void SourseFileChange(object sender, EventArgs e)
        {
            cmb_PlotType.Items.Clear();
            PlotSourceData psd = PlotSourceData.NotDefined;
            if (str2PlotSourceData(cmb_file.SelectedItem.ToString(), ref psd))
            {
                currSource = psd;
                var strs = Source2GraphCmb[psd].GetEnumNames();
                foreach (var value in strs)
                    cmb_PlotType.Items.Add(value);
                cmb_PlotType.SelectedIndex = 0;

            }
            else
                MessageBox.Show("There are not graphs for given file.");

            string path = OutFiles[cmb_file.SelectedIndex];
           // zedGraphControl1 = new ZedGraphControl();
            currGraph = new PlotSpec(zedGraphControl1, path);

        }
        //
        private void FormGraphInit()
        {
            var strs = (ZedGraph.SymbolType.Circle).GetType().GetEnumNames();
            foreach (var value in strs)
                cmb_symbol.Items.Add(value);

            cmb_symbol.SelectedIndex = Config.Instance.SymbolType;

            nud_DotSize.Value = Config.Instance.SymbolSize;
            cb_isShowLines.Checked = Config.Instance.IsShowLines;
            nud_Wight.Value = Config.Instance.LineWidth;
            rb_AU.Checked = Config.Instance.UseAU;
            rb_Xaxis_calend.Checked = Config.Instance.UseCalend;
            nud_Smooth.Value = Convert.ToDecimal(Config.Instance.Tension);

            GraphPane pane = zedGraphControl1.GraphPane;

            int labelsXfontSize = 10;
            int labelsYfontSize = 10;

            int titleXFontSize = 12;
            int titleYFontSize = 12;

            int legendFontSize = 12;

            int mainTitleFontSize = 14;
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
            pane.IsFontsScaled = false;

            pane.XAxis.MajorGrid.IsVisible = true;
            pane.YAxis.MajorGrid.IsVisible = true;
            pane.YAxis.MajorGrid.IsZeroLine = false;
            //
            cmb_symbol.SelectedIndex = Config.Instance.SymbolType;
            nud_DotSize.Value = Convert.ToDecimal(Config.Instance.SymbolSize);
            nud_Wight.Value = Convert.ToDecimal(Config.Instance.LineWidth);
        }
        private void ChangeColor()
        {

            OrbMod_FormColorChange FM = new OrbMod_FormColorChange();
            FM.Owner = this;
            FM.Show();
        }

        private void OrbMod_FormGraph_FormClosing(object sender, FormClosingEventArgs e)
        {
            FormGraph_SetConfig();
        }

        private void FormGraph_SetConfig()
        {
            Config.Instance.SymbolType = cmb_symbol.SelectedIndex;
            Config.Instance.SymbolSize = Convert.ToInt32(nud_DotSize.Value);
            Config.Instance.IsShowLines = cb_isShowLines.Checked;
            
            Config.Instance.LineWidth = Convert.ToInt32(nud_Wight.Value);
            Config.Instance.UseAU = rb_AU.Checked;
            Config.Instance.UseCalend = rb_Xaxis_calend.Checked;
            Config.Instance.Tension = Convert.ToSingle(nud_Smooth.Value);

            Config.Instance.isSmoothGraph = (Config.Instance.Tension > 0);
        }

        private void zedGraphControl1_ZoomEvent(ZedGraphControl sender, ZoomState oldState, ZoomState newState)
        {
            currGraph.zgStateChange();
        }

        private void butt_AutoScale_Click(object sender, EventArgs e)
        {
            currGraph.Autoscale();
            currGraph.zgStateChange();
        }

        private void butt_ColorScheme_Click(object sender, EventArgs e)
        {
            ChangeColor();
        }

        private void zedGraphControl1_SizeChanged(object sender, EventArgs e)
        {
            currGraph.zgStateChange();
        }
    }

}
