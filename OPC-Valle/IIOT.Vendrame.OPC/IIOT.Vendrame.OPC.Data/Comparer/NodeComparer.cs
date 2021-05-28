using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;

namespace IIOT.Vendrame.OPC.Data.Comparer
{
    public class NodeComparer : IComparer
    {
        public int Compare(object x, object y)
        {
            return (new CaseInsensitiveComparer()).Compare(((Opc.Ua.ReferenceDescription)x).DisplayName.ToString(), ((Opc.Ua.ReferenceDescription)y).DisplayName.ToString());
        }
    }
}
