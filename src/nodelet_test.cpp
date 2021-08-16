#include <pluginlib/class_list_macros.h>
#include <nodelet/nodelet.h>
#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <iostream>
#include <math.h>

namespace nodelet_ns
{
class Plus : public nodelet::Nodelet
{
public:
  Plus() : value_(0)
  {}

private:
  ros::Publisher pub_;
  ros::Subscriber sub_;
  ros::NodeHandle nh_;
  double value_;

  virtual void onInit()
  {
    //nh_ = getNodeHandle();
    nh_ = getPrivateNodeHandle();
    nh_.getParam("/value", value_);

    pub_ = nh_.advertise<std_msgs::Float64>("out", 10);
    sub_ = nh_.subscribe("in", 10, &Plus::callback, this);
  }

  void callback(const std_msgs::Float64::ConstPtr &data)
  {
    nh_.getParam("/value", value_);
    //std_msgs::Float64Ptr output(new std_msgs::Float64());
    //output->data = data->data + value_;

    std_msgs::Float64 output;
    output.data = data->data + value_;

    std::cout << "Add " << this->value_ << " to input." << std::endl;
    //std::cout << "output = " << output->data << std::endl;

    pub_.publish(output);
  }

};

//PLUGINLIB_DECLARE_CLASS(nodelet_ns, Plus, nodelet_ns::Plus, nodelet::Nodelet);
//PLUGINLIB_DECLARE_CLASS(nodelet_ns, Plus, nodelet_ns::Plus, nodelet::Nodelet);
}

PLUGINLIB_EXPORT_CLASS(nodelet_ns::Plus, nodelet::Nodelet)