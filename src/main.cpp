#include "eureka_inverse/main.hpp"

CmdVelProcessor::CmdVelProcessor() 
: Node("inverse_cmd_vel"), 
  filtered_angular_z(0.0), 
  alpha(0.2)
{
    subscription = this->create_subscription<geometry_msgs::msg::Twist>(
        "/custom_cmd_vel", 
        10, 
        std::bind(&CmdVelProcessor::topic_callback, this, std::placeholders::_1));
    
    publisher = this->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 10);
}

void CmdVelProcessor::topic_callback(const geometry_msgs::msg::Twist::SharedPtr msg) const
{
    auto modified_msg = geometry_msgs::msg::Twist();
    modified_msg.linear.x = msg->linear.x;
    modified_msg.linear.y = msg->linear.y;
    modified_msg.linear.z = msg->linear.z;
    filtered_angular_z = alpha * (msg->angular.z/msg->linear.x) + (1.0 - alpha) * filtered_angular_z;
    modified_msg.angular.z = filtered_angular_z;
    publisher->publish(modified_msg);
}

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<CmdVelProcessor>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}