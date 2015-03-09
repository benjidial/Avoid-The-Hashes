// Headers:
#include <iostream>
#include <string>

// Global Variables:
int g_nLives;
int g_nTurnsSurvived;
char g_chLeft;
char g_chRight;
char g_chExit;
char g_achField[5][5] =
{
	{' ', ' ', ' ', ' ', ' ', },
	{' ', ' ', ' ', ' ', ' ', },
	{' ', ' ', ' ', ' ', ' ', },
	{' ', ' ', ' ', ' ', ' ', },
	{' ', ' ', ' ', ' ', ' '}
};

// Classes:
class object
{
private:
	int nXPos;
	int nYPos;
public:
	void Create(int nInitXPos, int nInitYPos)
	{
		nXPos = nInitXPos;
		nYPos = nInitYPos;
	}
	void up()
	{
		if (nYPos != 1)
			nYPos--;
	}
	void left()
	{
		if (nXPos != 1)
			nXPos--;
	}
	void down()
	{
		if (nYPos != 5)
			nYPos++;
	}
	void right()
	{
		if (nXPos != 5)
			nXPos++;
	}
	int X()
	{
		return nXPos;
	}
	int Y()
	{
		return nYPos;
	}
};

// Global Objects:
object g_cPlayer;
object g_cEnemy1;
object g_cEnemy2;
object g_cApple;

// Forward Declarations:
void InitStuff();            // inits objs and settings
void Tutorial();             // show how one plays game
void Print(bool isV = true); // outputs from g_achField
void CheckForCollision();    // a collision returns one
void ProcessInput();         // will check against g_ch
void MoveOthers();           // move up 1 and lateral 1
void MakeNewApple();         // make a new apple object
bool operator==(object cObj1, object cObj2); // overloaded == function

// Functions:
int main()
{
	char chQ;
	while (true)
	{
		InitStuff();
		while (true)
		{
			std::cout << std::endl << "Would you like to hear the tutorial? (Y/N) ";
			char chW;
			std::cin >> chW;
			if ((chW == 'Y') || (chW == 'y'))
			{
				Tutorial();
				break;
			}
			if ((chW == 'N') || (chW == 'n'))
				break;
		}
		while (g_nLives >= 0)
		{
			Print();
			ProcessInput();
			MoveOthers();
			CheckForCollision();
			g_nTurnsSurvived++;
		}
		Print();
		using namespace std;
Q:
		cout << "You survived " << g_nTurnsSurvived << " turn(s)!" << endl;
		cout << "Continue playing? (Y/N) ";
		cin >> chQ;
		if ((chQ != 'Y') && (chQ != 'y') && (chQ != 'N') && (chQ != 'n'))
		{
			cout << "Invalid input." << endl;
			goto Q;
		}
		else if ((chQ == 'n') || (chQ == 'N'))
			return 0;

		std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	}
}
void InitStuff()
{
	using namespace std;
	cout << "Welcome!" << endl;
	cout << "What would you like to use for left?" << endl;
	cout << "(I recommend 'z'.) ";
	cin >> g_chLeft;
	cout << endl << "What would you like to use for right?" << endl;
	cout << "(I recommend 'c'.) ";
	cin >> g_chRight;
	cout << endl << "What would you like to use to exit?" << endl;
	cout << "(I recommend 'q'.) ";
	cin >> g_chExit;
	cout << endl << "Finally, enter a random integer." << endl;
	int nQ;
	cin >> nQ;
	srand(nQ);
	g_cPlayer.Create(3, 1);
	g_cEnemy1.Create(1, 1);
	g_cEnemy2.Create(5, 2);
	g_cApple.Create((rand() % 5) - 1, 5);
	g_nLives = 3;
	g_nTurnsSurvived = -1;
}
void Tutorial()
{
	Print(false);
	using namespace std;
	cout << "Press enter." << endl;
	cin.clear();
	cin.ignore(255, '\n');
	cin.get();
	cout << "'$' represents you." << endl;
	cout << "'#' represents an enemy.  If you touch one you will lose a life." << endl;
	cout << "'@' represents the apple.  If you touch it you will gain a life." << endl;
	cout << "Press enter." << endl;
	cin.clear();
	cin.get();
	cout << "You can move left and right with '" << g_chLeft << "' and '" << g_chRight << "', respectively." << endl;
	cout << "The enemies will randomly move left or right, and will always move up 1." << endl;
	cout << "The apple will not move left or right, and will move up about half of the time." << endl;
	cout << "Press enter to start playing." << endl;
	cin.clear();
	cin.get();
	cout << endl;
}
void Print(bool isV)
{
	char g_achField[5][5] =
	{
		{' ', ' ', ' ', ' ', ' ', },
		{' ', ' ', ' ', ' ', ' ', },
		{' ', ' ', ' ', ' ', ' ', },
		{' ', ' ', ' ', ' ', ' ', },
		{' ', ' ', ' ', ' ', ' '}
	};
	g_achField[g_cApple.Y() - 1][g_cApple.X() - 1] = '@';
	g_achField[g_cPlayer.Y() - 1][g_cPlayer.X() - 1] = '$';
	g_achField[g_cEnemy1.Y() - 1][g_cEnemy1.X() - 1] = '#';
	g_achField[g_cEnemy2.Y() - 1][g_cEnemy2.X() - 1] = '#';
	using namespace std;
	if (g_nLives >= 0)
	{
		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
		if (isV)
		{
			cout << "Lives:\t" << g_nLives << endl;
			cout << "Turn:\t" << g_nTurnsSurvived + 1 << endl;
		}
		cout << "}-----{" << endl;
		for (int nCount1 = 0; nCount1 < 5; nCount1++)
		{
			cout << "}";
			for (int nCount2 = 0; nCount2 < 5; nCount2++)
				cout << g_achField[nCount1][nCount2];
			cout << "{" << endl;
		}
		cout << "}-----{" << endl;
	}
}
void CheckForCollision()
{
	if (g_cPlayer == g_cApple)
	{
		g_nLives++;
		MakeNewApple();
	}
	if (g_cEnemy1 == g_cApple)
		MakeNewApple();
	if (g_cEnemy2 == g_cApple)
		MakeNewApple();
	if (g_cPlayer == g_cEnemy1)
		g_nLives--;
	if (g_cPlayer == g_cEnemy2)
		g_nLives--;
}
void ProcessInput()
{
PauseBack:
	char chQ;
	std::cin >> chQ;
	if (chQ == g_chLeft)
		g_cPlayer.left();
	else if (chQ == g_chRight)
		g_cPlayer.right();
	else if (chQ == g_chExit)
	{
		using namespace std;
		do
		{
			char chQ;
			cout << "Are you sure you want to exit? (Y/N)";
			cin >> chQ;
			if ((chQ == 'Y') || (chQ == 'y'))
				exit(0);
		} while ((chQ != 'N') && (chQ != 'n'));
		goto PauseBack;
	}
	else if (rand() % 2 == 1)
		g_cPlayer.left();
	else g_cPlayer.right();
}
void MoveOthers()
{
	if (rand() % 2 == 1)
		g_cEnemy1.left();
	else
		g_cEnemy1.right();
	if (g_cEnemy1.Y() == 1)
	{
		g_cEnemy1.down();
		g_cEnemy1.down();
		g_cEnemy1.down();
		g_cEnemy1.down();
	}
	else g_cEnemy1.up();
	if (rand() % 2 == 1)
		g_cEnemy2.left();
	else
		g_cEnemy2.right();
	if (g_cEnemy2.Y() == 1)
	{
		g_cEnemy2.down();
		g_cEnemy2.down();
		g_cEnemy2.down();
		g_cEnemy2.down();
	}
	else g_cEnemy2.up();
	if (rand() % 2 == 1)
	{
		if (g_cApple.Y() != 1)
			g_cApple.up();
		else MakeNewApple();
	}
}
void MakeNewApple()
{
AppleQ:
	int nQ = (rand() % 5) + 1;
	if ((nQ == g_cEnemy1.X()) && (5 == g_cEnemy1.Y()))
		goto AppleQ;
	if ((nQ == g_cEnemy2.X()) && (5 == g_cEnemy2.Y()))
		goto AppleQ;
	g_cApple.Create(nQ, 5);
}
bool operator==(object cObj1, object cObj2)
{
	if ((cObj1.X() == cObj2.X()) && (cObj1.Y() == cObj2.Y()))
		return 1;
	else return 0;
}