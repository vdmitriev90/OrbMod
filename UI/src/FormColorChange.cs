using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace OrbModUI
{
    public partial class OrbMod_FormColorChange : Form
    {
        //
        public OrbMod_FormColorChange()
        {
            InitializeComponent();
        }
        //
        private void col_Main_MouseClick(object sender, MouseEventArgs e)
        {
            Panel lb = sender as Panel;
            if (colorDialog1.ShowDialog() == DialogResult.OK)
                lb.BackColor = colorDialog1.Color;

            setcol();
            getcol();
        }
        //
        void  setcol()
        {
            Config.Instance.col_Main = col_Main.BackColor.ToArgb();
            Config.Instance.ColorsAcc[0] = col_CB.BackColor.ToArgb();
            Config.Instance.ColorsAcc[1] = col_CB_HT.BackColor.ToArgb();
            Config.Instance.ColorsAcc[2] = col_Sun.BackColor.ToArgb();
            Config.Instance.ColorsAcc[3] = col_Merc.BackColor.ToArgb();
            Config.Instance.ColorsAcc[4] = col_Ven.BackColor.ToArgb();
            Config.Instance.ColorsAcc[5] = col_Earth.BackColor.ToArgb();
            Config.Instance.ColorsAcc[6] = col_Mars.BackColor.ToArgb();
            Config.Instance.ColorsAcc[7] = col_Jup.BackColor.ToArgb();
            Config.Instance.ColorsAcc[8] = col_Sat.BackColor.ToArgb();
            Config.Instance.ColorsAcc[9] = col_Ur.BackColor.ToArgb();
            Config.Instance.ColorsAcc[10] = col_Nep.BackColor.ToArgb();
            Config.Instance.ColorsAcc[11] = col_Pluto.BackColor.ToArgb();
            Config.Instance.ColorsAcc[12] = col_add1.BackColor.ToArgb();
            Config.Instance.ColorsAcc[13] = col_add2.BackColor.ToArgb();
            Config.Instance.ColorsAcc[14] = col_add3.BackColor.ToArgb();
            Config.Instance.ColorsAcc[15] = col_add4.BackColor.ToArgb();
            Config.Instance.ColorsAcc[16] = col_add5.BackColor.ToArgb();
            Config.Instance.ColorsAcc[17] = col_Add5_HT.BackColor.ToArgb();
            Config.Instance.ColorsAcc[18] = col_Rel1.BackColor.ToArgb();
            Config.Instance.ColorsAcc[19] = col_Rel2.BackColor.ToArgb();
            Config.Instance.ColorsAcc[20] = col_SRP.BackColor.ToArgb();
            Config.Instance.ColorsAcc[21] = col_Atm.BackColor.ToArgb();
        }
        //
        void getcol()
        {
            col_Main.BackColor = Color.FromArgb(Config.Instance.col_Main);
            col_CB.BackColor = Color.FromArgb(Config.Instance.ColorsAcc[0]);
            col_CB_HT.BackColor = Color.FromArgb(Config.Instance.ColorsAcc[1]);
            col_Sun.BackColor = Color.FromArgb(Config.Instance.ColorsAcc[2]);
            col_Merc.BackColor = Color.FromArgb(Config.Instance.ColorsAcc[3]);
            col_Ven.BackColor = Color.FromArgb(Config.Instance.ColorsAcc[4]);
            col_Earth.BackColor = Color.FromArgb(Config.Instance.ColorsAcc[5]);
            col_Mars.BackColor = Color.FromArgb(Config.Instance.ColorsAcc[6]);
            col_Jup.BackColor = Color.FromArgb(Config.Instance.ColorsAcc[7]);
            col_Sat.BackColor = Color.FromArgb(Config.Instance.ColorsAcc[8]);
            col_Ur.BackColor = Color.FromArgb(Config.Instance.ColorsAcc[9]);
            col_Nep.BackColor = Color.FromArgb(Config.Instance.ColorsAcc[10]);
            col_Pluto.BackColor = Color.FromArgb(Config.Instance.ColorsAcc[11]);
            col_add1.BackColor = Color.FromArgb(Config.Instance.ColorsAcc[12]);
            col_add2.BackColor = Color.FromArgb(Config.Instance.ColorsAcc[13]);
            col_add3.BackColor = Color.FromArgb(Config.Instance.ColorsAcc[14]);
            col_add4.BackColor = Color.FromArgb(Config.Instance.ColorsAcc[15]);
            col_add5.BackColor = Color.FromArgb(Config.Instance.ColorsAcc[16]);
            col_Add5_HT.BackColor = Color.FromArgb(Config.Instance.ColorsAcc[17]);
            col_Rel1.BackColor = Color.FromArgb(Config.Instance.ColorsAcc[18]);
            col_Rel2.BackColor = Color.FromArgb(Config.Instance.ColorsAcc[19]);
            col_SRP.BackColor = Color.FromArgb(Config.Instance.ColorsAcc[20]);
            col_Atm.BackColor = Color.FromArgb(Config.Instance.ColorsAcc[21]);
        }
        //
        private void OrbMod_FormColorChange_Load(object sender, EventArgs e)
        {
            getcol();
        }
        //
        private void OrbMod_FormColorChange_FormClosing(object sender, FormClosingEventArgs e)
        {
            setcol();
        }
    }
}
