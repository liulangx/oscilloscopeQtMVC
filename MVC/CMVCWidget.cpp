#include "CMVCWidget.h"

CMVCWidget::CMVCWidget(QWidget *parent)
    : QWidget(parent),
      m_initWindowForView(QRect(0, 0, 400, 400))
{
    m_glWidget = new QGLWidget();
    m_glWidget->makeCurrent();
    m_graphicsView = new CGraphicsView;
    m_scene = new CScene(m_initWindowForView.width(), m_initWindowForView.height(), m_glWidget);
    m_graphicsView->setGeometry(m_initWindowForView);
    m_graphicsView->setViewport(m_glWidget);
    m_graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    m_graphicsView->setScene(m_scene);
    m_layout.addWidget(m_graphicsView);
    this->setLayout(&m_layout);
    initGL();
}

CMVCWidget::CMVCWidget(QRect _initWindowForView, QWidget *parent)
    : QWidget(parent),
      m_initWindowForView(_initWindowForView)
{
    m_glWidget = new QGLWidget();
    m_glWidget->makeCurrent();
    m_graphicsView = new CGraphicsView(this);
    m_scene = new CScene(m_initWindowForView.width(), m_initWindowForView.height(), m_glWidget);
    m_graphicsView->setGeometry(m_initWindowForView);
    m_graphicsView->setViewport(m_glWidget);
    m_graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    m_graphicsView->setScene(m_scene);
    m_layout.addWidget(m_graphicsView);
    this->setLayout(&m_layout);
    initGL();
//    connect(this, SIGNAL(rotationChanged(QMatrix4x4)), m_scene, SLOT(onRotationChanged(QMatrix4x4)));
}

void CMVCWidget::initGL()
{
    m_scene->initGL();
}

void CMVCWidget::update()
{
    m_scene->update();
}

//void CMVCWidget::onRotationChanged(QMatrix4x4 _rotation)
//{
//    emit this->rotationChanged(_rotation);
//}
