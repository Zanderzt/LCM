/*  Designed By ZhangTong
*   2019/07/13
*   read the lcm log file and standared info write on logout.txt
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
    //ofstream out("info.txt");
    if (!log.good()) {
        perror("LogFile");
        fprintf(stderr, "couldn't open log file %s\n", argv[1]);
        return 1;
    }
    freopen("logout.txt","w",stdout);
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

        printf("%lld\n", (long long) msg1.utime);
        printf("%d\n", msg1.change_lane);
        printf("%f\n",msg1.lane_width);
        printf("%f,%f,%f,%f,%f,%f\n", msg1.center_line.confidence, msg1.center_line.length, 
                   msg1.center_line.a, msg1.center_line.b, msg1.center_line.c, msg1.center_line.d);
        for (int k=0;k<4;k++) //print four line_info
        {
        printf("%f,%d,%d,%f,%f,%f,%f,%f\n",msg1.lines[k].confidence, msg1.lines[k].type,
           msg1.lines[k].lineColor,msg1.lines[k].length,msg1.lines[k].a,msg1.lines[k].b, msg1.lines[k].c,msg1.lines[k].d);
        }
        printf("%d\n",msg1.object_count);
        for (int i=0;i<msg1.object_count;i++)
        {
        printf("%f,%f,%d,%d,%d,%d,%f,%f,%f,%f,%f,%f,%f\n",msg1.objects[i].centerPoint.x,msg1.objects[i].centerPoint.y,msg1.objects[i].id,
        msg1.objects[i].type,msg1.objects[i].brake,msg1.objects[i].turn,msg1.objects[i].speedLon,msg1.objects[i].speedLat,
        msg1.objects[i].angle,msg1.objects[i].confidence,msg1.objects[i].width,msg1.objects[i].height,msg1.objects[i].length);
        }
    }
    // Log file is closed automatically when the log variable goes out of
    // scope.

    printf("done\n");
    return 0;
}
