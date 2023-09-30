/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * You don't need to change anything in the driver code/main function except the part(s) where instructed.
 * You are expected to define your functionalities in the "functionality.h" header and call them here in the instructed part(s).
 * The game is started with a small box, you need to create other possible in "pieces.h" file in form of array.
    E.g., Syntax for 2 pieces, each having four coordinates -> int Pieces[2][4];
 * Load the images into the textures objects from img directory.
 * Don't make any changes to the "utils.h" header file except for changing the coordinate of screen or global variables of the game.
 * SUGGESTION: If you want to make changes in "utils.h", do it once you complete rest of the functionalities.
 * TIP: You can study SFML for drawing scenes, sprites and window.
 * */



//          Name : Ali Asif                     Roll No : 22i-1019



#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include "utils.h"
#include "pieces.h"
#include "functionality.h"

using namespace std;
using namespace sf;

int main()
{
    //////////////////////////////////////////////////////////
    //*********    Declaration Starts from Here    *********//

    // Defining Window, Texture and Time
    srand(time(0));
    RenderWindow window(VideoMode(320, 480), title);
    Texture obj1, obj2, obj3;

    // Loading "frames.png", "tiles.png" and "background.png" for Texture Objects
    obj1.loadFromFile("tiles.png");
    obj2.loadFromFile("background.png");
    obj3.loadFromFile("frame.png");

    // Defining Sprites
    Sprite sprite(obj1), background(obj2), frame(obj3);

    // Declaring Variables          rc : rotation counter,  fin : finish,   lvl1 : level 1
    int delta_x = 0, count = 0, score = 0, rc = 0, colorNum = 0;
    float timer = 0, delay;
    bool rotate = false, pause = false, fin = false, escape = false, helpp = false, start = false, drop = false, lvl1 = false, reset = false;

    // Defining and loading Fonts to be used for Text
    Font font;
    font.loadFromFile("Roboto-Bold.ttf");

    // Defining and loading the Background Music for the game
    Music music;
    music.openFromFile("music.ogg");
    music.play();

    // Text : GAME OVER
    Text gameOver;
    gameOver.setFont(font);
    gameOver.setCharacterSize(40);
    gameOver.setFillColor(Color::Red);
    gameOver.setStyle(Text::Bold);
    gameOver.setString("GAME OVER");
    gameOver.setPosition(40.f, window.getSize().y / 3);

    // Text : GAME PAUSED and START MENU
    Text paused;
    paused.setFont(font);
    paused.setCharacterSize(35);
    paused.setFillColor(Color::Red);
    paused.setStyle(Text::Bold);
    paused.setString("Game : TETRIS");
    paused.setPosition(35.f, window.getSize().y / 7);

    // Text : Press 'Enter' to Continue to Level 2
    Text resume;
    resume.setFont(font);
    resume.setCharacterSize(22);
    resume.setFillColor(Color::White);
    resume.setString("-  Press 'Enter' to Continue");
    resume.setPosition(33.f, window.getSize().y / 2.7);

    // Text : Press 'esc' to Exit
    Text exit;
    exit.setFont(font);
    exit.setCharacterSize(22);
    exit.setFillColor(Color::White);
    exit.setString("-  Press 'esc' to Exit");
    exit.setPosition(33.f, window.getSize().y / 2.2);

    // Text : RULES
    Text ruless;
    ruless.setFont(font);
    ruless.setCharacterSize(35);
    ruless.setFillColor(Color::Red);
    ruless.setStyle(Text::Bold);
    ruless.setString("RULES");
    ruless.setPosition(100.f, window.getSize().y / 9);

    // Text to be displayed on Help Screen
    Text rules;
    rules.setFont(font);
    rules.setCharacterSize(14);
    rules.setFillColor(Color::White);
    rules.setString("- The blocks can be moved only in specific\n   ways (left, right, rotate, drop)\n\n- The game is over if the blocks stack up in\n   such a way that the lines are not cleared\n   and reach the top of the screen\n\n- Each time a line is cleared in Tetris, you\n   are awarded points\n\n- Each time the blocks reach the top of the\n   screen, the game is over");
    rules.setPosition(5.f, window.getSize().y / 4);

    // Text : Press 'H' for Help
    Text help;
    help.setFont(font);
    help.setCharacterSize(22);
    help.setFillColor(Color::White);
    help.setString("-  Press 'H' for Help");
    help.setPosition(33.f, window.getSize().y / 1.85);

    // Text : For Level 1, Press 'A', then Press 'Enter'
    Text lev1;
    lev1.setFont(font);
    lev1.setCharacterSize(16);
    lev1.setFillColor(Color::White);
    lev1.setString("-  Press 'A', then 'Enter' for Level 1");
    lev1.setPosition(33.f, window.getSize().y / 1.6);

    // Text : For Level 2, Only Press 'Enter'
    Text lev2;
    lev2.setFont(font);
    lev2.setCharacterSize(18);
    lev2.setFillColor(Color::White);
    lev2.setString("-  For Level 2, Only Press 'Enter'");
    lev2.setPosition(33.f, window.getSize().y / 1.4);

    // Text : SCORE
    Text scoreDisp;
    scoreDisp.setFont(font);
    scoreDisp.setCharacterSize(16);
    scoreDisp.setFillColor(Color::Green);
    scoreDisp.setString("Score : " + to_string(score));
    scoreDisp.setPosition(230.f, window.getSize().y / 3.5);

    // Text : Press 'R' anytime to Restart the Game
    Text re;
    re.setFont(font);
    re.setCharacterSize(12);
    re.setFillColor(Color::White);
    re.setString("-  Press 'R' anytime to Restart the Game");
    re.setPosition(33.f, window.getSize().y / 1.2);

    // Defining a variable of Class Clock to store Time values
    Clock clock;

    //*************    Definition Ends here    *************//
    //////////////////////////////////////////////////////////




    //////////////////////////////////////////////////////////
    //**********    Game Loop Starts from Here    **********//

    while (window.isOpen())
    {
        // Defining how fast Shapes fall depending on the Level
        // Stops DOWN movement if key is no longer pressed
        if (lvl1 == true)
            delay = 0.6;
        else
            delay = 0.3;

        // Time variables
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;



        //*** Event Listening Part Starts from Here ***//
        Event e;

        // Event is occurring - until the game is in running state
        while (window.pollEvent(e))
        {
            // Close the Window if cross/close is clicked/pressed
            if (e.type == Event::Closed)
                window.close();

            // These Keys can be Held Down to continue their effect until they are not Released
            if (e.type == Event::KeyPressed)
            {
                // If 'Left' Key is Pressed, move the Shape Leftwards by one unit
                if (e.key.code == Keyboard::Left)
                    delta_x = -1;

                // If 'Right' Key is Pressed, move the Shape Rightwards by one unit
                else if (e.key.code == Keyboard::Right)
                    delta_x = 1;
            }

            // These Keys cannot be Held Down, can only be Pressed
            else if (e.type == Event::KeyReleased)
            {
                // If SpaceBar is Pressed, make the Shape drop quicker by skipping blocks
                if (e.key.code == Keyboard::Space)
                    drop = true;

                // If 'Up' Key is Pressed, Rotate the Shape by 90 Degrees
                else if (e.key.code == Keyboard::Up)
                    rotate = true;
            }
        }

        // If 'Down' Key is pressed, delay in falling Shape Decreases from 0.5 to 0.05
        if (Keyboard::isKeyPressed(Keyboard::Down)) 
            delay = 0.05;                           

        //*** Event Listening Part Ends Here ***//
        

        //*********************************************************************************************//
        /// Calling and Defining most of the Functions Here that are responsible to do specific Tasks ///

        // To Pause the Game at any time
        pause_game(pause);

        // To Resume the Game at any time if it is Paused 
        resume_game(pause);

        // To Restart the Game at any time during Gameplay
        restart_game(score, reset);

        // Another way to close the Game at any time
        escape_game(escape);
        if (escape == true)
            window.close();

        // Only works if Game is running and NOT Paused
        if (pause == false)
        {
            // Move Right
            if (delta_x == 1) 
            {
                right();
                delta_x = 0; // Resetting variable to initial value
            }

            // Move Left
            if (delta_x == -1) 
            {
                left();
                delta_x = 0; // Resetting variable to initial value
            }

            // Rotating the Shape
            if (rotate) 
            {
                rotate_piece();
                rc++;
                rotate = false; // Resetting variable to initial value
            }
            
            // This Function is responsible for making Shapes fall sequentially
            fallingPiece(timer, delay, drop, rc, colorNum, lvl1, start);

            //-----------------------------------------------------------------------------------------------------------------------------------------------------//
            // This code snippet is responsible for calculating the Score of the User and vanishing Completed Lines along with bringing the Upper Blocks Downwards //
            


            // line_no : the line which can complete and vanish,   count : counter for number of blocks in a row
            int count, line_no = 19; 

            for (int i = 19; i > 0; i--) // for each Row
            {
                count = 0; // Resetting variable to initial value each time Row Index changes

                for (int j = 0; j < 10; j++) // for each element in a row
                {
                    // Increment count if a Block exists in the Row
                    if (gameGrid[i][j])
                        count++;

                    // Move all of the upper Blocks one Line Downwards if Row Index (i) has become less than line_no
                    if (line_no > i)
                        gameGrid[line_no][j] = gameGrid[i][j];
                }

                // If line is NOT Complete, decrement line_no
                if (count != 10)
                    line_no--;

                else
                {
                    // Line has been Cleared
                    // Calculating Score based on no. of Lines cleared and Level Number

                    // Level 2
                    if (lvl1 == false)
                    {   
                        // Only 1 Line Cleared
                        if (line_no == i)
                            score += 10 * 2;

                        // Only 2 Lines Cleared
                        if (line_no - 1 == i)
                            score += 20 * 2;

                        // Only 3 Lines Cleared
                        if (line_no - 2 == i)
                            score += 30 * 2;

                        // Only 4 Lines Cleared
                        if (line_no - 3 == i)
                            score += 40 * 2;
                    }

                    // Level 1
                    else
                    {
                        // Only 1 Line Cleared
                        if (line_no == i)
                            score += 10;

                        // Only 2 Lines Cleared
                        if (line_no - 1 == i)
                            score += 20;
                        
                        // Only 3 Lines Cleared
                        if (line_no - 2 == i)
                            score += 30;

                        // Only 4 Lines Cleared
                        if (line_no - 3 == i)
                            score += 40;
                    }

                    // To constantly Update the Score on the Screen as Game progresses and more lines are Cleared
                    scoreDisp.setString("Score : " + to_string(score));
                }

                // If the User has Restarted the Game, reset the Score to 0
                if (reset == true)
                    score = 0;
            }
            
            //                                                          Code Snippet Ends Here                                                                     //
            //-----------------------------------------------------------------------------------------------------------------------------------------------------//
            
        }
        
        ///------------------  Calling and Defining most of the Functions Ends Here  -----------------///
        //*********************************************************************************************//


        // Commands and Code Snippets for Loading Images onto the Screen

        window.clear(Color::Black);
        window.draw(background);

        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (gameGrid[i][j] == 0)
                    continue;

                sprite.setTextureRect(IntRect(gameGrid[i][j] * 18, 0, 18, 18));
                sprite.setPosition(j * 18, i * 18);
                sprite.move(28, 31); // offset
                window.draw(sprite);
            }
        }

        for (int i = 0; i < 4; i++)
        {
            sprite.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
            sprite.setPosition(point_1[i][0] * 18, point_1[i][1] * 18);
            sprite.move(28, 31);
            window.draw(sprite);
        }

        //---The Final on Which Everything is Drawn Over is Loaded---//
        window.draw(frame);

        // Display the Start Menu when the User first Opens the Game
        if (count == 0)
            pause = true;

        // Code Snippet to Display and work around the GAME OVER Screen (only when the User has Lost the Game)
        for (int i = 0; i < N; i++)
        {
            if (gameGrid[0][i])
            {
                exit.setPosition(55.f, window.getSize().y / 1.95);
                exit.setString("Press 'esc' to Exit");
                pause = true;
                fin = true;
                window.clear(Color::Black);
                window.draw(gameOver);
                window.draw(exit);
            }
        }

        // Code Snippet to Display and work around in the Pause and Start Screen (only when the User has Paused the Game or the Window has just opened)
        if (pause == true && fin == false)
        {
            window.clear(Color::Black);
            
            // To enable User to Continue to the Game at any time
            resume_game(pause);
            
            window.draw(resume);
            window.draw(paused);
            window.draw(exit);
            window.draw(help);
            window.draw(re);

            if (start == false)
            {
                window.draw(lev1);
                window.draw(lev2);

                // To enable User to Resume the Game at any time
                level1(lvl1);
            }

            if (pause == false)
                window.draw(frame);

            
            // To enable User to go to the Help Screen at any time
            help_game(helpp);
            if (helpp == true)
            {
                window.clear(Color::Black);
                window.draw(ruless);
                window.draw(rules);
            }
        }

        //---The Window that now Contains the Frame is Displayed---//
        window.draw(scoreDisp);
        window.display();

        count = 1;
    }

    //*************    Game Loop Ends Here    **************//
    //////////////////////////////////////////////////////////

    return 0;
}
