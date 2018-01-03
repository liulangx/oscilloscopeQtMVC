#ifndef CGRID_H
#define CGRID_H
#include "DataManage/CVaoVboManager.h"
#include "textureindex.h"
#include "Shaders/CRender.h"
#include "Database.h"
#include <QGLWidget>
#include <QOpenGLTexture>
#include <QOpenGLFunctions_4_3_Core>
#include <map>

class CGrid : public QObject, public QOpenGLFunctions_4_3_Core
{
    Q_OBJECT
public:
    enum RangeChange {
        NotChange,
        Change
    };
    enum Range{
        xRange,
        yRange,
        zRange
    };
    enum DRAWTYPE {
        XZY = 0,
        XY,
        XZ,
        YZ
    };
    explicit CGrid(CVaoVboManager* _vaovboManager, QGLWidget* _widget);

    void setDrawGrid();
    void setDrawTeture();
    void draw();

    void setRotation(QMatrix4x4 _rotation);
    void setMove(QMatrix4x4 _move);
    void setZoom(float _scale);

    void adjustGridNumber(vector2f _x, vector2f _y, vector2f _z, RangeChange xChange, RangeChange yChange, RangeChange zChange);

    void setFontSize(GLfloat _fontSize = 6.0f);
    void setGridColor(vector4f color);

    void setGridOff();
    void setGridOn();

    void setAnixLabelOff();
    void setAnixLabelOn();

    void setDrawType(DRAWTYPE drawtype);

    void setCordi(vector2f  _x, vector2f _y, vector2f _z);
    void getGridNumber(int & _xGridNumPerAnix, int & _yGridNumPerAnix, int & _zGridNumPerAnix);
    void setGridNumber(int _xGridNumPerAnix, int _yGridNumPerAnix, int _zGridNumPerAnix);
private:
    void drawGrid();
    void drawAnixNumber();
    void drawAnixPoint();
    void drawAnixMinus();
    void drawAnixLabel();

    /*adjustGridNumber:
     * 函数描述：根据更改后的坐标范围[m_*range._y, m_*range._x]来调整网格数
     * 参数描述：anixGridNumberPerAnix: 需要更改的m_*GridNumPerAnix
     *         range: 确定的坐标类型的参数
     */
    bool adjustGridNumber(Range range, int &anixGridNumberPerAnix);

    void initial();
    void prepareRenders();

    bool setInvertedRot();
    void createAndUpdateAnixnumberWithPnt();
    void createAnixnumber();
    void updateAnixnumber();
    void updateAnixDecimalPnt();
    void updateAnixMinus();
    void updateAnixLabel();

    void clearGridVector();
    void addAxisLabel(CGrid::Range range, GLfloat axisOffset, GLfloat size);
    void addAnxisNumber(GLfloat anixNumber, Range range, GLfloat anixOffset, GLfloat size);
    /*getAnxiIntRange:
     * 函数描述：将网格坐标归为整数
     * 根据更改后的坐标范围[m_*range._y, m_*range._x]来调整网格数
     * PS：后期经过更改，去除了边界上的上边界和下边界的判断，即让MinUpper == Minf, MaxLower == Maxf.
     * 参数描述：
     * Maxf: 坐标上限
     * Minf: 坐标下限
     * MaxLower: 坐标上限 第一位非0整数部分
     * MinUpper: 坐标下限 第一位非0整数部分+1
     * front: MinUpper归一化到[0,1]
     * back:  MaxLower归一化到[0,1]
     */
    bool getAnxiIntRange(GLfloat Maxf, GLfloat Minf, GLfloat &MaxLower, GLfloat &MinUpper, GLfloat &front, GLfloat &back);
    bool getAnxiIntRange(GLfloat Maxf, GLfloat Minf, GLfloat &MaxLower, GLfloat &MinUpper);
    /* createAndUpdateGrid:
     * 函数描述： 调用createAndUpdateGrid(), createGrid();
     */
    void createAndUpdateGrid();
    /* createGrid:
     * 函数描述： 创建网格数组，包含坐标和颜色;
     *          初始化和每次调整坐标范围后会调用该函数
     */
    void createGrid();
    /* end */

    /* createGrid:
     * 函数描述：创建缓冲区(动态的)，包含坐标和颜色
     *          初始化和每次调整坐标范围后会调用该函数
     */
    void updateGrid();
    /* end */

    /*adjustGridNumber:
     * 函数描述：根据更改后的坐标范围[m_*range._y, m_*range._x]来调整网格数
     * 参数描述：anixGridNumberPerAnix: 需要更改的m_*GridNumPerAnix
     *         range: 确定的坐标类型的参数
     */
    GLboolean getIntvaluePointposOffsetForXAnix(GLfloat xAnix, GLint& xAnixValue, GLfloat& xAnixOffset, GLboolean& greaterThanOneMark);
    GLboolean getIntvaluePointposOffsetForYAnix(GLfloat yAnix, GLint& yAnixValue, GLfloat& yAnixOffset, GLboolean& greaterThanOneMark);
    GLboolean getIntvaluePointposOffsetForZAnix(GLfloat zAnix, GLint& zAnixValue, GLfloat& zAnixOffset, GLboolean& greaterThanOneMark);
private:
    CVaoVboManager* m_vaovboManager;
    QGLWidget*      m_glWidget;
    CRender*        m_therender;
    CRender*        m_gridRender;  //网格的坐标值，xyz符号由该人render渲染，由外部传入

    GLuint m_uniformIndexDrawtypePntAnixGrid;
    GLuint m_uniformIndexRotPntAnixGrid;
    GLuint m_uniformIndexMovePntAnixGrid;
    GLuint m_uniformIndexProjectionPntAnixGrid;
    GLuint m_uniformIndexChoosePntAnixGrid;
    QMatrix4x4                  m_rotation = {
                                    1.0f, 0.0f, 0.0f, 0.0f,
                                    0.0f, 1.0f, 0.0f, 0.0f,
                                    0.0f, 0.0f, 1.0f, 0.0f,
                                    0.0f, 0.0f, 0.0f, 1.0f,
                                };
    QMatrix4x4                  m_move = {
                                    1.0f, 0.0f, 0.0f, 0.0f,
                                    0.0f, 1.0f, 0.0f, 0.0f,
                                    0.0f, 0.0f, 1.0f, 0.0f,
                                    0.0f, 0.0f, 0.0f, 1.0f,
                                };
    QMatrix4x4                  m_projection = {
                                    1.0f, 0.0f, 0.0f, 0.0f,
                                    0.0f, 1.0f, 0.0f, 0.0f,
                                    0.0f, 0.0f, 1.0f, 0.0f,
                                    0.0f, 0.0f, 0.0f, 1.0f,
                                };
    float                       m_zoom = 1.0f;

    //GridRender for texture;
    GLuint                      m_uniformIndexScaleAnixtexture;
    GLuint                      m_uniformIndexMoveAnixtexture;
    GLuint                      m_uniformIndexBasecordAnixtexture;
    GLuint                      m_uniformIndexProjectionAnixtexture;
    GLuint                      m_uniformIndexRotAnixtexture;
    GLuint                      m_uniformIndexDrawtypeAnixtexture;
    GLuint                      m_uniformIndexRangeXAnixtexture;
    GLuint                      m_uniformIndexRangeYAnixtexture;
    GLuint                      m_uniformIndexRangeZAnixtexture;

    DRAWTYPE                    m_drawtype = DRAWTYPE::XZY;
    vector2f                    m_x = {0,1};			//坐标X, 该参数与坐标轴有关
    vector2f                    m_y = {0,1};			//坐标Y, 该参数与坐标轴有关
    vector2f                    m_z = {0,1};			//坐标Z, 该参数与坐标轴有关
    vector2f                    m_xRange = {0.01,-0.01};//{0.01,-0.01};			//坐标XRange
    vector2f                    m_yRange = {0.01,-0.01};			//坐标YRange
    vector2f                    m_zRange = {0.01,-0.01};			//坐标ZRange
    bool                        m_isFirstRange = true;
    QMatrix4x4                  m_rot = {
                                    1.0f, 0.0f, 0.0f, 0.0f,
                                    0.0f, 1.0f, 0.0f, 0.0f,
                                    0.0f, 0.0f, 1.0f, 0.0f,
                                    0.0f, 0.0f, 0.0f, 1.0f,
                                };      //rotation的逆矩阵

    //建立网格
    vector<float>               m_gridPositions;
    int                         m_xGridNumPerAnix = 4;     //x !!!Note: 生成缓冲区时应该注意当网格点数增加后，可能会导致缓冲区超界
    int                         m_yGridNumPerAnix = 4;     //y
    int                         m_zGridNumPerAnix = 4;     //z
    vector4f                    m_gridColor = {200/255.0f,200/255.0f,200/255.0f,1};
    GLfloat                     m_viewScale = 1.0f;//0.7;
    GLuint                      m_vaoGrid;
    GLuint                      m_vboGrid;
    //建立坐标值
    QOpenGLTexture*             m_textureDgt;                 //数字贴图
    QOpenGLTexture*             m_texturePnt;                 //小数点贴图
    QOpenGLTexture*             m_textureMinus;                 //负号贴图
    QOpenGLTexture*             m_textureLabel;

    GLuint                      m_vaoGridAnixnumDgt;        //数字VAO
    GLuint                      m_vboGridAnixnumDgt;        //VBO
    GLuint                      m_vboGridAnixnumDgtTexture;   //texture vbo
    vector<float>               m_gridAnixnumDgtPositions;  //数字位置容器
    vector<float>               m_gridAnixnumDgtTexture;  //数字Texture位置容器
    GLint                       m_DigPositionSize = -1;

    GLuint                      m_vaoGridAnixnumPnt;        //小数点VAO
    GLuint                      m_vboGridAnixnumPnt;        //VBO
    GLuint                      m_vboGridAnixnumPntTexture;   //texture vbo
    vector<float>               m_gridAnixnumPntPositions;  //小数点位置容器
    vector<float>               m_gridAnixnumPntTexture;  //小数点Texture位置容器
    GLint                       m_PntPositionSize = -1;

    GLuint                      m_vaoGridAnixnumMinus;        //负号VAO
    GLuint                      m_vboGridAnixnumMinus;        //VBO
    GLuint                      m_vboGridAnixnumMinusTexture;   //texture vbo
    vector<float>               m_gridAnixnumMinusPositions;  //负号位置容器
    vector<float>               m_gridAnixnumMinusTexture;  //负号Texture位置容器
    GLint                       m_MinusPositionSize = -1;

    GLuint                      m_vaoGridAnixnumLabel;        //"xyz/"
    GLuint                      m_vboGridAnixnumLabel;        //VBO
    GLuint                      m_vboGridAnixnumLabelTexture;   //texture vbo
    vector<float>               m_gridAnixnumLabelPositions;  //"xyz/"位置容器
    vector<float>               m_gridAnixnumLabelTexture;  //"xyz/"Texture位置容器
    GLint                       m_LabelPositionSize = -1;

    vector3f                    m_xAnixBase = {1, 0, 0};
    vector3f                    m_yAnixBase = {1, 0, 0};
    GLfloat                     m_fontSize = 0.10;
    GLfloat                     m_xSize = 0.06; //0.01
    GLfloat                     m_xOffsetBits = 0;      //x坐标在x轴方向的最大偏移位数
    GLfloat                     m_ySize = 0.06; //0.01
    GLfloat                     m_yOffsetBits = 0;      //y坐标在x轴方向的最大偏移位数
    GLfloat                     m_zSize = 0.06; //0.01
    GLfloat                     m_offset = 0.02;
    vector4f                    m_color = {51/255.0f,221/255.0f,255/255.0f,1};
    GLint                       m_precision = 3;
    vector<GLuint>              m_anixNumber;
    GLint                       m_tensNumber;
    //开关
    GLboolean                   m_gridOn = true;
    GLboolean                   m_anixLabelOn = true;
    GLboolean                   m_anixLabelNotEmpty = true;
    //PosisitonChange
    GLfloat                     m_zOffsetForDrawType = 0; // x,z

    GLboolean                   m_notCopyFromOtherOpenGLWidget = true;
};

#endif // CGRID_H
