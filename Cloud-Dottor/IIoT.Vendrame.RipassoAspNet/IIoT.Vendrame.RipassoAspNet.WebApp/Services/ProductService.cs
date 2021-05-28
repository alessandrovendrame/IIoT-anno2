using IIoT.Vendrame.RipassoAspNet.WebApp.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace IIoT.Vendrame.RipassoAspNet.WebApp.Services
{
    public class ProductService
    {
        private readonly List<Product> _products;

        public ProductService()
        {
            _products = new List<Product>();

            for(int i = 0; i < 100; i++)
            {
                _products.Add(new Product()
                {
                    Id = i,
                    Name = $"Prodotto {i}",
                    Code = $"ABC{i}"
                });
            }
        }

        public IEnumerable<Product> GetAll()
        {
            return _products;
        }

        public Product GetById(int id)
        {
            return _products.FirstOrDefault(p => p.Id == id);
        }

        public void Insert(Product product)
        {
            _products.Add(product);
        }
    }
}
