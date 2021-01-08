using System;
using System.Text;
using System.Threading.Tasks;
using uPLibrary.Networking.M2Mqtt;
using uPLibrary.Networking.M2Mqtt.Messages;

namespace ITS.Vendrame.MQTT_Test
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

            Console.Write("Inserisci topic dove vuoi inviare il messaggio: ");
            topic = Console.ReadLine();
            Console.Write("Inserisci il messaggio che vuoi mandare: ");
            message = Console.ReadLine();

            code = client.Connect(Guid.NewGuid().ToString());

            ushort msgId = client.Publish(topic,
                                          Encoding.UTF8.GetBytes(message),
                                          MqttMsgBase.QOS_LEVEL_EXACTLY_ONCE,
                                          false);

        }
    }
}
