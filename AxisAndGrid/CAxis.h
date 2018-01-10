#ifndef CAXIS_H
#define CAXIS_H
#include "Shaders/CRender.h"
#include "DataManage/CVaoVboManager.h"
#include "Database.h"
#include <QOpenGLFunctions_4_3_Core>
#include <QGLShader>
#include <QGLShaderProgram>
#include <QPainter>
#include <QGLWidget>
#include <vector>
using std::vector;
class CAxis : public QObject, public QOpenGLFunctions_4_3_Core
{
    Q_OBJECT
public:
    explicit CAxis(CVaoVboManager* _vaovboManager, QGLWidget* _widget);
    ~CAxis();
    void initial();
    void draw();
    void clearUp();
    void setCordi(vector2f  _x, vector2f _y, vector2f _z);
    void setCordiAlone(vector2f  _x, vector2f _y, vector2f _z);
    //设置当前的图像索引号
    void setCurrentIndex(u_short _currentIndex);
    void createNewAxisForNewIndex(u_short _index);
private:

    void genAxisBuffer(u_short _index);
    void updateAxisBuffer(u_short _index);
    void genAxis(u_short _index);     //生成坐标轴和箭头buffer(参数为坐标线位置)
private:
    CVaoVboManager*              m_vaovboManager = nullptr;
    QGLWidget*                  m_glwidget = nullptr;

    u_short m_index = 0;
    map<u_short, vector3uint>       m_mapIdx_BufIdx;

    map<u_short, vector2f>              m_xs/* = {0,1}*/;			//坐标X
    map<u_short, vector2f>              m_ys/* = {0,1}*/;			//坐标Y
    map<u_short, vector2f>              m_zs/* = {0,1}*/;			//坐标Z
    map<u_short, vector2f>              m_arrowbases/* = {0.01f,0.05f}*/;		//箭头底半径 箭头长度
    map<u_short,vector<GLuint>>				 m_arrowIndexs;					//箭头检索
    map<u_short,vector<float>>				 m_arrowpoints;					//箭头的点
    map<u_short,vector4f>					 m_xcolors/* = {1, 0, 0, 1}*/;//{45/255.0f,57/255.0f,227/255.0f,1};						//x轴颜色
    map<u_short,vector4f>					 m_ycolors/* = {0, 1, 0, 1}*/;//{45/255.0f,57/255.0f,227/255.0f,1};							//y轴颜色
    map<u_short,vector4f>					 m_zcolors/* = {0, 0, 1, 1}*/;//{45/255.0f,57/255.0f,227/255.0f,1};	   					//z轴颜色
    //	float*						m_arrow;						//线段的点
private:
    map<u_short, GLuint>						m_vaos;
    map<u_short, GLuint>						m_vbos;
    map<u_short, GLuint>						m_vboIndexs;
    bool                                        m_flagFirst = true;
};

#endif // CAXIS_H
