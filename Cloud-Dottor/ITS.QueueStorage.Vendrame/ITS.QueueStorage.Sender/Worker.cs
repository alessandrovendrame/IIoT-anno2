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

namespace ITS.QueueStorage.Sender
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
                Console.Write("Inserisci il messaggio da pushare nella coda: ");
                messaggio.Text = Console.ReadLine();

                queue.InsertMessage("messagesqueue", JsonSerializer.Serialize(messaggio));
            }
        }
    }
}
