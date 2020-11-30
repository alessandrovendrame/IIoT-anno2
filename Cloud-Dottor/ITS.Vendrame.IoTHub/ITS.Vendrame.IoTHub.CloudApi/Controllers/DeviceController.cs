using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ITS.Vendrame.IoTHub.Data.Models;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Azure.Devices;
using Microsoft.Extensions.Configuration;

namespace ITS.Vendrame.IoTHub.CloudApi.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class DeviceController : ControllerBase
    {
        private readonly ServiceClient _serviceClient;
        private readonly IConfiguration _configuration;

        public DeviceController(IConfiguration configuration)
        {
            _configuration = configuration;
            _serviceClient = ServiceClient.CreateFromConnectionString(_configuration.GetConnectionString("IotHub"));
        }

        // GET: api/Device
        [HttpGet]
        public IEnumerable<string> Get()
        {
            return new string[] { "value1", "value2" };
        }

        // GET: api/Device/5
        [HttpGet("{id}", Name = "Get")]
        public string Get(int id)
        {
            return "value";
        }

        // POST: api/Device
        [HttpPost]
        public IActionResult Post([FromBody] Messaggio messaggio)
        {
            var message = new Message(Encoding.ASCII.GetBytes(messaggio.MessageText));
            _serviceClient.SendAsync(messaggio.DeviceId, message);

            return Ok();
        }

        // PUT: api/Device/5
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
