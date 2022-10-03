#include "raylib.h"

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};
int main()
{
    // window Dimension using Array
    int windowDimensions[2];
    windowDimensions[0] = 512;
    windowDimensions[1] = 380;

    // initialize Window
    InitWindow(windowDimensions[0], windowDimensions[1], "RunnerUp");

    // acceleartion due to Gravity(pixels/s)/s
    const int gravity{1'000};

    //-------------------------------------------------------------------------------------------------------------
    // Nebula Variable
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

    const int sizeofNebulae{10};
    // Array and Loop for Anim Data
    AnimData nebulae[sizeofNebulae]{};

    for (int i = 0; i < sizeofNebulae; i++)
    {
        nebulae[i].rec.x = 0.0;
        nebulae[i].rec.y = 0.0;
        nebulae[i].rec.width = nebula.width / 8;
        nebulae[i].rec.height = nebula.height / 8;
        nebulae[i].pos.y = windowDimensions[1] - nebula.height / 8;
        nebulae[i].frame = 0;
        nebulae[i].runningTime = 0.0;
        nebulae[i].updateTime = 0.0;
        nebulae[i].pos.x = windowDimensions[0] + i * 300;
    }

    // nebula X Velocity (Pixels/seconds)
    int nebVel{-200};

    //------------------------------------------------------------------------------------------------------------
    // scarfy Vaiables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimData scarfyData;
    scarfyData.rec.width = scarfy.width / 6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    scarfyData.pos.x = windowDimensions[0] / 2 - scarfyData.rec.width / 2;
    scarfyData.pos.y = windowDimensions[1] - scarfyData.rec.height;
    scarfyData.frame = 0;
    scarfyData.updateTime = 1.0 / 12.0;
    scarfyData.runningTime = 0.0;

    // Is the Rectangle in Air
    bool IsinAir{};
    // JUMP VELOCITY pixels/sec
    const int jumpVel{-600};

    int velocity{0};

    SetTargetFPS(60);
    //! WindowShouldClose()-----NEGATION
    while (!WindowShouldClose())
    {
        // delta time (time since last frame)
        const float dT{GetFrameTime()};

        // Game Logic Begins
        BeginDrawing();
        ClearBackground(WHITE);

        if (scarfyData.pos.y >= windowDimensions[1] - scarfyData.rec.height)
        {
            velocity = 0;
            IsinAir = false;
        }
        else
        {
            velocity += gravity * dT;
            IsinAir = true;
        }

        // Jump Check
        if (IsKeyPressed(KEY_SPACE) && !IsinAir)
        {
            velocity += jumpVel;
        }

        for(int i=0; i < sizeofNebulae; i++ )
        {
            // update the position of each Nebula
           nebulae[i].pos.x += nebVel * dT; 
        }

        // update scarfy position
        scarfyData.pos.y += velocity * dT;

        // update scarfy's animation frame
        if (!IsinAir)
        {
            // update running time
            scarfyData.runningTime += dT;
            if (scarfyData.runningTime >= scarfyData.updateTime)
            {
                scarfyData.runningTime = 0.0;
                // update Animation frame
                scarfyData.rec.x = scarfyData.frame * scarfyData.rec.width;
                scarfyData.frame++;
                if (scarfyData.frame > 5)
                {
                    scarfyData.frame = 0;
                }
            }
        }

        for (int i = 0; i < sizeofNebulae; i++)
        {
            // update nebula animation frame
            nebulae[i].runningTime += dT;
            if (nebulae[i].runningTime >= nebulae[i].updateTime)
            {
                nebulae[i].runningTime = 0.0;
                nebulae[i].rec.x = nebulae[i].frame * nebulae[i].rec.width;
                nebulae[i].frame++;
                if (nebulae[i].frame > 7)
                {
                    nebulae[i].frame = 0;
                }
            }
        }
         
        for(int i = 0; i < sizeofNebulae; i++)
        {
            DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
        }

        // Draw Scarfy
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

        // Game Logic Ends
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}