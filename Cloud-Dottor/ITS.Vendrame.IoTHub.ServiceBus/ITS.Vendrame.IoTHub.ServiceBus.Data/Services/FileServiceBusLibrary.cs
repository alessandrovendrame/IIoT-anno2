using Azure.Messaging.ServiceBus;
using ITS.Vendrame.IoTHub.ServiceBus.Data.Models;
using ITS.Vendrame.IoTHub.ServiceBus.Data.Services.Storage;
using System;
using System.Collections.Generic;
using System.Data.Common;
using System.Data.SqlClient;
using System.IO;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;

namespace ITS.Vendrame.IoTHub.ServiceBus.Data.Services
{
    public class FileServiceBusLibrary : IFileServiceBus
    {
        public ServiceBusClient client;
        private readonly string path = "C:\\Users\\Alessandro Vendrame\\Desktop\\Scuola\\IIoT-anno2\\Cloud-Dottor\\ITS.Vendrame.IoTHub.ServiceBus\\FileFolder\\";
        private string dbCs;

        StorageHelper storageHelper = new StorageHelper();

        public Task ErrorHandler(ProcessErrorEventArgs args)
        {
            Console.WriteLine(args.Exception.ToString());
            return Task.CompletedTask;
        }

        public async Task MessageHandlerWriteLocal(ProcessMessageEventArgs args)
        {
            string jsonFile = args.Message.Body.ToString();

            var file = JsonSerializer.Deserialize<FileModel>(jsonFile);

            if(file.FileName != null)
            {
                using (StreamWriter writeText = File.AppendText(path + file.FileName))
                {
                    writeText.WriteLine(file.Text);
                    writeText.Close();
                }
            }
            else
            {
                Console.WriteLine("Nome del file non specificato!");
            }

            await args.CompleteMessageAsync(args.Message);
        }

        public async Task MessageHandlerWriteOnDB(ProcessMessageEventArgs args)
        {
            storageHelper.Insert(dbCs, args.Message.Body.ToString());

            await args.CompleteMessageAsync(args.Message);
        }

        public async Task ReceiveMessageFromCloud(string connectionString, string topicName, string subscriptionName, string dbConnectionString = null)
        {
            if(dbConnectionString != null)
            {
                dbCs = dbConnectionString;
            }
            client = new ServiceBusClient(connectionString);

            ServiceBusProcessor processor = client.CreateProcessor(topicName, subscriptionName, new ServiceBusProcessorOptions());

            if (subscriptionName == "localSave")
            {
                // add handler to process messages
                processor.ProcessMessageAsync += MessageHandlerWriteLocal;
            }
            else if (subscriptionName == "storage")
            {
                processor.ProcessMessageAsync += MessageHandlerWriteOnDB;
            }


            // add handler to process any errors
            processor.ProcessErrorAsync += ErrorHandler;

            // start processing 
            await processor.StartProcessingAsync();

            Console.WriteLine("Wait for a minute and then press any key to end the processing");
            Console.ReadKey();

            // stop processing 
            Console.WriteLine("\nStopping the receiver...");
            await processor.StopProcessingAsync();
            Console.WriteLine("Stopped receiving messages");
        }
    }
}
