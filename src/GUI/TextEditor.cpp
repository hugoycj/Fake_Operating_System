#include "TextEditor.h"
#include "ui_mainwindow.h"
#include <QIcon>

TextEditor::TextEditor(QWidget *parent)
    : QMainWindow(parent), statusLabel(this)
{
    this->construct();
}

bool TextEditor::construct()
{
    bool ret = true;
//    ret = ret && initMenuBar();
    ret = ret && initToolBar();
//    ret = ret && initStatusBar();
    ret = ret && initinitMainEditor();
    return ret;
}

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
bool TextEditor::initMenuBar()//菜单栏
{
    bool ret = true;

    QMenuBar* mb = menuBar();//一定要注意是menuBar()，这是普通成员函数，不是构造函数

    ret = ret && initFileMenu(mb);//传一个参数是为了在initFileMenu()函数将menu加入菜单栏
    ret = ret && initEditMenu(mb);
    ret = ret && initFormatMenu(mb);
    ret = ret && initViewMenu(mb);
    ret = ret && initHelpMenu(mb);

    return ret;

}

bool TextEditor::initToolBar()//工具栏
{
    bool ret = true;

    QToolBar* tb = addToolBar("Tool Bar");
    tb->setMovable(false);
    tb->setFloatable(false);
    tb->setIconSize(QSize(16,16));


    ret = ret && initFileToolItem(tb);

    return ret;
}

bool TextEditor::initStatusBar()//状态栏
{
    bool ret = true;

    QStatusBar* sb = statusBar();

    QLabel* label = new QLabel("Made By Hugo");

    if(label != NULL)
    {
        statusLabel.setMinimumWidth(200);
        statusLabel.setAlignment(Qt::AlignHCenter);
        statusLabel.setText("Ln:1    Col:1");


        label->setMinimumWidth(200);
        label->setAlignment(Qt::AlignHCenter);

        sb->addPermanentWidget(new QLabel());//单纯加入分隔符
        sb->addPermanentWidget(&statusLabel);
        sb->addPermanentWidget(label);
    }
    else
    {
        ret = false;
    }
    return ret;
}
bool TextEditor::initinitMainEditor()//编辑窗口
{
    bool ret = true;

    mainEdit.setParent(this);
    setCentralWidget(&mainEdit);

    return ret;
}

/************************************************文件菜单********************************************************/
bool TextEditor::initFileMenu(QMenuBar* mb)
{
    bool ret = true;

    QMenu* menu = new QMenu("File(&F)");//创建文件菜单，（&F）是为了可以Alt+F打开
    ret = (menu != NULL);
    if(ret)
    {
        QAction* action = NULL;

        //New
        ret = ret &&  makeAction(action, "New(&N)",Qt::CTRL + Qt::Key_N);
        if(ret)
        {
           menu->addAction(action);
        }

        menu->addSeparator();

        //Open
        ret = ret &&  makeAction(action, "Open(&O)...",Qt::CTRL + Qt::Key_O);
        if(ret)
        {
           menu->addAction(action);
        }

        menu->addSeparator();

        //Save
        ret = ret &&  makeAction(action, "Save(&S)",Qt::CTRL + Qt::Key_S);
        if(ret)
        {
           menu->addAction(action);
        }

        menu->addSeparator();

        //Save As
        ret = ret &&  makeAction(action, "Save As(&A)...",0);
        if(ret)
        {
           menu->addAction(action);
        }

        menu->addSeparator();

        //print
        ret = ret &&  makeAction(action, "Print(&P)...",Qt::CTRL + Qt::Key_P);
        if(ret)
        {
           menu->addAction(action);
        }

        menu->addSeparator();

        //Exit
        ret = ret &&  makeAction(action, "Exit(&X)",0);
        if(ret)
        {
           menu->addAction(action);//将菜单项加入到菜单
        }

    }
    if(ret)
    {
        mb->addMenu(menu);//将菜单加入到菜单栏
    }
    else
    {
        delete mb;
    }
    return ret;
}

/************************************************编辑菜单********************************************************/
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
        }

        menu->addSeparator();

        //Redo
        ret = ret &&  makeAction(action, "Redo(&R)...",Qt::CTRL + Qt::Key_Y);
        if(ret)
        {
           menu->addAction(action);
        }

        menu->addSeparator();

        //Cut
        ret = ret &&  makeAction(action, "Cut(&T)",Qt::CTRL + Qt::Key_X);
        if(ret)
        {
           menu->addAction(action);
        }

        menu->addSeparator();

        //Copy
        ret = ret &&  makeAction(action, "Copy(&C)...",Qt::CTRL + Qt::Key_C);
        if(ret)
        {
           menu->addAction(action);
        }

        menu->addSeparator();

        //Pase
        ret = ret &&  makeAction(action, "Pase(&P)...",Qt::CTRL + Qt::Key_V);
        if(ret)
        {
           menu->addAction(action);
        }

        menu->addSeparator();

        //Delete
        ret = ret &&  makeAction(action, "Delete(&L)",Qt::Key_Delete);
        if(ret)
        {
           menu->addAction(action);
        }

        menu->addSeparator();

        //Find
        ret = ret &&  makeAction(action, "Find(&F)...",Qt::CTRL + Qt::Key_F);
        if(ret)
        {
           menu->addAction(action);
        }

        menu->addSeparator();

        //Replace
        ret = ret &&  makeAction(action, "Replace(&R)...",Qt::CTRL + Qt::Key_H);
        if(ret)
        {
           menu->addAction(action);
        }

        menu->addSeparator();

        //Goto
        ret = ret &&  makeAction(action, "Goto(&G)",Qt::CTRL + Qt::Key_G);
        if(ret)
        {
           menu->addAction(action);
        }

        menu->addSeparator();

        //Select All
        ret = ret &&  makeAction(action, "Select All(&A)",Qt::CTRL + Qt::Key_A);
        if(ret)
        {
           menu->addAction(action);
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

/************************************************格式菜单********************************************************/
bool TextEditor::initFormatMenu(QMenuBar* mb)
{
    bool ret = true;

    QMenu* menu = new QMenu("Format(&O)");
    ret = (menu != NULL);
    if(ret)
    {
        QAction* action = NULL;

        //Auto Wrap
        ret = ret &&  makeAction(action, "Auto Wrap(&W)",0);
        if(ret)
        {
           menu->addAction(action);
        }

        menu->addSeparator();

        //Font
        ret = ret &&  makeAction(action, "Font(&F)...",0);
        if(ret)
        {
           menu->addAction(action);
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

/************************************************视图菜单********************************************************/
bool TextEditor::initViewMenu(QMenuBar* mb)
{
    bool ret = true;

    QMenu* menu = new QMenu("View(&V)");
    ret = (menu != NULL);
    if(ret)
    {
        QAction* action = NULL;

        //Tool Bar
        ret = ret &&  makeAction(action, "Tool Bar(&T)",0);
        if(ret)
        {
           menu->addAction(action);
        }

        menu->addSeparator();

        //Status Bar
        ret = ret &&  makeAction(action, "Status Bar(&S)",0);
        if(ret)
        {
           menu->addAction(action);
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

/************************************************帮助菜单********************************************************/
bool TextEditor::initHelpMenu(QMenuBar* mb)
{
    bool ret = true;

    QMenu* menu = new QMenu("Help(&H)");
    ret = (menu != NULL);
    if(ret)
    {
        QAction* action = NULL;

        //User Manual
        ret = ret &&  makeAction(action, "User Manual",0);
        if(ret)
        {
           menu->addAction(action);
        }

        menu->addSeparator();

        //About NotePad
        ret = ret &&  makeAction(action, "About NotePad...",0);
        if(ret)
        {
           menu->addAction(action);
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

//    QPixmap newpix("new.png");
//    QPixmap openpix("open.png");
//    QPixmap quitpix("quit.png");
//    tb->addAction(QIcon(newpix), "New File");
//    tb->addSeparator();
//    tb->addAction(QIcon(openpix), "Open File");
//    tb->addSeparator();
//    tb->addAction(QIcon(quitpix),"Quit Application");

    ret = ret && makeAction(action, "New", ":/tool/new.ico");
    if(ret)
    {
        tb->addAction(action);
    }

    ret = ret && makeAction(action, "Open", ":/tool/open.ico");
    if(ret)
    {
        tb->addAction(action);
    }

    ret = ret && makeAction(action, "Save", ":/tool/save.ico");
    if(ret)
    {
        tb->addAction(action);
    }

//    ret = ret && makeAction(action, "Save As", ":/Res/pic/saveas.png");
//    if(ret)
//    {
//        tb->addAction(action);
//    }
//    ret = ret && makeAction(action, "Print", ":/tool/print.ico");
//    if(ret)
//    {
//        tb->addAction(action);
//    }
    ret = ret && makeAction(action, "Undo", ":/tool/undo.ico");
    if(ret)
    {
        tb->addAction(action);
    }
//    ret = ret && makeAction(action, "Redo", ":/tool/redo.ico");
//    if(ret)
//    {
//        tb->addAction(action);
//    }

    return ret;

}

bool TextEditor::makeAction(QAction*& action, QString text, int key)//菜单项
{
    bool ret = true;
    action = new QAction(text, NULL);
    if(action != NULL)
    {
        action->setShortcut(QKeySequence(key));//创建快捷键
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

}

