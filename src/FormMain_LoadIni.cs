using System;
using System.IO;
using System.Windows.Forms;
using OrbModCLRWrapper;
using static System.Math;

namespace OrbModUI
{
    public partial class OrbMod_FormMain : Form
    {
        private void tsmi_LoadCfg_Click(object sender, EventArgs e)
        {
            if (ofd_LoadConfig.ShowDialog() == DialogResult.OK)
            {
                LoadCfg(ofd_LoadConfig.FileName);
            }
        }
        private bool LoadCfg(string fileName)
        {
            if(!OrbModWrap.loadConfig(fileName))
                MessageBox.Show("ModOrb:\nFailed to load:\n OrbMod.ini\n");

            Config.Instance.ObsSet =_ObsSet.getObsSetFromOrbMod();

            if (!Config.Instance.LoadConfig(fileName))
                MessageBox.Show("UI.Config:\nFailed to load:\n OrbMod.ini\n");

            Config.Instance.SV = OrbModWrap.getIC(Config.Instance.IDC, (int)Config.Instance.ICType, (int)Config.Instance.ICFrame);
            Config.Instance.observeratories = Config.Instance.ObsSet.UsedObs2String();

            CfgToForm();

            return true;

        }

        private void CfgToForm()
        {
            notLoadCfgYet = true;

            cmb_var.SelectedIndex = (int)Config.Instance.var;
            cmb_OrbFitMode.SelectedIndex = (int)Config.Instance.fitMode;
            cmb_IDCB.Text = Config.Instance.IDC.ToString();

            //Earth Fixed Frame
            cmb_EFixedFrame.SelectedIndex = (int)Config.Instance.EarthFrame;

            //mode
            cmb_mode.SelectedIndex = (int)Config.Instance.mode;
            //TypeOfObs
            cmb_TypeOfObs.SelectedIndex = (int)Config.Instance.ObsType;
            //integrator		
            cmb_NOR.Text = Convert.ToString(Config.Instance.NOr);
            tb_step.Text = Convert.ToString(Config.Instance.Step);
            cb_AutoStep.Checked = Config.Instance.IsAutoStep;
            nud_eps.Value = Convert.ToDecimal(Config.Instance.Local_eps);

            cmb_InitFrame.SelectedIndex = (int)Config.Instance.ICFrame;
            cmb_TimeScale.SelectedIndex = (int)Config.Instance.Tframe;
            // Observations processing
            nud_OrbFitEps.Value = Convert.ToDecimal(Config.Instance.OrbFitEps);
            nud_MaxIter.Value = Convert.ToDecimal(Config.Instance.niter);
            nud_OrbFitMaxIter.Value = Convert.ToDecimal(Config.Instance.OrbFitMaxIter);
            //Outliers rejection
            cb_isRejectOtls.Checked = Config.Instance.isRejOuts;
            nud_OutlSigmaNum.Value = Convert.ToDecimal(Config.Instance.OutlsThresh);
            cb_rememb_Outl.Checked = Config.Instance.isMemOuts;
            //Filter settings
            nud_NumIterPerBatch.Value = Convert.ToDecimal(Config.Instance.maxIterPerBatch);
            tb_LengthOfArc.Text = Convert.ToString(Config.Instance.arcLength);
            nud_MinObsNumInBatch.Value = Convert.ToDecimal(Config.Instance.MinObsinBatch);
            tb_AprioryPosSig.Text = Convert.ToString(Config.Instance.PosRMS);
            tb_AprioryVelSigma.Text = Convert.ToString(Config.Instance.VelRMS);
            tb_AprioryObsSig.Text = Convert.ToString(Config.Instance.ObsSigma);
            tb_ProcessNoise.Text = Convert.ToString(Config.Instance.Qnoise);


            tb_UTC_begin.Text = (Config.Instance.s_t0);
            tb_UTC_end.Text = (Config.Instance.s_te);

            string[] ICs = Config.Instance.SV;

            tb_IC_1.Text = (ICs[0]);
            tb_IC_2.Text = (ICs[1]);
            tb_IC_3.Text = (ICs[2]);
            tb_IC_4.Text = (ICs[3]);
            tb_IC_5.Text = (ICs[4]);
            tb_IC_6.Text = (ICs[5]);

            cmb_TypeOfIC.SelectedIndex = (int)Config.Instance.ICType;
            cb_UseToPP.Checked = Config.Instance.IsUsePeriTime;

            //planets	 
            cb_10.Checked = Config.Instance.b_pl[9];
            cb_1.Checked = Config.Instance.b_pl[0];
            cb_2.Checked = Config.Instance.b_pl[1];
            cb_3.Checked = Config.Instance.b_pl[2];
            cb_4.Checked = Config.Instance.b_pl[3];
            cb_5.Checked = Config.Instance.b_pl[4];
            cb_6.Checked = Config.Instance.b_pl[5];
            cb_7.Checked = Config.Instance.b_pl[6];
            cb_8.Checked = Config.Instance.b_pl[7];
            cb_9.Checked = Config.Instance.b_pl[8];

            //addbody	
            cb_add1.Checked = Config.Instance.b_add[0];

            cb_add2.Checked = Config.Instance.b_add[1];
            cb_add3.Checked = Config.Instance.b_add[2];
            cb_add4.Checked = Config.Instance.b_add[3];
            cb_add5.Checked = Config.Instance.b_add[4];

            tb_add1.Text = (Config.Instance.id_add[0]).ToString();
            tb_add2.Text = (Config.Instance.id_add[1]).ToString();
            tb_add3.Text = (Config.Instance.id_add[2]).ToString();
            tb_add4.Text = (Config.Instance.id_add[3]).ToString();
            tb_add5.Text = (Config.Instance.id_add[4]).ToString();

            //hight terms of add5
            cb_add_cunn_ON.Checked = Config.Instance.b_add5Cnm;
            cmb_add_cun_N.Text = (Config.Instance.add5_N).ToString();
            tb_add_cun_file.Text = (Config.Instance.add5_FileModel);

            //hight terms of CB
            cb_Cunn.Checked = Config.Instance.b_CB_Cnm;
            tb_Cunn_N.Text = (Config.Instance.CB_N).ToString();
            tb_Cnm_file.Text = (Config.Instance.CB_FileModel);

            //tide ob CB

            //releff	 
            cb_rel.Checked = Config.Instance.b_rel;
            cb_L_T.Checked = Config.Instance.b_rel_LT;

            //SRP
            cb_SRP.Checked = Config.Instance.b_SRP;
            tb_SRP_albedo.Text = ((Config.Instance.SRP_albedo).ToString());
            tb_SRP_S.Text = ((Config.Instance.SRP_S).ToString());
            tb_SRP_Mass.Text = ((Config.Instance.SRP_Mass).ToString());
            //atmos

            //OUTPUT
            tb_DiscrOut.Text = Convert.ToString(Config.Instance.discr);
            cb_out_sv_J2000.Checked = Config.Instance.b_out_sv_J2000;
            cb_out_el_J2000.Checked = Config.Instance.b_out_el_J2000;
            cb_out_sv_ECLIPJ2000.Checked = Config.Instance.b_out_sv_ECLIPJ2000;
            cb_out_elts_ECLIPJ2000.Checked = Config.Instance.b_out_el_ECLIPJ2000;
            cb_out_sv_IAUPlanet.Checked = Config.Instance.b_out_sv_IAUPlanet;

            cb_out_acc.Checked = Config.Instance.b_out_acc;
            cb_out_BL.Checked = Config.Instance.b_out_BL;
            chb_3b_FixFr_sv.Checked = Config.Instance.b_3_BFF_sv;
            cb_out_postFitRes.Checked = Config.Instance.isLogRes;
            tb_3b_ff_num.Text = Config.Instance.ID_3_BFF_num.ToString();

            notLoadCfgYet = false;
        }

    }
}
