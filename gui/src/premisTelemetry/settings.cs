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
        public settings()
        {
            InitializeComponent();
        }

        public void Metar_Setting_TextBox_TextChanged(object sender, EventArgs e)
        {
        }

        public string GetMetarText()
        {
            return Metar_Setting_TextBox.Text;  
        }

        private void metarEnter_Click(object sender, EventArgs e)
        {
            GetMetarText();

            Weather_Metar weather = new Weather_Metar();
            Weather_Metar.callWXAPI(GetMetarText());

        }
    }
}
