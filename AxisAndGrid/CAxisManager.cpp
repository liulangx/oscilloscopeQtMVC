#include "CAxisManager.h"

CAxisManager::CAxisManager(CVaoVboManager *_vaovboManager, QGLWidget *_widget)
    : m_vaovboManager(_vaovboManager)
    , m_glwidget(_widget)
{
    initial();
}

CAxisManager::~CAxisManager()
{
    for(map<u_short, CRender*>::iterator it = m_therenders.begin(); it != m_therenders.end(); ++it)
    {
        LLDELETE(it->second);
//        delete it->second;
    }
    m_therenders.clear();
    LLDELETE(m_axis);
}

void CAxisManager::initial()
{
    initializeOpenGLFunctions();
}

void CAxisManager::draw()
{
    setDraw();
    m_therenders.at(m_curIndex)->bindShader();
    //        drawAxis(m_index);
    m_axis->draw();
    m_therenders.at(m_curIndex)->releaseShader();
}

void CAxisManager::setDraw()
{
    m_glwidget->makeCurrent();
    m_therenders.at(m_curIndex)->bindShader();
    m_therenders.at(m_curIndex)->getShader()->setUniformValue(m_uniformIndexChoosePntAnixGrids.at(m_curIndex), 0);
    m_therenders.at(m_curIndex)->getShader()->setUniformValue(m_uniformIndexDrawtypePntAnixGrids.at(m_curIndex), m_drawtypes.at(m_curIndex));
    switch (m_drawtypes.at(m_curIndex))
    {
        case XZY:
        {
            QMatrix4x4 tmpProjection = {
                1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
            };
            tmpProjection.perspective(12.0, 1, 5, 20);
            m_therenders.at(m_curIndex)->getShader()->setUniformValue(m_uniformIndexRotPntAnixGrids.at(m_curIndex), m_rotations.at(m_curIndex));
            m_therenders.at(m_curIndex)->getShader()->setUniformValue(m_uniformIndexMovePntAnixGrids.at(m_curIndex), m_moves.at(m_curIndex));
            m_therenders.at(m_curIndex)->getShader()->setUniformValue(m_uniformIndexProjectionPntAnixGrids.at(m_curIndex), tmpProjection);
            break;
        }
        default:
        {
            QMatrix4x4 tmpProjection = {
                1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
            };
            //tmpProjection.perspective(12.0, 1, 5, 20);
            tmpProjection.ortho(-1.4f,1.4f,-1.4f,1.4f,-1.4f,1.4f);
            m_therenders.at(m_curIndex)->getShader()->setUniformValue(m_uniformIndexMovePntAnixGrids.at(m_curIndex), m_moves.at(m_curIndex));
            m_therenders.at(m_curIndex)->getShader()->setUniformValue(m_uniformIndexProjectionPntAnixGrids.at(m_curIndex), tmpProjection);
            break;
        }
    }
    m_therenders.at(m_curIndex)->releaseShader();
}

void CAxisManager::prepareAxis(u_short _index)
{
    m_glwidget->makeCurrent();
    if(!m_axis)
    {
        m_axis = new CAxis(m_vaovboManager, m_glwidget);
        m_axis->setCurrentIndex(_index);
        m_curIndex = _index;
    }
    m_axis->createNewAxisForNewIndex(_index);
    QMatrix4x4 rotation = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
    m_rotations.insert(std::pair<u_short, QMatrix4x4>(_index, rotation));

    QMatrix4x4 move = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
    m_moves.insert(std::pair<u_short, QMatrix4x4>(_index, move));

    DRAWTYPE drawtype = DRAWTYPE::XZY;
    m_drawtypes.insert(std::pair<u_short, DRAWTYPE>(_index, drawtype));


    //为每个图像准备着色器
    CRender* therender = new CRender;
    m_therenders.insert(std::pair<u_short, CRender*>(_index, therender));
    therender->prepare("/home/liu/asio/QOpenGLWidget_MVC/Shaders/basic.vert", "/home/liu/asio/QOpenGLWidget_MVC/Shaders/basic.Frag");

    //为axis着色器设置对应的旋转矩阵投影
    GLuint uniformIndexRotPntAnixGrid;
    GLuint uniformIndexProjectionPntAnixGrid;
    GLuint uniformIndexMovePntAnixGrid;
    GLuint uniformIndexChoosePntAnixGrid;
    GLuint uniformIndexDrawtypePntAnixGrid;
    uniformIndexRotPntAnixGrid = m_therenders.at(_index)->getShader()->uniformLocation("rot");
    uniformIndexProjectionPntAnixGrid = m_therenders.at(_index)->getShader()->uniformLocation("projection");
    uniformIndexMovePntAnixGrid = m_therenders.at(_index)->getShader()->uniformLocation("move");
    uniformIndexChoosePntAnixGrid = m_therenders.at(_index)->getShader()->uniformLocation("chose");
    uniformIndexDrawtypePntAnixGrid = m_therenders.at(_index)->getShader()->uniformLocation("drawtype");
    m_uniformIndexRotPntAnixGrids.insert(std::pair<u_short, GLuint>(_index, uniformIndexRotPntAnixGrid));
    m_uniformIndexProjectionPntAnixGrids.insert(std::pair<u_short, GLuint>(_index, uniformIndexProjectionPntAnixGrid));
    m_uniformIndexMovePntAnixGrids.insert(std::pair<u_short, GLuint>(_index, uniformIndexMovePntAnixGrid));
    m_uniformIndexChoosePntAnixGrids.insert(std::pair<u_short, GLuint>(_index, uniformIndexChoosePntAnixGrid));
    m_uniformIndexDrawtypePntAnixGrids.insert(std::pair<u_short, GLuint>(_index, uniformIndexDrawtypePntAnixGrid));


    QMatrix4x4 tmpProjection = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
    tmpProjection.perspective(12.0, 1, 5, 20);

    m_therenders.at(_index)->bindShader();			//绑定着色器
    m_therenders.at(_index)->getShader()->setUniformValue(m_uniformIndexRotPntAnixGrids.at(_index), m_rotations.at(_index));
    m_therenders.at(_index)->getShader()->setUniformValue(m_uniformIndexProjectionPntAnixGrids.at(_index), tmpProjection);
    m_therenders.at(_index)->getShader()->setUniformValue(m_uniformIndexMovePntAnixGrids.at(_index), m_moves.at(_index));
    m_therenders.at(_index)->getShader()->setUniformValue(m_uniformIndexChoosePntAnixGrids.at(_index), 0);
    m_therenders.at(_index)->getShader()->setUniformValue(m_uniformIndexDrawtypePntAnixGrids.at(_index), m_drawtypes.at(_index));
    m_therenders.at(_index)->releaseShader();        //解除着色器
}

void CAxisManager::setCurIndex(u_short _index)
{
    m_curIndex = _index;
    m_axis->setCurrentIndex(_index);
}

void CAxisManager::setDrawType(CAxisManager::DRAWTYPE _drawtype)
{
    m_drawtypes.at(m_curIndex) = _drawtype;
}

void CAxisManager::setRotation(u_short _index, QMatrix4x4 _rotation)
{
    m_rotations.at(_index) = _rotation;
}

void CAxisManager::setMove(u_short _index, QMatrix4x4 _move)
{
    m_moves.at(_index) = _move;
}

void CAxisManager::setCordi(vector2f _x, vector2f _y, vector2f _z)
{
    m_axis->setCordi(_x, _y, _z);
}

void CAxisManager::setRender()
{
    m_therenders.at(m_curIndex)->bindShader();
    m_therenders.at(m_curIndex)->getShader()->setUniformValue(m_uniformIndexRotPntAnixGrids.at(m_curIndex), m_rotations.at(m_curIndex));
    m_therenders.at(m_curIndex)->getShader()->setUniformValue(m_uniformIndexMovePntAnixGrids.at(m_curIndex), m_moves.at(m_curIndex));
    m_therenders.at(m_curIndex)->getShader()->setUniformValue(m_uniformIndexDrawtypePntAnixGrids.at(m_curIndex), m_drawtypes.at(m_curIndex));
    m_therenders.at(m_curIndex)->releaseShader();
}
