#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

QT_BEGIN_NAMESPACE
class QTcpSocket;
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
    void onLink();
    void onUnlink();
    void onConnected();
    void onDisconnected();
    void onReadyRead();
    void onSendData();

private:
    Ui::MainWindow *ui;
    QTcpSocket *m_pSocket;
    int m_nPort;
    QString m_strSerIp;
    QLabel *m_pConStaLab;
};

#endif // MAINWINDOW_H
