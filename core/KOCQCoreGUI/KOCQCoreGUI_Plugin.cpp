#include "kocqcoregui_plugin.h"
#include "CpuInfo.h"

#include <qqml.h>

void KOCQCoreGUIPlugin::registerTypes(const char *uri)
{
    // @uri com.kocqui.kocqcoregui

    // CpuInfo
    qmlRegisterType<CpuInfo>(uri, 1, 0, "CpuInfo");

    // The minor version of plugin
    qmlRegisterModule(uri, 1, 1);
}
