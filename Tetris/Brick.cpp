#include "Brick.h"
#include <memory>
#include<iostream>
#include<Windows.h>


Brick::Brick()
{
	rotationMatrix[0][0] = 1; rotationMatrix[0][1] = 0;
	rotationMatrix[1][0] = 0; rotationMatrix[1][1] = 1;
	offset = { 0,0 };
}

Brick::Brick(Type type)
{
	this->type = type;
	shape = Bitmap4x4(false);

	//		  x, y
	switch (type) {
	case Type::O:
		shape[0][0] = true;
		shape[0][1] = true;
		shape[1][0] = true;
		shape[1][1] = true;
		break;
	case Type::I:
		shape[0][1] = true;
		shape[1][1] = true;
		shape[2][1] = true;
		shape[3][1] = true;
		break;
	case Type::L:
		shape[2][0] = true;
		shape[0][1] = true;
		shape[1][1] = true;
		shape[2][1] = true;
		break;
	case Type::J:
		shape[0][0] = true;
		shape[0][1] = true;
		shape[1][1] = true;
		shape[2][1] = true;
		break;
	case Type::Z:
		shape[0][0] = true;
		shape[1][0] = true;
		shape[1][1] = true;
		shape[2][1] = true;
		break;
	case Type::S:
		shape[2][0] = true;
		shape[1][0] = true;
		shape[1][1] = true;
		shape[0][1] = true;
		break;
	case Type::T:
		shape[1][0] = true;
		shape[0][1] = true;
		shape[1][1] = true;
		shape[2][1] = true;
		break;
	case Type::G:
		shape[1][0] = true;
		shape[2][0] = true;
		shape[0][1] = true;
		shape[1][1] = true;
		shape[2][1] = true;
		break;
	case Type::BL:
		shape[0][2] = true;
		shape[0][1] = true;
		shape[0][0] = true;
		shape[1][1] = true;
		shape[2][1] = true;
		break;
	case Type::BG:
		shape[0][1] = true;
		shape[0][2] = true;
		shape[1][0] = true;
		shape[1][1] = true;
		shape[1][2] = true;
		break;
	case Type::H:
		shape[0][1] = true;
		shape[0][2] = true;
		shape[0][0] = true;
		shape[1][0] = true;
		shape[1][2] = true;
		break;
	case Type::D:
	case Type::D2:
		shape[0][0] = true;
		break;
	case Type::i:
		shape[1][1] = true;
		shape[1][2] = true;
		shape[1][0] = true;
		break;
	}

	rotationMatrix[0][0] = 1; rotationMatrix[0][1] = 0;
	rotationMatrix[1][0] = 0; rotationMatrix[1][1] = 1;
	offset = { 0,0 };
	rotation = 0;

}


int Brick::GetSize()
{
	switch (type) {
	case Type::O:
		return 2;
		break;
	case Type::I:
		return 4;
		break;
	case Type::L:
		return 3;
		break;
	case Type::J:
		return 3;
		break;
	case Type::Z:
		return 3;
		break;
	case Type::S:
		return 3;
		break;
	case Type::T:
		return 3;
		break;
	case Type::G:
		return 3;
		break;
	case Type::BL:
		return 3;
		break;
	case Type::BG:
		return 3;
		break;
	case Type::H:
		return 3;
		break;
	case Type::D:
	case Type::D2:
		return 1;
		break;
	case Type::i:
		return 3;
		break;
	}
}

void Brick::RotateCW()
{
	rotation++;
	if (rotation > 3)
		rotation = 0;

	Rotate();
}

void Brick::RotateCCW()
{
	rotation--;
	if (rotation < 0)
		rotation = 3;

	Rotate();
}

void Brick::Rotate()
{

	switch (rotation) {
	case 0:
		rotationMatrix[0][0] = 1; rotationMatrix[0][1] = 0;
		rotationMatrix[1][0] = 0; rotationMatrix[1][1] = 1;
		offset = { 0,0 };
		break;
	case 1:
		rotationMatrix[0][0] = 0; rotationMatrix[0][1] = -1;
		rotationMatrix[1][0] = 1; rotationMatrix[1][1] = 0;
		offset = { 1,0 };
		break;
	case 2:
		rotationMatrix[0][0] = -1; rotationMatrix[0][1] = 0;
		rotationMatrix[1][0] = 0; rotationMatrix[1][1] = -1;
		offset = { 1,1 };
		break;
	case 3:
		rotationMatrix[0][0] = 0; rotationMatrix[0][1] = 1;
		rotationMatrix[1][0] = -1; rotationMatrix[1][1] = 0;
		offset = { 0,1 };
		break;
	}
}

Bitmap4x4 Brick::GetShape()
{
	Bitmap4x4 rotatedShape = Bitmap4x4(false);

	Vector2i vt;
	for (int i = 0; i < GetSize(); i++) {
		for (int j = 0; j < GetSize(); j++) {
			
			vt.x = rotationMatrix[0][0] * i + rotationMatrix[0][1] * j;
			vt.y = rotationMatrix[1][0] * i + rotationMatrix[1][1] * j;

			rotatedShape[vt.x + (GetSize()-1)* offset.x][vt.y+(GetSize() -1)* offset.y] = shape[i][j];
			
		}

	}

	return rotatedShape;
}
