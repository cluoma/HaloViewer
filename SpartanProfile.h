//
//  SpartanProfile.h
//  wtHaloViewer
//
//  Created by Colin Luoma on 2015-11-29.
//
//

#ifndef _SPARTAN_PROFILE_H_
#define _SPARTAN_PROFILE_H_

#include "HaloAPI.h"

class RecentMatch
{
public:
    RecentMatch(std::string match_id, int, int, int, int, int, int, double, std::string, std::string, std::string);
    
    // Player match data
    int team_;
    int rank_;
    int result_;
    int total_kills_;
    int total_deaths_;
    int total_assists_;
    
    // Overall match data
    std::string match_id_;
    std::string hopper_id_;
    std::string base_variant_;
    std::string map_id_;
    double match_length_;
};

class PlaylistRank
{
public:
    PlaylistRank(std::string, int, int, int, int, int,
                 int, int,
                 int, int, int);
    
    std::string name_;
    int rank_;
    int level_;
    int csr_;
    int progress_;
    int remaining_placement_;
    
    int total_games_won_;
    int total_games_lost_;
    
    int total_kills_;
    int total_deaths_;
    int total_assists_;
};

class SpartanProfile
{
public:
    SpartanProfile();
    SpartanProfile(std::string);
    
    void updateProfile(std::string);
    void printRanks();
    std::string getGamertag();
    std::string getEmblem();
    std::string getSpartan();
    int getSpartanRank();
    
    std::string getRanks();
    std::vector<PlaylistRank> getPlaylistStats();
    std::vector<RecentMatch> getRecentMatches();
    std::string printRecentMatches();
    
private:
    void parseRecentMatches(HaloAPI);
    
    std::string gamertag_;
    std::string emblem_;
    std::string spartan_;
    int spartan_rank_;
    
    std::vector<PlaylistRank> playlist_ranks_;
    std::vector<RecentMatch> recent_matches_;
    double parseDuration(std::string duration);
};


#endif /* defined(__wtHaloViewer__SpartanProfile__) */
