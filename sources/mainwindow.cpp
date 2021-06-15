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

    initConnection();
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
}

void MainWindow::initStyles()
{
    this->setStyleSheet( "background: white; color: black;" );

    m_ui->lbFiles->setStyleSheet( "font: 16px; color: black;" );

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
    m_ui->filesListWidget->setVerticalScrollBarPolicy( Qt::ScrollBarPolicy::ScrollBarAlwaysOff );
}

void MainWindow::initConnection()
{
    bool result = false;

    result = connect( m_ui->cbProjects, static_cast<void ( QComboBox::* )(int)>( &QComboBox::currentIndexChanged ), [=]( int currentProject )
    {
        m_ui->filesListWidget->clear();

        populateListWidget( currentProject );
    });
    Q_ASSERT( result );

    result = connect( m_ui->actionAboutApplication, &QAction::triggered, [this]()
    {
        QMessageBox::about( this, "About the program",
                                  "Project Management Application \nTest assignment by Arthur Konovalov.");
    });
    Q_ASSERT( result );


    result = connect( m_ui->actionAboutQt, &QAction::triggered, [this]()
    {
        QMessageBox::aboutQt( this, "About Qt" );
    });
    Q_ASSERT( result );

    result = connect( m_ui->actionOpenDatabase, &QAction::triggered, [this]()
    {
        QString fileName = QFileDialog::getOpenFileName( this,
                    tr( "Open database" ), QCoreApplication::applicationDirPath(), tr( "(*.json)" ) );
        m_ui->cbProjects->clear();
        loadDatabase( fileName );
        populateListWidget( 0 );
    });

    result = connect( m_ui->actionCloseDatabase, &QAction::triggered, [this]()
    {
        int count = m_projects.size();
        for( int i = 0; i < count; ++i )
        {
            QString key = m_ui->cbProjects->itemData( i, Qt::UserRole ).toString();
            m_projects.remove( key );
        }
        m_ui->filesListWidget->clear();
        m_ui->cbProjects->clear();
        m_ui->cbProjects->addItem( tr( "[Empty]" ), QString( "empty" ) );
    });
}
