using System;
using System.IO;
using System.Windows.Forms;
using OrbModCLRWrapper;

namespace OrbModUI
{
    public partial class OrbMod_FormMain : Form
    {
        //
        public void  SaveIni(string fileName)
        {
            CfgFromForm();

            Config.Instance.SV = OrbModWrap.getIC(Config.Instance.IDC, (int)TypeOfIC.StateVector, (int)FrameOfIC.Equator_and_Equinox_J2000);
            Config.Instance.observeratories = OrbModWrap.getUsedObs();

            Config.Instance.SaveConfig(fileName);
        }
        //
        private void tsmi_SaveCfg_Click(object sender, EventArgs e)
        {
            if (sfd_SaveConfig.ShowDialog() == DialogResult.OK)
            {
                SaveIni(sfd_SaveConfig.FileName);
            }
        }
        //
        public void CfgFromForm()
        {
            Config.Instance.var = (Variables)cmb_var.SelectedIndex;
            Config.Instance.fitMode = (FitMode)cmb_OrbFitMode.SelectedIndex;
            Config.Instance.IDC = int.Parse(cmb_IDCB.Text);

            //Earth Fixed Frame
            Config.Instance.EarthFrame = (EarthFixFrame)cmb_EFixedFrame.SelectedIndex;

            //mode
            Config.Instance.mode = (ProcessMode)cmb_mode.SelectedIndex;
            //TypeOfObs
            Config.Instance.ObsType = (TypeOfObs)cmb_TypeOfObs.SelectedIndex;
            //integrator
           Config.Instance.NOr = int.Parse(cmb_NOR.Text);
            Config.Instance.Step = int.Parse(tb_step.Text);
            Config.Instance.IsAutoStep = cb_AutoStep.Checked;
           Config.Instance.Local_eps = Convert.ToDouble(nud_eps.Value);

            Config.Instance.ICFrame = (FrameOfIC)(cmb_InitFrame.SelectedIndex);
            Config.Instance.ICType = (TypeOfIC)(cmb_TimeScale.SelectedIndex);
            // Observations processing
            Config.Instance.OrbFitEps = Convert.ToDouble(nud_OrbFitEps.Value);
            (Config.Instance.niter) = Convert.ToInt32(nud_MaxIter.Value);
            (Config.Instance.OrbFitMaxIter) = Convert.ToInt32(nud_OrbFitMaxIter.Value);
            //Outliers rejection
            Config.Instance.isRejOuts = cb_isRejectOtls.Checked;
            Config.Instance.OutlsThresh = Convert.ToSingle(nud_OutlSigmaNum.Value);
            Config.Instance.isMemOuts = cb_rememb_Outl.Checked;
            //Filter settings
            (Config.Instance.maxIterPerBatch) = Convert.ToInt32( nud_NumIterPerBatch.Value);
            (Config.Instance.arcLength) = Convert.ToInt32(tb_LengthOfArc.Text);
            (Config.Instance.MinObsinBatch) = Convert.ToInt32(nud_MinObsNumInBatch.Value);
            (Config.Instance.PosRMS) = Convert.ToDouble(tb_AprioryPosSig.Text);
            (Config.Instance.VelRMS) = Convert.ToDouble(tb_AprioryVelSigma.Text);
            (Config.Instance.ObsSigma) = Convert.ToDouble(tb_AprioryObsSig.Text);
            (Config.Instance.Qnoise) = Convert.ToDouble(tb_ProcessNoise.Text);


            (Config.Instance.s_t0) = tb_UTC_begin.Text;
            (Config.Instance.s_te) = tb_UTC_end.Text;

             string[] ICs = Config.Instance.SV;

            (ICs[0]) = tb_IC_1.Text;
            (ICs[1]) = tb_IC_2.Text;
            (ICs[2]) = tb_IC_3.Text;
            (ICs[3]) = tb_IC_4.Text;
            (ICs[4]) = tb_IC_5.Text;
            (ICs[5]) = tb_IC_6.Text;
            Config.Instance.SV = ICs;

            Config.Instance.ICType = (TypeOfIC)cmb_TypeOfIC.SelectedIndex;
            Config.Instance.IsUsePeriTime = cb_UseToPP.Checked;

            //planets
            Config.Instance.b_pl[9] = cb_10.Checked;
            Config.Instance.b_pl[0] = cb_1.Checked;
            Config.Instance.b_pl[1] = cb_2.Checked;
            Config.Instance.b_pl[2] = cb_3.Checked;
            Config.Instance.b_pl[3] = cb_4.Checked;
            Config.Instance.b_pl[4] = cb_5.Checked;
            Config.Instance.b_pl[5] = cb_6.Checked;
            Config.Instance.b_pl[6] = cb_7.Checked;
            Config.Instance.b_pl[7] = cb_8.Checked;
            Config.Instance.b_pl[8] = cb_9.Checked;

            //addbody
            Config.Instance.b_add[0] = cb_add1.Checked;
           // if(Config.Instance.b_add[0])
            (Config.Instance.id_add[0]) = int.Parse(tb_add1.Text);

            Config.Instance.b_add[1] = cb_add2.Checked;
           // if (Config.Instance.b_add[1])
                (Config.Instance.id_add[1]) = int.Parse(tb_add2.Text);

            Config.Instance.b_add[2] = cb_add3.Checked;
           // if (Config.Instance.b_add[2])
                (Config.Instance.id_add[2]) = int.Parse(tb_add3.Text);

            Config.Instance.b_add[3] = cb_add4.Checked;
            //if (Config.Instance.b_add[3])
                (Config.Instance.id_add[3]) = int.Parse(tb_add4.Text);

            Config.Instance.b_add[4] = cb_add5.Checked;
          //  if (Config.Instance.b_add[4])
                (Config.Instance.id_add[4]) = int.Parse(tb_add5.Text);

            //hight terms of add5
            Config.Instance.b_add5Cnm = cb_add_cunn_ON.Checked;
            //if (Config.Instance.b_add5Cnm)
            //{
                (Config.Instance.add5_N) = int.Parse(cmb_add_cun_N.Text);
                (Config.Instance.add5_FileModel) = tb_add_cun_file.Text;
            //}
            //hight terms of CB
            Config.Instance.b_CB_Cnm = cb_Cunn.Checked;
            //if (Config.Instance.b_CB_Cnm)
            //{
                (Config.Instance.CB_N) = int.Parse(tb_Cunn_N.Text);
                (Config.Instance.CB_FileModel) = tb_Cnm_file.Text;
           // }
            //tide ob CB

            //releff
            Config.Instance.b_rel = cb_rel.Checked;
            Config.Instance.b_rel_LT = cb_L_T.Checked;

            //SRP
            Config.Instance.b_SRP = cb_SRP.Checked;
            //if (Config.Instance.b_SRP)
            //{
                ((Config.Instance.SRP_albedo)) = double.Parse(tb_SRP_albedo.Text);
                ((Config.Instance.SRP_S)) = double.Parse(tb_SRP_S.Text);
                ((Config.Instance.SRP_Mass)) = double.Parse(tb_SRP_Mass.Text);
            //}
            //atmos

            //OUTPUT
            Config.Instance.discr = double.Parse(tb_DiscrOut.Text);
            Config.Instance.b_out_sv_J2000 = cb_out_sv_J2000.Checked;
            Config.Instance.b_out_el_J2000 = cb_out_el_J2000.Checked;
            Config.Instance.b_out_sv_ECLIPJ2000 = cb_out_sv_ECLIPJ2000.Checked;
            Config.Instance.b_out_el_ECLIPJ2000 = cb_out_elts_ECLIPJ2000.Checked;
            Config.Instance.b_out_sv_IAUPlanet = cb_out_sv_IAUPlanet.Checked;

            Config.Instance.b_out_acc = cb_out_acc.Checked;
            Config.Instance.b_out_BL = cb_out_BL.Checked;
            Config.Instance.b_3_BFF_sv = chb_3b_FixFr_sv.Checked;
            Config.Instance.isLogRes = cb_out_postFitRes.Checked;
            Config.Instance.ID_3_BFF_num = int.Parse(tb_3b_ff_num.Text);


        }

    }
}