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
        static public bool DeviceConnected = false;

        static private string _TeensyData;


        public string TeensyData
        {
            get { return _TeensyData; }
            set { _TeensyData = value; }
        }

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

                _TeensyData = sp.ReadLine();
                DeviceConnected = true; //true allows gui state to change

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

        static public void TeensyMonitor()
        {
            _TeensyData = sp.ReadLine().ToString();
        }
    }
}
