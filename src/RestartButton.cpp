#include "Game.h"
#include "Renderer.h"
#include "RestartButton.h"
#include "Sprites.h"

namespace Minesweeper
{
    RestartButton::RestartButton(int x, int y) : m_x{x}, m_y{y} {}

    bool RestartButton::OnInput(UserCommand &command)
    {
        if (command.type != UserCommandType::MouseButtonDown || command.mouseButton != MouseButton::Left)
        {
            return false;
        }
        if (command.mouseX < m_x || command.mouseX > m_x + 36)
        {
            return false;
        }
        if (command.mouseY < m_y || command.mouseY > m_y + 36)
        {
            return false;
        }

        Game &game{Game::Get()};
        game.Restart();

        return true;
    }

    void RestartButton::OnRender()
    {
        Game &game{Game::Get()};
        bool isSad{game.GetStatus() == GameStatus::Lost};

        Renderer &renderer{Renderer::Get()};
        renderer.RenderSprite(m_x, m_y, isSad ? Sprites::RestartButtonSad : Sprites::RestartButtonHappy);
    }
}
