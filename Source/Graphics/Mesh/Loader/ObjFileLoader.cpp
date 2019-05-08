#include "ObjFileLoader.h"

ObjFileLoader::ObjFileLoader(const std::string& filePath) : _logger(LoggerFactory::CreateLogger("ObjFileLoader"))
{
    _lines = Files::ReadLines(filePath);
    _logger.Debug(std::to_string(_lines.size()) + " lines loaded");
}

Mesh ObjFileLoader::ReadMesh(Texture* pTexture)
{
    std::vector<GLfloat> vertices;
    std::vector<GLfloat> readUvs;
    std::vector<GLfloat> readNormals;

    std::vector<std::vector<IndexGroup>> faces;

    for (const std::string& line : _lines)
    {
        // Vertices declaration
        if (line.rfind("v ", 0) == 0)
        {
            // Why parts[1] and not 0? well because 'v' is returned by split too.
            std::vector<std::string> parts = Strings::Split(line, ' ');
            vertices.push_back(std::stof(parts[1]));
            vertices.push_back(std::stof(parts[2]));
            vertices.push_back(std::stof(parts[3]));
        }

        // Texture declaration
        else if (line.rfind("vt ", 0) == 0)
        {
            std::vector<std::string> parts = Strings::Split(line, ' ');
            readUvs.push_back(std::stof(parts[1]));
            readUvs.push_back(std::stof(parts[2]));
        }

        // Normal declaration
        else if (line.rfind("vn ", 0) == 0)
        {
            std::vector<std::string> parts = Strings::Split(line, ' ');
            readNormals.push_back(std::stof(parts[1]));
            readNormals.push_back(std::stof(parts[2]));
            readNormals.push_back(std::stof(parts[3]));
        }

        else if (line.rfind("f ", 0) == 0)
        {
            faces.emplace_back();
            // format is vertice/texture/normal
            std::vector<std::string> parts = Strings::Split(line, ' ');
            for (int i = 1; i < parts.size(); i++)
            {
                std::vector<std::string> index = Strings::Split(parts[i], '/');

                IndexGroup group;
                // -1 because in OBJ file array start at index 1
                group.positionIndex = std::stoi(index[0]) - 1;
                group.textureIndex = std::stoi(index[1]) - 1;
                group.normalIndex = std::stoi(index[2]) - 1;

                faces[faces.size() - 1].push_back(group);
            }
        }

        else
        {
            _logger.Warn("Non managed line: " + line); // todo Warn
        }
    }

    _logger.Debug("All lines processed. Converting into mesh");

    return BuildMesh(vertices, readUvs, readNormals, faces, pTexture);
}

Mesh ObjFileLoader::BuildMesh(const std::vector<GLfloat>& vertices,
                              const std::vector<GLfloat>& uvs,
                              const std::vector<GLfloat>& normals,
                              const std::vector<std::vector<IndexGroup>>& faces,
                              Texture* pTexture)
{
    // finally reorder everything and create indices
    std::vector<GLfloat> orderedUvs(vertices.size() * 2);
    std::vector<GLfloat> orderedNormals(vertices.size() * 3);
    std::vector<GLint> indices;
    for (auto& face : faces)
    {
        for (auto& group : face)
        {
            indices.push_back(group.positionIndex);

            // Re order texture coordinates
            if (group.textureIndex >= 0)
            {
                orderedUvs[group.positionIndex * 2] = uvs[group.textureIndex];
                orderedUvs[group.positionIndex * 2 + 1] = 1 - uvs[group.textureIndex + 1];
            }
            if (group.normalIndex >= 0)
            {
                orderedNormals[group.positionIndex * 3] = normals[group.positionIndex];
                orderedNormals[group.positionIndex * 3 + 1] = normals[group.positionIndex + 1];
                orderedNormals[group.positionIndex * 3 + 2] = normals[group.positionIndex + 2];
            }
        }
    }

    return Mesh(vertices, orderedUvs, indices, pTexture);
}