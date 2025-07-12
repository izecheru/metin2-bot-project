#include "gamePointers.h"
#include "scanner.h"
#include "signature.h"

void GamePointers::Init()
{
  void* base = GetModuleHandle(0);
  CPythonNetworkStream = *reinterpret_cast<uintptr_t*>(Scanner::PatternScan(base, Signature::Calliope::CPythonNetworkStream.signature) + 0x2);
  CPythonCharacterManager = CPythonNetworkStream + 0x20;
  testPtr = *reinterpret_cast<uintptr_t*>(Scanner::PatternScan(base, Signature::Calliope::InstanceMap.signature) + 0x2); // 98

  // does not work atm
  //kAliveInstance = *reinterpret_cast<TCharacterInstanceMap*>(*reinterpret_cast<uintptr_t*>(*reinterpret_cast<uintptr_t*>(CPythonCharacterManager + 0x24) + 0x4));
}