package handson1;

public class Main {

    public static void main(String[] args) {
        
        System.out.println("Iniciando poderosa prueba de Regresión Lineal Múltiple...\n");

        double[][] datosX = {
            {1.0, 41.9, 29.1},
            {1.0, 43.4, 29.3},
            {1.0, 43.9, 29.5},
            {1.0, 44.5, 29.7},
            {1.0, 47.3, 29.9},
            {1.0, 47.5, 30.3},
            {1.0, 47.9, 30.5},
            {1.0, 50.2, 30.7},
            {1.0, 52.8, 30.8},
            {1.0, 53.2, 30.9},
            {1.0, 56.7, 31.5},
            {1.0, 57.0, 31.7},
            {1.0, 63.5, 31.9},
            {1.0, 65.3, 32.0},
            {1.0, 71.1, 32.1},
            {1.0, 77.0, 32.5},
            {1.0, 77.8, 32.9}
        };

        double[][] datosY = {
            {251.3},
            {251.3},
            {248.3},
            {267.5},
            {273.0},
            {276.5},
            {270.3},
            {274.9},
            {285.0},
            {290.0},
            {297.0},
            {302.5},
            {304.5},
            {309.3},
            {321.7},
            {330.7},
            {349.0}
        };

        // pasándole los datos crudos
        System.out.println("Construyendo el modelo...");
        RegresionLineal modelo = new RegresionLineal(datosX, datosY);

        System.out.println("Calculando parámetros óptimos con la Ecuación Normal...");
        modelo.calcularParametros();

        System.out.println("\n--- RESULTADOS ---");
        modelo.imprimirEcuacion();
        
    }
}