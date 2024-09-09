#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include <QDialog>


namespace Ui {
class ConnectDialog;
}

class ConnectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectDialog(QString *ip1, quint16 *port1, QString *ip2, quint16 *port2, QString *savepath, bool *sended, QWidget *parent = nullptr);
    ~ConnectDialog();

signals:
    void connect1SucSig();
    void connect2SucSig();
    void state1Sig(QString text);
    void state2Sig(QString text);
    void close1Sig();
    void close2Sig();
    void endrev1Sig(QString title, QString text);
    void endrev2Sig(QString title, QString text);
    void outputDat1NameSig(QString name);
    void outputDat2NameSig(QString name);
    void deleteSig();


private slots:

    void on_pushButton_connect_clicked();

    void on_pushButton_recssave_clicked();

private:
    Ui::ConnectDialog *ui;

    QString *ip1, *ip2,  *savepath;
    quint16 *port1, *port2;
    bool *sended;
    bool isConfiged = false;
    bool RecSuccessed = false;      //回放 / 实时 标志
};

#endif // CONNECTDIALOG_H
