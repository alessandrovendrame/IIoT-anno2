using ITS.Vendrame.IITS.Northwind.WorkerApp.Models;
using System;
using System.Collections.Generic;
using System.Text;
using System.Threading.Tasks;

namespace ITS.Vendrame.IITS.Northwind.WorkerApp.Request
{
    public interface IRequestNorthwindApi
    {
        IEnumerable<CategoryModel> GetAll();
        Task<ApiResponse> Insert(CategoryModel c);
    }
}
