#ifndef REQUESTS_H
#define REQUESTS_H

#include "Config.hpp"
#include "Schedule.hpp"
#include "cpr/cpr.h"
#include <cpr/response.h>
#include <exception>
#include <future>
#include <nlohmann/json.hpp>
#include <string>
#include <thread>

namespace requests {
namespace url {
namespace {
static const std::string web_server =
    "http://" + Config::instance().get("server.domain") + ":" + "8000"
    //   Config::instance().get("server.port")
    ;
static const std::string redirect_uri = web_server + "/authorize";
static const std::string google_oauth = "https://accounts.google.com/o/oauth2";
static const std::string google_oauth_token = google_oauth + "/token";
static const std::string scope =
    "https://www.googleapis.com/auth/calendar.app.created";
static const std::string google_oauth_code =
    google_oauth +
    "/auth?client_id=" + Config::instance().get("google.app_id") +
    "&redirect_uri=" + redirect_uri + "&scope=" + scope + "&response_type=code";

static const std::string google_calendars =
    "https://www.googleapis.com/calendar/v3/calendars";

static std::string calendar_events(std::string calendar_id) {
  static const std::string events_suffix = "/events";
  return google_calendars + "/" + calendar_id + events_suffix;
}
} // namespace

} // namespace url
namespace oauth {

static std::string getToken(std::string code) {
  nlohmann::json body;
  std::string token;

  body["code"] = code;
  body["client_id"] = Config::instance().get("google.app_id");
  body["client_secret"] = getenv("SECHA_BOT_CLIENT_SECRET");
  body["grant_type"] = "authorization_code";
  body["redirect_uri"] = url::redirect_uri;

  cpr::Response r =
      cpr::Post(cpr::Url{url::google_oauth_token}, cpr::Body{body.dump()},
                cpr::Header{{"Content-Type", "application/json"}});

  nlohmann::json json_response = nlohmann::json::parse(r.text);
  if (json_response.contains("access_token")) {
    token = json_response["access_token"].dump();
  }
  return token;
}

} // namespace oauth
namespace calendar {
static std::string schedule(std::string access_token) {

  return "Not supported";
}

static std::string insertCalendar(const std::string &access_token,
                                  const std::string &summary) {
  std::string calendarId;
  nlohmann::json body;
  body["summary"] = summary;

  cpr::Response r =
      cpr::Post(cpr::Url{requests::url::google_calendars},
                cpr::Bearer{access_token}, cpr::Body{body.dump()},
                cpr::Header{{"Content-Type", "application/json"}});

  nlohmann::json json_response = nlohmann::json::parse(r.text);
  if (json_response.contains("id")) {
    calendarId = json_response["id"].dump();
    calendarId.erase(std::remove(calendarId.begin(), calendarId.end(), '\"'),
                     calendarId.end());
  } else if (json_response.contains("error")) {
    std::cout << json_response["error"];
  }

  return calendarId;
}

static long deleteCalendar(const std::string &access_token,
                           const std::string &calendarId) {
  cpr::Response r =
      cpr::Delete(cpr::Url{requests::url::google_calendars + "/" + calendarId},
                  cpr::Bearer{access_token},
                  cpr::Header{{"Content-Type", "application/json"}});
  return r.status_code;
}

static std::vector<std::shared_future<cpr::Response>>
saveSchedule(std::string access_token, const Schedule &schedule,
             const std::string &calendarId) {
  std::string url = requests::url::calendar_events(calendarId);
  std::vector<std::shared_future<cpr::Response>> responses;
  int batch = 5;
  int sleep_ms = 200;
  if (!calendarId.empty()) {
    for (int i = 0; i < schedule.events.size(); i++) {
      std::this_thread::sleep_for(std::chrono::milliseconds(sleep_ms));
      cpr::AsyncResponse r =
          cpr::PostAsync(cpr::Url{url}, cpr::Bearer{access_token},
                         cpr::Body{schedule.events[i].toJson().dump()},
                         cpr::Header{{"Content-Type", "application/json"}});
      responses.push_back(r.share());

      if ((i + 1) % batch == 0) {
        for (auto r : responses) {
          auto ans = r.get();
          try {
            auto json = nlohmann::json::parse(ans.text);
            if (json.contains("error")) {
              std::cout << json["error"] << "\n";
            }
          } catch (std::exception &e) {
            std::cerr << e.what() << "\n";
          }
        }
        responses.clear();
      }
    }
  }
  return responses;
}
} // namespace calendar
} // namespace requests

#endif /* REQUESTS_H */
