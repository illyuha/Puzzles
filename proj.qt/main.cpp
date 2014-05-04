#include "main.h"
#include "../Classes/AppDelegate.h"
#include <Testing/ADDeviceEmulator.h>
#include <ADLib/Device/ADAds.h>

using namespace cocos2d;

int CALLBACK WinMain(
        _In_  HINSTANCE,
        _In_  HINSTANCE,
        _In_  LPSTR,
        _In_  int
        )
{
    // TODO: find out what all the third-party code does

    // Q: [non-important bu interesting none the less] What on Earth is handle in C++? (^)

    AppDelegate app;

    ADDeviceEmulator * emulator = ADDeviceEmulator::getInstance();

    // TODO: why custom? why exactly such arguments?
    // Configure emulator
    DeviceConfig custom(Device::Custom);
    custom.setDeviceName("Custom");
    custom.setScreenDencity(1.0);
    custom.setScreenWidth(1920);
    custom.setScreenHeight(1200);

    emulator->setCustomDevice(custom);

    emulator->setFitTheScreen(true);
    emulator->setDevice(Device::IPad2); // TODO: why IPad2?
    emulator->setLanguage("en");
    emulator->setOrientation(Orientation::Portrait);

    return emulator->run();
}

