#include "eureka_inverse/main.hpp"

CmdVelProcessor::CmdVelProcessor() : Node("inverse_cmd_vel")
{
    subscription = this->create_subscription<geometry_msgs::msg::Twist>(
        "/custom_cmd_vel", 10, std::bind(&CmdVelProcessor::topic_callback, this, std::placeholders::_1));
    publisher = this->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 10);
}

void CmdVelProcessor::topic_callback(const geometry_msgs::msg::Twist::SharedPtr msg) const
{
    auto modified_msg = geometry_msgs::msg::Twist();
    modified_msg.linear.x = msg->linear.x;
    modified_msg.linear.y = msg->linear.y;
    modified_msg.linear.z = msg->linear.z;

    if (msg->linear.x < 0.0) 
    {
        modified_msg.angular.z = -msg->angular.z;
    } else 
    {
        modified_msg.angular.z = msg->angular.z;
    }
    publisher->publish(modified_msg);
}

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<CmdVelProcessor>());
    rclcpp::shutdown();
    return 0;
}