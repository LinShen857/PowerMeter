#include "PowerMeter.hpp"

PowerMeter* PowerMeter::instance_ = nullptr;

PowerMeter::PowerMeter(CanRouter& router, CanRouter::Bus bus, uint32_t host_id_,
                       uint32_t motor_id_)
    : CanDevice(host_id_, motor_id_), voltage(0.f), current(0.f), power(0.f), rx_cnt(0)
{
  router.Attach(bus, *this);
  instance_ = this;
}

PowerMeter* PowerMeter::Instance()
{
  return instance_;
}

void PowerMeter::OnClassicFrame(const LibXR::CAN::ClassicPack& frame)
{
  UpdateFeedback(frame.data);
}

void PowerMeter::UpdateFeedback(const uint8_t* rxdata)
{
  voltage = static_cast<float>(
                static_cast<int16_t>(static_cast<uint16_t>(static_cast<uint16_t>(rxdata[1]) << 8) |
                                     static_cast<uint16_t>(rxdata[0]))) /
            100.0f;
  current = static_cast<float>(
                static_cast<int16_t>(static_cast<uint16_t>(static_cast<uint16_t>(rxdata[3]) << 8) |
                                     static_cast<uint16_t>(rxdata[2]))) /
            100.0f;
  power = voltage * current;
  ++rx_cnt;
}
