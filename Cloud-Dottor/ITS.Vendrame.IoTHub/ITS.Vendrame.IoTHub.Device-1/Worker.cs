using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using ITS.Vendrame.IoTHub.Data.Models;
using Microsoft.Azure.Devices.Client;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;

namespace ITS.Vendrame.IoTHub.Device_1
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
                    _configuration.GetConnectionString("ItsIotHub"),
                    TransportType.Mqtt
                );

            while (!stoppingToken.IsCancellationRequested)
            {
                var message = new MessageReceive(deviceClient);
                await message.RunSampleAsync();
            }
        }
    }
}
