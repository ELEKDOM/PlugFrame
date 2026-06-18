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
#ifndef GUIMAINMENUNAMES_H
#define GUIMAINMENUNAMES_H

#include <QString>
#include "pfgui-lib_export.h"

namespace plugframe
{
class PFGUILIB_EXPORT GuiMainMenuNames
{

public:
    GuiMainMenuNames();
    GuiMainMenuNames(QString functionalDomainName, QString controllerName, QString categoryName = {});

public:
    QString functionalDomainName() const {return m_functionalDomainName;}
    void functionalDomainName(const QString& name) {m_functionalDomainName = name;}
    QString categoryName() const {return m_categoryName;}
    void categoryName(const QString& name) {m_categoryName = name;}
    QString controllerName() const {return m_controllerName;}
    void controllerName(const QString& name) {m_controllerName = name;}
    void reset();

private:
    QString m_functionalDomainName;
    QString m_categoryName;
    QString m_controllerName;
};
}//namespace plugframe
#endif // GUIMAINMENUNAMES_H