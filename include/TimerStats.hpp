//
// Created by Øystein Bringsli.
//

#ifndef LEDSTRIPCONTROLLER_TIMERSTATS_HPP
#define LEDSTRIPCONTROLLER_TIMERSTATS_HPP


struct TimerData {
    long loopsPerSecond;
    double estimatedLoopTime;
};

class TimerStats {

public:
    TimerStats();

    void startTimer();
    void printTimerData() const;

    unsigned long long printIters = 0;
    int updateFreq = 75;

private:
    unsigned long prevTime;

    long loopsPerTimeunit = 0;
    double estimatedLoopTime = 0;
    unsigned long iters = 0;

    TimerData getTimerData();
};


#endif //LEDSTRIPCONTROLLER_TIMERSTATS_HPP
