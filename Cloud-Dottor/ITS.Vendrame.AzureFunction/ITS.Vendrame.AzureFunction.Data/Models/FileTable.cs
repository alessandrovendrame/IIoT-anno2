using Microsoft.Azure.Cosmos.Table;
using System;
using System.Collections.Generic;
using System.Text;

namespace ITS.Vendrame.AzureFunction.Data.Models
{
    public class FileTable : TableEntity
    {
        public FileTable()
        {

        }

        public FileTable(string fileName, string fileExtension)
        {
            FileName = fileName;
            FileExtension = fileExtension;
            PartitionKey = fileExtension;
            RowKey = fileName;
        }

        public string FileName { get; set; }
        public string FileExtension { get; set; }
    }
}
