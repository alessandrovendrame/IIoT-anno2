using System;
using System.Collections.Generic;
using System.Text;

namespace ITS.Vendrame.ServiceBus.Data.Models
{
    public class FridgeModel
    {
        public int IdFridge { get; set; }
        public double DetectedTemperature { get; set; }
        public double SettedTemperature { get; set; }
        public DateTime DetectionTime { get; set; }
    }
}
