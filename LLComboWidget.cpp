#include "LLComboWidget.h"

LLComboWidget::LLComboWidget(QRect _initWindowForView, QWidget *parent)
    : QWidget(parent),
      m_initWindowForView(_initWindowForView)
{
    m_timer.setInterval(20);
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(update()));
    m_timer.start();
    connect(this, SIGNAL(newMVCWidget(u_short)), this, SLOT(onNewMVCWidget(u_short)));
    this->setLayout(&m_qGridLayout);
}

LLComboWidget::LLComboWidget(QWidget *parent)
    : QWidget(parent),
      m_initWindowForView(QRect(0, 0, 1024, 768))
{
    m_timer.setInterval(20);
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(update()));
    m_timer.start();
    connect(this, SIGNAL(newMVCWidget(u_short)), this, SLOT(onNewMVCWidget(u_short)));
    this->setLayout(&m_qGridLayout);
}

LLComboWidget::~LLComboWidget()
{
    for(map<u_short, CMVCWidget*>::iterator it = m_mvcWidgets.begin(); it != m_mvcWidgets.end(); ++it)
    {
        delete it->second;
    }
    m_mvcWidgets.clear();
}

void LLComboWidget::createNewMVCWidget(u_short _index)
{
    emit newMVCWidget(_index);
}

void LLComboWidget::update()
{
    for(map<u_short, CMVCWidget*>::iterator it = m_mvcWidgets.begin(); it != m_mvcWidgets.end(); ++it)
    {
        it->second->update();
    }
}

void LLComboWidget::onNewMVCWidget(u_short _index)
{
    if( m_mvcWidgets.end() == m_mvcWidgets.find(_index) )
    {
        CMVCWidget* mvcWidgetTmp = new CMVCWidget(m_initWindowForView);
        m_qGridLayout.addWidget(mvcWidgetTmp, (short)_index / 4, (short)_index % 4);
        m_mvcWidgets.insert(std::pair<u_short, CMVCWidget*>(_index, mvcWidgetTmp));
    }
    else
    {
        return;
    }
}
