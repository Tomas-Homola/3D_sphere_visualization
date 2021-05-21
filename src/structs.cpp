#include "structs.h"

QString infoCoefPOM(CoeficientsPOM coefPOM)
{
	QString difuse = QString("red:%1, green:%2, blue:%3").arg(coefPOM.difuse.red).arg(coefPOM.difuse.green).arg(coefPOM.difuse.blue);
	QString ambient = QString("red:%1, green:%2, blue:%3\nambient color: red:%4, green: %5, blue:%6").arg(coefPOM.ambient.red).arg(coefPOM.ambient.green).arg(coefPOM.ambient.blue).arg(coefPOM.ambient.ambientColor.red()).arg(coefPOM.ambient.ambientColor.green()).arg(coefPOM.ambient.ambientColor.blue());
	QString specular = QString("red:%1, green:%2, blue:%3\nspecular sharpness:%4").arg(coefPOM.specular.red).arg(coefPOM.specular.green).arg(coefPOM.specular.blue).arg(coefPOM.specular.specularSharpness);

	return QString("Difuse:" + difuse + "\nAmbient" + ambient + "\nSpecular:" + specular + "\n");
}