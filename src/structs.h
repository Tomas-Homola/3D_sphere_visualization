#pragma once
#include "qcolor.h"

struct Vector
{
	double x;
	double y;
	double z;

	void operator*=(double scalar);
	void operator+=(const Vector v);
	void operator-=(const Vector v);

	Vector operator+(const Vector v);
	Vector operator-(const Vector v);
	Vector operator*(double scalar);
	Vector operator/(double scalar);
};

QString infoVector(Vector v, int precision = 6);
double dotProduct(Vector v1, Vector v2);
double norm(Vector v);

struct PointLightSource
{
	double x;
	double y;
	double z;

	QColor lightColor;
};

struct DiffuseComponent
{
	double red;
	double green;
	double blue;
};

struct SpecularComponent
{
	double red;
	double green;
	double blue;

	double specularSharpness;
};

struct AmbientComponent
{
	double red;
	double green;
	double blue;

	QColor ambientColor;
};

struct CoeficientsPOM
{
	DiffuseComponent difuse;
	AmbientComponent ambient;
	SpecularComponent specular;
};

QString infoCoefPOM(CoeficientsPOM coefPOM);