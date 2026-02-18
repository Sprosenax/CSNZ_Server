#pragma once

#include "definitions.h"
#include "nlohmann/json.hpp"
#include <cstdint>

using json = nlohmann::json;
using ordered_json = nlohmann::ordered_json;

class CServerConfig
{
public:
	CServerConfig();
	~CServerConfig();

	bool Load();
	void LoadDefaultConfig(ordered_json& cfg);

	std::string hostName;
	std::string description;
	std::string tcpPort;
	std::string udpPort;
	int tcpSendBufferSize;
	int maxPlayers;
	std::string welcomeMessage;
	bool restartOnCrash;
	int inventorySlotMax;
	bool checkClientBuild;
	int allowedClientTimestamp;
	int allowedLauncherVersion;
	int maxRegistrationsPerIP;
	uint64_t metadataToSend;
	DefaultUser defUser;
	std::vector<Notice_s> notices;
	ServerConfigGameMatch_s gameMatch;
	ServerConfigRoom_s room;
	int activeMiniGamesFlag;
	int flockingFlyerType;
	ServerConfigBingo bingo;
	WeaponReleaseConfig weaponRelease;
	std::vector<std::string> nameBlacklist;
	std::vector<Survey> surveys;
	bool ssl;
	bool crypt;
	int mainMenuSkinEvent;
	int banListMaxSize;
	std::string voxelHTTPIP;
	std::string voxelHTTPPort;
	std::string voxelVxlURL;
	std::string voxelVmgURL;
	std::vector<std::string> dedicatedServerWhitelist;

	struct VipTier
	{
		std::string name;
		int pointsRequired;
		// Case 8 rank privileges data
		int mileagePayback;         // shown as "Mileage Payback: X"
		float mileageRate;          // mileage rate multiplier
		std::vector<int> subItems;  // sub-item IDs (reward box items etc)
		uint8_t unk24;
		uint8_t unk25;
		uint8_t zombieScenario;     // "Clear Easy in Zombie Scenario" flag
		uint8_t loginSupplies;      // "Login Supplies Login" count
		uint8_t unk28;
		uint8_t unk30;
		uint8_t unk31;
		uint8_t unk32;
	};
	std::vector<VipTier> vipTiers; // index = vipLevel (0=None, 1=Bronze, ..., 7=VVIP)
};

extern class CServerConfig* g_pServerConfig;