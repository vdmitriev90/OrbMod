namespace OrbModUI
{
    partial class OrbMod_FormAbout
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
            this.label1 = new System.Windows.Forms.Label();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.bt_close = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(8, 14);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(35, 13);
            this.label1.TabIndex = 5;
            this.label1.Text = "label1";
            // 
            // textBox1
            // 
            this.textBox1.AcceptsReturn = true;
            this.textBox1.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.textBox1.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.textBox1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Underline, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.textBox1.ForeColor = System.Drawing.Color.Blue;
            this.textBox1.Location = new System.Drawing.Point(48, 49);
            this.textBox1.MaximumSize = new System.Drawing.Size(142, 20);
            this.textBox1.MinimumSize = new System.Drawing.Size(142, 20);
            this.textBox1.Multiline = true;
            this.textBox1.Name = "textBox1";
            this.textBox1.ReadOnly = true;
            this.textBox1.Size = new System.Drawing.Size(142, 20);
            this.textBox1.TabIndex = 4;
            this.textBox1.Text = "v_dmitriev@miigaik.ru";
            // 
            // bt_close
            // 
            this.bt_close.Location = new System.Drawing.Point(68, 72);
            this.bt_close.Name = "bt_close";
            this.bt_close.Size = new System.Drawing.Size(93, 23);
            this.bt_close.TabIndex = 3;
            this.bt_close.Text = "OK";
            this.bt_close.UseVisualStyleBackColor = true;
            this.bt_close.Click += new System.EventHandler(this.bt_close_Click);
            // 
            // OrbMod_FormAbout
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(260, 97);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.bt_close);
            this.Name = "OrbMod_FormAbout";
            this.Text = "About";
            this.Load += new System.EventHandler(this.OrbMod_FormAbout_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Button bt_close;
    }
}