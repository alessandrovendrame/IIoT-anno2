using System;
using System.Collections.Generic;
using System.Text;

namespace IIOT.Vendrame.Simulations.Data.Models
{
    public class TermoSim
    {
        public bool Stato { get; set; }
        public double Temperatura { get; set; }
        public string Modalita { get; set; }
        public int VelocitaVentole { get; set; }

        public TermoSim()
        {
            Stato = false;
            Modalita = "Manuale";
            VelocitaVentole = 0;
        }

        public void GetTemperature()
        {
            double MIN_TEMP = 0.0;
            double MAX_TEMP = 50.0;

            var random = new Random();

            Temperatura = random.NextDouble() * (MAX_TEMP-MIN_TEMP) + MIN_TEMP;
        }

        public void GetVelocita()
        {
            int MIN_VEL = 0;
            int MAX_VEL = 6;

            var random = new Random();

            VelocitaVentole = random.Next(MIN_VEL, MAX_VEL);
        }
    }
}
