using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using rtChart;
using System.IO.Ports;
using System.IO;
using System.Diagnostics;

namespace premisTelemetry
{
    public partial class global : Form
    {
        public global()
        {
            InitializeComponent();
        }



        
        //Logic for clicking buttons to move pages
        private void StageView_Button_Click(object sender, EventArgs e)
        {
            userControl11.Hide();
            settings1.Hide();
            userControl21.Show();
            userControl21.BringToFront();

        }


        //Logic for clicking buttons to move pages
        private void TelemetryView_Button_Click(object sender, EventArgs e)
        {
            userControl21.Hide();
            settings1.Hide();
            userControl11.Show();
            userControl11.BringToFront();
            //readFile(wxName, wxFilePath);

        }





        //Close the application
        private void button3_Click(object sender, EventArgs e)
        {
            Teensy.sp.Close();  
            Close();
        }


        private void Settings_Button_Click(object sender, EventArgs e)
        {
            userControl11.Hide();
            userControl21.Hide();

            settings1.Show();
            settings1.BringToFront();


        }

        /*
        const string wxFilePath = @"wx.txt";
        static string wxName;

        static private string readFile(string outlist, string filePath)
        {
            outlist = File.ReadLines(filePath).First();
            Console.ReadLine();

            return outlist;

        }
        */
    }
}
