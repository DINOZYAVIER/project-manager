#ifndef PROJECT_HANDLER_H
#define PROJECT_HANDLER_H

struct ProjectFile
{
    ProjectFile() {}
    virtual ~ProjectFile() {}

    QString _id;
    QString _name;
};

struct ImageFile : public ProjectFile
{
    ImageFile() {}
    ~ImageFile() override {}
};

struct AudioFile : public ProjectFile
{
    AudioFile() {}
    ~AudioFile() override {}
};

class ProjectHandler
{
public:
    ProjectHandler( QJsonObject json );
    ~ProjectHandler();

private:
    QMap<QString, std::shared_ptr<ProjectFile>> m_files;

    ProjectFile jsonToProjectFile( QJsonObject json );
    QJsonObject projectFileToJson( ProjectFile file );
};

#endif // PROJECT_HANDLER_H
