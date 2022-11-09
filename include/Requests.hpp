#ifndef REQUESTS_H
#define REQUESTS_H

#include <string>
#include "cpr/cpr.h"
#include <nlohmann/json.hpp>
#include "Schedule.hpp"
#include "Config.hpp"

namespace requests
{
    namespace url
    {
        namespace
        {
            static const std::string web_server = Config::instance().get("servers.local.domain");
            static const std::string redirect_uri = web_server + "/authorize";
            static const std::string google_oauth = "https://accounts.google.com/o/oauth2";
            static const std::string google_oauth_token = google_oauth + "/token";
            static const std::string scope = "https://www.googleapis.com/auth/calendar";
            static const std::string google_oauth_code = google_oauth +
                                                         "/auth?client_id=" + Config::instance().get(Config::VAR_APP_CLIENT_ID) +
                                                         "&redirect_uri=" + redirect_uri +
                                                         "&scope=" + scope +
                                                         "&response_type=code";

            static const std::string google_calendars = "https://www.googleapis.com/calendar/v3/calendars";

            static std::string calendar_events(std::string calendar_id)
            {
                static const std::string events_suffix = "/events";
                return google_calendars + "/" + calendar_id + events_suffix;
            }
        }

    }
    namespace oauth
    {

        static std::string getToken(std::string code)
        {
            nlohmann::json body;
            std::string token;

            body["code"] = code;
            body["client_id"] = Config::instance().get(Config::VAR_APP_CLIENT_ID);
            body["client_secret"] = Config::instance().get(Config::VAR_APP_SECRET);
            body["grant_type"] = "authorization_code";
            body["redirect_uri"] = url::redirect_uri;

            cpr::Response r = cpr::Post(
                cpr::Url{url::google_oauth_token},
                cpr::Body{body.dump()},
                cpr::Header{{"Content-Type", "application/json"}});

            nlohmann::json json_response = nlohmann::json::parse(r.text);
            if (json_response.contains("access_token"))
            {
                token = json_response["access_token"].dump();
            }
            return token;
        }

    }
    namespace calendar
    {
        static std::string schedule(std::string access_token)
        {
            return "Not supported";
        }

        static std::string insertCalendar(const std::string &access_token, const std::string &summary)
        {
            std::string calendarId;
            nlohmann::json body;
            body["summary"] = summary;

            cpr::Response r = cpr::Post(
                cpr::Url{requests::url::google_calendars},
                cpr::Bearer{access_token},
                cpr::Body{body.dump()},
                cpr::Header{{"Content-Type", "application/json"}});

            nlohmann::json json_response = nlohmann::json::parse(r.text);
            if (json_response.contains("id"))
            {
                calendarId = json_response["id"].dump();
                calendarId.erase(std::remove(calendarId.begin(), calendarId.end(), '\"'), calendarId.end());
            }
            return calendarId;
        }

        static long deleteCalendar(const std::string &access_token, const std::string &calendarId)
        {
            cpr::Response r = cpr::Delete(
                cpr::Url{requests::url::google_calendars + "/" + calendarId},
                cpr::Bearer{access_token},
                cpr::Header{{"Content-Type", "application/json"}});
            return r.status_code;
        }

        static std::string saveSchedule(std::string access_token, const Schedule &schedule)
        {
            std::string calendarId = insertCalendar(access_token, schedule.summary);
            std::string url = requests::url::calendar_events(calendarId);

            if (!calendarId.empty())
            {
                for (auto &event : schedule.events)
                {
                    cpr::AsyncResponse r = cpr::PostAsync(
                        cpr::Url{url},
                        cpr::Bearer{access_token},
                        cpr::Body{event.toJson().dump()},
                        cpr::Header{{"Content-Type", "application/json"}});
                }
            }
            deleteCalendar(access_token, calendarId);
            return calendarId;
        }
    }
}

#endif /* REQUESTS_H */
