#include "calculator.h"
#include "ui_calculator.h"
#include <QRegularExpression>

double calcVal = 0.0; //current value of calculations
bool divTrigger = false;
bool multTrigger = false;
bool addTrigger = false;
bool subTrigger = false;


Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);

    ui->Display->setText(QString::number(calcVal));
    QPushButton *numButtons[10];
    for(int i = 0; i<10;++i){
        QString butName = "Button"+QString::number(i);
        numButtons[i] = Calculator::findChild<QPushButton *>(butName);
        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumPressed()));// When the button is released call num_pressed()
    }
    connect(ui->Add, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Subtract, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Multiply, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Divide, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Equals, SIGNAL(released()), this, SLOT(EqualButtonPressed()));
    connect(ui->ChangeSign, SIGNAL(released()), this, SLOT(ChangeNumberSign()));
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::NumPressed(){
    QPushButton *button = (QPushButton *)sender(); //sender returns a pointer to the button pressed
    QString butVal = button->text(); //get the number on the button
    QString displayVal = ui->Display->text(); //get the value in the display
    if((displayVal.toDouble()==0)||(displayVal.toDouble()==0.0)){
        ui->Display->setText((butVal));

    }
    else{
        QString newVal = displayVal + butVal; //put the new number to the right of whats there
        double dblNewVal = newVal.toDouble();
        ui->Display->setText(QString::number(dblNewVal, 'g', 16)); //set the value in the display and allow up to 16 digits b4 using exponents
    }
}

void Calculator::MathButtonPressed(){
    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;

    QString displayVal = ui->Display->text();
    calcVal = displayVal.toDouble();
    QPushButton *button = (QPushButton *)sender(); //sender returns a pointer to the button pressed
    QString butVal = button->text();
    if(QString::compare(butVal, "/", Qt::CaseInsensitive)==0){
        //we have a match
        divTrigger = true;
    }
    else if(QString::compare(butVal, "*", Qt::CaseInsensitive)==0){
        //we have a match
        multTrigger = true;
    }
    else if(QString::compare(butVal, "+", Qt::CaseInsensitive)==0){
        //we have a match
        addTrigger = true;
    }
    else{
        subTrigger = true;
    }
    ui->Display->setText("");

}

void Calculator::EqualButtonPressed(){
    double solution = 0.0;
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    if(addTrigger||subTrigger||multTrigger||divTrigger){
        if(addTrigger){
            solution = calcVal + dblDisplayVal;
        }
        else if(subTrigger){
            solution = calcVal - dblDisplayVal;
        }
        else if(multTrigger){
            solution = calcVal * dblDisplayVal;
        }
        else{
            solution = calcVal / dblDisplayVal;
        }

    }
    ui->Display->setText(QString::number(solution));
}

void Calculator::ChangeNumberSign() {

    QString displayVal = ui->Display->text();
    QRegularExpression reg("[-]?[0-9.]*");
    QRegularExpressionMatch match = reg.match(displayVal);
    if(match.hasMatch()) {
        double dblDisplayVal = displayVal.toDouble();
        double dblDisplayValSign = -1 * dblDisplayVal;
        ui->Display->setText(QString::number(dblDisplayValSign));
    }

 }
