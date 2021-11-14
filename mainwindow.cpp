#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QToolBar"
#include "QTextEdit"
#include <iostream>
#include "QFileDialog"
#include "QFile"
#include "QTextStream"
#include "QMessageBox"
#include <QCloseEvent>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    auto* menubar = this->menuBar();
    auto* menu = menubar->addMenu(tr("&File"));
    //auto* tools = menubar->addMenu(tr("&Tools"));
    //auto* shape = menubar->addMenu(tr("&Shape"));

    QAction* action1 = new QAction(QIcon(":/images/open.png"),tr("&Open"),this);
    QAction* action2 = new QAction(QIcon(":/images/save.png"),tr("&Save"),this);
    QAction* action3 = new QAction(QIcon(":/images/quit.png"),tr("&Quit"),this);
    QAction* action4 = new QAction(QIcon(":/images/edit.png"), tr("&Edit"),this);

    menu->addAction(action1);
    menu->addAction(action2);
    menu->addAction(action3);
    menu->addAction(action4);

    connect(action1,SIGNAL(triggered()),this,SLOT(openFile()));
    connect(action2,SIGNAL(triggered()),this,SLOT(saveFile()));
    connect(action3,SIGNAL(triggered()),this,SLOT(quitApp()));
    connect(action4,SIGNAL(triggered()),this,SLOT(editShape()));

    action1->setShortcut((tr("Ctrl+O")));
    action1->setToolTip(tr("Open"));
    action1->setStatusTip(tr("Open"));

    action2->setShortcut((tr("Ctrl+S")));
    action2->setToolTip(tr("Save"));
    action2->setStatusTip(tr("Save"));

    action3->setShortcut((tr("Ctrl+Q")));
    action3->setToolTip(tr("Quit"));
    action3->setStatusTip(tr("Quit"));

    action4->setShortcut((tr("Ctrl+E")));
    action4->setToolTip(tr("Edit"));
    action4->setStatusTip(tr("Edit"));
    /*
    auto* thicknessMenu = new QMenu(tr("&Thickness"));
    auto* colorMenu = new QMenu(tr("&Color"));
    auto* styleMenu = new QMenu(tr("&Style"));

    tools->addMenu(thicknessMenu);
    tools->addMenu(colorMenu);
    tools->addMenu(styleMenu);

    QAction* color1 = new QAction(tr("&Black"),this);
    QAction* color2 = new QAction(tr("&Blue"),this);
    QAction* color3 = new QAction(tr("&Red"),this);
    QAction* color4 = new QAction(tr("&Green"),this);

    colorMenu->addAction(color1);
    colorMenu->addAction(color2);
    colorMenu->addAction(color3);
    colorMenu->addAction(color4);



    connect(color1,&QAction::triggered,[this]{set_color(Qt::black);});
    connect(color2,&QAction::triggered,[this]{set_color(Qt::blue);});
    connect(color3,&QAction::triggered,[this]{set_color(Qt::red);});
    connect(color4,&QAction::triggered,[this]{set_color(Qt::green);});

    QAction* thickness1 = new QAction(tr("&Thin"),this);
    QAction* thickness2 = new QAction(tr("&Medium"),this);
    QAction* thickness3 = new QAction(tr("&Large"),this);

    thicknessMenu->addAction(thickness1);
    thicknessMenu->addAction(thickness2);
    thicknessMenu->addAction(thickness3);

    connect(thickness1,&QAction::triggered,[this]{set_thickness(1);});
    connect(thickness2,&QAction::triggered,[this]{set_thickness(2);});
    connect(thickness3,&QAction::triggered,[this]{set_thickness(3);});

    QAction* style1 = new QAction(tr("&Solid"),this);
    QAction* style2 = new QAction(tr("&Dash"),this);
    QAction* style3 = new QAction(tr("&Dot"),this);

    styleMenu->addAction(style1);
    styleMenu->addAction(style2);
    styleMenu->addAction(style3);

    connect(style1,&QAction::triggered,[this]{set_style(Qt::SolidLine);});
    connect(style2,&QAction::triggered,[this]{set_style(Qt::DashLine);});
    connect(style3,&QAction::triggered,[this]{set_style(Qt::DotLine);});*/

    auto* toolbar = this->addToolBar((tr("File")));
    toolbar->addAction(action1);
    toolbar->addAction(action2);
    toolbar->addAction(action3);
    toolbar->addAction(action4);
    /*
    QAction* lineAction = new QAction(tr("&Line"),this);
    QAction* rectAction = new QAction(tr("&Rectangle"),this);
    QAction* ellipseAction = new QAction(tr("&Ellipse"),this);

    shape->addAction(lineAction);
    shape->addAction(rectAction);
    shape->addAction(ellipseAction);

    connect(lineAction,&QAction::triggered,[this]{set_shape("line");});
    connect(rectAction,&QAction::triggered,[this]{set_shape("rectangle");});
    connect(ellipseAction,&QAction::triggered,[this]{set_shape("ellipse");});
    */
    QGraphicsScene* scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));

    QGraphicsScene* scene2 = new QGraphicsScene();
    ui->graphicsView_2->setScene(scene2);
    ui->graphicsView_2->setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::openFile(){
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open File"),
                                                    "D:/Dev",
                                                    tr("Text Files(*.txt)")
                                                    );
    QFile file(fileName);

    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "error opening file: " << file.error();
        return;
    }

    QTextStream instream(&file);
    QString content = instream.readAll();

    text->setHtml(content);

    file.close();
}
void MainWindow::saveFile(){
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Open File"),
                                                    "D:/Dev",
                                                    tr("Text Files(*.txt)")
                                                    );
    QFile file(fileName);
    if(file.open(QIODevice::WriteOnly))
          {
              QTextStream stream(&file);

              stream << text->toPlainText();

              file.close();
          }

}
void MainWindow::quitApp(){
    QApplication::quit();
}


void MainWindow::closeEvent (QCloseEvent *event)
{
    QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "Test", "Quit?",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply != QMessageBox::Yes) {
              event->ignore();
          } else {
              event->accept();
          }
}
void MainWindow::set_thickness(int size){
    ui->canvas->set_thickness(size);
}
void MainWindow::set_color(QColor color){
    ui->canvas->set_color(color);
}
void MainWindow::set_style(Qt::PenStyle style){
    ui->canvas->set_style(style);
}
void MainWindow::set_shape(std::string shape){
    ui->canvas->set_shape(shape);
}

void MainWindow::editShape(){
    ui->canvas->editShape();
    edit = not edit;
    ui->horizontalSlider_10->setValue(0);
    ui->horizontalSlider_11->setValue(0);
    ui->horizontalSlider_12->setValue(0);
    ui->horizontalSlider_9->setValue(2);
    ui->horizontalSlider_13->setValue(50);
    ui->radioButton_7->setChecked(true);
    ui->radioButton_8->setChecked(false);
    ui->radioButton_9->setChecked(false);
    if (edit) ui->tabWidget->setCurrentIndex(1);
    if(not edit) ui->tabWidget->setCurrentIndex(0);
}




void MainWindow::on_radioButton_toggled(bool checked)
{
    if(checked) set_shape("line");
}


void MainWindow::on_radioButton_3_toggled(bool checked)
{
    if(checked) set_shape("rectangle");
}


void MainWindow::on_radioButton_2_toggled(bool checked)
{
    if(checked) set_shape("ellipse");
}


void MainWindow::on_radioButton_4_toggled(bool checked)
{
    if(checked) set_style(Qt::SolidLine);
}


void MainWindow::on_radioButton_5_toggled(bool checked)
{
     if(checked) set_style(Qt::DashLine);
}


void MainWindow::on_radioButton_6_toggled(bool checked)
{
    if(checked) set_style(Qt::DotLine);
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    set_thickness(value);
}




void MainWindow::on_horizontalSlider_3_valueChanged(int value)
{
    set_color(QColor(value,gColor,bColor));
    rColor=value;
    ui->graphicsView->setBackgroundBrush(QBrush(QColor(value,gColor,bColor), Qt::SolidPattern));
}


void MainWindow::on_horizontalSlider_4_valueChanged(int value)
{
    set_color(QColor(rColor,value,bColor));
    gColor=value;
    ui->graphicsView->setBackgroundBrush(QBrush(QColor(rColor,value,bColor), Qt::SolidPattern));
}


void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    set_color(QColor(rColor,gColor,value));
    bColor=value;
    ui->graphicsView->setBackgroundBrush(QBrush(QColor(rColor,gColor,value), Qt::SolidPattern));
}





void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    if(index==0) edit=true;
    if(index==1) edit = false;
    editShape();
}


void MainWindow::on_radioButton_7_toggled(bool checked)
{
    if(checked) editStyle(Qt::SolidLine);
}


void MainWindow::on_radioButton_8_toggled(bool checked)
{
    if(checked) editStyle(Qt::DashLine);
}


void MainWindow::on_radioButton_9_toggled(bool checked)
{
    if(checked) editStyle(Qt::DotLine);
}

void MainWindow::editStyle(Qt::PenStyle style) {
    ui->canvas->editStyle(style);
}

void MainWindow::on_pushButton_clicked()
{
    ui->canvas->editSelection();
}


void MainWindow::on_horizontalSlider_9_valueChanged(int value)
{
    ui->canvas->editSize(value);
}


void MainWindow::on_horizontalSlider_10_valueChanged(int value)
{
    ui->canvas->editColor(QColor(value,edit_gColor,edit_bColor));
    edit_rColor=value;
    ui->graphicsView_2->setBackgroundBrush(QBrush(QColor(value,edit_gColor,edit_bColor), Qt::SolidPattern));
}


void MainWindow::on_horizontalSlider_11_valueChanged(int value)
{
    ui->canvas->editColor(QColor(edit_rColor,value,edit_bColor));
    edit_gColor=value;
    ui->graphicsView_2->setBackgroundBrush(QBrush(QColor(edit_rColor,value,edit_bColor), Qt::SolidPattern));
}


void MainWindow::on_horizontalSlider_12_valueChanged(int value)
{
    ui->canvas->editColor(QColor(edit_rColor,edit_gColor,value));
    edit_bColor=value;
    ui->graphicsView_2->setBackgroundBrush(QBrush(QColor(edit_rColor,edit_gColor,value), Qt::SolidPattern));
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->canvas->scaleDefinitive();
}


void MainWindow::on_horizontalSlider_13_valueChanged(int value)
{
    ui->canvas->scaleSelection(value);
}

