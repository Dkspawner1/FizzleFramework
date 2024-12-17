#include <fstream>
#include <sstream>
#include <stb_image.h>
#include <Content/SpriteFont.h>


SpriteFont::SpriteFont(const std::string& name, const std::string& path) : Asset(name) {
    LoadFontFile(path);
}

SpriteFont::~SpriteFont() {
    glDeleteTextures(1, &m_textureID);
}

std::string SpriteFont::GetDirectoryPath(const std::string& filePath) {
    const size_t pos = filePath.find_last_of("/\\");
    return (pos == std::string::npos) ? "" : filePath.substr(0, pos + 1);
}

void SpriteFont::LoadFontFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open font file: " + path);
    }

    std::string line;
    std::string textureName;
    while (std::getline(file, line)) {
        if (line.find("common ") == 0) {
            std::istringstream iss(line);
            std::string token;
            while (iss >> token) {
                if (token.find("lineHeight=") == 0) {
                    m_lineHeight = std::stoi(token.substr(11));
                }
            }
        } else if (line.find("page ") == 0) {
            size_t filePos = line.find("file=");
            if (filePos != std::string::npos) {
                textureName = line.substr(filePos + 6);
                textureName = textureName.substr(0, textureName.length() - 1); // Remove quotes
            }
        } else if (line.find("char ") == 0) {
            std::istringstream iss(line);
            std::string token;

            CharInfo info;
            int id;
            while (iss >> token) {
                if (token.find("id=") == 0) id = std::stoi(token.substr(3));
                if (token.find("x=") == 0) info.x = std::stoi(token.substr(2));
                if (token.find("y=") == 0) info.y = std::stoi(token.substr(2));
                if (token.find("width=") == 0) info.width = std::stoi(token.substr(6));
                if (token.find("height=") == 0) info.height = std::stoi(token.substr(7));
                if (token.find("xoffset=") == 0) info.xoffset = std::stoi(token.substr(8));
                if (token.find("yoffset=") == 0) info.yoffset = std::stoi(token.substr(8));
                if (token.find("xadvance=") == 0) info.xadvance = std::stoi(token.substr(9));
            }
            m_charInfo[static_cast<char>(id)] = info;
        }
    }
    if (!textureName.empty()) {
        std::string texturePath = GetDirectoryPath(path) + textureName;
        LoadTexture(texturePath);
    }
}

void SpriteFont::LoadTexture(const std::string& texturePath) {
    int width, height, channels;
    unsigned char* data = stbi_load(texturePath.c_str(), &width, &height, &channels, STBI_rgb_alpha);
    if (!data) {
        throw std::runtime_error("Failed to load font texture: " + texturePath);
    }
    m_textureWidth = width;
    m_textureHeight = height;
    glGenTextures(1, &m_textureID);
    glBindTexture(GL_TEXTURE_2D, m_textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
}

