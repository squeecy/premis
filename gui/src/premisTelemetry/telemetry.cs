using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.IO.Ports;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;
using rtChart;

namespace premisTelemetry
{
    public partial class telemetry : UserControl
    {
        public telemetry()
        {
            InitializeComponent();
        }

        private void port_DataReceived(object sender, SerialDataReceivedEventArgs e) { } //send data when receiving data

        private double updateYaw() { return Data_Val.eulerYaw; } //convert to sys.func
        private double updatePitch() { return Data_Val.eulerPitch; } //convert to sys.func
        private double updateRoll() { return Data_Val.eulerRoll; } //convert to sys.func

        private void button1_Click(object sender, EventArgs e)
        {

            //init charts
            kayChart pitchData = new kayChart(orientationChart, 120);
            kayChart rollData = new kayChart(orientationChart, 120);

            //init chart names
            rollData.serieName = "ROLL";
            pitchData.serieName = "PITCH";

            Teensy.sp.DataReceived += new SerialDataReceivedEventHandler(port_DataReceived); //receiving data

            //display 1st line 
            Task.Run(() =>
            {
                rollData.updateChart(updateRoll, 50);
            });

            //display 2nd line
            Task.Run(() =>
            {
                pitchData.updateChart(updatePitch, 50);
            });
        }

    }
}
