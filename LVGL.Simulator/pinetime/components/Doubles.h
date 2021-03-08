#pragma once 

#include <cstdint>

namespace Pinetime {
  namespace Controllers {
    class Battery{
      public:
      int PercentRemaining() { return 100; }
      bool IsCharging() const { return true; }
      bool IsPowerPresent() const { return true; }
    };
    class Ble{
      public:
      bool IsConnected() { return false; }
    };
    class NotificationManager{
      public:
      bool AreNewNotificationsAvailable() { return true; };
    };
    class HeartRateController{
      public:
      enum class States { Stopped, NotEnoughData, NoTouch, Running};

      States State() const { return States::Running; }
      std::uint8_t HeartRate() const { return 75; }
    };

    class Settings {
        public:        
        void SetClockFace(std::uint8_t face) { clockFace = face; };
        std::uint8_t GetClockFace() { return clockFace; };
        std::uint8_t clockFace = 0;

        enum class ClockType { H24, H12 };

        void SetClockType(ClockType clocktype) { clockType = clocktype; };
        ClockType GetClockType() { return clockType; };

        ClockType clockType = ClockType::H24;

    };
  }
  namespace Applications {
    class DisplayApp {};
  }
}
