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
    public class VeiculoController : Controller
    {
        private BusHelperContext _db { get; set; }
        public VeiculoController(BusHelperContext db)
        {
            this._db = db;
        }

        [HttpGet]
        public IEnumerable<Veiculo> Get()
        {
            return this._db.veiculos.ToList();
        }

        [HttpGet("{id}")]
        public VeiculoViewModel Get(int id)
        {
            var veiculo = this._db.veiculos.SingleOrDefault(s => s.Id == id);
            var historico = this._db.historicoSensores.Include(h => h.sensor).ThenInclude(s => s.veiculo).Where(h => h.sensor.veiculo.Id == id);
            var entradas = historico.Where(h => h.sensor.acao == AcaoSensor.Entrada);
            var saidas = historico.Where(h => h.sensor.acao == AcaoSensor.Saida);
            var ocupadas = entradas.Count() - saidas.Count();
            var capacidadeTotal = veiculo.capacidadeEmPe + veiculo.capacidadeSentados;

            VeiculoViewModel detalhesVeiculo = new VeiculoViewModel();
            detalhesVeiculo.veiculo = veiculo;
            detalhesVeiculo.lotacao = (ocupadas * 100) / capacidadeTotal;

            return detalhesVeiculo;
        }

        [HttpGet("{id}/sensores")]
        public IEnumerable<Sensor> GetSensores(int id)
        {
            return this._db.sensores.Include(s => s.veiculo).Where(s => s.veiculo.Id == id).ToList();
        }

        [HttpPost()]
        public Veiculo Post([FromBody] NovoVeiculoViewModel model)
        {
            var novoVeiculo = new Veiculo(
                model.codigo,
                model.capacidadeEmPe,
                model.capacidadeSentados
            );

            this._db.veiculos.Add(novoVeiculo);
            this._db.SaveChanges();

            return novoVeiculo;
        }

        [HttpPut("{id}")]
        public Veiculo Put(int id, [FromBody] AtualizaVeiculoViewModel model)
        {
            var veiculo = this._db.veiculos.SingleOrDefault(v => v.Id == id);
            veiculo.codigo = model.codigo;
            veiculo.capacidadeEmPe = model.capacidadeEmPe;
            veiculo.capacidadeSentados = model.capacidadeSentados;

            this._db.veiculos.Update(veiculo);
            this._db.SaveChanges();

            return veiculo;
        }
    }
}
