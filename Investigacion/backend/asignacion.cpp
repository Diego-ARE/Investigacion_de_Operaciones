#include <glpk.h>  // Incluimos la biblioteca GLPK para resolver problemas de programación lineal
#include <cstdio>
#include <iostream> // Incluimos la biblioteca para entrada/salida estándar

int main(int argc, char* argv[]) {
    // Se Valida si se paso la cantidad correcta de datos
    if (argc != 7) {
        std::cerr << "Uso: " << argv[0] << " horasCarga horasDescarga horasOrganizacion costoA costoB costoC" << std::endl;
        return 1; //Codigo de error si la entrada es incorrecta
    }

    // Convertimos los datos del fronted a variables de tipo double
    double horasCarga = std::stod(argv[1]);          // Horas de carga
    double horasDescarga = std::stod(argv[2]);       // Horas de descarga
    double horasOrganizacion = std::stod(argv[3]);   // Horas de organización
    double costoA = std::stod(argv[4]);               // Costo por hora del auxiliar Tipo A - Propio
    double costoB = std::stod(argv[5]);               // Costo por hora del auxiliar Tipo B -Tercerisado
    double costoC = std::stod(argv[6]);               // Costo por hora del auxiliar  Tipo C -Temporal




    // Creación del problema de programación lineal
    glp_prob *lp; 													// Declaramos un puntero para el problema
    lp = glp_create_prob(); 										// Creamos un nuevo problema
    glp_set_prob_name(lp, "Asignacion de auxiliares de bodega"); 	// Nombre del problema
    glp_set_obj_dir(lp, GLP_MIN);  									// Definimos que queremos minimizar el costo


    // RESTRICCIONES
    glp_add_rows(lp, 3);  // Agregamos tres restricciones
    glp_set_row_name(lp, 1, "Horas_Carga"); 			// Nombre de la primera restricción
    glp_set_row_bnds(lp, 1, GLP_LO, horasCarga, 0.0);  	// Restricción: carga >= horasCarga
	
    glp_set_row_name(lp, 2, "Horas_Descarga"); 				// Nombre de la segunda restricción
    glp_set_row_bnds(lp, 2, GLP_LO, horasDescarga, 0.0);  	// Restricción: descarga >= horasDescarga
	
    glp_set_row_name(lp, 3, "Horas_Organizacion"); 				// Nombre de la tercera restricción
    glp_set_row_bnds(lp, 3, GLP_LO, horasOrganizacion, 0.0);  	// Restricción: organización >= horasOrganizacion



    // Definir las variables de decisión (x1, x2, x3, x4, x5, x6)
    glp_add_cols(lp, 6);  // Agregamos seis variables



    // Definición de la variable x1: Horas de carga por auxiliares tipo A
    glp_set_col_name(lp, 1, "x1"); 													// Nombre de la variable
    glp_set_col_bnds(lp, 1, GLP_LO, 0.0, 0.0);  									// Restricción: x1 >= 0
    glp_set_obj_coef(lp, 1, costoA);  												// Coeficiente del costo para x1 (Auxiliar A)

    // Definición de la variable x2: Horas de descarga por auxiliares tipo A
    glp_set_col_name(lp, 2, "x2"); 													// Nombre de la variable
    glp_set_col_bnds(lp, 2, GLP_LO, 0.0, 0.0);  									// Restricción: x2 >= 0
    glp_set_obj_coef(lp, 2, costoA);  												// Coeficiente del costo para x2 (Auxiliar A)

    // Definición de la variable x3: Horas de organización por auxiliares tipo A
    glp_set_col_name(lp, 3, "x3"); 													// Nombre de la variable
    glp_set_col_bnds(lp, 3, GLP_LO, 0.0, 0.0);  									// Restricción: x3 >= 0
    glp_set_obj_coef(lp, 3, costoA);  												// Coeficiente del costo para x3 (Auxiliar A)

    // Definición de la variable x4: Horas de carga por auxiliares tipo B
    glp_set_col_name(lp, 4, "x4"); 													// Nombre de la variable
    glp_set_col_bnds(lp, 4, GLP_LO, 0.0, 0.0);  									// Restricción: x4 >= 0
    glp_set_obj_coef(lp, 4, costoB);  												// Coeficiente del costo para x4 (Auxiliar B)

    // Definición de la variable x5: Horas de organización por auxiliares tipo B
    glp_set_col_name(lp, 5, "x5"); 													// Nombre de la variable
    glp_set_col_bnds(lp, 5, GLP_LO, 0.0, 0.0);  									// Restricción: x5 >= 0
    glp_set_obj_coef(lp, 5, costoB);  												// Coeficiente del costo para x5 (Auxiliar B)

    // Definición de la variable x6: Horas de descarga por auxiliares tipo C
    glp_set_col_name(lp, 6, "x6"); 													// Nombre de la variable
    glp_set_col_bnds(lp, 6, GLP_LO, 0.0, 0.0);  									// Restricción: x6 >= 0
    glp_set_obj_coef(lp, 6, costoC);  												// Coeficiente del costo para x6 (Auxiliar C)



    // Definir la matriz de coeficientes (matriz de restricciones)
    int ia[1+9], ja[1+9];  													// aRREGLO para almacenar las dimensiones de la matriz
    double ar[1+9];  														// Arreglo para almacenar los valores de la matriz


    // Restricción 1: Carga >= horasCarga (x1 + x4 >= horasCarga)
    ia[1] = 1, ja[1] = 1, ar[1] = 1.0;  // Auxiliar A, Restriccion Carga
    ia[2] = 1, ja[2] = 4, ar[2] = 1.0;  // Auxiliar B, Restriccion Carga

    // Restricción 2: Descarga >= horasDescarga (x2 + x6 >= horasDescarga)
    ia[3] = 2, ja[3] = 2, ar[3] = 1.0;  // Auxiliar A, Restriccion Descarga
    ia[4] = 2, ja[4] = 6, ar[4] = 1.0;  // Auxiliar C, Restriccion Descarga

    // Restricción 3: Organización >= horasOrganizacion (x3 + x5 >= horasOrganizacion)
    ia[5] = 3, ja[5] = 3, ar[5] = 1.0;  //	Auxiliar A, Restriccion organizacion
    ia[6] = 3, ja[6] = 5, ar[6] = 1.0;  // 	Auxiliar B, Restriccion organizacion

    // Cargar la matriz de coeficientes en el problema
    glp_load_matrix(lp, 6, ia, ja, ar);

    
    glp_simplex(lp, NULL);												// Resolver el problema usando el método simplex

    // Resultado en formato JSON
    std::string resultado = "{\n";
    resultado += "  \"costo_minimo\": " + std::to_string(glp_get_obj_val(lp)) + ",\n"; 					// Costo mínimo obtenido
    resultado += "  \"horas_carga_tipo_A\": " + std::to_string(glp_get_col_prim(lp, 1)) + ",\n"; 		// Horas de carga de tipo A
    resultado += "  \"horas_descarga_tipo_A\": " + std::to_string(glp_get_col_prim(lp, 2)) + ",\n"; 	// Horas de descarga de tipo A
    resultado += "  \"horas_organizacion_tipo_A\": " + std::to_string(glp_get_col_prim(lp, 3)) + ",\n"; // Horas de organización de tipo A
    resultado += "  \"horas_carga_tipo_B\": " + std::to_string(glp_get_col_prim(lp, 4)) + ",\n"; 		// Horas de carga de tipo B
    resultado += "  \"horas_organizacion_tipo_B\": " + std::to_string(glp_get_col_prim(lp, 5)) + ",\n"; // Horas de organización de tipo B
    resultado += "  \"horas_descarga_tipo_C\": " + std::to_string(glp_get_col_prim(lp, 6)) + "\n"; 		// Horas de descarga de tipo C
    resultado += "}\n";

    // Imprimir el resultado en formato JSON
    std::cout << resultado;

    // Liberar la memoria utilizada por el problema
    glp_delete_prob(lp);

    return 0; // Salir del programa con éxito
}