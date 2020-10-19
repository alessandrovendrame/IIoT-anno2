using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using ITS.Vendrame.IITS.Northwind.Data.Models;
using ITS.Vendrame.IITS.Northwind.Data.Repositories;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;

namespace ITS.Vendrame.IITS.Northwind.WebApi.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class CustomersController : ControllerBase
    {
        private readonly ICustomersRepository _customerRepository;

        public CustomersController(ICustomersRepository customerRepository)
        {
            _customerRepository = customerRepository;
        }

        // GET: api/Customers
        [HttpGet]
        public IEnumerable<Customer> Get()
        {
            return _customerRepository.getAll();
        }

        // GET: api/Customers/5
        [HttpGet("{id}")]
        public IActionResult Get(string id)
        {
            var customer = _customerRepository.GetById(id);

            if (customer == null)
                return NotFound();

            return Ok(customer);
        }

        // POST: api/Customers
        [HttpPost]
        public void Post([FromBody] Customer customer)
        {
            _customerRepository.Insert(customer);
        }

        // PUT: api/Customers/5
        [HttpPut("{id}")]
        public IActionResult Put(string id, [FromBody] Customer customer)
        {
            var dbCus = _customerRepository.GetById(id);

            if (dbCus == null)
                return NotFound();

            customer.CustomerID = id;
            _customerRepository.Update(customer);
            return NoContent();
        }

        // DELETE: api/ApiWithActions/5
        [HttpDelete("{id}")]
        public IActionResult Delete(string id)
        {
            var dbCus = _customerRepository.GetById(id);

            if (dbCus == null)
                return NotFound();

            _customerRepository.Delete(id);
            return NoContent();
        }
    }
}
