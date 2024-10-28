#pragma once

#include "Entity.h"
#include "Mouse.h"
#include "Renderer.h"
#include <memory>
#include <vector>

namespace Minesweeper {
struct Block {
  bool IsOpen{false};
  bool IsFlagged{false};
  bool IsMine{false};
  bool IsExploded{false};
  int NearMineCount{0};
  int Group{0};
};

class Board : public Entity {
public:
  Board(std::shared_ptr<Renderer> renderer, const int boardWidth,
        const int boardHeight, const int mines);
  virtual const Rect GetBox() override;
  virtual const bool OnClick(const int px, const int py,
                             const MouseButton button) override;
  void Render();

private:
  std::shared_ptr<Renderer> m_renderer;
  int m_boardWidth{0};
  int m_boardHeight{0};
  std::vector<std::shared_ptr<Block>> m_blocks{};

private:
  void PlaceMine(const int x, const int y);
  void CreateGroups();
  inline void MergeGroups(const int a, const int b);
  const bool OnLeftClick(const int i);
  const bool OnRightClick(const int i);
  inline int PosToIndex(const int x, const int y);
};
} // namespace Minesweeper
