#include "connectdialog.h"
#include "ui_connectdialog.h"

#include <QFileDialog>
#include <QIntValidator>
#include <QMessageBox>
#include <QCloseEvent>

ConnectDialog::ConnectDialog(QString *ip1, quint16 *port1, QString *ip2, quint16 *port2, QString *savepath, bool *sended, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectDialog),ip1(ip1),ip2(ip2), savepath(savepath),port1(port1),port2(port2), sended(sended)
{
    ui->setupUi(this);
    setWindowTitle("连接请求");
    if(ui->lineEdit_recpath->text().isEmpty())
    {
        ui->pushButton_connect->setEnabled(false);
    }


    if(!(ui->lineEdit_recpath->text() == NULL))
    {
        isConfiged = true;
        *savepath = ui->lineEdit_recpath->text();
    }

}

ConnectDialog::~ConnectDialog()
{
    delete ui;
}

//连接
void ConnectDialog::on_pushButton_connect_clicked()
{
    if(isConfiged || !(ui->lineEdit_recpath->text() == NULL))
    {
        QString iptemp1 = ui->lineEdit_ipaddress1->text();
        QString porttemp1 = ui->lineEdit_port1->text();
        QString iptemp2 = ui->lineEdit_ipaddress2->text();
        QString porttemp2 = ui->lineEdit_port2->text();

        *ip1 = iptemp1;
        *port1 = porttemp1.toInt();
        *ip2 = iptemp2;
        *port2 = porttemp2.toInt();

        *sended = true;
        accept();
    }
    else
    {
        QMessageBox::warning(this, "警告", "未填写接收地址！");
    }
}

void ConnectDialog::on_pushButton_recssave_clicked()
{
    *savepath = QFileDialog::getExistingDirectory(this, "保存路径", "./", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->lineEdit_recpath->setText(*savepath);
    if(!(ui->lineEdit_recpath->text() == NULL))
     {
        isConfiged = true;
        ui->pushButton_connect->setEnabled(true);
     }
    else
        isConfiged = false;
}

