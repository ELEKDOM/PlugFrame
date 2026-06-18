#include "guiregistercontrollerservice.h"
#include "service-int/guiregistercontrollerserviceinterface.h"
#include "guiengine.h"

GuiRegisterControllerService::GuiRegisterControllerService(plugframe::BundleImplementation *implementation):
    plugframe::ServiceImplementation{implementation}
{

}

GuiRegisterControllerService::~GuiRegisterControllerService()
{

}

void GuiRegisterControllerService::registerController(const plugframe::QspGuiPageController &controller)
{
    GuiEngine *engine{dynamic_cast<GuiEngine*>(implementation())};

    engine->registerController(controller);
}

QString GuiRegisterControllerService::serviceName()
{
    return plugframe::GuiRegisterControllerServiceInterface::serviceName();
}
