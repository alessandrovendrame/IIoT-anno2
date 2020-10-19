using ITS.Vendrame.IITS.Northwind.Data.Models;
using System;
using System.Collections.Generic;
using System.Text;

namespace ITS.Vendrame.IITS.Northwind.Data.Repositories
{
    public interface ICustomersRepository
    {
        IEnumerable<Customer> getAll();
        Customer GetById(string id);
        void Insert(Customer customer);
        void Update(Customer customer);
        void Delete(string customerId);
    }
}
