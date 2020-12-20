using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using ITS.Vendrame.TestFinale.Client.Services;
using ITS.Vendrame.TestFinale.Data.Models;
using Microsoft.Azure.Devices;
using Microsoft.Azure.Devices.Client;
using Microsoft.Azure.Devices.Shared;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;

namespace ITS.Vendrame.TestFinale.Client
{
    public class Worker : BackgroundService
    {
        private readonly ILogger<Worker> _logger;
        private readonly IConfiguration _configuration;
        private int ticketNumber;
        private string departmentId;
        private readonly ServiceClient _serviceClient;
        private readonly string _deviceId = "device-vendrame-1";

        public Worker(ILogger<Worker> logger, IConfiguration configuration)
        {
            _logger = logger;
            _configuration = configuration;
            _serviceClient = ServiceClient.CreateFromConnectionString(_configuration.GetConnectionString("IotDevice"));
        }

        protected override async Task ExecuteAsync(CancellationToken stoppingToken)
        {
            ClientService client = new ClientService(_configuration);
            client.InitClient();

            TwinCollection reportedProperties, connectivity;
      
            connectivity = new TwinCollection();
            var twin = await client.Client.GetTwinAsync();

            if (twin.Properties.Desired["departmentId"] != null && twin.Properties.Desired["ticketNumber"] != null)
            {
                reportedProperties = new TwinCollection();
                departmentId = twin.Properties.Desired["departmentId"];
                ticketNumber = twin.Properties.Desired["ticketNumber"];

                var deviceClient = DeviceClient.CreateFromConnectionString(
                    _configuration.GetConnectionString("IotHub"), //cambiare stringa di connessione
                    Microsoft.Azure.Devices.Client.TransportType.Mqtt
                );

                Console.WriteLine("Premi invio per generare un nuovo biglietto.");
                while (!stoppingToken.IsCancellationRequested)
                {
                    if (Console.ReadKey().Key == ConsoleKey.Enter)
                    {
                        ticketNumber++;
                        DepartmentModel department = new DepartmentModel(departmentId, ticketNumber);

                        Console.WriteLine("Biglietto numero: " + department.getTicket());

                        reportedProperties["departmentId"] = departmentId;
                        reportedProperties["ticketNumber"] = ticketNumber;
                        await client.Client.UpdateReportedPropertiesAsync(reportedProperties);

                        var information = departmentId + "_" + ticketNumber;

                        var message = new Microsoft.Azure.Devices.Client.Message(Encoding.ASCII.GetBytes(department.getTicket()));

                        await deviceClient.SendEventAsync(message);

                        Console.WriteLine("Premi invio per generare un nuovo biglietto.");
                    }
                }
            }
            else
            {
                Console.WriteLine("Il dispositivo deve ancora essere configurato");
            }
        }
    }
}
