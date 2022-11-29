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
    public struct Data_Val
    {
        static public double eulerYaw { get; set; }
        static public double eulerPitch { get; set; }
        static public double eulerRoll { get; set; }
    }

    public partial class stageview : UserControl
    {

        public static stageview instance;
        public Label altimeterLabel_p, temperatureLabel_p, dewpointLabel_p, totalwindLabel_p;
        public PictureBox weatherPicBox_p;

        public class Data_Sender
        {
        }

        public stageview()
        {
            InitializeComponent();
            instance = this;
            altimeterLabel_p = altimeterLabel;
            temperatureLabel_p = temperatureLabel;
            dewpointLabel_p = dewpointLabel;
            totalwindLabel_p = totalwindLabel;
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

        //When receiving data from the port
        private void port_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            Teensy teensy = new Teensy();

            string data = Teensy.sp.ReadExisting();
            Console.WriteLine(data); //print information to console


            //stageview stage = new stageview();
            //access form from a thread
            Invoke(new Action(() =>
            {
                /* Print Format
                 *
                 * Euler Yaw
                 * Euler Pitch
                 * Euler Roll
                 *
                 */
                string longData = data.Replace(Environment.NewLine, ","); //put information horrizontally instead of vertically

                //place data into the struct
                Data_Val.eulerYaw = double.Parse(longData.Split(',')[0]);
                Data_Val.eulerPitch = double.Parse(longData.Split(',')[1]);
                Data_Val.eulerRoll = double.Parse(longData.Split(',')[2]);


                test_tel.Text = Data_Val.eulerPitch.ToString();
            }));
        }

        private void Connect_Button_Click(object sender, EventArgs e)
        {
            Teensy teensy = new Teensy();
            Teensy.TeensyInit();

            if (Teensy.DeviceConnected)
            {
                State_Panel.ForeColor = Color.Green;
                backGround_Panel.BackColor = Color.Green;
                StageUpdate_Label.Text = "Connected";
                test_tel.Text = teensy.TeensyData;
                Teensy.sp.DataReceived += new
                    SerialDataReceivedEventHandler(port_DataReceived); //Start information reading
            }

            if (!Teensy.DeviceConnected)
            {
                SoftBlink(State_Panel, Color.FromArgb(255, 159, 19), Color.Red, 2000, true);
                StageUpdate_Label.Text = "Looking For Device";
                Console.WriteLine("Button has been clicked");

            }
        }
    }
}
