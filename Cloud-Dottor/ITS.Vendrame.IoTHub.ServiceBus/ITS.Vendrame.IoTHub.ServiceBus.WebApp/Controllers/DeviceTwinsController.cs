using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using ITS.Vendrame.IoTHub.ServiceBus.Data.Models.DeviceTwinSettings;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Configuration;

namespace ITS.Vendrame.IoTHub.ServiceBus.WebApp.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class DeviceTwinsController : ControllerBase
    {
        private readonly IConfiguration _configuration;
        private readonly string _iotHubCS;

        public DeviceTwinsController(IConfiguration configuration)
        {
            _configuration = configuration;
            _iotHubCS = _configuration.GetConnectionString("IoT-Hub");
        }

        // POST: api/DeviceTwins
        [HttpPost]
        public async void Post([FromBody] DT_SettingsModel settings)
        {
            using (var manager = Microsoft.Azure.Devices.RegistryManager.CreateFromConnectionString(_iotHubCS))
            {
                var twin_update = await manager.GetTwinAsync("vendrame-fileDevice");
                twin_update.Properties.Desired["fileName"] = settings.LastFile;
                await manager.UpdateTwinAsync(twin_update.DeviceId, twin_update, twin_update.ETag);
            }
        }
    }
}
