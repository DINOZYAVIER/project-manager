#include "include/precompiled.h"
#include "include/project_handler.h"

ProjectHandler::ProjectHandler( QJsonObject json )
{
    Q_UNUSED( json );
}

ProjectHandler::~ProjectHandler()
{

}

ProjectFile ProjectHandler::jsonToProjectFile( QJsonObject json )
{
    Q_UNUSED( json );
    return ImageFile();
}

QJsonObject ProjectHandler::projectFileToJson( ProjectFile file )
{
    Q_UNUSED( file );
    return QJsonObject();
}
