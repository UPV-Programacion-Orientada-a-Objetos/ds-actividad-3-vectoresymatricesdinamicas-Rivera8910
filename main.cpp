#include <iostream>
#include <iomanip> 

const int NUM_PRODUCTOS = 5;
const int NUM_MATERIAS_PRIMAS = 4;
const int SEMANAS_INICIALES = 4;

class PlanificadorProduccion {
private:

    float** matrizPlanificacion;    
    float* vectorCostosUnitarios;   
    float* vectorMateriaPrima;      
    float* costoAdquisicionMP;      
    int* vectorRequerimientos;    

    int numSemanasActuales;         

public:
    
    PlanificadorProduccion() {
        numSemanasActuales = SEMANAS_INICIALES;

        matrizPlanificacion = new float*[NUM_PRODUCTOS];
       
        for (int i = 0; i < NUM_PRODUCTOS; ++i) {
            matrizPlanificacion[i] = new float[numSemanasActuales];
        }
       
        for (int i = 0; i < NUM_PRODUCTOS; ++i) {
            for (int j = 0; j < numSemanasActuales; ++j) {
                matrizPlanificacion[i][j] = 100 + (i * 10) + (j * 5); // Ejemplo: 100, 105, 110...
            }
        }

       
        vectorCostosUnitarios = new float[NUM_PRODUCTOS]{10.5, 22.0, 15.75, 8.2, 30.0};
        vectorMateriaPrima = new float[NUM_MATERIAS_PRIMAS]{5000, 8000, 3000, 10000};
        costoAdquisicionMP = new float[NUM_MATERIAS_PRIMAS]{2.5, 5.0, 7.2, 1.8};

    
        vectorRequerimientos = new int[NUM_PRODUCTOS * NUM_MATERIAS_PRIMAS]{
            2, 1, 0, 3,  // Producto 0
            1, 3, 2, 1,  // Producto 1
            0, 2, 4, 0,  // Producto 2
            3, 0, 1, 2,  // Producto 3
            1, 1, 1, 1   // Producto 4
        };

        std::cout << "Sistema de Planificacion inicializado correctamente." << std::endl;
    }

    
    ~PlanificadorProduccion() {
       
        for (int i = 0; i < NUM_PRODUCTOS; ++i) {
            delete[] matrizPlanificacion[i];
        }
        
        delete[] matrizPlanificacion;
        delete[] vectorCostosUnitarios;
        delete[] vectorMateriaPrima;
        delete[] costoAdquisicionMP;
        delete[] vectorRequerimientos;

        std::cout << "Pa fuera Loco" << std::endl;
    }
    void mostrarPlan() {
        std::cout << "\n--- Plan de Produccion Actual ---" << std::endl;
        std::cout << std::fixed << std::setprecision(2);
        std::cout << std::setw(12) << "Producto" << " |";
        for (int j = 0; j < numSemanasActuales; ++j) {
            std::cout << std::setw(10) << "Semana " << j + 1 << " |";
        }
        std::cout << "\n--------------------------------------------------------------------------------\n";

        for (int i = 0; i < NUM_PRODUCTOS; ++i) {
            std::cout << std::setw(12) << "Tipo " + std::to_string(i + 1) << " |";
            for (int j = 0; j < numSemanasActuales; ++j) {
                std::cout << std::setw(10) << matrizPlanificacion[i][j] << " |";
            }
            std::cout << std::endl;
        }
    }
    
    void agregarSemana() {
        int nuevasSemanas = numSemanasActuales + 1;
        
        
        float** nuevaMatriz = new float*[NUM_PRODUCTOS];
        for (int i = 0; i < NUM_PRODUCTOS; ++i) {
            nuevaMatriz[i] = new float[nuevasSemanas];
        }

      
        for (int i = 0; i < NUM_PRODUCTOS; ++i) {
            for (int j = 0; j < numSemanasActuales; ++j) {
                nuevaMatriz[i][j] = matrizPlanificacion[i][j];
            }
           
            nuevaMatriz[i][numSemanasActuales] = 0.0f;
        }

        
        for (int i = 0; i < NUM_PRODUCTOS; ++i) {
            delete[] matrizPlanificacion[i];
        }
        delete[] matrizPlanificacion;

        matrizPlanificacion = nuevaMatriz;
        numSemanasActuales = nuevasSemanas;
        
        std::cout << "\nSe ha agregado una nueva semana al plan. El total de semanas ahora es: " << numSemanasActuales << std::endl;
    }
    
    void actualizarProduccion() {
        int producto, semana;
        float cantidad;

        std::cout << "\n--- Actualizar Plan de Produccion ---" << std::endl;
        std::cout << "Ingrese el tipo de producto (1-" << NUM_PRODUCTOS << "): ";
        std::cin >> producto;
        std::cout << "Ingrese el numero de semana (1-" << numSemanasActuales << "): ";
        std::cin >> semana;

       
        if (std::cin.fail() || producto < 1 || producto > NUM_PRODUCTOS || semana < 1 || semana > numSemanasActuales) {
            std::cout << "Entrada invalida. Por favor, verifique los rangos." << std::endl;
            std::cin.clear(); 
            std::cin.ignore(10000, '\n'); 
            return;
        }

        std::cout << "Ingrese la nueva cantidad de produccion: ";
        std::cin >> cantidad;
         if (std::cin.fail() || cantidad < 0) {
            std::cout << "Cantidad invalida." << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            return;
        }

        matrizPlanificacion[producto - 1][semana - 1] = cantidad;
        std::cout << "Plan actualizado correctamente." << std::endl;
    }

    void calcularConsumo(int semana) {
        if (semana < 1 || semana > numSemanasActuales) {
            std::cout << "Semana invalida." << std::endl;
            return;
        }
        int semanaIdx = semana - 1; 

        float consumoTotalMP[NUM_MATERIAS_PRIMAS] = {0}; 

        
        for (int p = 0; p < NUM_PRODUCTOS; ++p) {
            float unidadesProducidas = matrizPlanificacion[p][semanaIdx];
            
            for (int mp = 0; mp < NUM_MATERIAS_PRIMAS; ++mp) {
                
                int requerimiento = vectorRequerimientos[p * NUM_MATERIAS_PRIMAS + mp];
                consumoTotalMP[mp] += unidadesProducidas * requerimiento;
            }
        }
        
        std::cout << "\n--- Reporte de Consumo de Materia Prima para la Semana " << semana << " ---" << std::endl;
        for (int mp = 0; mp < NUM_MATERIAS_PRIMAS; ++mp) {
            std::cout << "Materia Prima Tipo " << (char)('A' + mp) << ": " << consumoTotalMP[mp] << " unidades." << std::endl;
        }
    }

    void calcularCOGS(int semana) {
         if (semana < 1 || semana > numSemanasActuales) {
            std::cout << "Semana invalida." << std::endl;
            return;
        }
        int semanaIdx = semana - 1;

        float cogsSemanal = 0.0;
        float consumoTotalMP[NUM_MATERIAS_PRIMAS] = {0};
        float valorInventarioFinal = 0.0;

        for (int p = 0; p < NUM_PRODUCTOS; ++p) {
            float unidadesProducidas = matrizPlanificacion[p][semanaIdx];
            cogsSemanal += unidadesProducidas * vectorCostosUnitarios[p];
        }

        for (int p = 0; p < NUM_PRODUCTOS; ++p) {
            float unidadesProducidas = matrizPlanificacion[p][semanaIdx];
            for (int mp = 0; mp < NUM_MATERIAS_PRIMAS; ++mp) {
                int requerimiento = vectorRequerimientos[p * NUM_MATERIAS_PRIMAS + mp];
                consumoTotalMP[mp] += unidadesProducidas * requerimiento;
            }
        }

        std::cout << "\n--- Reporte Financiero para la Semana " << semana << " ---" << std::endl;
        std::cout << "\nCalculo de Inventario Final de Materia Prima:" << std::endl;
        for (int mp = 0; mp < NUM_MATERIAS_PRIMAS; ++mp) {
            float inventarioFinal = vectorMateriaPrima[mp] - consumoTotalMP[mp];
            if (inventarioFinal < 0) {
                 std::cout << "No hay Inventario suficiente para Materia Prima " << (char)('A' + mp) << std::endl;
                 inventarioFinal = 0; 
            }
            valorInventarioFinal += inventarioFinal * costoAdquisicionMP[mp];
            std::cout << "Materia Prima " << (char)('A' + mp) << ": " << inventarioFinal << " unidades restantes." << std::endl;
        }

        std::cout << "\n----------------------------------------------------" << std::endl;
        std::cout << "Costo de Bienes Vendidos (COGS) de la semana: $" << cogsSemanal << std::endl;
        std::cout << "Valor del Inventario Final de Materia Prima: $" << valorInventarioFinal << std::endl;
        std::cout << "----------------------------------------------------" << std::endl;
    }
};
void mostrarMenu() {
    std::cout << "\n========= Menu del Sistema de Planificacion =========\n";
    std::cout << "1. Mostrar Plan de Produccion Completo\n";
    std::cout << "2. Agregar una Nueva Semana al Plan\n";
    std::cout << "3. Actualizar Cantidad de Produccion\n";
    std::cout << "4. Ver Consumo de Materia Prima por Semana\n";
    std::cout << "5. Calcular COGS e Inventario Final por Semana\n";
    std::cout << "6. Salir\n";
    std::cout << "=====================================================\n";
    std::cout << "Seleccione una opcion: ";
}

int main() {
    PlanificadorProduccion sistema; 
    int opcion;
    int semana;

    do {
        mostrarMenu();
        std::cin >> opcion;
        
        if (std::cin.fail()) {
            std::cout << "Opcion invalida. Por favor, ingrese un numero." << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            opcion = 0;
        }

        switch (opcion) {
            case 1:
                sistema.mostrarPlan();
                break;
            case 2:
                sistema.agregarSemana();
                break;
            case 3:
                sistema.actualizarProduccion();
                break;
            case 4:
                std::cout << "Ingrese el numero de semana para calcular el consumo: ";
                std::cin >> semana;
                sistema.calcularConsumo(semana);
                break;
            case 5:
                std::cout << "Ingrese el numero de semana para el reporte financiero: ";
                std::cin >> semana;
                sistema.calcularCOGS(semana);
                break;
            case 6:
                
                break;
            default:
                std::cout << "Opcion no valida. Intente de nuevo.\n";
                break;
        }

    } while (opcion != 6);

    return 0;
}
