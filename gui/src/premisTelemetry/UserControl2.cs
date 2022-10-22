using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;
using System.IO.Ports;
using System.Net.Http;

namespace premisTelemetry
{
    public partial class UserControl2 : UserControl
    {

        readonly SerialPort sp = new SerialPort();
        bool DeviceConnected = false;

        private void DeviceState()
        {
            if (!DeviceConnected)
            {
                timer1.Start();
            }
        }

        public UserControl2()
        {
            InitializeComponent();
            //DeviceState();
        }


        private async void SoftBlink(Control ctrl, Color c1, Color c2, short CycleTime_ms, bool BkClr)
        {
            var sw = new Stopwatch(); sw.Start();
            short halfCycle = (short)Math.Round(CycleTime_ms * 0.5);
            while (true)
            {
                await Task.Delay(1);
                var n = sw.ElapsedMilliseconds % CycleTime_ms;
                var per = (double)Math.Abs(n - halfCycle) / halfCycle;
                var red = (short)Math.Round((c2.R - c1.R) * per) + c1.R;
                var grn = (short)Math.Round((c2.G - c1.G) * per) + c1.G;
                var blw = (short)Math.Round((c2.B - c1.B) * per) + c1.B;
                var clr = Color.FromArgb(red, grn, blw);
                if (BkClr) ctrl.BackColor = clr; else ctrl.ForeColor = clr;
            }
        }


        private void TeensyInit()
        {
            sp.PortName = "COM3";
            sp.BaudRate = 9600;
            sp.Open();
            DeviceConnected = true;

        }

        private void Connect_Button_Click(object sender, EventArgs e)
        {

            try
            {
                TeensyInit();
                if (DeviceConnected)
                {
                    State_Panel.ForeColor = Color.Green;
                    backGround_Panel.BackColor = Color.Green;
                    StageUpdate_Label.Text = "Connected";
                    
                }
            }
            catch (UnauthorizedAccessException)
            {
                MessageBox.Show("The Port is Busy", "Busy", MessageBoxButtons.OK, MessageBoxIcon.Stop);
            }
            catch (NullReferenceException)
            {
                MessageBox.Show("There is no serial port", "Empty", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }

            if (!DeviceConnected)
            {
                //timer1.Start();
                SoftBlink(State_Panel, Color.FromArgb(255, 159, 19), Color.Red, 2000, true);
                StageUpdate_Label.Text = "Looking For Device";
                Console.WriteLine("Button has been clicked");
            }
            
        }




    }
}
