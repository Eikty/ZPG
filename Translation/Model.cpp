#define TINYOBJLOADER_IMPLEMENTATION
#include "Model.h"

Model::Model(const float* points, GLsizei pointsCount, Material* material, bool uv) {
    int vertexComponents = uv ? 8 : 6;

	VBO = 0;
	glGenBuffers(1, &VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * pointsCount * vertexComponents, points, GL_STATIC_DRAW);

	VAO = 0;
	glGenVertexArrays(1, &VAO); //generate the VAO
	glBindVertexArray(VAO); //bind the VAO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glEnableVertexAttribArray(0); //enable vertex attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexComponents * sizeof(float), NULL);
	glEnableVertexAttribArray(1); //enable vertex attributes
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertexComponents * sizeof(float), (void*)(3 * sizeof(float)));

    if (uv) {
        glEnableVertexAttribArray(2); //enable vertex attributes
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, vertexComponents * sizeof(float), (void*)(6 * sizeof(float)));
    }

	this->pointsCount = pointsCount;
    this->material = material;
}

Model::Model(const char* name, Material* material) {
    std::string inputfile = std::string("assets/") + name;

    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;

    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, inputfile.c_str(), "assets/");

    if (!warn.empty()) std::cout << "Warn: " << warn << std::endl;
    if (!err.empty()) std::cerr << "Err: " << err << std::endl;
    if (!ret) throw std::runtime_error("Failed to load OBJ file!");

    std::vector<float> vertices;

    for (const auto& shape : shapes) {
        for (const auto& index : shape.mesh.indices) {
            // Position
            vertices.push_back(attrib.vertices[3 * index.vertex_index + 0]);
            vertices.push_back(attrib.vertices[3 * index.vertex_index + 1]);
            vertices.push_back(attrib.vertices[3 * index.vertex_index + 2]);

            // Normals (if exist)
            if (index.normal_index >= 0) {
                vertices.push_back(attrib.normals[3 * index.normal_index + 0]);
                vertices.push_back(attrib.normals[3 * index.normal_index + 1]);
                vertices.push_back(attrib.normals[3 * index.normal_index + 2]);
            }
            else {
                vertices.push_back(0.0f);
                vertices.push_back(0.0f);
                vertices.push_back(0.0f);
            }

            //  UV coordinates (if exist)
            if (index.texcoord_index >= 0) {
                vertices.push_back(attrib.texcoords[2 * index.texcoord_index + 0]);
                vertices.push_back(attrib.texcoords[2 * index.texcoord_index + 1]);
            }
            else {
                vertices.push_back(0.0f);
                vertices.push_back(0.0f);
            }
        }
    }

    VBO = 0;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);


    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    pointsCount = (int)vertices.size() / 3;


    glGenVertexArrays(1, &VAO); //generate the VAO
    glBindVertexArray(VAO); //bind the VAO
    glEnableVertexAttribArray(0); //enable vertex attributes
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1); //enable vertex attributes
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2); //enable vertex attributes
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    this->material = material;
}

void Model::draw() {
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, pointsCount);
}

Material* Model::getMaterial() {
    return material;
}