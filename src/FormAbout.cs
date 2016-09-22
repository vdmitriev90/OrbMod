using System;
using System.Windows.Forms;
using OrbModCLRWrapper;

namespace OrbModUI
{
    public partial class OrbMod_FormAbout : Form
    {
        public OrbMod_FormAbout()
        {
            InitializeComponent();
        }

        private void bt_close_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void OrbMod_FormAbout_Load(object sender, EventArgs e)
        {
            string str = "OrbMod version:\t" + OrbModWrap.getVersion() + "\n";
            str += "OrbMod UI version:\t1.0\n";
            str += "Author:\t Vasily Dmitriev, Moscow, MIIGAiK MexLab";
            this.label1.Text = str;
        }
    }
}
