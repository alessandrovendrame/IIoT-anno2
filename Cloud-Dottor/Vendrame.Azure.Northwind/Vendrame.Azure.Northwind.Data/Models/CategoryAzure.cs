using Microsoft.Azure.Cosmos.Table;
using System;
using System.Collections.Generic;
using System.Text;

namespace Vendrame.Azure.Northwind.Data.Models
{
    public class CategoryAzure : TableEntity
    {
        public CategoryAzure(int categoryId, string categoryName)
        {
            PartitionKey = categoryId.ToString();
            RowKey = categoryName;
        }
        public int CategoryId { get; set; }
        public string CategoryName { get; set; }
        public string Description { get; set; }
    }
}
