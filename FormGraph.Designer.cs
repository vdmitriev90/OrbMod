namespace OrbModUI
{ 
    partial class OrbMod_FormGraph
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(OrbMod_FormGraph));
            this.cmb_symbol = new System.Windows.Forms.ComboBox();
            this.nud_DotSize = new System.Windows.Forms.NumericUpDown();
            this.label12 = new System.Windows.Forms.Label();
            this.butt_ColorScheme = new System.Windows.Forms.Button();
            this.nud_Wight = new System.Windows.Forms.NumericUpDown();
            this.nud_Smooth = new System.Windows.Forms.NumericUpDown();
            this.label9 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.rb_AU = new System.Windows.Forms.RadioButton();
            this.rb_km = new System.Windows.Forms.RadioButton();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.rb_Xaxis_calend = new System.Windows.Forms.RadioButton();
            this.rb_Xaxis_days = new System.Windows.Forms.RadioButton();
            this.butt_AutoScale = new System.Windows.Forms.Button();
            this.label14 = new System.Windows.Forms.Label();
            this.label13 = new System.Windows.Forms.Label();
            this.cmb_PlotType = new System.Windows.Forms.ComboBox();
            this.cmb_file = new System.Windows.Forms.ComboBox();
            this.butt_plot = new System.Windows.Forms.Button();
            this.zedGraphControl1 = new ZedGraph.ZedGraphControl();
            this.colorDialog1 = new System.Windows.Forms.ColorDialog();
            this.label1 = new System.Windows.Forms.Label();
            this.cb_isShowLines = new System.Windows.Forms.CheckBox();
            ((System.ComponentModel.ISupportInitialize)(this.nud_DotSize)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nud_Wight)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nud_Smooth)).BeginInit();
            this.groupBox2.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // cmb_symbol
            // 
            this.cmb_symbol.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmb_symbol.FormattingEnabled = true;
            this.cmb_symbol.Location = new System.Drawing.Point(6, 122);
            this.cmb_symbol.Name = "cmb_symbol";
            this.cmb_symbol.Size = new System.Drawing.Size(118, 21);
            this.cmb_symbol.TabIndex = 32;
            // 
            // nud_DotSize
            // 
            this.nud_DotSize.Location = new System.Drawing.Point(6, 284);
            this.nud_DotSize.Maximum = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.nud_DotSize.Name = "nud_DotSize";
            this.nud_DotSize.Size = new System.Drawing.Size(45, 20);
            this.nud_DotSize.TabIndex = 31;
            this.nud_DotSize.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(58, 287);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(45, 13);
            this.label12.TabIndex = 30;
            this.label12.Text = "Dot size";
            // 
            // butt_ColorScheme
            // 
            this.butt_ColorScheme.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.butt_ColorScheme.Location = new System.Drawing.Point(1, 376);
            this.butt_ColorScheme.Name = "butt_ColorScheme";
            this.butt_ColorScheme.Size = new System.Drawing.Size(123, 20);
            this.butt_ColorScheme.TabIndex = 28;
            this.butt_ColorScheme.Text = "Color Scheme";
            this.butt_ColorScheme.UseVisualStyleBackColor = true;
            this.butt_ColorScheme.Click += new System.EventHandler(this.butt_ColorScheme_Click);
            // 
            // nud_Wight
            // 
            this.nud_Wight.Location = new System.Drawing.Point(6, 261);
            this.nud_Wight.Maximum = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.nud_Wight.Name = "nud_Wight";
            this.nud_Wight.Size = new System.Drawing.Size(45, 20);
            this.nud_Wight.TabIndex = 27;
            this.nud_Wight.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // nud_Smooth
            // 
            this.nud_Smooth.DecimalPlaces = 1;
            this.nud_Smooth.Increment = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            this.nud_Smooth.Location = new System.Drawing.Point(6, 306);
            this.nud_Smooth.Maximum = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.nud_Smooth.Name = "nud_Smooth";
            this.nud_Smooth.Size = new System.Drawing.Size(45, 20);
            this.nud_Smooth.TabIndex = 26;
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(58, 312);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(51, 13);
            this.label9.TabIndex = 25;
            this.label9.Text = "Smooting";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(58, 264);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(55, 13);
            this.label8.TabIndex = 24;
            this.label8.Text = "Line wigth";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.rb_AU);
            this.groupBox2.Controls.Add(this.rb_km);
            this.groupBox2.Location = new System.Drawing.Point(6, 204);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(77, 51);
            this.groupBox2.TabIndex = 23;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Units";
            // 
            // rb_AU
            // 
            this.rb_AU.AutoSize = true;
            this.rb_AU.Location = new System.Drawing.Point(6, 31);
            this.rb_AU.Name = "rb_AU";
            this.rb_AU.Size = new System.Drawing.Size(68, 17);
            this.rb_AU.TabIndex = 1;
            this.rb_AU.Text = "AU, days";
            this.rb_AU.UseVisualStyleBackColor = true;
            // 
            // rb_km
            // 
            this.rb_km.AutoSize = true;
            this.rb_km.Checked = true;
            this.rb_km.Location = new System.Drawing.Point(6, 12);
            this.rb_km.Name = "rb_km";
            this.rb_km.Size = new System.Drawing.Size(69, 17);
            this.rb_km.TabIndex = 0;
            this.rb_km.TabStop = true;
            this.rb_km.Text = "km, km/s";
            this.rb_km.UseVisualStyleBackColor = true;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.rb_Xaxis_calend);
            this.groupBox1.Controls.Add(this.rb_Xaxis_days);
            this.groupBox1.Location = new System.Drawing.Point(6, 149);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(118, 53);
            this.groupBox1.TabIndex = 22;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Time axis format";
            // 
            // rb_Xaxis_calend
            // 
            this.rb_Xaxis_calend.AutoSize = true;
            this.rb_Xaxis_calend.Location = new System.Drawing.Point(6, 32);
            this.rb_Xaxis_calend.Name = "rb_Xaxis_calend";
            this.rb_Xaxis_calend.Size = new System.Drawing.Size(107, 17);
            this.rb_Xaxis_calend.TabIndex = 6;
            this.rb_Xaxis_calend.TabStop = true;
            this.rb_Xaxis_calend.Text = "Formant calendar";
            this.rb_Xaxis_calend.UseVisualStyleBackColor = false;
            // 
            // rb_Xaxis_days
            // 
            this.rb_Xaxis_days.AutoSize = true;
            this.rb_Xaxis_days.Checked = true;
            this.rb_Xaxis_days.Location = new System.Drawing.Point(6, 13);
            this.rb_Xaxis_days.Name = "rb_Xaxis_days";
            this.rb_Xaxis_days.Size = new System.Drawing.Size(72, 17);
            this.rb_Xaxis_days.TabIndex = 5;
            this.rb_Xaxis_days.TabStop = true;
            this.rb_Xaxis_days.Text = "TDB days";
            this.rb_Xaxis_days.UseVisualStyleBackColor = true;
            // 
            // butt_AutoScale
            // 
            this.butt_AutoScale.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.butt_AutoScale.Location = new System.Drawing.Point(2, 400);
            this.butt_AutoScale.Name = "butt_AutoScale";
            this.butt_AutoScale.Size = new System.Drawing.Size(122, 22);
            this.butt_AutoScale.TabIndex = 21;
            this.butt_AutoScale.Text = "Autoscale";
            this.butt_AutoScale.UseVisualStyleBackColor = true;
            this.butt_AutoScale.Click += new System.EventHandler(this.butt_AutoScale_Click);
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(9, 53);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(36, 13);
            this.label14.TabIndex = 84;
            this.label14.Text = "Graph";
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(9, 9);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(23, 13);
            this.label13.TabIndex = 83;
            this.label13.Text = "File";
            // 
            // cmb_PlotType
            // 
            this.cmb_PlotType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmb_PlotType.FormattingEnabled = true;
            this.cmb_PlotType.Location = new System.Drawing.Point(6, 73);
            this.cmb_PlotType.Name = "cmb_PlotType";
            this.cmb_PlotType.Size = new System.Drawing.Size(118, 21);
            this.cmb_PlotType.TabIndex = 82;
            // 
            // cmb_file
            // 
            this.cmb_file.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmb_file.FormattingEnabled = true;
            this.cmb_file.Location = new System.Drawing.Point(6, 29);
            this.cmb_file.Name = "cmb_file";
            this.cmb_file.Size = new System.Drawing.Size(118, 21);
            this.cmb_file.TabIndex = 81;
            this.cmb_file.SelectedIndexChanged += new System.EventHandler(this.SourseFileChange);
            // 
            // butt_plot
            // 
            this.butt_plot.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.butt_plot.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.butt_plot.Location = new System.Drawing.Point(1, 427);
            this.butt_plot.Name = "butt_plot";
            this.butt_plot.Size = new System.Drawing.Size(123, 23);
            this.butt_plot.TabIndex = 19;
            this.butt_plot.Text = "Plot";
            this.butt_plot.UseVisualStyleBackColor = true;
            this.butt_plot.Click += new System.EventHandler(this.butt_plot_Click);
            // 
            // zedGraphControl1
            // 
            this.zedGraphControl1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.zedGraphControl1.IsShowCopyMessage = false;
            this.zedGraphControl1.Location = new System.Drawing.Point(130, 3);
            this.zedGraphControl1.Name = "zedGraphControl1";
            this.zedGraphControl1.ScrollGrace = 0D;
            this.zedGraphControl1.ScrollMaxX = 0D;
            this.zedGraphControl1.ScrollMaxY = 0D;
            this.zedGraphControl1.ScrollMaxY2 = 0D;
            this.zedGraphControl1.ScrollMinX = 0D;
            this.zedGraphControl1.ScrollMinY = 0D;
            this.zedGraphControl1.ScrollMinY2 = 0D;
            this.zedGraphControl1.Size = new System.Drawing.Size(611, 451);
            this.zedGraphControl1.TabIndex = 33;
            this.zedGraphControl1.ZoomEvent += new ZedGraph.ZedGraphControl.ZoomEventHandler(this.zedGraphControl1_ZoomEvent);
            this.zedGraphControl1.SizeChanged += new System.EventHandler(this.zedGraphControl1_SizeChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(7, 105);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(68, 13);
            this.label1.TabIndex = 85;
            this.label1.Text = "Symbol Type";
            // 
            // cb_isShowLines
            // 
            this.cb_isShowLines.AutoSize = true;
            this.cb_isShowLines.Location = new System.Drawing.Point(6, 332);
            this.cb_isShowLines.Name = "cb_isShowLines";
            this.cb_isShowLines.Size = new System.Drawing.Size(81, 17);
            this.cb_isShowLines.TabIndex = 86;
            this.cb_isShowLines.Text = "Show Lines";
            this.cb_isShowLines.UseVisualStyleBackColor = true;
            // 
            // OrbMod_FormGraph
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(741, 456);
            this.Controls.Add(this.cb_isShowLines);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.label14);
            this.Controls.Add(this.zedGraphControl1);
            this.Controls.Add(this.label13);
            this.Controls.Add(this.cmb_PlotType);
            this.Controls.Add(this.cmb_symbol);
            this.Controls.Add(this.cmb_file);
            this.Controls.Add(this.nud_DotSize);
            this.Controls.Add(this.label12);
            this.Controls.Add(this.butt_ColorScheme);
            this.Controls.Add(this.nud_Wight);
            this.Controls.Add(this.nud_Smooth);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.butt_AutoScale);
            this.Controls.Add(this.butt_plot);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MinimumSize = new System.Drawing.Size(757, 461);
            this.Name = "OrbMod_FormGraph";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.OrbMod_FormGraph_FormClosing);
            this.Load += new System.EventHandler(this.OrbMod_FormGraph_Load);
            ((System.ComponentModel.ISupportInitialize)(this.nud_DotSize)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nud_Wight)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nud_Smooth)).EndInit();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox cmb_symbol;
        private System.Windows.Forms.NumericUpDown nud_DotSize;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Button butt_ColorScheme;
        private System.Windows.Forms.NumericUpDown nud_Wight;
        private System.Windows.Forms.NumericUpDown nud_Smooth;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.RadioButton rb_AU;
        private System.Windows.Forms.RadioButton rb_km;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.RadioButton rb_Xaxis_calend;
        private System.Windows.Forms.RadioButton rb_Xaxis_days;
        private System.Windows.Forms.Button butt_AutoScale;
        private System.Windows.Forms.Button butt_plot;
        private ZedGraph.ZedGraphControl zedGraphControl1;
        private System.Windows.Forms.ComboBox cmb_PlotType;
        private System.Windows.Forms.ComboBox cmb_file;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.ColorDialog colorDialog1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.CheckBox cb_isShowLines;
    }
}