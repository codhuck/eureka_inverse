#include <memory>
#include <cmath>
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"

class CmdVelProcessor : public rclcpp::Node
{
public:
    CmdVelProcessor();

private:
    void topic_callback(const geometry_msgs::msg::Twist::SharedPtr msg) const;

    rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr subscription;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher;
    mutable double filtered_angular_z;
    const double alpha;
};

