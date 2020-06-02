#include "TextEditor.h"
#include "ui_mainwindow.h"
#include <QIcon>
#include <iostream>

TextEditor::TextEditor(QWidget *parent)
    : QMainWindow(parent)
{
    this->construct();
}

bool TextEditor::construct()
{
    bool ret = true;

    ret = ret && initMenuBar();
    ret = ret && initToolBar();
    ret = ret && initStatusBar();
    ret = ret && initinitMainEditor();

    return ret;
}

void TextEditor::save_action_slot() {
    std::cout << "save action" << std::endl;
}

void TextEditor::exit_action_slot() {
    std::cout << "exit action" << std::endl;
}

void TextEditor::undo_action_slot() {
    std::cout << "undo action" << std::endl;
};

void TextEditor::redo_action_slot() {
    std::cout << "redo action" << std::endl;
};

void TextEditor::cut_action_slot() {
    std::cout << "cut action" << std::endl;
};

void TextEditor::copy_action_slot() {
    std::cout << "copy action" << std::endl;
};

void TextEditor::paste_action_slot() {
    std::cout << "paste action" << std::endl;
};

void TextEditor::delete_action_slot() {
    std::cout << "delete action" << std::endl;
};

void TextEditor::select_all_action_slot() {
    std::cout << "select all action" << std::endl;
};

TextEditor* TextEditor::NewInstance()
{
    TextEditor* ret = new TextEditor();

    if((ret==NULL) || (!ret->construct()))
    {
        delete ret;
        ret = NULL;
    }

    return ret;
}

bool TextEditor::initMenuBar()
{
    bool ret = true;

    QMenuBar* mb = menuBar();

    ret = ret && initFileMenu(mb);
    ret = ret && initEditMenu(mb);
    return ret;

}

bool TextEditor::initToolBar()
{
    bool ret = true;

    QToolBar* tb = addToolBar("Tool Bar");
    tb->setMovable(false);
    tb->setFloatable(false);
    tb->setIconSize(QSize(16,16));

    ret = ret && initFileToolItem(tb);

    return ret;
}

bool TextEditor::initStatusBar()
{
    bool ret = true;

    QStatusBar* sb = statusBar();

    QLabel* label = new QLabel("Made By Hugo");

    if(label != NULL)
    {
        label->setMinimumWidth(200);
        label->setAlignment(Qt::AlignHCenter);

        sb->addPermanentWidget(new QLabel());
        sb->addPermanentWidget(label);
    }
    else
    {
        ret = false;
    }
    return ret;
}

bool TextEditor::initinitMainEditor()
{
    bool ret = true;

    mainEdit.setParent(this);
    setCentralWidget(&mainEdit);

    return ret;
}

bool TextEditor::initFileMenu(QMenuBar* mb)
{
    bool ret = true;

    QMenu* menu = new QMenu("File(&F)");
    ret = (menu != NULL);
    if(ret)
    {
        QAction* action = NULL;

        //Save
        ret = ret && makeAction(action, "Save(&S)",Qt::CTRL + Qt::Key_S);
        if(ret)
        {
           menu->addAction(action);
           connect(action, SIGNAL(triggered()), this, SLOT(save_action_slot()));
        }

        menu->addSeparator();

        //Exit
        ret = ret &&  makeAction(action, "Exit(&X)",0);
        if(ret)
        {
           menu->addAction(action);
           connect(action, SIGNAL(triggered()), this, SLOT(exit_action_slot()));
        }

    }
    if(ret)
    {
        mb->addMenu(menu);
    }
    else
    {
        delete mb;
    }
    return ret;
}

bool TextEditor::initEditMenu(QMenuBar* mb)
{
    bool ret = true;

    QMenu* menu = new QMenu("Edit(&E)");
    ret = (menu != NULL);
    if(ret)
    {
        QAction* action = NULL;

        //Undo
        ret = ret &&  makeAction(action, "Undo(&U)",Qt::CTRL + Qt::Key_Z);
        if(ret)
        {
           menu->addAction(action);
           connect(action, SIGNAL(triggered()), this, SLOT(undo_action_slot()));
        }

        menu->addSeparator();

        //Redo
        ret = ret &&  makeAction(action, "Redo(&R)...",Qt::CTRL + Qt::Key_Y);
        if(ret)
        {
           menu->addAction(action);
           connect(action, SIGNAL(triggered()), this, SLOT(redo_action_slot()));
        }

        menu->addSeparator();

        //Cut
        ret = ret &&  makeAction(action, "Cut(&T)",Qt::CTRL + Qt::Key_X);
        if(ret)
        {
           menu->addAction(action);
           connect(action, SIGNAL(triggered()), this, SLOT(cut_action_slot()));
        }

        menu->addSeparator();

        //Copy
        ret = ret &&  makeAction(action, "Copy(&C)...",Qt::CTRL + Qt::Key_C);
        if(ret)
        {
           menu->addAction(action);
           connect(action, SIGNAL(triggered()), this, SLOT(copy_action_slot()));
        }

        menu->addSeparator();

        //Paste
        ret = ret &&  makeAction(action, "Paste(&P)...",Qt::CTRL + Qt::Key_V);
        if(ret)
        {
           menu->addAction(action);
           connect(action, SIGNAL(triggered()), this, SLOT(paste_action_slot()));
        }

        menu->addSeparator();

        //Delete
        ret = ret &&  makeAction(action, "Delete(&L)",Qt::Key_Delete);
        if(ret)
        {
           menu->addAction(action);
           connect(action, SIGNAL(triggered()), this, SLOT(delete_action_slot()));
        }

        menu->addSeparator();

        //Select All
        ret = ret &&  makeAction(action, "Select All(&A)",Qt::CTRL + Qt::Key_A);
        if(ret)
        {
           menu->addAction(action);
           connect(action, SIGNAL(triggered()), this, SLOT(select_all_action_slot()));
        }

    }
    if(ret)
    {
        mb->addMenu(menu);
    }
    else
    {
        delete mb;
    }
    return ret;
}

bool TextEditor::initFileToolItem(QToolBar* tb)
{
    bool ret = true;
    QAction* action = NULL;

    ret = ret && makeAction(action, "Save", ":/tool/save.ico");
    if(ret)
    {
        tb->addAction(action);
    }

    ret = ret && makeAction(action, "Undo", ":/tool/undo.ico");
    if(ret)
    {
        tb->addAction(action);
    }
    return ret;

}

bool TextEditor::makeAction(QAction*& action, QString text, int key)
{
    bool ret = true;
    action = new QAction(text, NULL);
    if(action != NULL)
    {
        action->setShortcut(QKeySequence(key));
    }
    else
    {
        ret = false;
    }

    return ret;
}

bool TextEditor::makeAction(QAction*& action, QString tip, QString icon)
{
    bool ret = true;
    action = new QAction("", NULL);
    if(action != NULL)
    {
        action->setToolTip(tip);
        action->setIcon(QIcon(icon));
    }
    else
    {
        ret = false;
    }
    return ret;
}

TextEditor::~TextEditor()
{

};

void TextEditor::receiveOriginalText(std::string text, std::string filename) {
    this->mainEdit.setPlainText(QString::fromStdString(text));
    this->filename = filename;
};

void TextEditor::closeEvent(QCloseEvent* event) {
    QString text = this->mainEdit.toPlainText();
    QVector<QString> transfer;
    transfer.push_back(text);
    transfer.push_back(QString::fromStdString(this->filename));
    emit this->sendText(transfer);
};
