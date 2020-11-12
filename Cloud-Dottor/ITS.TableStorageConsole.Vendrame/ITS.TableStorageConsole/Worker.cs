using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using ITS.TableStorageConsole.Models;
using Microsoft.Azure.Cosmos.Table;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;

namespace ITS.TableStorageConsole
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
            var cs = _configuration.GetConnectionString("ItsStorage");
            var storageAccount = CloudStorageAccount.Parse(cs);
            var tableClient = storageAccount.CreateCloudTableClient(new TableClientConfiguration());
            var usersClient = tableClient.GetTableReference("users");

            //creazione tabella users
            await usersClient.CreateIfNotExistsAsync();

            //inserimento
            var user = new User(Guid.NewGuid(), "Alessandro", "Vendrame");
            var insertUser = TableOperation.Insert(user);

            var result = await usersClient.ExecuteAsync(insertUser).ConfigureAwait(false);

            var getUser = TableOperation.Retrieve<User>("Vendrame", "ab6c7541-7a71-437e-aac4-43dc2982dcf3");
            var resultGet = await usersClient.ExecuteAsync(getUser);

            while (!stoppingToken.IsCancellationRequested)
            {
                _logger.LogInformation("Worker running at: {time}", DateTimeOffset.Now);
                await Task.Delay(1000, stoppingToken);
            }
        }
    }
}
