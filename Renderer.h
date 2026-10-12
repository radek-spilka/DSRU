//
// Created by PC on 06.05.2026.
//

#ifndef PROJEKT_ZOO_RENDERER_H
#define PROJEKT_ZOO_RENDERER_H

#include <vector>
#include <string>

class Renderer {
private:
    int m_consoleWidth;
    int m_consoleHeight;
    int m_cameraX;
    int m_cameraY;
    std::vector<std::string> m_screenBuffer;
    std::vector<std::vector<std::string>> m_colorBuffer;

public:
    Renderer();

    int getConsoleWidth() const;
    int getConsoleHeight() const;
    int getCameraX() const;
    int getCameraY() const;

    void setCamera(int x, int y);

    void clearBuffer();
    void drawString(int worldX, int worldY, const std::string& str, const std::string& colorCode);
    void drawFrame(int worldX, int worldY, int w, int h);

    void renderToConsole();
};

#endif //PROJEKT_ZOO_RENDERER_H