#ifndef SMARTGRID_CONFIG_H
#define SMARTGRID_CONFIG_H

struct Config {
    int id;
    int startTime;
    int endTime;
    // for test
    bool operator==(const Config& rhs) const {
        return id == rhs.id && startTime == rhs.startTime && endTime == rhs.endTime;
    }
};

#endif //SMARTGRID_CONFIG_H
