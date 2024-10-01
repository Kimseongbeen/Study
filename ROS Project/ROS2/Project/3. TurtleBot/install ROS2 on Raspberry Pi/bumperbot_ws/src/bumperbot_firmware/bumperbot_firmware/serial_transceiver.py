#!/usr/bin/env python3
import serial
import rclpy
from rclpy.node import Node
from std_msgs.msg import String

class SerialTransceiver(Node):
    def __init__(self):
        super().__init__("serial_transceiver")

        self.declare_parameter("port", "/dev/ttyUSB0")
        self.declare_parameter("baudrate", 115200)

        self.port_ = self.get_parameter("port").value
        self.baudrate_ = self.get_parameter("baudrate").value

        self.pub_ = self.create_publisher(String, "serial_receiver", 10)
        self.sub_ = self.create_subscription(String, "serial_transmitter", self.transmit_callback, 10)
        self.arduino_ = serial.Serial(port=self.port_, baudrate=self.baudrate_, timeout=0.1)

        self.frequency_ = 0.01
        self.timer_ = self.create_timer(self.frequency_, self.timer_callback)

    def timer_callback(self):
        if rclpy.ok() and self.arduino_.is_open:
            data = self.arduino_.readline()

            try:
                decoded_data = data.decode("utf-8").strip()
                if decoded_data:
                    msg = String()
                    msg.data = decoded_data
                    self.pub_.publish(msg)
            except:
                pass

    def transmit_callback(self, msg):
        if self.arduino_.is_open:
            self.arduino_.write((msg.data + '\n').encode('utf-8'))

def main():
    rclpy.init()

    serial_transceiver = SerialTransceiver()
    rclpy.spin(serial_transceiver)
    
    serial_transceiver.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()