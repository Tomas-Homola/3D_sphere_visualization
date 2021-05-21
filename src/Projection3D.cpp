#include "Projection3D.h"

void Projection3D::recalculateVector_n()
{
	n.setX(qSin(zenit) * qCos(azimut));
	n.setY(qSin(zenit) * qSin(azimut));
	n.setZ(qCos(zenit));
}

void Projection3D::recalculateVector_u()
{
	u.setX(qSin(zenit + M_PI_2) * qCos(azimut));
	u.setY(qSin(zenit + M_PI_2) * qSin(azimut));
	u.setZ(qCos(zenit + M_PI_2));
}

void Projection3D::recalculateVector_v()
{
	v = QVector3D::crossProduct(n, u);
	/*v.x = n.z * u.y - n.y * u.z;
	v.y = n.x * u.z - n.z * u.x;
	v.z = n.y * u.x - n.x * u.y;*/
}

Projection3D::Projection3D()
{
	recalculateVectors();
}

QString Projection3D::getCoordinatesVector_n(int precision)
{
	return QString("%1 %2 %3").arg(QString::number(n.x(), 'f', precision)).arg(QString::number(n.y(), 'f', precision)).arg(QString::number(n.z(), 'f', precision));
}

QString Projection3D::getCoordinatesVector_u(int precision)
{
	return QString("%1 %2 %3").arg(QString::number(u.x(), 'f', precision)).arg(QString::number(u.y(), 'f', precision)).arg(QString::number(u.z(), 'f', precision));
}

QString Projection3D::getCoordinatesVector_v(int precision)
{
	return QString("%1 %2 %3").arg(QString::number(v.x(), 'f', precision)).arg(QString::number(v.y(), 'f', precision)).arg(QString::number(v.z(), 'f', precision));
}

