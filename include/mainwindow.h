#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

struct ProjectHandler;

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
    Ui::MainWindow*                          m_ui;
    QVector<std::shared_ptr<ProjectHandler>> m_projects;

    void loadDatabase( const QString& path );
};
#endif // MAINWINDOW_H
