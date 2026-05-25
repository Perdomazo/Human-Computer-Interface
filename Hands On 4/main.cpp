#include "raylib.h"
#include "rlgl.h"  // <-- lo necesitamos para rlPushMatrix() y rlRotatef()
#include <cmath>

// --- MATEMÁTICAS 2D ---
Vector2 RotarConMatriz(Vector2 p, float theta) {
    Vector2 r;
    r.x = p.x * cosf(theta) - p.y * sinf(theta);
    r.y = p.x * sinf(theta) + p.y * cosf(theta);
    return r;
}

void DibujarCuadradoRotado(Vector2 centro, float lado, float theta, Color color) {
    Vector2 v1 = {-lado/2, -lado/2}; Vector2 v2 = { lado/2, -lado/2};
    Vector2 v3 = { lado/2,  lado/2}; Vector2 v4 = {-lado/2,  lado/2};

    v1 = RotarConMatriz(v1, theta); v2 = RotarConMatriz(v2, theta);
    v3 = RotarConMatriz(v3, theta); v4 = RotarConMatriz(v4, theta);

    v1.x += centro.x; v1.y += centro.y; v2.x += centro.x; v2.y += centro.y;
    v3.x += centro.x; v3.y += centro.y; v4.x += centro.x; v4.y += centro.y;

    DrawLineEx(v1, v2, 4, color); DrawLineEx(v2, v3, 4, color);
    DrawLineEx(v3, v4, 4, color); DrawLineEx(v4, v1, 4, color);
}

// funcion para dibujar los rieles negros, por donde pasa cada cuadrito
void DibujarRastroParabola2D() {
    Vector2 pos = { 500.0f, 500.0f };
    float vy = -400.0f; 
    float vx = 180.0f;
    float g = 600.0f;   
    float dt = 0.016f;  
    
    Vector2 prev = pos;
    while (pos.y <= 600.0f) {
        pos.x += vx * dt;
        vy += g * dt;
        pos.y += vy * dt;
        DrawLineEx(prev, pos, 1.5f, BLACK); 
        prev = pos;
    }
}

void DibujarRastroParabola3D() {
    Vector3 pos = { 4.0f, 0.5f, 3.0f };
    float vy = 10.0f;
    float vz = -4.0f;
    float g = -25.0f;
    float dt = 0.016f;
    
    Vector3 prev = pos;
    while (pos.z >= -4.0f) {
        pos.z += vz * dt;
        vy += g * dt;
        pos.y += vy * dt;
        
        if (pos.y < 0.5f) { 
            pos.y = 0.5f;
            vy = 10.0f; 
        }
        DrawLine3D(prev, pos, BLACK);
        prev = pos;
    }
}

void DibujarRastroOrbita3D() {
    int segmentos = 40;
    float radio = 4.0f;
    for (int i = 0; i < segmentos; i++) {
        float a1 = (float)i * 2.0f * PI / segmentos;
        float a2 = (float)(i + 1) * 2.0f * PI / segmentos;
        Vector3 p1 = { radio * cosf(a1), 0.5f, radio * sinf(a1) };
        Vector3 p2 = { radio * cosf(a2), 0.5f, radio * sinf(a2) };
        DrawLine3D(p1, p2, BLACK);
    }
}

// Función auxiliar para la UI
void DibujarLeyendaMovimientos() {
    int posX = 640; int posY = 20;
    DrawRectangle(posX - 10, posY - 5, 260, 165, Fade(LIGHTGRAY, 0.3f));
    DrawRectangleLines(posX - 10, posY - 5, 260, 165, GRAY);

    DrawText("Lista de Transformaciones:", posX, posY, 16, BLACK);
    DrawText("[ ] Traslacion y Rebote", posX, posY + 25, 16, RED);
    DrawText("[ ] Rotacion (Matriz / rlgl)", posX, posY + 50, 16, BLUE);
    DrawText("[ ] Movimiento Senoidal", posX, posY + 75, 16, GREEN);
    DrawText("[ ] Orbita Circular", posX, posY + 100, 16, ORANGE);
    DrawText("[ ] Trayectoria Parabolica", posX, posY + 125, 16, PURPLE);
}

int main() {
    const int screenWidth = 900;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Proyecto Transformaciones: Correccion 3D");
    SetTargetFPS(60);

    bool mostrar3D = false; 
    float t = 0.0f;

    // --- VARIABLES 2D ---
    Vector2 posTraslacion2D = { 100, 100 }; float velX2D = 250.0f; 
    float anguloRotacion2D = 0.0f;
    Vector2 baseSenoidal2D = { 450, 250 }; 
    Vector2 posTrayectoria2D = { 500, 500 }; float velTrayY2D = -400.0f; 
    
    // --- VARIABLES 3D ---
    Camera3D camera = { 0 };
    camera.target = { 0.0f, 0.0f, 0.0f };
    camera.up = { 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    float radioCamara = 14.0f; float velCamara = 0.4f; 

    // Variables de cada movimiento 3D
    Vector3 posTraslacion3D = { 0.0f, 0.5f, -3.0f }; float velX3D = 5.0f;
    
    Vector3 posRotacion3D = { -2.0f, 0.5f, 0.0f }; 
    float anguloRotacion3D = 0.0f; 
    
    Vector3 baseSenoidal3D = { -4.0f, 1.0f, 0.0f };
    Vector3 posTrayectoria3D = { 4.0f, 0.5f, 3.0f }; float velTrayY3D = 10.0f; float velTrayZ3D = -4.0f; 

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        t += dt;

        if (IsKeyPressed(KEY_SPACE)) mostrar3D = !mostrar3D;

        if (!mostrar3D) {
            // ACTUALIZACIÓN 2D
            posTraslacion2D.x += velX2D * dt;
            if (posTraslacion2D.x > screenWidth - 15 || posTraslacion2D.x < 15) velX2D = -velX2D;

            anguloRotacion2D += 2.0f * dt;
            float posYSenoidal2D = baseSenoidal2D.y + 60.0f * sinf(3.0f * t);
            float xOrbita2D = 250 + 80.0f * cosf(2.0f * t);
            float yOrbita2D = 430 + 80.0f * sinf(2.0f * t);

            posTrayectoria2D.x += 180.0f * dt;
            velTrayY2D += 600.0f * dt; 
            posTrayectoria2D.y += velTrayY2D * dt;
            if (posTrayectoria2D.y > screenHeight) {
                posTrayectoria2D = { 500, 500 }; velTrayY2D = -400.0f;
            }

            // DIBUJADO 2D
            BeginDrawing();
            ClearBackground(RAYWHITE);
            
            // Rieles 2D
            DrawLineEx({15, 100}, {screenWidth - 15, 100}, 1.5f, BLACK); 
            DrawCircleLines(450, 100, 35.35f, BLACK);                    
            DrawLineEx({450, 250 - 60}, {450, 250 + 60}, 1.5f, BLACK);   
            DrawCircleLines(250, 430, 80.0f, BLACK);                     
            DibujarRastroParabola2D();                                   

            // Objetos 2D
            DrawCircleV(posTraslacion2D, 15, RED);
            DibujarCuadradoRotado({450, 100}, 50, anguloRotacion2D, BLUE);
            DrawCircle(baseSenoidal2D.x, posYSenoidal2D, 15, GREEN);
            DrawCircle(xOrbita2D, yOrbita2D, 15, ORANGE);
            DrawCircleV(posTrayectoria2D, 15, PURPLE);

            DrawText("Modo 2D - Presiona [ESPACIO] para ir a 3D", 20, 20, 18, DARKGRAY);
            DibujarLeyendaMovimientos();
            EndDrawing();

        } else {
            // ACTUALIZACIÓN 3D
            camera.position.x = radioCamara * cosf(t * velCamara);
            camera.position.z = radioCamara * sinf(t * velCamara);
            camera.position.y = 7.0f; 

            posTraslacion3D.x += velX3D * dt;
            if (posTraslacion3D.x > 4.0f || posTraslacion3D.x < -4.0f) velX3D = -velX3D;

            // grados no radianes
            anguloRotacion3D += 90.0f * dt; // Gira 90 grados por segundo

            float posYSenoidal3D = baseSenoidal3D.y + 2.0f * sinf(3.0f * t);

            float xOrbita3D = 0.0f + 4.0f * cosf(2.0f * t);
            float zOrbita3D = 0.0f + 4.0f * sinf(2.0f * t);

            posTrayectoria3D.z += velTrayZ3D * dt;
            velTrayY3D += -25.0f * dt; 
            posTrayectoria3D.y += velTrayY3D * dt;
            if (posTrayectoria3D.y < 0.5f) { 
                posTrayectoria3D.y = 0.5f; velTrayY3D = 10.0f; 
                if(posTrayectoria3D.z < -4.0f) posTrayectoria3D.z = 3.0f; 
            }

            // DIBUJADO 3D
            BeginDrawing();
            ClearBackground(RAYWHITE);

            BeginMode3D(camera);
                DrawGrid(14, 1.0f);

                // Rieles 3D
                DrawLine3D({-4.0f, 0.5f, -3.0f}, {4.0f, 0.5f, -3.0f}, BLACK); // Traslacion
                DrawLine3D({-4.0f, -1.0f, 0.0f}, {-4.0f, 3.0f, 0.0f}, BLACK); // Senoidal
                DibujarRastroOrbita3D();                                      // Orbita
                DibujarRastroParabola3D();                                    // Parabola 
                
              

                // Objetos 3D
                DrawCube(posTraslacion3D, 1.0f, 1.0f, 1.0f, RED);       
                DrawCube({baseSenoidal3D.x, posYSenoidal3D, baseSenoidal3D.z}, 1.0f, 1.0f, 1.0f, GREEN); 
                DrawCube({xOrbita3D, 0.5f, zOrbita3D}, 0.8f, 0.8f, 0.8f, ORANGE); 
                DrawSphere(posTrayectoria3D, 0.5f, PURPLE);             

                // CORRECCIÓN ROTACIÓN 3D AZUL: Usando rlgl como indicó el profesor
                rlPushMatrix();
                    rlTranslatef(posRotacion3D.x, posRotacion3D.y, posRotacion3D.z); // 1. Lo llevamos a su posición
                    rlRotatef(anguloRotacion3D, 0.0f, 1.0f, 0.0f);                   // 2. Lo rotamos sobre Y
                    
                    // Al dibujarlo lo hacemos en el "origen" porque rlTranslatef ya movió el universo temporalmente
                    DrawCube({0.0f, 0.0f, 0.0f}, 1.0f, 1.0f, 1.0f, BLUE);             
                    DrawCubeWires({0.0f, 0.0f, 0.0f}, 1.0f, 1.0f, 1.0f, DARKBLUE); // Cables para notar el giro espacial
                rlPopMatrix();

            EndMode3D();

            DrawText("Modo 3D - Presiona [ESPACIO] para regresar a 2D", 20, 20, 18, DARKGRAY);
            DibujarLeyendaMovimientos();
            EndDrawing();
        }
    }

    CloseWindow();
    return 0;
}
