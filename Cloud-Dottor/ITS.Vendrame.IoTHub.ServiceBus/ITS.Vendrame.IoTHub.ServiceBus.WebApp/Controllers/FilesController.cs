using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using ITS.Vendrame.IoTHub.ServiceBus.Data.Services.Storage;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Configuration;

namespace ITS.Vendrame.IoTHub.ServiceBus.WebApp.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class FilesController : ControllerBase
    {
        private readonly IConfiguration _configuration;
        private readonly string _dbCS;
        StorageHelper sh = new StorageHelper();

        public FilesController(IConfiguration configuration)
        {
            _configuration = configuration;
            _dbCS = _configuration.GetConnectionString("AzureDB");
        }

        // GET: api/Files/prova.txt
        [HttpGet("{fileName}", Name = "Get")]
        public string Get(string fileName)
        {
            StorageHelper sh = new StorageHelper();

            return sh.GetData(_dbCS, fileName);
        }
    }
}
