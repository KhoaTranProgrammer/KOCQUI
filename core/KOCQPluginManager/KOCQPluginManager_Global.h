#ifndef KOCQPLUGINMANAGER_GLOBAL_H
#define KOCQPLUGINMANAGER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(KOCQPLUGINMANAGER_LIBRARY)
#  define KOCQPLUGINMANAGERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define KOCQPLUGINMANAGERSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // KOCQPLUGINMANAGER_GLOBAL_H
