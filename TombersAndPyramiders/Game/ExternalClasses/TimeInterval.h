class TimeInterval {
    public:
        int times[10];
        int index;
        int count = 0;

    public:
    TimeInterval() {
        times[0] = {1000};
        count = 1;
    }

    TimeInterval(int timeCount, int timers[]) {
        for (int i = 0; i < timeCount; i++) {
            times[i] = timers[i];
        }
    }

    int getNextTime(int timeSinceLastTime) {
        if (++index >= count) {
            index = 0;
        }
        return times[index] - timeSinceLastTime;
    }

    int getCurrentTime() {
        return times[index];
    }
};
