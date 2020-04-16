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
 * VERSION: 1.0.1 *
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
 * 1.0.1: Apr-17-2020                                               *
 *        Modify to only load dll file                              *
 *******************************************************************/

#include "KOCQPluginManager.h"

static KOCQPluginManager *m_instance = nullptr;

KOCQPluginManager* KOCQPluginManager::getInstance()
{
    // Create new one in case of NULL
    if(!m_instance) {
        m_instance = new KOCQPluginManager();
    }

    // Return the available instance
    return m_instance;
}

KOCQPluginManager::KOCQPluginManager()
{
    m_engine = NULL;
    m_rootObject = NULL;
    m_source = NULL;
}

void KOCQPluginManager::setQmlEngine(QQmlEngine* engine)
{
    this->m_engine = engine;
}

void KOCQPluginManager::setRootObject(QObject* rootObject)
{
    this->m_rootObject = rootObject;
    QObject::connect(m_rootObject, SIGNAL(addIconSignal(QVariant)),
                        this, SLOT(addIconSlot(QVariant)));
}

void KOCQPluginManager::setSource(QUrl source)
{
    this->m_source = source;
}

void KOCQPluginManager::setPluinPath(QString pluinPath)
{
    this->m_pluinPath = pluinPath;
}

void KOCQPluginManager::loadAllPlugins()
{
    QDir directory(m_pluinPath);
    QStringList allFiles = directory.entryList();
    foreach(QString filename, allFiles) {
        if(filename != "." && filename != "..")
        {
            QString filePath = m_pluinPath + filename;
            try
            {
                if(filename.contains(".dll"))
                {
                    QLibrary library(filePath);
                    library.load();
                    CreateWidgetFunction newWidget = (CreateWidgetFunction) library.resolve("createNewPlugin");
                    m_pluginQLibrary.push_back(newWidget);
                    QMetaObject::invokeMethod(m_rootObject, "addPlugin");
                }
            }
            catch(const std::bad_alloc &)
            {

            }
        }
    }
}

void KOCQPluginManager::addIconSlot(const QVariant &v)
{
    CreateWidgetFunction newWidget = m_pluginQLibrary.first();
    newWidget(m_engine, m_rootObject, m_source, this);
    emit addIconSignal(v);
    m_pluginQLibrary.pop_front();
}

