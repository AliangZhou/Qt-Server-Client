#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTcpSocket>
#include <QMessageBox>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_nPort(9999),
    m_strSerIp("172.20.14.38")
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
    ui->serIp->setText(m_strSerIp);
    ui->serport->setText(QString::number(m_nPort));

    m_pSocket = new QTcpSocket(this);
    m_pConStaLab = new QLabel(this);
    m_pConStaLab->setPixmap(QPixmap(":/res/icon_unlink.png"));

    ui->statusBar->addWidget(new QLabel("Connect: "));
    ui->statusBar->addWidget(m_pConStaLab);
}

void MainWindow::connectPart()
{
    connect(ui->linkBtn, &QPushButton::clicked, this, &MainWindow::onLink);
    connect(m_pSocket, &QTcpSocket::connected, this, &MainWindow::onConnected);
    connect(m_pSocket, &QTcpSocket::disconnected, this, &MainWindow::onDisconnected);   //服务器断开连接
    connect(m_pSocket, &QTcpSocket::readyRead, this, &MainWindow::onReadyRead);
    connect(ui->sendBtn, &QPushButton::clicked, this, &MainWindow::onSendData);
}

void MainWindow::onLink()
{
    m_pSocket->connectToHost(m_strSerIp, m_nPort);
}

void MainWindow::onUnlink()
{

}

void MainWindow::onConnected()
{
    m_pConStaLab->setPixmap(QPixmap(":/res/icon_link.png"));
}

void MainWindow::onDisconnected()
{
    m_pConStaLab->setPixmap(QPixmap(":/res/icon_unlink.png"));
}

void MainWindow::onReadyRead()
{
    QString readText = m_pSocket->readAll();
    ui->recText->append(QString("Server Say: %1").arg(readText));
}

void MainWindow::onSendData()
{
    QString strSend = ui->sendText->toPlainText();
    m_pSocket->write(strSend.toUtf8());
    ui->recText->append(QString("Client Say: %1").arg(strSend));
    ui->sendText->clear();
}
