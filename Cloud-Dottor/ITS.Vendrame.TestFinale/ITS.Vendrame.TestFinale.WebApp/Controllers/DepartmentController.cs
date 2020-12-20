using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using ITS.Vendrame.TestFinale.Data.Models;
using ITS.Vendrame.TestFinale.WebApp.Services;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Azure.Devices.Shared;
using Microsoft.Extensions.Configuration;

namespace ITS.Vendrame.TestFinale.WebApp.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class DepartmentController : ControllerBase
    {
        private readonly IConfiguration _configuration;
        public DepartmentController(IConfiguration configuration)
        {
            _configuration = configuration;
        }

        // GET: api/Department
        [HttpGet]
        public Task<DepartmentModel> Get()
        {
            TwinService twin = new TwinService(_configuration);
            var department = twin.GetDesired();

            return department;
        }

        // GET: api/Department/5
        [HttpGet("{id}", Name = "Get")]
        public string Get(int id)
        {
            return "value";
        }

        // POST: api/Department
        [HttpPost]
        public void Post([FromBody] DepartmentModel departmentInfo)
        {
            TwinService twin = new TwinService(_configuration);
            twin.Desired(departmentInfo);
        }

        // PUT: api/Department/5
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
