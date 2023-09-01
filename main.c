#include <stdlib.h>
#include <raylib.h>

#define WIDTH 1024
#define HEIGHT 768

int main() {
    InitWindow(WIDTH, HEIGHT, "GPU Game Of Life");
    SetTargetFPS(60);

    Image image = LoadImage("assets/gol.png");

    RenderTexture2D frames[2];
    frames[0] = LoadRenderTexture(WIDTH, HEIGHT);
    frames[1] = LoadRenderTexture(WIDTH, HEIGHT);

    BeginTextureMode(frames[0]);
        ClearBackground(BLACK);
        for (int i = 0; i < WIDTH; i++){
            for (int j = 0; j < HEIGHT; j++) {
                float color = (float)rand() / (float)RAND_MAX;
                DrawPixel(i, j, ColorFromNormalized((Vector4){color, color, color, 1.0}));
            }
        }
    EndTextureMode();

    while (!WindowShouldClose()) {
        BeginDrawing();
        DrawTexture(frames[0].texture, 0, 0, WHITE);
        EndDrawing();
        
    }

    CloseWindow();
}
