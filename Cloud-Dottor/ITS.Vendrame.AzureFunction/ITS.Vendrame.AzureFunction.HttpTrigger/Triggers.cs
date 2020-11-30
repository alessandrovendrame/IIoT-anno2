using System;
using System.IO;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Azure.WebJobs;
using Microsoft.Azure.WebJobs.Extensions.Http;
using Microsoft.AspNetCore.Http;
using Microsoft.Extensions.Logging;
using Microsoft.Extensions.Configuration;
using System.Text.Json;
using Microsoft.Azure.Cosmos.Table;
using ITS.Vendrame.AzureFunction.Data.Models;
using System.Linq;
using System.Collections;
using System.Collections.Generic;

namespace ITS.Vendrame.AzureFunction.HttpTrigger
{
    public class Triggers
    {
        private readonly IConfiguration _configuration;
        private string cs;
        private CloudStorageAccount storageAccount;
        private CloudTableClient tableClient;
        private CloudTable filesTable;

        public Triggers(IConfiguration configuration)
        {
            _configuration = configuration;
            cs = _configuration.GetConnectionString("ItsStorage");
            storageAccount = CloudStorageAccount.Parse(cs);
            tableClient = storageAccount.CreateCloudTableClient(new TableClientConfiguration());
            filesTable = tableClient.GetTableReference("files");

            filesTable.CreateIfNotExistsAsync();
        }

        [FunctionName("ShowFilesInTable")]
        public IEnumerable<FileTable> Run([HttpTrigger(AuthorizationLevel.Anonymous, "get",Route = null)] HttpRequest req,ILogger log)
        {
            log.LogInformation("C# HTTP trigger function processed a request.");

            var storageAccount = CloudStorageAccount.Parse(_configuration.GetConnectionString("ItsStorage"));
            var tableClient = storageAccount.CreateCloudTableClient(new TableClientConfiguration());
            var table = tableClient.GetTableReference("files");

            var list = table.ExecuteQuery(new TableQuery<FileTable>());

            return list.ToArray<FileTable>();
        }

        [FunctionName("QueueTrigger")]
        public void RunQueue([QueueTrigger("filequeue", Connection = "ItsStorage")] string myQueueItem, ILogger log)
        {
            log.LogInformation($"C# Queue trigger function processed: {myQueueItem}");

            var fileToAdd = JsonSerializer.Deserialize<FileModel>(myQueueItem);
            FileTable ft = new FileTable(fileToAdd.FileName, fileToAdd.Extension);

            if (fileToAdd.ChangeType == WatcherChangeTypes.Created)
            {
                var insertFile = TableOperation.Insert(ft);
                filesTable.ExecuteAsync(insertFile).ConfigureAwait(false);
            }
            else if(fileToAdd.ChangeType == WatcherChangeTypes.Deleted)
            {
                var fileToDelete = TableOperation.Retrieve<FileTable>(fileToAdd.Extension, fileToAdd.FileName);
                TableResult result = filesTable.Execute(fileToDelete);
                var deleteEntity = (FileTable)result.Result;
                TableOperation delete = TableOperation.Delete(deleteEntity);

                filesTable.Execute(delete);

                //await filesClient.ExecuteAsync(deleteFile).ConfigureAwait(false);
            }else if(fileToAdd.ChangeType == WatcherChangeTypes.Renamed)
            {
                var fileToDelete = TableOperation.Retrieve<FileTable>(fileToAdd.OldExtension, fileToAdd.OldName);
                TableResult result = filesTable.Execute(fileToDelete);
                var deleteEntity = (FileTable)result.Result;
                TableOperation delete = TableOperation.Delete(deleteEntity);
                filesTable.Execute(delete);

                var insertFile = TableOperation.Insert(ft);
                filesTable.ExecuteAsync(insertFile).ConfigureAwait(false);
            }
        }
    }
    
}
