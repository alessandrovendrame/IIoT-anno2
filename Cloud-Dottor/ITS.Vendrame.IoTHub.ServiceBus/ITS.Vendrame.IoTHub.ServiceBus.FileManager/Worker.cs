using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.Json;
using System.Threading;
using System.Threading.Tasks;
using System.Xml.Serialization;
using ITS.Vendrame.IoTHub.ServiceBus.Data.Models;
using Microsoft.Azure.Devices.Client;
using Microsoft.Azure.Devices.Shared;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;

namespace ITS.Vendrame.IoTHub.ServiceBus.FileManager
{
    public class Worker : BackgroundService
    {
        private readonly ILogger<Worker> _logger;
        private readonly IConfiguration _configuration;
        dynamic lastFile_name;
        private string file_text;
        private readonly string _deviceCS;
        private readonly string _iotHubCS;
        private static DeviceClient _deviceClient;

        public Worker(ILogger<Worker> logger, IConfiguration configuration)
        {
            _logger = logger;
            _configuration = configuration;
            _deviceCS = _configuration.GetConnectionString("Device_Twin");
            _iotHubCS = _configuration.GetConnectionString("IoT-Hub");
            _deviceClient = DeviceClient.CreateFromConnectionString(_deviceCS, TransportType.Mqtt);
        }

        protected override async Task ExecuteAsync(CancellationToken stoppingToken)
        {
            Twin twin;
            while (!stoppingToken.IsCancellationRequested)
            {
                try
                {
                    twin = await _deviceClient.GetTwinAsync();
                    lastFile_name = twin.Properties.Desired["fileName"];
                }catch(Exception e)
                {
                    lastFile_name = "";
                }
                
                if(lastFile_name != "")
                {
                    ConsoleKeyInfo choice;
                    do
                    {
                        Console.Clear();
                        Console.WriteLine($"L'ultima volta hai creato il file {lastFile_name}. Vuoi continuare a modificarlo? <y/n>: ");
                        choice = Console.ReadKey();
                    } while (choice.KeyChar != 'y' && choice.KeyChar != 'n');

                    Console.Clear();

                    switch (choice.KeyChar)
                    {
                        case 'y':
                            WriteOnFile();
                            break;
                        case 'n':
                            Console.WriteLine("Inserisci il nome del file: ");
                            lastFile_name = Console.ReadLine();
                            WriteOnFile();
                            break;
                    }
                }
                else
                {
                    Console.WriteLine("Inserisci il nome del file: ");
                    lastFile_name = Console.ReadLine();
                    WriteOnFile();
                }

                FileModel file = new FileModel();
                file.FileName = lastFile_name;
                file.Text = file_text;

                using (var manager = Microsoft.Azure.Devices.RegistryManager.CreateFromConnectionString(_iotHubCS))
                {
                    var twin_update = await manager.GetTwinAsync("vendrame-fileDevice");
                    twin_update.Properties.Desired["fileName"] = lastFile_name;
                    await manager.UpdateTwinAsync(twin_update.DeviceId, twin_update, twin_update.ETag);
                }

                SendMessageToCloudDeviceAsync(file);

                await Task.Delay(1000, stoppingToken);
            }
        }

        private void WriteOnFile()
        {
            Console.WriteLine("Inserisci il testo da aggiungere al tuo file: ");
            file_text = Console.ReadLine();

        }

        private static async void SendMessageToCloudDeviceAsync(FileModel file)
        {
            var messageString = JsonSerializer.Serialize(file);
            var message = new Message(Encoding.ASCII.GetBytes(messageString));

            await _deviceClient.SendEventAsync(message);
            Console.WriteLine("{0} > Sending message: {1}", DateTime.Now, messageString);
            await Task.Delay(1000);
        }
    }
}
