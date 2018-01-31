using busHelper.Dados.Model;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace busHelper.ViewModel
{
    public class NovoSensorViewModel
    {
        public int valor { get; set; }
        public double lat { get; set; }
        public double lng { get; set; }
        public int veiculoId { get; set; }
        public TipoSensor tipo { get; set; }
        public AcaoSensor acao { get; set; }
    }
}
