using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace ITS.Vendrame.AzureFunction.Data.Models
{
    public class FileModel
    {
        public string FileName { get; set; }
        public string Extension { get; set; }
        public WatcherChangeTypes ChangeType { get; set; }
        public string OldName { get; set; }
        public string OldExtension { get; set; }
    }
}
