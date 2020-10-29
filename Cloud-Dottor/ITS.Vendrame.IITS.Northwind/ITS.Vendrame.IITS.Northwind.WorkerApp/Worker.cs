using System;
using System.Collections.Generic;
using System.Diagnostics.Tracing;
using System.IO;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using ITS.Vendrame.IITS.Northwind.WorkerApp.Models;
using ITS.Vendrame.IITS.Northwind.WorkerApp.Request;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;
using Newtonsoft.Json;

namespace ITS.Vendrame.IITS.Northwind.WorkerApp
{
    public class Worker : BackgroundService
    {
        private readonly ILogger<Worker> _logger;
        private readonly IRequestNorthwindApi _requestNorthwindApi;

        public Worker(ILogger<Worker> logger, IRequestNorthwindApi requestNorthwindApi)
        {
            _logger = logger;
            _requestNorthwindApi = requestNorthwindApi;
        }

        private async void OnChanged(object source, FileSystemEventArgs e)
        {
            // Specify what is done when a file is changed, created, or deleted.
            Console.WriteLine($"File: {e.FullPath} {e.ChangeType}");

            var categoria = JsonConvert.DeserializeObject<CategoryModel>(File.ReadAllText(e.FullPath));

            var messaggio = await _requestNorthwindApi.Insert(categoria);

            _logger.LogInformation(messaggio.Message);

            File.Delete(e.FullPath);
        }

        protected override async Task ExecuteAsync(CancellationToken stoppingToken)
        {
            FileSystemWatcher watcher = new FileSystemWatcher();
            watcher.Path = "C:\\FolderToCheck\\";

            // Watch for changes in LastAccess and LastWrite times, and
            // the renaming of files or directories.
            watcher.NotifyFilter = NotifyFilters.LastAccess
                                 | NotifyFilters.LastWrite
                                 | NotifyFilters.FileName
                                 | NotifyFilters.DirectoryName;

            // Only watch text files.
            watcher.Filter = "*.json";

            // Add event handlers.
            watcher.Created += OnChanged;
            // watcher.Changed += OnChanged;

            // Begin watching.
            watcher.EnableRaisingEvents = true;


            while (!stoppingToken.IsCancellationRequested)
            {

                _logger.LogInformation("Worker running at: {time}", DateTimeOffset.Now);

                var categories = _requestNorthwindApi.GetAll();

                /*foreach(CategoryModel x in categories)
                {
                    _logger.LogInformation("ID categoria: " + x.CategoryId + "\nNome categoria: " + x.CategoryName + "\nDescription: " + x.Description);
                }*/

                //var messaggio = await _requestNorthwindApi.Insert(new CategoryModel{ CategoryName = "xxx", Description = "aaa"});

                //_logger.LogInformation(messaggio.Message);

                await Task.Delay(10000, stoppingToken);
            }
        }
    }
}
