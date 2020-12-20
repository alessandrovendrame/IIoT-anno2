using ITS.Vendrame.TestFinale.Data.Models;
using Microsoft.Azure.Devices.Client;
using Microsoft.Extensions.Configuration;
using System;
using System.Collections.Generic;
using System.Text;
using System.Threading.Tasks;

namespace ITS.Vendrame.TestFinale.Client.Services
{
    public class ClientService
    {
        public DeviceClient Client { get; set; }
        private readonly IConfiguration _configuration;

        public ClientService(IConfiguration configuration)
        {
            _configuration = configuration;
        }
        
        public async void InitClient()
        {
            try
            {
                Console.WriteLine("Connecting to hub");
                Client = DeviceClient.CreateFromConnectionString(_configuration.GetConnectionString("IotDevice"),
                                                                    Microsoft.Azure.Devices.Client.TransportType.Amqp);
                Console.WriteLine("Retrieving twin");
            }
            catch (Exception ex)
            {
                Console.WriteLine();
                Console.WriteLine("Error in sample: {0}", ex.Message);
            }
        }

        
    }
}
