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


#include <QCoreApplication>
#include <QPluginLoader>
#include "logger/pflog.h"
#include "launcher/bundlesstore.h"
#include "launcher/location.h"
#include "plugin/bundleinterface.h"
#include "plugin/frameworkinterface.h"

using namespace elekdom::plugframe::core::launcher;
using namespace elekdom::plugframe;

BundlesStore::BundlesStore(QspLocation location):
    m_location(location)
{
}

framework::plugin::FrameworkInterface* BundlesStore::loadFrameworkPlugin(QString caller)
{
    framework::plugin::FrameworkInterface* ret = nullptr;
    core::plugin::BundleInterface* bundleItf;

    QDir smfFrameworkDir;
    QStringList files;
    QString fileName;

    //pfDebug3(caller) << "->BundlesStore::loadFrameworkPlugin";

    if (m_location->cdFrameworkBundleDir(smfFrameworkDir))
    {
        //pfInfo8(caller) << QCoreApplication::tr("Répertoire du bundle système [ %1 ]").arg(smfFrameworkDir.absolutePath());

        files = smfFrameworkDir.entryList(QDir::Files);
        if (files.size() > 0)
        {
            fileName = files[0];
            //pfDebug4(caller) << "Bundle framework filename: " << fileName;
            //pfDebug4(caller) << "Bundle framework full filename: " << smfFrameworkDir.absoluteFilePath(fileName);

            QPluginLoader pluginLoader(smfFrameworkDir.absoluteFilePath(fileName));
            QObject *plugin = pluginLoader.instance();
            if (plugin)
            {
                pfDebug5(caller) << QCoreApplication::tr("Framwork loaded %1").arg(files[0]);
                ret = qobject_cast<framework::plugin::FrameworkInterface*>(plugin);
                bundleItf = ret->getBundleInterface();
                bundleItf->setFileName(fileName);
                bundleItf->setAbsolutePath(smfFrameworkDir.absolutePath());
                bundleItf->setMetaData(pluginLoader.metaData());
                bundleItf->setQplugin(plugin);
            }
            else
            {
                pfDebug4(caller) << pluginLoader.errorString();
            }
        }
    }
    else
    {
        pfWarning1(caller) << "No bundle framework directory! ";
    }

   // pfDebug3(caller) << "<-BundlesStore::loadFrameworkPlugin " << ret;
    return ret;
}

/**
 * @brief BundlesStore::loadPlugins
 * @param bundleList
 * @description load all plugins from the plugin subdirectory.
 * plugins directories are located into the "bundles directory".
 * After loading, a bundle is initialized
 */
void BundlesStore::loadPlugins(QString caller, plugin::BundleList& bundleList)
{
    QDir BundlesDir;

    if (m_location->cdBundlesDir(BundlesDir))
    {
        QPluginLoader pluginLoader;

        for (auto&& subdirName : BundlesDir.entryList(QDir::Dirs|QDir::NoDotAndDotDot))
        {
            if (m_location->isBundleSubDir(subdirName))
            {
                QDir BundleDir(BundlesDir.absoluteFilePath(subdirName));
                QStringList files, namesFilter;
                QObject *plugin {};

                //             linux      win        macx
                namesFilter << "*.so" << "*.dll" << "*.dylib";
                files = BundleDir.entryList(namesFilter, QDir::Files);

                if (files.size() == 1)
                {
                    QString fileName{BundleDir.absoluteFilePath(files[0])};
                    //pfDebug4(caller) << QCoreApplication::tr("Plugin à charger [ %1 ]").arg(files[0]);
                    pluginLoader.setFileName(fileName);
                    plugin = pluginLoader.instance();
                }

                if (plugin)
                {
                    plugframe::core::plugin::BundleInterface* bundle = qobject_cast<plugframe::core::plugin::BundleInterface*>(plugin);
                    if (bundle)
                    {
                        pfDebug5(caller) << QCoreApplication::tr("Plugin [ %1 ] chargé").arg(files[0]);

                        // hold bundle lib name and location
                        bundle->setFileName(files[0]);
                        bundle->setAbsolutePath(BundleDir.absolutePath());

                        // hold json metadata
                        bundle->setMetaData(pluginLoader.metaData());

                        // plugin addr
                        bundle->setQplugin(plugin);

                        // Initialize the new loaded bundle
                        bundle->init();

                        // New bundle to add into the framework
                        bundleList << bundle;
                    }
                }
                else
                {
                    pfWarning8(caller) << QCoreApplication::tr("%1, Err : ").arg(files[0]) << pluginLoader.errorString();
                }
            } // if (m_location->isBundleSubDir(subdirName))
        } // for (auto&& subdirName : BundlesDir.entryList(QDir::Dirs|QDir::NoDotAndDotDot))
    }
}
