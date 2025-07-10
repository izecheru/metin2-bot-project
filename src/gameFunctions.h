#pragma once
#include "entity.h"
#include <Windows.h>
#include <vector>

using SetAutoAttackTarget_t = int(__thiscall*)(void*, int targetVID);

// those functions work
using SendDropItemPacket_t = char(__thiscall*)(void* pCNetwork, int itemPos,
  int zero, int amount);
using SendUseSkillPacket_t = bool(__thiscall*)(void*, int index, int target);

using SendUseItemPacket_t = char(__thiscall*)(void* pCNetwork, int itemPos);

using SendMoveItemPacket_t = char(__thiscall*)(void* pCNetwork, int fromPos,
  int toPos, int amount);

namespace GameFunction
{
  /// Initialize the function pointers
  void Init();

  inline SendUseItemPacket_t pSendUseItemPacket;
  inline SendDropItemPacket_t pSendDropItemPacket;
  inline SendMoveItemPacket_t pSendMoveItemPacket;

  /// Uses the item specified by the index provided as parameter
  void SendItemUsePacket(int itemPos);

  /// Drops the item specified by the item pos parameter, this function also takes
  /// quantity parameter
  void SendDropItemPacket(int itemPos, int zero, int amount);

  /// <summary>
  /// Moves an item from a slot to another
  /// </summary>
  /// <param name="from"> The slot we take the item from</param>
  /// <param name="to"> The slot we take the item to</param>
  void SendMoveItemPacket(int from, int to, int amount);
}; // namespace GameFunction
