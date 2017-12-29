#include "Shaders/CRender.h"

#define ATTRIB_VERTEX 1

CRender::CRender()
{
}


CRender::~CRender()
{
}

void CRender::prepare()
{
    initializeOpenGLFunctions();
    QOpenGLFunctions_4_3_Core::glClearColor(1,1,1,0.2);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    initialShader();
}

void CRender::bindShader()
{
    m_shaderprogram.bind();
}

void CRender::releaseShader()
{
    m_shaderprogram.release();
}

GLuint CRender::getUniformDataIndex(const char * _name)
{
    return GLuint(m_shaderprogram.uniformLocation(_name));
}

QGLShaderProgram * CRender::getShader()
{
    return &m_shaderprogram;
}

void CRender::initialShader()
{
    //shader程序
    if (!m_shaderprogram.addShaderFromSourceFile(QGLShader::Vertex, "/home/liu/asio/QOpenGLWidget_MVC/Shaders/basic.vert"))
    {
        QMessageBox::information(NULL, "vert",
            m_shaderprogram.log(),
            QMessageBox::Yes | QMessageBox::No,
            QMessageBox::Yes);
    }
    if (!m_shaderprogram.addShaderFromSourceFile(QGLShader::Fragment, "/home/liu/asio/QOpenGLWidget_MVC/Shaders/basic.Frag"))
    {
        QMessageBox::information(NULL, "Frag",
            m_shaderprogram.log(),
            QMessageBox::Yes | QMessageBox::No,
            QMessageBox::Yes);
    }
    if (!m_shaderprogram.link())
    {
        QMessageBox::information(NULL, "Link",
            m_shaderprogram.log(),
            QMessageBox::Yes | QMessageBox::No,
            QMessageBox::Yes);
    }
}

