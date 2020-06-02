#include "ui_fileexplorer.h"
#include "fileexplorer.h"
#include "TextEditor.h"
#include "properties.h"
#include <iostream>

fileexplorer::fileexplorer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::fileexplorer)
{
    ui->setupUi(this);
    setWindowTitle("File Explorer");

    // set right click actions
    open_action = new QAction("open");
    delete_action = new QAction("delete");
    create_file_action = new QAction("create file");
    create_dir_action = new QAction("create directoriy");
    properties_action = new QAction("properties");
    rename_action = new QAction("rename");

    // version label
    QString labeltext = QString::fromStdString("version:"+fs.ver);
    ui->label->setText(labeltext);

    // connects
    connect(open_action, SIGNAL(triggered()), this, SLOT(open_action_slot()));
    connect(create_file_action, SIGNAL(triggered()), this, SLOT(create_file_action_slot()));
    connect(create_dir_action, SIGNAL(triggered()), this, SLOT(create_dir_action_slot()));
    connect(delete_action, SIGNAL(triggered()), this, SLOT(delete_action_slot()));
    connect(properties_action, SIGNAL(triggered()), this, SLOT(properties_action_slot()));
    connect(rename_action, SIGNAL(triggered()), this, SLOT(rename_action_slot()));

    // shortcuts

    // initiallize
    this->l.set(ui->plainTextEdit);
    this->fs.l = this->l;

}

fileexplorer::~fileexplorer()
{
    delete ui;
}

void fileexplorer::on_BackButton_clicked()
{
    std::cout << "BackButton Clicked" << std::endl;
    this->fs.cd("..");
    updateDirView();
}

void fileexplorer::on_MountButton_clicked()
{
    std::cout << "MountButton Clicked" << std::endl;
    bool isOk;
    QString filePath = QInputDialog::getText(this, "Input", "Please input the absolute path of the disk", QLineEdit::Normal, NULL, &isOk);
    if(isOk) {
        QString driveLetter = QInputDialog::getText(this, "Input", "Please input the drive letter of the disk", QLineEdit::Normal, NULL, &isOk);
        if(isOk) {
            this->fs.mount(filePath.toStdString(), driveLetter.toStdString());
        };
    };
    updateDirView();
};

void fileexplorer::on_UnmountButton_clicked() {
    std::cout << "UnmountButton clicked" << std::endl;
    bool isOk;
    QString driveLetter = QInputDialog::getText(this, "Input", "Please input the drive letter of the disk that you want to unmount", QLineEdit::Normal, NULL, &isOk);
    if(isOk) {
        this->fs.unmount(driveLetter.toStdString());
    };
};

void fileexplorer::on_FormatButton_clicked()
{
    std::cout << "FormatButton Clicked" << std::endl;
    bool isOk;
    QString driveletter = QInputDialog::getText(this, "Input", "Please input the drive letter of the drive you want to format", QLineEdit::Normal, NULL, &isOk);
    if(isOk) {
        QString confirm_message = QInputDialog::getText(this, "Input", "Type \"I confirm to format the disk\" to confirm", QLineEdit::Normal, NULL, &isOk);
        if(isOk) {
            if (confirm_message == "I confirm to format the disk") {
                this->fs.format(driveletter.toStdString());
            };
        };
    };
    updateDirView();
};

void fileexplorer::on_CopyInButton_clicked()
{
    std::cout << "CopyInButton Clicked" << std::endl;
    bool isOk;
    QString externalpath = QInputDialog::getText(this, "Input", "Please input the absolute external path", QLineEdit::Normal, NULL, &isOk);
    if(isOk) {
        QString filename = QInputDialog::getText(this, "Input", "Please input the name of the file", QLineEdit::Normal, NULL, &isOk);
        if(isOk) {
            this->fs.copyin(externalpath.toStdString(), filename.toStdString());
        };
    };
    updateDirView();
};

void fileexplorer::on_CopyOutButton_clicked()
{
    std::cout << "CopyOutButton Clicked" << std::endl;
    bool isOk;
    QString externalpath = QInputDialog::getText(this, "Input", "Please input the absolute external path", QLineEdit::Normal, NULL, &isOk);
    if(isOk) {
        QString filename = QInputDialog::getText(this, "Input", "Please input the name of the file", QLineEdit::Normal, NULL, &isOk);
        if(isOk) {
            this->fs.copyout(filename.toStdString(), externalpath.toStdString());
        };
    };
    updateDirView();
};

void fileexplorer::on_ExecuteButton_clicked() {
    this->fs.execute(ui->lineEdit->text().toStdString());
    ui->lineEdit->clear();
    updateDirView();
};

void fileexplorer::on_lineEdit_returnPressed() {
    this->fs.execute(ui->lineEdit->text().toStdString());
    ui->lineEdit->clear();
    updateDirView();
};

void fileexplorer::on_comboBox_activated(const QString &arg1) {
    this->fs.chdisk(arg1.toStdString());
    updateDirView();
};

void fileexplorer::contextMenuEvent(QContextMenuEvent *e)
{
    QMenu* menu = new QMenu(this);
    menu->addAction(open_action);
    menu->addAction(delete_action);
    menu->addSeparator();
    menu->addAction(create_file_action);
    menu->addAction(create_dir_action);
    menu->addSeparator();
    menu->addAction(rename_action);
    menu->addSeparator();
    menu->addAction(properties_action);

    menu->show();
    menu->exec(QCursor::pos());
    delete menu;
};

void fileexplorer::updateDirView() {
    ui->listWidget->clear();
    vector<vector<string>> directories = this->fs.directory();
    for(size_t i = 0; i != directories.size(); i++) {
        QListWidgetItem* item =  new QListWidgetItem;
        item->setText(QString::fromStdString(directories[i][1]));
        if(directories[i][0] == "FILE") {
            item->setIcon(QIcon(":/image/icon/file.ico"));
        } else if(directories[i][0] == "DIR") {
            item->setIcon(QIcon(":/image/icon/dir.ico"));
        };
        ui->listWidget->addItem(item);
    };
    ui->comboBox->clear();
    vector<string> disklist = this->fs.disklist();
    QStringList strlist;
    for (size_t i=0; i<disklist.size(); i++) {
        string text = disklist[i];
        strlist << QString::fromStdString(text);
    };
    ui->comboBox->addItems(strlist);
};

void fileexplorer::open_action_slot() {
    std::cout << "open action" << std::endl;
    vector<vector<string>> directories = this->fs.directory();
    QListWidgetItem* item = ui->listWidget->currentItem();
    string filename = item->data(0).toString().toStdString();
    if(item == NULL) {
        return;
    } else {
        for(size_t i = 0; i != directories.size(); i++) {
            if (directories[i][1] == filename) {
                if(directories[i][0] == "FILE") {
                    string text = this->fs.open(filename);
                    Qt::WindowFlags m_flags = windowFlags();
                    TextEditor *te = new TextEditor(this);
                    te->setWindowFlags(m_flags | Qt::WindowStaysOnTopHint);
                    te->setWindowModality(Qt::ApplicationModal);
                    te->receiveOriginalText(text, filename);
                    connect(te, SIGNAL(sendText(QVector<QString>)), this, SLOT(receiveText(QVector<QString>)));
                    te->show();
                } else if(directories[i][0] == "DIR") {
                    this->fs.cd(filename);
                };
            };
        };
    };
    updateDirView();
};

void fileexplorer::delete_action_slot() {
    std::cout << "delete action" << std::endl;
    vector<vector<string>> directories = this->fs.directory();
    QListWidgetItem* item = ui->listWidget->currentItem();
    string filename = item->data(0).toString().toStdString();
    if(item == NULL) {
        return;
    } else {
        for(size_t i = 0; i != directories.size(); i++) {
            if (directories[i][1] == filename) {
                if(directories[i][0] == "FILE") {
                    this->fs._delete(filename);
                } else if(directories[i][0] == "DIR") {
                    this->fs.rd(filename);
                };
            };
        };
    };
    updateDirView();
};

void fileexplorer::create_file_action_slot() {
    std::cout << "create file action" << std::endl;
    bool isOk;
    QString fileName = QInputDialog::getText(this, "Input", "Please input the file's name", QLineEdit::Normal, NULL, &isOk);
    if(isOk) {
        this->fs.create(fileName.toStdString());
    };
    updateDirView();
};

void fileexplorer::create_dir_action_slot() {
    std::cout << "create dir action" << std::endl;
    bool isOk;
    QString directoryName = QInputDialog::getText(this, "Input", "Please input the directory's name", QLineEdit::Normal, NULL, &isOk);
    if(isOk) {
        this->fs.md(directoryName.toStdString());
    };
    updateDirView();
};

void fileexplorer::rename_action_slot() {
    std::cout << "rename action" << std::endl;
    QListWidgetItem* item = ui->listWidget->currentItem();
    bool isOk;
    QString newName = QInputDialog::getText(this, "Input", "Please input the new name", QLineEdit::Normal, NULL, &isOk);
    if(isOk) {
        this->fs.rename(item->text().toStdString(), newName.toStdString());
    };
    updateDirView();
};

void fileexplorer::properties_action_slot() {
    std::cout << "properties action" << std::endl;
    QListWidgetItem* item = ui->listWidget->currentItem();
    Qt::WindowFlags m_flags = windowFlags();
    properties *p = new properties(this);
    p->setWindowFlags(m_flags | Qt::WindowStaysOnTopHint);
    p->setWindowModality(Qt::ApplicationModal);
    p->set_attrs(this->fs.getattr(item->text().toStdString()));
    p->show();
    connect(p, SIGNAL(sendAttrs(QVector<QString>)), this, SLOT(receiveAttr(QVector<QString>)));

    updateDirView();
};

void fileexplorer::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    vector<vector<string>> directories = this->fs.directory();
    string filename = item->data(0).toString().toStdString();
    for(size_t i = 0; i != directories.size(); i++) {
        if (directories[i][1] == filename) {
            if(directories[i][0] == "FILE") {
                string text = this->fs.open(filename);
                Qt::WindowFlags m_flags = windowFlags();
                TextEditor *te = new TextEditor(this);
                te->setWindowFlags(m_flags | Qt::WindowStaysOnTopHint);
                te->setWindowModality(Qt::ApplicationModal);
                te->receiveOriginalText(text, filename);
                connect(te, SIGNAL(sendText(QVector<QString>)), this, SLOT(receiveText(QVector<QString>)));
                te->show();
            } else if(directories[i][0] == "DIR") {
                this->fs.cd(filename);
            };
        };
    };
    updateDirView();
};

void fileexplorer::receiveText(QVector<QString> data) {
    this->fs.receive(data[1].toStdString(), data[0].toStdString());
};

void fileexplorer::receiveAttr(QVector<QString> attrs) {
    vector<string> stdattrs;
    for (int i = 0; i<attrs.size(); i++) {
        stdattrs.push_back(attrs[i].toStdString());
    };
    this->fs.setattr(stdattrs[stdattrs.size()-1], stdattrs);
};
