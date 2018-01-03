#include "CSceneManager.h"
#include "MVC/CScene.h"
const float pi = 3.1415926;
CSceneManager::CSceneManager(CScene *_mvcWidget, QGLWidget *_widget)
    : QObject(_mvcWidget)
    , m_glwidget(_widget)
    , m_vaovboManager(new CVaoVboManager)
{
    QObject::connect(this, SIGNAL(update()), qobject_cast<CScene*>(this->parent()), SLOT(update()));
}

void CSceneManager::initGL(u_short _index)
{
    m_vaovboManager->prepare();
    prepareDataForEachImg(_index);
    prepareGrid(_index);
    prepareAxis(_index);
    prepareLine(_index);

}

void CSceneManager::prepareDataForEachImg(u_short _index)
{
    //为每个图像的旋转准备旋转矩阵
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
    bool leftPushDown = false;
    bool rightPushDown = false;
    int mouseCordx = 0;
    int mouseCordy = 0;
    u_char frameType = 0;
    m_leftPushDowns.insert(std::pair<u_short, bool>(_index, leftPushDown));
    m_rightPushDowns.insert(std::pair<u_short, bool>(_index, rightPushDown));
    m_mouseCordxs.insert(std::pair<u_short, int>(_index, mouseCordx));
    m_mouseCordys.insert(std::pair<u_short, int>(_index, mouseCordy));
    m_frameTypes.insert(std::pair<u_short, u_char>(_index, frameType));
}

void CSceneManager::draw()
{
    m_axisManager->draw();
    m_lineManager->draw();
    m_gridManager->draw();
}

void CSceneManager::prepareAxis(u_short _index)
{
    if(!m_axisManager)
    {
        m_axisManager = new CAxisManager(m_vaovboManager, m_glwidget);
    }
//    CVaoVboManager* vaovboManage = new CVaoVboManager;
    m_axisManager->prepareAxis(_index);
}

void CSceneManager::prepareLine(u_short _index)
{
    if(!m_lineManager)
    {
        m_lineManager = new CLineManager(this, m_vaovboManager, m_glwidget);
        m_lineManager->setCurIndex(_index);
    }
    vector3f position = {0, 0, 0};
//    for(int j(0); j < 100; ++j)
//    {
        for(int i(0); i < 100; ++i)
        {
            position._y = /*j / 200.0 +*/ 0.5 * sin(i / 100.0);
            position._z = cos(i / 100.0);
            position._x = i / 100.0;
            m_lineManager->addPoint(_index, 0, position);
        }
//    }
        m_lineManager->createNewLineForNewIndex(_index);
}

void CSceneManager::prepareGrid(u_short _index)
{
    if(!m_gridManager)
    {
        m_gridManager = new CGridManager(m_vaovboManager, m_glwidget);
        m_gridManager->setCurIndex(_index);
    }
    m_gridManager->createNewLineForNewIndex(_index);
}

void CSceneManager::setRot(float _x, float _y)
{
    //计算旋转矩阵
    m_rotations.at(m_index) = QMatrix4x4(1.0, 0.0, 0.0, 0.0,
                    0.0, cos(_x), -sin(_x), 0.0,
                    0.0, sin(_x), cos(_x), 0.0,
                        0.0, 0.0, 0.0, 1.0)*
        QMatrix4x4(cos(_y), 0.0, sin(_y), 0.0,
            0.0, 1.0, 0.0, 0.0,
            -sin(_y), 0.0, cos(_y), 0.0,
            0.0, 0.0, 0.0, 1.0)/**
                QMatrix4x4(cos(_z), -sin(_z), 0.0, 0.0,
                    sin(_z), cos(_z), 0.0, 0.0,
                    0.0, 0.0, 1.0, 0.0,
                    0.0, 0.0, 0.0, 1.0)*/*m_rotations.at(m_index);
    m_lineManager->setRotation(m_index, m_rotations.at(m_index));
    m_axisManager->setRotation(m_index, m_rotations.at(m_index));
    m_gridManager->setRotation(m_index, m_rotations.at(m_index));
}

void CSceneManager::setMove(float _x, float _y)
{
    m_moves.at(m_index) = QMatrix4x4(1.0, 0.0, 0.0, _x,
                                     0.0, 1.0, 0.0, _y,
                                     0.0, 0.0, 1.0, 0.0,
                                     0.0, 0.0, 0.0, 1.0) * m_moves.at(m_index);
    m_lineManager->setMove(m_index, m_moves.at(m_index));
    m_axisManager->setMove(m_index, m_moves.at(m_index));
    m_gridManager->setMove(m_index, m_moves.at(m_index));
}

void CSceneManager::setDrawType(CGrid::DRAWTYPE _drawtype)
{
    m_gridManager->setDrawType(_drawtype);
    //setCordi({ 0,1 }, { 0,1 }, {0,1});
    switch (_drawtype)
    {
        case CGrid::DRAWTYPE::XZY:
        {
            m_moves.at(m_index) = { 1,0,0,0,
                    0,1,0,0,
                    0,0,1,0,
                    0,0,0,1 };
            m_rotations.at(m_index) = { 1,0,0,0,
                    0,1,0,0,
                    0,0,1,0,
                    0,0,0,1 };
//            m_gridManager->setRotation(m_index, m_rotations.at(m_index));
//            m_gridManager->setMove(m_index, m_moves.at(m_index));
            setMove(0, 0);
            setRot(0, 0);

            m_gridManager->setCordi({ 0,1 }, { 0,1 }, {0,1});
//            m_gridManager->setMove(m_index, m_moves.at(m_index));
//            m_gridManager->setRotation(m_index, m_rotations.at(m_index));
            break;
        }
        case CGrid::DRAWTYPE::XY:
        {

            m_moves.at(m_index) = { 1,0,0,0,
                    0,1,0,0,
                    0,0,1,0,
                    0,0,0,1 };
            m_rotations.at(m_index) = { 1,0,0,0,
                    0,1,0,0,
                    0,0,1,0,
                    0,0,0,1 };
//            m_gridManager->setRotation(m_index, m_rotations.at(m_index));
//            m_gridManager->setMove(m_index, m_moves.at(m_index));
            setRot(0, 0);
            setMove(-0.9, -0.9);
            m_gridManager->setCordi({ -0.9f,0.9f }, { -0.9f,0.9f }, { 0,1 });
//            m_gridManager->setMove(m_index, m_moves.at(m_index));
//            m_gridManager->setRotation(m_index, m_rotations.at(m_index));
            break;
        }
        case CGrid::DRAWTYPE::XZ:
        {

            m_moves.at(m_index) = { 1,0,0,0,
                    0,1,0,0,
                    0,0,1,0,
                    0,0,0,1 };
            m_rotations.at(m_index) = { 1,0,0,0,
                    0,1,0,0,
                    0,0,1,0,
                    0,0,0,1 };
//            m_gridManager->setRotation(m_index, m_rotations.at(m_index));
//            m_gridManager->setMove(m_index, m_moves.at(m_index));
            setRot(-pi/2, 0);
            setMove(-0.9, -0.9);
            m_gridManager->setCordi({ -0.9f,0.9f }, { 0,1 }, { -0.9f,0.9f });
            break;
        }
        case CGrid::DRAWTYPE::YZ:
        {

            m_moves.at(m_index) = { 1,0,0,0,
                    0,1,0,0,
                    0,0,1,0,
                    0,0,0,1 };
            m_rotations.at(m_index) = { 1,0,0,0,
                    0,1,0,0,
                    0,0,1,0,
                    0,0,0,1 };
//            m_gridManager->setRotation(m_index, m_rotations.at(m_index));
//            m_gridManager->setMove(m_index, m_moves.at(m_index));
            setRot(0, pi/2);
            setMove(-0.9, -0.9);
            m_gridManager->setCordi({ 0,1 }, { -0.9f,0.9f }, { -0.9f,0.9f });
            break;
        }
    }
    emit update();



}

void CSceneManager::addPoint(size_t _lineindex, const vector3f &_position)
{

}


void CSceneManager::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_leftPushDowns.at(m_index) = true;
        m_mouseCordxs.at(m_index) = event->scenePos().x();
        m_mouseCordys.at(m_index) = event->scenePos().y();
    }
    if (event->button() == Qt::RightButton)
    {
        m_rightPushDowns.at(m_index) = true;
        m_mouseCordxs.at(m_index) = event->scenePos().x();
        m_mouseCordys.at(m_index) = event->scenePos().y();
    }
}

void CSceneManager::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(0 == m_frameTypes.at(m_index))
    {
        if (m_leftPushDowns.at(m_index))
        {
            float _roatx = m_mouseCordxs.at(m_index) - event->scenePos().x();
            float _roaty = m_mouseCordys.at(m_index) - event->scenePos().y();
            m_mouseCordxs.at(m_index) = event->scenePos().x();
            m_mouseCordys.at(m_index) = event->scenePos().y();

            setRot(_roaty / 200,  _roatx/ 200/*,0*/);
        }
    }
    if(m_rightPushDowns.at(m_index))
    {
        float _movex = ((float)m_mouseCordxs.at(m_index) - event->scenePos().x()) / qobject_cast<CScene*>(parent())->width();
        float _movey = ((float)m_mouseCordys.at(m_index) - event->scenePos().y()) / qobject_cast<CScene*>(parent())->height();
        m_mouseCordxs.at(m_index) = event->scenePos().x();
        m_mouseCordys.at(m_index) = event->scenePos().y();
        setMove(-_movex, _movey);
    }

}

void CSceneManager::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_leftPushDowns.at(m_index) = false;
    }
    if (event->button() == Qt::RightButton)
    {
        m_rightPushDowns.at(m_index) = false;
    }
}

void CSceneManager::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        if(m_index < 1)
            m_index += 1;
        else
            m_index = 0;
        m_axisManager->setCurIndex(m_index);
        //m_axis->setCurrentIndex(m_index);
        m_lineManager->setCurIndex(m_index);
        m_gridManager->setCurIndex(m_index);
    }
    if(event->button() == Qt::RightButton)
    {
        if(m_drawtype != CGrid::DRAWTYPE::YZ)
        {
            m_drawtype = (CGrid::DRAWTYPE)(int(m_drawtype) + 1);
        }
        else
        {
            m_drawtype = CGrid::DRAWTYPE::XZY;
        }

        this->setDrawType(m_drawtype);

    }
}

void CSceneManager::WheelEvent(QGraphicsSceneWheelEvent *event)
{
    if(event->delta() > 0)
    {
        float scale = 1.1;
        m_gridManager->setZoom(scale);
        m_lineManager->setZoom(scale);
    }
    else
    {
        float scale = 0.9;
        m_gridManager->setZoom(scale);
        m_lineManager->setZoom(scale);
    }
    emit update();
}

void CSceneManager::onAdjustGridNumer(u_short _imgIndex, vector2f _xrange, vector2f _yrange, vector2f _zrange, CGrid::RangeChange _xRanChange, CGrid::RangeChange _yRanChange, CGrid::RangeChange _zRanChange)
{
    m_gridManager->adjustGridNumer(_imgIndex, _xrange, _yrange, _zrange, _xRanChange, _yRanChange, _zRanChange);

    int a;
    qDebug() << "this is a test" << endl;
}
