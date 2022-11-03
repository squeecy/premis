using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace premisTelemetry
{
    public partial class settings : UserControl
    {

        public static settings instance;
        public stageview Stageview;

        public settings()
        {
            InitializeComponent();
            instance = this;

        }

        public string GetMetarText()
        {
            return Metar_Setting_TextBox.Text;  
        }


        private void metarEnter_Click(object sender, EventArgs e)
        {

            //metarReturn metar = new metarReturn();
            //call the API on button click
            Weather_Metar.callWXAPI(GetMetarText());

            //Making sure the variable has a value before displaying
            if (!string.IsNullOrEmpty(Weather_Metar.metar_s.local_Altimeter))
            {
                //sends parsed information to label in stageview.cs
                stageview.instance.altimeterLabel_p.Location = new Point(108, 37);
                stageview.instance.altimeterLabel_p.ForeColor = Color.Black;
                stageview.instance.altimeterLabel_p.Text = Weather_Metar.metar_s.local_Altimeter;
                stageview.instance.temperatureLabel_p.Text = Weather_Metar.metar_s.local_Temperature;
                stageview.instance.dewpointLabel_p.Text = Weather_Metar.metar_s.local_DewPoint;
                stageview.instance.totalwindLabel_p.Text = Weather_Metar.metar_s.total_Wind;
            }
        }
    }
}
