using System;
using System.IO;
using System.Windows.Forms;
using OrbModCLRWrapper;

namespace OrbModUI
{
    public partial class OrbMod_FormMain : Form
    {
        private void cmb_TypeOfIC_SelectedIndexChanged(object sender, EventArgs e)
        {

            ChangeIC();
            if ((TypeOfIC)cmb_TypeOfIC.SelectedIndex == TypeOfIC.OrbitalElements)
            {
                lb_IC_1.Text = "a, km";
                lb_IC_2.Text = "e";
                lb_IC_3.Text = "i, deg";
                lb_IC_4.Text = "node, deg";
                lb_IC_5.Text = "peri, reg";
                lb_IC_6.Text = "M, deg";
            }
            else if ((TypeOfIC)cmb_TypeOfIC.SelectedIndex == TypeOfIC.StateVector)
            {
                lb_IC_1.Text = "X, km";
                lb_IC_2.Text = "Y, km";
                lb_IC_3.Text = "Z, km";
                lb_IC_4.Text = "Vx, km/s";
                lb_IC_5.Text = "Vy, km/s";
                lb_IC_6.Text = "Vz, km/s";
            }
        }
        //
        void ChangeIC()
        {
            if (!notLoadCfgYet)
            {
                int IDC = int.Parse(cmb_IDCB.Text);

                string[] IC_ = new string[6];

                IC_[0] = tb_IC_1.Text;
                IC_[1] = tb_IC_2.Text;
                IC_[2] = tb_IC_3.Text;
                IC_[3] = tb_IC_4.Text;
                IC_[4] = tb_IC_5.Text;
                IC_[5] = tb_IC_6.Text;

                OrbModWrap.setIC(IC_, IDC, (int)Config.Instance.ICType, (int)Config.Instance.ICFrame);

                Config.Instance.ICType = (TypeOfIC)cmb_TypeOfIC.SelectedIndex;
                Config.Instance.ICFrame = (FrameOfIC)cmb_InitFrame.SelectedIndex;

                string[] IC_out = OrbModWrap.getIC(IDC, (int)Config.Instance.ICType, (int)Config.Instance.ICFrame);
                

                tb_IC_1.Text = IC_out[0];
                tb_IC_2.Text = IC_out[1];
                tb_IC_3.Text = IC_out[2];
                tb_IC_4.Text = IC_out[3];
                tb_IC_5.Text = IC_out[4];
                tb_IC_6.Text = IC_out[5];

                Config.Instance.SV = OrbModWrap.getIC(IDC, (int)TypeOfIC.StateVector, (int)FrameOfIC.Equator_and_Equinox_J2000);

            }
        }
        private void bt_refresh_IC_Click(object sender, EventArgs e)
        {
            int IDC = int.Parse(cmb_IDCB.Text);
            Config.Instance.ICType = (TypeOfIC)cmb_TypeOfIC.SelectedIndex;
            Config.Instance.ICFrame = (FrameOfIC)cmb_InitFrame.SelectedIndex;

            string[] IC_out = OrbModWrap.getIC(IDC, (int)Config.Instance.ICType, (int)Config.Instance.ICFrame);

            tb_IC_1.Text = IC_out[0];
            tb_IC_2.Text = IC_out[1];
            tb_IC_3.Text = IC_out[2];
            tb_IC_4.Text = IC_out[3];
            tb_IC_5.Text = IC_out[4];
            tb_IC_6.Text = IC_out[5];

            Config.Instance.SV = OrbModWrap.getIC(IDC, (int)TypeOfIC.StateVector, (int)FrameOfIC.Equator_and_Equinox_J2000);
        }
        private void cmb_InitFrame_SelectedIndexChanged(object sender, EventArgs e)
        {
            ChangeIC();
        }

    }
}