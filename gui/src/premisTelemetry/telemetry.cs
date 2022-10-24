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
using rtChart;

namespace premisTelemetry
{
    public partial class telemetry : UserControl
    {
        public telemetry()
        {

            InitializeComponent();

        }

        private void button1_Click(object sender, EventArgs e)
        {

            kayChart cpuData = new kayChart(chart1, 60);

            cpuData.serieName = "CPU";

            Task.Factory.StartNew(() =>
            {
                cpuData.updateChart(updateWithCPU, 10);
               

            });
        }

        readonly PerformanceCounter cpu = new PerformanceCounter("Processor Information", "% Processor Time", "_Total");
        private double updateWithCPU()
        {
            return cpu.NextValue();
        }

    }
}
