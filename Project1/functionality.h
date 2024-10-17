#pragma once

/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * You need to define the required function in the part instructed here below.
 * Avoid making any unnecessary changes, particularly the ones you don't understand.
 * The different pieces should be defined using an array - uncomment the following code once you are done creating the array.
 * TIP: Understand thoroughly before getting started with coding.
 * */

 //---Piece Starts to Fall When Game Starts---//

 //M.Abdulrehman_22I-1182_B_PF_Project


void fallingPiece(float& timer, float& delay, int& color, int& s) {
	if (timer >= delay)
	{
		for (int i = 0; i < 4; i++) {
			point_2[i][0] = point_1[i][0];
			point_2[i][1] = point_1[i][1];
			point_1[i][1] += 1;            //How much units downward
		}
		if (!anamoly())
		{
			for (int i = 0; i < 4; i++)
				gameGrid[point_2[i][1]][point_2[i][0]] = color;
			color = 1 + rand() % 7;
			s = rand() % 7;
			//--- Un-Comment this Part When You Make BLOCKS array---//

			for (int i = 0; i < 4; i++)
			{
				point_1[i][0] = BLOCKS[s][i] % 2;
				point_1[i][1] = BLOCKS[s][i] / 2;
			}

		}
		timer = 0;
	}
}
/////////////////////////////////////////////
///*** START CODING YOUR FUNTIONS HERE ***///

// FUNCTION : 1

void right_move(int& delta_x)				//for right movement
{
	if (delta_x == 1)
	{
		for (int i = 0; i < 4; i++)
		{
			if (point_1[i][0] == N - 1)			//condition so that blocks do not move out of grid from right side
				return;
			if (gameGrid[point_1[i][1]][point_1[i][0] + 1] != 0)		//using this so that blocks on right do not overlap blocks on their left
				return;
		}
		for (int i = 0; i < 4; i++)
			point_1[i][0] += delta_x;				// making the blocks move right 
	}
}

// FUNCTION : 2
void left_move(int& delta_x)			//for left movement
{

	if (delta_x == -1)
	{
		for (int i = 0; i < 4; i++)
		{
			if (point_1[i][0] == 0)   		//condition so that blocks do not move out of grid from left side
				return;
			if (gameGrid[point_1[i][1]][point_1[i][0] - 1])		//using this so that blocks on left do not overlap blocks on their right
				return;
		}
		for (int i = 0; i < 4; i++)
			point_1[i][0] += delta_x;				// making the blocks move left
	}
}

// FUCNTION : 3
void line_swap(int& score)
{
	bool flag;
	int counter = 0;
	for (int i = M - 1; i > 0; i--)
	{

		flag = 0;
		for (int j = N - 1; j >= 0; j--)
		{
			if (gameGrid[i][j] == 0)		// checking if the ith row and jth column is empty
				flag = 1;

		}

		if (flag == 0)
		{
			++counter;
			switch (counter)
			{
			case 1:					// If counter=1, add 10 to score variable
				score += 10;
				break;
			case 2:					// If counter=2, add 20 to score variable
				score += 20;
				break;
			case 3:					// If counter=3, add 30 to score variable
				score += 30;
				break;
			case 4:					// If counter=4, add 40 to score variable
				score += 40;

				break;
			}
			for (int k = i; k > 0; k--)				// Loop for the current row
			{
				for (int l = 0; l < 10; l++)
				{
					gameGrid[k][l] = gameGrid[k - 1][l];	// swapping the blocks of the row with the blocks of the row which is above
				}
			}
		}
	}
}

// FUNCTION : 4

void gameOver(float& timer)
{
	bool flag = false;
	for (int i = 0; i < 10; i++)
	{
		if (gameGrid[0][i] != 0)		// checking if the first row of the game contains even a single block
			flag = true;
	}
	if (flag == true)
	{
		timer = 0;					// if the first row has a block at any point of location, timer is set to zero so blocks stop falling 

	}

}
// FUCNTION : 5

void rotation(bool& rotate, int& s)
{
	int Py = point_1[1][1];            // this is the central point about which block will rotate
	int Px = point_1[1][0];
	int x, y;
	if (rotate == true)
	{
		for (int i = 0; i < 4; i++)
		{
			if (point_1[i][0] == 0 || point_1[i][0] == N - 1)
				return;										//if block is in first or last column, rotation don't work
			else if (s == 0 && point_1[i][0] == 1)
				return;										//if block is "I", which is the first shape in BLOCKS array, when it is in 2 column, rotation dont work for "I" only.
		}

		for (int i = 0; i < 4; i++)
			if (point_1[i][0] > 0 || point_1[i][0] < N - 1)
			{
				x = point_1[i][1] - Py;									//these are temporary variables for simplicity
				y = point_1[i][0] - Px;
				point_1[i][0] = Px - x;
				point_1[i][1] = Py + y;
			}
	}
}
// FUCNTION : 6

bool space1()
{
	for (int i = 0; i < 4; i++)
	{
		if (point_1[i][1] == 19)								//	checking if the block is in the last row of the gameGrid
			return 0;										// if condition becomes true then this fucntion will return 0 or false value
		if (gameGrid[point_1[i][1] + 1][point_1[i][0]] != 0)		// checking if there is a block infront of a block in y-axis
			return 0;
	}
	return 1;												// if above both conditions become false then the fucntion will return true value

}

// FUNCTION : 7

void space2(float& timer)
{
	for (int i = 0; i < 4; i++)
	{
		point_1[i][1] += 1;			// adding 1 in y-axis of point_1 until the fucntion space1 remains true
	}
	timer = 0;							// making timers zero so that when space is pressed only one block hard drops
}

// FUNCTION : 8

bool saaya1(int saaya[4][2])
{
	for (int i = 0; i < 4; i++)
	{
		if (saaya[i][1] >= 19)									// checking if the current location of shadow is within grid or not
			return 0;
		if (gameGrid[saaya[i][1] + 1][saaya[i][0]] != 0)			// checking if there is already a shadow infront of an incoming shadow
			return 0;
	}
	return 1;
}

// FUCNTION : 9

void saaya2(int saaya[4][2])
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 2; j++)
			saaya[i][j] = point_1[i][j];						// making the shadow equal to  point_1 so shadow have the same coordinates as location of point_1

	while (saaya1(saaya))									// This will continue until the fucntion saaya1 returns a false value after checking the conditions
	{
		for (int i = 0; i < 4; i++)
		{
			saaya[i][1] += 1;								   //bringing it down until a block or floor comes in way
		}
	}
}

// FUNTION : 10

void fallingPiece_B(float& b_timer, float& b_delay, int b_array[2], int& b_color)			// same fucntion for bomb as for point_1 above
{
	if (b_timer >= b_delay)
	{
		if (!anamoly())
		{

			gameGrid[b_array[1]][b_array[0]] = b_color;							//assigning value of color to the current position of bomb
		}

		if (b_array[1] != M - 1)
			b_array[1] += 1;														//if bomb is not on floor then increase it along y
		else
		{
			srand(time(0));
			b_color = rand() % 7 + 1;
			b_array[1] = 0;														//if it reaches floor so assign new color take it to the top and asign new random x axis position
			b_array[0] = rand() % 10;
		}
		b_timer = 0;
	}
}

// FUCNTION : 11

bool bomb_check(int b_array[2])
{
	if (gameGrid[b_array[1] + 1][b_array[0]] != 0)				// check if a block comes below the bomb
	{
		return 1;
	}

	return 0;
}

// FUNCTION : 12

void work_bomb(int b_array[2], int b_color)				// main working of bomb
{
	if (bomb_check(b_array))								// This continues until fucntion bomb_check returns a true value
	{

		if (b_color == gameGrid[b_array[1] + 1][b_array[0]])  //check if colors are same of bomb and block below it
		{
			for (int i = 0; i <= M - 1; i++)
				for (int j = 0; j < N; j++)
					gameGrid[i][j] = 0;						// whole game grid is cleared if the color of the bomb and the color of the block on which it hits matches
		}
		b_color = rand() % 7 + 1;								// assigning random colors to bomb
		b_array[1] = 0;									// taking the bomb to the top
		b_array[0] = rand() % 10;							// assigning random x-axis position to block once it starts falling through the grid
	}
}
///*** YOUR FUNCTIONS END HERE ***///
/////////////////////////////////////
