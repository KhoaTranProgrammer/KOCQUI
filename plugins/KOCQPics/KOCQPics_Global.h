#ifndef KOCQPICS_GLOBAL_H
#define KOCQPICS_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(KOCQPICS_LIBRARY)
#  define KOCQPICSSHARED_EXPORT Q_DECL_EXPORT
#else
#  define KOCQPICSSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // KOCQPICS_GLOBAL_H