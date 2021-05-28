using Microsoft.Azure.Devices;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ITS.Vendrame.C2D_Messages.WebApp.Models
{
    public class Sender
    {
        static ServiceClient serviceClient;
        static string connectionString = "HostName=vendrame-iiotHub.azure-devices.net;SharedAccessKeyName=service;SharedAccessKey=pFrmUVQGGyk2smp0mZh2xxSdEkYaUVClIdY51QO+m54=";

        public Sender()
        {
            serviceClient = ServiceClient.CreateFromConnectionString(connectionString);
        }

        public async Task SendCloudToDeviceMessageAsync(string targetDevice, string message)
        {
            var commandMessage = new Message(Encoding.ASCII.GetBytes(message));
            await serviceClient.SendAsync(targetDevice, commandMessage);
        }
    }
}
