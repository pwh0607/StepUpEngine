#ifndef VECTOR_H
#define VECTOR_H

class Vector
{
public:
	float x;
	float y;
	float z;
};

class Position : public Vector {
public:
	Position(float x, float y, float z);
};

class Rotation :public Vector {
public:
	Rotation(float x, float y, float z);
};

class Scale :public Vector {
public:
	Scale(float x, float y, float z);
};

#endif