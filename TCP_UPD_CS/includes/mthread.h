#ifndef MTHREAD_H
#define MTHREAD_H

#include <QThread>
#include <QtNetwork>
#include <QTextEdit>
#include <QApplication>
#include <QGraphicsView>
#include <QLineEdit>
#include <QTcpSocket>
#include <QDebug>
#include <QFileDialog>
#include <QChar>
#include <QByteArray>

class MThread: public QThread
{
    Q_OBJECT
public:
    static const int INTERFACE_W = 350;
    static const int INTERFACE_H = 192;
    MThread(int ID, QGraphicsView* _disp, QTextEdit *_interface, QLineEdit *_status, QString _formato = "txt", QObject *parent = 0 );
    ~MThread();
    void run();
signals:
    void escuta();

public slots:
    void readyRead();
    void disconnected();
    void newSocket(QTcpSocket *_novo);
    int socketDescriptor();
private:
    QGraphicsView *disp;
    QTcpSocket *socket;
    QTextEdit *interface;
    QLineEdit *status;
    QString formato;
    int _socketDescriptor;
    bool _pode;
};

#endif // MTHREAD_H
