using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Client.Sensors
{
    public class VirtualMovementSensor : SensorInterface, MovementSensorInterface
    {
        public string toJson()
        {
            return "{\"movement\": " + GetMovement() + "}";
        }

        public int GetMovement()
        {
            var random = new Random();
            
            return random.Next(2);
        }
    }
}
