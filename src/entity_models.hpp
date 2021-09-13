#pragma once
#include "lve_model.hpp"
#include <memory>
#include <vector>

namespace lve{
    class ModelBuilder{
        public:

            struct MeshData
            {
                std::shared_ptr<LveModel> mesh;
                std::vector<LveModel::Vertex> vertices;
            };
            

            MeshData createCircleModel(float radius,unsigned int numSides, LveDevice& lveDevice) {

                std::vector<LveModel::Vertex> uniqueVertices{};
                for (int i = 0; i < numSides; i++) {
                    float angle = i * glm::two_pi<float>() / numSides;
                    uniqueVertices.push_back({{radius * glm::cos(angle),radius * glm::sin(angle)}});
                }

                return createPolygon(uniqueVertices, lveDevice);
            }

            MeshData createRectModel(float width, float height, LveDevice& lveDevice){
                LveModel::Vertex t_r = {{width/2, height/2}};
                LveModel::Vertex t_l = {{-width/2, height/2}};
                LveModel::Vertex b_r = {{width/2, -height/2}};
                LveModel::Vertex b_l = {{-width/2, -height/2}};

                std::vector<LveModel::Vertex> uniqueVertices = {t_l, t_r, b_r, b_l};

                return createPolygon(uniqueVertices, lveDevice);
            }


        private:

        MeshData createPolygon(std::vector<LveModel::Vertex> vertexList, LveDevice& lveDevice) {

                vertexList.push_back({});  // adds center vertex at 0, 0
                
                // Rotates around the origin and populates triangle segments using points from uniqueVertices
                std::vector<LveModel::Vertex> vertices{};
                int numSides = vertexList.size() - 1;
                for (int i = 0; i < numSides; i++) {
                    vertices.push_back(vertexList[i]);
                    vertices.push_back(vertexList[(i + 1) % numSides]);
                    vertices.push_back(vertexList[numSides]);
                }

                MeshData meshData = {std::make_unique<LveModel>(lveDevice, vertices), vertices};
                return meshData;
            }
    };
}