//################################################################
//# Copyright (C) 2022, EduArt Robotik GmbH, All rights reserved.#
//# Further information can be found in the LICENSE file.        #
//################################################################

#include <ros/ros.h>
#include <sensor_msgs/Joy.h>
#include <unistd.h>

#define VERSION1 0

int main(int argc, char** argv)
{
     ros::init(argc, argv, "eduard_test");
     ros:: NodeHandle nh = ros::NodeHandle("~");
     ros::Publisher joy_pub = nh.advertise<sensor_msgs::Joy>("/joy", 10);

     ros::Rate node_rate(10);
     

#if VERSION1
     while(ros::ok())
     {
         
        sensor_msgs::Joy joy_buf;
        //Hi Stefan, bitte einmal zeigen, wie ich auf die Achsen und die Knöpfe schreibe,
        //dann denke ich mir die Logic dazu aus (Switch case)
        //Legst du für den Datenaustausch dann einfach ein Repo an?
        //Ich brauche dann entsprechende Rechte auf dem Account "fennma67764"
        joy_buf.header.frame_id = "joy";
        joy_buf.axes.push_back(0.0);
        joy_buf.axes.push_back(1.0);
        joy_buf.axes.push_back(0.0);
        joy_buf.axes.push_back(1.0);
         
        for(int i=0; i<10; i++)
            joy_buf.buttons.push_back(0);
        joy_buf.buttons.push_back(1);


        // axes ist initial ein Vektor der Länge 0. Erst nachdem man mit push_back Elemente eingefügt hat, kann man auf diese mit den eckigen Klammern zugreifen.
        // aber vorsicht! Du hast joy_buf innerhalb der while-Schleife definiert. Diese Variable wird am Ende der Schleife wieder aus dem Speicher entfernt und am Anfang der Schleifen neu angelegt.
        // Du kannst also auch die push_back-Anweisungen einmal vor der while-Schleife ausführen und dann mit dem []-Operator lesend und schreibend zugreifen, siehe Version 2 unten.
        //joy_buf.axes[0] = 0.0;
        //joy_buf.axes[1] = 1.0;
        //joy_buf.axes[2] = 0.0;
        //joy_buf.axes[3] = 1.0;
        //joy_buf.buttons[10] = 1;

        joy_pub.publish(joy_buf);
        ros::spinOnce();
        node_rate.sleep();
     }

#else

    sensor_msgs::Joy joy_buf;
    joy_buf.header.frame_id = "joy";
    for(int i=0; i<4; i++)
        joy_buf.axes.push_back(0.0);
        
    for(int i=0; i<11; i++)
        joy_buf.buttons.push_back(0);

     while(ros::ok())
     {
         
        joy_buf.axes[0] = 0.0;
        joy_buf.axes[1] = 1.0;
        joy_buf.axes[2] = 0.0;
        joy_buf.axes[3] = 1.0;
        joy_buf.buttons[10] = 1;

        joy_pub.publish(joy_buf);
        ros::spinOnce();
        node_rate.sleep();
     }

#endif


     return 0;
}
