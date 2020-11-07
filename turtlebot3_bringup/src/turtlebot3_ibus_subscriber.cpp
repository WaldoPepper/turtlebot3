// ROS includes.
#include <ros/ros.h>
#include <ros/time.h>

#include <ibus_protocol/IBUS.h>
#include <geometry_msgs/Twist.h>

class IBUSSubscriber
{
 public:
  explicit IBUSSubscriber(ros::NodeHandle nh)
  {
      // Create a subscriber.
      // Name the topic, message queue, callback function with class name, and object containing callback function.
      sub_ = nh.subscribe("ibus", 10, &IBUSSubscriber::messageCallback, this);
      pub_ = nh.advertise<geometry_msgs::Twist>("cmd_vel", 10);
  }

  void messageCallback(const ibus_protocol::IBUS& msg)
    {
        geometry_msgs::Twist vel_msg;

        ROS_INFO("message is %d", msg.ch1);

        double angular = double (msg.ch1);
        double speed = double (msg.ch2);

        angular = - angular / 500.0;
        speed = speed / 500.0;

        vel_msg.linear.x = speed;
        vel_msg.linear.y = 0;
        vel_msg.linear.z = 0;
        vel_msg.angular.x = 0;
        vel_msg.angular.y = 0;
        vel_msg.angular.z = angular;

        pub_.publish(vel_msg);
    }

 private:
  ros::Subscriber sub_;
  ros::Publisher pub_;
};

int main(int argc, char **argv)
{
  // Set up ROS.
  ros::init(argc, argv, "ibus_subscriber");
  ros::NodeHandle nh;

  // Create a new node_example::Talker object.
  IBUSSubscriber node(nh);

  // Let ROS handle all callbacks.
  ros::spin();

  return 0;
}




