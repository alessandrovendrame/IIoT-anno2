using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;
using System.Threading;
using System.Threading.Tasks;
using Client.Sensors;
using ITS.Vendrame.Scooter.Data.Models;
using ITS.Vendrame.Scooter.Data.Models.QueueModels;
using ITS.Vendrame.Scooter.Data.Models.SensorsModel;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;

namespace ITS.Vendrame.Scooter.PositionSensor
{
    public class Worker : BackgroundService
    {
        private readonly ILogger<Worker> _logger;
        private readonly IConfiguration _configuration;
        private VirtualPositionSensor virtualPositionSensor = new VirtualPositionSensor();

        public Worker(ILogger<Worker> logger, IConfiguration configuration)
        {
            _logger = logger;
            _configuration = configuration;
        }

        protected override async Task ExecuteAsync(CancellationToken stoppingToken)
        {
            Queue queue = new Queue(_configuration.GetConnectionString("ITS_Storage"));
            PositionSensorModel sensore = new PositionSensorModel();
            sensore.SensorType = "Position_Sensor";
            sensore.ScooterId = 1;
            sensore.SensorId = 3;

            queue.CreateQueue("collarini-vendrame-queue");

            while (!stoppingToken.IsCancellationRequested)
            {
                var info = virtualPositionSensor.toJson();
                sensore.SensorValue = info;
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
