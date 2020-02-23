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
                QLibrary library(filePath);
                library.load();
                CreateWidgetFunction newWidget = (CreateWidgetFunction) library.resolve("createNewPlugin");
                m_pluginQLibrary.push_back(newWidget);
                QMetaObject::invokeMethod(m_rootObject, "addPlugin");
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

