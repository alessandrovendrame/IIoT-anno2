using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Client.Sensors
{
    public class VirtualBatterySensor : SensorInterface, BatterySensorInterface
    {
        public string toJson()
        {
            return "{\"battery\": " + GetBatteryStatus() + "}";
        }

        public int GetBatteryStatus()
        {
            var random = new Random();
           
            return random.Next(101);
        }
    }
}
