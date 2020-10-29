using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Text;

namespace ITS.Vendrame.IITS.Northwind.WorkerApp.Models
{
    public class CategoryModel
    {
        [JsonProperty("categoryID")]
        public int CategoryId { get; set; }
        [JsonProperty("categoryName")]
        public string CategoryName { get; set; }
        [JsonProperty("description")]
        public string Description { get; set; }
    }
}
