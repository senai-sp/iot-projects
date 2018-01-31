using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace busHelper.Dados.Model
{
    public class Sensor
    {
        public Sensor()
        {

        }

        public Sensor(int valor, double lat, double lng, TipoSensor tipo, AcaoSensor acao)
        {
            this.valor = valor;
            this.lat = lat;
            this.lng = lng;
            this.tipo = tipo;
            this.acao = acao;
        }

        public int Id { get; set; }
        public int valor { get; set; }
        public double lat { get; set; }
        public double lng { get; set; }
        public TipoSensor tipo { get; set; }
        public AcaoSensor acao { get; set; }
        public virtual Veiculo veiculo { get; set; }

    }
}