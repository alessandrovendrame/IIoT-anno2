using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Azure.Cosmos.Table;

namespace ITS.Vendrame.Azure.Data.Models
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
