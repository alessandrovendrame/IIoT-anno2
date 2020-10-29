using ITS.Vendrame.IITS.Northwind.WorkerApp.Models;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Net;
using System.Net.Http;
using System.Text;
using System.Threading.Tasks;

namespace ITS.Vendrame.IITS.Northwind.WorkerApp.Request
{
    public class RequestNorthwindApi : IRequestNorthwindApi
    {
        string url = "https://localhost:44302/api/categories";

        public RequestNorthwindApi()
        {
            ServicePointManager.ServerCertificateValidationCallback += (sender, cert, chain, sslPolicyErrors) => true;
        }
        public IEnumerable<CategoryModel> GetAll()
        {
            var client = new WebClient();
            var result = client.DownloadString(url);
         
            var res = JsonConvert.DeserializeObject<IEnumerable<CategoryModel>>(result, new JsonSerializerSettings(){ 
                Error = (sender, e) =>
                {
                    e.ErrorContext.Handled = true;
                }
            });

            return res;
        }

        public async Task<ApiResponse> Insert(CategoryModel c)
        {
            string categoria = JsonConvert.SerializeObject(c);
            using(var httpClientHandler = new HttpClientHandler())
            {
                using (var cHttp = new HttpClient(httpClientHandler))
                {
                    ServicePointManager.ServerCertificateValidationCallback += (sender, cert, chain, sslPolicyErrors) => true;
                    var data = new StringContent(categoria, Encoding.UTF8, "application/json");
                    var response = await cHttp.PostAsync(url, data);

                    var messaggio = JsonConvert.DeserializeObject<ApiResponse>(await response.Content.ReadAsStringAsync());

                    return messaggio;
                }
            }
        }
    }
}
