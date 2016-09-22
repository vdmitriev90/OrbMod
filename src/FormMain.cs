using System;
using System.Drawing;
using System.IO;
using System.Windows.Forms;
using OrbModCLRWrapper;
using static OrbModUI.Config;

namespace OrbModUI
{
    public partial class OrbMod_FormMain : Form
    {
        bool notLoadCfgYet = true;

        string kernelPath;
        string observatoriesPath;
        string cfgPath;

        System.Diagnostics.Stopwatch timer = new System.Diagnostics.Stopwatch();
        //
        public OrbMod_FormMain()
        {
            InitializeComponent();
        }
        //
        private void OrbMod_FormMain_Load(object sender, EventArgs e)
        {
            this.Text += OrbModWrap.getVersion();

            foreach (var value in Enum.GetValues(typeof(FitMode)))
                cmb_OrbFitMode.Items.Add(((FitMode)value).ToString());

            foreach (var value in Enum.GetValues(typeof(TypeOfObs)))
                cmb_TypeOfObs.Items.Add(((TypeOfObs)value).ToString());

            foreach (var value in Enum.GetValues(typeof(ProcessMode)))
                cmb_mode.Items.Add(((ProcessMode)value).ToString());

            foreach (var value in Enum.GetValues(typeof(Variables)))
                cmb_var.Items.Add(((Variables)value).ToString());

            foreach (var value in Enum.GetValues(typeof(EarthFixFrame)))
                cmb_EFixedFrame.Items.Add(((EarthFixFrame)value).ToString());

            foreach (var value in Enum.GetValues(typeof(TypeOfIC)))
                cmb_TypeOfIC.Items.Add(((TypeOfIC)value).ToString());

            foreach (var value in Enum.GetValues(typeof(FrameOfIC)))
                cmb_InitFrame.Items.Add(((FrameOfIC)value).ToString());

            foreach (var value in Enum.GetValues(typeof(TimeFormat)))
                cmb_TimeScale.Items.Add(((TimeFormat)value).ToString());

            string AppPath = System.Reflection.Assembly.GetExecutingAssembly().Location;
            string AppDir = Path.GetDirectoryName(AppPath);

             kernelPath = Path.Combine(AppDir, "metak.tm");
             observatoriesPath = Path.Combine(AppDir, "observatories.txt");
             cfgPath = Path.Combine(AppDir, "OrbMod.ini");

            if (!OrbModWrap.loadKernels(kernelPath))
                MessageBox.Show("ModOrb:\nFailed to load:\n metak.tm\n");
            if (!OrbModWrap.loadObservatories(observatoriesPath))
                MessageBox.Show("ModOrb:\nFailed to load:\n observatories.txt\n");

            if (!LoadCfg(cfgPath))
                MessageBox.Show("UI.FormMain:\nFailed to load:\n OrbMod.ini\n");


            if (System.IO.File.Exists(Config.Instance.ObsPath))
                Config.Instance.ObsSet.LoadObs(Config.Instance.ObsPath,(int)Config.Instance.ObsType);

        }
        //
        private void tsmi_Plot_Click(object sender, EventArgs e)
        {
            OrbMod_FormGraph fm = new OrbMod_FormGraph();
            fm.Owner = this;
            fm.Show();
        }
        //
        private void tsmi_ObsView_Click(object sender, EventArgs e)
        {
            OrbMod_FormOberv fm = new OrbMod_FormOberv();
            fm.Owner = this;
            fm.Show();
        }
        //
        private void tsmi_LoadObs_Click(object sender, EventArgs e)
        {
            if (ofd_Obs.ShowDialog() == DialogResult.OK)
            {
                string fname = ofd_Obs.FileName;
                int ObsT = cmb_TypeOfObs.SelectedIndex;
                Config.Instance.ObsSet.LoadObs(fname,ObsT);
                Config.Instance.ObsSet.SetObservationToCore();
               // Config.Instance.ObsSet = new _ObsSet();
                Config.Instance.observeratories = Config.Instance.ObsSet.UsedObs2String();

                Config.Instance.ObsPath = fname;
            }
        }
        //
        private void aboutToolStripMenuItem_Click_1(object sender, EventArgs e)
        {
            OrbMod_FormAbout fm = new OrbMod_FormAbout();
            fm.Owner = this;
            fm.Show();
        }
        //
        private void butt_add_cun_choose_file_Click(object sender, EventArgs e)
        {
            if (select_gravity_model.ShowDialog() == DialogResult.OK)
            {
                tb_add_cun_file.Text = select_gravity_model.FileName;
            }
        }
        //
        private void bt_Cnm_file_Click(object sender, EventArgs e)
        {
            if (select_gravity_model.ShowDialog() == DialogResult.OK)
            {
                tb_Cnm_file.Text = select_gravity_model.FileName;
            }
        }
        //
        private void OrbMod_FormMain_FormClosing(object sender, FormClosingEventArgs e)
        { try
            {
                SaveIni(cfgPath);
            }
            catch(Exception ex)
            {
                string ex_text = "An Error has occured.\n" + ex.Message + "\n";
                ex_text += "Call stack\n" + ex.StackTrace + "\n";
                MessageBox.Show(ex_text);
                this.Close();
            }
        }
        //
        private void button1_Click(object sender, EventArgs e)
        {
            SaveIni(cfgPath);
            toolStripStatusLabel1.ForeColor = Color.Red;
            toolStripStatusLabel1.Text = "In Progress";
            if (bgw_1.IsBusy != true)
            {
                // Start the asynchronous operation.
                bgw_1.RunWorkerAsync();
            }
        }
        //
        private void bgw_1_DoWork(object sender, System.ComponentModel.DoWorkEventArgs e)
        {
            timer.Reset();
            timer.Start();
            OrbModWrap.Process(cfgPath);
        }
        //
        private void bgw_1_RunWorkerCompleted(object sender, System.ComponentModel.RunWorkerCompletedEventArgs e)
        {
            toolStripStatusLabel1.ForeColor = Color.Green;
            toolStripStatusLabel1.Text = "Done!";
            timer.Stop();
            double sec = Convert.ToDouble(timer.ElapsedMilliseconds)/1000.0;
            toolStripStatusLabel2.Text = sec.ToString("F1");
        }
    }
}
