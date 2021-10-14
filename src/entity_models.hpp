#pragma once
#include "lve_model.hpp"
#include "glm/gtc/constants.hpp"
#include <memory>
#include <vector>

namespace lve{
    class ModelBuilder{
        public:

            struct MeshData
            {
                std::shared_ptr<LveModel> mesh;
                int resolution;
                const char* type;
            };

            std::vector<LveModel::Vertex> rotateVectors(std::vector<LveModel::Vertex> vertices, float theta){
                
                std::vector<LveModel::Vertex> newVertices;

                for (int i = 0; i < vertices.size(); i++)
                {
                    float new_x = vertices[i].position.x * glm::cos(theta) - vertices[i].position.y * glm::sin(theta);
                    float new_y = vertices[i].position.x * glm::sin(theta) + vertices[i].position.y * glm::cos(theta);

                    LveModel::Vertex vertex = {{new_x, -new_y}};

                    newVertices.push_back(vertex);
                }
                return newVertices;

            }

            std::vector<LveModel::Vertex> increaseResolution(std::vector<LveModel::Vertex> vertices, int targetRes ,int& resolution){
                std::vector<LveModel::Vertex> newVertices;
                newVertices = vertices;

                while(resolution < targetRes){
                    std::vector<LveModel::Vertex> tempVertices{};
                    for(int i = 0; i < newVertices.size()/3; i++){
                        LveModel::Vertex midpoint;

                        midpoint.position = (newVertices[i*3].position + newVertices[i*3 + 1].position + newVertices[i*3 + 2].position);
                        midpoint.position.x = midpoint.position.x/3;
                        midpoint.position.y = midpoint.position.y/3;
                        

                        tempVertices.push_back(newVertices[i*3]);
                        tempVertices.push_back(newVertices[i*3 + 1]);
                        tempVertices.push_back(midpoint);

                        tempVertices.push_back(newVertices[i*3 + 1]);
                        tempVertices.push_back(newVertices[i*3 + 2]);
                        tempVertices.push_back(midpoint);

                        tempVertices.push_back(newVertices[i*3 + 2]);
                        tempVertices.push_back(newVertices[i*3]);
                        tempVertices.push_back(midpoint);
                    }
                    newVertices = tempVertices;
                    ++resolution;
                }
                return newVertices;


            }
            

            MeshData createCircleModel(float radius,unsigned int numSides, const char* type, LveDevice& lveDevice) {

                std::vector<LveModel::Vertex> uniqueVertices{};
                for (int i = 0; i < numSides; i++) {
                    float angle = i * glm::two_pi<float>() / numSides;
                    uniqueVertices.push_back({{radius * glm::cos(angle),radius * glm::sin(angle)}});
                }
                MeshData meshData = {createPolygon(uniqueVertices, lveDevice), 1, type};
                return meshData;
            }

            MeshData createRectModel(float width, float height, const char* type, LveDevice& lveDevice){
                LveModel::Vertex t_r = {{width/2, height/2}};
                LveModel::Vertex t_l = {{-width/2, height/2}};
                LveModel::Vertex b_r = {{width/2, -height/2}};
                LveModel::Vertex b_l = {{-width/2, -height/2}};

                std::vector<LveModel::Vertex> uniqueVertices = {t_l, t_r, b_r, b_l};

                MeshData meshData = {createPolygon(uniqueVertices, lveDevice), 1, type};
                return meshData;
            }

            MeshData createLineModel(float scale, float theta, const char* type, LveDevice& lveDevice){
                float width = .1f * scale;
                float height = 0.005f;
                LveModel::Vertex t_r = {{width, height/2}};
                LveModel::Vertex t_l = {{0, height/2}};
                LveModel::Vertex b_r = {{width, -height/2}};
                LveModel::Vertex b_l = {{0, -height/2}};

                std::vector<LveModel::Vertex> uniqueVertices = {t_l, t_r, b_r, b_l};

                std::vector<LveModel::Vertex> rotatedVertices = rotateVectors(uniqueVertices, theta);



                MeshData meshData = {createPolygon(rotatedVertices, lveDevice), 1, type};
                return meshData;

            }


        private:

        std::unique_ptr<LveModel> createPolygon(std::vector<LveModel::Vertex> vertexList, LveDevice& lveDevice) {

                vertexList.push_back({});  // adds center vertex at 0, 0
                
                // Rotates around the origin and populates triangle segments using points from uniqueVertices
                std::vector<LveModel::Vertex> vertices{};
                int numSides = vertexList.size() - 1;
                for (int i = 0; i < numSides; i++) {
                    vertices.push_back(vertexList[i]);
                    vertices.push_back(vertexList[(i + 1) % numSides]);
                    vertices.push_back(vertexList[numSides]);
                }

                
                return std::make_unique<LveModel>(lveDevice, vertices);
            }
    };
}