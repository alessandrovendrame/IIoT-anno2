using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;

namespace IIoT.Vendrame.RipassoAspNet.WebApp.Models
{
    public class Product
    {
        public int Id { get; set; }

        [Required]
        [StringLength(50)]
        public string Name { get; set; }

        [StringLength(20)]
        public string Code { get; set; }

    }
}
