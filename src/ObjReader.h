#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <glm/glm.hpp>


class ObjReader
{

	std::vector<glm::vec3> vertGeometry;
	std::vector<glm::vec2> vertTexture;
	std::vector<glm::vec3> vertNormal;

	std::vector<std::vector<int>> verticesFacesGeometry;
	std::vector<std::vector<int>> verticesFacesTexture;
	std::vector<std::vector<int>> verticesFacesNormal;
	

public:
	ObjReader();
	~ObjReader();
	bool readFile(const std::string& path);
	std::vector<std::string> split(const std::string& s, const char separator, const bool skipEmptyElements);
	void determine(const std::string& s);
	void addGvec3(const std::vector<std::string>& strWord);
	void addTvec2(const std::vector<std::string>& strWord);
	void addNvec3(const std::vector<std::string>& strWord);
	void addFvec(const std::vector<std::string>& strWord);
	std::vector<float> createVertices();

	static std::vector<int> splitTriangle(const std::vector<std::vector<int>>& verticesFaces);

	void createNormals();

	
};