#include "guibundlesconffilesselector.h"
#include "guibundleconffilesselectoritem.h"

GuiBundlesConfFilesSelector::GuiBundlesConfFilesSelector(GuiDeveloperModeView *parent):
    plugframe::GuiWidgetList(parent),
    m_view(parent)
{}

void GuiBundlesConfFilesSelector::display(const QString &appliName, const QList<BundleArtefact> &bundleArtefactList)
{
    for (auto i=0;i<bundleArtefactList.size();i++)
    {

        if(bundleArtefactList[i].m_confFilesFlag)
        {
            plugframe::GuiWidgetListItem *item;

            item = new GuiBundleConfFilesSelectorItem{i,
                                                      appliName,
                                                      bundleArtefactList[i].m_bundleName,
                                                      m_view};
            displayItem(item);
        }
    }
}