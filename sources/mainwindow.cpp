#include <include/precompiled.h>
#include "include/mainwindow.h"
#include "ui_mainwindow.h"

#include "include/project_handler.h"

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

void MainWindow::loadDatabase( const QString& path )
{
    QFile file( path);
    QJsonObject projects;

    if( file.open( QIODevice::ReadWrite | QIODevice::Text ) )
       projects = QJsonDocument::fromJson( file.readAll() ).object();
    else
       return;

    for( auto project : projects )
    {
        auto projectObject = project.toObject();

        m_projects.append( std::shared_ptr<ProjectHandler>( new ProjectHandler( projectObject ) ) );
    }
}
