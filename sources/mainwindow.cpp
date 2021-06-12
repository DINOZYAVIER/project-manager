#include <include/precompiled.h>
#include "include/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow( QWidget* parent )
    : QMainWindow( parent )
    , m_ui( new Ui::MainWindow )
{
    m_ui->setupUi(this);
    setWindowTitle( tr( "Project Manager" ) );
    m_ui->cbProjects->addItem( tr( "[Empty]" ), QString( "empty" ) );
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

