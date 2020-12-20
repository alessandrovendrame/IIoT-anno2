using Microsoft.Azure.Cosmos.Table;
using System;
using System.Collections.Generic;
using System.Text;

namespace ITS.Vendrame.TestFinale.Data.Models
{
    public class TicketEntity : TableEntity
    {
        public TicketEntity()
        {

        }

        public TicketEntity(DepartmentModel department)
        {
            PartitionKey = "IIoT";
            RowKey = department.getTicket();
        }
    }
}
