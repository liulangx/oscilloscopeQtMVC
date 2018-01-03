#include "CGridManager.h"

CGridManager::CGridManager(CVaoVboManager *_vaovboManager, QGLWidget *_widget)
    : m_vaovboManager(_vaovboManager)
    , m_glwidget(_widget)
{
    initial();
}

CGridManager::~CGridManager()
{

}

void CGridManager::createNewLineForNewIndex(u_short _imgIndex)
{
    if(m_grids.find(_imgIndex) != m_grids.end())
    {
#ifdef DEBUG
        qWarning() << "已创建网格！";
#endif
        return;
    }


    CGrid* grid = new CGrid(m_vaovboManager, m_glwidget);

    m_grids.insert(std::pair<u_short, CGrid*>(_imgIndex, grid));
}

void CGridManager::setCurIndex(u_short _index)
{
    m_curIndex = _index;
}

void CGridManager::setRotation(u_short _index, QMatrix4x4 _rotation)
{
    m_grids.at(_index)->setRotation(_rotation);
}

void CGridManager::setMove(u_short _index, QMatrix4x4 _move)
{
    m_grids.at(_index)->setMove(_move);
}

void CGridManager::setZoom(float _scale)
{
    m_grids.at(m_curIndex)->setZoom(_scale);
}

void CGridManager::setDrawType(CGrid::DRAWTYPE _drawtype)
{
    m_grids.at(m_curIndex)->setDrawType(_drawtype);
    //    m_grids.at(m_curIndex)
}

void CGridManager::setCordi(vector2f _x, vector2f _y, vector2f _z)
{
    m_grids.at(m_curIndex)->setCordi(_x, _y, _z);
}

void CGridManager::draw()
{
    m_grids.at(m_curIndex)->draw();
}

void CGridManager::adjustGridNumer(u_short _imgIndex, vector2f _xrange, vector2f _yrange, vector2f _zrange, CGrid::RangeChange _xRanChange, CGrid::RangeChange _yRanChange, CGrid::RangeChange _zRanChange)
{
    m_grids.at(_imgIndex)->adjustGridNumber(_xrange, _yrange, _zrange, _xRanChange, _yRanChange, _zRanChange);
}

void CGridManager::initial()
{
    initializeOpenGLFunctions();
    m_glwidget->makeCurrent();
}
