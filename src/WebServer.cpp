#include <string>
#include <nlohmann/json.hpp>
#include "WebServer.hpp"
#include "Auth.hpp"
#include "Requests.hpp"

WebServer::WebServer(Auth &auth) : auth{auth}
{
}

std::string parseChatId(struct mg_http_message *hm)
{

    char buf[100] = "";
    std::string body = std::string(hm->body.ptr, hm->body.len);
    if (!body.empty())
    {
        nlohmann::json json = nlohmann::json::parse(body);
        if (json.contains("chat_id"))
        {
            return json["chat_id"].dump();
        }
    }

    return "";
}
void fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data)
{
    Auth *auth = static_cast<Auth *>(c->fn_data);
    struct mg_http_serve_opts opts = {.root_dir = "web_root", .mime_types = "text/html"};

    if (ev == MG_EV_HTTP_MSG)
    {
        struct mg_http_message *hm = (struct mg_http_message *)ev_data;
        std::string chatId = parseChatId(hm);

        if (mg_http_match_uri(hm, "/current"))
        {
            if (!chatId.empty())
            {
                auth->waiting_for_tokens.push(chatId);
                mg_http_reply(c, 200, NULL, "");
            }
            else
            {
                mg_http_reply(c, 500, NULL, "%s", "Chat id parameter missing");
            }
        }
        else if (mg_http_match_uri(hm, "/authorize"))
        {
            struct mg_str params = hm->query;
            struct mg_str code_var = mg_http_var(hm->query, mg_str("code"));
            std::string code(code_var.ptr, code_var.len);
            if (code.find("%2F") != std::string::npos)
            {
                code.replace(code.find("%2F"), 3, "/");
            }
            if (!code.empty())
            {
                std::string access_token = requests::oauth::getToken(code);
                auth->access_tokens.emplace(auth->waiting_for_tokens.front(), access_token);
                auth->waiting_for_tokens.pop();
                mg_http_serve_file(c, hm, "web_root/authSuccess.html", &opts);
            }
            else
            {
                mg_http_reply(c, 500, NULL, "%s", "Parameters missing");
            }
        }
        else if (mg_http_match_uri(hm, "/schedule"))
        {

            if (auth->access_tokens.find(chatId) != auth->access_tokens.end())
            {
                std::string access_token = auth->access_tokens.at(chatId);
                std::string response = "{\"some_calendar\": \"calendar\"}";
                mg_http_reply(c, 200, "Content-Type: application/json\r\n", "%s", response.c_str());
            }
            else
            {
                mg_http_reply(c, 500, "Content-Type: application/json\r\n", "%s", "Error. No access token found. Please send /auth command");
            }
        }
        else if (mg_http_match_uri(hm, "/static/*"))
        {
            std::string uri = std::string(hm->uri.ptr, hm->uri.len);
            std::string substr = "/static/";
            uri.erase(0, substr.size());
            uri = "web_root/" + uri;
            mg_http_serve_file(c, hm, uri.c_str(), &opts);
        }
        else
        {
            mg_http_serve_file(c, hm, "web_root/404.html", &opts);
        }
    }
}

void WebServer::start()
{
    mg_mgr_init(&mgr);
    mg_http_listen(&mgr, "0.0.0.0:8000", fn, &auth); // Create listening connection
    for (;;)
        mg_mgr_poll(&mgr, 1000);
}
