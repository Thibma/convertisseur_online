#include "conversion.h"

Conversion::Conversion(QVector<Drone *> listDrone)
{
    drones = listDrone;
    fileName = "conversion.kml";

    miseEnPage();
    save();

}

void Conversion::miseEnPage()
{
    /* En-tête */
    file.append("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                "<kml xmlns=\"http://www.opengis.net/kml/2.2\" xmlns:gx=\"http://www.google.com/kml/ext/2.2\" xmlns:kml=\"http://www.opengis.net/kml/2.2\" xmlns:atom=\"http://www.w3.org/2005/Atom\">\n"
                "<Document>\n"
                "  <name>");
    file.append(fileName);
    file.append("</name>\n");

    /* Création des styles */
    /*for(int i = 0; i < drones.size(); i++) {
        file.append("  <Style id=\"");
        file.append(QString::number(i));
        file.append("\">\n"
                         "      <LineStyle>\n"
                         "          <color>");
        int opacite = (255 * m_customDrones[i].opacite) / 100;
        file.append(QString::number(opacite, 16));
        file.append(m_color_drones[m_customDrones[i].indexCouleur]);
        file.append("</color>\n"
                         "          <width>");
        file.append(QString::number(m_customDrones[i].largeur));
        file.append("</width>\n"
                         "      </LineStyle>\n"
                         "  </Style>\n");
    }*/
    file.append("  <Style id=\"Depart\">\n"
                "      <IconStyle>\n"
                "          <scale>1</scale>\n"
                "      </IconStyle>\n"
                "      <LabelStyle>\n"
                "          <scale>1</scale>\n"
                "      </LabelStyle>\n"
                "  </Style>\n"
                "  <Style id=\"Arrivee\">\n"
                "      <IconStyle>\n"
                "          <scale>1</scale>\n"
                "      </IconStyle>\n"
                "      <LabelStyle>\n"
                "          <scale>1</scale>\n"
                "      </LabelStyle>\n"
                "  </Style>\n");

    /* Ajout des données */
    for (int j = 0; j < drones.size(); j++)
    {
        file.append("  <Folder>\n"
                    "      <name>");
        file.append(drones[j]->getModel());
        file.append(" - ");
        file.append(drones[j]->getSn());

        /* Premier point */
        file.append("</name>\n"
                    "      <Placemark>\n"
                    "          <name>Premier point"
                    "</name>\n");
        file.append("          <description>");
        file.append(drones[j]->getFirstDate().time().toString());
        file.append("          </description>\n");
        file.append("          <Point>\n"
                    "              <altitudeMode>absolute</altitudeMode>\n"
                    "              <coordinates>");
        file.append(QString::number(drones[j]->getFirstCoordinates().longitude()));
        file.append(",");
        file.append(QString::number(drones[j]->getFirstCoordinates().latitude()));
        file.append(",");
        file.append(QString::number(drones[j]->getFirstCoordinates().altitude()));
        file.append("</coordinates>\n"
                    "          </Point>\n"
                    "      </Placemark>\n");

        /* Tracé du drone */
        file.append("      <Placemark>\n"
                    "          <name>");
        file.append("Tracé du " + drones[j]->getModel());
        file.append("</name>\n");
        file.append("          <styleUrl>#");
        file.append(QString::number(j));
        file.append("</styleUrl>\n"
                    "          <LineString>\n"
                    "              <altitudeMode>absolute</altitudeMode>\n"
                    "              <coordinates>\n");
        for (int i = 0; i < drones[j]->getDroneValue().size(); i++)
        {
            file.append(QString::number(drones[j]->getDroneValue()[i].getCoordinates().longitude()));
            file.append(",");
            file.append(QString::number(drones[j]->getDroneValue()[i].getCoordinates().latitude()));
            file.append(",");
            file.append(QString::number(drones[j]->getDroneValue()[i].getCoordinates().altitude()));
            file.append(" ");
        }
        file.append("\n"
                    "              </coordinates>\n"
                    "          </LineString>\n"
                    "      </Placemark>\n");


        /* Dernier point */
        file.append("      <Placemark>\n"
                    "          <name>Dernier point</name>\n"
                    "          <description>");
        file.append(drones[j]->getLastDate().time().toString());
        file.append("</description>\n"
                    "          <Point>\n"
                    "              <altitudeMode>absolute</altitudeMode>\n"
                    "              <coordinates>");
        file.append(QString::number(drones[j]->getLastCoordinates().longitude()));
        file.append(",");
        file.append(QString::number(drones[j]->getLastCoordinates().latitude()));
        file.append(",");
        file.append(QString::number(drones[j]->getLastCoordinates().altitude()));
        file.append("</coordinates>\n"
                    "          </Point>\n"
                    "      </Placemark>\n");


        file.append("  </Folder>\n");
    }
    /* Pied du fichier */
    file.append("</Document>\n"
                "</kml>");
}

void Conversion::save()
{
    /* Ouverture de la boîte de dialogue pour sauvegarder */
        QString urlFileName = QFileDialog::getSaveFileName(nullptr, QObject::tr("Sauvegarde du fichier KML"), QDir::homePath() + "/Documents/" + fileName, QObject::tr("Google Earth (*.kml)"));
        if (urlFileName.isEmpty())
            return;
        else
        {
            QFile file(urlFileName);

            /* Test du fichier */
            if (!file.open(QIODevice::WriteOnly))
            {
                QMessageBox erreur;
                erreur.setIcon(QMessageBox::Warning);
                erreur.setWindowTitle("Erreur fichier");
                erreur.setText("Impossible d'enregistrer le fichier.");
                erreur.setStandardButtons(QMessageBox::Ok);
                erreur.exec();
                return;
            }

            /* Ecriture dans le fichier */
            QTextStream out(&file);
            out << Conversion::file;
        }
}
