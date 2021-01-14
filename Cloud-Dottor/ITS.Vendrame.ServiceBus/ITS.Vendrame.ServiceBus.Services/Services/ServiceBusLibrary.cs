using Azure.Messaging.ServiceBus;
using ITS.Vendrame.ServiceBus.Data.Models;
using Microsoft.Azure.Cosmos.Table;
using Microsoft.Extensions.Configuration;
using System;
using System.Collections.Generic;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;

namespace ITS.Vendrame.ServiceBus.Services.Services
{
    public class ServiceBusLibrary
    {
        private readonly IConfiguration _configuration;

        public ServiceBusLibrary(IConfiguration configuration)
        {
            _configuration = configuration;
        }

        public async Task SendMessageToTopicAsync(string topicName, string fridgeToJson)
        {
            // create a Service Bus client 
            await using (ServiceBusClient client = new ServiceBusClient(_configuration.GetConnectionString("serviceBus")))
            {
                // create a sender for the topic
                ServiceBusSender sender = client.CreateSender(topicName);
                await sender.SendMessageAsync(new ServiceBusMessage(fridgeToJson));
                Console.WriteLine($"Sent a single message to the topic: {topicName}");
            }
        }

        public async Task AlertMessageHandler(ProcessMessageEventArgs args)
        {
            string body = args.Message.Body.ToString();

            var fridge = JsonSerializer.Deserialize<FridgeModel>(body);

            // complete the message. messages is deleted from the queue. 
            await args.CompleteMessageAsync(args.Message);
        }

        public async Task SaveMessageHandler(ProcessMessageEventArgs args)
        {
            string body = args.Message.Body.ToString();

            var fridgeFromBody = JsonSerializer.Deserialize<FridgeModel>(body);

            FridgeStorageEntity fridgeStorageEntity = new FridgeStorageEntity(fridgeFromBody.IdFridge, fridgeFromBody.DetectedTemperature, fridgeFromBody.DetectedTemperature, fridgeFromBody.DetectionTime);

            var cs = _configuration.GetConnectionString("tableStorage");
            var storageAccount = CloudStorageAccount.Parse(cs);
            var tableClient = storageAccount.CreateCloudTableClient(new TableClientConfiguration());
            var fridgeClient = tableClient.GetTableReference("fridges");

            var insertFridge = TableOperation.Insert(fridgeStorageEntity);
            var result = await fridgeClient.ExecuteAsync(insertFridge).ConfigureAwait(false);

            // complete the message. messages is deleted from the queue. 
            await args.CompleteMessageAsync(args.Message);
        }

        static Task ErrorHandler(ProcessErrorEventArgs args)
        {
            Console.WriteLine(args.Exception.ToString());
            return Task.CompletedTask;
        }

        public async Task ReceiveMessagesFromSubscriptionAsync(string subscriptionName, string topicName)
        {
            await using (ServiceBusClient client = new ServiceBusClient(_configuration.GetConnectionString("serviceBus")))
            {
                // create a processor that we can use to process the messages
                ServiceBusProcessor processor = client.CreateProcessor(topicName, subscriptionName, new ServiceBusProcessorOptions());

                if(subscriptionName == "alert")
                {
                    // add handler to process messages
                    processor.ProcessMessageAsync += AlertMessageHandler;
                }else if(subscriptionName == "storage")
                {
                    processor.ProcessMessageAsync += SaveMessageHandler;
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
}
