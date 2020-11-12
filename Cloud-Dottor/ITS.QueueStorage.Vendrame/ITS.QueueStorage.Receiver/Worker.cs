using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;
using System.Threading;
using System.Threading.Tasks;
using ITS.QueueStorage.Data.Model;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;

namespace ITS.QueueStorage.Receiver
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
            var connectionString = _configuration.GetConnectionString("ItsStorage");
            Queue queue = new Queue(connectionString);
            Message messaggio = new Message();

            while (!stoppingToken.IsCancellationRequested)
            {
                await Task.Delay(10000, stoppingToken);

                var messageQueue = queue.DequeueMessage("messagesqueue");

                if(messageQueue.Any())
                {
                    foreach(var message in messageQueue)
                    {
                        Console.WriteLine(message.Text);
                    }
                }
                else
                {
                    Console.WriteLine("La coda al momento è vuota");
                }                
            }
        }
    }
}
