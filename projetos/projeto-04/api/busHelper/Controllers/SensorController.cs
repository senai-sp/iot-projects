using busHelper.Dados;
using busHelper.Dados.Model;
using busHelper.ViewModel;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace busHelper.Controllers
{
    [Route("api/[controller]")]
    public class SensorController : Controller
    {
        private BusHelperContext _db { get; set; }

        public SensorController(BusHelperContext db)
        {
            this._db = db;
        }
        
        [HttpGet]
        public IEnumerable<Sensor> Get()
        {
            return this._db.sensores.Include(s => s.veiculo).ToList();
        }

        [HttpGet("{id}")]
        public Sensor Get(int id)
        {
            var data = this._db.sensores.Include(s => s.veiculo).SingleOrDefault(s => s.Id == id);
            return data;
        }

        [HttpGet("historico")]
        public IEnumerable<HistoricoSensor> GetHistoricoList()
        {
            return this._db.historicoSensores.Include(h => h.sensor).Include(h => h.sensor).ToList();
        }

        [HttpGet("{id}/historico")]
        public IEnumerable<HistoricoSensor> GetHistorico(int id)
        {
            return this._db.historicoSensores.Include(h => h.sensor).Where(h => h.sensor.Id == id).ToList();
        }

        [HttpPost()]
        public Sensor Post([FromBody] NovoSensorViewModel model)
        {
            var novoSensor = new Sensor(
                valor: model.valor, 
                lat:  model.lat, 
                lng: model.lng, 
                tipo: model.tipo,
                acao: model.acao
            );

            novoSensor.veiculo = this._db.veiculos.SingleOrDefault(v => v.Id == model.veiculoId);
            this._db.sensores.Add(novoSensor);
            this._db.SaveChanges();

            return novoSensor;
        }

        [HttpPut("{id}")]
        public Sensor Put(int id, [FromBody] AtualizaSensorViewModel model)
        {
            var sensor = this._db.sensores.SingleOrDefault(s => s.Id == id);
            sensor.valor = model.valor;
            sensor.lat = model.lat;
            sensor.lng = model.lng;

            var entradaHistorico = new HistoricoSensor(
                data: DateTime.Now, 
                sensor: sensor, 
                valor: model.valor,
                lat: model.lat,
                lng: model.lng
            );

            this._db.sensores.Update(sensor);
            this._db.SaveChanges();

            this._db.historicoSensores.Add(entradaHistorico);
            this._db.SaveChanges();

            return sensor;
        }
    }
}
