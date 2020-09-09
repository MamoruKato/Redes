#include "servidor.h"


Servidor::Servidor(QGraphicsView *disp,QTextEdit *interface,QLineEdit *status, QPushButton *encerrarServidor,
                   QObject *parent,const QString formato,const QString &host, const int porta):QTcpServer(parent)
{
    connect(encerrarServidor, SIGNAL(clicked()), SLOT(encerrar()));

    _formato = formato;
    _disp = disp;
    _text = interface;
    _encerrado = false;
    _status = status;
    address = host;
    _porta = porta;

}

Servidor::~Servidor()
{

}

void Servidor::startServer()
{
    if(!this->listen(QHostAddress::Any,_porta))
    {

        _status->setText("Nao foi possivel realizar conexao");
        emit falhaConexao();
        return;
    }
    else
        _status->setText("Conectado");

}

void Servidor::escutaServidor()
{

    QTcpSocket *novo = new QTcpSocket();
    newsocket(novo);

    if(!_socket->setSocketDescriptor(_thread->socketDescriptor()))
    {
        _status->setText("Falha");
        return;
    }
    _status->setText("Recebendo");

    connect(_socket, SIGNAL(readyRead()),_thread,SLOT(readyRead()));
    connect(_socket,SIGNAL(disconnected()), _thread, SLOT(disconnected()));
}


void Servidor::newsocket(QTcpSocket *socket)
{
    _socket = socket;
    emit changedSocket(_socket);
}


void Servidor::incomingConnection(qintptr socketDescriptor)
{
    _thread = new MThread(socketDescriptor,_disp,_text,_status, _formato, this);

    connect(this, SIGNAL(changedSocket(QTcpSocket*)),_thread, SLOT(newSocket(QTcpSocket*)));
    connect(_thread, SIGNAL(escuta()), this, SLOT(escutaServidor()));
    connect(_thread, SIGNAL(finished()), _thread, SLOT(deleteLater()));

    _thread->start();
}

void Servidor::encerrar()
{

    _encerrado = true;
    _status->setText("Encerrado");
    this->close();
    this->deleteLater();
}
