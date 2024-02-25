#pragma once
#include <Windows.h>
struct OffsetSig {
		const char* pattern = nullptr;
		const char* mask = nullptr;
		BYTE offset = 0;
		OffsetSig(const char* p, const char* m, BYTE off) {
				pattern = p;
				mask = m;
				offset = off;
		}
};

struct Sig {
		const char* pattern;
		const char* mask;
		Sig(const char* p, const char* m) {
				pattern = p;
				mask = m;
		}
};

namespace elaris {

		inline OffsetSig AliveMap
		(
				"\x8D\x4E\x00\xE8\x00\x00\x00\x00\x8B\x7D\x00\x8B\x45",
				"xx?x????xx?xx",
				0x2
		);

		inline OffsetSig CPythonNetworkStream
		(
				"\x8B\x0D\x00\x00\x00\x00\xE8\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x5E\x8B\xE5\x5D\xC3\xCC\xCC\xCC\x55\x8B\xEC\x51",
				"xx????x????x????xxxxxxxxxxxx",
				0x2
		);

		inline OffsetSig  CPythonCharacterManager
		(
				"\x8B\x0D\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x85\xC0\x0F\x84\x00\x00\x00\x00\x8D\x4C\x24",
				"xx????x????xxxx????xxx",
				0x2
		);

		inline OffsetSig  CPythonPlayer
		(
				"\x8B\x3D\x00\x00\x00\x00\x33\xF6\x66\x90",
				"xx????xxxx",
				0x2
		);

		inline Sig CActorInstance
		(
				"\x83\xB9\x00\x00\x00\x00\x00\x0F\x94\xC0\xC3\xCC\xCC\xCC\xCC\xCC\x8B\x81\x00\x00\x00\x00\xC3\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xE8",
				"xx?????xxxxxxxxxxx????xxxxxxxxxxx"
		);

		// function signatures
		inline Sig SendUseSkill
		(
				"\x55\x8B\xEC\x83\xEC\x00\xA1\x00\x00\x00\x00\x33\xC5\x89\x45\x00\x8B\x45\x00\x89\x45\x00\x8B\x45\x00\x56",
				"xxxxx?x????xxxx?xx?xx?xx?x"
		);
};