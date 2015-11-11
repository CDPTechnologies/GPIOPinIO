#include "FileIOServer.h"

FileIOServer::FileIOServer()
{
}

FileIOServer::~FileIOServer()
{
}

void FileIOServer::Create(const char* fullName)
{
    CDPComponent:: Create(fullName);
}

void FileIOServer::CreateModel()
{
    CDPComponent::CreateModel();
}

void FileIOServer::Configure(const char* xml, const char* end)
{
    CDPXMLConfiguration xmlComponent;
    GetComponentXML(xmlComponent, xml, end);
    CDPComponent::Configure(xmlComponent.StartPosition(), xmlComponent.StopPosition());
}


