#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "boost/tokenizer.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <nlohmann/json.hpp>
#include <sstream>

class Schedule
{
public:
    class Event
    {
    public:
        class DateTime
        {
        public:
            std::string timezone = "Europe/Moscow";
            std::string dateTimeISO;
        };

        nlohmann::json toJson() const
        {
            nlohmann::json start_json;
            start_json["timeZone"] = start.timezone;
            start_json["dateTime"] = start.dateTimeISO;

            nlohmann::json end_json;
            end_json["timeZone"] = end.timezone;
            end_json["dateTime"] = end.dateTimeISO;

            nlohmann::json json;
            json["summary"] = summary;
            json["description"] = description;
            json["location"] = location;
            json["start"] = start_json;
            json["end"] = end_json;
            return json;
        };

        std::string summary;
        std::string description;
        std::string location;
        DateTime start;
        DateTime end;
    };

    static Schedule loadSchedule()
    {
        Schedule s;
        s.summary = "Secha Schedule";
        std::ifstream ifs("schedule.csv", std::ifstream::in);
        typedef boost::tokenizer<boost::escaped_list_separator<char>> tokenizer;
        boost::escaped_list_separator<char> separator('\\', ',', '\"');
        for (std::string line; std::getline(ifs, line);) {
            tokenizer tok{line, separator};
            tokenizer::iterator it = tok.begin();
            Schedule::Event e;
            std::string date = *it++;
            e.summary = *it++;
            std::string start = *it++;
            e.start.dateTimeISO = toISODatetime(date, start);
            std::string end = *it++;
            e.end.dateTimeISO = toISODatetime(date, end);
            e.description = *it++;
            s.events.push_back(e);
        }
        return s;
    }

    static std::string toISODatetime(std::string &date, std::string &time)
    {
        std::stringstream ss;
        ss << date << " " << time;
        std::tm t = {};
        ss >> std::get_time(&t, "%d.%m.%Y %H:%M");
        std::stringstream().swap(ss);
        ss << std::put_time(&t, "%Y-%m-%dT%H:%M:%S");
        return ss.str();
    }

    std::string calendarId;
    std::string summary;
    std::string timezone;
    std::vector<Event> events;
};

#endif /* SCHEDULE_H */
