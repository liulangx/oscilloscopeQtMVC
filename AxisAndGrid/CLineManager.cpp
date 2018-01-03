#include "CLineManager.h"
#include "CSceneManager.h"

CLineManager::CLineManager(QObject *_sceneManger, CVaoVboManager *_vaovboManager, QGLWidget *_widget)
    : QObject(_sceneManger)
    , m_vaovboManager(_vaovboManager)
    , m_glwidget(_widget)
{
//    CSceneManager* test = qobject_cast<CSceneManager*>(parent());
//    test->draw();
    initial();
}

CLineManager::~CLineManager()
{
    this->cleanUp();
}

void CLineManager::cleanUp()
{

}

void CLineManager::initial()
{
    initializeOpenGLFunctions();
    m_glwidget->makeCurrent();


}

void CLineManager::createNewLineForNewIndex(u_short _imgIndex)
{
    if(m_mapIdx_Lines.find(_imgIndex) != m_mapIdx_Lines.end())
    {
#ifdef DEBUG
        qWarning() << "已创建线条！";
#endif
        return;
    }
//    vector2f xRange = {1, 0};
//    vector2f yRange = {1, 0};
//    vector2f zRange = {1, 0};
//    m_xRanges.insert(std::pair<u_short, vector2f>(_imgIndex, xRange));
//    m_yRanges.insert(std::pair<u_short, vector2f>(_imgIndex, yRange));
//    m_zRanges.insert(std::pair<u_short, vector2f>(_imgIndex, zRange));

//    DRAWTYPE drawtype = DRAWTYPE::XZY;
//    m_drawtypes.insert(std::pair<u_short, DRAWTYPE>(_imgIndex, drawtype));
//    QMatrix4x4 rotation = {
//        1, 0, 0, 0,
//        0, 1, 0, 0,
//        0, 0, 1, 0,
//        0, 0, 0, 1
//    };
//    m_rotations.insert(std::pair<u_short, QMatrix4x4>(_imgIndex, rotation));
//    QMatrix4x4 move = {
//        1, 0, 0, 0,
//        0, 1, 0, 0,
//        0, 0, 1, 0,
//        0, 0, 0, 1
//    };
//    m_moves.insert(std::pair<u_short, QMatrix4x4>(_imgIndex, move));
//    QMatrix4x4 projection = {
//        1, 0, 0, 0,
//        0, 1, 0, 0,
//        0, 0, 1, 0,
//        0, 0, 0, 1
//    };
//    m_projections.insert(std::pair<u_short, QMatrix4x4>(_imgIndex, projection));
//    float zoom = 1;
//    m_zooms.insert(std::pair<u_short, float>(_imgIndex, zoom));
//    vector4f lineColor = {1.0f, 0.0f, 0.0f, 1.0f};
//    m_lineColors.insert(std::pair<u_short, vector4f>(_imgIndex, lineColor));


    CLines* lines = new CLines(this, _imgIndex, m_vaovboManager, m_glwidget);

    m_mapIdx_Lines.insert(std::pair<u_short, CLines*>(_imgIndex, lines));
//    lines->createNewLineForSameImg(0, 2400);
}

bool CLineManager::addPoint(u_short _imgIndex, size_t _lineindex, const vector3f &_position)
{
    if(m_mapIdx_Lines.find(_imgIndex) == m_mapIdx_Lines.end())
    {
        createNewLineForNewIndex(_imgIndex);
    }
    m_mapIdx_Lines.at(_imgIndex)->addPoint(_lineindex, _position);
    return true;
}


void CLineManager::draw()
{
    m_mapIdx_Lines.at(m_curIndex)->draw();
}

void CLineManager::setCurIndex(u_short _curIndex)
{
    m_curIndex = _curIndex;
}

void CLineManager::setRotation(u_short _imgIndex, QMatrix4x4 _rotation)
{
    m_mapIdx_Lines.at(_imgIndex)->setRotation(_rotation);
}

void CLineManager::setMove(u_short _imgIndex, QMatrix4x4 _move)
{
    m_mapIdx_Lines.at(_imgIndex)->setMove(_move);
}

void CLineManager::setZoom(float _scale)
{
    m_mapIdx_Lines.at(m_curIndex)->setZoom(_scale);
}
