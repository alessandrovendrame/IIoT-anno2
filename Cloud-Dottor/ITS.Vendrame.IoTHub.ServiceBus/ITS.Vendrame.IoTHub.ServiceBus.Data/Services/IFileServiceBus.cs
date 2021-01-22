using Azure.Messaging.ServiceBus;
using System;
using System.Collections.Generic;
using System.Text;
using System.Threading.Tasks;

namespace ITS.Vendrame.IoTHub.ServiceBus.Data.Services
{
    public interface IFileServiceBus
    {
        Task MessageHandlerWriteLocal(ProcessMessageEventArgs args);
        Task MessageHandlerWriteOnDB(ProcessMessageEventArgs args);
        Task ErrorHandler(ProcessErrorEventArgs args);
        Task ReceiveMessageFromCloud(string connectionString, string topicName, string subscriptionName, string dbConnectionString = null);
    }
}
