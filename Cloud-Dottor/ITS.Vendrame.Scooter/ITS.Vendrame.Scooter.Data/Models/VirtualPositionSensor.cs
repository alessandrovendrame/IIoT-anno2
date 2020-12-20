using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Client.Sensors
{
    public class VirtualPositionSensor : SensorInterface, PositionSensorInterface
    {
        public string toJson()
        {
            var coords = GetPosition();
            return "long: " + coords[0] + ", lat: " + coords[1];
        }

        public int[] GetPosition()
        {
            int[] coords = new int[2];
            var random = new Random();

            coords[0] = random.Next(-181, 181); ;
            coords[1] = random.Next(-91, 91);

            return coords;
        }
    }
}
