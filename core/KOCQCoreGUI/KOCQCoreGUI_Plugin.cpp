#include "kocqcoregui_plugin.h"
#include "CpuInfo.h"
#include "KOCQMatImage.h"

#include <qqml.h>

void KOCQCoreGUIPlugin::registerTypes(const char *uri)
{
    // @uri com.kocqui.kocqcoregui

    // CpuInfo
    qmlRegisterType<CpuInfo>(uri, 1, 0, "CpuInfo");

    // KOCQMatImage
    qmlRegisterType<KOCQMatImage>(uri, 1, 0, "KOCQMatImage");

    // The minor version of plugin
    qmlRegisterModule(uri, 1, 0);
}
