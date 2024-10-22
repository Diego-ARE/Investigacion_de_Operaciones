import { Component } from '@angular/core';
import { CalculoService } from './service.service';

@Component({
  selector: 'app-asignacion-auxiliares',
  templateUrl: './asignacion-auxiliares.component.html',
  styleUrls: ['./asignacion-auxiliares.component.css']
})
export class AsignacionAuxiliaresComponent {
  horasCarga!: number;
  horasDescarga!: number;
  horasOrganizacion!: number;
  costoA!: number;
  costoB!: number;
  costoC!: number;

  resultado: any = {}; // Objeto para almacenar los resultados procesados

  constructor(private calculoService: CalculoService) {}

  calcularCostoMinimo() {
    this.calculoService.calcular(this.horasCarga, this.horasDescarga, this.horasOrganizacion, this.costoA, this.costoB, this.costoC)
      .subscribe(
        (data: any) => {
          console.log(data); // Agrega esta línea
          // Asigna directamente los datos del backend al objeto resultado
          this.resultado = data;
        },
        (error) => {
          console.error('Error al realizar el cálculo', error);
        }
      );
  }
}
