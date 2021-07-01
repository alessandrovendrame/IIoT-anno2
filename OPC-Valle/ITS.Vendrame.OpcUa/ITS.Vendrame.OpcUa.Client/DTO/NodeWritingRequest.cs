using System;
using System.Collections.Generic;
using System.Text;

namespace ITS.Vendrame.OpcUa.Client.DTO
{
    public class NodeWritingRequest<T> where T : IConvertible
    {
        public string NodeId { get; }

        public T Value { get; }

        public NodeWritingRequest(
            string nodeId,
            T value)
        {
            NodeId = nodeId;
            Value = value;
        }
    }
}
