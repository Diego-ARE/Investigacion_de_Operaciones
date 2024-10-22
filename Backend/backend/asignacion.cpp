#include <glpk.h>  // Incluimos la biblioteca GLPK
#include <cstdio>
#include <iostream> // Para usar std::cin


int main(int argc, char* argv[]) {
    if (argc != 7) {
        std::cerr << "Uso: " << argv[0] << " horasCarga horasDescarga horasOrganizacion costoA costoB costoC" << std::endl;
        return 1;
    }

    double horasCarga = std::stod(argv[1]);
    double horasDescarga = std::stod(argv[2]);
    double horasOrganizacion = std::stod(argv[3]);
    double costoA = std::stod(argv[4]);
	double costoB = std::stod(argv[5]);
	double costoC = std::stod(argv[6]);


    // Creación de problema
    glp_prob *lp;
    lp = glp_create_prob();
    glp_set_prob_name(lp, "Asignacion de auxiliares de bodega");
    glp_set_obj_dir(lp, GLP_MIN);  // Queremos minimizar el costo

    // Definir las restricciones
    glp_add_rows(lp, 3);  // Tres restricciones: Carga, Descarga, Organización
    glp_set_row_name(lp, 1, "Horas_Carga");
    glp_set_row_bnds(lp, 1, GLP_LO, horasCarga, 0.0);  // Carga >= horasCarga
    glp_set_row_name(lp, 2, "Horas_Descarga");
    glp_set_row_bnds(lp, 2, GLP_LO, horasDescarga, 0.0);  // Descarga >= horasDescarga
    glp_set_row_name(lp, 3, "Horas_Organizacion");
    glp_set_row_bnds(lp, 3, GLP_LO, horasOrganizacion, 0.0);  // Organización >= horasOrganizacion

    // Definir las variables de decisión (x1, x2, x3, x4, x5, x6)
    glp_add_cols(lp, 6);  // Seis variables

    // Variable x1: Horas de carga por auxiliares tipo A
    glp_set_col_name(lp, 1, "x1");
    glp_set_col_bnds(lp, 1, GLP_LO, 0.0, 0.0);  // x1 >= 0
    glp_set_obj_coef(lp, 1, costoA);  // Costo por hora del Auxiliar A

    // Variable x2: Horas de descarga por auxiliares tipo A
    glp_set_col_name(lp, 2, "x2");
    glp_set_col_bnds(lp, 2, GLP_LO, 0.0, 0.0);  // x2 >= 0
    glp_set_obj_coef(lp, 2, costoA);  // Costo por hora del Auxiliar A

    // Variable x3: Horas de organización por auxiliares tipo A
    glp_set_col_name(lp, 3, "x3");
    glp_set_col_bnds(lp, 3, GLP_LO, 0.0, 0.0);  // x3 >= 0
    glp_set_obj_coef(lp, 3, costoA);  // Costo por hora del Auxiliar A

    // Variable x4: Horas de carga por auxiliares tipo B
    glp_set_col_name(lp, 4, "x4");
    glp_set_col_bnds(lp, 4, GLP_LO, 0.0, 0.0);  // x4 >= 0
    glp_set_obj_coef(lp, 4, costoB);  // Costo por hora del Auxiliar B

    // Variable x5: Horas de organización por auxiliares tipo B
    glp_set_col_name(lp, 5, "x5");
    glp_set_col_bnds(lp, 5, GLP_LO, 0.0, 0.0);  // x5 >= 0
    glp_set_obj_coef(lp, 5, costoB);  // Costo por hora del Auxiliar B

    // Variable x6: Horas de descarga por auxiliares tipo C
    glp_set_col_name(lp, 6, "x6");
    glp_set_col_bnds(lp, 6, GLP_LO, 0.0, 0.0);  // x6 >= 0
    glp_set_obj_coef(lp, 6, costoC);  // Costo por hora del Auxiliar C

    // Definir la matriz de coeficientes (matriz de restricciones)
    int ia[1+9], ja[1+9];  // Dimensiones para la matriz de coeficientes
    double ar[1+9];

    // Restricción 1: Carga >= horasCarga (x1 + x4 >= horasCarga)
    ia[1] = 1, ja[1] = 1, ar[1] = 1.0;  // x1
    ia[2] = 1, ja[2] = 4, ar[2] = 1.0;  // x4

    // Restricción 2: Descarga >= horasDescarga (x2 + x6 >= horasDescarga)
    ia[3] = 2, ja[3] = 2, ar[3] = 1.0;  // x2
    ia[4] = 2, ja[4] = 6, ar[4] = 1.0;  // x6

    // Restricción 3: Organización >= horasOrganizacion (x3 + x5 >= horasOrganizacion)
    ia[5] = 3, ja[5] = 3, ar[5] = 1.0;  // x3
    ia[6] = 3, ja[6] = 5, ar[6] = 1.0;  // x5

    // Cargar la matriz en el problema
    glp_load_matrix(lp, 6, ia, ja, ar);

    // Resolver el problema
    glp_simplex(lp, NULL);

// Preparar el resultado en formato JSON
std::string resultado = "{\n";
resultado += "  \"costo_minimo\": " + std::to_string(glp_get_obj_val(lp)) + ",\n";
resultado += "  \"horas_carga_tipo_A\": " + std::to_string(glp_get_col_prim(lp, 1)) + ",\n";
resultado += "  \"horas_descarga_tipo_A\": " + std::to_string(glp_get_col_prim(lp, 2)) + ",\n";
resultado += "  \"horas_organizacion_tipo_A\": " + std::to_string(glp_get_col_prim(lp, 3)) + ",\n";
resultado += "  \"horas_carga_tipo_B\": " + std::to_string(glp_get_col_prim(lp, 4)) + ",\n";
resultado += "  \"horas_organizacion_tipo_B\": " + std::to_string(glp_get_col_prim(lp, 5)) + ",\n";
resultado += "  \"horas_descarga_tipo_C\": " + std::to_string(glp_get_col_prim(lp, 6)) + "\n";
resultado += "}\n";

// Imprimir el resultado en formato JSON
std::cout << resultado;

    // Liberar memoria
    glp_delete_prob(lp);

    return 0;
}
