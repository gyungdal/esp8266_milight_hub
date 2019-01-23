#include <MiLightRadioFactory.h>

MiLightRadioFactory* MiLightRadioFactory::fromSettings(const Settings& settings) {
  switch (settings.radioInterfaceType) {
    case nRF24:
      return new NRF24Factory(settings.csnPin, settings.cePin, settings.rf24PowerLevel);

    case LT8900:
      return new LT8900Factory(settings.csnPin, settings.resetPin, settings.cePin);

    default:
      return NULL;
  }
}

NRF24Factory::NRF24Factory(uint8_t csnPin, uint8_t cePin, RF24PowerLevel rF24PowerLevel)
  : rf24(RF24(cePin, csnPin))
{ 
  rf24.setPALevel(RF24PowerLevelHelpers::rf24ValueFromValue(rF24PowerLevel));
}

MiLightRadio* NRF24Factory::create(const MiLightRadioConfig &config) {
  return new NRF24MiLightRadio(rf24, config);
}

LT8900Factory::LT8900Factory(uint8_t csPin, uint8_t resetPin, uint8_t pktFlag)
  : _csPin(csPin),
    _resetPin(resetPin),
    _pktFlag(pktFlag)
{ }

MiLightRadio* LT8900Factory::create(const MiLightRadioConfig& config) {
  return new LT8900MiLightRadio(_csPin, _resetPin, _pktFlag, config);
}
