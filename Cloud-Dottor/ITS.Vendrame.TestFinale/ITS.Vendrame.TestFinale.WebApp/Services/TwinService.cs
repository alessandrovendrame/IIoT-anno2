using ITS.Vendrame.TestFinale.Data.Models;
using Microsoft.Azure.Devices;
using Microsoft.Azure.Devices.Client;
using Microsoft.Extensions.Configuration;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace ITS.Vendrame.TestFinale.WebApp.Services
{
    public class TwinService
    {
        public DeviceClient Client { get; set; }
        private readonly IConfiguration _configuration;
        private RegistryManager registryManager;
        public TwinService(IConfiguration configuration)
        {
            _configuration = configuration;
        }
    /*  public async void InitClient()
        {
            try
            {
                Console.WriteLine("Connecting to hub");
                Client = DeviceClient.CreateFromConnectionString(_configuration.GetConnectionString("IotDevice"),
                                                                 Microsoft.Azure.Devices.Client.TransportType.Mqtt);
                Console.WriteLine("Retrieving twin");
                await Client.GetTwinAsync();
            }
            catch (Exception ex)
            {
                Console.WriteLine();
                Console.WriteLine("Error in sample: {0}", ex.Message);
            }
        }
    */
        public async void Desired(DepartmentModel departmentInfo)
        {
            try
            {
                registryManager = RegistryManager.CreateFromConnectionString(_configuration.GetConnectionString("IotHubConnectionString"));
                var twin = await registryManager.GetTwinAsync("device-vendrame-1");
                twin.Properties.Desired["departmentId"] = departmentInfo.DepartmentId; //Immettere department id
                twin.Properties.Desired["ticketNumber"] = departmentInfo.TicketNumber;
                
                await registryManager.UpdateTwinAsync(twin.DeviceId, twin, twin.ETag);
            }
            catch (Exception ex)
            {
                Console.WriteLine();
                Console.WriteLine("Error in sample: {0}", ex.Message);
            }
        }

        public async Task<DepartmentModel> GetDesired()
        {
            DepartmentModel department = new DepartmentModel();

            registryManager = RegistryManager.CreateFromConnectionString(_configuration.GetConnectionString("IotHubConnectionString"));
            var twin = await registryManager.GetTwinAsync("device-vendrame-1");

            department.DepartmentId = twin.Properties.Desired["departmentId"];
            department.TicketNumber = twin.Properties.Desired["ticketNumber"];

            return department;
        }
    }
}
