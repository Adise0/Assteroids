#pragma once

#include <Crow2D/Crow2D.h>
#include <unordered_map>
#include <vector>

namespace Assteroids::Data {

enum class Stat { Acceleration, Deceleration, TurnSpeed, FireRate, AbilityDamage, MaxSpeed, Count };

class Stats {
  // #region Getters
private:
  short GetAccelerationLevel() const;
  short GetDecelerationLevel() const;
  short GetTurnSpeedLevel() const;
  short GetFireRateLevel() const;
  short GetAbilityDamageLevel() const;
  short GetMaxSpeedLevel() const;

private:
  float GetAcceleration() const;
  float GetDeceleration() const;
  int GetTurnSpeed() const;
  float GetFireRate() const;
  float GetAbilityDamage() const;
  float GetMaxSpeed() const;
  // #endregion

  // #region Data
public:
  GETTER_PROPERTY(Stats, short, accelerationLevel, GetAccelerationLevel);
  GETTER_PROPERTY(Stats, short, decelerationLevel, GetDecelerationLevel);
  GETTER_PROPERTY(Stats, short, turnSpeedLevel, GetTurnSpeedLevel);
  GETTER_PROPERTY(Stats, short, fireRateLevel, GetFireRateLevel);
  GETTER_PROPERTY(Stats, short, abilityDamageLevel, GetAbilityDamageLevel);
  GETTER_PROPERTY(Stats, short, maxSpeedLevel, GetMaxSpeedLevel);

  GETTER_PROPERTY(Stats, float, acceleration, GetAcceleration);
  GETTER_PROPERTY(Stats, float, deceleration, GetDeceleration);
  GETTER_PROPERTY(Stats, int, turnSpeed, GetTurnSpeed);
  GETTER_PROPERTY(Stats, float, fireRate, GetFireRate);
  GETTER_PROPERTY(Stats, float, abilityDamage, GetAbilityDamage);
  GETTER_PROPERTY(Stats, float, maxSpeed, GetMaxSpeed);

public:
  static const short MaxLevel = 5;
  static Stats *Singleton;

private:
  short _accelerationLevel = 1;
  short _decelerationLevel = 1;
  short _turnSpeedLevel = 1;
  short _fireRateLevel = 1;
  short _abilityDamageLevel = 1;
  short _maxSpeedLevel = 1;
  static std::unordered_map<Stat, std::string> _statNames;

private:
  std::vector<float> _accelerationByLevel = {1.0f, 1.3f, 1.5f, 1.8f, 2.5f};
  std::vector<float> _decelerationByLevel = {0.5f, 1.0f, 1.3f, 1.6f, 2.0f};
  std::vector<int> _turnSpeedByLevel = {60, 90, 130, 180, 200};
  std::vector<float> _fireRateByLevel = {1.0f, 1.3f, 1.5f, 1.8f, 2.5f};
  std::vector<float> _abilityDamageByLevel = {10.0f, 20.0f, 30.0f, 50.0f, 100.0f};
  std::vector<float> _maxSpeedByLevel = {2.0f, 4.0f, 6.0f, 8.0f, 10.0f};
  // #endregion

  // #region Contructor
public:
  Stats();
  // #endregion

  // #region Methods
public:
  void Upgrade(Stat stat);
  static std::string GetStatName(Stat stat);
  static Stat GetStatByName(const std::string &statName);

  static int GetStatLevel(Stat stat);
  static float GetStat(Stat stat);
  static float GetStatAtLevel(Stat stat, short level);

  // #endregion
};
} // namespace Assteroids::Data
