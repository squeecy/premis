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

        static private void port_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {

            //_TeensyData = sp.ReadExisting();
            Console.WriteLine("Data: " + sp.ReadExisting()); //print information to console

        }

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
                //reads information
                sp.DataReceived += new
                    SerialDataReceivedEventHandler(port_DataReceived);
                sp.Open();

                _TeensyData=sp.ReadExisting();
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
