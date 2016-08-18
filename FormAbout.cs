using System;
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
            string str = "OrbMod version:\t" + OrbModCLRWrapper.OrbModWrap.Instance.getVersion() + "\n";
            str += "OrbMod UI version:\t1.0\n";
            str += "Author:\t Vasily Dmitriev, Moscow, MIIGAiK MexLab";
            this.label1.Text = str;
        }
    }
}
