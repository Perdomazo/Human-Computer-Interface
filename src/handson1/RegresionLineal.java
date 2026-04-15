package handson1;

public class RegresionLineal {
    
    private Matriz X;
    private Matriz Y;
    private Matriz beta; 

    // El constructor recibe los datos crudos y los convierte en objetos Matriz
    public RegresionLineal(double[][] datosX, double[][] datosY) {
        this.X = new Matriz(datosX);
        this.Y = new Matriz(datosY);
    }

   
    public void calcularParametros() {
       
        Matriz xTranspuesta = X.transponer();

        
        Matriz xTx = xTranspuesta.multiplicar(X);

        
        Matriz inversa = xTx.invertir();

        
        Matriz xTy = xTranspuesta.multiplicar(Y);

        
        this.beta = inversa.multiplicar(xTy);
    }


    public void imprimirEcuacion() {
        System.out.println("Los parámetros óptimos (Beta) son:");
        if (beta != null) {
            beta.imprimir();
        } else {
            System.out.println("Error: Beta no ha sido calculado o hubo un error en la matriz.");
        }
    }
}