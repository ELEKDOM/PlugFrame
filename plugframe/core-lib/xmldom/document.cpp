// Copyright (C) 2025 ELEKDOM Christophe Mars c.mars@elekdom.fr
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


#include <QFile>
#include "document.h"

using namespace elekdom::plugframe::core::xmldom;

Document::Document(BrowserHook &browserHook):
    m_browserHook{browserHook},
    m_fileLoaded{false}
{

}

Document::~Document()
{

}

void Document::load(const QString &xmlFileName)
{
    QFile file(xmlFileName);

    m_fileLoaded = false;
    if (file.open(QIODevice::ReadOnly))
    {
        m_fileLoaded = setContent(&file);
        file.close();
    }
}

qint16 Document::confId()
{
    qint16 ret{-1};

    if (fileLoaded())
    {
        QDomElement docElem = documentElement();
        QString elemName{docElem.tagName()};
        QString rootName{rootNodeName()};

        if (rootName == elemName)
        {
            QString attrVal{docElem.attribute(confidAttr())};

            if (!attrVal.isEmpty())
            {
                ret = attrVal.toInt();
            }
        }
    }

    return ret;
}

bool Document::browse()
{
    bool ret{false};

    browserHook().browseBegin();

    if (m_fileLoaded)
    {
        ret = _browse();
    }

    browserHook().browseEnd();

    return ret;
}
