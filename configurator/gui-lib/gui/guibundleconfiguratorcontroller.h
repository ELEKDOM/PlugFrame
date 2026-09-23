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
#ifndef GUIBUNDLECONFIGURATORCONTROLLER_H
#define GUIBUNDLECONFIGURATORCONTROLLER_H

#include "guifileconfiguratorcontroller.h"

namespace configurator
{
class CONFIGURATORLIB_EXPORT GuiBundleConfiguratorController : public GuiFileConfiguratorController
{
public:
    GuiBundleConfiguratorController(const QString& associatedBundleName,QObject *parent = nullptr);
    ~GuiBundleConfiguratorController() override;

public:
    QStringList getBundleConfFileList(const QString& confFilesRepository,const QString& bundleName);
    bool hasBundleConfFiles(const QString& bundleName);
    bool editBundleConfFiles(const QString &projectSourcePath,
                             const QString &projectName,
                             const QString &applicationName,
                             const QString &bundleName,
                             const QString &confFilesRepository);
private:
    QString m_associatedBundleName;
};
using QspGuiBundleConfiguratorController = QSharedPointer<GuiBundleConfiguratorController>;
}//namespace configurator
#endif // GUIBUNDLECONFIGURATORCONTROLLER_H
