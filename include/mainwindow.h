#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
class ProjectHandler;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow( QWidget* parent = nullptr );
    ~MainWindow();

private:
    Ui::MainWindow*                                m_ui;
    QMap<QString, std::shared_ptr<ProjectHandler>> m_projects;

    void loadDatabase( const QString& path );
    void populateProjectsMenu( QString id, QString name );
    void populateListWidget( int projectIndex = 0 );
    void initStyles();
    void setGridPolicy();
    void initConnection();
};
#endif // MAINWINDOW_H
