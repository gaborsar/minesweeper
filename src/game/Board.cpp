#include "Board.h"
#include "../graphics/SpriteRenderer.h"
#include "../sound/SoundManager.h"
#include "GameSession.h"
#include <cassert>
#include <random>

#define MAX_SIZE 30 * 16

namespace Game {
Board::Board() {
  m_mt = static_cast<std::mt19937>(std::random_device{}());
  m_blocks = new Block[MAX_SIZE]{};
}

Board::~Board() { delete[] m_blocks; }

void Board::Move(int x, int y) {
  m_x = x;
  m_y = y;
}

void Board::Init(int boardWidth, int boardHeight, int numberOfMines) {
  assert(boardHeight * boardWidth <= MAX_SIZE);

  m_boardWidth = boardWidth;
  m_boardHeight = boardHeight;
  m_hasChanged = false;

  for (int i{0}; i < MAX_SIZE; ++i) {
    Block *block{&m_blocks[i]};
    block->IsOpen = false;
    block->IsFlagged = false;
    block->IsMine = false;
    block->IsExploded = false;
    block->NearMineCount = 0;
    block->Groups.first = 0;
    block->Groups.second = 0;
  }

  std::uniform_int_distribution<int> randX{0, m_boardWidth - 1};
  std::uniform_int_distribution<int> randY{0, m_boardHeight - 1};

  for (int i{0}; i < numberOfMines; ++i) {
    int x{randX(m_mt)};
    int y{randY(m_mt)};
    int j{PosToIndex(x, y)};
    while ((&m_blocks[j])->IsMine) {
      x = randX(m_mt);
      y = randY(m_mt);
      j = PosToIndex(x, y);
    }
    PlaceMine(x, y);
  }

  CreateGroups();
}

bool Board::OnInput(const SDL_Event &event) {
  if (event.type != SDL_MOUSEBUTTONDOWN) {
    return false;
  }
  if (event.button.x < m_x || event.button.x > m_x + m_boardWidth * 30) {
    return false;
  }
  if (event.button.y < m_y || event.button.y > m_y + m_boardHeight * 30) {
    return false;
  }

  int x{event.button.x - m_x};
  int y{event.button.y - m_y};

  if (event.button.button == SDL_BUTTON_LEFT) {
    return OnLeftClick(x, y);
  }
  if (event.button.button == SDL_BUTTON_RIGHT) {
    return OnRightClick(x, y);
  }

  return false;
}

void Board::OnRender() {
  for (int y{0}; y < m_boardHeight; ++y) {
    for (int x{0}; x < m_boardWidth; ++x) {
      int i{PosToIndex(x, y)};
      int px{m_x + x * 30};
      int py{m_y + y * 30};
      Block block{m_blocks[i]};
      if (block.IsOpen) {
        if (block.IsExploded) {
          SpriteRenderer::RenderSprite(px, py, Sprites::BlockMineExploded);
          continue;
        }
        if (block.IsMine) {
          SpriteRenderer::RenderSprite(px, py, Sprites::BlockMine);
          continue;
        }
        SpriteRenderer::RenderSprite(px, py,
                                     Sprites::BlockDigits[block.NearMineCount]);
        continue;
      }
      if (block.IsFlagged) {
        SpriteRenderer::RenderSprite(px, py, Sprites::BlockFlagged);
        continue;
      }
      SpriteRenderer::RenderSprite(px, py, Sprites::BlockClosed);
    }
  }
}

int Board::GetNumberOfFlags() {
  int count{0};
  for (int i{0}; i < m_boardHeight * m_boardWidth; ++i) {
    if (m_blocks[i].IsFlagged) {
      count++;
    }
  }
  return count;
}

void Board::PlaceMine(int x, int y) {
  int i1{PosToIndex(x, y)};
  m_blocks[i1].IsMine = true;
  for (int y2{y - 1}; y2 <= y + 1; ++y2) {
    if (y2 < 0 || y2 > m_boardHeight - 1) {
      continue;
    }
    for (int x2{x - 1}; x2 <= x + 1; ++x2) {
      if (x2 < 0 || x2 > m_boardWidth - 1) {
        continue;
      }
      int i2{PosToIndex(x2, y2)};
      ++m_blocks[i2].NearMineCount;
    }
  }
}

void Board::CreateGroups() {
  for (int i{0}; i < m_boardWidth * m_boardHeight; ++i) {
    if (!m_blocks[i].IsMine && m_blocks[i].NearMineCount == 0) {
      m_blocks[i].Groups.first = i + 1;
    }
  }

  for (int y1{0}; y1 < m_boardHeight; ++y1) {
    for (int x1{0}; x1 < m_boardWidth; ++x1) {
      int i1{PosToIndex(x1, y1)};
      Block *block1{&m_blocks[i1]};
      if (block1->IsMine || block1->NearMineCount != 0) {
        continue;
      }
      int g1{block1->Groups.first};
      for (int y2{y1 - 1}; y2 <= y1 + 1; ++y2) {
        if (y2 < 0 || y2 > m_boardHeight - 1) {
          continue;
        }
        for (int x2{x1 - 1}; x2 <= x1 + 1; ++x2) {
          if (x2 < 0 || x2 > m_boardWidth - 1) {
            continue;
          }
          int i2{PosToIndex(x2, y2)};
          Block *block2{&m_blocks[i2]};
          if (block2->IsMine || block2->NearMineCount != 0) {
            continue;
          }
          int g2{block2->Groups.first};
          if (g1 == g2) {
            continue;
          }
          if (g1 < g2) {
            MergeGroups(g1, g2);
          } else {
            MergeGroups(g2, g1);
          }
        }
      }
    }
  }

  for (int y1{0}; y1 < m_boardHeight; ++y1) {
    for (int x1{0}; x1 < m_boardWidth; ++x1) {
      int i1{PosToIndex(x1, y1)};
      Block *block1{&m_blocks[i1]};
      if (block1->IsMine || block1->NearMineCount != 0) {
        continue;
      }
      int g{block1->Groups.first};
      for (int y2{y1 - 1}; y2 <= y1 + 1; ++y2) {
        if (y2 < 0 || y2 > m_boardHeight - 1) {
          continue;
        }
        for (int x2{x1 - 1}; x2 <= x1 + 1; ++x2) {
          if (x2 < 0 || x2 > m_boardWidth - 1) {
            continue;
          }
          int i2{PosToIndex(x2, y2)};
          Block *block2{&m_blocks[i2]};
          if (block2->IsMine || block2->NearMineCount == 0) {
            continue;
          }
          if (block2->Groups.first == g || block2->Groups.second == g) {
            continue;
          }
          assert(block2->Groups.first == 0 || block2->Groups.second == 0);
          if (block2->Groups.first == 0) {
            block2->Groups.first = g;
          } else {
            block2->Groups.second = g;
          }
        }
      }
    }
  }
}

inline void Board::MergeGroups(int g1, int g2) {
  for (int i{0}; i < m_boardWidth * m_boardHeight; ++i) {
    Block *block{&m_blocks[i]};
    if (block->Groups.first != g2) {
      continue;
    }
    block->Groups.first = g1;
  }
}

bool Board::OnLeftClick(int px, int py) {
  int x{px / 30};
  if (x < 0 || x > m_boardWidth - 1) {
    return false;
  }
  int y{py / 30};
  if (y < 0 || y > m_boardHeight - 1) {
    return false;
  }
  int i{PosToIndex(x, y)};
  Block *block{&m_blocks[i]};
  if (block->IsOpen || block->IsFlagged) {
    return false;
  }
  m_hasChanged = true;
  block->IsOpen = true;
  if (block->IsMine) {
    for (int i{0}; i < m_boardHeight * m_boardWidth; ++i) {
      Block *block{&m_blocks[i]};
      block->IsOpen = true;
      block->IsFlagged = false;
    }
    block->IsExploded = true;
    SoundManager::PlayLosingSound();
    GameSession::Lose();
  } else {
    if (block->NearMineCount == 0) {
      int g{block->Groups.first};
      for (int i{0}; i < m_boardHeight * m_boardWidth; ++i) {
        Block *block{&m_blocks[i]};
        if (!block->IsFlagged &&
            (block->Groups.first == g || block->Groups.second == g)) {
          block->IsOpen = true;
        }
      }
    }
    bool hasWon{true};
    for (int i{0}; i < m_boardHeight * m_boardWidth; ++i) {
      Block *block{&m_blocks[i]};
      if (block->IsMine ? block->IsOpen : !block->IsOpen) {
        hasWon = false;
        break;
      }
    }
    if (hasWon) {
      SoundManager::PlayWinningSound();
      GameSession::Win();
    } else {
      SoundManager::PlayClickingSound();
    }
  }
  return true;
}

bool Board::OnRightClick(int px, int py) {
  int x{px / 30};
  if (x < 0 || x > m_boardWidth - 1) {
    return false;
  }
  int y{py / 30};
  if (y < 0 || y > m_boardHeight - 1) {
    return false;
  }
  int i{PosToIndex(x, y)};
  Block *block{&m_blocks[i]};
  if (block->IsOpen) {
    return false;
  }
  block->IsFlagged = !block->IsFlagged;
  return true;
}
} // namespace Game
