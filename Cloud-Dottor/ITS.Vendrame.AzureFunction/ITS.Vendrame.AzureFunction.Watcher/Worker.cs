using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text.Json;
using System.Threading;
using System.Threading.Tasks;
using ITS.Vendrame.AzureFunction.Data.Models;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;

namespace ITS.Vendrame.AzureFunction.Watcher
{
    public class Worker : BackgroundService
    {
        private readonly ILogger<Worker> _logger;
        private readonly IConfiguration _configuration;
        private readonly string _queueConnectionString;

        public Worker(ILogger<Worker> logger, IConfiguration configuration)
        {
            _logger = logger;
            _configuration = configuration;
            _queueConnectionString = _configuration.GetConnectionString("ItsStorage");
        }

        private void OnCreated(object source, FileSystemEventArgs e)
        {
            // Specify what is done when a file is changed, created, or deleted.
            Console.WriteLine($"File: {e.Name} {e.ChangeType}");

            string[] propreties = e.Name.Split(".");
            FileModel fileModel = new FileModel();
            fileModel.FileName = propreties[0];
            fileModel.Extension = propreties[1];
            fileModel.ChangeType = WatcherChangeTypes.Created;

            Queue queue = new Queue(_queueConnectionString);

            var plainTextBytes = System.Text.Encoding.UTF8.GetBytes(JsonSerializer.Serialize(fileModel));
            var JsonBase64 = System.Convert.ToBase64String(plainTextBytes);

            queue.InsertMessage("filequeue", JsonBase64);
        }

        private void OnRenamed(object source, RenamedEventArgs e)
        {
            // Specify what is done when a file is changed, created, or deleted.
            Console.WriteLine($"File: {e.Name} {e.ChangeType}");

            string[] propreties = e.Name.Split(".");
            FileModel fileModel = new FileModel();
            fileModel.FileName = propreties[0];
            fileModel.Extension = propreties[1];
            fileModel.ChangeType = WatcherChangeTypes.Renamed;
            string[] oldProp = e.OldName.Split(".");
            fileModel.OldName = oldProp[0];
            fileModel.OldExtension = oldProp[1];

            Queue queue = new Queue(_queueConnectionString);

            var plainTextBytes = System.Text.Encoding.UTF8.GetBytes(JsonSerializer.Serialize(fileModel));
            var JsonBase64 = System.Convert.ToBase64String(plainTextBytes);

            queue.InsertMessage("filequeue", JsonBase64);
        }

        private void OnDeleted(object source, FileSystemEventArgs e)
        {
            // Specify what is done when a file is changed, created, or deleted.
            Console.WriteLine($"File: {e.Name} {e.ChangeType}");

            string[] propreties = e.Name.Split(".");
            FileModel fileModel = new FileModel();
            fileModel.FileName = propreties[0];
            fileModel.Extension = propreties[1];
            fileModel.ChangeType = WatcherChangeTypes.Deleted;

            Queue queue = new Queue(_queueConnectionString);

            var plainTextBytes = System.Text.Encoding.UTF8.GetBytes(JsonSerializer.Serialize(fileModel));
            var JsonBase64 = System.Convert.ToBase64String(plainTextBytes);

            queue.InsertMessage("filequeue", JsonBase64);
        }

        protected override async Task ExecuteAsync(CancellationToken stoppingToken)
        {
            FileSystemWatcher watcher = new FileSystemWatcher();

            watcher.Path = "C:\\Users\\Alessandro Vendrame\\Desktop\\Scuola\\IIoT-anno2\\Cloud-Dottor\\ITS.Vendrame.AzureFunction\\input";

            // Watch for changes in LastAccess and LastWrite times, and
            // the renaming of files or directories.
            watcher.NotifyFilter = NotifyFilters.LastAccess
                                    | NotifyFilters.LastWrite
                                    | NotifyFilters.FileName
                                    | NotifyFilters.DirectoryName;

            // Only watch text files.
            watcher.Filter = "*.*";

            // Add event handlers.
            watcher.Created += OnCreated;
            watcher.Deleted += OnDeleted;
            watcher.Renamed += OnRenamed;

            // Begin watching.
            watcher.EnableRaisingEvents = true;



            while (!stoppingToken.IsCancellationRequested)
            {
                await Task.Delay(10000, stoppingToken);
            }
        }
    }
}
