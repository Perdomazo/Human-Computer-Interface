# Transformaciones Matemáticas 2D y 3D con Raylib
## Adrián Jesús Ventura Perdomo Lobo y Sebastian Castillo Porras
Este proyecto es una aplicación gráfica desarrollada en C++ utilizando [Raylib](https://www.raylib.com/). Su objetivo es demostrar la implementación práctica de modelos matemáticos y cinemáticos para simular transformaciones espaciales en tiempo real, calculadas mediante la integración de Euler (`Delta Time`).

La aplicación cuenta con una máquina de estados que permite visualizar las transformaciones tanto en un plano bidimensional (2D) como en un entorno tridimensional (3D) con una cámara orbital.

## 🚀 Transformaciones Implementadas

El proyecto incluye la simulación paramétrica y visualización de rastros/trayectorias para los siguientes movimientos:

* **Traslación y Rebote:** Movimiento rectilíneo uniforme con inversión de vector velocidad al detectar colisiones con los límites espaciales.
* **Rotación:** * **2D:** Calculada manualmente multiplicando los vértices por una matriz de rotación paramétrica.
    * **3D:** Rotación intrínseca sobre el eje Y utilizando el estado de matrices del pipeline gráfico (`rlgl.h`).
* **Movimiento Senoidal:** Oscilación armónica simple calculada mediante funciones trigonométricas en función del tiempo.
* **Órbita (Movimiento Circular):** Trayectoria paramétrica utilizando componentes de seno y coseno sincronizadas.
* **Trayectoria Parabólica:** Simulación balística aplicando una aceleración constante (gravedad) sobre el eje vertical interactuando con una velocidad horizontal constante.

## 🎮 Controles

* **[ESPACIO]** - Alternar instantáneamente entre la vista 2D y la vista 3D.

## 🛠️ Requisitos y Compilación (Linux)

Para compilar este proyecto, necesitas tener instalado el compilador de C++ y las dependencias de desarrollo de Raylib. 

Poniendo de ejemplo el sistema operativo trabajado:

```bash
sudo dnf install gcc-c++ raylib-devel
