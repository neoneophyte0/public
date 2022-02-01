#include <iostream>
#include <conio.h>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <Windows.h>
using namespace std;

bool CheckMove(char Move, int MoveArray[4][4]);							//functions used
void Display(int DisplayArray[4][4]);
void AddsANumber(int AddingArray[4][4]);
int Check(int temporary[4][4], int CheckArray[4][4]);
int maxScore(int MainArray[4][4]);

int main()
{

	int x, y, a, b;
	int MainArray[4][4];

	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			MainArray[j][i] = 0;
		}
	}
	system("color 9f");
      cout << "\n\n\n\n\n\n" << right <<setw(50)<< "WELCOME TO 1024";
      Sleep(600);
      system("cls");

      system("color f9");

	Display(MainArray);

	char s;
	cout << "Press s to start: ";
	s = _getch();

	while (s != 's')
		s = _getch();
	if (s == 's')
	{
		system("cls");
	}

	srand(time(0));
	x = rand() % 4;
	y = rand() % 4;

	while (true)
	{
		a = rand() % 4;
		b = rand() % 4;
		if (x != a && y != b)
			break;
	}

	MainArray[a][b] = (rand() % 2) + 1;
	MainArray[x][y] = (rand() % 2) + 1;

	Display(MainArray);

	int TempArray[4][4];
	char Move = 'j';
	char LastMove = 'a';
	bool xx = false;

	for (int i = 0; i < 4; i++)													//checks if empty slots are available
	{
		for (int j = 0; j < 4; j++)
		{
			if (MainArray[i][j] == 0)
			{
			    //checks if empty slots are available
				xx = true;
				break;
			}
		}
	}

	while (xx)
	{
		bool check = false;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 3; j++)	//checks if any moves are left(any numbers can be added)
			{
			    //Also checks if there any zeros left because up there we compared the rows and columns but still a zero can be left

                if (MainArray[i][j] == MainArray[i][j + 1] || MainArray[j + 1][i] == MainArray[j][i] || MainArray[i][j] == 0 || MainArray[i][j + 1] == 0)
				{
					check = true;
				}
			}
		}

        for(int i = 0; i < 4; i++)
           {
               for(int j = 0; j < 4; j++)
               {
                if(MainArray[i][j] == 1024)
                    {
                        system("cls");
						cout << "Your Final Score is: " << maxScore(MainArray) << endl;
                        cout << "CONGRATULATIONS, YOU PLAYED WELL TILL THE END AND HAVE SUCCESSFULLY FORMED 1024." << endl;

                        system("pause");
                        return 0;
                    }
               }
           }


		if (check == false)
		{
		    system("cls");
		    system("color 9f");
			cout << "Your Final Max Score is: " << maxScore(MainArray) << endl;
			cout << "GAME OVER" << endl;

			system("pause");
			return 0;
		}

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				TempArray[i][j] = MainArray[i][j];		//copying
			}
		}

		LastMove = Move;
		cout << "Enter move!";
		Move = _getch();

		while (Move != 'u' && Move != 'l' && Move != 'd' && Move != 'r')
		{
			Move = _getch();
		}

		bool Checking;
		Checking = CheckMove(Move, MainArray);
        // checking if a new number has to be added or not! for example if all the elements are shifted upwards at 'u'...																//to be added or not! e.g if all the

		system("cls");

		Display(MainArray);
		Sleep(200);

		if (Checking == false && LastMove == Move)
			continue;
		if (!Check(TempArray, MainArray))
			AddsANumber(MainArray);

		Sleep(200);

		system("cls");

		Display(MainArray);

	}
	system("pause");
	return 0;
}

void Display(int DisplayArray[4][4])
{
	cout << "                         ";
	for (int i = 0; i < 30; i++)
	{
		if (i == 0)
			cout << static_cast<char>(201);
		else {
			if (i == 29)
				cout << static_cast<char>(187);
			else
				cout << static_cast<char>(205);
		}
	}
	cout << endl;

	for (int j = 0; j < 4; j++)
	{
		cout << "                         ";
		cout << static_cast<char>(186);

		for (int i = 0; i < 4; i++)
		{
			if (DisplayArray[j][i] != 0 && DisplayArray[j][i] > 0)
				cout << "|" << setw(5) << DisplayArray[j][i] << "|";
			else
				cout << "|     |";
		}
		cout << static_cast<char>(186);
		cout << endl;
	}

	cout << "                         ";
	for (int i = 0; i < 30; i++)
	{
		if (i == 0)
		{
			cout << static_cast<char>(200);
		}
		else
		{
			if (i == 29)
			{
				cout << static_cast<char>(188);
			}
			else
			{
				cout << static_cast<char>(205);
			}
		}
	}

	cout << endl << endl;

	char design[10][10];

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			design[i][j] = ' ';
		}
	}
	cout << right << "Enter your moves l, r, u, d";
	design[0][3] = 'u';
	design[1][3] = '+';
	design[2][0] = 'l';
	design[2][1] = '+';
	design[2][2] = ' ';
	design[2][3] = 'o';
	design[2][4] = ' ';
	design[2][5] = '+';
	design[2][6] = 'r';
	design[3][3] = '+';
	design[4][3] = 'd';
	cout << endl;

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			cout << design[i][j];
		}
		cout << endl;
	}
}

bool CheckMove(char Move, int MoveArray[4][4])
{
	if (Move == 'u')
	{
		int check = 0;
		int count = 0;

		for (int j = 0; j < 4; j++)
		{
			for (int i = 0; i < 3; i++)
			{
				if (MoveArray[i][j] == MoveArray[i + 1][j])
				{
					if (MoveArray[i][j] == 0 && MoveArray[i + 1][j] == 0)
						continue;

				    count++;
				    check++;
				    MoveArray[i][j] = MoveArray[i][j] + MoveArray[i + 1][j];
				    MoveArray[i + 1][j] = 0;
				}
            }
		}

		//if theres a zero in eg in 2002 then when you press u key the array should merge to 4000, so after sorting to 2200, we need to merge again

		for (int j = 0; j < 4; j++)
		{
			if (MoveArray[1][j] == 0 || MoveArray[2][j] == 0)
			{
				//if any of the upper terms are left as zero, array elements will now shift upwards.
				for (int count1 = 0; count1 < 3; count1++)
				{
					for (int i = 3; i > 0; i--)
					{
						if (MoveArray[i - 1][j] == 0)
						{
							check++;
							MoveArray[i - 1][j] = MoveArray[i][j];
							MoveArray[i][j] = 0;
						}
					}
				}

				if (count == 0)
				{
					for (int i = 0; i < 4; i++)
					{
						if (MoveArray[i][j] == MoveArray[i + 1][j])
						{
							if (MoveArray[i][j] == 0 && MoveArray[i + 1][j] == 0)
								continue;
							count++;
							check++;
							MoveArray[i][j] = MoveArray[i][j] + MoveArray[i + 1][j];
							MoveArray[i + 1][j] = 0;
						}
					}
				}
			}
			else
			{
				//if any of the upper terms are left as zero, array elements will now shift upwards.
				for (int count1 = 0; count1 < 3; count1++)
				{
					for (int i = 3; i > 0; i--)
					{
						if (MoveArray[i - 1][j] == 0)
						{
							MoveArray[i - 1][j] = MoveArray[i][j];
							MoveArray[i][j] = 0;
							check++;
						}
					}
				}
			}
		}

		for (int i = 0; i < 4; i++)
		{
			if (MoveArray[0][i] == 0)
			{
				return true;    //this Full fills one of the conditions to add a new 2 or 1
			}
		}
		return false;
	}

	if (Move == 'd')
	{
		int count = 0; // keeps count of merging/addition of same numbers in one move
		for (int j = 0; j < 4; j++)
		{
			//merging is gonna be downwards and if theres 0 1 1 1 in a column then we will merge the numbers at the end first so, the loop starts from 3
			for (int i = 3; i > 0; i--)
			{
				if (MoveArray[i][j] == MoveArray[i - 1][j])
				{
					if (MoveArray[i][j] == 0 && MoveArray[i - 1][j] == 0)
						continue;
					count++;
					MoveArray[i][j] = MoveArray[i][j] + MoveArray[i - 1][j];
					MoveArray[i - 1][j] = 0;
				}
			}
		}
		//if theres a zero eg in 2002 then when you press d key the array should merge to 0004, so after sorting to 0022 we need to merge it again
		for (int j = 0; j < 4; j++)
		{
        //if any of the lower terms are left as zero, array elements will now shift downwards.
			if (MoveArray[1][j] == 0 || MoveArray[2][j] == 0)
			{
				for (int count1 = 0; count1 < 3; count1++)
				{
					for (int i = 0; i < 3; i++)
					{
						if (MoveArray[i + 1][j] == 0)
						{
							MoveArray[i + 1][j] = MoveArray[i][j];
							MoveArray[i][j] = 0;
						}
					}
				}

				if (count == 0)
				{
					for (int i = 3; i > 0; i--)
					{
						if (MoveArray[i][j] == MoveArray[i - 1][j])
						{
							if (MoveArray[i][j] == 0 && MoveArray[i - 1][j] == 0)
								continue;
							count++;
							MoveArray[i][j] = MoveArray[i][j] + MoveArray[i - 1][j];
							MoveArray[i - 1][j] = 0;
						}
					}
				}
			}

			else
			{
				//if any of the lower terms are left as zeros, array elements will now shift downwards
				for (int count1 = 0; count1 < 3; count1++)
				{
					for (int i = 0; i < 3; i++)
					{
						if (MoveArray[i + 1][j] == 0)
						{
							MoveArray[i + 1][j] = MoveArray[i][j];
							MoveArray[i][j] = 0;
						}
					}
				}
			}
		}

		for (int i = 0; i < 4; i++)
		{
			if (MoveArray[3][i] == 0 && count != 0)
			{
				return true;
			}
		}

		return false;
	}

	if (Move == 'r')
	{
		int count = 0;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 3; j > 0; j--)
			{
				if (MoveArray[i][j] == MoveArray[i][j - 1])
				{
					if (MoveArray[i][j] == 0 && MoveArray[i][j - 1] == 0)
						continue;
					count++;
					MoveArray[i][j] = MoveArray[i][j] + MoveArray[i][j - 1];
					MoveArray[i][j - 1] = 0;
				}
			}
		}

		//if there is a zero example in a row 2002 then when you press r key the array should merge to 0004, so after sorting to 0022 we need to merge it again
		for (int i = 0; i < 4; i++)
		{
			if (MoveArray[i][1] == 0 || MoveArray[i][2] == 0)
			{
				//if any of the forward terms are left as zero, array elements will now shift rightwards
				for (int count1 = 0; count1 < 3; count1++)
				{
					for (int j = 0; j < 3; j++)
					{
						if (MoveArray[i][j + 1] == 0)
						{
							MoveArray[i][j + 1] = MoveArray[i][j];
							MoveArray[i][j] = 0;
						}
					}
				}

				if (count == 0)
				{
					for (int j = 3; j > 0; j--)
					{
						if (MoveArray[i][j] == MoveArray[i][j - 1])
						{
							if (MoveArray[i][j] == 0 && MoveArray[i][j - 1] == 0)
								continue;
							count++;
							MoveArray[i][j] = MoveArray[i][j] + MoveArray[i][j - 1];
							MoveArray[i][j - 1] = 0;
						}
					}
				}
			}

			else
			{
				//if any of the forward terms are left as zero, array elements will now shift rightwards
				for (int count1 = 0; count1 < 3; count1++)
				{
					for (int j = 0; j < 3; j++)
					{
						if (MoveArray[i][j + 1] == 0)
						{
							MoveArray[i][j + 1] = MoveArray[i][j];
							MoveArray[i][j] = 0;
						}
					}
				}
			}
		}

		for (int i = 0; i < 4; i++)
		{
			if (MoveArray[i][3] == 0)
			{
				return true;
			}
		}
		return false;
	}

	if (Move == 'l')
	{
		int count = 0;
		for (int j = 0; j < 4; j++)
		{
			for (int i = 0; i < 3; i++)
			{
				if (MoveArray[j][i] == MoveArray[j][i + 1])
				{
					if (MoveArray[j][i] == 0 && MoveArray[j][i + 1] == 0)
						continue;
					count++;
					MoveArray[j][i] = MoveArray[j][i] + MoveArray[j][i + 1];
					MoveArray[j][i + 1] = 0;
				}
			}
		}

		for (int j = 0; j < 4; j++)
		{
			if (MoveArray[j][1] == 0 || MoveArray[j][2] == 0)
			{
				//if any of the leftward terms column-wise are left as zero, array elements will now shift leftwards
				for (int count1 = 0; count1 < 3; count1++)
				{
					for (int i = 3; i > 0; i--)
					{
						if (MoveArray[j][i - 1] == 0)
						{
							MoveArray[j][i - 1] = MoveArray[j][i];
							MoveArray[j][i] = 0;
						}
					}
				}

				if (count == 0)
				{
					for (int i = 0; i < 3; i++)
					{
						if (MoveArray[j][i] == MoveArray[j][i + 1])
						{
							if (MoveArray[j][i] == 0 && MoveArray[j][i + 1] == 0)
								continue;
							count++;
							MoveArray[j][i] = MoveArray[j][i] + MoveArray[j][i + 1];
							MoveArray[j][i + 1] = 0;
						}
					}
				}
			}
			else
			{
				//if any of the leftward terms are left as zero, array elements will now shift leftwards

				for (int count1 = 0; count1 < 3; count1++)
				{
					for (int i = 3; i > 0; i--)
					{
						if (MoveArray[j][i - 1] == 0)
						{
							MoveArray[j][i - 1] = MoveArray[j][i];
							MoveArray[j][i] = 0;
						}
					}
				}
			}
		}
		for (int i = 0; i < 4; i++)
		{
			if (MoveArray[i][0] == 0 && count != 0)
			{
				return true;
			}
		}
		return false;
	}
}

void AddsANumber(int AddingArray[4][4])
{
	int x, y;
	bool CheckForZero = false;

	srand(time(0));
	//randomizing array

	x = rand() % 4;
	y = rand() % 4;

	while (AddingArray[x][y] != 0)
	{
		x = rand() % 4;
		y = rand() % 4;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (AddingArray[i][j] == 0)
				{
					CheckForZero = true;
					break;
				}
			}
		}
		if (CheckForZero == false)
			break;
	}
	if (AddingArray[x][y] == 0)
	{
		AddingArray[x][y] = ((rand() % 2) + 1);
	}
}

int Check(int temporary[4][4], int CheckArray[4][4])
{
	int num = 1, i, j;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
            if (temporary[i][j] != CheckArray[i][j])
			{
				//checking if any shifting/change occured after we executed the move
				num = 0;
				break;
			}
	return num;
}
int maxScore(int MainArray[4][4]) //The board Maximum number
{
	int max = MainArray[0][0];
	for (int i = 0; i <= 3; i++)
		for (int j = 0; j <= 3; j++)
			if (MainArray[i][j] > max)
				max = MainArray[i][j];
	return max;
}
