#ifndef BUMPERBOT_FIRMWARE__BUMPERBOT_INTERFACE_HPP_
#define BUMPERBOT_FIRMWARE__BUMPERBOT_INTERFACE_HPP_

#include <hardware_interface/system_interface.hpp>
#include <libserial/SerialPort.h>
#include <rclcpp/rclcpp.hpp>

using hardware_interface::CallbackReturn;
using hardware_interface::return_type;

namespace bumperbot_firmware
{
class BumperbotInterface : public hardware_interface::SystemInterface
{
public:
  BumperbotInterface();
  virtual ~BumperbotInterface();

  CallbackReturn on_init(const hardware_interface::HardwareInfo & info) override;

  std::vector<hardware_interface::StateInterface> export_state_interfaces() override;

  std::vector<hardware_interface::CommandInterface> export_command_interfaces() override;

  CallbackReturn on_activate(const rclcpp_lifecycle::State & previous_state) override;

  CallbackReturn on_deactivate(const rclcpp_lifecycle::State & previous_state) override;

  return_type read(const rclcpp::Time & time, const rclcpp::Duration & period) override;

  return_type write(const rclcpp::Time & time, const rclcpp::Duration & period) override;

private:
  LibSerial::SerialPort arduino_;
  std::string port_;

  std::vector<double> velocity_commands_;
  std::vector<double> position_states_;
  std::vector<double> velocity_states_;

  rclcpp::Time last_run_;
};

}  // namespace bumperbot_firmware

#endif  // BUMPERBOT_FIRMWARE__BUMPERBOT_INTERFACE_HPP_