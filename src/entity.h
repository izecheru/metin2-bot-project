#pragma once
#include "utils.h"
#include <Windows.h>
#include <map>
#include <mutex>
#include <vector>

namespace Entity {
struct Vector3 {
  float x, y, z;
};

class Mob {
public:
  char pad_0000[96];   // 0x0000
  char entityName[20]; // 0x0060 something else
  char pad_0074[4];    // 0x0074
  int32_t vid;         // 0x0078
  char pad_007C[68];   // 0x007C
  int32_t level;       // 0x00C0
  char pad_00C4[680];  // 0x00C4
  float fRot;          // 0x036C
  char pad_0370[24];   // 0x0370
  Vector3 location;    // 0x0388
  char pad_0394[3008]; // 0x0394
}; // Size: 0x0F54

inline std::vector<Mob> entityList;
inline std::mutex entityListMutex; // Mutex to protect vector operations
} // namespace Entity
