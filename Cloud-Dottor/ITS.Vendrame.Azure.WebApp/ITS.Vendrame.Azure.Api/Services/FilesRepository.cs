using ITS.Vendrame.Azure.Data.Models;
using Microsoft.Azure.Cosmos.Table;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading.Tasks;

namespace ITS.Vendrame.Azure.Api.Services
{
    public class FilesRepository : IFilesRepository
    {
        public IEnumerable<FileTable> getAll(string connectionString)
        {
            var storageAccount = CloudStorageAccount.Parse(connectionString);
            var tableClient = storageAccount.CreateCloudTableClient(new TableClientConfiguration());
            var filesTable = tableClient.GetTableReference("files");

            var entities = filesTable.ExecuteQuery(new TableQuery<FileTable>()).ToList();

            return entities.ToList();
        }
    }
}
