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
    void	prepare();
    void	bindShader();
    void	releaseShader();

    GLuint	getUniformDataIndex(const char* _name);			//获取uniform数据
    QGLShaderProgram* getShader();
protected:
    void initialShader();
    QGLShaderProgram			m_shaderprogram;				//shader程序管理
};
