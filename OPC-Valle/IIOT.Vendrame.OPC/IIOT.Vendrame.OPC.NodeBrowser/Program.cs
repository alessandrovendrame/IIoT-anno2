using IIOT.Vendrame.OPC.Data.Comparer;
using IIOT.Vendrame.OPC.Data.Services;
using System;
using System.Collections;

namespace IIOT.Vendrame.OPC.NodeBrowser
{
    class Program
    {
        static void Main(string[] args)
        {
            var communicationService = new PlcCommunicationService();

            communicationService.StartAsync("opc.tcp://uademo.prosysopc.com:53530/OPCUA/SimulationServer").GetAwaiter().GetResult();


            getTree("i=85", communicationService,0);
            
        }

        public static void getTree(string startingNode, PlcCommunicationService service, int subLevel)
        {
            var nodeList = service.BrowseNode(startingNode);

            if(nodeList.Count > 0)
            {
                var array = nodeList.ToArray();
                Array.Sort(array, new NodeComparer());

                foreach (var element in array)
                {
                    var subNodes = service.BrowseNode(element.NodeId.ToString());

                    var subArray = subNodes.ToArray();
                    Array.Sort(subArray, new NodeComparer());

                    for (int i = 0; i < subLevel; i++)
                    {
                        Console.Write("  ");
                    }

                    Console.WriteLine("-" + element);

                    if (subNodes.Count > 0)
                    {
                        var newsubLevel = subLevel+1;

                        foreach (var subnode in subArray)
                        {
                            for (int i = 0; i < newsubLevel; i++)
                            {
                                Console.Write("  ");
                            }
                            Console.WriteLine("-" + subnode);
                            var newLevel = newsubLevel+1;
                            getTree(subnode.NodeId.ToString(), service, newLevel);
                        }
                    }
                }
            }
            
        }

        
    }
}
