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

    initStyles();
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

        QIcon icon;
        if( auto _file = dynamic_cast<ImageFile*>( file.get() ) )
            icon = QIcon( ":/icons/audio_ic.png" );
        else if( auto _file = dynamic_cast<AudioFile*>( file.get() ) )
            icon = QIcon( ":/icons/image_ic-2x.png" );
        item->setIcon( icon );
        m_ui->filesListWidget->addItem( item );
    }
    m_ui->filesListWidget->resize( m_ui->filesListWidget->width(),
                                   m_ui->filesListWidget->count() * 30 );
}

void MainWindow::initStyles()
{
    this->setStyleSheet( "background: white;" );

    m_ui->lbFiles->setStyleSheet( "font: 16px;" );

    QFile cbStyle( ":/ComboBoxStyle.css" );
    cbStyle.open( QFile::ReadOnly );
    m_ui->cbProjects->setStyleSheet( cbStyle.readAll() );

    setGridPolicy();
    QFile lwStyle( ":/ListWidgetStyle.css" );
    lwStyle.open( QFile::ReadOnly );
    m_ui->filesListWidget->setStyleSheet( lwStyle.readAll() );
}

void MainWindow::setGridPolicy()
{
    m_ui->filesListWidget->setIconSize( QSize( 50, 50 ) );
    m_ui->filesListWidget->setSpacing( 5 );
    //m_ui->filesListWidget->setViewMode( QListView::IconMode );
    //m_ui->filesListWidget->setFlow( QListView::TopToBottom );

    //m_ui->filesListWidget->setFixedHeight( m_ui->filesListWidget->count() * 20 );
    //m_ui->filesListWidget->setGridSize( QSize( m_ui->filesListWidget->width(), 20 ) );
    //m_ui->filesListWidget->setVerticalScrollBarPolicy( Qt::ScrollBarPolicy::ScrollBarAlwaysOff );
}
