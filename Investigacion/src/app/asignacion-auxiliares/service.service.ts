import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { Observable } from 'rxjs';

@Injectable({
  providedIn: 'root'
})
export class CalculoService {
  private apiUrl = 'http://localhost:3000/calcular'; // La URL de tu backend

  constructor(private http: HttpClient) {}

  calcular(horasCarga: number, horasDescarga: number, horasOrganizacion: number, costoA: number, costoB: number, costoC: number): Observable<any> {
    // Ajusta los parámetros según los campos esperados por tu backend
    const body = { horasCarga, horasDescarga, horasOrganizacion, costoA, costoB, costoC };
    return this.http.post<any>(this.apiUrl, body); // Asume que el backend devuelve JSON
  }
}
