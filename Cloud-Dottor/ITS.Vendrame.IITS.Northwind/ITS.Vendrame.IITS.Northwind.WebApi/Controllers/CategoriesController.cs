using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using ITS.Vendrame.IITS.Northwind.Data;
using ITS.Vendrame.IITS.Northwind.Data.Models;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;

namespace ITS.Vendrame.IITS.Northwind.WebApi.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class CategoriesController : ControllerBase
    {
        private readonly ICategoriesRepository _categoriesRepository;

        public CategoriesController(ICategoriesRepository categoriesRepository)
        {
            _categoriesRepository = categoriesRepository;
        }

        // GET: api/Categories
        [HttpGet]
        public IEnumerable<Category> Get()
        {
            return _categoriesRepository.getAll();
        }

        // GET: api/Categories/5
        [HttpGet("{id}", Name = "Get")]
        public Category Get(int id)
        {
            return _categoriesRepository.GetById(id);
        }

        // POST: api/Categories
        [HttpPost]
        public void Post([FromBody] Category category)
        {
            _categoriesRepository.Insert(category);
        }

        // PUT: api/Categories/5
        [HttpPut("{id}")]
        public void Put([FromBody] Category category)
        {
            _categoriesRepository.Update(category);
        }

        // DELETE: api/ApiWithActions/5
        [HttpDelete("{id}")]
        public void Delete(int id)
        {
            _categoriesRepository.Delete(id);
        }
    }
}
