using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;
using System.Text.Json.Serialization;
using System.Threading;
using System.Threading.Tasks;
using Client.Sensors;
using ITS.Vendrame.Scooter.Data.Models;
using ITS.Vendrame.Scooter.Data.Models.QueueModels;
using ITS.Vendrame.Scooter.Data.Models.SensorsModel;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;

namespace ITS.Vendrame.Scooter.SpeedSensor
{
    public class Worker : BackgroundService
    {
        private readonly ILogger<Worker> _logger;
        private readonly IConfiguration _configuration;
        private VirtualSpeedSensor virtualSpeedSensor = new VirtualSpeedSensor();

        public Worker(ILogger<Worker> logger, IConfiguration configuration)
        {
            _logger = logger;
            _configuration = configuration;
        }

        protected override async Task ExecuteAsync(CancellationToken stoppingToken)
        {
            SpeedSensorModel sensore = new SpeedSensorModel();
            sensore.ScooterId = 1;
            sensore.SensorId = 4;
            Queue queue = new Queue(_configuration.GetConnectionString("ITS_Storage"));

            queue.CreateQueue("collarini-vendrame-queue");

            while (!stoppingToken.IsCancellationRequested)
            {
                var info = virtualSpeedSensor.GetSpeed();
                sensore.SensorType = "Speed_Sensor";
                sensore.SensorValue = info.ToString();
                sensore.SensorDetectionDate = DateTime.Now;

                var json = JsonSerializer.Serialize(sensore);
                Console.WriteLine("Json file sent: " + json);

                var plainTextBytes = System.Text.Encoding.UTF8.GetBytes(json);
                var jsonBase64 = System.Convert.ToBase64String(plainTextBytes);
                queue.InsertMessage("collarini-vendrame-queue", jsonBase64);

                await Task.Delay(5000, stoppingToken);
            }
        }
    }
}
