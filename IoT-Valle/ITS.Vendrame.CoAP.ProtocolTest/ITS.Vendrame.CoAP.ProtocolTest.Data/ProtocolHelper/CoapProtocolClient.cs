using CoAP;
using System;
using System.Collections.Generic;
using System.Text;

namespace ITS.Vendrame.CoAP.ProtocolTest.Data.ProtocolHelper
{
    public class CoapProtocolClient
    {
        // create a new client
        CoapClient client;
        Request request;
        
        public CoapProtocolClient()
        {
            
            client = new CoapClient();
            // set the Uri to visit
            client.Uri = new Uri("coap://192.168.104.60:5683/hello-world");

            /*
            request = new Request(Method.GET);
            request.URI = new Uri("coap://192.168.104.60:5683/hello-world");
            */
        }

        public string Get()
        {
            
            // now send a GET request to say hello~
            var response = client.Get();

            return response.PayloadString;
            
            /*
            request.Send();

            // wait for one response
            Response response = request.WaitForResponse();

            return response.Payload.ToString();
            */
        }

        public void Post(string message)
        {
            client.Uri = new Uri("coap://192.168.104.60:5683/hello-world");
            client.Post(message);
        }
    }
}
