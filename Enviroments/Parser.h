//------------------Parser.h------------------//
//  Author: Excilious
//  Date: 20/07/24
//  Abstraction: Iterate between file format header.
//
//----------------------------------------------//

#ifndef PARSER_HEADER
#define PARSER_HEADER

#include <string>
#include <list>
#include <algorithm>
#include <cctype>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include "../Dependancies/glm/glm.hpp"

class Parser
{
    public:
        Parser();
        
        void ParseThroughContents(const char* NewFile);

        std::vector<float> Vertices = {};
        std::vector<unsigned int> Indices = {};
        std::vector<float> Size = {};
        std::vector<float> Position = {};
        std::vector<float> Rotation = {};

        std::vector<float> PlayerPosition = {};
        std::string RemoveSpaces(std::string SubString);
        std::string DestroyCharacters(std::string &InputString,std::string CharacterToDestroy);

        std::map<int,std::map<std::string,glm::vec4>> LightMap {};
        std::map<std::string,std::map<std::string,glm::vec4>> EntityMap = {};

    private:
        int LightCountPosition = 0;
        int InterfacePosition = 0;
        std::vector<float> TempStorage = {};
        std::vector<float> EntityTempStorage = {};
        std::string TempString;

        void FetchLightContainers(std::string Header,std::string String);
        void FetchWorldContainers(std::string Header,std::string String);
        void FetchEntityContainers(std::string Header,std::string String);
};

#endif