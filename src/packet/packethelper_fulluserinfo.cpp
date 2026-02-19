#include "packethelper_fulluserinfo.h"

using namespace std;

CPacketHelper_FullUserInfo::CPacketHelper_FullUserInfo()
{
}

vector<unsigned char> PackAchievementList(const vector<int>& unpacked)
{
	vector<unsigned char> packed;

	int nextIdx = 0;
	for (int i = 0; i < 128; i++)
	{
		int v28 = i * 8;
		unsigned char pack = 0;
		for (int j = 0; j < 8; j++)
		{
			if ((int)unpacked.size() <= nextIdx)
			{
				packed.push_back(pack);
				if (packed.size() != 128)
				{
					packed.insert(packed.end(), 128 - packed.size(), 0);
				}
				return packed;
			}

			if (v28 && v28 == unpacked[nextIdx])
			{
				nextIdx++;
				pack |= 1 << j;
			}
			v28++;
		}
		packed.push_back(pack);
	}

	return packed;
}

void CPacketHelper_FullUserInfo::Build(Buffer& buf, int userID, const CUserCharacter& character)
{
	// Only mask out bits we have NO handler for.
	// Bit 24 (UFLAG_LOW_UNK24) and bit 31 (UFLAG_LOW_UNK31) are now handled below.
	const int maskedLowFlag = character.lowFlag;
	const int maskedHighFlag = character.highFlag;

	buf.writeInt32_LE(maskedLowFlag);
	buf.writeInt32_LE(maskedHighFlag);

	// bit 0
	if (maskedLowFlag & UFLAG_LOW_NAMEPLATE)
	{
		buf.writeUInt8(0);
		buf.writeUInt32_LE(character.nameplateID);
	}

	// bit 1
	if (maskedLowFlag & UFLAG_LOW_GAMENAME)
	{
		buf.writeStr(character.gameName);
	}

	// bit 2
	if (maskedLowFlag & UFLAG_LOW_GAMENAME2)
	{
		buf.writeStr(character.gameName);

		buf.writeUInt8(0);
		buf.writeUInt8(0);
		buf.writeUInt8(0);
	}

	// bit 3
	if (maskedLowFlag & UFLAG_LOW_LEVEL)
	{
		buf.writeUInt32_LE(character.level);
	}

	// bit 4
	if (maskedLowFlag & UFLAG_LOW_UNK4)
	{
		buf.writeUInt8(0);
	}

	// bit 5
	if (maskedLowFlag & UFLAG_LOW_EXP)
	{
		buf.writeUInt64_LE(character.exp);
	}

	// bit 6
	if (maskedLowFlag & UFLAG_LOW_CASH)
	{
		buf.writeUInt64_LE(character.cash);
	}

	// bit 7
	if (maskedLowFlag & UFLAG_LOW_POINTS)
	{
		buf.writeUInt64_LE(character.points);
	}

	// bit 8
	if (maskedLowFlag & UFLAG_LOW_STAT)
	{
		buf.writeUInt32_LE(character.battles);
		buf.writeUInt32_LE(character.win);
		buf.writeUInt32_LE(character.kills);
		buf.writeUInt32_LE(character.deaths);
		buf.writeUInt32_LE(0); // zombie kills
		buf.writeUInt32_LE(0); // survivals
		buf.writeUInt32_LE(0); // total zombie kills
		buf.writeUInt32_LE(0); // total infect count
		buf.writeUInt32_LE(0); // avg round damage
		buf.writeUInt32_LE(0); // avg infect count
		buf.writeUInt32_LE(0); // total num of kills
		buf.writeUInt32_LE(0); // total num of death
		buf.writeUInt32_LE(0); // number of CT wins
		buf.writeUInt32_LE(0); // number of T wins
		buf.writeUInt32_LE(0); // ZombieTendencyTypeA
		buf.writeUInt32_LE(0); // weapon
		buf.writeUInt32_LE(0); // ZombieTendencyTypeC
		buf.writeUInt32_LE(0); // OriginalTendencyTypeA
		buf.writeUInt32_LE(0); // weapon
		buf.writeUInt32_LE(0); // OriginalTendencyTypeC
	}

	// bit 9
	if (maskedLowFlag & UFLAG_LOW_LOCATION)
	{
		buf.writeStr(character.regionName);

		buf.writeUInt16_LE(character.nation);
		buf.writeUInt16_LE(character.city);
		buf.writeUInt16_LE(character.town);

		buf.writeStr(""); // PCBang name
	}

	// bit 10
	if (maskedLowFlag & UFLAG_LOW_CASH2)
	{
		buf.writeUInt32_LE(0);
	}

	// bit 11
	if (maskedLowFlag & UFLAG_LOW_UNK11)
	{
		buf.writeUInt8(0); // count = 0, no loop entries
	}

	// bit 12
	if (maskedLowFlag & UFLAG_LOW_CLAN)
	{
		buf.writeUInt32_LE(character.clanID);
		buf.writeUInt32_LE(character.clanMarkID);
		buf.writeStr(character.clanName);

		buf.writeUInt8(0);
		buf.writeUInt8(0);
		buf.writeUInt8(0);
	}

	// bit 13
	if (maskedLowFlag & UFLAG_LOW_TOURNAMENT)
	{
		buf.writeUInt8(character.tournament); // bitmask: bit0=565, bit1=566, bit3=567, bit2=568
	}

	// bit 14
	if (maskedLowFlag & UFLAG_LOW_RANK)
	{
		buf.writeUInt8(0xFF); // bitmask: which of 4 rank slots are present (0xFF = all 4)
		for (int i = 0; i < 4; i++)
			buf.writeUInt8(character.tier[i]);
		buf.writeUInt8(character.leagueID);
	}

	// bit 15 - IDA reads exactly 2 bytes: ReadUInt8(602) + ReadUInt8(603)
	if (maskedLowFlag & UFLAG_LOW_UNK15)
	{
		buf.writeUInt8(0);
		buf.writeUInt8(0);
	}

	// bit 16
	if (maskedLowFlag & UFLAG_LOW_PASSWORDBOXES)
	{
		buf.writeUInt16_LE(character.passwordBoxes);
	}

	// bit 17
	if (maskedLowFlag & UFLAG_LOW_UNK17)
	{
		buf.writeUInt32_LE(0);
	}

	// bit 18
	if (maskedLowFlag & UFLAG_LOW_ACHIEVEMENT)
	{
		buf.writeUInt16_LE(character.prefixId);
		buf.writeUInt8(0);
		buf.writeUInt8(0);
		buf.writeUInt32_LE(character.honorPoints);
	}

	// bit 19
	if (maskedLowFlag & UFLAG_LOW_ACHIEVEMENTLIST)
	{
		vector<int> list = character.achievementList;
		sort(list.begin(), list.end());
		buf.writeArray(PackAchievementList(character.achievementList));
	}

	// bit 20
	if (maskedLowFlag & UFLAG_LOW_UNK20)
	{
		buf.writeUInt16_LE(0);
		buf.writeUInt16_LE(0);
		buf.writeUInt16_LE(0);
		buf.writeUInt16_LE(0);
		buf.writeUInt16_LE(0);
	}

	// bit 21
	if (maskedLowFlag & UFLAG_LOW_UNK21)
	{
		buf.writeUInt8(0);
		buf.writeUInt32_LE(0);
	}

	// bit 22
	if (maskedLowFlag & UFLAG_LOW_TITLES)
	{
		if (character.titles.size() == 5)
		{
			for (auto titleID : character.titles)
				buf.writeUInt16_LE(titleID);
		}
		else
		{
			for (int i = 0; i < 5; i++)
				buf.writeUInt16_LE(0);
		}
	}

	// bit 23 - IDA reads exactly 1 byte: ReadUInt8(644)
	if (maskedLowFlag & UFLAG_LOW_UNK23)
	{
		buf.writeUInt8(0);
	}

	// bit 24 - IDA reads exactly 1 byte: ReadUInt8(648)
	if (maskedLowFlag & UFLAG_LOW_UNK24)
	{
		buf.writeUInt8(0);
	}

	// bit 25
	if (maskedLowFlag & UFLAG_LOW_UNK25)
	{
		buf.writeUInt16_LE(0);
	}

	// bit 26
	if (maskedLowFlag & UFLAG_LOW_UNK26)
	{
		buf.writeUInt32_LE(character.mileagePoints);
		buf.writeUInt32_LE(0); // achievement points
	}

	// bit 27
	if (maskedLowFlag & UFLAG_LOW_UNK27)
	{
		buf.writeUInt32_LE(userID);
	}

	// bit 28
	if (maskedLowFlag & UFLAG_LOW_UNK28)
	{
		buf.writeUInt8(0); // count = 0
	}

	// bit 29
	if (maskedLowFlag & UFLAG_LOW_UNK29)
	{
		buf.writeUInt8(0); // count = 0
	}

	// bit 30 - IDA reads exactly 2 bytes: ReadUInt8(680) + ReadUInt8(684)
	if (maskedLowFlag & UFLAG_LOW_UNK30)
	{
		buf.writeUInt8(0);
		buf.writeUInt8(0);
	}

	// bit 31 - IDA reads: 7x ReadUInt32 + 2x ReadUInt8 = 30 bytes
	if (maskedLowFlag & UFLAG_LOW_UNK31)
	{
		buf.writeUInt32_LE(0); // a4+688
		buf.writeUInt32_LE(0); // a4+692
		buf.writeUInt32_LE(0); // a4+696
		buf.writeUInt32_LE(0); // a4+700
		buf.writeUInt32_LE(0); // a4+704
		buf.writeUInt32_LE(0); // a4+708
		buf.writeUInt32_LE(0); // a4+712
		buf.writeUInt8(0);     // a4+716
		buf.writeUInt8(0);     // a4+717
	}

	// highFlag bit 0 (UFLAG_HIGH_CHATCOLOR) - IDA reads ReadUInt16(748)
	if (maskedHighFlag & UFLAG_HIGH_CHATCOLOR)
	{
		buf.writeInt16_LE(character.chatColorID);
	}
}