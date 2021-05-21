#pragma once
#include "qcolor.h"

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