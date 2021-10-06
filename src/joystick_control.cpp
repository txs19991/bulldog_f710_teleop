#include <ros/ros.h>
#include <sensor_msgs/Joy.h>
#include <geometry_msgs/Twist.h>



class class_js
{
public:
    class_js();
    ros::Publisher  pub;
    geometry_msgs::Twist vel_cmd;
    int rate;
private:
    ros::NodeHandle n_;
    ros::Subscriber sub_;
    void SubCallback(const sensor_msgs::Joy::ConstPtr& Joy);
    double vlinear,vangular;	
};

class_js::class_js()
{
    vel_cmd.linear.x = 0.0;
    vel_cmd.linear.y = 0.0;
    vel_cmd.angular.z = 0.0;
    sub_ = n_.subscribe("/joy", 10, &class_js::SubCallback, this);
    pub = n_.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
    //default linear velocity:0.3 m/s
    n_.param<double>("vel_linear", vlinear, 0.3);
    //default angular velocity:1 rad/s
    n_.param<double>("vel_angular", vangular, 1); 
    //default /cmd_vel publish rate:20 Hz
    n_.param<int>("pub_rate", rate, 20);
    
    // pub = n_.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);
}

void class_js::SubCallback(const sensor_msgs::Joy::ConstPtr& Joy){     
    vel_cmd.linear.x = Joy->axes[3] * vlinear * Joy->buttons[4];
    vel_cmd.linear.y = Joy->axes[2] * vlinear * Joy->buttons[4];
    // 旋转应该是左摇杆上下
    vel_cmd.angular.z = Joy->axes[0] * vangular * Joy->buttons[4];
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "bulldog_js");
    class_js js_cmd;
    ros::Rate pub_rate(js_cmd.rate);
    ros::AsyncSpinner spinner(1);
    spinner.start();
    while(ros::ok()){
        js_cmd.pub.publish(js_cmd.vel_cmd);
        if(js_cmd.vel_cmd.linear.x || js_cmd.vel_cmd.angular.z)
            ROS_INFO("linear:%.3f angular:%.3f", js_cmd.vel_cmd.linear.x, js_cmd.vel_cmd.angular.z);
        pub_rate.sleep();
    }
    return 0;
}