/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * You need to define the required function in the part instructed here below.
 * Avoid making any unnecessary changes, particularly the ones you don't understand.
 * The different pieces should be defined using an array - uncomment the following code once you are done creating the array.
 * TIP: Understand thoroughly before getting started with coding.
 * */



//          Name : Ali Asif                     Roll No : 22i-1019



#include <SFML/Graphics.hpp>
using namespace sf;


// Function for how and when which Shapes will fall
//---Piece Starts to Fall When Game Starts---//
void fallingPiece(float &timer, float &delay, bool &drop, int &rc, int &colorNum, bool &lvl1, bool &start)
{
    // n : which shape
    int n;

    if (timer > delay)
    {
        for (int i = 0; i < 4; i++)
        {
            // Copy current coordinates of the Shape to array point_2
            point_2[i][0] = point_1[i][0];
            point_2[i][1] = point_1[i][1];

            // If SpaceBar is Pressed
            if (drop == true && point_1[3][1] < 16 && gameGrid[point_1[3][1] + 1][point_1[3][0]] == 0 && gameGrid[point_1[3][1] + 2][point_1[3][0]] == 0 && gameGrid[point_1[3][1] + 3][point_1[3][0]] == 0 && gameGrid[point_1[3][1] + 4][point_1[3][0]] == 0 && rc % 2 == 0)
                point_1[i][1] += 4; // How much units downward

            // Normal Drop
            else
                point_1[i][1] += 1;
        }

        // Randomly Generating the Color of the Blocks and the Shapes
        if (!anamoly())
        {
            for (int i = 0; i < 4; i++)
                gameGrid[point_2[i][1]][point_2[i][0]] = colorNum;

            colorNum = 1 + (rand() % 7);

            if (lvl1 == true)
                n = rand() % 4;
            else
                n = rand() % 7;

            for (int i = 0; i < 4; i++)
            {
                point_1[i][0] = BLOCKS[n][i] % 2;
                point_1[i][1] = BLOCKS[n][i] / 2;
            }
        }

        // Resetting variables to their initial values
        timer = 0;
        drop = false;
        start = true;
    }
}

/////////////////////////////////////////////
///*****    CODING FUNTIONS HERE    ******///

// Function to move the Shape Rightwards by one unit
void right()
{
    if (point_1[0][0] < N - 1 && point_1[1][0] < N - 1 && point_1[2][0] < N - 1 && point_1[3][0] < N - 1 && gameGrid[point_1[0][1]][point_1[0][0] + 1] == 0 && gameGrid[point_1[1][1]][point_1[1][0] + 1] == 0 && gameGrid[point_1[2][1]][point_1[2][0] + 1] == 0 && gameGrid[point_1[3][1]][point_1[3][0] + 1] == 0) // To stop blocks from changing shape when at the right boundary and overlapping rightwards
        for (int i = 0; i < 4; i++)
            point_1[i][0] += 1;
}

// Function to move the Shape Leftwards by one unit
void left()
{
    if (point_1[0][0] > 0 && point_1[1][0] > 0 && point_1[2][0] > 0 && point_1[3][0] > 0 && gameGrid[point_1[0][1]][point_1[0][0] - 1] == 0 && gameGrid[point_1[1][1]][point_1[1][0] - 1] == 0 && gameGrid[point_1[2][1]][point_1[2][0] - 1] == 0 && gameGrid[point_1[3][1]][point_1[3][0] - 1] == 0) // To stop blocks from changing shape when at the left boundary and overlapping leftwards
        for (int i = 0; i < 4; i++)
            point_1[i][0] -= 1;
}

// Function to Rotate the Shape by 90 Degrees
void rotate_piece()
{
    // Taking point_1[1][0] as x for center of rotation and point_1[1][1] as y
    int arr[4][2], before_rotate[4][2], x_center = point_1[1][0], y_center = point_1[1][1];

    // Setting condition which ensures that Shapes do not Rotate where they should not, specifically at the Boundaries
    if ((point_1[0][0] > 1 || point_1[1][0] > 1 || point_1[2][0] > 1 || point_1[3][0] > 1) && (point_1[0][0] < 8 || point_1[1][0] < 8 || point_1[2][0] < 8 || point_1[3][0] < 8))
    {
        for (int i = 0; i < 4; i++)
        {
            // Center of Rotation
            before_rotate[i][0] = point_1[i][0];
            before_rotate[i][1] = point_1[i][1];
        }

        for (int i = 0; i < 4; i++)
        {
            // Interchanging the x and y-axis and adding the Center of Rotation to both axis
            arr[i][0] = -before_rotate[i][1] + x_center + y_center;
            arr[i][1] = before_rotate[i][0] - x_center + y_center;
        }

        for (int i = 0; i < 4; i++)
        {
            // Finally, giving the point_1 array the new coordinates after it has been rotated
            point_1[i][0] = arr[i][0];
            point_1[i][1] = arr[i][1];
        }
    }
}

// Function to detect 'P' Key presses for Pausing the Game
void pause_game(bool &pause)
{
    if (Keyboard::isKeyPressed(Keyboard::P)) // To Pause the Game
        pause = true;
}

// Function to detect 'Enter' Key presses for Resuming the Game
void resume_game(bool &pause)
{
    if (Keyboard::isKeyPressed(Keyboard::Return)) // To Resume the Game
        pause = false;
}

// Function to detect 'esc' Key presses for Exiting the Game
void escape_game(bool &escape)
{
    if (Keyboard::isKeyPressed(Keyboard::Escape)) // To Close the Game
        escape = true;
}

// Function to detect 'H' Key presses for opening HELP MENU when Game is Paused or at Start Menu
void help_game(bool &helpp)
{
    if (Keyboard::isKeyPressed(Keyboard::H)) // To Open Help Menu
        helpp = true;
}

// To Drop Shape if SpaceBar is Pressed
void drop_or_normal()
{
    if (Keyboard::isKeyPressed(Keyboard::Space)) // To drop piece
    {
        for (int i = 0; i < 4; i++)
        {
            point_2[i][0] = point_1[i][0];
            point_2[i][1] = point_1[i][1];
            point_1[i][1] -= 1; // How much units downward
        }
    }
}

// Function to detect 'A' Key presses for starting Level 1
void level1(bool &lvl1)
{
    if (Keyboard::isKeyPressed(Keyboard::A)) // To Open Help Menu
        lvl1 = true;
}

// Function to detect 'R' Key presses for Restarting the Game
void restart_game(int &score, bool &reset)
{
    if (Keyboard::isKeyPressed(Keyboard::R)) // To Restart Game
    {
        // To Clear the whole of the Playing Grid 
        for (int i = 0; i<M;i++)
        {
            for (int j = 0; j<N;j++)
                gameGrid[i][j] = 0;
        }

        reset = true;
    }
}

///*** ENDING MY FUNCTIONS HERE ***///
//////////////////////////////////////