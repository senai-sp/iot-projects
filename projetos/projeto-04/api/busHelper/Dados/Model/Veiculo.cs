using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace busHelper.Dados.Model
{
    public class Veiculo
    {
        public Veiculo()
        {

        }

        public Veiculo(string codigo, int capacidadeEmPe, int capacidadeSentados)
        {
            this.codigo = codigo;
            this.capacidadeEmPe = capacidadeEmPe;
            this.capacidadeSentados = capacidadeSentados;
        }

        public int Id { get; set; }
        public string codigo { get; set; }
        public int capacidadeEmPe { get; set; }
        public int capacidadeSentados { get; set; }
        public double status { get; set; }
    }
}
