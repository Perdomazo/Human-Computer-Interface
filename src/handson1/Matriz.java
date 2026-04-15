package handson1;

public class Matriz {
	private double[][] datos;
	private int filas;
	private int columnas;

	public Matriz( int filas, int columnas) {
		this.filas = filas;
		this.columnas = columnas;
		this.datos = new double [filas][columnas];
	}

	public Matriz(double[][] datos) {
		this.datos = datos;
		this.filas = datos.length;
		this.columnas = datos[0].length;
	}

	public double[][] getDatos() {
		return datos;
	}

	public int getFilas() {
		return filas;
	}

	public int getColumnas() {
		return columnas;
	}

	public void imprimir() {
		for( int i = 0; i < filas; i++) {
			for( int j = 0; j < columnas; j++) {
				System.out.print(datos[i][j]+" ");
			}
			System.out.println(" ");
		}
	}

	public Matriz transponer() {

		double [][] nuevaMatriz = new double [columnas][filas];

		for( int i = 0; i < filas; i++) {
			for( int j = 0; j < columnas; j++) {
				nuevaMatriz[j][i] = datos[i][j];
			}
		}
		return new Matriz(nuevaMatriz);
	}

	public Matriz multiplicar(Matriz otra) {

		double [][] nuevaMatriz = new double [this.filas][otra.getColumnas()];

		if (this.columnas == otra.getFilas() ) {


			for( int i = 0; i < this.filas; i++) {
				for( int j = 0; j < otra.getColumnas(); j++) {

					double suma = 0;

					for( int k = 0; k < this.columnas; k++ ) {
						suma += this.datos[i][k] * otra.getDatos()[k][j];
					}

					nuevaMatriz[i][j]=suma;

				}
			}

		}

		else {
			return null;
		}

		return new Matriz(nuevaMatriz);
	}

	public Matriz invertir() {
		if (this.filas != this.columnas) {
			return null;
		}

		int n = this.filas;
		double[][] copia = new double [n][n];
		double[][] inversa = new double [n][n];

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				copia[i][j] = this.datos[i][j]; 

				if (i == j) {
					inversa[i][j] = 1.0;
				} else {
					inversa[i][j] = 0.0;
				}
			}
		}

		for (int i = 0; i < n; i++) {
			double pivote = copia[i][i]; //sabiendo que el pivote != 0

			for(int k = 0; k < n; k++) {
				copia[i][k]= copia[i][k]/pivote;
				inversa[i][k] = inversa[i][k]/pivote;
			}

			for (int j=0; j < n; j++) {
				if (i != j) {
					double factor = copia[j][i];

					for (int k = 0; k < n; k++) {
						copia[j][k] = copia[j][k] -factor *copia [i][k];
						inversa[j][k] = inversa[j][k] - factor * inversa[i][k];
					}
				}
			}
		}



		return new Matriz(inversa);
	}
}
