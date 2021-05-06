using ITS.Vendrame.CoAP.ProtocolTest.Data.ProtocolHelper;
using System;

namespace ITS.Vendrame.CoAP.ProtocolTest
{
    class Program
    {
        static void Main(string[] args)
        {
            CoapProtocolClient coapProtocolClient = new CoapProtocolClient();

            Console.WriteLine(coapProtocolClient.Get());

            coapProtocolClient.Post("Hello from CoAP Client!");
        }
    }
}
