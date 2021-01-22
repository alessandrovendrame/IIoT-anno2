using ITS.Vendrame.IoTHub.ServiceBus.Data.Models;
using System;
using System.Collections.Generic;
using System.Data.SqlClient;
using System.Linq;
using System.Text;
using System.Text.Json;

namespace ITS.Vendrame.IoTHub.ServiceBus.Data.Services.Storage
{
    public class StorageHelper
    {
        public string GetData(string connectionString, string fileName)
        {
            string testo = "";
            List<string> text = new List<string>();

            using (SqlConnection conn = new SqlConnection(connectionString))
            {
                conn.Open();

                string qry = "SELECT FileName,FileText FROM tblFile WHERE FileName = @FileName";

                using (SqlCommand cmd = new SqlCommand(qry, conn))
                {
                    cmd.Parameters.AddWithValue("FileName", fileName);

                    using (SqlDataReader reader = cmd.ExecuteReader())
                    {
                        while (reader.Read())
                        {
                            text.Add(reader["FileText"].ToString());
                        }
                    }
                }
            }

            foreach (var riga in text)
            {
                testo += riga;
                testo += "\n";
            }

            return testo;
        }

        public void Insert(string connectionString, string jsonMessage)
        {
            var file = JsonSerializer.Deserialize<FileModel>(jsonMessage);

            using ( SqlConnection conn = new SqlConnection(connectionString))
            {
                conn.Open();

                string qry = "INSERT INTO tblFile(FileName,FileText) VALUES (@FileName,@FileText)";

                using (SqlCommand cmd = new SqlCommand(qry, conn))
                {
                    cmd.Parameters.AddWithValue("FileName", file.FileName);
                    cmd.Parameters.AddWithValue("FileText", file.Text);

                    cmd.ExecuteNonQuery();
                }
            }
        }
    }
}
