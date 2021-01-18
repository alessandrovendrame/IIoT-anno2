using Microsoft.Azure.Cosmos.Table;
using System;
using System.Collections.Generic;
using System.Text;

namespace ITS.Vendrame.ServiceBus.Data.Models
{
    public class FridgeStorageEntity : TableEntity
    {
        public FridgeStorageEntity(int fridgeId, double detectedTemperature, double settedTemperature, DateTime detectionTime)
        {
            PartitionKey = "ITS";
            RowKey = Guid.NewGuid().ToString();
            IdFridge = fridgeId;
            DetectedTemperature = detectedTemperature;
            SettedTemperature = settedTemperature;
            DetectionTime = detectionTime;
        }

        public FridgeStorageEntity()
        {

        }

        public int IdFridge { get; set; }
        public double DetectedTemperature { get; set; }
        public double SettedTemperature { get; set; }
        public DateTime DetectionTime { get; set; }
    }
}
