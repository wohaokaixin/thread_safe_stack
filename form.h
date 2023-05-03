#ifndef FORM_H
#define FORM_H

#include <QMainWindow>
#include <QString>
#include "quanju_func.h"

namespace Ui {
class Form;
}

class Form : public QMainWindow
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();
    Ui::Form *ui;


private slots:
    void on_pushButton_clicked();

private:

};

#endif // FORM_H
