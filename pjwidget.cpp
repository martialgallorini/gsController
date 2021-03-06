#include "pjwidget.h"
#include "ui_pjwidget.h"
#include "projector.h"

pjWidget::pjWidget(qint16 _pid, QString _ip, quint16 _port, pjProtocol _protocol, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pjWidget)
{
    ui->setupUi(this);

    //create projector
    proj = new Projector(_ip, _port, _protocol, this);

    // set projector ID
    pid = _pid;
    connect(proj, SIGNAL(sigSocketConnected()), this, SLOT(pjConnected()));
    connect(proj, SIGNAL(sigSocketDisconnected()), this, SLOT(pjDisconnected()));
}

pjWidget::~pjWidget()
{
    delete proj;
    delete ui;
}

void pjWidget::setProjectorName(QString pjName)
{
    ui->selector->setText(pjName);
}

void pjWidget::selectProjector(bool checked)
{
    ui->selector->setChecked(checked);
}

bool pjWidget::isSelected()
{
    return ui->selector->isChecked();
}

QAbstractSocket::SocketState pjWidget::socketState()
{
    return proj->socketState();
}

void pjWidget::connection(QString ip, quint16 port)
{
    proj->connection(ip, port);
}

void pjWidget::closeConnection()
{
    proj->closeConnection();
}

QString pjWidget::getIp()
{
    return proj->ipAddr;
}

quint16 pjWidget::getPort()
{
    return proj->portNum;
}

void pjWidget::shutterOn()
{
    proj->shutterOn();
}

void pjWidget::shutterOff()
{
    proj->shutterOff();
}

void pjWidget::patternOn()
{
    proj->patternOn();
}

void pjWidget::patternOff()
{
    proj->patternOff();
}

void pjWidget::powerOn()
{
    proj->powerOn();
}

void pjWidget::powerOff()
{
    proj->powerOff();
}

void pjWidget::patternNext()
{
    proj->pgUpKey();
}

void pjWidget::patternPrev()
{
    proj->pgDownKey();
}



// SLOTS -----------------------------

void pjWidget::on_patternOn_clicked()
{
    proj->patternOn();
}

void pjWidget::on_patternOff_clicked()
{
    proj->patternOff();
}

void pjWidget::on_patternNext_clicked()
{
    proj->pgUpKey();
}

void pjWidget::on_patternPrev_clicked()
{
    proj->pgDownKey();
}

void pjWidget::on_mute_clicked()
{
    proj->shutterOn();
}

void pjWidget::on_unmute_clicked()
{
    proj->shutterOff();
}

void pjWidget::on_on_clicked()
{
    proj->powerOn();
}

void pjWidget::on_off_clicked()
{
    proj->powerOff();
}

void pjWidget::pjConnected()
{
    // set green icon
    ui->online_icon->setPixmap(QPixmap(":/icons/img/ok.png"));
    emit sigPjConnected();
}

void pjWidget::pjDisconnected()
{
    // set red icon
    ui->online_icon->setPixmap(QPixmap(":/icons/img/ko.png"));
    emit sigPjDisconnected();
}

