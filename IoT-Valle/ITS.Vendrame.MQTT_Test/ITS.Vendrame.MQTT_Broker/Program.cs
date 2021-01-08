using System;
using System.Text;
using System.Threading;
using uPLibrary.Networking.M2Mqtt;
using uPLibrary.Networking.M2Mqtt.Messages;

namespace ITS.Vendrame.MQTT_Broker
{
    class Program
    {
        private static string mqttLink = "test.mosquitto.org";
        private static string topic;
        private static string message;
        private static byte code;

        static void Main(string[] args)
        {
            MqttClient client = new MqttClient(mqttLink);

            Console.Write("Inserisci topic dove vuoi ascoltare i messaggi: ");
            topic = Console.ReadLine();

            code = client.Connect(Guid.NewGuid().ToString());

            ushort id = client.Subscribe(new string[] { topic },
                                         new byte[] { MqttMsgBase.QOS_LEVEL_EXACTLY_ONCE });
            
            client.MqttMsgPublishReceived += client_MqttMsgPublishReceived;
             
        }

        static void client_MqttMsgPublishReceived(object sender, MqttMsgPublishEventArgs e)
        {
            // handle message received 
            Console.WriteLine("Received = " + Encoding.UTF8.GetString(e.Message) + " on topic " + e.Topic);
        }
    }
}
