using System;
using System.Collections.Generic;
using System.Text;

namespace ITS.Vendrame.TestFinale.Data.Models
{
    public class DepartmentModel
    {
        public DepartmentModel(string departmentId, int ticketNumber)
        {
            DepartmentId = departmentId;
            TicketNumber = ticketNumber;
        }

        public DepartmentModel()
        {

        }

        public string DepartmentId { get; set; }
        public int TicketNumber { get; set; }

        public string getTicket()
        {
            if(TicketNumber < 10)
            {
                return DepartmentId + "00" + TicketNumber;
            }else if(TicketNumber < 100)
            {
                return DepartmentId + "0" + TicketNumber;
            }else
            {
                return DepartmentId + "" + TicketNumber;
            }           
        }
    }
}
