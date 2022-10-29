namespace premisTelemetry
{
    partial class global
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
            this.panel1 = new System.Windows.Forms.Panel();
            this.Settings_Button = new System.Windows.Forms.Button();
            this.button3 = new System.Windows.Forms.Button();
            this.TelemetryView_Button = new System.Windows.Forms.Button();
            this.StageView_Button = new System.Windows.Forms.Button();
            this.panel4 = new System.Windows.Forms.Panel();
            this.userControl21 = new premisTelemetry.stageview();
            this.userControl11 = new premisTelemetry.telemetry();
            this.settings1 = new premisTelemetry.settings();
            this.panel1.SuspendLayout();
            this.panel4.SuspendLayout();
            this.SuspendLayout();
            // 
            // panel1
            // 
            this.panel1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(20)))), ((int)(((byte)(44)))), ((int)(((byte)(75)))));
            this.panel1.Controls.Add(this.Settings_Button);
            this.panel1.Controls.Add(this.button3);
            this.panel1.Controls.Add(this.TelemetryView_Button);
            this.panel1.Controls.Add(this.StageView_Button);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Left;
            this.panel1.ForeColor = System.Drawing.SystemColors.ControlText;
            this.panel1.Location = new System.Drawing.Point(0, 0);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(216, 738);
            this.panel1.TabIndex = 0;
            // 
            // Settings_Button
            // 
            this.Settings_Button.Location = new System.Drawing.Point(0, 603);
            this.Settings_Button.Name = "Settings_Button";
            this.Settings_Button.Size = new System.Drawing.Size(213, 63);
            this.Settings_Button.TabIndex = 3;
            this.Settings_Button.Text = "Settings";
            this.Settings_Button.UseVisualStyleBackColor = true;
            this.Settings_Button.Click += new System.EventHandler(this.Settings_Button_Click);
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(0, 703);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(213, 23);
            this.button3.TabIndex = 2;
            this.button3.Text = "Exit";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // TelemetryView_Button
            // 
            this.TelemetryView_Button.Location = new System.Drawing.Point(0, 91);
            this.TelemetryView_Button.Name = "TelemetryView_Button";
            this.TelemetryView_Button.Size = new System.Drawing.Size(213, 63);
            this.TelemetryView_Button.TabIndex = 1;
            this.TelemetryView_Button.Text = "Telemetry View";
            this.TelemetryView_Button.UseVisualStyleBackColor = true;
            this.TelemetryView_Button.Click += new System.EventHandler(this.TelemetryView_Button_Click);
            // 
            // StageView_Button
            // 
            this.StageView_Button.Location = new System.Drawing.Point(0, 22);
            this.StageView_Button.Name = "StageView_Button";
            this.StageView_Button.Size = new System.Drawing.Size(213, 63);
            this.StageView_Button.TabIndex = 0;
            this.StageView_Button.Text = "Stage View";
            this.StageView_Button.UseVisualStyleBackColor = true;
            this.StageView_Button.Click += new System.EventHandler(this.StageView_Button_Click);
            // 
            // panel4
            // 
            this.panel4.Controls.Add(this.userControl21);
            this.panel4.Controls.Add(this.userControl11);
            this.panel4.Controls.Add(this.settings1);
            this.panel4.Location = new System.Drawing.Point(219, 0);
            this.panel4.Name = "panel4";
            this.panel4.Size = new System.Drawing.Size(1081, 738);
            this.panel4.TabIndex = 4;
            // 
            // userControl21
            // 
            this.userControl21.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(32)))), ((int)(((byte)(67)))), ((int)(((byte)(112)))));
            this.userControl21.Location = new System.Drawing.Point(0, 0);
            this.userControl21.Name = "userControl21";
            this.userControl21.Size = new System.Drawing.Size(1081, 738);
            this.userControl21.TabIndex = 1;
            // 
            // userControl11
            // 
            this.userControl11.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(32)))), ((int)(((byte)(67)))), ((int)(((byte)(112)))));
            this.userControl11.Location = new System.Drawing.Point(0, 3);
            this.userControl11.Name = "userControl11";
            this.userControl11.Size = new System.Drawing.Size(1081, 738);
            this.userControl11.TabIndex = 0;
            // 
            // settings1
            // 
            this.settings1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(32)))), ((int)(((byte)(67)))), ((int)(((byte)(112)))));
            this.settings1.ForeColor = System.Drawing.SystemColors.ControlText;
            this.settings1.Location = new System.Drawing.Point(-3, 3);
            this.settings1.Name = "settings1";
            this.settings1.Size = new System.Drawing.Size(1081, 738);
            this.settings1.TabIndex = 2;
            // 
            // global
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(32)))), ((int)(((byte)(67)))), ((int)(((byte)(112)))));
            this.ClientSize = new System.Drawing.Size(1300, 738);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.panel4);
            this.ForeColor = System.Drawing.SystemColors.ControlText;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Name = "global";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Form1";
            this.panel1.ResumeLayout(false);
            this.panel4.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Button TelemetryView_Button;
        private System.Windows.Forms.Button StageView_Button;
        private System.Windows.Forms.Panel panel4;
        private telemetry userControl11;
        private stageview userControl21;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.Button Settings_Button;
        private settings settings1;
    }
}

