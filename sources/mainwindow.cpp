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
    loadDatabase( "/Users/dinozyavier/Desktop/database.json" );
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::loadDatabase( const QString& path )
{
    QFile file( path );
    QJsonObject metaProjects;

    if( file.open( QIODevice::ReadWrite | QIODevice::Text ) )
       metaProjects = QJsonDocument::fromJson( file.readAll() ).object();
    else
       return;

    for( auto key : metaProjects.keys() )
    {
        auto projectObject = metaProjects.value( key ).toArray();

        for( auto project : projectObject )
        {
            auto object = project.toObject();
            QString id = object.value( "id" ).toString();
            QString name = object.value( "name" ).toString();

            if( id.isEmpty() )
                continue;
           m_projects.insert( id, std::shared_ptr<ProjectHandler>( new ProjectHandler( object, id, name ) ) );
        }
    }
}
