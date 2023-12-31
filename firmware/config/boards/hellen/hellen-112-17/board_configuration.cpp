/**
 * @file boards/hellen/hellen-112-17/board_configuration.cpp
 *
 * See https://rusefi.com/s/XX
 *
 * @author Andrey Belomutskiy, (c) 2012-2023
 */

#include "pch.h"
#include "defaults.h"
#include "hellen_meta.h"

static void setInjectorPins() {
	engineConfiguration->injectionPins[0] = Gpio::MM100_INJ1;
	engineConfiguration->injectionPins[1] = Gpio::MM100_INJ2;
	engineConfiguration->injectionPins[2] = Gpio::MM100_INJ3;
	engineConfiguration->injectionPins[3] = Gpio::MM100_INJ4;
}

static void setIgnitionPins() {
	engineConfiguration->ignitionPins[0] = Gpio::MM100_IGN1;
	engineConfiguration->ignitionPins[1] = Gpio::MM100_IGN2;
	engineConfiguration->ignitionPins[2] = Gpio::MM100_IGN3;
	engineConfiguration->ignitionPins[3] = Gpio::MM100_IGN4;
}

static void setupVbatt() {
	// 4.7k high side/4.7k low side = 2.0 ratio divider
	engineConfiguration->analogInputDividerCoefficient = 2.0f;

	// set vbatt_divider 5.835
	// 33k / 6.8k
	engineConfiguration->vbattDividerCoeff = (33 + 6.8) / 6.8; // 5.835

	// pin input +12 from Main Relay
	engineConfiguration->vbattAdcChannel = MM100_IN_VBATT;

	engineConfiguration->adcVcc = 3.29f;
}

static void setupDefaultSensorInputs() {
  //  engineConfiguration->vehicleSpeedSensorInputPin = Gpio::H144_IN_VSS;

	engineConfiguration->tps1_1AdcChannel = MM100_IN_TPS_ANALOG;

	engineConfiguration->mafAdcChannel = EFI_ADC_NONE;
	engineConfiguration->map.sensor.hwChannel = H144_IN_MAP1;

//	engineConfiguration->afr.hwChannel = EFI_ADC_NONE;

	engineConfiguration->clt.adcChannel = MM100_IN_CLT_ANALOG;

	engineConfiguration->iat.adcChannel = MM100_IN_IAT_ANALOG;
}

#include "hellen_leds_100.cpp"

void setBoardConfigOverrides() {
	// rev A needs EN pin but newer revisions would potentially not use it
	setHellenMegaEnPin();
	setupVbatt();

	setHellenSdCardSpi1();
	configureHellenMegaAccCS2Pin();
	configureHellenCanTerminator();
	setHellenCan();

	engineConfiguration->clt.config.bias_resistor = 4700;
	engineConfiguration->iat.config.bias_resistor = 4700;

	engineConfiguration->triggerInputPins[0] = Gpio::H144_IN_RES1;
	engineConfiguration->camInputs[0] = Gpio::H144_IN_RES3;

    //ETB1
    // PWM pin
    engineConfiguration->etbIo[0].controlPin = Gpio::MM100_OUT_PWM6;
    // DIR pin
	engineConfiguration->etbIo[0].directionPin1 = Gpio::MM100_SPI2_MISO;
   	// Disable pin
   	engineConfiguration->etbIo[0].disablePin = Gpio::MM100_SPI2_MOSI;
   	// Unused
 	engineConfiguration->etbIo[0].directionPin2 = Gpio::Unassigned;
}

/**
 * @brief   Board-specific configuration defaults.
 *
 * See also setDefaultEngineConfiguration
 *
 * @todo    Add your board-specific code, if any.
 */
void setBoardDefaultConfiguration() {
	setInjectorPins();
	setIgnitionPins();

    // not override since sometimes we have issues?
//	setHellenMMbaro();

	engineConfiguration->displayLogicLevelsInEngineSniffer = true;

	engineConfiguration->globalTriggerAngleOffset = 0;

	engineConfiguration->enableSoftwareKnock = true;

	engineConfiguration->canTxPin = Gpio::MM100_CAN_TX;
	engineConfiguration->canRxPin = Gpio::MM100_CAN_RX;

	engineConfiguration->fuelPumpPin = Gpio::MM100_OUT_PWM5;;
//	engineConfiguration->idle.solenoidPin = Gpio::H144_LS_6;
//	engineConfiguration->fanPin = Gpio::H144_OUT_IO12;
	engineConfiguration->mainRelayPin = Gpio::MM100_IGN8;
//	engineConfiguration->malfunctionIndicatorPin = Gpio::H144_OUT_IO7;

	// how come this is not denso 183?!
	engineConfiguration->map.sensor.type = MT_CUSTOM;
	engineConfiguration->map.sensor.lowValue = 11.4;
	engineConfiguration->mapLowValueVoltage = 0.5;
	engineConfiguration->map.sensor.highValue = 170.7;
	engineConfiguration->mapHighValueVoltage = 4.8;

//	engineConfiguration->brakePedalPin = Gpio::H144_IN_CAM;
//	engineConfiguration->acRelayPin = Gpio::H144_LS_5;
//    engineConfiguration->tachOutputPin = Gpio::H144_OUT_IO10;
    // A/C switch on k-line

	// "required" hardware is done - set some reasonable defaults
	setupDefaultSensorInputs();
	engineConfiguration->enableVerboseCanTx = true;

	engineConfiguration->etbFunctions[0] = DC_Throttle1;

	// Some sensible defaults for other options
	setCrankOperationMode();

	setAlgorithm(LM_SPEED_DENSITY);

	engineConfiguration->injectorCompensationMode = ICM_FixedRailPressure;

	setCommonNTCSensor(&engineConfiguration->clt, HELLEN_DEFAULT_AT_PULLUP);
	setCommonNTCSensor(&engineConfiguration->iat, HELLEN_DEFAULT_AT_PULLUP);

    setTPS1Calibration(100, 650);
	//hellenWbo();
}

static Gpio OUTPUTS[] = {
    Gpio::MM100_INJ1,
    Gpio::MM100_INJ2,
    Gpio::MM100_INJ3,
    Gpio::MM100_INJ4,
};

int getBoardMetaOutputsCount() {
    return efi::size(OUTPUTS);
}

Gpio* getBoardMetaOutputs() {
    return OUTPUTS;
}
