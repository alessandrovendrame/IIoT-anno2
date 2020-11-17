using System;
using System.Collections.Generic;
using System.Text;

namespace ITS.Vendrame.Azure.Data.Models
{
    public class FileModel
    {
        public string FileName { get; set; }
        public string Extension { get; set; }
        public bool Alive { get; set; }
    }
}
