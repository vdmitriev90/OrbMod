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
        string AppDir;
        public OrbMod_FormGraph()
        {
            InitializeComponent();
        }

        private void butt_plot_Click(object sender, EventArgs e)
        {

        }

        private void OrbMod_FormGraph_Load(object sender, EventArgs e)
        {
            string AppPath = System.Reflection.Assembly.GetExecutingAssembly().Location;
            AppDir = Path.GetDirectoryName(AppPath);
            string[] files = Directory.GetFiles(AppDir, "*.out");
            foreach(string it in files)
            {
                cmb_file.Items.Add(Path.GetFileName(it));

            }

            if (cmb_file.Items.Count > 0)
                cmb_file.SelectedIndex = 0;



        }
        
    }
}
