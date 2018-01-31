using System;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Infrastructure;
using Microsoft.EntityFrameworkCore.Metadata;
using Microsoft.EntityFrameworkCore.Migrations;
using busHelper.Dados;
using busHelper.Dados.Model;

namespace busHelper.Migrations
{
    [DbContext(typeof(BusHelperContext))]
    [Migration("20180124220107_updateVeiculo")]
    partial class updateVeiculo
    {
        protected override void BuildTargetModel(ModelBuilder modelBuilder)
        {
            modelBuilder
                .HasAnnotation("ProductVersion", "1.1.2")
                .HasAnnotation("SqlServer:ValueGenerationStrategy", SqlServerValueGenerationStrategy.IdentityColumn);

            modelBuilder.Entity("busHelper.Dados.Model.HistoricoSensor", b =>
                {
                    b.Property<int>("Id")
                        .ValueGeneratedOnAdd();

                    b.Property<DateTime>("data");

                    b.Property<double>("lat");

                    b.Property<double>("lng");

                    b.Property<int?>("sensorId");

                    b.Property<int>("valor");

                    b.HasKey("Id");

                    b.HasIndex("sensorId");

                    b.ToTable("historicoSensores");
                });

            modelBuilder.Entity("busHelper.Dados.Model.Sensor", b =>
                {
                    b.Property<int>("Id")
                        .ValueGeneratedOnAdd();

                    b.Property<int>("acao");

                    b.Property<double>("lat");

                    b.Property<double>("lng");

                    b.Property<int>("tipo");

                    b.Property<int>("valor");

                    b.Property<int?>("veiculoId");

                    b.HasKey("Id");

                    b.HasIndex("veiculoId");

                    b.ToTable("sensores");
                });

            modelBuilder.Entity("busHelper.Dados.Model.Veiculo", b =>
                {
                    b.Property<int>("Id")
                        .ValueGeneratedOnAdd();

                    b.Property<int>("capacidadeEmPe");

                    b.Property<int>("capacidadeSentados");

                    b.Property<string>("codigo");

                    b.Property<double>("status");

                    b.HasKey("Id");

                    b.ToTable("veiculos");
                });

            modelBuilder.Entity("busHelper.Dados.Model.HistoricoSensor", b =>
                {
                    b.HasOne("busHelper.Dados.Model.Sensor", "sensor")
                        .WithMany()
                        .HasForeignKey("sensorId");
                });

            modelBuilder.Entity("busHelper.Dados.Model.Sensor", b =>
                {
                    b.HasOne("busHelper.Dados.Model.Veiculo", "veiculo")
                        .WithMany()
                        .HasForeignKey("veiculoId");
                });
        }
    }
}
