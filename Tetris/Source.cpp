#include <iostream>
#include <vector>
#include<Windows.h>
#include"Brick.h"

void SetUp();
void Draw();
void Input();
void Logic();

bool gameOver, hit;

constexpr int width = 10, height =20;

Bitmap<width,height> map(false), prevMap(false);

Brick brick;
int score;

float timer, controlTimer;

int main()
{
	system("cls");
	SetUp();

	while (!gameOver) {

		if (hit==true) {
			map = prevMap;
			//+New prick
			brick = Brick(Brick::Type(rand()%7));
			brick.worldPosition = { width / 2 - int(brick.GetSize() / 2), 0 };
			hit = false;
			timer = -10;
			controlTimer = 0;
		}
		Input();
		Logic();
		Draw();
		Sleep(40);
	}

	std::cout << "GAME OVER !" << std::endl;
	Sleep(2000);
	std::cout << "Try again?" << std::endl;
	system("pause");
	main();

	return 0;
}

void SetUp()
{
	srand(time(0));
	map = Bitmap<width, height>(false);
	timer = -10;
	controlTimer = 0;
	gameOver = false;
	score = 0;
	brick = Brick(Brick::Type(rand() % 7));
	brick.worldPosition = { width / 2 - int(brick.GetSize()/2), 0};
	hit = false;
}

void Draw()
{
	std::string canvas = "";

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });

	for (int i = -1; i <= width; i++) {
		canvas += "##";
	}
	canvas += '\n';

	for (int j = 0; j < height; j++) {
		for (int i = -1; i <= width; i++) {
			if(i==-1||i==width)
				canvas += "::";
			else if (map[i][j]==true) {
					canvas += "[]";
			}
			else {
				canvas += "  ";
			}
		}
		canvas += '\n';
	}

	for (int i = -1; i <= width; i++) {
		canvas += "##";
	}
	canvas += '\n';

	std::cout << canvas;
	std::cout << "Score: " << score << " pts    " << std::endl;
}

void Input()
{
	map = map.PasteAndFilter(!brick.GetShape(), brick.worldPosition.x, brick.worldPosition.y);
	//Moving tile left and right
	if ((GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState(0x41)))
	{
		if (controlTimer > 10) {
		controlTimer = 0;
		brick.worldPosition.x--;
		for (int j = 0; j < brick.GetSize(); j++) {
			for (int i = 0; i < brick.GetSize(); i++) {
				if (brick.GetShape()[j][i] == true && brick.worldPosition.x + j < 0) {
					brick.worldPosition.x++;
					break;
				}
			}
		}
		if (map.Overlaps(brick.GetShape(), brick.worldPosition.x, brick.worldPosition.y)) {
			brick.worldPosition.x++;
		}

		}
	}
	else if ((GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState(0x44)))
	{
	if (controlTimer > 10) {
		controlTimer = 8;
		brick.worldPosition.x++;
		for (int j = brick.GetSize() - 1; j >= 0; j--) {
			for (int i = 0; i < brick.GetSize(); i++) {
				if (brick.GetShape()[j][i] == true && brick.worldPosition.x + j + 1 > width) {
					brick.worldPosition.x--;
					break;
				}
			}
		}

		if (map.Overlaps(brick.GetShape(), brick.worldPosition.x, brick.worldPosition.y)) {
			brick.worldPosition.x--;
		}
	}
	}


	//Rotating
	else if ((GetAsyncKeyState(VK_UP) || GetAsyncKeyState(0x57)))
	{

		if (controlTimer > 10) {
			controlTimer = 0;
			brick.RotateCW();

			if (map.Overlaps(brick.GetShape(), brick.worldPosition.x, brick.worldPosition.y)) {
				brick.RotateCCW();
			}

			for (int j = brick.GetSize() - 1; j >= 0; j--) {
				for (int i = 0; i < brick.GetSize(); i++) {
					if (brick.GetShape()[j][i] == true && brick.worldPosition.x + j + 1 > width) {
						brick.worldPosition.x-= brick.worldPosition.x + j + 1 - width;
						break;
					}
				}
			}

			for (int j = 0; j < brick.GetSize(); j++) {
				for (int i = 0; i < brick.GetSize(); i++) {
					if (brick.GetShape()[j][i] == true && brick.worldPosition.x + j < 0) {
						brick.worldPosition.x += -brick.worldPosition.x + j;
						break;
					}
				}
			}

		}
	}
	else if ((GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState(0x45)))
	{
		timer += 9;
	}
	else {
		controlTimer = 20;
	}
}

void Logic()
{
	timer += 1;
	controlTimer += 1;



	if (timer >= 15) {
		timer -= 15;
		brick.worldPosition.y++;

		for (int j = brick.GetSize() - 1; j >= 0; j--) {
			for (int i = 0; i < brick.GetSize(); i++) {
				if (brick.GetShape()[i][j] == true && brick.worldPosition.y + j + 1 == height + 1) {
					brick.worldPosition.y--;
					map = map.PasteOrFilter(brick.GetShape(), brick.worldPosition.x, brick.worldPosition.y);
					prevMap = map;
					hit = true;
					return;
				}
			}
		}
		if (map.Overlaps(brick.GetShape(), brick.worldPosition.x, brick.worldPosition.y)) {

			brick.worldPosition.y--;
			map = map.PasteOrFilter(brick.GetShape(), brick.worldPosition.x, brick.worldPosition.y);
			prevMap = map;
			hit = true;
			return;
		}
	}


	//Smashing bricks
	int count =0;
	
	for (unsigned j = height - 1; j > 0; j--) {
		count = 0;
		for (unsigned i = 0; i <width; i++) {
			if (map[i][j] == false){
				break;
			}
			count++;
		}

		if (count == width) {
			Bitmap<width, height> temp(map);
			score += 40;
			map = map.Paste(temp, 0, 1,width,j);
			map = map.PasteOrFilter(brick.GetShape(), brick.worldPosition.x, brick.worldPosition.y);
			return;
		}
	}

	for (unsigned i = 0;i<width; i++) {
		if (map[i][2] == true) {
			gameOver = true;
		}
	}


	//Printing Brick on the map buffer
	map = map.PasteOrFilter(brick.GetShape(), brick.worldPosition.x, brick.worldPosition.y);
	

}
