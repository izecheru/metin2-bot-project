#pragma once
#include <Windows.h>
#include <string>
#include <vector>

#include "signature.h"
#include <Psapi.h>

namespace Scanner {
std::uint8_t *PatternScan(void *module, const char *signature);
}
