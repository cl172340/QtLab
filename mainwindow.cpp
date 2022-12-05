#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>
#include"QDebug"
#include"QPushButton"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug()<<"hello";



    btnNums={{Qt::Key_0,ui->btnNum0},
             {Qt::Key_1,ui->btnNum1},
             {Qt::Key_2,ui->btnNum2},
             {Qt::Key_3,ui->btnNum3},
             {Qt::Key_4,ui->btnNum4},
             {Qt::Key_5,ui->btnNum5},
             {Qt::Key_6,ui->btnNum6},
             {Qt::Key_7,ui->btnNum7},
             {Qt::Key_8,ui->btnNum8},
             {Qt::Key_9,ui->btnNum9},
            };
    foreach(auto btn,btnNums)
        connect(btn,SIGNAL(clicked()),this,SLOT(btnNumClicked()));

    //connect(ui->btnNum0,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    //connect(ui->btnNum1,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    //connect(ui->btnNum2,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    //connect(ui->btnNum3,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    //connect(ui->btnNum4,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    //connect(ui->btnNum5,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    //connect(ui->btnNum6,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    //connect(ui->btnNum7,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    //connect(ui->btnNum8,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    //connect(ui->btnNum9,SIGNAL(clicked()),this,SLOT(btnNumClicked()));

    connect(ui->btnMultiply,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));
    connect(ui->btnAdd,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));
    connect(ui->btnMinus,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));
    connect(ui->btnDivide,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));

    connect(ui->btnPercentage,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
    connect(ui->btnInverse,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
    connect(ui->btnSquare,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
    connect(ui->btnSqrt,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::calculation(bool *ok)
{
    double result=0;
    if(operands.size()==2 && opcodes.size()>0)
    {//取操作数
        double operand1= operands.front().toDouble();
        operands.pop_front();
        double operand2= operands.front().toDouble();
        operands.pop_front();
      //取操作符
        QString op= opcodes.front();
        opcodes.pop_front();

        if(op=="+")
        {
            result= operand1+operand2;
        }
        else if (op=="-") {
            result= operand1-operand2;
        }
        else if (op=="×") {
            result= operand1*operand2;
        }
        else if (op=="/") {
            result= operand1/operand2;
        }
        operands.push_back(QString::number(result));

        ui->statusbar->showMessage("c");
    }
    else
        ui->statusbar->showMessage(QString("operands is %1,opcodes is %2").arg(operands.size()).arg(opcodes.size()));
    return QString::number(result);
}


void MainWindow::btnNumClicked()
{
    QString digit=qobject_cast<QPushButton*>(sender())->text();

    if(digit=="0" && operand=="0")
            digit="";
    if(operand=="0" && digit!="0")
            operand="";
    operand+=digit;

    ui->display->setText(operand);
}


void MainWindow::on_btnPeriod_clicked()
{
    if(!operand.contains("."))
        operand +=qobject_cast<QPushButton*>(sender())->text();
    ui->display->setText(operand);
}


void MainWindow::on_btnDel_clicked()
{
    operand =operand.left(operand.length()-1);
    ui->display->setText(operand);
}


void MainWindow::on_btnClearAll_clicked()
{

}

void MainWindow::btnBinaryOperatorClicked()
{
    ui->statusbar->showMessage("last");
    QString opcode=qobject_cast<QPushButton*>(sender())->text();

    if(operand !="")
    {
        operands.push_back(operand);
        operand="";

        opcodes.push_back(opcode);
    QString result=calculation();

    ui->display->setText(result);
    }
}

void MainWindow::btnUnaryOperatorClicked()
{
    if(operand !="")
    {
        double result=operand.toDouble();
        operand="";

        QString op =qobject_cast<QPushButton*>(sender())->text();

        if(op=="%")
            result /=100.0;
        else if (op=="1/x")
            result=1/result;
        else if (op=="x^2")
            result*=result;
        else if (op=="√")
            result=sqrt(result);

        ui->display->setText(QString::number(result));
    }
}

void MainWindow::on_btnEqual_clicked()
{
    if(operand !="")
    {
        operands.push_back(operand);
        operand="";
    }
    QString result=calculation();

    ui->display->setText(result);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    foreach(auto btnKey, btnNums.keys())
    {
        if(event->key()==btnKey)
            btnNums[btnKey]->animateClick(100);
    }

    //if(event->key()==Qt::Key_0)
    // ui->btnNum0->animateClick(100);
    //else if(event->key()==Qt::Key_1)
    //ui->btnNum1->animateClick(100);
    if(event->key()==Qt::Key_Backspace)
        ui->btnDel->animateClick(100);
    if(event->key()==Qt::Key_Minus)
        ui->btnMinus->animateClick(100);
    if(event->key()==Qt::Key_Equal)
        ui->btnEqual->animateClick(100);
    if(event->key()==Qt::Key_Plus)
        ui->btnAdd->animateClick(100);
    if(event->key()==Qt::Key_Slash)
        ui->btnDivide->animateClick(100);
    if(event->key()==Qt::Key_Asterisk)
        ui->btnMultiply->animateClick(100);
    if(event->key()==Qt::Key_Period)
        ui->btnPeriod->animateClick(100);
    if(event->key()==Qt::Key_Percent)
        ui->btnPercentage->animateClick(100);
}


void MainWindow::on_btnClear_clicked()
{
    operand.clear();
    ui->display->setText(operand);
}


void MainWindow::on_btnPlus_clicked()
{

}

