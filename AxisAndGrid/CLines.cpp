#include "CLines.h"

#include "CSceneManager.h"
const float pi = 3.1415926;
const size_t linesLength = 24 * 3600 *50;

CLines::CLines(QObject *_lineManager, u_short _imgIndex, CVaoVboManager *_vaovboManager, QGLWidget *_widget)
    : QObject(_lineManager)
    , m_imgIndex(_imgIndex)
    , m_vaovboManager(_vaovboManager)
    , m_lineRender(new CRender)
    , m_glwidget(_widget)
    , m_persize(sizeof(vector3f)) // 位置3+颜色4
{
    CSceneManager* test = qobject_cast<CSceneManager*>(parent()->parent());
    QObject::connect(this, SIGNAL(adjustGridNumer(u_short, vector2f,vector2f,vector2f,CGrid::RangeChange,CGrid::RangeChange,CGrid::RangeChange)), test, SLOT(onAdjustGridNumer(u_short, vector2f,vector2f,vector2f,CGrid::RangeChange,CGrid::RangeChange,CGrid::RangeChange)));
    initial();
}

CLines::~CLines()
{
    this->cleanUp();
}

void CLines::cleanUp()
{
    LLDELETE(m_lineRender);
}

void CLines::initial()
{
    initializeOpenGLFunctions();
    initialRender();
}

void CLines::initialRender()
{
    m_glwidget->makeCurrent();
    m_lineRender->prepare("/home/liu/asio/QOpenGLWidget_MVC/Shaders/lines.vert", "/home/liu/asio/QOpenGLWidget_MVC/Shaders/lines.Frag", "/home/liu/asio/QOpenGLWidget_MVC/Shaders/lines.geo");

    QMatrix4x4 tmpProjection = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
    tmpProjection.perspective(12.0, 1, 5, 20);

    m_uniformIndexChosePntAnixGridForLines =  m_lineRender->getShader()->uniformLocation("chose");
    m_uniformIndexRangeXPntAnixGridForLines = m_lineRender->getShader()->uniformLocation("rangeX");
    m_uniformIndexRangeYPntAnixGridForLines = m_lineRender->getShader()->uniformLocation("rangeY");
    m_uniformIndexRangeZPntAnixGridForLines = m_lineRender->getShader()->uniformLocation("rangeZ");
    m_uniformIndexScalePntAnixGridForLines = m_lineRender->getShader()->uniformLocation("scale");
    m_uniformIndexRotPntAnixGridForLines = m_lineRender->getShader()->uniformLocation("rot");
    m_uniformIndexMovePntAnixGridForLines = m_lineRender->getShader()->uniformLocation("move");
    m_uniformIndexBasecordPntAnixGridForLines = m_lineRender->getShader()->uniformLocation("basecord");
    m_uniformIndexDrawtypePntAnixGridForLines = m_lineRender->getShader()->uniformLocation("drawtype");
    m_uniformIndexProjectionPntAnixGridForLines = m_lineRender->getShader()->uniformLocation("projection");
    m_uniformIndexViewLinefactorPntAnixGridForLines = m_lineRender->getShader()->uniformLocation("viewScale");
    m_uniformIndexLineColorPntAnixGridForLines = m_lineRender->getShader()->uniformLocation("lineColor");
    m_uniformIndexXyPlaneMarkForLines = m_lineRender->getShader()->uniformLocation("xyPlaneMark");
    m_uniformIndexXzPlaneMarkForLines = m_lineRender->getShader()->uniformLocation("xzPlaneMark");
    m_uniformIndexYzPlaneMarkForLines = m_lineRender->getShader()->uniformLocation("yzPlaneMark");
    m_uniformIndexXLowerForLines = m_lineRender->getShader()->uniformLocation("xLower");
    m_uniformIndexYLowerForLines = m_lineRender->getShader()->uniformLocation("yLower");
    m_uniformIndexZLowerForLines = m_lineRender->getShader()->uniformLocation("zLower");

    m_lineRender->bindShader();
    m_lineRender->getShader()->setUniformValue(m_uniformIndexRangeXPntAnixGridForLines, m_xRange._x, m_xRange._y);
    m_lineRender->getShader()->setUniformValue(m_uniformIndexRangeYPntAnixGridForLines, m_yRange._x, m_yRange._y);
    m_lineRender->getShader()->setUniformValue(m_uniformIndexRangeZPntAnixGridForLines, m_zRange._x, m_zRange._y);
    m_lineRender->getShader()->setUniformValue(m_uniformIndexRotPntAnixGridForLines, m_rotation);
    m_lineRender->getShader()->setUniformValue(m_uniformIndexScalePntAnixGridForLines, m_zoom);
    m_lineRender->getShader()->setUniformValue(m_uniformIndexMovePntAnixGridForLines, m_move);
    m_lineRender->getShader()->setUniformValue(m_uniformIndexDrawtypePntAnixGridForLines, 0);
    m_lineRender->getShader()->setUniformValue(m_uniformIndexProjectionPntAnixGridForLines, tmpProjection);
    m_lineRender->getShader()->setUniformValue(m_uniformIndexLineColorPntAnixGridForLines, m_lineColor._r, m_lineColor._g, m_lineColor._b, m_lineColor._a);
    m_lineRender->getShader()->setUniformValue(m_uniformIndexXyPlaneMarkForLines, false);
    m_lineRender->getShader()->setUniformValue(m_uniformIndexXzPlaneMarkForLines, false);
    m_lineRender->getShader()->setUniformValue(m_uniformIndexYzPlaneMarkForLines, false);
    m_lineRender->getShader()->setUniformValue(m_uniformIndexXLowerForLines, m_xRange._y);
    m_lineRender->getShader()->setUniformValue(m_uniformIndexYLowerForLines, m_yRange._y);
    m_lineRender->getShader()->setUniformValue(m_uniformIndexZLowerForLines, m_zRange._y);
    m_lineRender->releaseShader();
}

void CLines::createNewLineForSameImg(size_t _lineIndex, size_t _pointSize)
{
    if(m_vaos.find(_lineIndex) == m_vaos.end())
    {
        m_glwidget->makeCurrent();
        vector4f color = {1, 0, 0, 1};
        m_colors.insert(std::pair<size_t, vector4f>(_lineIndex, color));
        size_t pointCount = 0;
        m_pointCounts.insert(std::pair<size_t, size_t>(_lineIndex, pointCount));

        size_t pointSize = _pointSize;
        m_pointSizes.insert(std::pair<size_t, size_t>(_lineIndex, pointSize));

        GLuint vao;
        GLuint vbo;
        vao = m_vaovboManager->allocVAO(m_glwidget);
        vbo = m_vaovboManager->allocVBO(m_glwidget);
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER,
                     m_pointSizes.at(_lineIndex) * m_persize,			//颜色和位置
                     nullptr,
                     GL_DYNAMIC_DRAW);
        //glBufferData(GL_ARRAY_BUFFER, pointCount * m_persize, test.data(), GL_DYNAMIC_DRAW);

        //glEnableVertexAttribArray(2);		//法相坐标
        glVertexAttribPointer(0,
                              3,
                              GL_FLOAT,
                              GL_FALSE,
                              m_persize,
                              nullptr);
        glEnableVertexAttribArray(0);		//顶点坐标属性

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        m_vaos.insert(std::pair<size_t, GLuint>(_lineIndex, vao));
        m_vbos.insert(std::pair<size_t, GLuint>(_lineIndex, vbo));
    }
    //glColor3f(1, 1, 0);
}

void CLines::setRenderParam(GLuint _uniformIndexXyPlaneMarkForLines, GLuint _uniformIndexXzPlaneMarkForLines, GLuint _uniformIndexYzPlaneMarkForLines, GLuint _uniformIndexXLowerForLines, GLuint _uniformIndexYLowerForLines, GLuint _uniformIndexZLowerForLines)
{
    m_uniformIndexXyPlaneMarkForLines = _uniformIndexXyPlaneMarkForLines;
    m_uniformIndexXzPlaneMarkForLines = _uniformIndexXzPlaneMarkForLines;
    m_uniformIndexYzPlaneMarkForLines = _uniformIndexYzPlaneMarkForLines;
    m_uniformIndexXLowerForLines = _uniformIndexXLowerForLines;
    m_uniformIndexYLowerForLines = _uniformIndexYLowerForLines;
    m_uniformIndexZLowerForLines = _uniformIndexZLowerForLines;
}

void CLines::draw()
{
    setDraw();
    m_glwidget->makeCurrent();
    m_lineRender->bindShader();

    size_t lineIndex = 0;
    for(map<size_t, GLuint>::iterator it = m_vaos.begin(); it != m_vaos.end(); ++it)
    {
        lineIndex = it->first;
        m_lineRender->getShader()->setUniformValue(m_uniformIndexLineColorPntAnixGridForLines, m_colors.at(lineIndex)._r, m_colors.at(lineIndex)._g, m_colors.at(lineIndex)._b, m_colors.at(lineIndex)._a);
        m_lineRender->getShader()->setUniformValue(m_uniformIndexXyPlaneMarkForLines, false);
        m_lineRender->getShader()->setUniformValue(m_uniformIndexXzPlaneMarkForLines, false);
        m_lineRender->getShader()->setUniformValue(m_uniformIndexYzPlaneMarkForLines, false);
        //m_glwidget->makeCurrent();
        size_t lineIndex = it->first;
        GLuint vao = it->second;
        glBindVertexArray(vao);
        glLineWidth(1.5);
        glDrawArrays(GL_LINE_STRIP, 0, m_pointCounts.at(lineIndex));
        glBindVertexArray(0);
//        m_XYPlaneOn = true;
        if(m_XYPlaneOn)
        {
            m_lineRender->getShader()->setUniformValue(m_uniformIndexXyPlaneMarkForLines, true);
            m_lineRender->getShader()->setUniformValue(m_uniformIndexXzPlaneMarkForLines, false);
            m_lineRender->getShader()->setUniformValue(m_uniformIndexYzPlaneMarkForLines, false);
            m_lineRender->getShader()->setUniformValue(m_uniformIndexZLowerForLines, m_zRange._y/*m_zLower*/);
            glBindVertexArray(vao);
            glLineWidth(1);
            glDrawArrays(GL_LINE_STRIP, 0, m_pointCounts.at(lineIndex));
            glBindVertexArray(0);
        }
//        m_XZPlaneOn = true;
        if(m_XZPlaneOn)
        {
            m_lineRender->getShader()->setUniformValue(m_uniformIndexXyPlaneMarkForLines, false);
            m_lineRender->getShader()->setUniformValue(m_uniformIndexXzPlaneMarkForLines, true);
            m_lineRender->getShader()->setUniformValue(m_uniformIndexYzPlaneMarkForLines, false);
            m_lineRender->getShader()->setUniformValue(m_uniformIndexYLowerForLines, m_yRange._y/*m_yLower*/);
            glBindVertexArray(vao);
            glLineWidth(1);
            glDrawArrays(GL_LINE_STRIP, 0, m_pointCounts.at(lineIndex));
            glBindVertexArray(0);
        }
//        m_YZPlaneOn = true;
        if(m_YZPlaneOn)
        {
            m_lineRender->getShader()->setUniformValue(m_uniformIndexXyPlaneMarkForLines, false);
            m_lineRender->getShader()->setUniformValue(m_uniformIndexXzPlaneMarkForLines, false);
            m_lineRender->getShader()->setUniformValue(m_uniformIndexYzPlaneMarkForLines, true);
            m_lineRender->getShader()->setUniformValue(m_uniformIndexXLowerForLines, m_xRange._y/*m_xLower*/);
            glBindVertexArray(vao);
            glLineWidth(1);
            glDrawArrays(GL_LINE_STRIP, 0, m_pointCounts.at(lineIndex));
            glBindVertexArray(0);
        }
    }
    m_lineRender->releaseShader();
}

void CLines::clearUp()
{

}

void CLines::setColor(size_t _lineIndex, vector4f _color)
{
    m_colors.at(_lineIndex)._r = _color._r;
    m_colors.at(_lineIndex)._g = _color._g;
    m_colors.at(_lineIndex)._b = _color._b;
    m_colors.at(_lineIndex)._a = _color._a;
}

vector4f CLines::getColor(size_t _lineIndex) const
{
    if(m_colors.find(_lineIndex) != m_colors.end())
        return m_colors.at(_lineIndex);
    else
    {
#ifdef DEBUG
        qWarning() << "wrong! no such a line!";
#endif
    }
}

//void CLines::addLine(const vector3f &_posion, GLfloat _xLower, GLfloat _yLower, GLfloat _zLower)
//{
//    m_xLower = _xLower;
//    m_yLower = _yLower;
//    m_zLower = _zLower;
//    m_glwidget->makeCurrent();
//    if (m_pointCount >= m_pointSize)
//    {
//        QMessageBox::information(NULL, "points",
//            "存储点数到达最大值",
//            QMessageBox::Yes | QMessageBox::No,
//            QMessageBox::Yes);
//        m_pointCount = 0;
//        return;
//    }
//    glBindVertexArray(m_vao);
//    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
//    glBufferSubData(GL_ARRAY_BUFFER,
//        m_pointCount * m_persize,
//        sizeof(vector3f),
//        (GLvoid*)&_posion);
//    //qDebug() << "1: " << (m_pointCount) * m_persize;
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    glBindVertexArray(0);

//    ++m_pointCount;
//}

bool CLines::addPoint(size_t _lineindex, const vector3f &_position)
{
    bool createLineMark = false;

    if (m_vaos.find(_lineindex) != m_vaos.end())
    {
//            m_lines.at(_lineindex)->addLine(_position, m_xRange._y, m_yRange._y, m_zRange._y);
        if(m_first2Two)
        {

            float xfisrtPoint = (m_xRange._x + m_xRange._y) / 2.0f;
            float yfisrtPoint = (m_yRange._x + m_yRange._y) / 2.0f;
            float zfisrtPoint = (m_zRange._x + m_zRange._y) / 2.0f;
            if(xfisrtPoint < _position._x)
            {
                m_xRange._x = _position._x;
                m_xRange._y = xfisrtPoint;
                m_RangeChange = true;
            }
            else if(xfisrtPoint > _position._x)
            {
                m_xRange._y = _position._x;
                m_xRange._x = xfisrtPoint;
                m_RangeChange = true;
            }
            else {

            }

            if(yfisrtPoint < _position._y)
            {
                m_yRange._x = _position._y;
                m_yRange._y = yfisrtPoint;
                m_RangeChange = true;
            }
            else if(yfisrtPoint > _position._y)
            {
                m_yRange._y = _position._y;
                m_yRange._x = yfisrtPoint;
                m_RangeChange = true;
            }
            else {

            }

            if(zfisrtPoint < _position._z)
            {
                m_zRange._x = _position._z;
                m_zRange._y = zfisrtPoint;
                m_RangeChange = true;
            }
            else if(zfisrtPoint > _position._z)
            {
                m_zRange._y = _position._z;
                m_zRange._x = zfisrtPoint;
                m_RangeChange = true;
            }
            else {

            }
            m_first2Two = false;
            m_stateChange = true;
        }
        else
        {
            if (m_xRange._x < _position._x)
            {
                if(_position._x >= 0)
                    m_xRange._x = _position._x*1.2;
                else if(_position._x < 0)
                    m_xRange._x = _position._x*0.8;
                m_stateChange = true;
                m_xRanChange = CGrid::RangeChange::Change;
                m_RangeChange = true;
            }
            if (m_xRange._y > _position._x)
            {
                if(_position._x <= 0)
                    m_xRange._y = _position._x*1.2;
                else if(_position._x > 0)
                    m_xRange._y = _position._x*0.8;
                m_stateChange = true;
                m_xRanChange = CGrid::RangeChange::Change;
                m_RangeChange = true;
            }

            if (m_yRange._x < _position._y)
            {
                if(_position._y >= 0)
                    m_yRange._x = _position._y*1.2;
                else if(_position._y < 0)
                    m_yRange._x = _position._y*0.8;
                m_stateChange = true;
                m_yRanChange = CGrid::RangeChange::Change;
                m_RangeChange = true;
            }
            if (m_yRange._y > _position._y)
            {
                if(_position._y <= 0)
                    m_yRange._y = _position._y*1.2;
                else if(_position._y > 0)
                    m_yRange._y = _position._y*0.8;
                m_stateChange = true;
                m_yRanChange = CGrid::RangeChange::Change;
                m_RangeChange = true;
            }

            if (m_zRange._x < _position._z)
            {
                if(_position._z >= 0)
                    m_zRange._x = _position._z*1.2;
                else if(_position._z < 0)
                    m_zRange._x = _position._z*0.8;
                m_stateChange = true;
                m_zRanChange = CGrid::RangeChange::Change;
                m_RangeChange = true;
            }
            if (m_zRange._y > _position._z)
            {
                if(_position._z <= 0)
                    m_zRange._y = _position._z * 1.2;
                else if(_position._z > 0)
                    m_zRange._y = _position._z * 0.8;
                m_stateChange = true;
                m_zRanChange = CGrid::RangeChange::Change;
                m_RangeChange = true;
            }
            //qDebug() << "_position._z: " << _position._z;
            //qDebug() << "m_zRange._y: " << m_zRange._y;
        }
        addPoint(_lineindex, _position, m_xRange._y, m_yRange._y, m_zRange._y);
    }
    //如未建立则创建后添加
    else
    {
//            m_isFirstData = true;
        if(m_vaos.empty())
        {
            m_first2Two = true;

            m_xRange._x = _position._x + 0.5 * fabs(_position._x);
            m_xRange._y = _position._x - 0.5 * fabs(_position._x);

            m_yRange._x = _position._y + 0.5 * fabs(_position._y);
            m_yRange._y = _position._y - 0.5 * fabs(_position._y);

            m_zRange._x = _position._z + 0.5 * fabs(_position._z);
            m_zRange._y = _position._z - 0.5 * fabs(_position._z);

            m_xRanChange = CGrid::RangeChange::Change;
            m_yRanChange = CGrid::RangeChange::Change;
            m_zRanChange = CGrid::RangeChange::Change;

            m_stateChange = true;
            m_RangeChange = true;
        }
        else if(m_first2Two)
        {
            float xfisrtPoint = (m_xRange._x + m_xRange._y) / 2.0f;
            float yfisrtPoint = (m_yRange._x + m_yRange._y) / 2.0f;
            float zfisrtPoint = (m_zRange._x + m_zRange._y) / 2.0f;
            if(xfisrtPoint < _position._x)
            {
                m_xRange._x = _position._x;
                m_xRange._y = xfisrtPoint;
                m_RangeChange = true;
            }
            else if(xfisrtPoint > _position._x)
            {
                m_xRange._y = _position._x;
                m_xRange._x = xfisrtPoint;
                m_RangeChange = true;
            }
            else {

            }

            if(yfisrtPoint < _position._y)
            {
                m_yRange._x = _position._y;
                m_yRange._y = yfisrtPoint;
                m_RangeChange = true;
            }
            else if(yfisrtPoint > _position._y)
            {
                m_yRange._y = _position._y;
                m_yRange._x = yfisrtPoint;
                m_RangeChange = true;
            }
            else {

            }

            if(zfisrtPoint < _position._z)
            {
                m_zRange._x = _position._z;
                m_zRange._y = zfisrtPoint;
                m_RangeChange = true;
            }
            else if(zfisrtPoint > _position._z)
            {
                m_zRange._y = _position._z;
                m_zRange._x = zfisrtPoint;
                m_RangeChange = true;
            }
            else {

            }
            m_first2Two = false;
            m_stateChange = true;
        }
        else
        {
            if (m_xRange._x < _position._x)
            {
                if(_position._x >= 0)
                    m_xRange._x = _position._x*1.2;
                else if(_position._x < 0)
                    m_xRange._x = _position._x*0.8;
                m_stateChange = true;
                m_xRanChange = CGrid::RangeChange::Change;
                m_RangeChange = true;
            }
            if (m_xRange._y > _position._x)
            {
                if(_position._x <= 0)
                    m_xRange._y = _position._x*1.2;
                else if(_position._x > 0)
                    m_xRange._y = _position._x*0.8;
                m_stateChange = true;
                m_xRanChange = CGrid::RangeChange::Change;
                m_RangeChange = true;
            }

            if (m_yRange._x < _position._y)
            {
                if(_position._y >= 0)
                    m_yRange._x = _position._y*1.2;
                else if(_position._y < 0)
                    m_yRange._x = _position._y*0.8;
                m_stateChange = true;
                m_yRanChange = CGrid::RangeChange::Change;
                m_RangeChange = true;
            }
            if (m_yRange._y > _position._y)
            {
                if(_position._y <= 0)
                    m_yRange._y = _position._y*1.2;
                else if(_position._y > 0)
                    m_yRange._y = _position._y*0.8;
                m_stateChange = true;
                m_yRanChange = CGrid::RangeChange::Change;
                m_RangeChange = true;
            }

            if (m_zRange._x < _position._z)
            {
                if(_position._z >= 0)
                    m_zRange._x = _position._z*1.2;
                else if(_position._z < 0)
                    m_zRange._x = _position._z*0.8;
                m_stateChange = true;
                m_zRanChange = CGrid::RangeChange::Change;
                m_RangeChange = true;
            }
            if (m_zRange._y > _position._z)
            {
                if(_position._z <= 0)
                    m_zRange._y = _position._z * 1.2;
                else if(_position._z > 0)
                    m_zRange._y = _position._z * 0.8;
                m_stateChange = true;
                m_zRanChange = CGrid::RangeChange::Change;
                m_RangeChange = true;
            }
            //qDebug() << "_position._z: " << _position._z;
            //qDebug() << "m_zRange._y: " << m_zRange._y;
        }
        addPoint(addLine(_lineindex, linesLength), _position, m_xRange._y, m_yRange._y, m_zRange._y);
        createLineMark = true;
    }

    //如果坐标系的上下界变化则更新网格
    if(m_stateChange)
    {
        //通过鼠标中键放大图像时，本质上放大的上界减去下界的值，所以下界不变，上界为m_xRange._y + (m_xRange._x - m_xRange._y) / m_zoom
        vector2f xrange = {m_xRange._y + (m_xRange._x - m_xRange._y) / m_zoom, m_xRange._y};
        vector2f yrange = {m_yRange._y + (m_yRange._x - m_yRange._y) / m_zoom, m_yRange._y};
        vector2f zrange = {m_zRange._y + (m_zRange._x - m_zRange._y) / m_zoom, m_zRange._y};
        //更新网格
        emit adjustGridNumer(m_imgIndex, xrange, yrange, zrange, m_xRanChange, m_yRanChange, m_zRanChange);
//        m_grid.adjustGridNumber(xrange, yrange, zrange, m_xRanChange, m_yRanChange, m_zRanChange);
        m_xRanChange = CGrid::RangeChange::NotChange;
        m_yRanChange = CGrid::RangeChange::NotChange;
        m_zRanChange = CGrid::RangeChange::NotChange;
    }
    return createLineMark;
}

size_t CLines::addLine(size_t _lineIndex, size_t _pointSize)
{
    createNewLineForSameImg(_lineIndex, _pointSize);
    return _lineIndex;
}

void CLines::addPoint(size_t _lineIndex, const vector3f &_position, GLfloat _xLower, GLfloat _yLower, GLfloat _zLower)
{

    m_xLower = _xLower;
    m_yLower = _yLower;
    m_zLower = _zLower;
    m_glwidget->makeCurrent();
    if (m_pointCounts.at(_lineIndex) >= m_pointSizes.at(_lineIndex))
    {
        QMessageBox::information(NULL, "points",
            "存储点数到达最大值",
            QMessageBox::Yes | QMessageBox::No,
            QMessageBox::Yes);
        m_pointCounts.at(_lineIndex) = 0;
        return;
    }
    glBindVertexArray(m_vaos.at(_lineIndex));
    glBindBuffer(GL_ARRAY_BUFFER, m_vbos.at(_lineIndex));
    glBufferSubData(GL_ARRAY_BUFFER,
        m_pointCounts.at(_lineIndex) * m_persize,
        sizeof(vector3f),
        (GLvoid*)&_position);
    //qDebug() << "1: " << (m_pointCount) * m_persize;
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    ++(m_pointCounts.at(_lineIndex));
}

void CLines::setRotation(QMatrix4x4 _rotation)
{
    m_rotation = _rotation;
}

void CLines::setMove(QMatrix4x4 _move)
{
    m_move = _move;
}

void CLines::setZoom(float _scale)
{
    m_zoom *= _scale;
}

void CLines::setDrawtype(CGrid::DRAWTYPE _drawtype)
{
    m_drawtype = (CLines::DRAWTYPE) _drawtype;
}

void CLines::setRender()
{
    m_lineRender->bindShader();
    m_lineRender->getShader()->setUniformValue(m_uniformIndexMovePntAnixGridForLines, m_move);
    m_lineRender->getShader()->setUniformValue(m_uniformIndexRotPntAnixGridForLines, m_rotation);
    m_lineRender->getShader()->setUniformValue(m_uniformIndexDrawtypePntAnixGridForLines, m_drawtype);
    m_lineRender->releaseShader();
}

void CLines::setDraw()
{
    m_lineRender->bindShader();
    m_lineRender->getShader()->setUniformValue(m_uniformIndexDrawtypePntAnixGridForLines, m_drawtype);

    switch (m_drawtype)
    {
    case XZY:
        {
//            m_stataChange = true;
            if (true/*m_stataChange*/)
            {
                QMatrix4x4 tmpProjection = {
                    1, 0, 0, 0,
                    0, 1, 0, 0,
                    0, 0, 1, 0,
                    0, 0, 0, 1
                };
                tmpProjection.perspective(12.0, 1, 5, 20);
                //tmpProjection.ortho(-1.4f,1.4f,-1.4f,1.4f,-1.4f,1.4f);

                m_lineRender->getShader()->setUniformValue(m_uniformIndexRangeXPntAnixGridForLines, m_xRange._x, m_xRange._y);
                m_lineRender->getShader()->setUniformValue(m_uniformIndexRangeYPntAnixGridForLines, m_yRange._x, m_yRange._y);
                m_lineRender->getShader()->setUniformValue(m_uniformIndexRangeZPntAnixGridForLines, m_zRange._x, m_zRange._y);
                m_lineRender->getShader()->setUniformValue(m_uniformIndexRotPntAnixGridForLines, m_rotation);
                m_lineRender->getShader()->setUniformValue(m_uniformIndexScalePntAnixGridForLines, m_zoom);
                m_lineRender->getShader()->setUniformValue(m_uniformIndexMovePntAnixGridForLines, m_move);
                //qDebug() << "m_move: "<< m_move(0,3) << m_move(1, 3) << m_move(2, 3);
//                m_lineRender->getShader()->setUniformValue(m_uniformIndexsBasecordPntAnixGridForLines, m_cordOrigin._x, m_cordOrigin._y, m_cordOrigin._z);
                m_lineRender->getShader()->setUniformValue(m_uniformIndexProjectionPntAnixGridForLines, tmpProjection);
                //m_stataChange = false;
            }
            break;
        }
    case XY:
        {
//            m_stataChange = true;
            if (true/*m_stataChange*/)
            {
                QMatrix4x4 tmpProjection = {
                    1, 0, 0, 0,
                    0, 1, 0, 0,
                    0, 0, 1, 0,
                    0, 0, 0, 1
                };
                //tmpProjection.perspective(12.0, 1, 5, 20);
                tmpProjection.ortho(-1.4f,1.4f,-1.4f,1.4f,-1.4f,1.4f);
                m_lineRender->getShader()->setUniformValue(m_uniformIndexRangeXPntAnixGridForLines, m_xRange._x, m_xRange._y);
                m_lineRender->getShader()->setUniformValue(m_uniformIndexRangeYPntAnixGridForLines, m_yRange._x, m_yRange._y);
                m_lineRender->getShader()->setUniformValue(m_uniformIndexScalePntAnixGridForLines, m_zoom);
                m_lineRender->getShader()->setUniformValue(m_uniformIndexMovePntAnixGridForLines, m_move);
//                m_lineRender->getShader()->setUniformValue(m_uniformIndexsBasecordPntAnixGridForLines, m_cordOrigin._x, m_cordOrigin._y, m_cordOrigin._z);
                m_lineRender->getShader()->setUniformValue(m_uniformIndexProjectionPntAnixGridForLines, tmpProjection);
//                m_stataChange = false;
            }
            break;
        }
    case XZ:
        {
//            m_stataChange = true;
            if (true/*m_stataChange*/)
            {
                QMatrix4x4 tmpProjection = {
                    1, 0, 0, 0,
                    0, 1, 0, 0,
                    0, 0, 1, 0,
                    0, 0, 0, 1
                };
                //tmpProjection.perspective(12.0, 1, 5, 20);
                tmpProjection.ortho(-1.4f,1.4f,-1.4f,1.4f,-1.4f,1.4f);
                m_lineRender->getShader()->setUniformValue(m_uniformIndexRangeXPntAnixGridForLines, m_xRange._x, m_xRange._y);
                m_lineRender->getShader()->setUniformValue(m_uniformIndexRangeZPntAnixGridForLines, m_zRange._x, m_zRange._y);
                m_lineRender->getShader()->setUniformValue(m_uniformIndexScalePntAnixGridForLines, m_zoom);
                m_lineRender->getShader()->setUniformValue(m_uniformIndexMovePntAnixGridForLines, m_move);
//                m_lineRender->getShader()->setUniformValue(m_uniformIndexsBasecordPntAnixGridForLine, m_cordOrigin._x, m_cordOrigin._y, m_cordOrigin._z);
                m_lineRender->getShader()->setUniformValue(m_uniformIndexProjectionPntAnixGridForLines, tmpProjection);
//                m_stataChange = false;
            }
            break;
        }
    case YZ:
        {
//            m_stataChange = true;
            if (true/*m_stataChange*/)
            {
                QMatrix4x4 tmpProjection = {
                    1, 0, 0, 0,
                    0, 1, 0, 0,
                    0, 0, 1, 0,
                    0, 0, 0, 1
                };
                //tmpProjection.perspective(12.0, 1, 5, 20);
                tmpProjection.ortho(-1.4f,1.4f,-1.4f,1.4f,-1.4f,1.4f);
                m_lineRender->getShader()->setUniformValue(m_uniformIndexRangeYPntAnixGridForLines, m_yRange._x, m_yRange._y);
                m_lineRender->getShader()->setUniformValue(m_uniformIndexRangeZPntAnixGridForLines, m_zRange._x, m_zRange._y);
                m_lineRender->getShader()->setUniformValue(m_uniformIndexScalePntAnixGridForLines, m_zoom);
                m_lineRender->getShader()->setUniformValue(m_uniformIndexMovePntAnixGridForLines, m_move);
//                m_lineRender->getShader()->setUniformValue(m_uniformIndexsBasecordPntAnixGridForLines, m_cordOrigin._x, m_cordOrigin._y, m_cordOrigin._z);
                m_lineRender->getShader()->setUniformValue(m_uniformIndexProjectionPntAnixGridForLines, tmpProjection);
//                m_stataChange = false;
            }
            break;
        }
    }
    m_lineRender->releaseShader();
}

void CLines::setXYPlaneOn()
{
    if(m_XYPlaneOn)
    {
        m_XYPlaneOn = false;
    }
    else
    {
        m_XYPlaneOn = true;
    }
}

void CLines::setXZPlaneOn()
{
    if(m_XZPlaneOn)
    {
        m_XZPlaneOn = false;
    }
    else
    {
        m_XZPlaneOn = true;
    }
}

void CLines::setYZPlaneOn()
{
    if(m_YZPlaneOn)
    {
        m_YZPlaneOn = false;
    }
    else
    {
        m_YZPlaneOn = true;
    }
}
