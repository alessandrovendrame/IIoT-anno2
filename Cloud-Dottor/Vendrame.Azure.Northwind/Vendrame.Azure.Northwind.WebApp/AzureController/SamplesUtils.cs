using Microsoft.Azure.Cosmos.Table;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Vendrame.Azure.Northwind.Data.Models;

namespace Vendrame.Azure.Northwind.WebApp.AzureController
{
    public class SamplesUtils
    {
        public static async Task<CategoryAzure> InsertOrMergeEntityAsync(CloudTable table, CategoryAzure category)
        {
            if (category == null)
            {
                throw new ArgumentNullException("entity");
            }

            try
            {
                // Create the InsertOrReplace table operation
                TableOperation insertOrMergeOperation = TableOperation.InsertOrMerge(category);

                // Execute the operation.
                TableResult result = await table.ExecuteAsync(insertOrMergeOperation);
                CategoryAzure insertedCustomer = result.Result as CategoryAzure;

                if (result.RequestCharge.HasValue)
                {
                    Console.WriteLine("Request Charge of InsertOrMerge Operation: " + result.RequestCharge);
                }

                return insertedCustomer;
            }
            catch (StorageException e)
            {
                Console.WriteLine(e.Message);
                Console.ReadLine();
                throw;
            }
        }
    }
}
