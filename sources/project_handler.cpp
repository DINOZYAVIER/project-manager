#include "include/precompiled.h"
#include "include/project_handler.h"

ProjectHandler::ProjectHandler( QJsonArray json, QString id, QString name )
    : ProjectFile( id, name )
{
    for( auto file : json )
    {
        QJsonObject fileObject = file.toObject();
        QString fileID = fileObject.value( "id" ).toString();

        auto projectFile = jsonToProjectFile( fileObject );

        if( projectFile.get() )
            m_files.insert( fileID, projectFile );
    }
}

ProjectHandler::~ProjectHandler()
{

}

std::shared_ptr<ProjectFile> ProjectHandler::jsonToProjectFile( QJsonObject json )
{
    QString id = json.value( "id" ).toString();
    QString name = json.value( "name" ).toString();
    QString type = json.value( "type" ).toString();

    if( id.isEmpty() )
        return nullptr;

    if( "Image" == type )
        return std::shared_ptr<ProjectFile>( new ImageFile( id, name ) );
    else if( "Audio" == type )
        return std::shared_ptr<ProjectFile>( new AudioFile( id, name ) );
    else
        return nullptr;
}

QJsonObject ProjectHandler::projectFileToJson( std::shared_ptr<ProjectFile> file )
{
    QString name = file->_name;
    QString id = file->_id;
    QString type = "";

    if( auto _file = dynamic_cast<ImageFile*>( file.get() ) )
        type = "Image";
    else if( auto _file = dynamic_cast<AudioFile*>( file.get() ) )
        type = "Audio";

    QJsonObject json;
    if( !type.isEmpty() )
    {
        json.insert( "id", file->_id );
        json.insert( "name", file->_name );
        json.insert( "type", type );
    }
    return json;
}
