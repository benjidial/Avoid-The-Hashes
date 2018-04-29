#include <stdio.h>
#include <stdlib.h>

struct point {
  int xPos;
  int yPos;
};

int lives;
int turnsSurvived;
char left;
char right;
char field[5][5] = {
  {' ', ' ', ' ', ' ', ' '},
  {' ', ' ', ' ', ' ', ' '},
  {' ', ' ', ' ', ' ', ' '},
  {' ', ' ', ' ', ' ', ' '},
  {' ', ' ', ' ', ' ', ' '}
};

struct point player;
struct point enemy1;
struct point enemy2;
struct point apple;

void print(int isV) {
  for (int i = 0; i < 5; i++)
    for (int j = 0; j < 5; j++)
      field[i][j] = ' ';
  field[apple.yPos - 1][apple.xPos - 1] = '@';
  field[player.yPos - 1][player.xPos - 1] = '$';
  field[enemy1.yPos - 1][enemy1.xPos - 1] = '#';
  field[enemy2.yPos - 1][enemy2.xPos - 1] = '#';

  if (lives) {
    if (isV)
      printf("Lives:\t%d\nTurn:\t%d\n", lives, turnsSurvived + 1);
    puts("}-----{");
    for (int count1 = 0; count1 < 5; count1++) {
      putchar('}');
      for (int count2 = 0; count2 < 5; count2++)
        putchar(field[count1][count2]);
      putchar('{');
      putchar('\n');
    }
    puts("}-----{");
  }
}

void makeNewApple() {
  int x;
  do
    x = (rand() % 5) + 1;
  while (((x == enemy1.xPos) && (5 == enemy1.yPos)) || ((x == enemy2.xPos) && (5 == enemy2.yPos)));
  apple = (struct point){x, 5};
}

int main() {
  puts("Welcome!  What would you like to use for left and right?");
  left = getchar();
  right = getchar();
  getchar();
  puts("Finally, enter a random integer.");
  int seed;
  scanf("%d", &seed);
  srand(seed);

  player = (struct point){3, 1};
  enemy1 = (struct point){1, 1};
  enemy2 = (struct point){5, 2};
  apple = (struct point){(rand() % 5) - 1, 5};
  lives = 3;
  turnsSurvived = -1;

  print(0);
  puts("Press enter.");
  getchar();
  puts("'$' represents you.\n"
       "'#' represents an enemy.  If you touch one you will lose a life.\n"
       "'@' represents the apple.  If you touch it you will gain a life.\n"
       "Press enter.");
  getchar();
  printf("You can move left and right with '%c' and '%c', respectively.\n"
         "The enemies will randomly move left or right, and will always move up 1.\n"
         "The apple will not move left or right, and will move up half of the time.\n"
         "Press enter to start playing.\n", left, right);
  getchar();

  while (lives) {
    print(1);

    char ch = getchar();
    getchar();
    if (ch == left) {
      if (player.xPos != 1)
        player.xPos--;
    }
    else if (ch == right) {
      if (player.xPos != 5)
        player.xPos++;
    }
    else if (rand() % 2 == 1) {
      if (player.xPos != 1)
        player.xPos--;
    }
    else if (player.xPos != 5)
      player.xPos++;

    if (rand() % 2 == 1) {
      if (enemy1.xPos != 1)
        enemy1.xPos--;
    }
    else if (enemy1.xPos != 5)
      enemy1.xPos++;
    if (enemy1.yPos == 1)
      enemy1.yPos = 5;
    else
      enemy1.yPos--;

    if (rand() % 2 == 1) {
      if (enemy2.xPos != 1)
        enemy2.xPos--;
    }
    else if (enemy2.xPos != 5)
      enemy2.xPos++;
    if (enemy2.yPos == 1)
      enemy2.yPos = 5;
    else
      enemy2.yPos--;

    if (rand() % 2 == 1) {
      if (apple.yPos != 1)
        apple.yPos--;
      else
        makeNewApple();
    }

    if ((player.xPos == apple.xPos) && (player.yPos == apple.yPos)) {
      lives++;
      makeNewApple();
    }
    if ((enemy1.xPos == apple.xPos) && (enemy1.yPos == apple.yPos))
      makeNewApple();
    if ((enemy2.xPos == apple.xPos) && (enemy2.yPos == apple.yPos))
      makeNewApple();
    if ((player.xPos == enemy1.xPos) && (player.yPos == enemy1.yPos))
      lives--;
    if ((player.xPos == enemy2.xPos) && (player.yPos == enemy2.yPos))
      lives--;

    turnsSurvived++;
  }
  print(0);

  printf("You survived %d turn(s)!\n", turnsSurvived);
  return 0;
}
