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
    public class InsertProductModel : PageModel
    {

        private readonly ProductService _productService;

        [BindProperty]
        public Product Input { get; set; }

        public InsertProductModel(ProductService productService)
        {
            _productService = productService;
        }

        public void OnGet()
        {
            Input = new Product();
        }

        public IActionResult OnPost()
        {
            if (ModelState.IsValid)
            {
                _productService.Insert(Input);
                return RedirectToPage("/Index");
            }

            return Page();
        }
    }
}
