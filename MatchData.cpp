//
//  MatchData.cpp
//  wtHaloViewer
//
//  Created by Colin Luoma on 2016-04-17.
//
//

#include <json/json.h>

#include "MatchData.h"

MatchData::MatchData(std::string match_id)
{
    match_id_ = match_id;
    
    // Get match data JSON string from Halo 5 API
    HaloAPI halo_api();
    std::string json_data = halo_api.getPostGameCarnageArena(match_id);
    
    Json::Value root;
    Json::Reader reader;
    bool parsingSuccessful = reader.parse( json_data, root );
    if ( !parsingSuccessful )
    {
        // report to the user the failure and their locations in the document.
        std::cout  << "Failed to parse configuration\n"
        << reader.getFormattedErrorMessages();
    }
    
    for (int j = 0; j < root["PlayerStats"].size(); j++)
    {
        gamertags_.push_back(root["PlayerStats"][j]["Player"]["Gamertag"].asString());
    }
}