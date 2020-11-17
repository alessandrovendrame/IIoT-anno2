using ITS.Vendrame.Azure.Data.Models;
using Microsoft.Azure.Cosmos.Table;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;

namespace ITS.Vendrame.Azure.Api.Services
{
    public class QueueReaderService : BackgroundService
    {
        private readonly IConfiguration _configuration;
        private readonly ILogger<FileTable> _logger;

        public QueueReaderService(IConfiguration configuration, ILogger<FileTable> logger)
        {
            _configuration = configuration;
            _logger = logger;
        }

        protected override async Task ExecuteAsync(CancellationToken stoppingToken)
        {
            var cs = _configuration.GetConnectionString("ItsStorage");
            var storageAccount = CloudStorageAccount.Parse(cs);
            var tableClient = storageAccount.CreateCloudTableClient(new TableClientConfiguration());
            var filesClient = tableClient.GetTableReference("files");

            await filesClient.CreateIfNotExistsAsync();

            Queue queue = new Queue(cs);

            while (!stoppingToken.IsCancellationRequested)
            {
                await Task.Delay(10000, stoppingToken);

                var fileQueue = queue.DequeueMessage("filequeue");

                foreach (FileModel f in fileQueue)
                {
                    FileTable ft = new FileTable(f.FileName, f.Extension);

                    if (f.Alive)
                    {
                        var insertFile = TableOperation.Insert(ft);
                        await filesClient.ExecuteAsync(insertFile).ConfigureAwait(false);
                    }
                    else
                    {
                        var fileToDelete = TableOperation.Retrieve<FileTable>(f.Extension, f.FileName);
                        TableResult result = filesClient.Execute(fileToDelete);
                        var deleteEntity = (FileTable)result.Result;
                        TableOperation delete = TableOperation.Delete(deleteEntity);

                        filesClient.Execute(delete);

                        //await filesClient.ExecuteAsync(deleteFile).ConfigureAwait(false);
                    }
                }
            }
            

        }
    }
}
