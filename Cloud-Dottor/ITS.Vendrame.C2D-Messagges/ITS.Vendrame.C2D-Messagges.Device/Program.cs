using Microsoft.Azure.Devices.Client;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ITS.Vendrame.C2D_Messagges.Device
{
    class Program
    {
        private static DeviceClient s_deviceClient;
        private static string _connectionString;
        private static async Task ReceiveC2dAsync()
        {
            s_deviceClient = DeviceClient.CreateFromConnectionString(_connectionString);
            Console.WriteLine("\nReceiving cloud to device messages from service");
            while (true)
            {
                Message receivedMessage = await s_deviceClient.ReceiveAsync();
                if (receivedMessage == null) continue;

                Console.ForegroundColor = ConsoleColor.Yellow;
                Console.WriteLine("Received message: {0}",
                Encoding.ASCII.GetString(receivedMessage.GetBytes()));
                Console.ResetColor();

                await s_deviceClient.CompleteAsync(receivedMessage);
            }
        }

        static async Task Main(string[] args)
        {
            Console.WriteLine("Inserisci nome del device");
            var deviceName = Console.ReadLine();

            switch (deviceName)
            {
                case "IIOT_Device":
                    _connectionString = "HostName=vendrame-iiotHub.azure-devices.net;DeviceId=IIOT_Device;SharedAccessKey=lPsbe5Yg0hFD8HZogphetMROin7mjTmPUP36offrivM=";
                    break;
                case "IIOT_Device_2":
                    _connectionString = "HostName=vendrame-iiotHub.azure-devices.net;DeviceId=IIOT_Device_2;SharedAccessKey=fbMwFAOwHNwXI6eeT1qleeQhVDx3lGp9uyYkcGOucRE=";
                    break;
                case "IIOT_Device_3":
                    _connectionString = "HostName=vendrame-iiotHub.azure-devices.net;DeviceId=IIOT_Device_3;SharedAccessKey=wvCB5X/9nDS8t+nsIGwz1/yxZI0hdeLgfLAaOF0ZOnY=";
                    break;
                case "IIOT_Device_4":
                    _connectionString = "HostName=vendrame-iiotHub.azure-devices.net;DeviceId=IIOT_Device_4;SharedAccessKey=1uNW39GiwhhOHmcMgulSem2Tlmjy0YjbK6hQeDlCmP8=";
                    break;
            }


            await ReceiveC2dAsync();
        }
    }
}
