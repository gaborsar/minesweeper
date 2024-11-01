#pragma once

namespace Minesweeper
{
    enum class UserCommandType
    {
        None,
        MouseButtonDown,
        MouseButtonUp
    };

    enum class MouseButton
    {
        None,
        Left,
        Right
    };

    struct UserCommand
    {
        UserCommandType type{UserCommandType::None};
        MouseButton mouseButton{MouseButton::None};
        int mouseX{0};
        int mouseY{0};
    };
}
