using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using IIoT.Vendrame.RipassoAspNet.WebApp.Models;
using IIoT.Vendrame.RipassoAspNet.WebApp.Services;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;

namespace IIoT.Vendrame.RipassoAspNet.WebApp.Pages.Products
{
    public class DetailsModel : PageModel
    {
        private readonly ProductService _productService;

        public Product Product { get; set; }

        public DetailsModel(ProductService productService)
        {
            _productService = productService;
        }

        public void OnGet(int id)
        {
            Product = _productService.GetById(id);
        }
    }
}
