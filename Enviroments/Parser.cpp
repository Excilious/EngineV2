//------------------Parser.cpp------------------//
//  Author: Excilious
//  Date: 20/07/24
//  Abstraction: Main file to fetch entity/world data.
//
//----------------------------------------------//

#include "Parser.h"

Parser::Parser()
{}

std::string Parser::DestroyCharacters(std::string &InputString,std::string CharacterToDestroy)
{
    for (char& NewCharacter : CharacterToDestroy)
    {InputString.erase(std::remove(InputString.begin(), InputString.end(), NewCharacter), InputString.end());}
    return InputString;
}

std::string Parser::RemoveSpaces(std::string SubString)
{
    SubString.erase(remove(SubString.begin(),SubString.end(),' '),SubString.end());
    return SubString;
}

void Parser::FetchLightContainers(std::string Header,std::string String)
{
    String = DestroyCharacters(String,"<>");
    if (Header == "<lc>")
    {
        String = DestroyCharacters(String,"lc");
        std::stringstream NewString(String);
        while (NewString.good())
        {
            std::string SubString;
            std::getline(NewString,SubString,',');
            TempStorage.push_back(std::stof(SubString));
            if (TempStorage.size() >= 4)
            {
                LightMap[LightCountPosition]["LightColour"] = glm::vec4(TempStorage.data()[0],TempStorage.data()[1],TempStorage.data()[2],TempStorage.data()[3]);
                TempStorage = {};
            }
        } 
    }
    else if (Header == "<ls>")
    {
        LightCountPosition++;
        String = DestroyCharacters(String,"ls");
        std::stringstream NewString(String);
        while (NewString.good())
        {
            std::string SubString;
            std::getline(NewString,SubString,',');
            TempStorage.push_back(std::stof(SubString));
            if (TempStorage.size() >= 4)
            {
                LightMap[LightCountPosition]["LightScale"] = glm::vec4(TempStorage.data()[0],TempStorage.data()[1],TempStorage.data()[2],TempStorage.data()[3]);
                TempStorage = {};
            }
        } 
    }
    else if (Header == "<lp>")
    {
        String = DestroyCharacters(String,"lp");

        std::stringstream NewString(String);
        while (NewString.good())
        {
            std::string SubString;
            std::getline(NewString,SubString,',');
            TempStorage.push_back(std::stof(SubString));
            if (TempStorage.size() >= 4)
            {
                LightMap[LightCountPosition]["LightPosition"] = glm::vec4(TempStorage.data()[0],TempStorage.data()[1],TempStorage.data()[2],TempStorage.data()[3]);
                TempStorage = {};
            }
        } 
    }
}

void Parser::FetchWorldContainers(std::string Header,std::string String)
{
    String = DestroyCharacters(String,"<>");
    if (Header == "<wv>")
    {
        String = DestroyCharacters(String,"wv");
        std::stringstream NewString(String);
        while (NewString.good())
        {
            std::string SubString;
            std::getline(NewString,SubString,',');
            if (!SubString.empty() || !(SubString.length() == 0))
            {Vertices.push_back(std::stof(SubString));}
        } 
    }
    else if (Header == "<wp>")
    {
        String = DestroyCharacters(String,"wp");
        std::stringstream NewString(String);
        while (NewString.good())
        {
            std::string SubString;
            std::getline(NewString,SubString,',');
            Position.push_back(std::stof(SubString));
        }
    }
    else if (Header == "<ws>")
    {
        String = DestroyCharacters(String,"ws");
        std::stringstream NewString(String);
        while (NewString.good())
        {
            std::string SubString;
            std::getline(NewString,SubString,',');
            Size.push_back(std::stof(SubString));
        }
    }
    else if (Header == "<wr>")
    {
        String = DestroyCharacters(String,"wr");
        std::stringstream NewString(String);
        while (NewString.good())
        {
            std::string SubString;
            std::getline(NewString,SubString,',');
            Rotation.push_back(std::stof(SubString));
        }
    }
    else if (Header == "<wi>")
    {
        String = DestroyCharacters(String,"wi");
        std::stringstream NewString(String);
        while (NewString.good())
        {
            std::string SubString;
            std::getline(NewString,SubString,',');
            Indices.push_back(std::stoi(SubString));
        }
    }
}

void Parser::FetchEntityContainers(std::string Header,std::string String)
{
    String = DestroyCharacters(String,"<>");
    if (Header == "<ep>")
    {
        String = DestroyCharacters(String,"ep");
        std::stringstream NewString(String);
        while (NewString.good())
        {
            std::string SubString;
            std::getline(NewString,SubString,',');
            EntityTempStorage.push_back(std::stof(SubString));
            if (EntityTempStorage.size() >= 4)
            {
                EntityMap[TempString]["Position"] = glm::vec4(EntityTempStorage.data()[0],EntityTempStorage.data()[1],EntityTempStorage.data()[2],EntityTempStorage.data()[3]);
                EntityTempStorage = {};
            }
        }
    }
    else if (Header == "<ef>")
    {
        String = String.substr(2,String.size());
        String = RemoveSpaces(String);
        std::stringstream NewString(String);
        while (NewString.good())
        {
            std::string SubString;
            std::getline(NewString,SubString);
            EntityMap[TempString][SubString] = glm::vec4(0.0f,0.0f,0.0f,0.0f);
        }
    }
    else if (Header == "<es>")
    {
        String = DestroyCharacters(String,"es");
        std::stringstream NewString(String);
        while (NewString.good())
        {
            std::string SubString;
            std::getline(NewString,SubString,',');
            EntityTempStorage.push_back(std::stof(SubString));
            if (EntityTempStorage.size() >= 4)
            {
                EntityMap[TempString]["Scale"] = glm::vec4(EntityTempStorage.data()[0],EntityTempStorage.data()[1],EntityTempStorage.data()[2],EntityTempStorage.data()[3]);
                EntityTempStorage = {};
            }
        }
    }
    else if (Header == "<er>")
    {
        String = DestroyCharacters(String,"er");
        std::stringstream NewString(String);
        while (NewString.good())
        {
            std::string SubString;
            std::getline(NewString,SubString,',');
            EntityTempStorage.push_back(std::stof(SubString));
            if (EntityTempStorage.size() >= 4)
            {
                EntityMap[TempString]["Rotation"] = glm::vec4(EntityTempStorage.data()[0],EntityTempStorage.data()[1],EntityTempStorage.data()[2],EntityTempStorage.data()[3]);
                EntityTempStorage = {};
            }
        }
    }
}

void Parser::ParseThroughContents(const char* NewFile)
{
    std::ifstream InputFileContents(NewFile,std::ios::binary);
    std::string String;

    while (std::getline(InputFileContents,String))
    {
        String = DestroyCharacters(String," ");
        if (String.substr(0,1) == "#")
        {continue;}
        else if (String.substr(0,2) == "<w")
        {FetchWorldContainers(String.substr(0,4),String);}
        else if (String.substr(0,2) == "<l")
        {FetchLightContainers(String.substr(0,4),String);}
        else if (String.substr(0,2) == "<e")
        {FetchEntityContainers(String.substr(0,4),String);}
    }
    InputFileContents.close();
}