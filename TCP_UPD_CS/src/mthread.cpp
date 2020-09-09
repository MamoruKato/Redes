#include "mthread.h"

MThread::MThread(int ID, QGraphicsView* _disp, QTextEdit *_interface, QLineEdit *_status, QString _formato, QObject *parent): QThread(parent)
{
    formato = _formato;
    disp = _disp;
    _pode = false;
    status = _status;
    interface = _interface;
    this->_socketDescriptor = ID;
}

MThread::~MThread()
{

}

void MThread::run()
{
    emit(escuta());

    exec();

}


int MThread::socketDescriptor()
{
    return this->_socketDescriptor;
}

void MThread::newSocket(QTcpSocket *_novo)
{
    socket = _novo;
}

void MThread::readyRead()
{
    status->setText("Lendo Dados");

    QByteArray dados(socket->readAll());

    QString Sender = socket->peerAddress().toString();
    QString Porta = QVariant(socket->peerPort()).toString();
    interface->setText("Ip: " + Sender + "\n" + "Porta: " + Porta + "\n");

    socket->write(dados);

    QGraphicsScene scene;
    if(formato == "txt")
    {
        scene.addText(dados);
    }
    else if(formato == "png" || formato == "jpeg" || formato == "jpg ")
    {
        QPixmap p;
        p.loadFromData(dados,"PNG");
        p = p.scaled(QSize(this->INTERFACE_W, this->INTERFACE_H),Qt::KeepAspectRatio);
        scene.addPixmap(p);
    }

    disp->setScene(&scene);

    status->setText("Dados lidos");

    QFile file(QFileDialog::getSaveFileName(NULL,tr("Save File")));

    if(!file.fileName().isEmpty())
    {
        file.open(QIODevice::WriteOnly);
        file.write(dados);

        file.waitForBytesWritten(1000);
        file.close();

    }
}



void MThread::disconnected()
{
    this->deleteLater();
    this->quit();
}
