/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   Example originally created with raylib 1.0, last time updated with raylib 1.0

*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2013-2022 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

//I worked with Lance Co for this exercise

#include "raylib.h"
#include <iostream>
#include <vector>


Vector2 LinearInterpolation(Vector2 P0, Vector2 P1, float T)
{
    Vector2 returnedPoint = { 0,0 };

    returnedPoint.x = P0.x + (T * (P1.x - P0.x));
    returnedPoint.y = P0.y + (T * (P1.y - P0.y));

    return returnedPoint;
}
Vector2 BezierPoint(Vector2 P0, Vector2 P1, Vector2 P2, float T)
{
    Vector2 Point1, Point2, retPoint;

    Point1 = LinearInterpolation(P0, P1, T);
    Point2 = LinearInterpolation(P1, P2, T);
    retPoint = LinearInterpolation(Point1, Point2, T);

    return retPoint;
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1366;
    const int screenHeight = 768;

    Vector2 P0, P1, P2, redPoint, greenPoint, bluePoint;
    float T;
    int numOfSteps, numOfControlPoints, numOfCurves;
    std::string input;
    std::vector<Vector2> controlPoints, bezierPoints;


    P0 = { 0,0 };
    P1 = { 0,0 };
    P2 = { 0,0 };

    redPoint = { 0,0 };
    greenPoint = { 0,0 };
    bluePoint = { 0,0 };


    InitWindow(screenWidth, screenHeight, "Homework 2 - Arceo, Co");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        std::cin >> numOfSteps;
        std::cin >> numOfControlPoints;
        for (int i = 0; i < numOfControlPoints; i++)
        {
            std::cin >> P0.x;
            std::cin >> P0.y;
            controlPoints.push_back({P0.x, P0.y});
        }
        //std::cin >> P0.x;
        //std::cin >> P0.y;
        //std::cin >> P1.x;
        //std::cin >> P1.y;
        //std::cin >> P2.x;
        //std::cin >> P2.y;

        numOfCurves = numOfControlPoints / 2;
        std::cout << numOfCurves << "\n";

        //j is the number of curves present, computed above by floor dividing the number of control points by 2
        //since the controlPoints vector indexes from 0, indices must be adjusted by subtracting 1
        
        for (int j = 1; j <= numOfCurves; j++)
        {
            std::cout << "q" << "\n";
            P0 = controlPoints[(2*j) - 2];
            std::cout << "q" << "\n";
            P1 = controlPoints[2*j-1];
            std::cout << "q" << "\n";
            P2 = controlPoints[(2*j)];
            std::cout << "q" << "\n";
            for (int i = 1; i <= numOfSteps; i++)
            {
                bezierPoints.push_back(BezierPoint(P0, P1, P2, (float)i / (float)numOfSteps));
                //bezierPoints.push_back(BezierPoint(controlPoints[0], controlPoints[1], controlPoints[2], (float)i / (float)numOfSteps));
            }
        }

        //redPoint = BezierPoint(P0, P1, P2, 0.25);
        //greenPoint = BezierPoint(P0, P1, P2, 0.5);
        //bluePoint = BezierPoint(P0, P1, P2, 0.75);
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        //DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        DrawLineV(P0, P1, BLACK);
        DrawLineV(P1, P2, BLACK);
        DrawCircleV(P0, 10, BLACK);
        DrawCircleV(P1, 10, YELLOW);
        DrawCircleV(P2, 10, PINK);

        for (Vector2 Point : bezierPoints)
        {
            DrawCircleV(Point, 10, RED);
        }

        //DrawLineV(P0, redPoint, PURPLE);
        //DrawLineV(redPoint, greenPoint, PURPLE);
        //DrawLineV(greenPoint, bluePoint, PURPLE);
        //DrawLineV(bluePoint, P2, PURPLE);

        

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
