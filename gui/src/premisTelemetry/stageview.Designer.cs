namespace premisTelemetry
{
    partial class stageview
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
            this.components = new System.ComponentModel.Container();
            this.StageUpdate_Label = new System.Windows.Forms.Label();
            this.panel1 = new System.Windows.Forms.Panel();
            this.Connect_Button = new System.Windows.Forms.Button();
            this.State_Panel = new System.Windows.Forms.Panel();
            this.backGround_Panel = new System.Windows.Forms.Panel();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.timer2 = new System.Windows.Forms.Timer(this.components);
            this.timer3 = new System.Windows.Forms.Timer(this.components);
            this.panel2 = new System.Windows.Forms.Panel();
            this.panel8 = new System.Windows.Forms.Panel();
            this.panel9 = new System.Windows.Forms.Panel();
            this.panel6 = new System.Windows.Forms.Panel();
            this.panel3 = new System.Windows.Forms.Panel();
            this.panel7 = new System.Windows.Forms.Panel();
            this.panel5 = new System.Windows.Forms.Panel();
            this.panel4 = new System.Windows.Forms.Panel();
            this.StateTitle = new System.Windows.Forms.Label();
            this.panel1.SuspendLayout();
            this.State_Panel.SuspendLayout();
            this.panel2.SuspendLayout();
            this.SuspendLayout();
            // 
            // StageUpdate_Label
            // 
            this.StageUpdate_Label.Font = new System.Drawing.Font("Unispace", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.StageUpdate_Label.Location = new System.Drawing.Point(73, 20);
            this.StageUpdate_Label.Name = "StageUpdate_Label";
            this.StageUpdate_Label.Size = new System.Drawing.Size(209, 19);
            this.StageUpdate_Label.TabIndex = 0;
            this.StageUpdate_Label.Text = "Device Not Connected";
            this.StageUpdate_Label.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.Connect_Button);
            this.panel1.Controls.Add(this.State_Panel);
            this.panel1.Location = new System.Drawing.Point(4, 161);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(342, 238);
            this.panel1.TabIndex = 1;
            // 
            // Connect_Button
            // 
            this.Connect_Button.Location = new System.Drawing.Point(130, 212);
            this.Connect_Button.Name = "Connect_Button";
            this.Connect_Button.Size = new System.Drawing.Size(75, 23);
            this.Connect_Button.TabIndex = 1;
            this.Connect_Button.Text = "Connect";
            this.Connect_Button.UseVisualStyleBackColor = true;
            this.Connect_Button.Click += new System.EventHandler(this.Connect_Button_Click);
            // 
            // State_Panel
            // 
            this.State_Panel.BackColor = System.Drawing.Color.White;
            this.State_Panel.Controls.Add(this.StageUpdate_Label);
            this.State_Panel.Location = new System.Drawing.Point(3, 3);
            this.State_Panel.Name = "State_Panel";
            this.State_Panel.Size = new System.Drawing.Size(336, 58);
            this.State_Panel.TabIndex = 0;
            // 
            // backGround_Panel
            // 
            this.backGround_Panel.BackColor = System.Drawing.Color.White;
            this.backGround_Panel.Location = new System.Drawing.Point(1, 158);
            this.backGround_Panel.Name = "backGround_Panel";
            this.backGround_Panel.Size = new System.Drawing.Size(348, 244);
            this.backGround_Panel.TabIndex = 2;
            // 
            // panel2
            // 
            this.panel2.Controls.Add(this.panel8);
            this.panel2.Controls.Add(this.panel9);
            this.panel2.Controls.Add(this.panel6);
            this.panel2.Controls.Add(this.panel3);
            this.panel2.Controls.Add(this.panel7);
            this.panel2.Controls.Add(this.panel5);
            this.panel2.Location = new System.Drawing.Point(-21, 435);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(1152, 238);
            this.panel2.TabIndex = 3;
            // 
            // panel8
            // 
            this.panel8.Location = new System.Drawing.Point(782, 105);
            this.panel8.Name = "panel8";
            this.panel8.Size = new System.Drawing.Size(206, 56);
            this.panel8.TabIndex = 9;
            // 
            // panel9
            // 
            this.panel9.BackColor = System.Drawing.Color.White;
            this.panel9.Location = new System.Drawing.Point(805, 102);
            this.panel9.Name = "panel9";
            this.panel9.Size = new System.Drawing.Size(163, 62);
            this.panel9.TabIndex = 10;
            // 
            // panel6
            // 
            this.panel6.Location = new System.Drawing.Point(443, 105);
            this.panel6.Name = "panel6";
            this.panel6.Size = new System.Drawing.Size(206, 56);
            this.panel6.TabIndex = 7;
            // 
            // panel3
            // 
            this.panel3.Location = new System.Drawing.Point(134, 105);
            this.panel3.Name = "panel3";
            this.panel3.Size = new System.Drawing.Size(206, 56);
            this.panel3.TabIndex = 5;
            // 
            // panel7
            // 
            this.panel7.BackColor = System.Drawing.Color.White;
            this.panel7.Location = new System.Drawing.Point(466, 102);
            this.panel7.Name = "panel7";
            this.panel7.Size = new System.Drawing.Size(163, 62);
            this.panel7.TabIndex = 8;
            // 
            // panel5
            // 
            this.panel5.BackColor = System.Drawing.Color.White;
            this.panel5.Location = new System.Drawing.Point(157, 102);
            this.panel5.Name = "panel5";
            this.panel5.Size = new System.Drawing.Size(163, 62);
            this.panel5.TabIndex = 6;
            // 
            // panel4
            // 
            this.panel4.BackColor = System.Drawing.Color.White;
            this.panel4.Location = new System.Drawing.Point(4, 432);
            this.panel4.Name = "panel4";
            this.panel4.Size = new System.Drawing.Size(1109, 244);
            this.panel4.TabIndex = 4;
            // 
            // StateTitle
            // 
            this.StateTitle.AutoSize = true;
            this.StateTitle.Font = new System.Drawing.Font("Unispace", 27.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.StateTitle.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.StateTitle.Location = new System.Drawing.Point(451, 15);
            this.StateTitle.Name = "StateTitle";
            this.StateTitle.Size = new System.Drawing.Size(157, 44);
            this.StateTitle.TabIndex = 5;
            this.StateTitle.Text = "Premis";
            // 
            // UserControl2
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(32)))), ((int)(((byte)(67)))), ((int)(((byte)(112)))));
            this.Controls.Add(this.StateTitle);
            this.Controls.Add(this.panel2);
            this.Controls.Add(this.panel4);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.backGround_Panel);
            this.Name = "UserControl2";
            this.Size = new System.Drawing.Size(1081, 738);
            this.panel1.ResumeLayout(false);
            this.State_Panel.ResumeLayout(false);
            this.panel2.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label StageUpdate_Label;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Panel State_Panel;
        private System.Windows.Forms.Panel backGround_Panel;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.Timer timer2;
        private System.Windows.Forms.Timer timer3;
        private System.Windows.Forms.Button Connect_Button;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.Panel panel8;
        private System.Windows.Forms.Panel panel9;
        private System.Windows.Forms.Panel panel6;
        private System.Windows.Forms.Panel panel3;
        private System.Windows.Forms.Panel panel7;
        private System.Windows.Forms.Panel panel5;
        private System.Windows.Forms.Panel panel4;
        private System.Windows.Forms.Label StateTitle;
    }
}
