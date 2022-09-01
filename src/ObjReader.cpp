#include "ObjReader.h"
#include <fstream>

ObjReader::ObjReader()
{
}

ObjReader::~ObjReader()
{
}

bool ObjReader::readFile(const std::string& path)
{
    std::ifstream objFile;


    // objFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        objFile.open(path);
        std::string str;
        while (std::getline(objFile, str))
        {
            determine(str);
        }
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "ERROR::OBJ::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;
        return false;
    }
    createNormals();
    return true;
}

std::vector<std::string> ObjReader::split(const std::string& s, const char separator, const bool skipEmptyElements)
{
    std::vector<std::string> output;
    std::string::size_type prev_pos = 0, pos = 0;
    while ((pos = s.find(separator, pos)) != std::string::npos) {
        std::string substring(s.substr(prev_pos, pos - prev_pos));
        if ((!substring.empty())||(!skipEmptyElements))
            output.push_back(substring);
        prev_pos = ++pos;
    }

    std::string substring(s.substr(prev_pos, pos - prev_pos));
    if ((!substring.empty())||(!skipEmptyElements))
        output.push_back(substring); // Last word
    return output;
}

void ObjReader::determine(const std::string& s)
{
    std::vector<std::string> strTemp = split(s, ' ', true);
    
    if (strTemp.empty())
        return;
    if (strTemp[0] == "v")
        addGvec3(strTemp);
    if (strTemp[0] == "vt")
        addTvec2(strTemp);
    if (strTemp[0] == "vn")
        addNvec3(strTemp);
    if (strTemp[0] == "f")
        addFvec(strTemp);
}

void ObjReader::addGvec3(const std::vector<std::string>& strWord)
{
    vertGeometry.push_back(glm::vec3(std::stof(strWord[1]), std::stof(strWord[2]), std::stof(strWord[3])));
}

void ObjReader::addTvec2(const std::vector<std::string>& strWord)
{
    vertTexture.push_back(glm::vec2(std::stof(strWord[1]), std::stof(strWord[2])));
}

void ObjReader::addNvec3(const std::vector<std::string>& strWord)
{
    vertNormal.push_back(glm::vec3(std::stof(strWord[1]), std::stof(strWord[2]), std::stof(strWord[3])));
}

void ObjReader::addFvec(const std::vector<std::string>& strWord)
{
    std::vector<int> result[3];
    for (int i = 1; i < strWord.size(); i++) 
    {
        std::vector<std::string> splitOut = split(strWord[i], '/', false);
        for (int j = 0; j < splitOut.size(); j++)
        {
            if (splitOut[j].empty())
                continue;
            result[j].push_back(std::stoi(splitOut[j])-1);
        }
    }
    verticesFacesGeometry.push_back(result[0]);
    verticesFacesTexture.push_back(result[1]);
    verticesFacesNormal.push_back(result[2]);
}

std::vector<float> ObjReader::createVertices()
{
    std::vector<float> outVertices;
    
    std::vector<int> verticesFacesGeometry = splitTriangle(this->verticesFacesGeometry);
    std::vector<int> verticesFacesTexture = splitTriangle(this->verticesFacesTexture);
    std::vector<int> verticesFacesNormal = splitTriangle(this->verticesFacesNormal);

    for (size_t i = 0; i < verticesFacesGeometry.size(); i++)
    {
        int indexGeometry = verticesFacesGeometry[i];
        
        int indexNormal = verticesFacesNormal[i];
        
        outVertices.push_back(vertGeometry[indexGeometry].x);
        outVertices.push_back(vertGeometry[indexGeometry].y);
        outVertices.push_back(vertGeometry[indexGeometry].z);
        
        outVertices.push_back(vertNormal[indexNormal].x);
        outVertices.push_back(vertNormal[indexNormal].y);
        outVertices.push_back(vertNormal[indexNormal].z);

        if (!vertTexture.empty())
        {
            int indexTexture = verticesFacesTexture[i];
            outVertices.push_back(vertTexture[indexTexture].x);
            outVertices.push_back(vertTexture[indexTexture].y);
        }
        else
        {
            outVertices.push_back(0.f);
            outVertices.push_back(0.f);
        }
    }
    return outVertices;
}

std::vector<int> ObjReader::splitTriangle(const std::vector<std::vector<int>>& verticesFaces)
{
    std::vector<int> vertices;
    vertices.reserve(verticesFaces.size()*3);

    for (size_t i = 0; i < verticesFaces.size(); i++)
    {
        for (size_t j = 2; j < verticesFaces[i].size(); j++)
        {
            vertices.push_back(verticesFaces[i][0]);
            vertices.push_back(verticesFaces[i][j-1]);
            vertices.push_back(verticesFaces[i][j]);
        }
    }
    return vertices;
}

void ObjReader::createNormals()
{
    if (!vertNormal.empty())
        return;
    vertNormal.resize(vertGeometry.size());
    verticesFacesNormal = verticesFacesGeometry;
    for (int i = 0; i < verticesFacesGeometry.size(); i++)
    {
        int index0 = verticesFacesGeometry[i][0];
        int index1 = verticesFacesGeometry[i][1];
        int index2 = verticesFacesGeometry[i][2];


        glm::vec3 norm = glm::normalize(glm::cross(vertGeometry[index1]- vertGeometry[index0], vertGeometry[index2] - vertGeometry[index0]));
        for (int j = 0; j < verticesFacesGeometry[i].size(); j++)
        {
            const int index = verticesFacesNormal[i][j];
            vertNormal[index] = norm;
        }
    }
}
