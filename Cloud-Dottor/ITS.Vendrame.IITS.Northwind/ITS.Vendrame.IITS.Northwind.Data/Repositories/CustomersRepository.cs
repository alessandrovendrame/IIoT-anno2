using Dapper;
using Dapper.Contrib.Extensions;
using ITS.Vendrame.IITS.Northwind.Data.Models;
using Microsoft.Data.SqlClient;
using Microsoft.Extensions.Configuration;
using System;
using System.Collections.Generic;
using System.Text;

namespace ITS.Vendrame.IITS.Northwind.Data.Repositories
{
    public class CustomersRepository : ICustomersRepository
    {
        private readonly IConfiguration _configuration;
        private readonly string _connectionString;

        public CustomersRepository(IConfiguration configuration)
        {
            _configuration = configuration;
            _connectionString = configuration.GetConnectionString("Northwind");
        }

        public void Delete(string customerId)
        {
            using (var connection = new SqlConnection(_connectionString))
            {
                connection.Delete(new Customer() { CustomerID = customerId });
            }
        }

        public IEnumerable<Customer> getAll()
        {
            using (var connection = new SqlConnection(_connectionString))
            {
                return connection.GetAll<Customer>();
            }
        }

        public Customer GetById(string id)
        {
            using (var connection = new SqlConnection(_connectionString))
            {
                return connection.Get<Customer>(id);
            }
        }

        public void Insert(Customer customer)
        {
            using (var connection = new SqlConnection(_connectionString))
            {
                //connection.Execute("INSERT INTO Customers VALUES (@val)", new {customer} );
                connection.Insert(customer);
            }
        }

        public void Update(Customer customer)
        {
            using (var connection = new SqlConnection(_connectionString))
            {
                connection.Update(customer);
            }
        }
    }
}
