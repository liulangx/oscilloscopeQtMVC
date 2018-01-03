#pragma once
#include <vector>
#include <QOpenGLFunctions_4_3_Core>
#include <QGLShaderProgram>
#include <QMessageBox>
class CRender:protected QOpenGLFunctions_4_3_Core
{
public:
    CRender();
    ~CRender();
    void	prepare(QString _vertShaderPath, QString _fragShaderPath, QString _geomShaderPath = "");
    void	bindShader();
    void	releaseShader();

    GLuint	getUniformDataIndex(const char* _name);			//获取uniform数据
    QGLShaderProgram* getShader();
protected:
    void initialShader(QString _vertShaderPath, QString _fragShaderPath, QString _GeomShaderPath);
    void initialShader(QString _vertShaderPath, QString _fragShaderPath);
    QGLShaderProgram			m_shaderprogram;				//shader程序管理
};
