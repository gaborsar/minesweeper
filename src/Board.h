#pragma once

#include <SDL.h>
#include <random>
#include <utility>

namespace Minesweeper {
struct Block {
  bool IsOpen{false};
  bool IsFlagged{false};
  bool IsMine{false};
  bool IsExploded{false};
  int NearMineCount{0};
  std::pair<int, int> Groups{0, 0};
};

class Board {
public:
  Board();
  ~Board();
  void Move(int x, int y);
  void Init(int boardWidth, int boardHeight, int numberOfMines);

  bool OnInput(const SDL_Event &event);
  void OnRender();

  bool HasChanged() { return m_hasChanged; }
  int GetNumberOfFlags();

private:
  std::mt19937 m_mt;

  int m_x{0};
  int m_y{0};

  int m_boardWidth{0};
  int m_boardHeight{0};

  bool m_hasChanged{false};
  Block *m_blocks;

  void PlaceMine(int x, int y);
  void CreateGroups();
  inline void MergeGroups(int a, int b);

  bool OnLeftClick(int px, int py);
  bool OnRightClick(int px, int py);

  inline int PosToIndex(int x, int y) { return y * m_boardWidth + x; }
};
} // namespace Minesweeper
