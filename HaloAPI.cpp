//
//  HaloAPI.cpp
//  wtHaloViewer
//
//  Created by Colin Luoma on 2016-04-03.
//
//

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <sstream>

#include <boost/algorithm/string.hpp>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

#include <json/json.h>

#include "HaloAPI.h"

using namespace curlpp::options;
using namespace std;

HaloAPI::HaloAPI(string api_key)
{
    api_key_ = api_key;
}
HaloAPI::HaloAPI()
{
    api_key_ = "05cdc66c52ca4465b0b6e3c56bb87b71";
}

// Returns the URL of the supplied gamertags emblem (the custom image)
string HaloAPI::getEmblemURL(string game)
{
    // String to store emblem URL
    string emblemURL;
    
    // Copy string and replaces spaces in gamertag with + for use in API call
    std::string gamertag(game);
    boost::replace_all(gamertag, " ", "+");
    
    // Initialize stringstream and json data string
    std::ostringstream ss;
    std::string json_data;
    
    // Initialize request to be sent
    curlpp::Easy myRequest;
    
    // Set the URL using supplied gamertag
    myRequest.setOpt<Url>("https://www.haloapi.com/profile/h5/profiles/" + gamertag + "/emblem");
    
    // Add header info (this is where we use the API key)
    std::list<std::string> headers;
    string head_key = "Ocp-Apim-Subscription-Key:  " + api_key_;
    headers.push_back(head_key);
    headers.push_back("Accept: application/json");
    myRequest.setOpt(new HttpHeader(headers));
    myRequest.setOpt(new Header(true));
    
    // Send request and get a result.
    // By default the result goes to standard output.
    myRequest.perform();
    
    // Print request to stringstrem and store in json_data string
    ss << myRequest;
    json_data = ss.str();
    
    // Extract emblem URL from reply header data
    std::vector<std::string> strs;
    boost::split(strs, json_data, boost::is_any_of("\n "));
    for (int i = 0; i < strs.size(); i++)
    {
        if (boost::algorithm::contains(strs[i], "halocdn"))
        {
            boost::replace_all(strs[i], "\r", "");
            emblemURL = strs[i];
        }
    }
    return emblemURL;
}

// Return the json data in a string for a call to service record
// Given a mode: arena, or warzone, and a gamertag
string HaloAPI::getServiceRecord(string mode, string game)
{
    if (mode != "arena" && mode != "warzone")
    {
        return "Error: Invalid mode argument";
    }
    
    // Copy string and replaces spaces in gamertag with + for use in API call
    string gamertag(game);
    boost::replace_all(gamertag, " ", "+");
    
    // Initialize stringstream and json data string
    ostringstream ss;
    string json_data;
    
    // Our request to be sent.
    curlpp::Easy myRequest;
    
    // Set the URL.
    myRequest.setOpt<Url>("https://www.haloapi.com/stats/h5/servicerecords/" + mode + "?players=" + gamertag);
    
    // Add header infor
    list<string> headers;
    string head_key = "Ocp-Apim-Subscription-Key:  " + api_key_;
    headers.push_back(head_key);
    headers.push_back("Accept: application/json");
    myRequest.setOpt(new HttpHeader(headers));
    
    myRequest.setOpt(new WriteStream(&ss));
    
    // Send request and get a result.
    // By default the result goes to standard output.
    myRequest.perform();
    json_data = ss.str();
    ss.str(string());
    
    return json_data;
}

string HaloAPI::getMatchesForPlayer(string mode, int count, int start, string game)
{
    if (mode != "arena" && mode != "warzone" && mode != "custom" && mode != "campaign")
    {
        return "Error: Invalid mode argument";
    }
    
    // Copy string and replaces spaces in gamertag with + for use in API call
    string gamertag(game);
    boost::replace_all(gamertag, " ", "+");
    
    // Initialize stringstream and json data string
    ostringstream ss;
    string json_data;
    
    // Our request to be sent.
    curlpp::Easy myRequest;
    
    // Set the URL.
    myRequest.setOpt<Url>("https://www.haloapi.com/stats/h5/players/"+ gamertag +"/matches?modes="+ mode +"&start=0&count=20");
    
    // Add header infor
    list<string> headers;
    string head_key = "Ocp-Apim-Subscription-Key:  " + api_key_;
    headers.push_back(head_key);
    headers.push_back("Accept: application/json");
    myRequest.setOpt(new HttpHeader(headers));
    
    myRequest.setOpt(new WriteStream(&ss));
    
    // Send request and get a result.
    // By default the result goes to standard output.
    myRequest.perform();
    json_data = ss.str();
    ss.str(string());
    
    return json_data;
}

string HaloAPI::getPostGameCarnageArena(string match_id)
{
    
    // Initialize stringstream and json data string
    ostringstream ss;
    string json_data;
    
    // Our request to be sent.
    curlpp::Easy myRequest;
    
    // Set the URL.
    myRequest.setOpt<Url>("https://www.haloapi.com/stats/h5/arena/matches/" + match_id);
    
    // Add header infor
    list<string> headers;
    string head_key = "Ocp-Apim-Subscription-Key:  " + api_key_;
    headers.push_back(head_key);
    headers.push_back("Accept: application/json");
    myRequest.setOpt(new HttpHeader(headers));
    
    myRequest.setOpt(new WriteStream(&ss));
    
    // Send request and get a result.
    // By default the result goes to standard output.
    myRequest.perform();
    json_data = ss.str();
    ss.str(string());
    
    return json_data;
}