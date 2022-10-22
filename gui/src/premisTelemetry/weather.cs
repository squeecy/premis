using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net.Http;
using Newtonsoft.Json;
using System.IO;

namespace premisTelemetry
{

    class WeatherParse
    {
        public class Altimeter 
        {
            public double altimeter{ get; set; }
        }
    }

    public class Weather_Metar
    {




        const string wxFilePath = @"wx.txt";
        static string wxName;

        static private string readFile(string outlist, string filePath)
        {
            outlist = File.ReadLines(filePath).First();
            Console.ReadLine();

            return outlist; 
            
        }

        static public async void callWXAPI(string location)
        {
            string responseData;
            settings Settings = new settings();

            string test = Settings.GetMetarText();

            var baseAddress = new Uri("https://avwx.rest/api/");

            using (var httpClient = new HttpClient { BaseAddress = baseAddress })
            {
                httpClient.DefaultRequestHeaders.TryAddWithoutValidation("authorization", "Token MEEwBWGLolVe-a0ND4wSdlWklrIyTTVuIALhoPnb3Qk");

                using (var response = await httpClient.GetAsync($"metar/{location}"))
                {
                    responseData = await response.Content.ReadAsStringAsync();
                    Console.WriteLine(responseData);
                }
            }
        }
    }
}
