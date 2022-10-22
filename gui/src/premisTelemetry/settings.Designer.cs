namespace premisTelemetry
{
    partial class settings
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

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.panel1 = new System.Windows.Forms.Panel();
            this.State_Panel = new System.Windows.Forms.Panel();
            this.METAR_SETTING_Label = new System.Windows.Forms.Label();
            this.backGround_Panel = new System.Windows.Forms.Panel();
            this.Metar_Setting_TextBox = new System.Windows.Forms.TextBox();
            this.metarEnter = new System.Windows.Forms.Button();
            this.panel1.SuspendLayout();
            this.State_Panel.SuspendLayout();
            this.SuspendLayout();
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.metarEnter);
            this.panel1.Controls.Add(this.Metar_Setting_TextBox);
            this.panel1.Controls.Add(this.State_Panel);
            this.panel1.Location = new System.Drawing.Point(23, 32);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(342, 172);
            this.panel1.TabIndex = 3;
            // 
            // State_Panel
            // 
            this.State_Panel.BackColor = System.Drawing.Color.White;
            this.State_Panel.Controls.Add(this.METAR_SETTING_Label);
            this.State_Panel.Location = new System.Drawing.Point(3, 3);
            this.State_Panel.Name = "State_Panel";
            this.State_Panel.Size = new System.Drawing.Size(336, 58);
            this.State_Panel.TabIndex = 0;
            // 
            // METAR_SETTING_Label
            // 
            this.METAR_SETTING_Label.Font = new System.Drawing.Font("Unispace", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.METAR_SETTING_Label.Location = new System.Drawing.Point(73, 20);
            this.METAR_SETTING_Label.Name = "METAR_SETTING_Label";
            this.METAR_SETTING_Label.Size = new System.Drawing.Size(209, 19);
            this.METAR_SETTING_Label.TabIndex = 0;
            this.METAR_SETTING_Label.Text = "METAR";
            this.METAR_SETTING_Label.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // backGround_Panel
            // 
            this.backGround_Panel.BackColor = System.Drawing.Color.White;
            this.backGround_Panel.Location = new System.Drawing.Point(20, 29);
            this.backGround_Panel.Name = "backGround_Panel";
            this.backGround_Panel.Size = new System.Drawing.Size(348, 178);
            this.backGround_Panel.TabIndex = 4;
            // 
            // Metar_Setting_TextBox
            // 
            this.Metar_Setting_TextBox.Location = new System.Drawing.Point(90, 93);
            this.Metar_Setting_TextBox.Name = "Metar_Setting_TextBox";
            this.Metar_Setting_TextBox.Size = new System.Drawing.Size(155, 20);
            this.Metar_Setting_TextBox.TabIndex = 1;
            this.Metar_Setting_TextBox.TextChanged += new System.EventHandler(this.Metar_Setting_TextBox_TextChanged);
            // 
            // metarEnter
            // 
            this.metarEnter.Location = new System.Drawing.Point(136, 146);
            this.metarEnter.Name = "metarEnter";
            this.metarEnter.Size = new System.Drawing.Size(75, 23);
            this.metarEnter.TabIndex = 2;
            this.metarEnter.Text = "enter";
            this.metarEnter.UseVisualStyleBackColor = true;
            this.metarEnter.Click += new System.EventHandler(this.metarEnter_Click);
            // 
            // settings
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(32)))), ((int)(((byte)(67)))), ((int)(((byte)(112)))));
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.backGround_Panel);
            this.ForeColor = System.Drawing.SystemColors.ControlText;
            this.Name = "settings";
            this.Size = new System.Drawing.Size(1081, 738);
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.State_Panel.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.TextBox Metar_Setting_TextBox;
        private System.Windows.Forms.Panel State_Panel;
        private System.Windows.Forms.Label METAR_SETTING_Label;
        private System.Windows.Forms.Panel backGround_Panel;
        private System.Windows.Forms.Button metarEnter;
    }
}
