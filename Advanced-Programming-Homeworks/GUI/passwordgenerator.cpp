#include "passwordgenerator.h"
#include "ui_passwordgenerator.h"
#include <QString>

//cavitcakir_23657

PasswordGenerator::PasswordGenerator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PasswordGenerator)
{
    ui->setupUi(this);
    ui->strenghtBar->setRange(0,100);
    ui->lengthBox->setRange(4,40);
}

PasswordGenerator::~PasswordGenerator()
{
    delete ui;
}


QString upperString() // generates upper case letters
{
    QString str = QChar('A' + char(qrand() % ('Z' - 'A')));
    return str;
}

QString lowerString()  // generates lower case letters
{
    QString str = QChar('a' + char(qrand() % ('z' - 'a')));
    return str;
}

QString randNumber() // generates random number
{
    QString str = QChar('0' + char(qrand() % ('9' - '0')));
    return str;
}

void PasswordGenerator::on_pushButton_2_clicked()
{
    int lengthPass = ui->lengthBox->value();
    bool letters = ui->letterCheck->isChecked();
    bool numbers = ui->numberCheck->isChecked();
    QString password;

    if(letters && numbers) // if password will contain all possible characters
    {
        for(int i = 0;i<lengthPass;i++)
        {
            QString str = QChar('0' + char(qrand() % ('3' - '0')));
            if(str == "1")
            {
                password += upperString();
            }
            else if(str == "2")
            {
                password += lowerString();
            }
            else
            {
                password += randNumber();
            }
        }
    }
    else if(letters && !numbers) // if password will only contain letters
    {
        for(int i = 0;i<lengthPass;i++)
        {
            QString str = QChar('0' + char(qrand() % ('2' - '0')));
            if(str == "1")
            {
                password += upperString();
            }
            else
            {
                password += lowerString();
            }
        }
    }
    else if(!letters && numbers)  // if password will only contain numbers
    {
        for(int i = 0;i<lengthPass;i++)
        {
             password += randNumber();
        }
    }
    else // if password will not contain anything.
    {
        password = "";
    }

    ui->outPass->setText(password);
}

void PasswordGenerator::on_pushButton_clicked()
{
    QString a = ui->enteredPass->text();
    if(a.length()>14)
    {
        ui->strenghtBar->setValue(100);
        ui->percantage->setText("100%");
    }
    else if(a.length()>9)
    {
        ui->strenghtBar->setValue(75);
        ui->percantage->setText("75%");
    }
    else if(a.length()>4)
    {
        ui->strenghtBar->setValue(50);
        ui->percantage->setText("50%");
    }
    else
    {
        ui->strenghtBar->setValue(25);
        ui->percantage->setText("25%");
    }
}
