#pragma once

#include <array>
#include <functional>
#include <memory>
#include <lvgl/lvgl.h>
#include "Screen.h"
#include "../DisplayApp.h"

namespace Pinetime {
  namespace Applications {
    namespace Screens {

      enum class ScreenListModes {UpDown, RightLeft, LongPress};
      template <size_t N>
      class ScreenList : public Screen {
        public:

          ScreenList(DisplayApp* app, uint8_t initScreen, std::array<std::function<std::unique_ptr<Screen>()>, N>&& screens, ScreenListModes mode)
          : Screen(app), initScreen{initScreen}, screens{std::move(screens)}, mode{mode}, current{this->screens[initScreen]()} {
            screenIndex = initScreen;
          }

          ~ScreenList() override {
            lv_obj_clean(lv_scr_act());
          }

          bool Refresh() override {
            running = current->Refresh();
            return running;
          }

          bool OnButtonPushed() override {
            running = false;
            return true;
          }

          

        private:
          
          uint8_t initScreen = 0;
          std::array<std::function<std::unique_ptr<Screen>()>, N> screens;
          ScreenListModes mode = ScreenListModes::UpDown;

          uint8_t screenIndex = 0;          
          std::unique_ptr<Screen> current;

          bool running = true;
      };
    }
  }
}
