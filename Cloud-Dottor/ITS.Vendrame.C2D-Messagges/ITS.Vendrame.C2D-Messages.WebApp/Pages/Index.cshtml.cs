using ITS.Vendrame.C2D_Messages.WebApp.Models;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using Microsoft.Extensions.Logging;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace ITS.Vendrame.C2D_Messages.WebApp.Pages
{
    public class IndexModel : PageModel
    {
        [BindProperty]
        public string message { get; set; }

        [BindProperty]
        public string deviceName { get; set; }

        private Sender s_Sender;
        private readonly ILogger<IndexModel> _logger;

        public IndexModel(ILogger<IndexModel> logger)
        {
            _logger = logger;
            s_Sender = new Sender();
        }

        public void OnGet()
        {

        }

        public IActionResult OnPost()
        {
            s_Sender.SendCloudToDeviceMessageAsync(deviceName,message);
            return RedirectToPage("/Index");
        }
    }
}
