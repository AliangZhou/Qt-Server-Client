#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


namespace Ui {
class MainWindow;
}

QT_BEGIN_NAMESPACE
class QTcpSocket;
class QTcpServer;
class QLabel;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void initInterface();
    void connectPart();

private slots:
    void onListen();
    void onNewConnection();
    void onReadyRead();
    void onSendData();
private:
    Ui::MainWindow *ui;
    QTcpSocket *m_pSocket;
    QTcpServer *m_pServer;
    int m_nPort;
    QLabel *m_pConStaLab;
};

#endif // MAINWINDOW_H
