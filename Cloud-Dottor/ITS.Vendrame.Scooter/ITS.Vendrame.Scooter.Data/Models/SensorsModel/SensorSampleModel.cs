using System;
using System.Collections.Generic;
using System.Text;

namespace ITS.Vendrame.Scooter.Data.Models.SensorsModel
{
    public class SensorSampleModel
    {
        public int ScooterId { get; set; }
        public int SensorId { get; set; }
        public string SensorType { get; set; }
        public DateTime SensorDetectionDate { get; set; }
    }
}
