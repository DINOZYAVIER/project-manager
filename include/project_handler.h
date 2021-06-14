#ifndef PROJECT_HANDLER_H
#define PROJECT_HANDLER_H

struct ProjectFile
{
    ProjectFile( QString id, QString name )
        : _id( id )
        , _name( name ) {}
    virtual ~ProjectFile() {}

    QString _id;
    QString _name;
};

struct ImageFile : public ProjectFile
{
    ImageFile( QString id, QString name )
        : ProjectFile( id, name ) {}
    ~ImageFile() override {}
};

struct AudioFile : public ProjectFile
{
    AudioFile( QString id, QString name )
        : ProjectFile( id, name ) {}
    ~AudioFile() override {}
};

class ProjectHandler : ProjectFile
{
public:
    ProjectHandler( QJsonArray json, QString id, QString name );
    ~ProjectHandler();

    QMap<QString, std::shared_ptr<ProjectFile>> files() { return m_files; }
private:
    QMap<QString, std::shared_ptr<ProjectFile>> m_files;
    QString                                     m_id;
    QString                                     m_name;

    static std::shared_ptr<ProjectFile> jsonToProjectFile( QJsonObject json );
    static QJsonObject projectFileToJson( std::shared_ptr<ProjectFile> file );
};

#endif // PROJECT_HANDLER_H
