using IIoT.Vendrame.RipassoAspNet.WebApp.Models;
using IIoT.Vendrame.RipassoAspNet.WebApp.Services;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using Microsoft.Extensions.Logging;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace IIoT.Vendrame.RipassoAspNet.WebApp.Pages
{
    public class IndexModel : PageModel
    {
        private readonly ILogger<IndexModel> _logger;
        private readonly ProductService _productService;

        public IEnumerable<Product> Products { get; set; }

        public IndexModel(ILogger<IndexModel> logger, ProductService productService)
        {
            _logger = logger;
            _productService = productService;
        }

        public void OnGet()
        {
            Products = _productService.GetAll();
        }

        public IActionResult OnPost()
        {
            return Page();
        }
    }
}
