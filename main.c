#include <stdlib.h>
#include <raylib.h>

#define WIDTH 1600
#define HEIGHT 900

int main() {
    InitWindow(WIDTH, HEIGHT, "GPU Game Of Life");
    SetTargetFPS(30);

    RenderTexture2D frames[2];
    frames[0] = LoadRenderTexture(WIDTH, HEIGHT);
    SetTextureWrap(frames[0].texture, TEXTURE_WRAP_REPEAT);
    SetTextureFilter(frames[0].texture, TEXTURE_FILTER_POINT);
    frames[1] = LoadRenderTexture(WIDTH, HEIGHT);
    SetTextureWrap(frames[1].texture, TEXTURE_WRAP_REPEAT);
    SetTextureFilter(frames[1].texture, TEXTURE_FILTER_POINT);
    int current = 0;

    Shader gol_shader = LoadShader(NULL, "gol.glsl");
    Vector2 resolution = {WIDTH, HEIGHT};
    int resolution_loc = GetShaderLocation(gol_shader, "resolution");
    SetShaderValue(gol_shader, resolution_loc, &resolution, SHADER_UNIFORM_VEC2);

    BeginTextureMode(frames[0]);
        ClearBackground(BLACK);
        for (int i = 0; i < WIDTH; i++){
            for (int j = 0; j < HEIGHT; j++) {
                float color = (float)(rand() % 2);
                DrawPixel(i, j, ColorFromNormalized((Vector4){color, color, color, 1.0}));
            }
        }
    EndTextureMode();

    while (!WindowShouldClose()) {
        BeginTextureMode(frames[1 - current]);
        ClearBackground(BLACK);
        BeginShaderMode(gol_shader);
        DrawTexture(frames[current].texture, 0, 0, WHITE);
        EndShaderMode();
        EndTextureMode();

        current = 1 - current;

        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(frames[current].texture, 0, 0, WHITE);
        EndDrawing();


    }

    CloseWindow();
}
