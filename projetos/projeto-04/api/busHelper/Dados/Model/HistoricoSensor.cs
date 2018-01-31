using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace busHelper.Dados.Model
{
    public class HistoricoSensor
    {
        public HistoricoSensor()
        {

        }
        public HistoricoSensor(DateTime data, Sensor sensor, int valor, double lat, double lng)
        {
            this.data = data;
            this.sensor = sensor;
            this.valor = valor;
            this.lat = lat;
            this.lng = lng;
        }

        public int Id { get; set; }
        public int valor { get; set; }
        public double lat { get; set; }
        public double lng { get; set; }
        public DateTime data { get; set; }
        public Sensor sensor { get; set; }
    }
}
