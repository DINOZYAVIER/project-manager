#include <include/precompiled.h>
#include "include/mainwindow.h"
#include "ui_mainwindow.h"

#include "include/project_handler.h"

MainWindow::MainWindow( QWidget* parent )
    : QMainWindow( parent )
    , m_ui( new Ui::MainWindow )
{
    m_ui->setupUi( this );
    setWindowTitle( tr( "Project Manager" ) );

    initStyles();
    loadDatabase( "/Users/dinozyavier/Desktop/database.json" );

    if( m_projects.isEmpty() )
        m_ui->cbProjects->addItem( tr( "[Empty]" ), QString( "empty" ) );
    else
        populateListWidget( 0 );

    bool result = false;

    result = connect( m_ui->cbProjects, static_cast<void ( QComboBox::* )(int)>( &QComboBox::currentIndexChanged ), [=]( int currentProject )
    {
        m_ui->filesListWidget->clear();

        populateListWidget( currentProject );
    });
    Q_ASSERT( result );

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
            QJsonArray files = object.value( "files" ).toArray();

            if( id.isEmpty() )
                continue;

            populateProjectsMenu( id, name );
            m_projects.insert( id, std::shared_ptr<ProjectHandler>( new ProjectHandler( files, id, name ) ) );
        }
    }
}

void MainWindow::populateProjectsMenu( QString id, QString name )
{
   m_ui->cbProjects->addItem( name, id );
}

void MainWindow::populateListWidget( int projectIndex )
{
    if( m_projects.isEmpty() )
        return;

    auto projectFiles = m_projects.value( m_ui->cbProjects->itemData( projectIndex, Qt::UserRole ).toString() );
    for( auto file : projectFiles->files() )
    {
        QListWidgetItem* item = new QListWidgetItem( file->_name, m_ui->filesListWidget );
        item->setData( Qt::UserRole, file->_id );
        m_ui->filesListWidget->addItem( item );
    }
}

void MainWindow::initStyles()
{
}
