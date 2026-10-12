#include "Renderer.h"
#include <iostream>
#include <windows.h>

#include "Colors.h"

Renderer::Renderer() : m_cameraX(0), m_cameraY(0) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if (GetConsoleScreenBufferInfo(hOut, &csbi)) {
        m_consoleWidth = (csbi.srWindow.Right - csbi.srWindow.Left + 1) - 1;
        m_consoleHeight = (csbi.srWindow.Bottom - csbi.srWindow.Top + 1) - 1;
    } else {
        m_consoleWidth = 119;
        m_consoleHeight = 29;
    }

    m_screenBuffer.resize(m_consoleHeight, std::string(m_consoleWidth, ' '));
    m_colorBuffer.resize(m_consoleHeight, std::vector<std::string>(m_consoleWidth, ""));

    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hOut, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hOut, &cursorInfo);
}

int Renderer::getConsoleWidth() const { return m_consoleWidth; }
int Renderer::getConsoleHeight() const { return m_consoleHeight; }
int Renderer::getCameraX() const { return m_cameraX; }
int Renderer::getCameraY() const { return m_cameraY; }

void Renderer::setCamera(int x, int y) {
    m_cameraX = x;
    m_cameraY = y;
}

void Renderer::clearBuffer() {
    for (int y = 0; y < m_consoleHeight; ++y) {
        m_screenBuffer[y].assign(m_consoleWidth, ' ');
    }
}

void Renderer::drawString(int worldX, int worldY, const std::string& str, const std::string& colorCode) {
    int screenX = worldX - m_cameraX;
    int screenY = worldY - m_cameraY;

    if (screenY < 0 || screenY >= m_consoleHeight) return;

    for (size_t i = 0; i < str.length(); ++i) {
        int cx = screenX + static_cast<int>(i);
        if (cx >= 0 && cx < m_consoleWidth) {
            m_screenBuffer[screenY][cx] = str[i];
            m_colorBuffer[screenY][cx] = colorCode;
        }
    }
}

void Renderer::drawFrame(int worldX, int worldY, int w, int h) {
    if (w <= 1 || h <= 1) return;

    drawString(worldX, worldY, std::string(w, '-'), Colors::getInstance()->FRAME_COLOR);
    drawString(worldX, worldY + h - 1, std::string(w, '-'), Colors::getInstance()->FRAME_COLOR);

    for (int i = 1; i < h - 1; ++i) {
        drawString(worldX, worldY + i, "|", Colors::getInstance()->FRAME_COLOR);
        drawString(worldX + w - 1, worldY + i, "|", Colors::getInstance()->FRAME_COLOR);
    }
}

void Renderer::renderToConsole() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleCursorPosition(hOut, {0, 0});


        std::string frame;
        frame.reserve(m_consoleWidth * m_consoleHeight + m_consoleHeight * 10);

        std::string currentColor = "";

        for (int y = 0; y < m_consoleHeight; ++y) {
            for (int x = 0; x < m_consoleWidth; ++x) {
                if (m_colorBuffer[y][x] != currentColor) {
                    currentColor = m_colorBuffer[y][x];
                    frame += (currentColor.empty() ? "\x1b[0m" : currentColor);
                }
                frame += m_screenBuffer[y][x];
            }
            frame += '\n';
        }
        frame += "\x1b[0m";
        std::cout << frame;
}
