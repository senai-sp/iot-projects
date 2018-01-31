using busHelper.Dados.Model;
using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace busHelper.Dados
{
    public class BusHelperContext : DbContext
    {
        public BusHelperContext(DbContextOptions<BusHelperContext> options) : base(options)
        {

        }

        public DbSet<Sensor> sensores { get; set; }
        public DbSet<HistoricoSensor> historicoSensores { get; set; }
        public DbSet<Veiculo> veiculos { get; set; }

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            
        }
    }
}
