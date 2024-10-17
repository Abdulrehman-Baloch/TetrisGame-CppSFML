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

//M.Abdulrehman_22I-1182_B_PF_Project

#include<iostream>
#include <SFML/Graphics.hpp>
#include <time.h>
#include "utils.h"
#include "blocks.h"
#include "functionality.h"
#include<sstream>
#include<SFML/Audio.hpp>
#include<string>
using namespace sf;
int main()
{
    
    int b_array[2] = { 0 };             // ARRAY FOR THE BOMB         
    float b_delay = 0.5;              // Delay for bomb
    float b_timer = 0;                // Timer for bomb 

    int s=0;
    for (int i = 0; i < 4; i++)                           // for removing the first tiny block
    {
        point_1[i][0] = BLOCKS[s][i] % 2;
        point_1[i][1] = BLOCKS[s][i] / 2;
    }
    srand(time(0));
    sf::Font font;
    font.loadFromFile("img/pink pastel.otf");
    sf::Font font1;
    font1.loadFromFile("img/Milky Honey.ttf");
    sf::Music sound;
    sound.openFromFile("img/Sneaky-Snitch.wav");
    sound.play();
    sf::SoundBuffer movement;
    movement.loadFromFile("img/move.wav");
    sf::Sound move;
    move.setBuffer(movement);

    Texture obj1, obj2, obj3, obj4, obj5;
   
    obj1.loadFromFile("img/tiles.png");
    obj2.loadFromFile("img/backround1.jpeg");
    obj3.loadFromFile("img/frame.png");
    obj5.loadFromFile("img/bomb.jpeg");


    Sprite sprite(obj1), background(obj2), frame(obj3), saaya3(obj4), bomb(obj5);
    int delta_x = 0, color = 1;
    float timer = 0, delay = 0.5;

    bool rotate = 0;
    bool flag = true;
    int b_color = 0;
    b_color = rand() % 7 + 1;
    int score = 0;
    int saaya[4][2];                // array for the shadow which will be equal in size to point_1

    RenderWindow window(VideoMode(400, 440), title);

    Clock clock;
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        if (flag == true)
        {
            timer += time;
            b_timer += time;
        }
        //---Event Listening Part---//
        Event e;
        while (window.pollEvent(e)) {                       //Event is occurring - until the game is in running state
            if (e.type == Event::Closed)                   //If cross/close is clicked/pressed
                window.close();                            //Opened window disposes
            if (e.type == Event::KeyPressed) {             //If any other key (not cross) is pressed
                if (e.key.code == Keyboard::Up)            //Check if the other key pressed is UP key
                    rotate = true;                         //Rotation gets on
                else if (e.key.code == Keyboard::Left)     //Check if the other key pressed is LEFT key
                {
                    delta_x = -1;                          //Change in X-Axis - Negative
                    move.play();
                }
                else if (e.key.code == Keyboard::Right)    //Check if the other key pressed is RIGHT key
                {
                    delta_x = 1;                           //Change in X-Axis - Positive
                    move.play();
                }

            }

        }
        if (Keyboard::isKeyPressed(Keyboard::Down))         // Just another way to detect key presses without event listener
            delay = 0.02;                                    // If DOWN key is pressed, delay in falling piece decreases from 0 to 0.06


        if (Keyboard::isKeyPressed(Keyboard::P))
        {
            flag = false;                                //  if P is pressed then game is paused
            sound.pause();
        }


        if (Keyboard::isKeyPressed(Keyboard::S))           // if S is pressed then game is resumed
        {
            flag = true;
            sound.play();
        }


        if (Keyboard::isKeyPressed(Keyboard::Space))      // hard drop of blocks      
        {
            if (flag == true)
            {
                while (space1())                           // If space1 fucntion returns a true value then the function space2 is called which makes the block hard drop
                    space2(timer);
            }
            move.play();
        }


        if (Keyboard::isKeyPressed(Keyboard::Escape))
            return 0;                                // If esc is pressed, the window is closed

        if (Keyboard::isKeyPressed(Keyboard::R))         // Using R key to restart the game
        {
            if (flag == true)                           // Restart when the blocks are falling
            {
                score = 0;
                for (int i = 0; i < 20; i++)
                {
                    for (int j = 0; j < 10; j++)
                        gameGrid[i][j] = 0;           // Whole grid is made equal to zero so that any occupied place in the grid becomes un-occupied
                }
                for (int i = 0; i < 4; i++)
                    point_1[i][1] = 0;                // using this so that current falling block becomes equal to zero
            }
            else if (flag == false)                    // Restart when the blocks are in hault(paused)
            {
                flag = true;
                for (int i = 0; i < 20; i++)
                {
                    for (int j = 0; j < 10; j++)
                        gameGrid[i][j] = 0;
                }
                for (int i = 0; i < 4; i++)
                    point_1[i][1] = 0;

                sound.play();
            }
        }

        ///////////////////////////////////////////////
        ///*** STAR T CALLING YOUR FUNCTIONS HERE ***///


        if (flag == true)
        {

            right_move(delta_x);                                    // movement to right using right key
            left_move(delta_x);                                     // movement to left using left key
            line_swap(score);                                       // line swap and clear fucntion
            fallingPiece(timer, delay, color, s);                    // Example: fallingPiece() function is called here
            fallingPiece_B(b_timer, b_delay, b_array, b_color);     // falling fucntion for bomb
            work_bomb(b_array, b_color);                           // working of bomb
            saaya2(saaya);                                          // shadow 
            gameOver(timer);                                        // Game over  
            rotation(rotate, s);                                    // rotation using UP key
        }

        ///*** YOUR CALLING STATEMENTS END HERE ***///
        //////////////////////////////////////////////


        window.clear(Color::Black);
        window.draw(background);
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                if (gameGrid[i][j] == 0)
                    continue;
                sprite.setTextureRect(IntRect(gameGrid[i][j] * 18, 0, 18, 18));
                sprite.setPosition(j * 18, i * 18);
                sprite.move(28, 31); //offset
                window.draw(sprite);
            }
        }
        for (int i = 0; i < 4; i++)
        {
            sprite.setTextureRect(IntRect(color * 18, 0, 18, 18));
            sprite.setPosition(point_1[i][0] * 18, point_1[i][1] * 18);
            sprite.move(28, 31);
            window.draw(sprite);
        }
        for (int i = 0; i < 4; i++)
        {
            saaya3.setTextureRect(IntRect(color * 18, 0, 18, 18));
            saaya3.setColor(Color(100, 100, 100, 200));
            saaya3.setPosition(saaya[i][0] * 18, saaya[i][1] * 18);          //drawing array of shadow just like point_1 
            saaya3.move(28, 31);
            window.draw(saaya3);
        }

        sf::Text display("Score:", font);                                  //displaying the score text
        display.setPosition(250, 50);
        window.draw(display);


        sf::Text value(std::to_string(score), font);                  //displaying value of score
        value.setPosition(300, 100);
        window.draw(value);

        sf::Text Pause("Paused\nPress s to\nresume\nPress esc to\nexit\nPress R to\nrestart", font1);                 //displaying pause menu
        Pause.setPosition(250, 150);
        Pause.setFillColor(Color::White);
        Pause.setCharacterSize(25);
        if (flag == false)                         // when P is pressed the flag becomes false and then pause window is displayed
        {
            window.draw(Pause);

        }
        sf::Text Over("Game Over\nPress esc to\nexit or R to \nrestart", font1);
        Over.setPosition(250, 350);
        Over.setFillColor(Color::Red);
        Over.setCharacterSize(20);
        for (int i = 0; i < 10; i++)
        {
            if (gameGrid[0][i] != 0)                   // checking for row 1 if there are any blocks in it
            {
                window.draw(Over);
                score = 0;
                b_timer = 0;
            }
        }

        bomb.setScale(0.08, 0.08);
        bomb.setPosition(b_array[0] * 18, b_array[1] * 18);
        bomb.move(28, 31);
        switch (b_color)                 // assigning different colors to the bomb according to the cases which are generated randomly
        {
        case 1:
            bomb.setColor(Color::Red);
            break;
        case 2:
            bomb.setColor(Color::Green);
            break;
        case 3:
            bomb.setColor(Color::Magenta);
            break;
        case 4:
            bomb.setColor(Color(255, 140, 0));
            break;
        case 5:
            bomb.setColor(Color(0, 0, 150, 0));
            break;
        case 6:
            bomb.setColor(Color::Blue);
            break;
        case 7:
            bomb.setColor(Color::Yellow);
            break;
        }

        window.draw(bomb);


        //---The Final on Which Everything is Drawn Over is Loaded---//
        window.draw(frame);
        //---The Window that now Contains the Frame is Displayed---//

        window.display();
        delay = 0.5;
        delta_x = 0;
        rotate = false;

    }

    return 0;
}
