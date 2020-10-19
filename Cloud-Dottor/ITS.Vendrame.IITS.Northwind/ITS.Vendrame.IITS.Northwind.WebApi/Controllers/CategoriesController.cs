using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.RegularExpressions;
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
        [HttpGet("{id}")]
        public IActionResult Get(int id)
        {
            var category = _categoriesRepository.GetById(id);

            if (category == null)
                return NotFound();

            return Ok(category);
        }

        // POST: api/Categories
        [HttpPost]
        public void Post([FromBody] Category category)
        {
            _categoriesRepository.Insert(category);
        }

        // PUT: api/Categories/5
        [HttpPut("{id}")]
        public IActionResult Put(int id,[FromBody] Category category)
        {
            var dbCat = _categoriesRepository.GetById(id);

            if (dbCat == null)
                return NotFound();

            category.CategoryId = id;
            _categoriesRepository.Update(category);
            return NoContent();
        }

        // DELETE: api/ApiWithActions/5
        [HttpDelete("{id}")]
        public IActionResult Delete(int id)
        {
            var dbCat = _categoriesRepository.GetById(id);

            if (dbCat == null)
                return NotFound();

            _categoriesRepository.Delete(id);
            return NoContent();
        }
    }
}
