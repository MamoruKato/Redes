#include "cliente.h"

Cliente::Cliente(const QString &host, const int porta, const QString protocolo, QByteArray _dados, QGraphicsView *disp,
                 QTextEdit *teste, QLineEdit *status, QPushButton *enviarCliente, QPushButton *Parar, QString formato, QString checagem)
{

    connect(enviarCliente,SIGNAL(clicked()),SLOT(enviarParaServidor()));
    connect(Parar, SIGNAL(clicked()), SLOT(encerrar()));

    _checagem = checagem;
    socket = NULL;
    udpsocket = NULL;
    _formato = formato;
    dados = _dados;
    _teste = teste;
    _host = host;
    _porta = porta;
    _status = status;
    _disp = disp;
     clientProtocol = protocolo;

}

Cliente::~Cliente()
{

}

void Cliente::run()
{
    exec();
}

void Cliente::enviarParaServidor()
{

    if(clientProtocol == "TCP")
    {
        this->enviaTcpProtocol();
    }
    else if(clientProtocol == "UDP")
    {
        this->enviaUdpProtocol();
    }
    else
        return;
}

void Cliente::enviaTcpProtocol()
{
    QVariant strPorta(_porta);
    int dadosEscritos= 0;

    socket = new QTcpSocket(this);

    socket->connectToHost(_host,_porta);
    if (!socket->waitForConnected(1000))
    {
        socket->error();
        _status->setText("Falha na conexao");
        emit falhaConexao();

        return;
    }
    else
        _status->setText("Conectado");

    emit enviando();

    _status->setText("Enviando");
    dadosEscritos = socket->write(dados);
    socket->waitForBytesWritten(1000);
    socket->waitForReadyRead(3000);


    _status->setText("Enviado");
    socket->close();

    socket->deleteLater();

    _teste->setText("IP: " + _host + "\n" + "Porta: " + strPorta.toString() + "\n"
                    + "Enviados: " + QVariant(dadosEscritos).toString() + " bytes");

    emit enviado();

}

void Cliente::enviaUdpProtocol()
{
    QVariant strPorta(_porta);
    QByteArray dadom;
    QHostAddress addr(_host);

    int dadosEscritos=0,temp = 0;
    int pos = 0, tamanho = dados.size();
    udpsocket = new QUdpSocket(this);

    while(pos < tamanho)
    {

        dadom = dados.mid(pos,MAX_UDP_SIZE);
        pos += MAX_UDP_SIZE;

        temp = udpsocket->writeDatagram(dadom,addr,_porta);
        dadosEscritos += temp;
    }

   _teste->setText("IP: " + _host + "\n" + "Porta: " + strPorta.toString() + "\n"
                   + "Enviados: " + QVariant(dadosEscritos).toString() + "bytes");

   _status->setText("Dados enviados");

   udpsocket->close();
   udpsocket->deleteLater();

}

void Cliente::enviarCheckSum()
{
    if(_checagem == "checkSum")
    {
        char *checksum = new char(qChecksum(dados,dados.size()));

        socket = new QTcpSocket();

        socket->connectToHost(_host,_porta);
        if (!socket->waitForConnected(1000))
        {
            socket->error();
            _status->setText("Não foi possivel transmitir Checksum");

            return;
        }

        QByteArray bCheckSum(checksum);
        socket->write(bCheckSum);
        socket->waitForBytesWritten(1000);
        socket->waitForReadyRead(3000);


        _status->setText("Enviado Checksum");

        socket->close();

        socket->deleteLater();
    }
    else if(_checagem == "CRC")
    {
        char *crc = new char(CRC::Calculate(dados.data(),dados.size(),CRC::CRC_32()));

        socket = new QTcpSocket();

        socket->connectToHost(_host,_porta);
        if (!socket->waitForConnected(1000))
        {
            socket->error();
            _status->setText("Não foi possivel transmitir CRC");

            return;
        }

        QByteArray bCheckSum(crc);
        socket->write(bCheckSum);
        socket->waitForBytesWritten(1000);
        socket->waitForReadyRead(3000);


        _status->setText("Enviado CRC");

        socket->close();

        socket->deleteLater();

    }
    else
        return;

}

void Cliente::encerrar()
{
    _status->setText("Cliente Encerrado");
    this->quit();
    this->wait();
    this->deleteLater();
}

//CRC code implemented by https://github.com/d-bahr/CRCpp
