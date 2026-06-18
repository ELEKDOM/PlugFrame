#ifndef GUIREGISTERCONTROLLERSERVICE_H
#define GUIREGISTERCONTROLLERSERVICE_H

#include <QSharedPointer>
#include "service/serviceimplementation.h"
#include "gui/guipagecontroller.h"

class GuiRegisterControllerService : public plugframe::ServiceImplementation
{
public:
    GuiRegisterControllerService(plugframe::BundleImplementation *implementation);
    ~GuiRegisterControllerService() override;

public:
    void registerController(const plugframe::QspGuiPageController& controller);

protected:
    QString serviceName() override;
};
using QspGuiRegisterControllerService = QSharedPointer<GuiRegisterControllerService>;
#endif // GUIREGISTERCONTROLLERSERVICE_H
