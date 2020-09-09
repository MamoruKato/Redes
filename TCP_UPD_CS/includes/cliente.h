#ifndef CLIENTE_H
#define CLIENTE_H

#include <QtNetwork/QAbstractSocket>
#include <QPushButton>
#include <QObject>
#include <QDataStream>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QUdpSocket>
#include <QCoreApplication>
#include <QApplication>
#include <QTextEdit>
#include <QLineEdit>
#include <QThread>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include "CRC.h"

class Cliente: public QThread
{
    Q_OBJECT
public:
    static const int MAX_UDP_SIZE = 512;

    Cliente(const QString &host, const int porta, const QString protocolo, QByteArray _dados, QGraphicsView *disp,
            QTextEdit *teste, QLineEdit *status, QPushButton *enviarCliente, QPushButton *Parar, QString formato, QString checagem);

    void run();
    ~Cliente();

signals:
    void falhaConexao();
    void enviando();
    void enviado();
    void arquivoGrande();
public slots:
    void enviarParaServidor();
    void encerrar();
    void enviarCheckSum();
private:
    void enviaTcpProtocol();
    void enviaUdpProtocol();

    QTcpSocket *socket;
    QUdpSocket *udpsocket;
    QGraphicsView* _disp;
    QString clientProtocol;
    QByteArray dados;
    QTextEdit *_teste;
    QString _host;
    QString _formato;
    QLineEdit *_status;
    QString _checagem;
    int _porta;
};

#endif // CLIENTE_H
