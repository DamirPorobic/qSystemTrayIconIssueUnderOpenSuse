#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mTrayIcon(new QSystemTrayIcon)
{
    ui->setupUi(this);

    QPixmap pixmap(50,50);
    pixmap.fill(QColor("red"));
    QIcon redIcon(pixmap);

    mQuitAction = new QAction("Quit", this);
    connect(mQuitAction, &QAction::triggered, [this]() {
        mTrayIcon->hide();
        this->close();
    });

    mShowMessageAction = new QAction("Show Message", this);
    connect(mShowMessageAction, &QAction::triggered, [this]() {
        mTrayIcon->showMessage("Click me!", "Click me and check main window for message");
    });

    connect(mTrayIcon, &QSystemTrayIcon::messageClicked, [this]() {
        this->ui->textEdit->append("message clicked");
    });

    connect(mTrayIcon, &QSystemTrayIcon::activated, [this]() {
        this->ui->textEdit->append("tray icon activated");
    });

    mMenu.addAction(mQuitAction);
    mMenu.addAction(mShowMessageAction);
    mTrayIcon->setIcon(redIcon);
    mTrayIcon->setContextMenu(&mMenu);
    mTrayIcon->setToolTip("Test TryIcon");
    mTrayIcon->show();

    this->ui->textEdit->append("starting...");
    this->ui->textEdit->append("try clicking red tray icon and message after triggering it via context menu.");
    this->ui->textEdit->append("clicking tray icon appends message, clicking message box, does not.");
}

MainWindow::~MainWindow()
{
    delete ui;
    delete mTrayIcon;
    delete mQuitAction;
    delete mShowMessageAction;
}

