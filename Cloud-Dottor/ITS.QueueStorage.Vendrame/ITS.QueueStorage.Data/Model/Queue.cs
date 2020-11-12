using Azure.Storage.Queues;
using Azure.Storage.Queues.Models;
using System;
using System.Collections.Generic;
using System.Text;
using System.Text.Json;

namespace ITS.QueueStorage.Data.Model
{
    public class Queue
    {
        private readonly string _connectionString;
        public Queue(string connectionString)
        {
            _connectionString = connectionString;
        }

        public bool CreateQueue(string queueName)
        {
            try
            {
                QueueClient queueClient = new QueueClient(_connectionString, queueName);

                queueClient.CreateIfNotExists();

                if (queueClient.Exists())
                {
                    Console.WriteLine($"Queue created: '{queueClient.Name}'");
                    return true;
                }
                else
                {
                    Console.WriteLine($"Make sure the Azurite storage emulator running and try again.");
                    return false;
                }
            }catch(Exception ex)
            {
                Console.WriteLine($"Exception: {ex.Message}\n\n");
                Console.WriteLine($"Make sure the Azurite storage emulator running and try again.");
                return false;
            }
            
        }

        //-------------------------------------------------
        // Insert a message into a queue
        //-------------------------------------------------
        public void InsertMessage(string queueName, string message)
        {
            // Instantiate a QueueClient which will be used to create and manipulate the queue
            QueueClient queueClient = new QueueClient(_connectionString, queueName);

            // Create the queue if it doesn't already exist
            queueClient.CreateIfNotExists();

            if (queueClient.Exists())
            {
                // Send a message to the queue
                queueClient.SendMessage(message);
            }

            Console.WriteLine($"Inserted: {message}");
        }

        //-------------------------------------------------
        // Process and remove a message from the queue
        //-------------------------------------------------
        public IEnumerable<Message> DequeueMessage(string queueName)
        {
            var list = new List<Message>();
            // Instantiate a QueueClient which will be used to manipulate the queue
            QueueClient queueClient = new QueueClient(_connectionString, queueName);

            if (queueClient.Exists())
            {
                // Get the next message
                QueueMessage[] retrievedMessage = queueClient.ReceiveMessages(10);

                // Process (i.e. print) the message in less than 30 seconds
                //Console.WriteLine($"Dequeued message: '{retrievedMessage[0].MessageText}'");

                foreach (var message in retrievedMessage)
                {
                    list.Add(JsonSerializer.Deserialize<Message>(message.MessageText));
                    queueClient.DeleteMessage(message.MessageId, message.PopReceipt);
                }               

            }

            return list;
        }

    }
}
