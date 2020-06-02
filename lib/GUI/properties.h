#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <QDialog>

namespace Ui {
class properties;
}

class properties : public QDialog
{
    Q_OBJECT

public:
    explicit properties(QWidget *parent = nullptr);
    void set_attrs(std::vector<std::string> attrs);
    std::string filename;
    ~properties();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

    void on_name_lineEdit_textChanged(const QString &arg1);
    void on_readonly_lineEdit_textChanged(const QString &arg1);
    void on_hidden_lineEdit_textChanged(const QString &arg1);
    void on_system_lineEdit_textChanged(const QString &arg1);
    void on_archive_lineEdit_textChanged(const QString &arg1);

signals:
    void sendAttrs(QVector<QString>);

private:
    Ui::properties *ui;
};

#endif // PROPERTIES_H
