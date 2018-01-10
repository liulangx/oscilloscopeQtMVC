#include "LLComboWidget.h"
const long int queueSize = 5000;
LLComboWidget::LLComboWidget(QRect _initWindowForView, QWidget *parent)
    : QWidget(parent)
    , m_initWindowForView(_initWindowForView)
    , m_mvcWidget(new CMVCWidget)
    , m_cirBuffer(queueSize)
{
    m_timer.setInterval(20);
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(update()));
    m_timer.start();
    connect(this, SIGNAL(newMVCWidget(u_short)), this, SLOT(onNewMVCWidget(u_short)));
    this->setLayout(&m_qGridLayout);
    m_qGridLayout.addWidget(m_mvcWidget);
}

LLComboWidget::LLComboWidget(QWidget *parent)
    : QWidget(parent)
    , m_initWindowForView(QRect(0, 0, 1024, 768))
    , m_mvcWidget(new CMVCWidget)
    , m_cirBuffer(queueSize)
{
    m_timer.setInterval(20);
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(update()));
    m_timer.start();
    connect(this, SIGNAL(newMVCWidget(u_short)), this, SLOT(onNewMVCWidget(u_short)));
    this->setLayout(&m_qGridLayout);
    m_qGridLayout.addWidget(m_mvcWidget);
}

LLComboWidget::~LLComboWidget()
{
    for(map<u_short, CMVCWidget*>::iterator it = m_mvcWidgets.begin(); it != m_mvcWidgets.end(); ++it)
    {
        delete it->second;
    }
    m_mvcWidgets.clear();
}

void LLComboWidget::recvMessage()
{
    try{
        boost::asio::io_service io_server;
        u_short port = 8003;
        m_server = new CAsioAsyncServer(io_server, port);
        m_server->run();

        io_server.run();
    }
    catch(std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

void LLComboWidget::run()
{
    m_timer.start(20);
    m_threadRecv = new boost::thread(std::bind(&LLComboWidget::recvMessage, this)); //开启数据读取线程
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(onTimeOut()));
}

void LLComboWidget::closeTimer()
{
    m_timer.destroyed();
    m_server->close();
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
    m_mvcWidget->update();
}

void LLComboWidget::onTimeOut()
{
    //将cirbuf中的数据读出并赋给opengl窗口
    readCirBufToCreateOpenGLImages();
    //刷新opengl窗口内容
    update();
}

void LLComboWidget::readCirBufToCreateOpenGLImages()
{
    //清空并重新读取CirBuffer中的数据
    m_cirBuffer.clear();
    m_server->getCirBuffer(&m_cirBuffer);

//    Message test;
//    test.mData.dataX = 1;
//    m_cirBuffer.push_back(test);

    float x = 0;
    float y = 0;
    float z = 0;
    vector4f _color;
//    QOpenglMain* _tmpCurrent;
    u_short imgNumber;
    u_short lineNumber;
    //u_short lastNumber = -1;
    bool createLineMark = false;
    vector2f xRange = {1.0f, 0.0f};
    vector2f yRange = {1.0f, 0.0f};
    vector2f zRange = {1.0f, 0.0f};

    //qDebug() << m_cirBuffer.size();
    for(boost::circular_buffer<Message>::iterator it = m_cirBuffer.begin(); it != m_cirBuffer.end(); )
    {
        imgNumber = it->mData.imageNumber;
        lineNumber = it->mData.lineNumber;

        vector<u_short>::iterator itFind = ::find(m_imageNumbers.begin(), m_imageNumbers.end(), imgNumber);
        if(m_imageNumbers.end() == itFind)
        {
            m_imageNumbers.push_back(imgNumber);
            m_mvcWidget->initGL(imgNumber);
//            m_dataRAW.addNewImage(imgNumber);
            continue;
        }
        else
        {
            x = it->mData.dataX;
            y = it->mData.dataY;
            z = it->mData.dataZ;
            //_tmpCurrent = m_charts.at(imgNumber);
            //_tmpCurrent = m_llOpengglWidgets.at(imgNumber)->getQOpenglMain();

            createLineMark = m_mvcWidget->addPoint(imgNumber, lineNumber, { x, y, z});
//                 createLineMark = m_llOpengglWidgets.at(imgNumber)->addPoint(lineNumber, { x, y, z});
                //_tmpCurrent->addPoint(0, { x, y, z});
//                if(m_llOpengglWidgets.at(imgNumber)->checkRangeChange(xRange, yRange, zRange))
//                {
//                    m_dataRAW.addNewLineRange(imgNumber, m_llOpengglWidgets.at(imgNumber)->getFrameType(), xRange, yRange, zRange);
//                }
                //_tmpCurrent->setColor(0, _color);
                if(createLineMark)
                {
                    _color._r = float(random()) / float(RAND_MAX); _color._g = float(random()) / float(RAND_MAX);
                    _color._b = float(random()) / float(RAND_MAX); _color._a = float(random()) / float(RAND_MAX);
                    m_mvcWidget->setColor(imgNumber, lineNumber, _color);
//                    m_llOpengglWidgets.at(imgNumber)->setColor(lineNumber, _color);
//                    m_dataRAW.addNewLineColor(imgNumber, lineNumber, _color);
                }


//            m_dataRAW.writeDataToFile(imgNumber, lineNumber, it->frame, x, y, z);
        }
        ++it;
        if(m_cirBuffer.size() != 0)
            m_cirBuffer.pop_front();
        //lastNumber = imgNumber;
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
