using IIOT.Vendrame.Simulations.Data.Models;
using System;

namespace IIOT.Vendrame.Simulations.Termostato
{
    class Program
    {
        static void Main(string[] args)
        {
            string error = null;
            int scelta;
            TermoSim termostato = new TermoSim();

            do
            {
                scelta = Menu(error);

                error = null;

                switch (scelta)
                {
                    case 0:
                        Console.WriteLine("\n\nSto chiudendo...");
                        break;
                    case 1:
                        termostato.GetTemperature();
                        Console.WriteLine("\n\nTemperatura registrata: " + termostato.Temperatura);
                        Console.WriteLine("\nPremi un tasto per continuare...");
                        Console.ReadLine();
                        break;
                    case 2:
                        termostato.GetVelocita();
                        Console.WriteLine("\n\nVelocita registrata: " + termostato.VelocitaVentole);
                        Console.WriteLine("\nPremi un tasto per continuare...");
                        Console.ReadLine();
                        break;
                    case 3:
                        Console.WriteLine("\n\nSato termostato: " + termostato.Stato);
                        Console.WriteLine("Temperatura registrata: " + termostato.Temperatura);
                        Console.WriteLine("Modalità termostato: " + termostato.Modalita);
                        Console.WriteLine("Velocita registrata: " + termostato.VelocitaVentole);
                        Console.WriteLine("\nPremi un tasto per continuare...");
                        Console.ReadLine();
                        break;
                    default:
                        error = "Devi scegliere un numero compreso tra 0 e 3!";
                        break;
                }
            } while (scelta != 0);
        }

        public static int Menu(string errore = null)
        {
            if(errore == null)
                Console.Clear();
            else
            {
                Console.Clear();
                Console.WriteLine("Errore: " + errore + "\n\n");
            }


            Console.WriteLine("|------------TERMOSTATO------------|");
            Console.WriteLine("|  1. Genera temperature           |");
            Console.WriteLine("|  2. Genera velocità              |");
            Console.WriteLine("|  3. Genera output                |");
            Console.WriteLine("|  0. Esci                         |");
            Console.WriteLine("|----------------------------------|");
            
            Console.Write("\n\nScelta: ");

            var scelta = int.Parse(Console.ReadLine());

            return scelta;
        }
    }
}
