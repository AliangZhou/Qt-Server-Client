#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTcpSocket>
#include <QTcpServer>
#include <QMessageBox>
#include <QLabel>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_nPort(9999),
    m_pSocket(NULL)
{
    ui->setupUi(this);
    initInterface();
    connectPart();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initInterface()
{
    ui->portText->setText(QString::number(m_nPort));

    m_pServer = new QTcpServer(this);
    m_pConStaLab = new QLabel(this);
    m_pConStaLab->setPixmap(QPixmap(":/res/icon_unlink.png"));

    ui->statusBar->addWidget(new QLabel("Connect: "));
    ui->statusBar->addWidget(m_pConStaLab);
}

void MainWindow::connectPart()
{
    connect(ui->startBtn, &QPushButton::clicked, this, &MainWindow::onListen);
    connect(m_pServer, &QTcpServer::newConnection, this, &MainWindow::onNewConnection);
    connect(ui->sendBtn, &QPushButton::clicked, this, &MainWindow::onSendData);
}

void MainWindow::onListen()
{
    bool bRes = m_pServer->listen(QHostAddress::AnyIPv4, m_nPort);
    if(!bRes){
        QMessageBox::warning(this, "Warning", "Listen port:9999 err, Please check!!!");

    }else{
        qDebug() << "listen port: 9999 success.";
        m_pConStaLab->setPixmap(QPixmap(":/res/icon_wait.png"));
    }
}

void MainWindow::onNewConnection()
{
    m_pSocket = m_pServer->nextPendingConnection();
    connect(m_pSocket, &QTcpSocket::readyRead, this, &MainWindow::onReadyRead);
    if(NULL == m_pSocket){
        QMessageBox::warning(this, "Warning", "new connection err...");
        return;
    }else{
        qDebug() << "have new connect ptr: " << QString::number(m_pSocket->socketDescriptor());
        m_pConStaLab->setPixmap(QPixmap(":/res/icon_link.png"));
    }
}

void MainWindow::onReadyRead()
{
    QString readText = m_pSocket->readAll();
    ui->recText->append(QString("Client Say: %1").arg(readText));
}

void MainWindow::onSendData()
{
    QString strWrite = ui->sendText->toPlainText();
    QByteArray by = strWrite.toLatin1();
    m_pSocket->write(by);
    ui->recText->append(QString("Server Say: %1").arg(strWrite));
    ui->sendText->clear();
}
