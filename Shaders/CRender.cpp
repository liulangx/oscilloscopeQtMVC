#include "Shaders/CRender.h"

#define ATTRIB_VERTEX 1

CRender::CRender()
{
}


CRender::~CRender()
{
}

void CRender::prepare(QString _vertShaderPath, QString _fragShaderPath, QString _geomShaderPath)
{
    initializeOpenGLFunctions();
    QOpenGLFunctions_4_3_Core::glClearColor(1,1,1,0.2);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if("" == _geomShaderPath)
        initialShader(_vertShaderPath, _fragShaderPath);
    else
    {
        initialShader(_vertShaderPath, _fragShaderPath, _geomShaderPath);
    }
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

void CRender::initialShader(QString _vertShaderPath, QString _fragShaderPath, QString _GeomShaderPath)
{
    //shader程序
    //_vertShaderPath = "Shaders/lines.vert";
    if (!m_shaderprogram.addShaderFromSourceFile(QGLShader::Vertex, _vertShaderPath))
    {
        QMessageBox::information(NULL, "vert",
            m_shaderprogram.log(),
            QMessageBox::Yes | QMessageBox::No,
            QMessageBox::Yes);
    }
    //_GeomShaderPath = "Shaders/lines.geo";
    if (!m_shaderprogram.addShaderFromSourceFile(QGLShader::Geometry, _GeomShaderPath))
    {
        QMessageBox::information(NULL, "geo",
            m_shaderprogram.log(),
            QMessageBox::Yes | QMessageBox::No,
            QMessageBox::Yes);
    }
    //_fragShaderPath = "Shaders/lines.Frag";
    if (!m_shaderprogram.addShaderFromSourceFile(QGLShader::Fragment, _fragShaderPath))
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

void CRender::initialShader(QString _vertShaderPath, QString _fragShaderPath)
{
    //shader程序
//    _vertShaderPath = "/home/liu/asio/QOpenGLWidget_MVC/Shaders/basic.vert";
    if (!m_shaderprogram.addShaderFromSourceFile(QGLShader::Vertex, _vertShaderPath))
    {
        QMessageBox::information(NULL, "vert",
            m_shaderprogram.log(),
            QMessageBox::Yes | QMessageBox::No,
            QMessageBox::Yes);
    }
//    _fragShaderPath = "/home/liu/asio/QOpenGLWidget_MVC/Shaders/basic.Frag";
    if (!m_shaderprogram.addShaderFromSourceFile(QGLShader::Fragment, _fragShaderPath))
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

