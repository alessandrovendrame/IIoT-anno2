using ITS.Vendrame.Azure.Data.Models;
using Microsoft.Azure.Cosmos.Table;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace ITS.Vendrame.Azure.Api.Services
{
    public interface IFilesRepository
    {
        public IEnumerable<FileTable> getAll(string connectionString);
    }
}
