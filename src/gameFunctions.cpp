#include "gameFunctions.h"
#include "gamePointers.h"
#include "scanner.h"
#include "signature.h"
#include "utils.h"

void GameFunction::Init()
{
  pSendDropItemPacket = reinterpret_cast<SendDropItemPacket_t>(PatternScanner::getInstance()->scan(std::string(Signature::Calliope::SendDropItemPacket.signature)));
  pSendUseItemPacket = reinterpret_cast<SendUseItemPacket_t>(PatternScanner::getInstance()->scan(std::string(Signature::Calliope::SendUseItemPacket.signature)));
  pSendMoveItemPacket = reinterpret_cast<SendMoveItemPacket_t>(PatternScanner::getInstance()->scan(std::string(Signature::Calliope::SendMoveItemPacket.signature)));
}

void GameFunction::SendItemUsePacket(int itemPos)
{
  if (Utils::CheckIfNullptr(*reinterpret_cast<void**>(GamePointers::CPythonNetworkStream)))
    return;

  // first is 1
  // second is 257
  // third is 513
  // so A of n is 1 + ( n - 1) * 256
  const int element = 1 + (itemPos - 1) * 256;
  pSendUseItemPacket(*reinterpret_cast<void**>(GamePointers::CPythonNetworkStream), element);
}

void GameFunction::SendDropItemPacket(int itemPos, int zero, int amount)
{
  if (Utils::CheckIfNullptr(*reinterpret_cast<void**>(GamePointers::CPythonNetworkStream)))
    return;

  // from third to fifth
  for (int inventory = 2; inventory <= 4; inventory++)
  {
    for (int slot = 1; slot <= 45; slot++)
    {
      int itemSlot = inventory * 45 + slot;

      // Calculate the item position based on the formula
      int itemPosition = 1 + (itemSlot - 1) * 256;
      pSendDropItemPacket(*reinterpret_cast<void**>(GamePointers::CPythonNetworkStream), itemPosition, 0, 1);
      Sleep(300);
    }
  }
}

void GameFunction::SendMoveItemPacket(int from, int to, int amount)
{
  if (Utils::CheckIfNullptr(*reinterpret_cast<void**>(GamePointers::CPythonNetworkStream)))
    return;

  pSendMoveItemPacket(*reinterpret_cast<void**>(GamePointers::CPythonNetworkStream), 1 + (from - 1) * 256, 1 + (to - 1) * 256, amount);
}