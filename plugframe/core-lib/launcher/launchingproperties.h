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


#ifndef LAUNCHING_PROPERTIES
#define LAUNCHING_PROPERTIES

#include <QSettings>
#include <QVariant>
#include "pfcore-lib_export.h"

namespace elekdom
{
namespace plugframe
{
namespace core
{
namespace launcher
{

class PFCORELIB_EXPORT LaunchingProperties : public QSettings
{
    // Framework launching properties
    static const QString PF_GROUP;
    static const QString PF_FRAMEWORK_STARTLEVEL; // = "smf.framework.startlevel";

    // Qt StyleSheet for gui
    static const QString QT_GROUP;
    static const QString GUI_STYLESHEET_FILE;

public:
    LaunchingProperties(const QString& fileName);

public:
    bool hasStartlevel();
    QString getStartlevel();
    bool hasStyleSheet();
    QString getStyleSheetFile();
};

} //namespace launcher
} //namespace core
} //namespace plugframe
} //namespace elekdom

#endif // LAUNCHING_PROPERTIES

