#include "servidorudp.h"

ServidorUDP::ServidorUDP(QTextEdit *interface, QLineEdit *status, QPushButton *encerrarServidor, QGraphicsView *disp, QString _checagem,
                         QString formato, QObject *parent, const QString &host, const int porta):
    QObject(parent)
{
    connect(encerrarServidor, SIGNAL(clicked()), SLOT(encerrar()));

    checagem = _checagem;
    full_data = 0;
    _disp = disp;
    _text = interface;
    _encerrado = false;
    _status = status;
    address = host;
    _porta = porta;
    _formato = formato;

}

void ServidorUDP::criaSocket()
{
    udpSocket = new QUdpSocket(this);

    if(!udpSocket->bind(QHostAddress::Any, _porta))
    {
        _status->setText("Falha ao conectar");
        return;
    }
    else
        _status->setText("Conectado");

    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));

}

bool ServidorUDP::recebeCheckSum(int dadosRecebidos, QString Sender, QString Porta)
{
    QHostAddress addr(address);
    bool resultado = false;

    if(checagem == "checkSum")
    {
        QTcpServer* recebeChecksum = new QTcpServer();
        recebeChecksum->listen(addr,_porta);
        emit leituraTerminada();

        if(!recebeChecksum->waitForNewConnection(3000))
        {
            _status->setText("Checksum nao recebido");
            return resultado;
        }

        char *checkSum2 = new char(qChecksum(full_data, full_data.size()));

        QTcpSocket *temporario = new QTcpSocket();
        QByteArray bCheckSum;

        temporario = recebeChecksum->nextPendingConnection();
        temporario->waitForReadyRead(3000);

        bCheckSum = temporario->readAll();

        if(*checkSum2 != *bCheckSum.data())
        {
            _text->setText("Ip: " + Sender + "\n" + "Porta: " + Porta
                           + "\n" + "Recebidos: " + QVariant(dadosRecebidos).toString() + " bytes\n"
                           + "Checksum nao confere");

        }
        else
        {
            _text->setText("Ip: " + Sender + "\n" + "Porta: " + Porta
                           + "\n" + "Recebidos: " + QVariant(dadosRecebidos).toString() + " bytes\n"
                           + "Checksum confere");
            resultado = true;
        }

        temporario->close();
        recebeChecksum->close();

        temporario->deleteLater();
        recebeChecksum->deleteLater();

        delete(checkSum2);

    }
    else if(checagem == "CRC")
    {
        QTcpServer* recebeChecksum = new QTcpServer();
        recebeChecksum->listen(addr,_porta);
        emit leituraTerminada();

        if(!recebeChecksum->waitForNewConnection(3000))
        {
            _status->setText("CRC nao recebido");
            return resultado;
        }

        char *crc2 = new char(CRC::Calculate(full_data.data(), full_data.size(),CRC::CRC_32()));

        QTcpSocket *temporario = new QTcpSocket();
        QByteArray bCrc;

        temporario = recebeChecksum->nextPendingConnection();
        temporario->waitForReadyRead(3000);

        bCrc = temporario->readAll();

        if(*crc2 != *bCrc.data())
        {
            _text->setText("Ip: " + Sender + "\n" + "Porta: " + Porta
                           + "\n" + "Recebidos: " + QVariant(dadosRecebidos).toString() + " bytes\n"
                           + "CRC nao confere");

        }
        else
        {
            _text->setText("Ip: " + Sender + "\n" + "Porta: " + Porta
                           + "\n" + "Recebidos: " + QVariant(dadosRecebidos).toString() + " bytes\n"
                           + "CRC confere");
            resultado = true;
        }

        temporario->close();
        recebeChecksum->close();

        temporario->deleteLater();
        recebeChecksum->deleteLater();

        delete(crc2);

    }
    else
        return resultado;

    return resultado;
}

void ServidorUDP::readPendingDatagrams()
{
    QHostAddress addr;
    quint16 porta;
    int dadosRecebidos = 0, temp = 0;
    _status->setText("Lendo Dados");
    QByteArray dados = 0;

    while(udpSocket->hasPendingDatagrams())
    {
        dados.resize(udpSocket->pendingDatagramSize());
        temp = udpSocket->readDatagram(dados.data(),dados.size(),&addr,&porta);
        dadosRecebidos += temp;

        full_data.push_back(dados);
    }

    QString Sender = addr.toString();
    QString Porta = QVariant(porta).toString();
    _text->setText("Ip: " + Sender + "\n" + "Porta: " + Porta
                   + "\n" + "Recebidos: " + QVariant(dadosRecebidos).toString() + " bytes");

     _status->setText("Dados lidos");


    if(this->recebeCheckSum(dadosRecebidos, Sender, Porta ))
        this->mostraArquivo();

    this->salvaArquivo();

}


void ServidorUDP::salvaArquivo()
{


    QFile file(QFileDialog::getSaveFileName(NULL,tr("Save File")));

    if(!file.fileName().isEmpty())
    {
        file.open(QIODevice::WriteOnly);
        file.write(full_data);

        file.waitForBytesWritten(1000);
        file.close();

    }

}

void ServidorUDP::mostraArquivo()
{
    QGraphicsScene *scene = new QGraphicsScene();
    if(_formato == "txt")
    {
        scene->addText(full_data);
    }
    else if(_formato == "png" || _formato == "jpeg" || _formato == "jpg ")
    {
        QPixmap p;
        p.loadFromData(full_data,"PNG");
        if(p.isNull())
            return;

        p = p.scaled(QSize(MThread::INTERFACE_W,MThread::INTERFACE_H),Qt::KeepAspectRatio);
        scene->addPixmap(p);
    }

    _disp->setScene(scene);
    scene->deleteLater();
}


void ServidorUDP::encerrar()
{
    if(udpSocket->isOpen())
        udpSocket->close();
    _status->setText("Encerrado");
}

//CRC code implemented by: https://github.com/d-bahr/CRCpp
