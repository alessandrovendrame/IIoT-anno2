using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using ITS.Vendrame.IoTHub.ServiceBus.Data.Services;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;

namespace ITS.Vendrame.IoTHub.ServiceBus.FileWriter
{
    public class Worker : BackgroundService
    {
        private readonly ILogger<Worker> _logger;
        private readonly IConfiguration _configuration;
        private readonly IFileServiceBus _fileServiceBus;

        private readonly string _serviceBusCS;

        public Worker(ILogger<Worker> logger, IConfiguration configuration, IFileServiceBus fileServiceBus)
        {
            _logger = logger;
            _configuration = configuration;
            _fileServiceBus = fileServiceBus;
            _serviceBusCS = _configuration.GetConnectionString("ServiceBus");
        }

        protected override async Task ExecuteAsync(CancellationToken stoppingToken)
        {
            while (!stoppingToken.IsCancellationRequested)
            {
                await _fileServiceBus.ReceiveMessageFromCloud(_serviceBusCS, "files", "localSave");
                await Task.Delay(1000, stoppingToken);
            }
        }
    }
}
