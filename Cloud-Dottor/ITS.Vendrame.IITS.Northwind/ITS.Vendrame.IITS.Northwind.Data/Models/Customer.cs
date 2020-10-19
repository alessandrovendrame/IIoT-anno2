using dapper = Dapper.Contrib.Extensions;
using System;
using System.Collections.Generic;
using System.Text;
using System.ComponentModel.DataAnnotations;

namespace ITS.Vendrame.IITS.Northwind.Data.Models
{
    [dapper.Table("Customers")]
    public class Customer
    {
        [dapper.ExplicitKey]
        [Required]
        [StringLength(5,MinimumLength = 3)]
        public string CustomerID { get; set; }
        [Required]
        [StringLength(40,MinimumLength = 5)]
        public string CompanyName { get; set; }
        public string ContactName { get; set; }
        public string ContactTitle { get; set; }
        public string Address { get; set; }
        public string City { get; set; }
        public string Region { get; set; }
        public string PostalCode { get; set; }
        public string Country { get; set; }
        public string Phone { get; set; }
        public string Fax { get; set; }

    }
}
