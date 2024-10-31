#pragma once

#include "Level.h"
#include "Renderer.h"
#include "Size.h"
#include "RestartButton.h"
#include <cassert>
#include <memory>

namespace Minesweeper
{
    inline constexpr Size GetWindowSize(int levelWidth, int levelHeight)
    {
        return {20 * 2 + 30 * levelWidth, 20 * 3 + 60 + 30 * levelHeight};
    }

    enum class GameStatus
    {
        Playing,
        Won,
        Lost
    };

    class Game
    {
    public:
        Game(std::shared_ptr<Renderer> renderer, int levelWidth, int levelHeight, int numberOfMines, int time);
        bool OnLeftClick(int px, int py);
        bool OnRightClick(int px, int py);
        bool OnUpdate(int time);
        void OnRender();

    private:
        std::shared_ptr<Renderer> m_renderer;
        GameStatus m_status{GameStatus::Playing};
        int m_levelWidth{0};
        int m_levelHeight{0};
        int m_numberOfMines{0};
        int m_startTime{0};
        int m_updateTime{0};
        int m_elapsedTime{0};
        std::unique_ptr<RestartButton> m_restartButton;
        std::unique_ptr<Level> m_level;

    private:
        void RenderBackground();
        void RenderCounter();
        void RenderTimer();
        void RenderNumber(int px, int py, int n);
        void RenderRestartButton();
    };
} // namespace Minesweeper
