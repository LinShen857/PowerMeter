#pragma once

// clang-format off
/* === MODULE MANIFEST V2 ===
module_description: CAN 功率计（电压/电流/功率）
depends:
  - id: LinShen857/CanDevice
    ref: same-or-dev
  - id: LinShen857/CanRouter
    ref: same-or-dev
=== END MANIFEST === */
// clang-format on

#include <cstdint>

#include "CanDevice.hpp"
#include "CanRouter.hpp"
#include "can.hpp"

class PowerMeter : public CanDevice
{
 public:
  PowerMeter(CanRouter& router, CanRouter::Bus bus, uint32_t host_id = 0,
             uint32_t motor_id = 0x213);

  void OnClassicFrame(const LibXR::CAN::ClassicPack& frame) override;
  void UpdateFeedback(const uint8_t* rxdata);

  static PowerMeter* Instance();

  float voltage;
  float current;
  float power;
  uint16_t rx_cnt;

 private:
  static PowerMeter* instance_;
};
