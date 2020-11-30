using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using ITS.Vendrame.DeviceToCloud.Data.Models;
using Microsoft.Azure.Devices;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;

namespace ITS.Vendrame.DeviceToCloud.Device_1
{
    public class Worker : BackgroundService
    {
        private readonly ILogger<Worker> _logger;
        private readonly IConfiguration _configuration;
        private readonly string _connectionStringDevice;
        private readonly ServiceClient _serviceClient;
        private readonly string _deviceId = "device-vendrame-1";

        public Worker(ILogger<Worker> logger, IConfiguration configuration)
        {
            _configuration = configuration;
            _connectionStringDevice = configuration.GetConnectionString("iot_device");
            _logger = logger;
            _serviceClient = ServiceClient.CreateFromConnectionString(_connectionStringDevice);
        }

        protected override async Task ExecuteAsync(CancellationToken stoppingToken)
        {
            Process p = Process.GetCurrentProcess();
            PerformanceCounter ramCounter = new PerformanceCounter("Process", "Working Set", "_Total");
            PerformanceCounter cpuCounter = new PerformanceCounter("Processor Information", "% Processor Time", "_Total");
            while (!stoppingToken.IsCancellationRequested)
            {
                var value = new Messaggio();
           
                value.DeviceId = _deviceId;

                var ram = ramCounter.NextValue();
                var cpu = cpuCounter.NextValue();

                string information ="RAM: " + (ram / 1024 / 1024) + " MB; CPU: " + cpu + " %_"+_deviceId;

                var message = new Message(Encoding.ASCII.GetBytes(information));
                
                await _serviceClient.SendAsync(value.DeviceId, message);
                _logger.LogInformation("Information: {information}", information);
                await Task.Delay(5000, stoppingToken);
            }
        }
    }
}
