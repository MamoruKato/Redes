#ifndef SERVIDOR_H
#define SERVIDOR_H

#include <QPushButton>
#include <QTextEdit>
#include <QtNetwork>
#include <QTcpServer>
#include <QObject>
#include <QString>
#include <QLineEdit>
#include "mthread.h"

class Servidor: public QTcpServer
{
    Q_OBJECT
public:
    Servidor(QGraphicsView* disp,QTextEdit *interface, QLineEdit *status, QPushButton *encerrarServidor, QObject *parent=0,
            const QString formato = "txt",const QString &host = "127.0.0.1", const int porta = 1234);

    ~Servidor();
    void startServer();
public slots:
    void encerrar();
    void escutaServidor();
    void newsocket(QTcpSocket *_socket);

signals:
    void falhaConexao();
    void changedSocket(QTcpSocket *novo);
protected:
    void incomingConnection(qintptr socketDescriptor) Q_DECL_OVERRIDE;

private:
    QGraphicsView *_disp;
    QTextEdit *_text;
    QLineEdit *_status;
    QTcpSocket *_socket;
    MThread *_thread;
    QString address;
    QString _formato;
    int _porta;
    bool _encerrado;
};

#endif // SERVIDOR_H
