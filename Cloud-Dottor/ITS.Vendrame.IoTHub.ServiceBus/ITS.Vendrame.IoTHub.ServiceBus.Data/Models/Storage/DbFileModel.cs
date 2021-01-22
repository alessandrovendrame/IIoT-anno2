using System;
using System.Collections.Generic;
using System.Text;

namespace ITS.Vendrame.IoTHub.ServiceBus.Data.Models.Storage
{
    public class DbFileModel
    {
        public int IDFile { get; set; }
        public string FileName { get; set; }
        public string Text { get; set; }
    }
}
