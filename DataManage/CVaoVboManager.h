#ifndef CVAOVBOMANAGE_H
#define CVAOVBOMANAGE_H
#include <QGLWidget>
#include <map>
#include <vector>
#include <QOpenGLFunctions_4_3_Core>
using std::vector;
using std::map;
class CVaoVboManager : protected QOpenGLFunctions_4_3_Core
{
public:
    CVaoVboManager();
    ~CVaoVboManager();
    void prepare();
    GLuint allocVAO(QGLWidget* _widget);
    GLuint allocVBO(QGLWidget* _widget);
    void delVAOVBO(QGLWidget*_widget);
private:
    map<QGLWidget*, vector<GLuint>> m_mapVaos;
    map<QGLWidget*, vector<GLuint>> m_mapVbos;
};

#endif // CVAOVBOMANAGE_H
