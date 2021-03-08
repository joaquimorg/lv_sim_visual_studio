/*
 * PROJECT:   LVGL ported to Windows Desktop
 * FILE:      LVGL.Windows.Desktop.cpp
 * PURPOSE:   Implementation for LVGL ported to Windows Desktop
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#include <chrono>
#include <ctime>
#include <Windows.h>
#include "resource.h"

#if _MSC_VER >= 1200
 // Disable compilation warnings.
#pragma warning(push)
// nonstandard extension used : bit field types other than int
#pragma warning(disable:4214)
// 'conversion' conversion from 'type1' to 'type2', possible loss of data
#pragma warning(disable:4244)
#endif

#include "lvgl/lvgl.h"
#include "lv_drivers/win32drv/win32drv.h"

#include "lv_pinetime_theme.h"
#include "components/Doubles.h"
#include "displayapp/Clock.h"
#include "components/datetime/DateTimeController.h"

using namespace Pinetime;


#if _MSC_VER >= 1200
// Restore compilation warnings.
#pragma warning(pop)
#endif


int main()
{
    lv_init();

    if (!lv_win32_init(
        GetModuleHandleW(NULL),
        SW_SHOW,
        LV_HOR_RES_MAX,
        LV_VER_RES_MAX,
        LoadIconW(GetModuleHandleW(NULL), MAKEINTRESOURCE(IDI_LVGL))))
    {
        return -1;
    }

    lv_theme_t* th = lv_pinetime_theme_init(
        LV_COLOR_WHITE, LV_COLOR_SILVER,
        0,
        &jetbrains_mono_bold_20,
        &jetbrains_mono_bold_20,
        &jetbrains_mono_bold_20,
        &jetbrains_mono_bold_20);

    lv_theme_set_act(th);

    // Set the background to Black
    lv_obj_set_style_local_bg_color(lv_scr_act(), LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0, 0, 0));

    Controllers::DateTime dateTimeController{};
    Controllers::Battery batteryController{};
    Controllers::Ble bleController{};
    Controllers::NotificationManager notificatioManager{};
    Controllers::Settings settingsController{};
    Controllers::HeartRateController heartRateController{};

    Applications::DisplayApp displayApp{};

    auto start = std::chrono::system_clock::now();
    std::time_t t = std::time(0);   // get time now
    std::tm* now = std::localtime(&t);
    dateTimeController.SetTime(now->tm_year + 1900, (now->tm_mon + 1), now->tm_mday, 0, 0, 0, 0, 0);

    // Select Watch Face

    // Digital
    //settingsController.SetClockFace(0);

    // Analog
    settingsController.SetClockFace(1);

    settingsController.SetClockType(Controllers::Settings::ClockType::H12);

    Applications::Screens::Clock display{
        &displayApp,
        dateTimeController,
        batteryController,
        bleController,
        notificatioManager,
        settingsController,
        heartRateController
    };

    while (!lv_win32_quit_signal)
    {
        lv_task_handler();        
        dateTimeController.UpdateTime(0);
        display.Refresh();
        Sleep(10);
    }

    return 0;
}
