#pragma once
#include <Windows.h>
struct ClassSignature {
		const char* pattern = nullptr;
		const char* mask = nullptr;
		BYTE offset = 0;
		ClassSignature(const char* p, const char* m, BYTE off) {
				pattern = p;
				mask = m;
				offset = off;
		}
};

struct Signature {
		const char* pattern;
		const char* mask;
		Signature(const char* p, const char* m) {
				pattern = p;
				mask = m;
		}
};

namespace elaris {

		inline Signature CActorInstance
		(
				"\x83\xB9\x00\x00\x00\x00\x00\x0F\x94\xC0\xC3\xCC\xCC\xCC\xCC\xCC\x8B\x81\x00\x00\x00\x00\xC3\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xE8",
				"xx?????xxxxxxxxxxx????xxxxxxxxxxx"
		);

		inline ClassSignature CPythonNetworkStream
		(
				"\x8B\x0D\x00\x00\x00\x00\xE8\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x5E\x8B\xE5\x5D\xC3\xCC\xCC\xCC\x55\x8B\xEC\x51",
				"xx????x????x????xxxxxxxxxxxx",
				0x2
		);

		inline ClassSignature  CPythonCharacterManager
		(
				"\x8B\x0D\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x85\xC0\x0F\x84\x00\x00\x00\x00\x8D\x4C\x24",
				"xx????x????xxxx????xxx",
				0x2
		);

		inline ClassSignature  CPythonPlayer
		(
				"\x8B\x3D\x00\x00\x00\x00\x33\xF6\x66\x90",
				"xx????xxxx",
				0x2
		);

		// function signatures
		inline Signature SendUseSkill
		(
				"\x55\x8B\xEC\x83\xEC\x00\xA1\x00\x00\x00\x00\x33\xC5\x89\x45\x00\x8B\x45\x00\x89\x45\x00\x8B\x45\x00\x56",
				"xxxxx?x????xxxx?xx?xx?xx?x"
		);
};