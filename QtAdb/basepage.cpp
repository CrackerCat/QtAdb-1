#include "basepage.h"
#include "ui_basepage.h"

basePage::basePage(QWidget *parent) :
    animationWidget(parent),
    ui(new Ui::basePage)
{
    ui->setupUi(this);
    SPManager = new sonPageManager;
    animation_listHide = new QPropertyAnimation(ui->listWidget,"geometry");
    parents = parent;

    lastPage = NULL;
    sonPage = NULL;
    /*
    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect();
    shadowEffect->setOffset(0,0);
    shadowEffect->setColor(Qt::gray);
    shadowEffect->setBlurRadius(10);*/

    //ui->listWidget->setGraphicsEffect(shadowEffect);
/*******原来的
    ui->listWidget->setStyleSheet("QListWidget{background-color:rgba(255,255,255,0);border-width:1px;border-radius:4px;outline:0px;}"
                                  "QListView::item:hover {"
                                  "background-color: rgba(250, 250, 250, 0.9);"
                                  "padding: 0px;"
                                  "border: 1px solid #BDBDBD;"
                                  "}"
                                  "QListView::item:selected {"
                                  "background-color: rgba(245, 245, 245, 0.9);"
                                  "color: black;"
                                  "padding: 0px;"
                                  "border: 2px solid #BDBDBD;"
                                  "}"
                                  "QListView::item{height:70px;border: 1px solid #BDBDBD;border-radius:4px;margin:6px 0px 0px 6px;}"
                                  );*/
    ui->listWidget->setStyleSheet("QListWidget{background-color:rgba(255,255,255,0);border:0px;border-radius:4px;outline:0px;}"
                                  "QListView::item:hover {"
                                  "background-color: #EEEEEE;"
                                  "padding: 0px;"
                                  "border: 0px solid #E0E0E0;"
                                  "}"
                                  "QListView::item:selected {"
                                  "background-color: #EEEEEE;"
                                  "color: black;"
                                  "padding: 0px;"
                                  "border: 0px solid #BDBDBD;"
                                  "}"
                                  "QListView::item{height:70px;border: 0px solid #BDBDBD;border-radius:4px;margin:6px 0px 0px 6px;}"
                                  );
    /*
     *
                                "QListWidget::item{background-color:rgba(255,255,255,0.9);border-color:rgba(255,255,255,0.9);border-width:0px;border-radius:4px;margin:4px 0px 0px 0px;}"
                                "QListWidget::item:hover{background-color:rgba(255,255,255,0.7);}"
                                "QListWidget::item::selected{background-color:rgba(255,255,255,0.5);color:black;}"
     * */
    ui->listWidget->setViewMode(QListView::ListMode);
    ui->listWidget->setFlow(QListView::TopToBottom);
    ui->listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    //ui->listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->listWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    QFile file("://qss/scrollbar.qss");
    file.open(QFile::ReadOnly);
    ui->listWidget->verticalScrollBar()->setStyleSheet(file.readAll());
    //QScroller::grabGesture(ui->listWidget,QScroller::LeftMouseButtonGesture);

    /*
    view->setViewMode(QListView::ListMode);
    view->setFlow(QListView::TopToBottom);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setHorizontalScrollMode(QListWidget::ScrollPerPixel);
    QScroller::grabGesture(view,QScroller::LeftMouseButtonGesture);
    */

    connect(ui->listWidget,SIGNAL(currentRowChanged(int)),this,SLOT(slot_createSonPage(int)));
    /*透明度动画
    exitOpacity = new QGraphicsOpacityEffect (this);//创建QGraphicsOpacityEffect对象关联控件ui.widgetProcess
    exitOpacity->setOpacity(1);//设置透明度为0，隐藏控件
    this->setGraphicsEffect(exitOpacity);//控件添加绘图效果*/

}

basePage::~basePage()
{
    qDebug() << "basepagepos = " << this->pos();
    //sleep(1000);
    //qDebug() << "~basePage" << "\n";
/*
    if(sonPage != NULL)
        sonPage->~basePage();*/

    //qDebug() << "~basePage deleted" << "\n";
    delete SPManager;
    delete ui;
    //qDebug() << "~basePage com" << "\n";
}
/*
void basePage::playExitAnimation()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this,"windowOpacity");
    animation->setDuration(1000);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
}
*/
void basePage::addItemsToList(pageListItem *itemWidget)
{
    QListWidgetItem *tmpItem = new QListWidgetItem();
    ui->listWidget->addItem(tmpItem);
    ui->listWidget->setItemWidget(tmpItem, itemWidget);
}

void basePage::setFather(QWidget *parent)
{
    father = parent;
}

void basePage::slot_createSonPage(int key)
{
    if(isEnable(key) && key >= 0)
    {
        this->setDisabled(true);

        listTimer = new QTimer(this);
        connect(listTimer, SIGNAL(timeout()), this, SLOT(slot_spgAnimationEnd()));
        listTimer->setSingleShot(true);
        listTimer->start(300);
        emit creatingSonPage();

        ui->listWidget->setCurrentRow(-1);
        //qDebug() << "dev of basePage = " << dev.addr;
        sonPage = SPManager->selector(this,whoAmI(),key,dev);
        if(sonPage != NULL)
        {
            //ui->listWidget->setVisible(false);

            /**/
            //sonPage->setVisible(false);


            animation_listHide->setDuration(300);
            animation_listHide->setEndValue(QRect(ui->listWidget->geometry().x(),ui->listWidget->geometry().y() + 50, ui->listWidget->width(),ui->listWidget->height()));
            animation_listHide->setStartValue(ui->listWidget->geometry());
            animation_listHide->setEasingCurve(QEasingCurve::OutQuart);
            animation_listHide->start();
            //sonPage->playLoadAnimation_sp();
            //animation->deleteLater();

            /*
    qDebug() << "wgtHeight = " << wgtHeight;
    if(parent->width() <= 600)
    {
        animation->setEndValue(QRect(301 - 30, 117 - 6 - 11, 600,wgtHeight));
    }
    else
    {
        animation->setEndValue(QRect(301 - 30, 117 - 6 - 11, parent->width(),wgtHeight));
    }
    //animation->setStartValue(QPoint(301 + 50,117));
    animation->setStartValue(QRect(301 + 50 - 30, 117 - 6 - 11, parent->width()-50,wgtHeight));

    animation->setEasingCurve(QEasingCurve::OutQuart);

    this->show();
    animation->start();
            */
            /**/
        }
    }
    ui->listWidget->setCurrentRow(-1);
}

void basePage::spg_return_pushed()
{
    sonPage->playExitAnimation_sp();
    QTimer *animationTimer = new QTimer(this);
    animationTimer->setSingleShot(true);
    animationTimer->start(300);
    connect(animationTimer, SIGNAL(timeout()), this, SLOT(slot_destroySonPage()));
}

void basePage::slot_destroySonPage()
{
    if(sonPage == NULL)
        throw "trying to destroy sonPage, but sonPage == NULL;";

    delete sonPage;
    sonPage = NULL;

    ui->listWidget->setVisible(true);
    playLoadAnimation_bp(this->height());
}

QString basePage::whoAmI()
{
    return myName;
}

void basePage::whoYouAre(QString name)
{
    myName = name;
}

void basePage::setEnableValue(int *val)
{
    for(int i = 0; i < 20 ; i++)
    {
        enableVal[i] = val[i];
    }
}

bool basePage::isEnable(int k)
{
    //qDebug() << "k=" << k;
    for(int i = 0; i < 20; i++)
    {
        if(enableVal[i] == k + 1)
            return true;
    }
    return false;
}

void basePage::setDev(device device)
{
    dev = device;
}

void basePage::self_castrate()
{
    delete ui->listWidget;
    delete ui->mainLayout;
    delete ui->verticalLayout;
}

void basePage::unlock()
{
    this->setDisabled(false);
}

void basePage::slot_spgAnimationEnd()
{
    ui->listWidget->setVisible(false);
    unlock();
    ui->mainLayout->addWidget(sonPage);
    sonPage->playLoadAnimation_sp(this->height());
    //sonPage->setVisible(true);
}
