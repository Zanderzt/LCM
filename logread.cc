/* Designed By ZhangTong
*  2019/07/05
*  file: read_log.cpp
*  LCM example program.  Demonstrates how to read and decode messages directly
*  from a log file in C++.  It is also possible to use the log file provider --
*  see the documentation on the LCM class for details on that method.
*  compile with:
*  $ g++ -o read_log read_log.cpp -llcm
*/
#include <stdio.h>
#include <lcm/lcm-cpp.hpp>
#include "lcmtypes/camera_info_t.hpp"

using namespace std;

int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "usage: read_log <logfile>\n");
        return 1;
    }

    // Open the log file.
    lcm::LogFile log(argv[1], "r");
    if (!log.good()) {
        perror("LogFile");
        fprintf(stderr, "couldn't open log file %s\n", argv[1]);
        return 1;
    }

    freopen("out.txt","w",stdout);  // create out.txt to write info 
    while (1) {
        // Read a log event.
        const lcm::LogEvent *event = log.readNextEvent();
        if (!event)
            break;

        // Only process messages on the EXAMPLE channel.
        if (event->channel != "camera")
            continue;

        // Try to decode the message.
        lcmtypes::camera_info_t msg1;

        if (msg1.decode(event->data, 0, event->datalen) != event->datalen)
            continue;

        // Decode success!  Print out the message contents.
        /*printf("Message:\n");
        printf("  utime       = %lld\n", (long long) msg1.utime);*/
        printf("%lld\n", (long long) msg1.utime);  //print info of time
        //printf(" change line  = %d\n", msg1.change_lane);
        //printf(" lane_width   = %f\n",msg1.lane_width);
        printf("%f\n",msg1.lane_width);    // print info of lane_width
        /*printf(" center_line  = (%f,%f,%f,%f,%f,%f)\n", msg1.center_line.confidence, msg1.center_line.length, 
                   msg1.center_line.a, msg1.center_line.b, msg1.center_line.c, msg1.center_line.d);*/
        printf("%f,%f,%f,%f,%f,%f\n", msg1.center_line.confidence, msg1.center_line.length, 
                   msg1.center_line.a, msg1.center_line.b, msg1.center_line.c, msg1.center_line.d);
        for (int k=0;k<4;k++) //print four line_info
        {
        /*printf(" line_info    = (%f,%d,%d,%f,%f,%f,%f,%f)\n",msg1.lines[k].confidence, msg1.lines[k].type,
           msg1.lines[k].lineColor,msg1.lines[k].length,msg1.lines[k].a,msg1.lines[k].b, msg1.lines[k].c,msg1.lines[k].d);*/
        printf("%f,%d,%d,%f,%f,%f,%f,%f\n",msg1.lines[k].confidence, msg1.lines[k].type,
           msg1.lines[k].lineColor,msg1.lines[k].length,msg1.lines[k].a,msg1.lines[k].b, msg1.lines[k].c,msg1.lines[k].d);
        }
        printf("number of obj = %d\n",msg1.object_count);
        //out << msg1.object_count << endl;
        for (int i=0;i<msg1.object_count;i++)
        {
        /*printf("    center_point  = (%f, %f)\n",msg1.objects[i].centerPoint.x,msg1.objects[i].centerPoint.y);
        printf("    ID ,type,brake= (%d, %d, %d)\n",msg1.objects[i].id,msg1.objects[i].type,msg1.objects[i].brake);
        printf("    turn,SPLo,SPLa= (%d, %f, %f)\n",msg1.objects[i].turn,msg1.objects[i].speedLon,msg1.objects[i].speedLat);
        printf("    angle, confi  = (%f, %f)\n",msg1.objects[i].angle,msg1.objects[i].confidence);
        printf("    w ,  h,  l    = (%f, %f, %f)\n",msg1.objects[i].width,msg1.objects[i].height,msg1.objects[i].length);*/
        printf("%f,%f,%d,%d,%d,%d,%f,%f,%f,%f,%f,%f,%f",msg1.objects[i].centerPoint.x,msg1.objects[i].centerPoint.y,msg1.objects[i].id,
        msg1.objects[i].type,msg1.objects[i].brake,msg1.objects[i].turn,msg1.objects[i].speedLon,msg1.objects[i].speedLat,
        msg1.objects[i].angle,msg1.objects[i].confidence,msg1.objects[i].width,msg1.objects[i].height,msg1.objects[i].length);
        }
    }

    // Log file is closed automatically when the log variable goes out of
    // scope.

    printf("done\n");
    return 0;
}
