#include "sp_dpichanger.h"
#include "ui_sp_dpichanger.h"

sp_dpiChanger::sp_dpiChanger(QWidget *parent) :
    animationWidget(parent),
    ui(new Ui::sp_dpiChanger)
{
    ui->setupUi(this);

    process = new adbProcess;
    explainer = new textExplainer;

    connect(this->ui->back_to_basePage,SIGNAL(clicked()),parent,SLOT(slot_destroySonPage()));

    ui->verticalLayout->setAlignment(Qt::AlignVCenter);

    ui->back_to_basePage->setStyleSheet("QPushButton{background-color:rgba(255,255,255,0.9);border-radius:4px;border:0px;}"
                                        "QPushButton:hover{background-color:rgba(255,255,255,0.7);}"
                                        "QPushButton:pressed{background-color:rgba(255,255,255,0.6);}");
    ui->runBtn->setStyleSheet("QPushButton{background-color:rgba(255,255,255,0.9);border-radius:4px;border:0px;}"
                              "QPushButton:hover{background-color:rgba(255,255,255,0.7);}"
                              "QPushButton:pressed{background-color:rgba(255,255,255,0.6);}");
    /*
    ui->showOutputBtn->setStyleSheet("QPushButton{background-color:rgba(255,255,255,0.9);border-radius:4px;border:0px;}"
                                     "QPushButton:hover{background-color:rgba(255,255,255,0.7);}"
                                     "QPushButton:pressed{background-color:rgba(255,255,255,0.6);}");*/

    QGraphicsDropShadowEffect *shadowEffect_runBtn = new QGraphicsDropShadowEffect(this);
    //QGraphicsDropShadowEffect *shadowEffect_showOutputBtn = new QGraphicsDropShadowEffect(this);
    QGraphicsDropShadowEffect *shadowEffect_back_to_basePage = new QGraphicsDropShadowEffect(this);
    QGraphicsDropShadowEffect *shadowEffect_refreshBtn = new QGraphicsDropShadowEffect(this);

    QGraphicsDropShadowEffect *shadowEffect_dpiInfo = new QGraphicsDropShadowEffect(this);
    QGraphicsDropShadowEffect *shadowEffect_currentDpi = new QGraphicsDropShadowEffect(this);
    QGraphicsDropShadowEffect *shadowEffect_label3 = new QGraphicsDropShadowEffect(this);

    shadowEffect_runBtn->setOffset(0,0);
    shadowEffect_runBtn->setColor(Qt::gray);
    shadowEffect_runBtn->setBlurRadius(5);

    /*
    shadowEffect_showOutputBtn->setOffset(0,0);
    shadowEffect_showOutputBtn->setColor(Qt::gray);
    shadowEffect_showOutputBtn->setBlurRadius(5);*/

    shadowEffect_back_to_basePage->setOffset(0,0);
    shadowEffect_back_to_basePage->setColor(Qt::gray);
    shadowEffect_back_to_basePage->setBlurRadius(5);

    shadowEffect_refreshBtn->setOffset(0,0);
    shadowEffect_refreshBtn->setColor(Qt::gray);
    shadowEffect_refreshBtn->setBlurRadius(5);

    shadowEffect_dpiInfo->setOffset(0,0);
    shadowEffect_dpiInfo->setColor(Qt::gray);
    shadowEffect_dpiInfo->setBlurRadius(5);

    shadowEffect_currentDpi->setOffset(0,0);
    shadowEffect_currentDpi->setColor(Qt::gray);
    shadowEffect_currentDpi->setBlurRadius(5);

    shadowEffect_label3->setOffset(0,0);
    shadowEffect_label3->setColor(Qt::gray);
    shadowEffect_label3->setBlurRadius(5);

    ui->back_to_basePage->setGraphicsEffect(shadowEffect_back_to_basePage);
    ui->runBtn->setGraphicsEffect(shadowEffect_runBtn);
    //ui->showOutputBtn->setGraphicsEffect(shadowEffect_showOutputBtn);
    ui->refreshBtn->setGraphicsEffect(shadowEffect_refreshBtn);
    ui->dpiInfo->setGraphicsEffect(shadowEffect_dpiInfo);
    ui->currentDpi->setGraphicsEffect(shadowEffect_currentDpi);
    ui->label_3->setGraphicsEffect(shadowEffect_label3);
}

sp_dpiChanger::~sp_dpiChanger()
{
    delete ui;
}

void sp_dpiChanger::setDpiInfo()
{
    qDebug() << "dve of sonPage = " << dev.addr;
    QString profile = process->run("adb shell wm density", dev).replace("Physical density", "默认").replace("Override density","当前").simplified();
    qDebug() << "02" << profile;
    ui->dpiInfo->setText(profile);
}

void sp_dpiChanger::on_runBtn_clicked()
{
    if(ui->lineEdit->text().toInt()){
        QString output;
        this->setDisabled(true);
        output = process->run("adb shell wm density " + ui->lineEdit->text().simplified() , dev);

        this->setDisabled(false);
        //qDebug() << output;

        refresh();
        ui->lineEdit->setPlaceholderText("已修改");
    }
    else if(!ui->lineEdit->text().toInt())
    {
        ui->lineEdit->clear();
        ui->lineEdit->setPlaceholderText("输入无效");
    }
    else
    {
        ui->lineEdit->clear();
        ui->lineEdit->setPlaceholderText("error");
    }
}

void sp_dpiChanger::refresh()
{
    qDebug() << "refresh";
    setDpiInfo();
    ui->lineEdit->clear();
}

void sp_dpiChanger::on_refreshBtn_clicked()
{
    refresh();
}

void sp_dpiChanger::setDev(device device)
{
    qDebug() << "setDev";
    dev = device;
    setDpiInfo();
}
