#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);


}

Form::~Form()
{
    delete ui;
}

void Form::on_pushButton_clicked()
{
    look_zhiling();
    QString outputMessage = "执行了函数！";
    ui->textEdit->append(outputMessage);
//    ui->textEdit->acceptRichText();
//    ui->textEdit->setText(outputMessage);

    QString instructions;

    QString id1 = "001";
    QString name1 = "instruction1";
    QString cao1 = "cao1";
    instructions.append(id1 + "," + name1 + "," + cao1 + "\n");
}

