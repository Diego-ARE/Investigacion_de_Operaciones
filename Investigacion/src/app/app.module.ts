import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
import { AppComponent } from './app.component';
import { AngularFireModule } from '@angular/fire/compat';
import { AngularFireDatabaseModule } from '@angular/fire/compat/database';
import { AsignacionAuxiliaresComponent } from './asignacion-auxiliares/asignacion-auxiliares.component';
import { FormsModule } from '@angular/forms';

import { HttpClientModule } from '@angular/common/http'; 

@NgModule({
  declarations: [
    AppComponent,
    AsignacionAuxiliaresComponent,
  ],
  imports: [
    BrowserModule,
    FormsModule,
    HttpClientModule,

  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }
