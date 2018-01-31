using System;
using System.Collections.Generic;
using Microsoft.EntityFrameworkCore.Migrations;

namespace busHelper.Migrations
{
    public partial class updateVeiculo : Migration
    {
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.AddColumn<int>(
                name: "capacidadeEmPe",
                table: "veiculos",
                nullable: false,
                defaultValue: 0);

            migrationBuilder.AddColumn<int>(
                name: "capacidadeSentados",
                table: "veiculos",
                nullable: false,
                defaultValue: 0);

            migrationBuilder.AddColumn<double>(
                name: "status",
                table: "veiculos",
                nullable: false,
                defaultValue: 0.0);
        }

        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropColumn(
                name: "capacidadeEmPe",
                table: "veiculos");

            migrationBuilder.DropColumn(
                name: "capacidadeSentados",
                table: "veiculos");

            migrationBuilder.DropColumn(
                name: "status",
                table: "veiculos");
        }
    }
}
