using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading.Tasks;
using ITS.Vendrame.Azure.Api.Services;
using ITS.Vendrame.Azure.Data.Models;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Azure.Cosmos.Table;
using Microsoft.Extensions.Configuration;

namespace ITS.Vendrame.Azure.Api.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class FilesController : ControllerBase
    {
        private readonly IConfiguration _configuration;
        private readonly string _connectionString;
        public FilesController(IConfiguration configuration)
        {
            _configuration = configuration;
            _connectionString = _configuration.GetConnectionString("ItsStorage");
        }
        // GET: api/Files
        [HttpGet]
        public IEnumerable<FileTable> Get()
        {
            FilesRepository fr = new FilesRepository();
            return fr.getAll(_connectionString);
        }

        // GET: api/Files/5
        [HttpGet("{id}", Name = "Get")]
        public string Get(int id)
        {
            return "value";
        }

        // POST: api/Files
        [HttpPost]
        public void Post([FromBody] string value)
        {
        }

        // PUT: api/Files/5
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
