#pragma once

namespace Utils {
inline bool CheckIfNullptr(void *ptr) {
  if (ptr == nullptr)
    return true;

  return false;
}   
                } // namespace Utils
