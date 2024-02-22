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
        DAY,
        EVENING,
        NIGHT
    };

    DateTime();
    void init();

    TimeState getTimeState();
    CurrentTime getCurrentTime();

};


#endif //LEDSTRIPCONTROLLER_DATETIME_HPP
