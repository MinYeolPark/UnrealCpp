#include "CPlayerState.h"

ACPlayerState::ACPlayerState()
{
	CharacterLevel = 1;
	GameScore = 0;
}

int32 ACPlayerState::GetGameScore() const
{
	return GameScore;
}

int32 ACPlayerState::GetGameHighScore() const
{
	return CharacterLevel;
}

int32 ACPlayerState::GetCharacterLevel() const
{
	return int32();
}

int32 ACPlayerState::GetCharacterIndex() const
{
	return int32();
}

float ACPlayerState::GetExpRatio() const
{
	return 0.0f;
}

bool ACPlayerState::AddExp(int32 IncomeExp)
{
	return false;
}

void ACPlayerState::AddGameScore()
{
}

void ACPlayerState::InitPlayerData()
{
	SetPlayerName(TEXT("Destiny"));
	CharacterLevel = 5;
	GameScore = 0;
}

void ACPlayerState::SavePlayerData()
{
}

void ACPlayerState::SetCharacterLevel(int32 NewCharacterLevel)
{
}
