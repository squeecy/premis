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
    public struct metarReturn
    {
        public string local_Altimeter { get; set; }
        public string local_Temperature { get; set; }
        public string local_DewPoint { get; set; }
        public string local_WindDirection { get; set; }
        public string local_WindSpeed { get; set; }
        public string total_Wind { get; set; }
    }

    public class Weather_Metar
    {
        //holds our parsed JSON data and makes it global
        static public metarReturn metar_s = new metarReturn();



        //Class to call back and parse our JSON
        public class Altimeter
        {
            public string repr { get; set; }
            static public double value { get; set; }
            public string spoken { get; set; }
        }

        public class Code
        {
            public string repr { get; set; }
            public string value { get; set; }
        }

        public class Dewpoint
        {
            public string repr { get; set; }
            public int value { get; set; }
            public string spoken { get; set; }
        }

        public class DewpointDecimal
        {
            public string repr { get; set; }
            public double value { get; set; }
            public string spoken { get; set; }
        }

        public class Meta
        {
            public DateTime timestamp { get; set; }
            public string stations_updated { get; set; }
        }

        public class PressureTendency
        {
            public string repr { get; set; }
            public string tendency { get; set; }
            public double change { get; set; }
        }

        public class RemarksInfo
        {
            public object maximum_temperature_6 { get; set; }
            public object minimum_temperature_6 { get; set; }
            public PressureTendency pressure_tendency { get; set; }
            public object precip_36_hours { get; set; }
            public object precip_24_hours { get; set; }
            public object sunshine_minutes { get; set; }
            public List<Code> codes { get; set; }
            public DewpointDecimal dewpoint_decimal { get; set; }
            public object maximum_temperature_24 { get; set; }
            public object minimum_temperature_24 { get; set; }
            public object precip_hourly { get; set; }
            public SeaLevelPressure sea_level_pressure { get; set; }
            public object snow_depth { get; set; }
            public TemperatureDecimal temperature_decimal { get; set; }
        }

        public class Root
        {
            public Meta meta { get; set; }
            public Altimeter altimeter { get; set; }
            public List<object> clouds { get; set; }
            public string flight_rules { get; set; }
            public List<object> other { get; set; }
            public Visibility visibility { get; set; }
            public WindDirection wind_direction { get; set; }
            public object wind_gust { get; set; }
            public WindSpeed wind_speed { get; set; }
            public List<object> wx_codes { get; set; }
            public string raw { get; set; }
            public string sanitized { get; set; }
            public string station { get; set; }
            public Time time { get; set; }
            public string remarks { get; set; }
            public Dewpoint dewpoint { get; set; }
            public double relative_humidity { get; set; }
            public RemarksInfo remarks_info { get; set; }
            public List<object> runway_visibility { get; set; }
            public Temperature temperature { get; set; }
            public List<object> wind_variable_direction { get; set; }
            public int density_altitude { get; set; }
            public int pressure_altitude { get; set; }
            public Units units { get; set; }
        }

        public class SeaLevelPressure
        {
            public string repr { get; set; }
            public double value { get; set; }
            public string spoken { get; set; }
        }

        public class Temperature
        {
            public string repr { get; set; }
            public int value { get; set; }
            public string spoken { get; set; }
        }

        public class TemperatureDecimal
        {
            public string repr { get; set; }
            public double value { get; set; }
            public string spoken { get; set; }
        }

        public class Time
        {
            public string repr { get; set; }
            public DateTime dt { get; set; }
        }

        public class Units
        {
            public string accumulation { get; set; }
            public string altimeter { get; set; }
            public string altitude { get; set; }
            public string temperature { get; set; }
            public string visibility { get; set; }
            public string wind_speed { get; set; }
        }

        public class Visibility
        {
            public string repr { get; set; }
            public int value { get; set; }
            public string spoken { get; set; }
        }

        public class WindDirection
        {
            public string repr { get; set; }
            public int value { get; set; }
            public string spoken { get; set; }
        }

        public class WindSpeed
        {
            public string repr { get; set; }
            public int value { get; set; }
            public string spoken { get; set; }
        }

        /*Get METAR information 
         * @Param location = location where we want the API to get information from
         */
        static public async void callWXAPI(string location)
        {
            string responseData; //holds calling data

            var baseAddress = new Uri("https://avwx.rest/api/"); //calls to the API

            using (var httpClient = new HttpClient { BaseAddress = baseAddress })
            {
                httpClient.DefaultRequestHeaders.TryAddWithoutValidation("authorization", "Token MEEwBWGLolVe-a0ND4wSdlWklrIyTTVuIALhoPnb3Qk"); //Validates API

                using (var response = await httpClient.GetAsync($"metar/{location}"))
                {
                    responseData = await response.Content.ReadAsStringAsync(); //Reads our data and passes it to string type
                    Root parseClass = JsonConvert.DeserializeObject<Root>(responseData); // convert the JSON to something readable

                    //repr -> report
                    metar_s.local_Altimeter = parseClass.altimeter.repr;
                    metar_s.local_Temperature = parseClass.temperature.repr;
                    metar_s.local_DewPoint = parseClass.dewpoint.repr;
                    metar_s.local_WindDirection = parseClass.wind_direction.repr;
                    metar_s.local_WindSpeed = parseClass.wind_speed.repr;
                    metar_s.total_Wind = $"{metar_s.local_WindDirection} / {metar_s.local_WindSpeed}";

                    //metarReturn.Add(metar);

                    Console.WriteLine(metar_s.local_Altimeter);
                }
            }
        }
    }
}
