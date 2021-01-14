using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace ITS.Vendrame.EditFile
{
    class Program
    {
        static void Main(string[] args)
        {
            StreamReader fr = new StreamReader("C:\\Users\\Alessandro Vendrame\\Desktop\\Scuola\\IIoT-anno2\\Python-Mungherli\\PrintaFile\\vocaboulary.txt");
            StreamWriter sw = new StreamWriter("C:\\Users\\Alessandro Vendrame\\Desktop\\Scuola\\IIoT-anno2\\Python-Mungherli\\PrintaFile\\vocaboularyFixed.txt");

            List<string> ls = new List<string>();

            bool salta = false;

            while (!fr.EndOfStream)
            {
                var riga = fr.ReadLine();
                
                if(riga.Contains(''))
                {
                    salta = !salta;
                }else if(salta == true && riga == "")
                {
                    salta = !salta;
                }

                if (!salta)
                {
                    if(riga != "Source")
                        if (!ls.Contains(riga))
                        {
                            ls.Add(riga);
                        }
                }

                

                /*
                var splitted = riga.Split(':');

                if (splitted[0].Contains(','))
                {
                    var words = splitted[0].Split(',');

                    foreach (var c in words)
                    {
                        sw.WriteLine(c.Trim());
                    }
                }
                else if (splitted[0].Contains(' '))
                { 
                    var words = splitted[0].Split(' ');

                    foreach (var c in words)
                    {
                        if(c != "" && c!= "..." && c !="/" && c!=" ")
                            sw.WriteLine(c.Trim(' ','(',')','='));
                    }
                }*/
 
            }

            ls.Sort();

            foreach ( var word in ls)
            {
                sw.WriteLine(word);
            }

            sw.Close();
            fr.Close();
        }
    }
}
