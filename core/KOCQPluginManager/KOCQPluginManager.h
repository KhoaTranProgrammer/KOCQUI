/*
 * MIT License
 * 
 * Copyright (c) 2020 KhoaTran Programmer
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/******************
 * VERSION: 1.0.2 *
 *****************/

/********************************************************************
 * PURPOSE                                                          *
 ********************************************************************
 * This class are used to manage all of Plugins                     *
 *******************************************************************/

/********************************************************************
 * VERSION HISTORY                                                  *
 ********************************************************************
 * 1.0.0: Apr-05-2020                                               *
 *        Initial version supports loading all of Plugins           *
 * 1.0.1: May-25-2020                                               *
 *        Add loadPlugin method to load 1 Plugin                    *
 * 1.0.2: Sep-09-2020                                               *
 *        Add option to get icon view type for addIconSlot,         *
 *        addIconSignal. Update algorithm to load plugins via index *
 *******************************************************************/

#ifndef KOCQPLUGINMANAGER_H
#define KOCQPLUGINMANAGER_H

#include <QObject>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QQuickView>
#include <QtQuick>
#include "KOCQPluginManager_Global.h"

typedef void (*CreateWidgetFunction)(QQmlEngine* engine, QObject* rootObject, QUrl source, QObject* pluginManagerObject);

class KOCQPLUGINMANAGERSHARED_EXPORT KOCQPluginManager : public QObject
{
    Q_OBJECT
public:
    static KOCQPluginManager* getInstance();
    void setQmlEngine(QQmlEngine* engine);
    void setRootObject(QObject* rootObject);
    void setSource(QUrl source);
    void setPluinPath(QString pluinPath);
    void loadAllPlugins();
    void loadPlugin(QString pluginLocation);

public slots:
    void addIconSlot(const QVariant &v, const QString & type);

signals:
    void addIconSignal(QVariant, QString);

private:
    KOCQPluginManager();

    int m_currentIndex;
    QVector<CreateWidgetFunction> m_pluginQLibrary;

    QQmlEngine* m_engine;
    QObject* m_rootObject;
    QUrl m_source;
    QString m_pluinPath;
};

#endif // KOCQPLUGINMANAGER_H
