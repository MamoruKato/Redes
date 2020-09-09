#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QPixmap>
#include <QMainWindow>
#include <QTextEdit>
#include <QTextBlock>
#include <QString>
#include <QLineEdit>
#include <QFile>
#include <QApplication>
#include <QPushButton>
#include<QGraphicsView>
#include <QGraphicsScene>
#include <QFileDialog>
#include <QMessageBox>
#include <QBuffer>
#include "servidor.h"
#include "servidorudp.h"
#include "cliente.h"
#include "dialog.h"



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    static const int LOGO_W = 492;
    static const int LOGO_H = 211;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString metodoChecagem();

private slots:

    void on_start_clicked();

    void on_Sair_2_clicked();

    void on_Limpa_clicked();

    void on_Enviar_clicked();

    void on_Parar_clicked();

    void on_Encerrar_clicked();

    void on_Escutar_clicked();

    void on_comear_clicked();

    void on_Ajuda_clicked();

    void on_File_clicked();

public slots:
    void servidorFalhaConexao();
    void clienteFalhaConexao();
    void clienteEnviando();
    void clienteEnviado();
private:
    Ui::MainWindow *ui;
    QString _formato;
    QString _filename;
    Servidor *servidor1;
    ServidorUDP *servidorUdp1;
    Cliente *cliente1;
    QByteArray _dados;
    QString _protocol;
    QString _host;
    QString _hostc;
    int _porta;
    int _portac;

};

#endif // MAINWINDOW_H
