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

#ifndef XMLDOCUMENT_H
#define XMLDOCUMENT_H

#include <QDomDocument>
#include <QString>
#include "xmlbrowserhook.h"
#include "pfcore-lib_export.h"

namespace plugframe
{
class PFCORELIB_EXPORT Document : public QDomDocument
{
protected:
    static QString confidAttr() {return QStringLiteral("conf-id");}

public:
    Document(XmlBrowserHook& browserHook);
    virtual ~Document();

public:
    void load(const QString& xmlFileName);
    bool fileLoaded() {return m_fileLoaded;}
    qint16 confId();
    bool browse();

protected:
    XmlBrowserHook& browserHook() {return m_browserHook;}
    virtual QString rootNodeName() = 0;
    virtual bool _browse() = 0;

private:
    XmlBrowserHook& m_browserHook;
    bool            m_fileLoaded;
};
}//namespace plugframe

#endif // XMLDOCUMENT_H
