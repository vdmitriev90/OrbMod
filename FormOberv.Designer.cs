namespace OrbModUI
{
    partial class OrbMod_FormOberv
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(OrbMod_FormOberv));
            this.cb_IsShowLegend = new System.Windows.Forms.CheckBox();
            this.lb_numobs = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.zg_ObsView = new ZedGraph.ZedGraphControl();
            this.dgv_1 = new System.Windows.Forms.DataGridView();
            this.col_01 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.col0 = new System.Windows.Forms.DataGridViewCheckBoxColumn();
            this.col1 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.col2 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.col3 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.col4 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.col5 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.csmi_1 = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.tsmi_Check = new System.Windows.Forms.ToolStripMenuItem();
            this.tsmi_UnCheck = new System.Windows.Forms.ToolStripMenuItem();
            this.label4 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.tb_UTC_start = new System.Windows.Forms.TextBox();
            this.tb_UTC_finish = new System.Windows.Forms.TextBox();
            this.bt_apply = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dgv_1)).BeginInit();
            this.csmi_1.SuspendLayout();
            this.SuspendLayout();
            // 
            // cb_IsShowLegend
            // 
            this.cb_IsShowLegend.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.cb_IsShowLegend.AutoSize = true;
            this.cb_IsShowLegend.Location = new System.Drawing.Point(624, 426);
            this.cb_IsShowLegend.Name = "cb_IsShowLegend";
            this.cb_IsShowLegend.Size = new System.Drawing.Size(94, 17);
            this.cb_IsShowLegend.TabIndex = 20;
            this.cb_IsShowLegend.Text = "Show legend?";
            this.cb_IsShowLegend.UseVisualStyleBackColor = true;
            this.cb_IsShowLegend.CheckedChanged += new System.EventHandler(this.cb_IsShowLegend_CheckedChanged);
            // 
            // lb_numobs
            // 
            this.lb_numobs.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.lb_numobs.AutoSize = true;
            this.lb_numobs.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lb_numobs.Location = new System.Drawing.Point(11, 432);
            this.lb_numobs.Name = "lb_numobs";
            this.lb_numobs.Size = new System.Drawing.Size(42, 13);
            this.lb_numobs.TabIndex = 18;
            this.lb_numobs.Text = "00000";
            // 
            // label2
            // 
            this.label2.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(376, 433);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(12, 13);
            this.label2.TabIndex = 17;
            this.label2.Text = "–";
            // 
            // splitContainer1
            // 
            this.splitContainer1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.splitContainer1.Location = new System.Drawing.Point(0, 0);
            this.splitContainer1.Name = "splitContainer1";
            this.splitContainer1.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.zg_ObsView);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.dgv_1);
            this.splitContainer1.Size = new System.Drawing.Size(802, 417);
            this.splitContainer1.SplitterDistance = 278;
            this.splitContainer1.SplitterWidth = 3;
            this.splitContainer1.TabIndex = 16;
            // 
            // zg_ObsView
            // 
            this.zg_ObsView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.zg_ObsView.IsShowCopyMessage = false;
            this.zg_ObsView.Location = new System.Drawing.Point(0, 0);
            this.zg_ObsView.Name = "zg_ObsView";
            this.zg_ObsView.ScrollGrace = 0D;
            this.zg_ObsView.ScrollMaxX = 0D;
            this.zg_ObsView.ScrollMaxY = 0D;
            this.zg_ObsView.ScrollMaxY2 = 0D;
            this.zg_ObsView.ScrollMinX = 0D;
            this.zg_ObsView.ScrollMinY = 0D;
            this.zg_ObsView.ScrollMinY2 = 0D;
            this.zg_ObsView.Size = new System.Drawing.Size(802, 278);
            this.zg_ObsView.TabIndex = 0;
            this.zg_ObsView.ZoomEvent += new ZedGraph.ZedGraphControl.ZoomEventHandler(this.zg_ObsView_ZoomEvent);
            // 
            // dgv_1
            // 
            this.dgv_1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgv_1.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.col_01,
            this.col0,
            this.col1,
            this.col2,
            this.col3,
            this.col4,
            this.col5});
            this.dgv_1.ContextMenuStrip = this.csmi_1;
            this.dgv_1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.dgv_1.Location = new System.Drawing.Point(0, 0);
            this.dgv_1.Name = "dgv_1";
            this.dgv_1.Size = new System.Drawing.Size(802, 136);
            this.dgv_1.TabIndex = 6;
            // 
            // col_01
            // 
            this.col_01.FillWeight = 25F;
            this.col_01.HeaderText = "#";
            this.col_01.Name = "col_01";
            this.col_01.ReadOnly = true;
            this.col_01.Width = 25;
            // 
            // col0
            // 
            this.col0.FillWeight = 30F;
            this.col0.HeaderText = "Use";
            this.col0.Name = "col0";
            this.col0.Width = 30;
            // 
            // col1
            // 
            this.col1.FillWeight = 30F;
            this.col1.HeaderText = "ID";
            this.col1.Name = "col1";
            this.col1.ReadOnly = true;
            this.col1.Width = 40;
            // 
            // col2
            // 
            this.col2.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.col2.HeaderText = "Name";
            this.col2.Name = "col2";
            // 
            // col3
            // 
            this.col3.HeaderText = "Num obs";
            this.col3.Name = "col3";
            this.col3.ReadOnly = true;
            // 
            // col4
            // 
            this.col4.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.col4.HeaderText = "First obs";
            this.col4.Name = "col4";
            this.col4.ReadOnly = true;
            // 
            // col5
            // 
            this.col5.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.col5.HeaderText = "Last obs";
            this.col5.Name = "col5";
            this.col5.ReadOnly = true;
            // 
            // csmi_1
            // 
            this.csmi_1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tsmi_Check,
            this.tsmi_UnCheck});
            this.csmi_1.Name = "csmi_1";
            this.csmi_1.Size = new System.Drawing.Size(121, 48);
            // 
            // tsmi_Check
            // 
            this.tsmi_Check.Name = "tsmi_Check";
            this.tsmi_Check.Size = new System.Drawing.Size(120, 22);
            this.tsmi_Check.Text = "Check";
            this.tsmi_Check.Click += new System.EventHandler(this.tsmi_Check_Click);
            // 
            // tsmi_UnCheck
            // 
            this.tsmi_UnCheck.Name = "tsmi_UnCheck";
            this.tsmi_UnCheck.Size = new System.Drawing.Size(120, 22);
            this.tsmi_UnCheck.Text = "Uncheck";
            this.tsmi_UnCheck.Click += new System.EventHandler(this.tsmi_UnCheck_Click);
            // 
            // label4
            // 
            this.label4.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(54, 432);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(160, 13);
            this.label4.TabIndex = 19;
            this.label4.Text = " total observations over interval: ";
            // 
            // label1
            // 
            this.label1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(547, 428);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(32, 13);
            this.label1.TabIndex = 15;
            this.label1.Text = " UTC";
            // 
            // tb_UTC_start
            // 
            this.tb_UTC_start.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.tb_UTC_start.Location = new System.Drawing.Point(220, 426);
            this.tb_UTC_start.Name = "tb_UTC_start";
            this.tb_UTC_start.Size = new System.Drawing.Size(150, 20);
            this.tb_UTC_start.TabIndex = 14;
            // 
            // tb_UTC_finish
            // 
            this.tb_UTC_finish.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.tb_UTC_finish.Location = new System.Drawing.Point(391, 426);
            this.tb_UTC_finish.Name = "tb_UTC_finish";
            this.tb_UTC_finish.Size = new System.Drawing.Size(150, 20);
            this.tb_UTC_finish.TabIndex = 13;
            // 
            // bt_apply
            // 
            this.bt_apply.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.bt_apply.Location = new System.Drawing.Point(724, 423);
            this.bt_apply.Name = "bt_apply";
            this.bt_apply.Size = new System.Drawing.Size(71, 23);
            this.bt_apply.TabIndex = 12;
            this.bt_apply.Text = "Apply";
            this.bt_apply.UseVisualStyleBackColor = true;
            this.bt_apply.Click += new System.EventHandler(this.bt_apply_Click);
            // 
            // OrbMod_FormOberv
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(807, 454);
            this.Controls.Add(this.cb_IsShowLegend);
            this.Controls.Add(this.lb_numobs);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.splitContainer1);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.tb_UTC_start);
            this.Controls.Add(this.tb_UTC_finish);
            this.Controls.Add(this.bt_apply);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MinimumSize = new System.Drawing.Size(789, 492);
            this.Name = "OrbMod_FormOberv";
            this.Text = "Observation View";
            this.Load += new System.EventHandler(this.OrbMod_FormOberv_Load);
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
            this.splitContainer1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.dgv_1)).EndInit();
            this.csmi_1.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.CheckBox cb_IsShowLegend;
        private System.Windows.Forms.Label lb_numobs;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.DataGridView dgv_1;
        private System.Windows.Forms.DataGridViewTextBoxColumn col_01;
        private System.Windows.Forms.DataGridViewCheckBoxColumn col0;
        private System.Windows.Forms.DataGridViewTextBoxColumn col1;
        private System.Windows.Forms.DataGridViewTextBoxColumn col2;
        private System.Windows.Forms.DataGridViewTextBoxColumn col3;
        private System.Windows.Forms.DataGridViewTextBoxColumn col4;
        private System.Windows.Forms.DataGridViewTextBoxColumn col5;
        private System.Windows.Forms.ContextMenuStrip csmi_1;
        private System.Windows.Forms.ToolStripMenuItem tsmi_Check;
        private System.Windows.Forms.ToolStripMenuItem tsmi_UnCheck;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox tb_UTC_start;
        private System.Windows.Forms.TextBox tb_UTC_finish;
        private System.Windows.Forms.Button bt_apply;
        private ZedGraph.ZedGraphControl zg_ObsView;
    }
}