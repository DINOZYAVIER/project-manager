#include "include/precompiled.h"
#include "include/project_handler.h"

ProjectHandler::ProjectHandler( QJsonObject json )
{
    Q_UNUSED( json );
}

ProjectHandler::~ProjectHandler()
{

}

std::shared_ptr<ProjectFile> ProjectHandler::jsonToProjectFile( QJsonObject json )
{
    QString id = json.value( "id" ).toString();
    QString name = json.value( "name" ).toString();
    QString type = json.value( "type" ).toString();

    if( "Image" == type )
        return std::shared_ptr<ProjectFile>( new ImageFile( name, id ) );
    else if( "Audio" == type )
        return std::shared_ptr<ProjectFile>( new AudioFile( name, id ) );
    else
        return nullptr;
}

QJsonObject ProjectHandler::projectFileToJson( std::shared_ptr<ProjectFile> file )
{
    QString name = file->_name;
    QString id = file->_id;
    QString type = "";

    QJsonObject json;
    json.insert( "id", file->_id );
    json.insert( "name", file->_name );


    if( auto _file = dynamic_cast<ImageFile*>( file.get() ) )
        type = "Image";
    else if( auto _file = dynamic_cast<ImageFile*>( file.get() ) )
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
