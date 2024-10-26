#pragma once

#include"Bitmap.h"



class Brick
{
public:
	enum class Type {
		O, //Smashboy - Square
		I, //Hero - Line
		L, //Orange Ricky - L Brick
		J, //Blue Ricky - J Brick
		Z, //Cleveland Z - Z Brick
		S, //Road Island Z - S Brick
		T, //Teewee - T Brick
		G,
		BL,
		BG,
		H,
		D, D2,
		i,
	};

	Brick();
	Brick(Type type);


	Vector2i worldPosition;
	int GetSize();
	void RotateCW();
	void RotateCCW();
	Bitmap4x4 GetShape();
	
private:
	void Rotate();
	short rotation;
	short rotationMatrix[2][2];
	Vector2i offset;
	Type type;
	Bitmap4x4 shape;

	

};

