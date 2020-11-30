using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Azure.Cosmos.Table;
using Microsoft.Azure.Devices.Client;

namespace ITS.Vendrame.DeviceToCloud.Data.Models
{
    public class MessageTableModel : TableEntity
    {
        public MessageTableModel()
        {

        }

        public MessageTableModel(Guid id,string deviceId, string messageText)
        {
            Id = id;
            DeviceId = deviceId;
            MessageText = messageText;

            PartitionKey = id.ToString();
            RowKey = deviceId;
        }

        public Guid Id { get; set; }
        public string DeviceId { get; set; }
        public string MessageText { get; set; }
    }
}
