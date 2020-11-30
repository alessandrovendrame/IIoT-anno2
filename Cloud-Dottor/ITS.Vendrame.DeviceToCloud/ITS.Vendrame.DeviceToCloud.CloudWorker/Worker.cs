using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using ITS.Vendrame.DeviceToCloud.Data.Models;
using Microsoft.Azure.Devices.Client;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;

namespace ITS.Vendrame.DeviceToCloud.CloudWorker
{
    public class Worker : BackgroundService
    {
        private readonly ILogger<Worker> _logger;
        private readonly IConfiguration _configuration;

        public Worker(ILogger<Worker> logger, IConfiguration configuration)
        {
            _logger = logger;
            _configuration = configuration;
        }

        protected override async Task ExecuteAsync(CancellationToken stoppingToken)
        {
            Console.WriteLine("Receiving cloud to device messages from service\n\n");

            var deviceClient = DeviceClient.CreateFromConnectionString(
                    _configuration.GetConnectionString("IotHub"),
                    TransportType.Mqtt
                );

            while (!stoppingToken.IsCancellationRequested)
            {
                var message = new MessageReceive(deviceClient, _configuration);
                await message.RunSampleAsync();
            }
        }
    }
}
