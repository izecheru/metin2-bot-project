#pragma once

#include <Windows.h>
#include <map>
#include <string>

namespace Signature
{
		struct OffsetSig
		{
				const char* signature = nullptr;
				BYTE offset = 0;

				OffsetSig(const char* sig, const BYTE off)
				{
						offset = off;
						signature = sig;
				}
		};

		struct Sig
		{
				const char* signature = nullptr;
				Sig(const char* sig) { signature = sig; }
		};

		inline auto PythonModules = Sig("68 ?? ?? ?? ?? 6A 00 6A 00 68 ?? ?? ?? ?? 68");

		namespace Calliope
		{
				inline auto InstanceMap =
						OffsetSig("C7 05 ? ? ? ? ? ? ? ? C7 05 ? ? ? ? ? ? ? ? E8 ? ? ? ? 68 ? ? ? "
											"? E8 ? ? ? ? 83 C4 ? 8B 0D",
											0x1);

				inline auto CPythonCharacterManager = OffsetSig(
						"8B 0D ?? ?? ?? ?? FF 75 ?? 83 C1 ?? 8B 01 FF 50 ?? 8B F0 89 75", 0x2);
				inline auto CPythonNetworkStream = OffsetSig("8B 0D ?? ?? ?? ?? 50 FF B3", 0x2);
				inline std::map<std::string, OffsetSig> mappedClassSignatures = {
						{"CPythonCharacterManager", CPythonCharacterManager},
						{"CPythonNetworkStream", CPythonNetworkStream} };

				inline auto SendUseSkillPacket = Sig("55 8B EC 83 EC ?? A1 ?? ?? ?? ?? 33 C5 "
																						 "89 45 ?? 8B 45 ?? 89 45 ?? 8B 45 ?? 56");
				inline auto SendUseItemPacket =
						Sig("55 8B EC 51 56 8B F1 E8 ?? ?? ?? ?? 84 C0 74 ?? 66 8B 45");
				inline auto SendDropItemPacket =
						Sig("55 8B EC 83 EC ?? 56 8B F1 E8 ?? ?? ?? ?? 84 C0 75 ?? B0 ?? 5E 8B E5 "
								"5D C2 ?? ?? 66 8B 45 ?? 8B CE 66 89 45 ?? 8A 45 ?? 88 45 ?? 8B 45 ?? "
								"89 45 ?? 8B 45");
				inline auto SendMoveItemPacket = Sig("55 8B EC 83 EC ?? 53 56 57 8B F1 E8");
				inline auto CreateInstance = Sig("55 8B EC 83 E4 ?? 51 53 56 8B 75");

				inline std::map<std::string, Sig> mappedFunctionSignatures = {
						{"SendUseSkillPacket", SendUseSkillPacket},
						{"SendUseItemPacket", SendUseItemPacket},
				};
		} // namespace Calliope

		namespace Elaris
		{
				inline auto CPyhtonMiniMap =
						OffsetSig("8B 0D ?? ?? ?? ?? 8B 3D ?? ?? ?? ?? 75", 0x2);
				inline auto CPyhtonBackground = OffsetSig("8B 3D ?? ?? ?? ?? 75", 0x2);
				inline auto CInstanceBase =
						OffsetSig("8B CF E8 ?? ?? ?? ?? 85 C0 75 ?? 68", 0x2);
				inline auto CPythonPlayer =
						OffsetSig("8B 0D ?? ?? ?? ?? 6A ?? 68 ?? ?? ?? ?? 6A ?? E8", 0x2);
				inline auto CItemManager =
						OffsetSig("8B 0D ?? ?? ?? ?? 50 E8 ?? ?? ?? ?? 85 C0 74 ?? 56", 0x2);
				inline auto CPythonItem = OffsetSig("8B 35 ?? ?? ?? ?? 8D 45 ?? 57 8B 7D", 0x2);
				inline auto CFlyingManager =
						OffsetSig("8B 3D ?? ?? ?? ?? A1 ?? ?? ?? ?? F3 0F 10 05", 0x2);
				inline auto CRaceManager =
						OffsetSig("8B 0D ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B F8 85 FF 75 ?? 32 C0", 0x2);
				inline auto CPyhtonCharacterManager =
						OffsetSig("8B 3D ?? ?? ?? ?? 8B 47 ?? 8D 4F", 0x2);
				inline auto CPythonNetworkStream =
						OffsetSig("8B 0D ?? ?? ?? ?? E8 ?? ?? ?? ?? E8 ?? ?? ?? ?? 5E 8B E5 5D C3 "
											"CC CC CC 55 8B EC 51",
											0x2);

				// Function signatures
				inline auto PatchMetinAutofarm = Sig("83 F8 ?? 72 ?? 8B 35");
				inline auto SendShopSellPacket =
						Sig("55 8B EC 51 56 8B F1 E8 ?? ?? ?? ?? 84 C0 75 ?? B0 ?? 5E 8B E5 5D C2 "
								"?? ?? 8D 45 ?? 66 C7 45 ?? ?? ?? 50 6A ?? 8B CE E8 ?? ?? ?? ?? 84 C0 "
								"75 ?? 68 ?? ?? ?? ?? E8 ?? ?? ?? ?? 83 C4 ?? 32 C0 5E 8B E5 5D C2 ?? "
								"?? 8D 45 ?? 8B CE 50 6A ?? E8 ?? ?? ?? ?? 84 C0 75 ?? 68 ?? ?? ?? ?? "
								"E8 ?? ?? ?? ?? 83 C4 ?? 32 C0 5E 8B E5 5D C2 ?? ?? 8B CE E8 ?? ?? ?? "
								"?? 5E 8B E5 5D C2 ?? ?? CC CC CC CC CC 55 8B EC 51");

				inline const auto SendPacket = Sig("55 8B EC 56 8B F1 57 8B 7D ?? 8B 56");
				inline auto SendUseSkill = Sig("55 8B EC 83 EC ?? A1 ?? ?? ?? ?? 33 C5 89 45 "
																			 "?? 8B 45 ?? 89 45 ?? 8B 45 ?? 56");
				inline auto CanUseSkill =
						Sig("E8 ?? ?? ?? ?? 84 C0 74 ?? E8 ?? ?? ?? ?? 83 F8 ?? 0F 97 C0");
				inline auto GetMainInstancePtr =
						Sig("8B 41 ?? C3 CC CC CC CC CC CC CC CC CC CC CC CC CC 55 8B EC 81 EC");
				inline auto SetAutoAttackTarget = Sig("55 8B EC 8B 45 ?? 89 41 ?? 5D C2 ?? ?? "
																							"CC CC CC 55 8B EC 83 EC ?? 53 56 8B F1");

				inline auto SendItemDropPacket =
						Sig("55 8B EC 83 EC ?? 56 8B F1 E8 ?? ?? ?? ?? 84 C0 75 ?? B0 ?? 5E 8B E5 "
								"5D C2 ?? ?? 66 8B 45 ?? 8B CE 66 89 45 ?? 8A 45 ?? 88 45 ?? 8B 45 ?? "
								"89 45 ?? 8D 45");
				inline auto RecvPacket =
						Sig("55 8B EC 5D E9 ?? ?? ?? ?? CC CC CC CC CC CC CC 55 8B EC 56 8B F1 57");
				inline auto SendItemUsePacket =
						Sig("55 8B EC 51 56 8B F1 E8 ?? ?? ?? ?? 84 C0 74 ?? 66 8B 45");

				inline std::map<std::string, Sig> mappedFunctionSignatures = {
						{"SendItemUsePacket", SendItemUsePacket},
						{"RecvPacket", RecvPacket},
						{"SendItemDropPacket", SendItemDropPacket},
						{"SetAutoAttackTarget", SetAutoAttackTarget},
						{"GetMainInstancePtr", GetMainInstancePtr},
						{"CanUseSkill", CanUseSkill},
						{"SendUseSkill", SendUseSkill},
						{"SendPacket", SendPacket},
						{"PatchMetinAutofarm", PatchMetinAutofarm} };

				inline std::map<std::string, OffsetSig> mappedClassSignatures = {
						{"CPyhtonBackground", CPyhtonBackground},
						{"CPythonPlayer", CPythonPlayer},
						{"CItemManager", CItemManager},
						{"CPythonItem", CPythonItem},
						{"CFlyingManager", CFlyingManager},
						{"CRaceManager", CRaceManager},
						{"CPyhtonCharacterManager", CPyhtonCharacterManager},
						{"CPythonNetworkStream", CPythonNetworkStream} };
		}; // namespace Elaris
} // namespace Signature
