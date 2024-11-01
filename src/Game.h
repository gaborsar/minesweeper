#pragma once

#include "Board.h"
#include "Core.h"
#include "Input.h"
#include "RestartButton.h"
#include <memory>

namespace Minesweeper
{
    inline constexpr Size GetWindowSize(int boardWidth, int boardHeight)
    {
        return {20 * 2 + 30 * boardWidth, 20 * 3 + 60 + 30 * boardHeight};
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
        Game(int boardWidth, int boardHeight, int numberOfMines, int time);
        static Game &Get();

        bool OnInput(UserCommand &command);
        bool OnUpdate(int time);
        void OnRender();

        GameStatus GetStatus() { return m_status; }
        void Restart();
        void Win();
        void Lose();

    private:
        GameStatus m_status{GameStatus::Playing};

        int m_boardWidth{0};
        int m_boardHeight{0};
        int m_numberOfMines{0};

        int m_startTime{0};
        int m_updateTime{0};
        int m_elapsedTime{0};

        std::unique_ptr<RestartButton> m_restartButton;
        std::unique_ptr<Board> m_board;

    private:
        bool OnLeftClick(int px, int py);
        bool OnRightClick(int px, int py);
        void RenderBackground();
        void RenderCounter();
        void RenderTimer();
        void RenderNumber(int px, int py, int n);
        void RenderRestartButton();
    };
} // namespace Minesweeper
