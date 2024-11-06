#include "Board.h"
#include "../core/Random.h"
#include "../graphics/SpriteManager.h"
#include "../graphics/SpriteRenderer.h"
#include "../sound/SoundManager.h"
#include "GameSession.h"
#include <cassert>

#define MAX_SIZE 30 * 16

namespace Game
{
  Board::Board()
  {
    m_blocks = new Block[MAX_SIZE]{};
  }

  Board::~Board()
  {
    delete[] m_blocks;
  }

  void Board::Move(int x, int y)
  {
    m_x = x;
    m_y = y;
  }

  void Board::Init(int boardWidth, int boardHeight, int numberOfMines)
  {
    assert(boardHeight * boardWidth <= MAX_SIZE);

    m_boardWidth = boardWidth;
    m_boardHeight = boardHeight;
    m_hasChanged = false;

    for (int i{0}; i < MAX_SIZE; ++i)
    {
      Block *block{&m_blocks[i]};
      block->isOpen = false;
      block->isFlagged = false;
      block->isMine = false;
      block->isExploded = false;
      block->nearMineCount = 0;
      block->groups.first = 0;
      block->groups.second = 0;
    }

    for (int i{0}; i < numberOfMines; ++i)
    {
      int x{Random::Int(0, m_boardWidth - 1)};
      int y{Random::Int(0, m_boardHeight - 1)};
      int j{PosToIndex(x, y)};
      while ((&m_blocks[j])->isMine)
      {
        x = Random::Int(0, m_boardWidth - 1);
        y = Random::Int(0, m_boardHeight - 1);
        j = PosToIndex(x, y);
      }
      PlaceMine(x, y);
    }

    CreateGroups();
  }

  bool Board::OnInput(const SDL_Event &event)
  {
    if (event.type != SDL_MOUSEBUTTONDOWN)
    {
      return false;
    }
    if (event.button.x < m_x || event.button.x > m_x + m_boardWidth * 30)
    {
      return false;
    }
    if (event.button.y < m_y || event.button.y > m_y + m_boardHeight * 30)
    {
      return false;
    }

    int x{event.button.x - m_x};
    int y{event.button.y - m_y};

    if (event.button.button == SDL_BUTTON_LEFT)
    {
      return OnLeftClick(x, y);
    }
    if (event.button.button == SDL_BUTTON_RIGHT)
    {
      return OnRightClick(x, y);
    }

    return false;
  }

  void Board::OnRender()
  {
    for (int y{0}; y < m_boardHeight; ++y)
    {
      for (int x{0}; x < m_boardWidth; ++x)
      {
        int i{PosToIndex(x, y)};
        int px{m_x + x * 30};
        int py{m_y + y * 30};
        Block block{m_blocks[i]};
        if (block.isOpen)
        {
          if (block.isExploded)
          {
            SpriteRenderer::RenderSprite(px, py, SpriteManager::BlockMineExploded);
            continue;
          }
          if (block.isMine)
          {
            SpriteRenderer::RenderSprite(px, py, SpriteManager::BlockMine);
            continue;
          }
          SpriteRenderer::RenderSprite(px, py, SpriteManager::BlockDigits[block.nearMineCount]);
          continue;
        }
        if (block.isFlagged)
        {
          SpriteRenderer::RenderSprite(px, py, SpriteManager::BlockFlagged);
          continue;
        }
        SpriteRenderer::RenderSprite(px, py, SpriteManager::BlockClosed);
      }
    }
  }

  bool Board::HasChanged()
  {
    return m_hasChanged;
  }

  int Board::GetNumberOfFlags()
  {
    int count{0};
    for (int i{0}; i < m_boardHeight * m_boardWidth; ++i)
    {
      if (m_blocks[i].isFlagged)
      {
        count++;
      }
    }
    return count;
  }

  void Board::PlaceMine(int x, int y)
  {
    int i1{PosToIndex(x, y)};
    m_blocks[i1].isMine = true;
    for (int y2{y - 1}; y2 <= y + 1; ++y2)
    {
      if (y2 < 0 || y2 > m_boardHeight - 1)
      {
        continue;
      }
      for (int x2{x - 1}; x2 <= x + 1; ++x2)
      {
        if (x2 < 0 || x2 > m_boardWidth - 1)
        {
          continue;
        }
        int i2{PosToIndex(x2, y2)};
        ++m_blocks[i2].nearMineCount;
      }
    }
  }

  void Board::CreateGroups()
  {
    for (int i{0}; i < m_boardWidth * m_boardHeight; ++i)
    {
      if (!m_blocks[i].isMine && m_blocks[i].nearMineCount == 0)
      {
        m_blocks[i].groups.first = i + 1;
      }
    }

    for (int y1{0}; y1 < m_boardHeight; ++y1)
    {
      for (int x1{0}; x1 < m_boardWidth; ++x1)
      {
        int i1{PosToIndex(x1, y1)};
        Block *block1{&m_blocks[i1]};
        if (block1->isMine || block1->nearMineCount != 0)
        {
          continue;
        }
        int g1{block1->groups.first};
        for (int y2{y1 - 1}; y2 <= y1 + 1; ++y2)
        {
          if (y2 < 0 || y2 > m_boardHeight - 1)
          {
            continue;
          }
          for (int x2{x1 - 1}; x2 <= x1 + 1; ++x2)
          {
            if (x2 < 0 || x2 > m_boardWidth - 1)
            {
              continue;
            }
            int i2{PosToIndex(x2, y2)};
            Block *block2{&m_blocks[i2]};
            if (block2->isMine || block2->nearMineCount != 0)
            {
              continue;
            }
            int g2{block2->groups.first};
            if (g1 == g2)
            {
              continue;
            }
            if (g1 < g2)
            {
              MergeGroups(g1, g2);
            }
            else
            {
              MergeGroups(g2, g1);
            }
          }
        }
      }
    }

    for (int y1{0}; y1 < m_boardHeight; ++y1)
    {
      for (int x1{0}; x1 < m_boardWidth; ++x1)
      {
        int i1{PosToIndex(x1, y1)};
        Block *block1{&m_blocks[i1]};
        if (block1->isMine || block1->nearMineCount != 0)
        {
          continue;
        }
        int g{block1->groups.first};
        for (int y2{y1 - 1}; y2 <= y1 + 1; ++y2)
        {
          if (y2 < 0 || y2 > m_boardHeight - 1)
          {
            continue;
          }
          for (int x2{x1 - 1}; x2 <= x1 + 1; ++x2)
          {
            if (x2 < 0 || x2 > m_boardWidth - 1)
            {
              continue;
            }
            int i2{PosToIndex(x2, y2)};
            Block *block2{&m_blocks[i2]};
            if (block2->isMine || block2->nearMineCount == 0)
            {
              continue;
            }
            if (block2->groups.first == g || block2->groups.second == g)
            {
              continue;
            }
            assert(block2->groups.first == 0 || block2->groups.second == 0);
            if (block2->groups.first == 0)
            {
              block2->groups.first = g;
            }
            else
            {
              block2->groups.second = g;
            }
          }
        }
      }
    }
  }

  void Board::MergeGroups(int g1, int g2)
  {
    for (int i{0}; i < m_boardWidth * m_boardHeight; ++i)
    {
      Block *block{&m_blocks[i]};
      if (block->groups.first != g2)
      {
        continue;
      }
      block->groups.first = g1;
    }
  }

  bool Board::OnLeftClick(int px, int py)
  {
    int x{px / 30};
    if (x < 0 || x > m_boardWidth - 1)
    {
      return false;
    }
    int y{py / 30};
    if (y < 0 || y > m_boardHeight - 1)
    {
      return false;
    }
    int i{PosToIndex(x, y)};
    Block *block{&m_blocks[i]};
    if (block->isOpen || block->isFlagged)
    {
      return false;
    }
    m_hasChanged = true;
    block->isOpen = true;
    if (block->isMine)
    {
      for (int i{0}; i < m_boardHeight * m_boardWidth; ++i)
      {
        Block *block{&m_blocks[i]};
        block->isOpen = true;
        block->isFlagged = false;
      }
      block->isExploded = true;
      SoundManager::PlayLosingSound();
      GameSession::Lose();
    }
    else
    {
      if (block->nearMineCount == 0)
      {
        int g{block->groups.first};
        for (int i{0}; i < m_boardHeight * m_boardWidth; ++i)
        {
          Block *block{&m_blocks[i]};
          if (!block->isFlagged && (block->groups.first == g || block->groups.second == g))
          {
            block->isOpen = true;
          }
        }
      }
      bool hasWon{true};
      for (int i{0}; i < m_boardHeight * m_boardWidth; ++i)
      {
        Block *block{&m_blocks[i]};
        if (block->isMine ? block->isOpen : !block->isOpen)
        {
          hasWon = false;
          break;
        }
      }
      if (hasWon)
      {
        SoundManager::PlayWinningSound();
        GameSession::Win();
      }
      else
      {
        SoundManager::PlayClickingSound();
      }
    }
    return true;
  }

  bool Board::OnRightClick(int px, int py)
  {
    int x{px / 30};
    if (x < 0 || x > m_boardWidth - 1)
    {
      return false;
    }
    int y{py / 30};
    if (y < 0 || y > m_boardHeight - 1)
    {
      return false;
    }
    int i{PosToIndex(x, y)};
    Block *block{&m_blocks[i]};
    if (block->isOpen)
    {
      return false;
    }
    block->isFlagged = !block->isFlagged;
    return true;
  }
} // namespace Game
