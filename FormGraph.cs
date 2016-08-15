using System;
using System.IO;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace OrbModUI
{

    public partial class OrbMod_FormGraph : Form
    {

        public enum PlotSourceData {Acc = 0, SV, Elts, Visi,Inegrator,_3_bodyFixFrame ,NotDefined};
        public enum Acc_vs_T { Accelerations = 0 };
        public enum SV_vs { X = 0, Y , Z, Vx, Vy, Vz, R, Vel ,XoY, XoZ, YoZ };
        public enum Elts_vs_T { SMA = 0,Ecc,Inc, Node,W,Mean, PeriDistance, ApoDistance };
        public enum Integ_vs_T { StepSize = 0, ItNum };
        public enum _3body_vs_T { X = 0, Y , Z, Vx, Vy , Vz, R ,V };


        private Dictionary<PlotSourceData, Type> Source2GraphCmb = new Dictionary<PlotSourceData, Type>()
        {
               {PlotSourceData.Acc, (Acc_vs_T.Accelerations).GetType() },
               {PlotSourceData.SV, (SV_vs.R).GetType() },
               {PlotSourceData.Elts, (Elts_vs_T.SMA).GetType() },
               {PlotSourceData.Inegrator, (Integ_vs_T.StepSize).GetType() },
               {PlotSourceData._3_bodyFixFrame, (_3body_vs_T.X).GetType() }

        };
        private Dictionary<string, PlotSourceData> str2PSD = new Dictionary<string, PlotSourceData>()
        {
            {"sv", PlotSourceData.SV },
            {"elts", PlotSourceData.Elts },
            {"acc", PlotSourceData.Acc },
            {"integ", PlotSourceData.Inegrator },
            {"3body_", PlotSourceData._3_bodyFixFrame }
        };
        string AppDir;
        public OrbMod_FormGraph()
        {
            InitializeComponent();
        }
        //
        private void butt_plot_Click(object sender, EventArgs e)
        {

        }
        //
        private void OrbMod_FormGraph_Load(object sender, EventArgs e)
        {
            string AppPath = System.Reflection.Assembly.GetExecutingAssembly().Location;
            AppDir = Path.GetDirectoryName(AppPath);
            string[] files = Directory.GetFiles(AppDir, "*.out");

            foreach (string it in files)
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
                var strs = Source2GraphCmb[psd].GetEnumNames();
                foreach (var value in strs)
                    cmb_PlotType.Items.Add(value);
                cmb_PlotType.SelectedIndex = 0;
            }
            else
                MessageBox.Show("There are not graphs for given file.");
        }

    }
}
