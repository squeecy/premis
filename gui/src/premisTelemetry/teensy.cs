using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO.Ports;
using System.Windows.Forms;

namespace premisTelemetry
{
    public class Teensy 
    {


        static public SerialPort sp = new SerialPort();

        //get device monitor information 
        /*
                THIS IS OUR FUCKING PROBLEM FIX THIS SHIT https://stackoverflow.com/questions/49445252/c-sharp-serialport-readline-freezes-my-program
        static public string serialReceiver()
        {
            try 
            { 
                return sp.ReadLine();
            }
            catch (Exception ex)
            {
                MessageBox.Show("No information packets received", "No packets", MessageBoxButtons.OK, MessageBoxIcon.Stop);
                return null;
            }
        }
        */


        static public bool DeviceConnected = false;
        static public void TeensyInit()
        {

            try
            {
                //connecting our microcontroller 
                sp.PortName = "COM3";
                sp.DtrEnable = true;
                sp.RtsEnable = true;
                sp.BaudRate = 9600;
                sp.Open();
                //true allows gui state to change
                DeviceConnected = true;

            }
            /* catches erros */
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
        }
    }
}
