#include "SurfaceRepresentation.h"

// Vertex stuff
Vertex::Vertex(double x, double y, double z, int index)
{
	this->x = x;
	this->y = y;
	this->z = z;
	
	this->index = index;

	edge = nullptr;
}
void Vertex::setCoordinates(double newX, double newY, double newZ)
{
	x = newX;
	y = newY;
	z = newZ;
}
void Vertex::setVertexColor(double red, double green, double blue)
{
	if ((red - 1.0) > 0.000001)
		vertexColor.setRedF(1.0);
	else if ((red - 1.0) < 0.000001)
		vertexColor.setRedF(0.0);
	else
		vertexColor.setRedF(red);

	if ((green - 1.0) > 0.000001)
		vertexColor.setGreenF(1.0);
	else if ((green - 1.0) < 0.000001)
		vertexColor.setGreenF(0.0);
	else
		vertexColor.setGreenF(red);

	if ((blue - 1.0) > 0.000001)
		vertexColor.setBlueF(1.0);
	else if ((blue - 1.0) < 0.000001)
		vertexColor.setBlueF(0.0);
	else
		vertexColor.setBlueF(red);
}
void Vertex::setVertexColor(int red, int green, int blue)
{
	if (red > 255)
		vertexColor.setRed(255);
	else if (red < 0)
		vertexColor.setRed(0);
	else
		vertexColor.setRed(red);

	if (green > 255)
		vertexColor.setGreen(255);
	else if (green < 0)
		vertexColor.setGreen(0);
	else
		vertexColor.setGreen(green);

	if (blue > 255)
		vertexColor.setBlue(255);
	else if (blue < 0)
		vertexColor.setBlue(0);
	else
		vertexColor.setBlue(blue);
}
QString Vertex::vertexInfo(int precision)
{
	return QString("%1 %2 %3").arg(QString::number(x, 'f', precision)).arg(QString::number(y, 'f', precision)).arg(QString::number(z, 'f', precision));
}
bool Vertex::operator==(Vertex v)
{
	double x = this->x - v.x;
	double y = this->y - v.y;
	double z = this->z - v.z;

	double distance = sqrt(x * x + y * y + z * z);
	
	if (distance < 0.000001)
		return true;
	else
		return false;
}
void Vertex::projectToUnitSphere()
{
	double d = getDistanceFromOrigin();

	if (qAbs(1.0 - d) > 0.000001) // ak by bola vzdialenost bodu mimo jednotkovej sfery
	{
		x = x / d;
		y = y / d;
		z = z / d;
	}
}

// H_edge stuff
H_edge::H_edge(Vertex* vert_origin, Face* face, H_edge* edge_prev, H_edge* edge_next, H_edge* pair)
{
	this->vert_origin = vert_origin;
	this->face = face;
	this->edge_prev = edge_prev;
	this->edge_next = edge_next;
	this->pair = pair;
}
void H_edge::setAll(Vertex* vert_origin, Face* face, H_edge* edge_prev, H_edge* edge_next, H_edge* pair)
{
	this->vert_origin = vert_origin;
	this->vert_end = edge_next->getVertexOrigin();
	this->face = face;
	this->edge_prev = edge_prev;
	this->edge_next = edge_next;
	this->pair = pair;
}
bool H_edge::hasPair()
{
	if (pair == nullptr)
		return false;
	else
		return true;
}
QString H_edge::edgeVerticesInfo()
{
	return QString("%1 %2").arg(QString::number(vert_origin->getIndex())).arg(QString::number(edge_next->vert_origin->getIndex()));
}

// Octahedron stuff
Octahedron::~Octahedron()
{
	for (int i = 0; i < vertices.size(); i++)
		delete vertices[i];
	for (int i = 0; i < edges.size(); i++)
		delete edges[i];
	for (int i = 0; i < faces.size(); i++)
		delete faces[i];

	vertices.clear(); edges.clear(); faces.clear();
}
bool Octahedron::isEmpty()
{
	if (vertices.isEmpty() && edges.isEmpty() && faces.isEmpty())
		return true;
	else
		return false;
}
void Octahedron::clear()
{
	if (!vertices.isEmpty())
		for (int i = 0; i < vertices.size(); i++)
			delete vertices[i];
	
	if (!edges.isEmpty())
		for (int i = 0; i < edges.size(); i++)
			delete edges[i];
	
	if (!faces.isEmpty())
		for (int i = 0; i < faces.size(); i++)
			delete faces[i];

	vertices.clear(); edges.clear(); faces.clear();
}
void Octahedron::calculateNormals()
{
	Vertex* vertex1 = nullptr, * vertex2 = nullptr, * vertex3 = nullptr;
	QVector3D faceNormal(0.0, 0.0, 0.0);

	// normlay vo vrcholoch, tie nedelim normou, lebo uz su na jedntkovej sfere -> maju normu == 1
	for (int i = 0; i < vertices.size(); i++)
	{
		vertices[i]->setVertexNormal(vertices[i]->getX(), vertices[i]->getY(), vertices[i]->getZ());
	}

	// nomraly pre plosky
	for (int i = 0; i < faces.size(); i++)
	{
		vertex1 = faces[i]->getEdge()->getVertexOrigin();
		vertex2 = faces[i]->getEdge()->getEdgeNext()->getVertexOrigin();
		vertex3 = faces[i]->getEdge()->getEdgePrevious()->getVertexOrigin();

		faceNormal = (vertex1->getVertexNormal() + vertex2->getVertexNormal() + vertex3->getVertexNormal()) / 3.0;
		faceNormal.normalize(); // normalizovanie vektoru normaly na plosku

		faces[i]->setFaceNormal(faceNormal);
	}
}
QString Face::faceVerticesInfo()
{
	// edge, edge_next, edge_prev
	return QString("%1 %2 %3").arg(QString::number(edge->getVertexOrigin()->getIndex())).arg(QString::number(edge->getEdgeNext()->getVertexOrigin()->getIndex())).arg(QString::number(edge->getEdgePrevious()->getVertexOrigin()->getIndex()));
}
void Face::setFaceColor(double red, double green, double blue)
{
	if ((red - 1.0) > 0.000001)
		faceColor.setRedF(1.0);
	else if ((red - 1.0) < 0.000001)
		faceColor.setRedF(0.0);
	else
		faceColor.setRedF(red);

	if ((green - 1.0) > 0.000001)
		faceColor.setGreenF(1.0);
	else if ((green - 1.0) < 0.000001)
		faceColor.setGreenF(0.0);
	else
		faceColor.setGreenF(red);

	if ((blue - 1.0) > 0.000001)
		faceColor.setBlueF(1.0);
	else if ((blue - 1.0) < 0.000001)
		faceColor.setBlueF(0.0);
	else
		faceColor.setBlueF(red);
}
void Face::setFaceColor(int red, int green, int blue)
{
	if (red > 255)
		faceColor.setRed(255);
	else if (red < 0)
		faceColor.setRed(0);
	else
		faceColor.setRed(red);

	if (green > 255)
		faceColor.setGreen(255);
	else if (green < 0)
		faceColor.setGreen(0);
	else
		faceColor.setGreen(green);

	if (blue > 255)
		faceColor.setBlue(255);
	else if (blue < 0)
		faceColor.setBlue(0);
	else
		faceColor.setBlue(blue);
}
