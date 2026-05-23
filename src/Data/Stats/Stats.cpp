#include "Stats.h"
#include <algorithm>
#include <cstdio>
#include <stdexcept>

namespace Assteroids::Data {

Stats *Stats::Singleton = nullptr;
std::unordered_map<Stat, std::string> Stats::_statNames = {
    {Stat::Acceleration, "Acceleration"}, {Stat::AbilityDamage, "AbilityDamage"},
    {Stat::Deceleration, "Deceleration"}, {Stat::MaxSpeed, "MaxSpeed"},
    {Stat::TurnSpeed, "TurnSpeed"},       {Stat::FireRate, "FireRate"},
};

short Stats::GetAccelerationLevel() const { return _accelerationLevel; }
short Stats::GetDecelerationLevel() const { return _decelerationLevel; }
short Stats::GetTurnSpeedLevel() const { return _turnSpeedLevel; }
short Stats::GetFireRateLevel() const { return _fireRateLevel; }
short Stats::GetAbilityDamageLevel() const { return _abilityDamageLevel; }
short Stats::GetMaxSpeedLevel() const { return _maxSpeedLevel; }

float Stats::GetAcceleration() const { return _accelerationByLevel[_accelerationLevel - 1]; }
float Stats::GetDeceleration() const { return _decelerationByLevel[_decelerationLevel - 1]; }
int Stats::GetTurnSpeed() const { return _turnSpeedByLevel[_turnSpeedLevel - 1]; }
float Stats::GetFireRate() const { return _fireRateByLevel[_fireRateLevel - 1]; }
float Stats::GetAbilityDamage() const { return _abilityDamageByLevel[_abilityDamageLevel - 1]; }
float Stats::GetMaxSpeed() const { return _maxSpeedByLevel[_maxSpeedLevel - 1]; }


Stats::Stats() {
  if (Singleton != nullptr) throw std::runtime_error("Statsm singleton already here!");
  Singleton = this;
}

void Stats::Upgrade(Stat stat) {
  short *currentLevel = nullptr;
  switch (stat) {
  case Stat::Acceleration:
    currentLevel = &_accelerationLevel;
    break;
  case Stat::Deceleration:
    currentLevel = &_decelerationLevel;
    break;
  case Stat::TurnSpeed:
    currentLevel = &_turnSpeedLevel;
    break;
  case Stat::FireRate:
    currentLevel = &_fireRateLevel;
    break;
  case Stat::AbilityDamage:
    currentLevel = &_abilityDamageLevel;
    break;
  case Stat::MaxSpeed:
    currentLevel = &_maxSpeedLevel;
    break;
  }

  if (!currentLevel || *currentLevel >= MaxLevel) return;
  (*currentLevel)++;
}

std::string Stats::GetStatName(Stat stat) { return _statNames[stat]; }

Stat Stats::GetStatByName(const std::string &statName) {
  auto it = std::find_if(_statNames.begin(), _statNames.end(),
                         [&statName](const auto &pair) { return pair.second == statName; });

  if (it == _statNames.end()) throw std::runtime_error("Unknown stat \"" + statName + "\"");
  return it->first;
}
} // namespace Assteroids::Data
