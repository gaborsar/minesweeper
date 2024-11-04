#include "Application.h"

namespace Minesweeper {
Application::Application(const char *title, int w, int h)
    : m_window{Engine::Window{title, w, h}} {}
} // namespace Minesweeper
