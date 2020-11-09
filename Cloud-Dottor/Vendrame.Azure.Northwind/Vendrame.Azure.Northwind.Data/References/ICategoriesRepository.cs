using System;
using System.Collections.Generic;
using System.Text;

namespace Vendrame.Azure.Northwind.Data
{
    public interface ICategoriesRepository
    {
        IEnumerable<Category> getAll();
        Category GetById(int id);
        void Insert(Category category);
        void Update(Category category);
        void Delete(int categoryId);
    }
}
