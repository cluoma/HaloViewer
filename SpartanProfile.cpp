//
//  SpartanProfile.cpp
//  wtHaloViewer
//
//  Created by Colin Luoma on 2015-11-29.
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
#include "SpartanProfile.h"
#include "HaloAPI.h"


using namespace curlpp::options;
using namespace std;

SpartanProfile::SpartanProfile()
{
    gamertag_ = "HHHH";
    emblem_ = "HHHH";
}

SpartanProfile::SpartanProfile(std::string gamertag)
{
    updateProfile(gamertag);
}

void SpartanProfile::updateProfile(std::string game)
{
    // Reset spartan ranks
    playlist_ranks_.clear();
    recent_matches_.clear();
    
    // Fixx input gamertag to input to URL
    std::string gamertag(game);
    boost::replace_all(gamertag, " ", "+");
    boost::trim(gamertag);
    
    // Create halo api with an api key (get api key from 343i api site)
    HaloAPI halo_api("05cdc66c52ca4465b0b6e3c56bb87b71");
    
    // Get Emblem URL
    emblem_ = halo_api.getEmblemURL(gamertag);
    if (!boost::algorithm::contains(emblem_, "https:"))
    {
        return;
    }
    
    // Get Arena service record data
    try
    {
        std::string json_data = halo_api.getServiceRecord("arena", gamertag);
        
        Json::Value root;   // will contains the root value after parsing.
        Json::Reader reader;
        bool parsingSuccessful = reader.parse( json_data, root );
        if ( !parsingSuccessful )
        {
            // report to the user the failure and their locations in the document.
            std::cout  << "Failed to parse configuration\n"
            << reader.getFormattedErrorMessages();
        }
        
        const Json::Value plugins = root["Results"];
        
        
        gamertag_ = plugins[0]["Result"]["PlayerId"]["Gamertag"].asString();
        spartan_rank_ = plugins[0]["Result"]["SpartanRank"].asInt();
        
        // Playlist ranks
        
        std::cout << "\n\n";
        for (int i = 0; i < plugins[0]["Result"]["ArenaStats"]["ArenaPlaylistStats"].size(); i++)
        {
            PlaylistRank rank(
                plugins[0]["Result"]["ArenaStats"]["ArenaPlaylistStats"][i]["PlaylistId"].asString(),
                plugins[0]["Result"]["ArenaStats"]["ArenaPlaylistStats"][i]["Csr"]["DesignationId"].asInt(),
                plugins[0]["Result"]["ArenaStats"]["ArenaPlaylistStats"][i]["Csr"]["Tier"].asInt(),
                plugins[0]["Result"]["ArenaStats"]["ArenaPlaylistStats"][i]["Csr"]["Csr"].asInt(),
                plugins[0]["Result"]["ArenaStats"]["ArenaPlaylistStats"][i]["Csr"]["PercentToNextTier"].asInt(),
                plugins[0]["Result"]["ArenaStats"]["ArenaPlaylistStats"][i]["MeasurementMatchesLeft"].asInt(),
                              
                plugins[0]["Result"]["ArenaStats"]["ArenaPlaylistStats"][i]["TotalGamesWon"].asInt(),
                plugins[0]["Result"]["ArenaStats"]["ArenaPlaylistStats"][i]["TotalGamesLost"].asInt(),
                              
                plugins[0]["Result"]["ArenaStats"]["ArenaPlaylistStats"][i]["TotalSpartanKills"].asInt(),
                plugins[0]["Result"]["ArenaStats"]["ArenaPlaylistStats"][i]["TotalDeaths"].asInt(),
                plugins[0]["Result"]["ArenaStats"]["ArenaPlaylistStats"][i]["TotalAssists"].asInt()
            );
            playlist_ranks_.push_back(rank);
        }
        
    }
    
    catch(curlpp::RuntimeError & e)
    {
        gamertag_ = e.what();
        std::cout << e.what() << std::endl;
    }
    
    catch(curlpp::LogicError & e)
    {
        gamertag_ = "Logic Error";
        std::cout << e.what() << std::endl;
    }
    
    // Call and parse recent arena matches
    parseRecentMatches(halo_api);
}

void SpartanProfile::parseRecentMatches(HaloAPI halo_api)
{
    // Get Recent arena matches
    try
    {
        std::string gamertag = gamertag_;
        boost::replace_all(gamertag, " ", "+");
        
        std::string json_data = halo_api.getMatchesForPlayer("arena", 25, 0, gamertag);
        
        
        Json::Value root;   // will contains the root value after parsing.
        Json::Reader reader;
        bool parsingSuccessful = reader.parse( json_data, root );
        if ( !parsingSuccessful )
        {
            // report to the user the failure and their locations in the document.
            std::cout  << "Failed to parse configuration\n"
            << reader.getFormattedErrorMessages();
        }
        const Json::Value plugins = root["Results"];
        //std::cout << "\n\n" << plugins[0]["Id"][0].asString();
        for (int i = 0; i < plugins.size(); i++)
        {
            std::string match_id = plugins[i]["Id"]["MatchId"].asString();
            std::string hopper_id = plugins[i]["HopperId"].asString();
            std::string base_variant = plugins[i]["GameBaseVariantId"].asString();
            std::string map_id = plugins[i]["MapId"].asString();
            int team_id = plugins[i]["Players"][0]["TeamId"].asInt();
            int rank = plugins[i]["Players"][0]["Rank"].asInt();
            int result = plugins[i]["Players"][0]["Result"].asInt();
            int total_kills = plugins[i]["Players"][0]["TotalKills"].asInt();
            int total_deaths = plugins[i]["Players"][0]["TotalDeaths"].asInt();
            int total_assists = plugins[i]["Players"][0]["TotalAssists"].asInt();
            double match_length = parseDuration(plugins[i]["MatchDuration"].asString());
            
            
            
            RecentMatch match(
                              match_id,
                              team_id,
                              rank,
                              result,
                              total_kills,
                              total_deaths,
                              total_assists,
                              match_length,
                              hopper_id,
                              base_variant,
                              map_id
                              );
            recent_matches_.push_back(match);
        }
    }
    catch(curlpp::LogicError & e)
    {
        
    }
}

// Parses string durations in the form of PT7M47.098796S and returns minutes
double SpartanProfile::parseDuration(std::string duration)
{
    for (int i = 0; i < duration.length(); i++)
    {
        char c = duration[i];
        if (c >= 'A' & c <= 'Z')
            duration[i] = ' ';
    }
    boost::trim(duration);
    
    std::vector<std::string> strs;
    boost::split(strs, duration, boost::is_any_of(" "));
    
    std::reverse(strs.begin(),strs.end());
    
    double seconds = 0;
    for (int i = 0; i < (int)strs.size(); i++)
    {
        switch (i)
        {
                // seconds
            case 0:
                seconds += stod(strs[i]);
                break;
                // minutes
            case 1:
                seconds += stod(strs[i]) * 60;
                break;
                // hours
            case 2:
                seconds += stod(strs[i]) * 60 * 60;
                break;
                // days
            case 3:
                seconds += stod(strs[i]) * 24 * 60 * 60;
                break;
        }
    }
    return seconds/60;
}

std::string SpartanProfile::getGamertag()
{
    return gamertag_;
}

std::string SpartanProfile::getEmblem()
{
    return emblem_;
}

std::string SpartanProfile::getSpartan()
{
    return spartan_;
}
int SpartanProfile::getSpartanRank()
{
    return spartan_rank_;
}

void SpartanProfile::printRanks()
{
    std::cout << "\n\n";
    for (int i = 0; i < playlist_ranks_.size(); i++)
    {
        std::cout << playlist_ranks_[i].name_ << std::endl;
        std::cout << playlist_ranks_[i].rank_ << std::endl;
        std::cout << playlist_ranks_[i].level_ << std::endl;
        std::cout << playlist_ranks_[i].progress_ << std::endl;
    }
}

std::string SpartanProfile::getRanks()
{
    std::string output;
    for (int i = 0; i < playlist_ranks_.size(); i++)
    {
        output += playlist_ranks_[i].name_ + " " +
            std::to_string(playlist_ranks_[i].rank_) + " " +
            std::to_string(playlist_ranks_[i].level_) + " " +
            std::to_string(playlist_ranks_[i].progress_) + " " +
            std::to_string(playlist_ranks_[i].remaining_placement_) + "\n";
    }
    return output;
}

std::vector<PlaylistRank> SpartanProfile::getPlaylistStats()
{
    return playlist_ranks_;
}

// Playlist Ranks
PlaylistRank::PlaylistRank(std::string name, int rank,
                           int level, int csr, int progress, int remaining_placement,
                           int total_games_won, int total_games_lost,
                           int total_kills, int total_deaths, int total_assists)
{
    name_ = name;
    rank_ = rank;
    level_ = level;
    csr_ = csr;
    progress_ = progress;
    remaining_placement_ = remaining_placement;
    
    total_games_won_ = total_games_won;
    total_games_lost_ = total_games_lost;
    
    total_kills_ = total_kills;
    total_deaths_ = total_deaths;
    total_assists_ = total_assists;
}

//Recent Matches
RecentMatch::RecentMatch(std::string match_id, int team, int rank, int result,
                         int total_kills, int total_deaths, int total_assists,
                         double match_length, std::string hopper_id, std::string base_variant,
                         std::string map_id)
{
    match_id_ = match_id;
    team_ = team;
    rank_ = rank;
    result_ = result;
    total_kills_ = total_kills;
    total_deaths_ = total_deaths;
    total_assists_ = total_assists;
    match_length_ = match_length;
    hopper_id_ = hopper_id;
    base_variant_ = base_variant;
    map_id_ = map_id;
}

std::vector<RecentMatch> SpartanProfile::getRecentMatches()
{
    return recent_matches_;
}

std::string SpartanProfile::printRecentMatches()
{
    std::string tmp = "";
    for (int i = 0; i < recent_matches_.size(); i++)
    {
        tmp += recent_matches_[i].match_id_ + "\n";
    }
    return tmp;
}