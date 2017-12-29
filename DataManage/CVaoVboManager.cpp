#include "CVaoVboManager.h"
#include "QDebug"
CVaoVboManager::CVaoVboManager()
{
    m_mapVaos.clear();
    m_mapVbos.clear();
//    QGLWidget *widget= new QGLWidget;
//    auto it = m_mapVaos.find(widget);
//    qDebug() << (GLvoid)it;
}

CVaoVboManager::~CVaoVboManager()
{
    for(map<QGLWidget*, vector<GLuint>>::iterator it1 = m_mapVaos.begin(); it1 != m_mapVaos.end(); ++it1)
    {
        for(vector<GLuint>::iterator it2 = it1->second.begin(); it2 != it1->second.end(); ++it2)
        {
            glDeleteVertexArrays(1, &(*it2));
        }
    }
    for(map<QGLWidget*, vector<GLuint>>::iterator it1 = m_mapVbos.begin(); it1 != m_mapVbos.end(); ++it1)
    {
        for(vector<GLuint>::iterator it2 = it1->second.begin(); it2 != it1->second.end(); ++it2)
        {
            glDeleteBuffers(1, &(*it2));
        }
    }
}

void CVaoVboManager::prepare()
{
    initializeOpenGLFunctions();
}

GLuint CVaoVboManager::allocVAO(QGLWidget *_widget)
{
//    map<QGLWidget*, vector<GLuint>>::iterator it = m_mapVaos.end();
//    m_mapVaos.find(_widget);
    _widget->makeCurrent();
    if(m_mapVaos.find(_widget) == m_mapVaos.end())
    {
        vector<GLuint> vaos;
        m_mapVaos.insert(std::pair<QGLWidget*, vector<GLuint>>(_widget, vaos));
    }
    GLuint vao;
    glGenVertexArrays(1, &vao);
    if(vao <= 0)
        return -1;
    m_mapVaos.at(_widget).push_back(vao);
    return (GLuint)vao;
}

GLuint CVaoVboManager::allocVBO(QGLWidget *_widget)
{
    _widget->makeCurrent();
    if(m_mapVbos.find(_widget) == m_mapVbos.end())
    {
        vector<GLuint> vbos;
        m_mapVbos.insert(std::pair<QGLWidget*, vector<GLuint>>(_widget, vbos));
    }

    GLuint vbo;
    glGenBuffers(1, &vbo);

    if(vbo <= 0)
        return -1;
    m_mapVbos.at(_widget).push_back(vbo);
    return (GLuint)vbo;
}

void CVaoVboManager::delVAOVBO(QGLWidget *_widget)
{
    _widget->makeCurrent();
    for(vector<GLuint>::iterator it = m_mapVaos.at(_widget).begin(); it != m_mapVaos.at(_widget).end(); ++it)
    {
        glDeleteVertexArrays(1, &(*it));
    }
    for(vector<GLuint>::iterator it = m_mapVbos.at(_widget).begin(); it != m_mapVbos.at(_widget).end(); ++it)
    {
        glDeleteBuffers(1, &(*it));
    }
}
