#include "lib/GUI/properties.h"
#include "ui_properties.h"
#include<vector>
#include<ctime>
#include<iostream>

properties::properties(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::properties)
{
    ui->setupUi(this);
    setWindowTitle("properties");
}

properties::~properties()
{
    delete ui;
}

void properties::on_buttonBox_accepted()
{
    QVector<QString> attrs;
    attrs.push_back(ui->name_lineEdit->text());
    attrs.push_back(ui->type_lineEdit->text());
    attrs.push_back(ui->readonly_lineEdit->text());
    attrs.push_back(ui->hidden_lineEdit->text());
    attrs.push_back(ui->system_lineEdit->text());
    attrs.push_back(ui->archive_lineEdit->text());
    time_t time = std::time(0);
    attrs.push_back(QString::fromStdString(std::to_string(time)));
    attrs.push_back(QString::fromStdString(this->filename));
    emit sendAttrs(attrs);
    // this->hide();
    this->close();
}

void properties::on_buttonBox_rejected()
{
    this->hide();
}

void properties::set_attrs(std::vector<std::string> attrs) {
    ui->name_lineEdit->setText(QString::fromStdString(attrs[0]));
    this->filename = attrs[0];
    ui->type_lineEdit->setText(QString::fromStdString(attrs[1]));
    ui->readonly_lineEdit->setText(QString::fromStdString(attrs[2]));
    ui->hidden_lineEdit->setText(QString::fromStdString(attrs[3]));
    ui->system_lineEdit->setText(QString::fromStdString(attrs[4]));
    ui->archive_lineEdit->setText(QString::fromStdString(attrs[5]));
    ui->creationtime_lineEdit->setText(QString::fromStdString(attrs[6]));
    ui->lastaccess_lineEdit->setText(QString::fromStdString(attrs[7]));
    ui->size_lineEdit->setText(QString::fromStdString(attrs[8]));
};

void properties::on_name_lineEdit_textChanged(const QString &arg1)
{
    if (arg1.toStdString().length() >= 1) {
        std::string new_string = arg1.toStdString().substr(0, 24);
        ui->name_lineEdit->setText(QString::fromStdString(new_string));
    };
};

void properties::on_readonly_lineEdit_textChanged(const QString &arg1)
{
    if (arg1.toStdString().length() >= 1) {
        std::string new_string = arg1.toStdString().substr(0, 1);
        ui->readonly_lineEdit->setText(QString::fromStdString(new_string));
    };
};

void properties::on_hidden_lineEdit_textChanged(const QString &arg1)
{
    if (arg1.toStdString().length() >= 1) {
        std::string new_string = arg1.toStdString().substr(0, 1);
        ui->hidden_lineEdit->setText(QString::fromStdString(new_string));
    };
};

void properties::on_system_lineEdit_textChanged(const QString &arg1)
{
    if (arg1.toStdString().length() >= 1) {
        std::string new_string = arg1.toStdString().substr(0, 1);
        ui->system_lineEdit->setText(QString::fromStdString(new_string));
    };
};

void properties::on_archive_lineEdit_textChanged(const QString &arg1)
{
    if (arg1.toStdString().length() >= 1) {
        std::string new_string = arg1.toStdString().substr(0, 1);
        ui->archive_lineEdit->setText(QString::fromStdString(new_string));
    };
};
