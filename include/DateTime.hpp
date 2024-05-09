//
// Created by Øystein Bringsli.
//

#ifndef LEDSTRIPCONTROLLER_DATETIME_HPP
#define LEDSTRIPCONTROLLER_DATETIME_HPP


class DateTime {
public:
    struct CurrentTime {
        int hour;
        int minute;
        int second;
    };

    enum TimeState {
        MORNING,
        SCHOOL,
        DAY,
        EVENING,
        NIGHT
    };

    DateTime();
    void init();

    TimeState getTimeState();
    CurrentTime getCurrentTime();

    static int timeDiffSeconds(int t0, int t1);
    double progress = 0.0;

};


#endif //LEDSTRIPCONTROLLER_DATETIME_HPP
