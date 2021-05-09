#include "structs.h"

QString infoVector(Vector v, int precision)
{
    return QString("(%1, %2, %3)").arg(QString::number(v.x,'f', precision)).arg(QString::number(v.y, 'f', precision)).arg(QString::number(v.z, 'f', precision));
}

double dotProduct(Vector v1, Vector v2)
{
    return ((v1.x + v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

double norm(Vector v)
{
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

QString infoCoefPOM(CoeficientsPOM coefPOM)
{
	QString difuse = QString("red:%1, green:%2, blue:%3").arg(coefPOM.difuse.red).arg(coefPOM.difuse.green).arg(coefPOM.difuse.blue);
	QString ambient = QString("red:%1, green:%2, blue:%3\nambient color: red:%4, green: %5, blue:%6").arg(coefPOM.ambient.red).arg(coefPOM.ambient.green).arg(coefPOM.ambient.blue).arg(coefPOM.ambient.ambientColor.red()).arg(coefPOM.ambient.ambientColor.green()).arg(coefPOM.ambient.ambientColor.blue());
	QString specular = QString("red:%1, green:%2, blue:%3\nspecular sharpness:%4").arg(coefPOM.specular.red).arg(coefPOM.specular.green).arg(coefPOM.specular.blue).arg(coefPOM.specular.specularSharpness);

	return QString("Difuse:" + difuse + "\nAmbient" + ambient + "\nSpecular:" + specular + "\n");
}

void Vector::operator*=(double scalar)
{
	x = scalar * x;
	y = scalar * y;
	z = scalar * z;
}

void Vector::operator+=(const Vector v)
{
	x += v.x;
	y += v.y;
	z += v.z;
}

void Vector::operator-=(const Vector v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
}

Vector Vector::operator+(const Vector v)
{
	return Vector{x + v.x, y + v.y, z + v.z};
}

Vector Vector::operator-(const Vector v)
{
	return Vector{ x - v.x, y - v.y, z - v.z };
}

Vector Vector::operator*(double scalar)
{
	return Vector{ x * scalar, y * scalar, z * scalar };
}

Vector Vector::operator/(double scalar)
{
	return Vector{ x / scalar, y / scalar, z / scalar };
}
