#include "raylib.h"

int main()
{   
    //window Dimension
    const int windowHeight = 512;
    const int windowWidth = 380;

    //initialize Window
    InitWindow(windowWidth,windowHeight,"RunnerUp");

    //acceleartion due to Gravity(pixels/s)/s
    const int gravity{1'000};

    //Nebula Variable
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    Rectangle nebRec{0.0,0.0, nebula.width/8, nebula.height/8};
    Vector2 nebPos{windowWidth,windowHeight - nebRec.height};

    //Nebula Animation Variables
    int nebFrame{};
    const float nebUpdateTime{1.0/12.0};
    float nebRunningTime{};

    //nebula X Velocity (Pixels/seconds)
    int nebVel{-200};

    //scarfy Vaiables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width/6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    Vector2 scarfyPos;
    scarfyPos.x = windowWidth/2 - scarfyRec.width/2;
    scarfyPos.y = windowHeight - scarfyRec.height;

    //animation frame
    int frame{};
    //amount of time before we update the animation frame
    const float upadateTimer{1.0/12.0};
    float runningTime{};

    //Is the Rectangle in Air
    bool IsinAir {};
    //JUMP VELOCITY pixels/sec
    const int jumpVel{-600};

   
    int velocity {0};

    SetTargetFPS(60);
    //!WindowShouldClose()-----NEGATION 
    while(!WindowShouldClose())
    {
        //delta time (time since last frame)
        const float dT{GetFrameTime()};

        //Game Logic Begins
        BeginDrawing();
        ClearBackground(WHITE);

        if(scarfyPos.y >= windowHeight - scarfyRec.height)
        {
          velocity = 0;
          IsinAir = false;
        }
        else
        {
           velocity +=gravity * dT; 
           IsinAir = true;
        }

        //Jump Check
        if(IsKeyPressed(KEY_SPACE)&& !IsinAir)
        {
            velocity += jumpVel;   
         
        }
        // update Nebula position
        nebPos.x += nebVel * dT;

        // update scarfy position
        scarfyPos.y += velocity * dT;

        //update scarfy's animation frame
        if(!IsinAir)
        {
            //update running time
            runningTime += dT;
            if (runningTime>= upadateTimer)
            {
                runningTime = 0.0;
                // update Animation frame
                scarfyRec.x= frame * scarfyRec.width;
                frame++;
                if (frame > 5)
                {
                    frame = 0;
                }
            }
        }
        //update nebula animation frame
        nebRunningTime +=dT;
        if(nebRunningTime >= nebUpdateTime)
        {
            nebRunningTime = 0.0;
            nebRec.x = nebFrame * nebRec.width;
            nebFrame++;
            if(nebFrame > 7)
            {
                nebFrame = 0;
            }
        }

        //Draw Nebula
        DrawTextureRec(nebula, nebRec, nebPos, WHITE);
        //Draw Scarfy
        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

        //Game Logic Ends
        EndDrawing();
    }
    UnloadTexture(scarfy); 
    UnloadTexture(nebula);
    CloseWindow();
}