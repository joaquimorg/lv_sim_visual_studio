﻿#pragma once

namespace Pinetime {
  namespace Applications {
    class DisplayApp;
    namespace Screens {

        template <class T>
        class DirtyValue {
        public:
            DirtyValue() = default;                      // Use NSDMI
            explicit DirtyValue(T const& v) :value{ v } {}   // Use MIL and const-lvalue-ref
            bool IsUpdated() const { return isUpdated; }
            T const& Get() { this->isUpdated = false; return value; }  // never expose a non-const lvalue-ref
            DirtyValue& operator=(const T& other) {
                if (this->value != other) {
                    this->value = other;
                    this->isUpdated = true;
                }
                return *this;
            }
        private:
            T value{};            // NSDMI - default initialise type
            bool isUpdated{ true }; // NSDMI - use brace initilisation
        };

      class Screen {
        public:
          explicit Screen(DisplayApp* app) : app{app} {}
          virtual ~Screen() = default;
          virtual bool Refresh() = 0;

          /** @return false if the button hasn't been handled by the app, true if it has been handled */
          virtual bool OnButtonPushed() { return false; }

          /** @return false if the event hasn't been handled by the app, true if it has been handled */
        //   virtual bool OnTouchEvent(TouchEvents event) { return false; }
          virtual bool OnTouchEvent(uint16_t x, uint16_t y) { return false; }

        protected:
          DisplayApp* app;
      };
    }
  }
}
