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
#include <QStringList>
#include "logger/pflog.h"
#include "launcher.h"
#include "launchingproperties.h"
#include "bundlesstore.h"
#include "factory/corefactory.h"
#include "plugin/bundleinterface.h"
#include "plugin/frameworkinterface.h"

using namespace elekdom::plugframe::core::launcher;

Launcher::Launcher()
{
}

Launcher::~Launcher()
{
     //pfDebug2("Launcher") << "->SmfLauncher::~SmfLauncher";

     // ...

     // the framework is a Qt plugin, so it has not be allocated with new operator !
     m_newFwk = nullptr;

     //pfDebug2("Launcher") << "<-SmfLauncher::~SmfLauncher";
}

int Launcher::exec(int argc, char *argv[])
{
    int ret;

    // creates the QApp according to the type of application (console, gui or qml)
    createApp(argc, argv);

    // creates and keeps the core factory
    setFactory(createFactory());

    // creates the platform location manager
    //pfInfo8(QString("Launcher")) << tr("Répertoire de la plateforme [ %1 ]").arg(QCoreApplication::applicationDirPath());
    m_spSmfLocation = m_spSmfCoreFactory->createLocation(QCoreApplication::applicationDirPath());

    // creates the bundle stores
    m_spBundlesStore = m_spSmfCoreFactory->createBundlesStore(m_spSmfLocation);

    // creates and load properties
    setLaunchingProperties();

    // set stylesheet for gui app only
    setStyleSheet();

    // to manage the launcher exit
    QObject::connect(m_spApp.get(), SIGNAL(aboutToQuit()), this, SLOT(onAboutToQuit()));

    // The platform is activated after the event loop is started
    QTimer::singleShot(0, this, SLOT(startPlatform()));

    // Run the Q app
    ret = m_spApp.get()->exec();

    return ret;
}

void Launcher::setStyleSheet()
{

}

CoreFactory * Launcher::createFactory()
{
    return new CoreFactory;
}

void Launcher::setFactory(CoreFactory *theFactory)
{
    m_spSmfCoreFactory.reset(theFactory);
}

QspCoreFactory Launcher::getFactory()
{
    return m_spSmfCoreFactory;
}

void Launcher::setLaunchingProperties()
{
    m_spSmfLaunchingProperties = m_spSmfCoreFactory->createLaunchingProperties("conf/properties.ini");
}

void Launcher::startPlatform()
{

    m_newFwk = m_spBundlesStore->loadFrameworkPlugin("Launcher");

    if (m_newFwk == nullptr)
    {
        pfWarning8(QString("Launcher")) << tr("framework null!");
        m_spApp.get()->exit(1);
    }
    else
    {
        // initialize the framework
        m_newFwk->initFwk(m_spBundlesStore, m_spSmfLaunchingProperties);

        // start the framework
        core::plugin::BundleInterface* bundleItf{m_newFwk->getBundleInterface()};
        bundleItf->start(nullptr);
    }
}

void Launcher::onAboutToQuit()
{
    plugframe::core::plugin::BundleInterface *frameworkBundleItf{m_newFwk->getBundleInterface()};
    frameworkBundleItf->stop();
}
