using ITS.Vendrame.OpcUa.Client.DTO;
using ITS.Vendrame.OpcUa.Client.Services;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ITS.Vendrame.OpcUa.Client
{
    public partial class Form1 : Form
    {

        PlcCommunicationService communicationService;

        

        public Form1()
        {
            InitializeComponent();
            communicationService = new PlcCommunicationService();
            
            

            communicationService.StartAsync("opc.tcp://laptop-l5tct0lf:26543/SampleServer").GetAwaiter().GetResult();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            checkUpdates();
        }

        private void checkUpdates()
        {
            var cpuValue = communicationService.ReadNodeValue("ns=2;i=6003");
            var ramValue = communicationService.ReadNodeValue("ns=2;i=6004");

            lblCPU.Text = cpuValue.ToString();
            lblRAM.Text = ramValue.ToString();
        }

        private void btnSendCpu_Click(object sender, EventArgs e)
        {
            var cpuToSend = Convert.ToDouble(txtCpu.Text);

            communicationService.WriteToNode(new NodeWritingRequest<double>("ns=2;i=6003", cpuToSend));

            checkUpdates();
        }

        private void btnSendRam_Click(object sender, EventArgs e)
        {
            var ramToSend = Convert.ToDouble(txtRam.Text);

            communicationService.WriteToNode(new NodeWritingRequest<double>("ns=2;i=6004", ramToSend));

            checkUpdates();
        }
    }
}
