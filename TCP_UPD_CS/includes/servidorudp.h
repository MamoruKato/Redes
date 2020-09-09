#ifndef SERVIDORUDP_H
#define SERVIDORUDP_H

#include <QPushButton>
#include <QTextEdit>
#include <qnetworkcookiejar.h>
#include <QObject>
#include <QString>
#include <QUdpSocket>
#include <QtNetwork>
#include <QLineEdit>
#include <QByteArray>
#include <CRC.h>
#include "mthread.h"


class ServidorUDP: public QObject
{
    Q_OBJECT
public:
    ServidorUDP(QTextEdit *interface, QLineEdit *status, QPushButton *encerrarServidor, QGraphicsView *disp,
               QString _checagem = "naoChecar",
               QString formato = "txt", QObject *parent=0, const QString &host = "127.0.0.1", const int porta = 1234);
    void criaSocket();

signals:
    void leituraTerminada();
public slots:
    void readPendingDatagrams();
    void encerrar();
    void salvaArquivo();
private:
    void mostraArquivo();
    bool recebeCheckSum(int dadosRecebidos, QString Sender, QString Porta);

    QTextEdit *_text;
    QLineEdit *_status;
    QTcpSocket *_socket;
    MThread *_thread;
    QString address;
    QUdpSocket *udpSocket;
    QGraphicsView *_disp;
    QString _formato;
    QByteArray full_data;
    QString checagem;
    QHostAddress _addr;
    int _porta;
    bool _encerrado;
};

#endif // SERVIDORUDP_H
