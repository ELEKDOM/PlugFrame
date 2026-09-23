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
#ifndef GUIEDITABLEWIDGET_H
#define GUIEDITABLEWIDGET_H

#include <QWidget>
#include "configurator-lib_export.h"

namespace configurator
{
class CONFIGURATORLIB_EXPORT GuiEditableWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GuiEditableWidget(QWidget *parent = nullptr);

public:
    virtual void edit(const QString& filePath) =0;

signals:
    void isDirty();
    void isClean();
};
}//namespace configurator
#endif // GUIEDITABLEWIDGET_H
