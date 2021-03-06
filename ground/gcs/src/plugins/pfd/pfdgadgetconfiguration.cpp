/**
 ******************************************************************************
 *
 * @file       pfdgadgetconfiguration.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 *
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup PFDPlugin Primary Flight Display Plugin
 * @{
 * @brief The Primary Flight Display Gadget
 *****************************************************************************/
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "pfdgadgetconfiguration.h"
#include "utils/pathutils.h"

/**
 * Loads a saved configuration or defaults if non exist.
 *
 */
PFDGadgetConfiguration::PFDGadgetConfiguration(QString classId, QSettings* qSettings, QObject *parent) :
    IUAVGadgetConfiguration(classId, parent),
    m_defaultDial("Unknown"),
    beSmooth(true)
{
    //if a saved configuration exists load it
    if(qSettings != 0) {
        QString dialFile = qSettings->value("dialFile").toString();
        useOpenGLFlag = qSettings->value("useOpenGLFlag").toBool();
        hqFonts = qSettings->value("hqFonts").toBool();
        beSmooth = qSettings->value("beSmooth").toBool();
        m_defaultDial=Utils::PathUtils().InsertDataPath(dialFile);
    }
}

/**
 * Clones a configuration.
 *
 */
IUAVGadgetConfiguration *PFDGadgetConfiguration::clone()
{
    PFDGadgetConfiguration *m = new PFDGadgetConfiguration(this->classId());
    m->m_defaultDial=m_defaultDial;
    m->useOpenGLFlag = useOpenGLFlag;
    m->hqFonts = hqFonts;
    m->beSmooth = beSmooth;
    return m;
}

/**
 * Saves a configuration.
 *
 */
void PFDGadgetConfiguration::saveConfig(QSettings* qSettings) const {
    QString dialFile = Utils::PathUtils().RemoveDataPath(m_defaultDial);
    qSettings->setValue("dialFile", dialFile);
    qSettings->setValue("useOpenGLFlag", useOpenGLFlag);
    qSettings->setValue("hqFonts", hqFonts);
    qSettings->setValue("beSmooth", beSmooth);
}
