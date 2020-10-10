#ifndef PASSWORDGENERATOR_H
#define PASSWORDGENERATOR_H

#include <QMainWindow>

namespace Ui {
class PasswordGenerator;
}

class PasswordGenerator : public QMainWindow
{
    Q_OBJECT

public:
    explicit PasswordGenerator(QWidget *parent = 0);
    ~PasswordGenerator();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::PasswordGenerator *ui;
};

#endif // PASSWORDGENERATOR_H
