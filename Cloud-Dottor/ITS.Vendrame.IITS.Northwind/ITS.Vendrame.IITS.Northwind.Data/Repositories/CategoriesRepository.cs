using Dapper.Contrib.Extensions;
using ITS.Vendrame.IITS.Northwind.Data.Models;
using Microsoft.Data.SqlClient;
using Microsoft.Extensions.Configuration;
using System;
using System.Collections.Generic;
using System.Text;

namespace ITS.Vendrame.IITS.Northwind.Data.Repositories
{
    public class CategoriesRepository : ICategoriesRepository
    {
        private readonly IConfiguration _configuration;
        private readonly string _connectionString;

        public CategoriesRepository(IConfiguration configuration)
        {
            _configuration = configuration;
            _connectionString = configuration.GetConnectionString("Northwind");
        }

        public void Delete(int categoryId)
        {
            using (var connection = new SqlConnection(_connectionString))
            {
                connection.Delete(new Category() { CategoryId = categoryId });
            }
        }

        public IEnumerable<Category> getAll()
        {
            using (var connection = new SqlConnection(_connectionString))
            {
                return connection.GetAll<Category>();
            }
        }

        public Category GetById(int id)
        {
            using (var connection = new SqlConnection(_connectionString))
            {
                return connection.Get<Category>(id);
            }
        }

        public void Insert(Category category)
        {
            using (var connection = new SqlConnection(_connectionString))
            {
                connection.Insert(category);
            }
        }

        public void Update(Category category)
        {
            using (var connection = new SqlConnection(_connectionString))
            {
                connection.Update(category);
            }
        }
    }
}
