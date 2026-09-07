// Copyright (C) 2026 ELEKDOM Christophe Mars c.mars@elekdom.fr
//
// This file is part of PlugFrame.
//
// PlugFrame is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// PlugFrame is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with PlugFrame. If not, see <https://www.gnu.org/licenses/>.
//
#include <QByteArray>
#include <QSaveFile>
#include "xmleditabledocument.h"

plugframe::XmlEditableDocument::XmlEditableDocument(XmlBrowserHook &browserHook,
                                                    const QString &xmlFileName) :
    plugframe::XmlDocument{browserHook},
    m_xmlFileName{xmlFileName}
{

}

plugframe::XmlEditableDocument::~XmlEditableDocument()
{

}

void plugframe::XmlEditableDocument::init()
{
    createNewDoc();
    writeIntoFile();
}

void plugframe::XmlEditableDocument::open()
{
    load(fileName());
    browse();
}

void plugframe::XmlEditableDocument::writeIntoFile()
{
    QByteArray outData{toByteArray()};
    QSaveFile outFile{fileName()};
    bool ok;

    ok = outFile.open(QIODevice::WriteOnly);
    if (ok)
    {
        ok = outFile.write(outData) == outData.size();
    }
    if (ok)
    {
        outFile.commit();
    }
}
