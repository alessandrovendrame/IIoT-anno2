using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;
using System.Threading.Tasks;
using Azure.Messaging.ServiceBus;
using ITS.Vendrame.ServiceBus.Data.Models;
using ITS.Vendrame.ServiceBus.Services.Services;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Configuration;

namespace ITS.Vendrame.ServiceBus.WebApp.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class FridgeController : ControllerBase
    {
        private readonly IConfiguration _configuration;
        private readonly string topicName = "fridge";

        public FridgeController(IConfiguration configuration)
        {
            _configuration = configuration;
        }

        // GET: api/Fridge
        [HttpGet]
        public IEnumerable<FridgeStorageEntity> Get()
        {
            ServiceBusLibrary service = new ServiceBusLibrary(_configuration);

            return service.GetData();
        }

        // GET: api/Fridge/5
        [HttpGet("{id}", Name = "Get")]
        public string Get(int id)
        {
            return "value";
        }

        // POST: api/Fridge
        [HttpPost]
        public async void Post([FromBody] FridgeModel fridge)
        {
            ServiceBusLibrary service = new ServiceBusLibrary(_configuration);

            string fridgeToJson = JsonSerializer.Serialize(fridge);

            await service.SendMessageToTopicAsync(topicName,fridgeToJson);
        }

        // PUT: api/Fridge/5
        [HttpPut("{id}")]
        public void Put(int id, [FromBody] string value)
        {
        }

        // DELETE: api/ApiWithActions/5
        [HttpDelete("{id}")]
        public void Delete(int id)
        {
        }
    }
}
