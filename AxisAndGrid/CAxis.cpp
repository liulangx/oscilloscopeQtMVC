#include "CAxis.h"

const float pi = 3.1415926;
#define  MAX_CHAR 1024
CAxis::CAxis(CVaoVboManager *_vaovboManager, QGLWidget *_widget)
    : m_vaovboManager(_vaovboManager)
    , m_glwidget(_widget)
{
    initial();
}

CAxis::~CAxis()
{
    clearUp();
}

void CAxis::initial()
{
    initializeOpenGLFunctions();
    m_glwidget->makeCurrent();
    //createNewAxisForNewIndex(m_index);
}

void CAxis::draw()
{
    if(m_mapIdx_BufIdx.find(m_index) != m_mapIdx_BufIdx.end())
    {
        m_glwidget->makeCurrent();
        GLuint m_vao = m_vaos.at(m_index);
        GLuint m_vboIndex = m_vboIndexs.at(m_index);
        glBindVertexArray(m_vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,
            m_vboIndex);
        glDrawElements(GL_TRIANGLES,m_arrowIndexs.at(m_index).size()-18, GL_UNSIGNED_INT, 0);
        glLineWidth(1.5);
        glDrawElements(GL_LINES, 18, GL_UNSIGNED_INT, (char*)((m_arrowIndexs.at(m_index).size() - 18)*4));
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); //ll
        glBindVertexArray(0);
    }
}

void CAxis::clearUp()
{
//    m_vaovboManager->delVAOVBO(m_glwidget, m_vaos.at());
}

void CAxis::setCordi(vector2f _x, vector2f _y, vector2f _z)
{
    m_xs.at(m_index)._x = 0;
    m_xs.at(m_index)._y = _x._y - _x._x;
    m_ys.at(m_index)._x = 0;
    m_ys.at(m_index)._y = _y._y - _y._x;
    m_zs.at(m_index)._x = 0;
    m_zs.at(m_index)._y = _z._y - _z._x;
    genAxis(m_index);							//��������
    updateAxisBuffer(m_index);
}

void CAxis::setCordiAlone(vector2f _x, vector2f _y, vector2f _z)
{
    m_xs.at(m_index)._x = 0;
    m_xs.at(m_index)._y = _x._y - _x._x;
    m_ys.at(m_index)._x = 0;
    m_ys.at(m_index)._y = _y._y - _y._x;
    m_zs.at(m_index)._x = 0;
    m_zs.at(m_index)._y = _z._y - _z._x;
}

void CAxis::setCurrentIndex(u_short _currentIndex)
{
    if(m_flagFirst)
    {
        m_index = _currentIndex;
        m_flagFirst = false;
        return;
    }
    if(m_mapIdx_BufIdx.find(_currentIndex) != m_mapIdx_BufIdx.end())
        m_index = _currentIndex;
#ifdef DEBUG
    else
        qWarning() << "该图索引号不存在！";
#endif
}

void CAxis::createNewAxisForNewIndex(/*CRender *_render,*/ u_short _index)
{
    if(m_mapIdx_BufIdx.find(_index) != m_mapIdx_BufIdx.end())
    {
#ifdef DEBUG
        qWarning() << "该图索引号已经存在！";
#endif
        return;
    }
    vector2f m_x = {0, 1};
    m_xs.insert(std::pair<u_short, vector2f>(_index, m_x));
    vector2f m_y = {0, 1};
    m_ys.insert(std::pair<u_short, vector2f>(_index, m_y));
    vector2f m_z = {0, 1};
    m_zs.insert(std::pair<u_short, vector2f>(_index, m_z));
    vector2f m_arrowbase = {0.01f,0.05f};
    m_arrowbases.insert(std::pair<u_short,vector2f>(_index, m_arrowbase));

    if(_index == 0)
    {
        vector4f m_xcolor = {1, 0, 0, 1};
        m_xcolors.insert(std::pair<u_short, vector4f>(_index, m_xcolor));
        vector4f m_ycolor = {0, 1, 0, 1};
        m_ycolors.insert(std::pair<u_short, vector4f>(_index, m_ycolor));
        vector4f m_zcolor = {0, 0, 1, 1};
        m_zcolors.insert(std::pair<u_short, vector4f>(_index, m_zcolor));
    }
    else if(_index == 1)
    {
        vector4f m_xcolor = {1, 0, 0, 1};
        m_xcolors.insert(std::pair<u_short, vector4f>(_index, m_xcolor));
        vector4f m_ycolor = {0, 1, 0, 1};
        m_ycolors.insert(std::pair<u_short, vector4f>(_index, m_ycolor));
        vector4f m_zcolor = {0, 0, 1, 1};
        m_zcolors.insert(std::pair<u_short, vector4f>(_index, m_zcolor));
    }
    else
    {
        vector4f m_xcolor = {1, 0, 0, 1};
        m_xcolors.insert(std::pair<u_short, vector4f>(_index, m_xcolor));
        vector4f m_ycolor = {0, 1, 0, 1};
        m_ycolors.insert(std::pair<u_short, vector4f>(_index, m_ycolor));
        vector4f m_zcolor = {0, 0, 1, 1};
        m_zcolors.insert(std::pair<u_short, vector4f>(_index, m_zcolor));
    }

    GLuint m_vao, m_vbo, m_vboIndex;

    m_vbo = m_vaovboManager->allocVBO(m_glwidget);
    m_vao = m_vaovboManager->allocVAO(m_glwidget);

    m_vboIndex = m_vaovboManager->allocVBO(m_glwidget);
    vector3uint bufIdx = {m_vbo, m_vao, m_vboIndex};

    m_mapIdx_BufIdx.insert(std::pair<u_short, vector3uint>(_index, bufIdx));

    m_vaos.insert(std::pair<u_short, GLuint>(_index, m_vao));
    m_vbos.insert(std::pair<u_short, GLuint>(_index, m_vbo));
    m_vboIndexs.insert(std::pair<u_short, GLuint>(_index, m_vboIndex));

    genAxis(_index);
    genAxisBuffer(_index);
}

void CAxis::genAxisBuffer(u_short _index)
{
    m_glwidget->makeCurrent();

    GLuint m_vao = m_vaos.at(_index);
    GLuint m_vbo = m_vbos.at(_index);
    GLuint m_vboIndex = m_vboIndexs.at(_index);

    glBindVertexArray(m_vao);
    GLuint  _persize = sizeof(vector3f) + sizeof(vector4f);//λ��3+��ɫ3
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER,
        m_arrowpoints.at(_index).size() * sizeof(GLfloat),
        m_arrowpoints.at(_index).data(),
        GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,
        3,
        GL_FLOAT,
        GL_FALSE,
        _persize,
        0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,
        4,
        GL_FLOAT,
        GL_FALSE,
        _persize,
        (char*)(sizeof(vector3f)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,
        m_vboIndex);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        m_arrowIndexs.at(_index).size() * sizeof(GLuint),
        m_arrowIndexs.at(_index).data(),
        GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void CAxis::updateAxisBuffer(u_short _index)
{
    m_glwidget->makeCurrent();

    GLuint m_vao = m_vaos.at(_index);
    GLuint m_vbo = m_vbos.at(_index);
    GLuint m_vboIndex = m_vboIndexs.at(_index);

    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    //GLboolean b = glIsVertexArray(m_vao);
    glBufferSubData(GL_ARRAY_BUFFER,
        0,
        m_arrowpoints.at(_index).size() * sizeof(GLfloat),
        m_arrowpoints.at(_index).data());
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,
        m_vboIndex);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER,
        0,
        m_arrowIndexs.at(_index).size() * sizeof(GLuint),
        m_arrowIndexs.at(_index).data());
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void CAxis::genAxis(u_short _index)
{
    m_glwidget->makeCurrent();
    vector<GLuint> m_arrowIndex;
    vector<float> m_arrowpoint;
    vector2f m_arrowbase = m_arrowbases.at(_index);
    vector2f m_x = m_xs.at(_index);
    vector2f m_y = m_ys.at(_index);
    vector2f m_z = m_zs.at(_index);
    vector4f m_xcolor = m_xcolors.at(_index);
    vector4f m_ycolor = m_ycolors.at(_index);
    vector4f m_zcolor = m_zcolors.at(_index);
    m_arrowIndex.clear();
    m_arrowpoint.clear();
    size_t anglenum = 20;			//��Ⱦ������Ҫ��������20��

    int offsite = 0;
    for (size_t index = 0; index < anglenum; ++index)		//��������
    {
        if (index < (anglenum - 1))
        {
            m_arrowIndex.push_back(0);
            m_arrowIndex.push_back(index + 1);
            m_arrowIndex.push_back(index + 2);
        }
        else {
            m_arrowIndex.push_back(0);
            m_arrowIndex.push_back(index + 1);
            m_arrowIndex.push_back(1);
        }
    }
    offsite = anglenum + 1;
    for (size_t index = 0; index < anglenum; ++index)		//��������
    {
        if (index < (anglenum - 1))
        {
            m_arrowIndex.push_back(0 + offsite);
            m_arrowIndex.push_back(index + 1 + offsite);
            m_arrowIndex.push_back(index + 2 + offsite);
        }
        else {
            m_arrowIndex.push_back(0 + offsite);
            m_arrowIndex.push_back(index + 1 + offsite);
            m_arrowIndex.push_back(1 + offsite);
        }
    }
    offsite = 2 * (anglenum + 1);
    for (size_t index = 0; index < anglenum; ++index)		//��������
    {
        if (index < (anglenum - 1))
        {
            m_arrowIndex.push_back(0 + offsite);
            m_arrowIndex.push_back(index + 1 + offsite);
            m_arrowIndex.push_back(index + 2 + offsite);
        }
        else {
            m_arrowIndex.push_back(0 + offsite);
            m_arrowIndex.push_back(index + 1 + offsite);
            m_arrowIndex.push_back(1 + offsite);
        }
    }
    offsite = 3 * (anglenum + 1);
    for (size_t index = 0; index < 6 * 3; ++index)					//����������
    {
        m_arrowIndex.push_back(offsite + index);
    }


    //X�����ͷ
    m_arrowpoint.push_back(m_x._y);			//x���
    m_arrowpoint.push_back(m_y._x);			//y��С
    m_arrowpoint.push_back(m_z._x);			//z��С
    m_arrowpoint.push_back(m_xcolor._r);//��ɫ
    m_arrowpoint.push_back(m_xcolor._g);//��ɫ
    m_arrowpoint.push_back(m_xcolor._b);//��ɫ
    m_arrowpoint.push_back(m_xcolor._a);//��ɫ
    for (size_t index = 0; index < anglenum; ++index)
    {
        m_arrowpoint.push_back(m_x._y - m_arrowbase._y);
        m_arrowpoint.push_back(m_y._x+m_arrowbase._x*cos(index * 2 * pi / anglenum));
        m_arrowpoint.push_back(m_z._x+m_arrowbase._x*sin(index * 2 * pi / anglenum));

        m_arrowpoint.push_back(m_xcolor._r);//��ɫ
        m_arrowpoint.push_back(m_xcolor._g);//��ɫ
        m_arrowpoint.push_back(m_xcolor._b);//��ɫ
        m_arrowpoint.push_back(m_xcolor._a);//��ɫ
    }

    //Y���� ��ͷ
    m_arrowpoint.push_back(m_x._x);			//x���
    m_arrowpoint.push_back(m_y._y);			//y��С
    m_arrowpoint.push_back(m_z._x);			//z��С
    m_arrowpoint.push_back(m_ycolor._r);//��ɫ
    m_arrowpoint.push_back(m_ycolor._g);//��ɫ
    m_arrowpoint.push_back(m_ycolor._b);//��ɫ
    m_arrowpoint.push_back(m_ycolor._a);//��ɫ
    for (size_t index = 0; index < anglenum; ++index)
    {
        m_arrowpoint.push_back(m_x._x + m_arrowbase._x*cos(index * 2 * pi / anglenum));
        m_arrowpoint.push_back(m_y._y - m_arrowbase._y);
        m_arrowpoint.push_back(m_z._x + m_arrowbase._x*sin(index * 2 * pi / anglenum));

        m_arrowpoint.push_back(m_ycolor._r);//��ɫ
        m_arrowpoint.push_back(m_ycolor._g);//��ɫ
        m_arrowpoint.push_back(m_ycolor._b);//��ɫ
        m_arrowpoint.push_back(m_ycolor._a);//��ɫ
    }

    //Z���� ��ͷ
    m_arrowpoint.push_back(m_x._x);
    m_arrowpoint.push_back(m_y._x);
    m_arrowpoint.push_back(m_z._y);
    m_arrowpoint.push_back(m_zcolor._r);//��ɫ
    m_arrowpoint.push_back(m_zcolor._g);//��ɫ
    m_arrowpoint.push_back(m_zcolor._b);//��ɫ
    m_arrowpoint.push_back(m_zcolor._a);//��ɫ
    for (size_t index = 0; index < anglenum; ++index)
    {
        m_arrowpoint.push_back(m_x._x + m_arrowbase._x*cos(index * 2 * pi / anglenum));
        m_arrowpoint.push_back(m_y._x - m_arrowbase._x*sin(index * 2 * pi / anglenum));
        m_arrowpoint.push_back(m_z._y - m_arrowbase._y);
        m_arrowpoint.push_back(m_zcolor._r);//��ɫ
        m_arrowpoint.push_back(m_zcolor._g);//��ɫ
        m_arrowpoint.push_back(m_zcolor._b);//��ɫ
        m_arrowpoint.push_back(m_zcolor._a);//��ɫ
    }

    //X��
    m_arrowpoint.push_back(m_x._x); m_arrowpoint.push_back(m_y._x); m_arrowpoint.push_back(m_z._x);
    m_arrowpoint.push_back(m_xcolor._r); m_arrowpoint.push_back(m_xcolor._g); m_arrowpoint.push_back(m_xcolor._b); m_arrowpoint.push_back(m_xcolor._a);

    m_arrowpoint.push_back(m_x._y); m_arrowpoint.push_back(m_y._x); m_arrowpoint.push_back(m_z._x);
    m_arrowpoint.push_back(m_xcolor._r); m_arrowpoint.push_back(m_xcolor._g); m_arrowpoint.push_back(m_xcolor._b); m_arrowpoint.push_back(m_xcolor._a);
    //Y��
    m_arrowpoint.push_back(m_x._x); m_arrowpoint.push_back(m_y._x); m_arrowpoint.push_back(m_z._x);
    m_arrowpoint.push_back(m_ycolor._r); m_arrowpoint.push_back(m_ycolor._g); m_arrowpoint.push_back(m_ycolor._b); m_arrowpoint.push_back(m_ycolor._a);

    m_arrowpoint.push_back(m_x._x); m_arrowpoint.push_back(m_y._y); m_arrowpoint.push_back(m_z._x);
    m_arrowpoint.push_back(m_ycolor._r); m_arrowpoint.push_back(m_ycolor._g); m_arrowpoint.push_back(m_ycolor._b); m_arrowpoint.push_back(m_ycolor._a);
    //Z��
    m_arrowpoint.push_back(m_x._x); m_arrowpoint.push_back(m_y._x); m_arrowpoint.push_back(m_z._x);
    m_arrowpoint.push_back(m_zcolor._r); m_arrowpoint.push_back(m_zcolor._g); m_arrowpoint.push_back(m_zcolor._b); m_arrowpoint.push_back(m_zcolor._a);

    m_arrowpoint.push_back(m_x._x); m_arrowpoint.push_back(m_y._x); m_arrowpoint.push_back(m_z._y);
    m_arrowpoint.push_back(m_zcolor._r); m_arrowpoint.push_back(m_zcolor._g); m_arrowpoint.push_back(m_zcolor._b); m_arrowpoint.push_back(m_zcolor._a);
    m_arrowIndexs.erase(_index);
    m_arrowpoints.erase(_index);
    m_arrowIndexs.insert(std::pair<u_short, vector<GLuint>>(_index, m_arrowIndex));
    m_arrowpoints.insert(std::pair<u_short, vector<float>>(_index, m_arrowpoint));

}
