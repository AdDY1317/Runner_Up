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
    //window Dimension
    int windowDimensions [2];
    windowDimensions[0] = 512;
    windowDimensions[1] = 380;
    //initialize Window
    InitWindow(windowDimensions[0],windowDimensions[1],"RunnerUp");

    //acceleartion due to Gravity(pixels/s)/s
    const int gravity{1'000};

    //Nebula Variable
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

    //AnimData for Nebula
    AnimData nebData{{0.0, 0.0, nebula.width/8, nebula.height/8},//rectangle rec
    {windowDimensions[0],windowDimensions[1] -nebula.height/8},               // Vector 2
    0,                                                         // int frame
    1.0/12.0,                                                  //float updateTime
    0};                                                        //float runnin time

    //AnimData for 2nd Nebula
    AnimData neb2Data{{0.0, 0.0, nebula.width/8, nebula.height/8},
    {windowDimensions[0] +300, windowDimensions[1] - nebula.height/8},
    0,
    1.0/16.0,
    0.0
    };

    //nebula X Velocity (Pixels/seconds)
    int nebVel{-200};

    //scarfy Vaiables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimData scarfyData;
    scarfyData.rec.width = scarfy.width/6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    scarfyData.pos.x = windowDimensions[0]/2 - scarfyData.rec.width/2;
    scarfyData.pos.y = windowDimensions[1] - scarfyData.rec.height;
    scarfyData.frame = 0;
    scarfyData.updateTime = 1.0/12.0;
    scarfyData.runningTime = 0.0;

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

        if(scarfyData.pos.y >= windowDimensions[1] - scarfyData.rec.height)
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
        nebData.pos.x += nebVel * dT;

        // update 2ND Nebula position
        neb2Data.pos.x += nebVel * dT;


        // update scarfy position
        scarfyData.pos.y += velocity * dT;

        //update scarfy's animation frame
        if(!IsinAir)
        {
            //update running time
            scarfyData.runningTime += dT;
            if (scarfyData.runningTime>= scarfyData.updateTime)
            {
                scarfyData.runningTime = 0.0;
                // update Animation frame
                scarfyData.rec.x= scarfyData.frame * scarfyData.rec.width;
                scarfyData.frame++;
                if (scarfyData.frame > 5)
                {
                    scarfyData.frame = 0;
                }
            }
        }
        //update nebula animation frame
        nebData.runningTime +=dT;
        if(nebData.runningTime >= nebData.updateTime)
        {
            nebData.runningTime = 0.0;
            nebData.rec.x = nebData.frame * nebData.rec.width;
            nebData.frame++;
            if(nebData.frame > 7)
            {
                nebData.frame = 0;
            }
        }
        //update 2ND nebula animation frame
        neb2Data.runningTime +=dT;
        if(neb2Data.runningTime >= neb2Data.updateTime)
        {
            neb2Data.runningTime = 0.0;
            neb2Data.rec.x = neb2Data.frame * neb2Data.rec.width;
            nebData.frame++;
            if(neb2Data.frame > 7)
            {
                neb2Data.frame = 0;
            }
        }


        //Draw Nebula
        DrawTextureRec(nebula, nebData.rec, nebData.pos, WHITE);
        //Draw 2nd nebula
         DrawTextureRec(nebula, neb2Data.rec, neb2Data.pos, RED);
        //Draw Scarfy
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

        //Game Logic Ends
        EndDrawing();
    }
    UnloadTexture(scarfy); 
    UnloadTexture(nebula);
    CloseWindow();
}