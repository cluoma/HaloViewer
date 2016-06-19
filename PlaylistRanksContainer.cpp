//
//  PlaylistRanksContainer.cpp
//  wtHaloViewer
//
//  Created by Colin Luoma on 2016-03-28.
//
//

#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WLineEdit>
#include <Wt/WMenu>
#include <Wt/WMessageBox>
#include <Wt/WNavigationBar>
#include <Wt/WPopupMenu>
#include <Wt/WPopupMenuItem>
#include <Wt/WStackedWidget>
#include <Wt/WTemplate>
#include <Wt/WText>
#include <Wt/WTextArea>
#include <Wt/WTabWidget>
#include <Wt/WImage>
#include <Wt/WBootstrapTheme>
#include <Wt/WHBoxLayout>
#include <Wt/WPanel>
#include <Wt/WTable>
#include <Wt/WTableCell>
#include <Wt/WLineEdit>

#include <boost/algorithm/string.hpp>
#include <algorithm>

#include "PlaylistRanksContainer.h"

PlaylistRanksContainer::PlaylistRanksContainer(SpartanProfile *Spartan)
{
    Spartan_ = Spartan;
    Wt::WText *text = new Wt::WText("HELLO :)", this);
    this->setWidth("40%");
    this->setMinimumSize(400, 0);
    this->setPadding(3);
}

// Updates all ranks
void PlaylistRanksContainer::update()
{
    this->clear();
    Wt::WContainerWidget *ranksTableContainer = new Wt::WContainerWidget();
    Wt::WTable *table = new Wt::WTable(ranksTableContainer);
    table->setHeaderCount(1);
    
    table->elementAt(0, 0)->addWidget(new Wt::WText("Playlist"));
    table->elementAt(0, 1)->addWidget(new Wt::WText("Rank"));
    table->elementAt(0, 2)->addWidget(new Wt::WText("CSR"));
    table->elementAt(0, 3)->addWidget(new Wt::WText("Wins"));
    table->elementAt(0, 4)->addWidget(new Wt::WText("Losses"));
    table->elementAt(0, 5)->addWidget(new Wt::WText("Kills"));
    table->elementAt(0, 6)->addWidget(new Wt::WText("Deaths"));
    table->elementAt(0, 7)->addWidget(new Wt::WText("Winrate"));
    table->elementAt(0, 8)->addWidget(new Wt::WText("KDA"));
    
    std::string playlist_names[] = {"Team Arena", "Slayer", "Breakout", "FFA", "SWAT"};
    std::string division_names[] = {"Unranked", "Bronze", "Silver", "Gold", "Platinum", "Diamond", "Onyx", "Champion"};
    
    std::vector<PlaylistRank> playlist_stats = Spartan_->getPlaylistStats();
    
    // Add one division rank template for each playlist
    for (int i = 0; i < 5; i++)
    {
        // Create template from string and bind the playlist Name (order comes from playlist_names)
        //Wt::WTemplate *rank_template = new Wt::WTemplate(template_text);
        //rank_template->bindString("playlist-name", playlist_names[i]);
        new Wt::WText(playlist_names[i], table->elementAt(i+1, 0));
        
        int spartan_has_data = 0;
        // Add Rank, Division, and Rank Emblem URL
        for (int j = 0; j < playlist_stats.size(); j++)
        {
            if (i == 0 && playlist_stats[j].name_ == "c98949ae-60a8-43dc-85d7-0feb0b92e719")
            {
                stats_to_table(table, i+1, j);
                spartan_has_data = 1;
                break;
                
            }
            else if (i == 1 && playlist_stats[j].name_ == "892189e9-d712-4bdb-afa7-1ccab43fbed4")
            {
                stats_to_table(table, i+1, j);
                spartan_has_data = 1;
                break;
                
            }
            else if (i == 4 && playlist_stats[j].name_ == "2323b76a-db98-4e03-aa37-e171cfbdd1a4")
            {
                stats_to_table(table, i+1, j);
                spartan_has_data = 1;
                break;
                
            }
            else if (i == 2 && playlist_stats[j].name_ == "f72e0ef0-7c4a-4307-af78-8e38dac3fdba")
            {
                stats_to_table(table, i+1, j);
                spartan_has_data = 1;
                break;
            }
            else if (i == 3 && playlist_stats[j].name_ == "d0766624-dbd7-4536-ba39-2d890a6143a9")
            {
                stats_to_table(table, i+1, j);
                spartan_has_data = 1;
                break;
            }
        }
        if (!spartan_has_data) {
            Wt::WImage *pl4 = new Wt::WImage(Wt::WLink(getRankEmblemUrl(0,0,0)),
                                             table->elementAt(i+1, 1));
            pl4->setWidth(40);
            pl4->setHeight(40);
            new Wt::WText("", table->elementAt(i+1, 2));
            new Wt::WText("", table->elementAt(i+1, 2));
            new Wt::WText("", table->elementAt(i+1, 3));
            new Wt::WText("", table->elementAt(i+1, 4));
            new Wt::WText("", table->elementAt(i+1, 5));
            new Wt::WText("", table->elementAt(i+1, 6));
            new Wt::WText("", table->elementAt(i+1, 7));
        }
    }
    table->addStyleClass("table table-condensed");
    ranksTableContainer->decorationStyle().setBorder(Wt::WBorder(Wt::WBorder::Style::Solid, Wt::WBorder::Width::Thin, Wt::WColor(0, 0, 0)));
    ranksTableContainer->decorationStyle().setBackgroundColor(Wt::WColor(240, 240, 240));
    ranksTableContainer->setPadding(3);
    this->addWidget(ranksTableContainer);
}

// Returns the URL to the emblem image for a given rank, division, and remaining placement matches
// If rank = division = remaining_placement = 0 returns rank_urls[0]
std::string PlaylistRanksContainer::getRankEmblemUrl(int rank, int division, int remaining_placement)
{
    std::string rank_urls[] = {
        "https://content.halocdn.com/media/Default/games/halo-5-guardians/csr/unranked_00-61fca949c33f433ba7e7507d97ff130f.png","https://content.halocdn.com/media/Default/games/halo-5-guardians/csr/csr_unranked_array01-1d782b69500f4faea7bd310407f621f4.png","https://content.halocdn.com/media/Default/games/halo-5-guardians/csr/csr_unranked_array02-f43773d8a68848eba30ef9e0ee1b7fc2.png","https://content.halocdn.com/media/Default/games/halo-5-guardians/csr/csr_unranked_array03-e39338b8bf8c4b91beccbb43222a0131.png","https://content.halocdn.com/media/Default/games/halo-5-guardians/csr/csr_unranked_array04-43c99e398c564384bd05560d3c574c21.png","https://content.halocdn.com/media/Default/games/halo-5-guardians/csr/csr_unranked_array05-3f8286472cc64976a7a9263c30fdc64e.png","https://content.halocdn.com/media/Default/games/halo-5-guardians/csr/csr_unranked_array06-6416017745164c6a9d956933023a4440.png","https://content.halocdn.com/media/Default/games/halo-5-guardians/csr/csr_unranked_array07-65f39149116c43079f75b358b482f40b.png","https://content.halocdn.com/media/Default/games/halo-5-guardians/csr/csr_unranked_array08-3edd9ef3c4a94ab89961ab5b89dd3283.png","https://content.halocdn.com/media/Default/games/halo-5-guardians/csr/csr_unranked_array09-5336d7a4b9294aa9a14906351b156e3a.png","https://content.halocdn.com/media/Default/games/halo-5-guardians/csr/csr_bronze_array01-c68c7e495d124eba8343c0874d74cd36.png","https://content.halocdn.com/media/Default/games/halo-5-guardians/csr/csr_bronze_array02-431098c768ef4832b5d925ba06efbe70.png","https://content.halocdn.com/media/Default/games/halo-5-guardians/csr/csr_bronze_array03-be10288e2f534c4ebd990769ebb98205.png","https://content.halocdn.com/media/Default/games/halo-5-guardians/csr/csr_bronze_array04-961414ccdf8a4e5c8a5f9222f3f28ef3.png","https://content.halocdn.com/media/Default/games/halo-5-guardians/csr/csr_bronze_array05-ee28f7cd7ef1456cba392ca10b947961.png","https://content.halocdn.com/media/Default/games/halo-5-guardians/csr/csr_bronze_array06-b9c70a4d151846d590e38b67ae0000e7.png","https://content.halocdn.com/media/Default/games/halo-5-guardians/csr/csr_silver_array01-b4739333586340bda2eed6099e630f92.png","https://content.halocdn.com/media/Default/games/halo-5-guardians/csr/csr_silver_array02-bbdda8849cd247219a78446423790d4c.png","https://content.halocdn.com/media/Default/games/halo-5-guardians/csr/csr_silver_array03-6849dd95d8f2408188412ce2e33c137b.png","https://content.halocdn.com/media/Default/games/halo-5-guardians/csr/csr_silver_array04-42293fba165048e8ac847898376f5653.png","https://content.halocdn.com/media/Default/games/halo-5-guardians/csr/csr_silver_array05-03f6dcc3b26542daadba4b0d7c988d53.png","https://content.halocdn.com/media/Default/games/halo-5-guardians/csr/csr_silver_array06-8e3ab3d5ce5d4f27af827e52e1837439.png","https://content.halocdn.com/media/Default/games/halo-5-guardians/csr/csr_gold_array01-5053cd291bb74d6a852f0cb90a62195e.png","https://content.halocdn.com/media/Default/games/halo-5-guardians/csr/csr_gold_array02-b68d8b0ec47f4ed689d6149959b74853.png","https://content.halocdn.com/media/Default/games/halo-5-guardians/csr/csr_gold_array03-bcbc2b460a934f10b499ee7f9bec6315.png","https://content.halocdn.com/media/Default/games/halo-5-guardians/csr/csr_gold_array04-3e368546454941e7be9662bb893d80ed.png","https://content.halocdn.com/media/Default/games/halo-5-guardians/csr/csr_gold_array05-257a761c7c91418aaa03e2f68e57b117.png","https://content.halocdn.com/media/Default/games/halo-5-guardians/csr/csr_gold_array06-89344b204245450d815f0e22ec3d4b1e.png","https://content.halocdn.com/media/Default/games/halo-5-guardians/csr/csr_platinum_array01-c8df3dc366ea49209762f9b08189ffa6.png","https://content.halocdn.com/media/Default/games/halo-5-guardians/csr/csr_platinum_array02-b405ecb131fd424daf54a9c65637e0ad.png","https://content.halocdn.com/media/Default/games/halo-5-guardians/csr/csr_platinum_array03-6bbe1ab4c33245deb98306c02af52b26.png","https://content.halocdn.com/media/Default/games/halo-5-guardians/csr/csr_platinum_array04-a6b2cf1f15164557a35df91f0f5f2e85.png","https://content.halocdn.com/media/Default/games/halo-5-guardians/csr/csr_platinum_array05-fe21b9454a2944e593f9012da06810f3.png","https://content.halocdn.com/media/Default/games/halo-5-guardians/csr/csr_platinum_array06-05c733f15d1b4101ba2b04d1eb56df63.png","https://content.halocdn.com/media/Default/games/halo-5-guardians/csr/csr_diamond_array01-9721d95b267942dcb1edcce6dfc25631.png","https://content.halocdn.com/media/Default/games/halo-5-guardians/csr/csr_diamond_array02-02e21757b59540f7a9b7d39656ab855d.png","https://content.halocdn.com/media/Default/games/halo-5-guardians/csr/csr_diamond_array03-b740122fc19c4e829bb8c8fda023a1f9.png","https://content.halocdn.com/media/Default/games/halo-5-guardians/csr/csr_diamond_array04-7848018cc29c43bf932b9c03b19ed766.png","https://content.halocdn.com/media/Default/games/halo-5-guardians/csr/csr_diamond_array05-539c69e9f27e4e8bbf9a52d9755dce7c.png","https://content.halocdn.com/media/Default/games/halo-5-guardians/csr/csr_diamond_array06-b64e6ab9c4864c0f8848554853892fab.png","https://content.halocdn.com/media/Default/games/halo-5-guardians/csr/csr_top_array00-783f32318c8c49eda0365c5daa50f5b6.png","https://content.halocdn.com/media/Default/games/halo-5-guardians/csr/csr_top_array01-3755e5127c9c46368e648d58da44390e.png"
    };
    
    if (rank == 0 && division == 0 && remaining_placement == 0)
    {
        return rank_urls[0];
    }
    
    int index = 0;
    if (rank > 0 && rank < 7)
    {
        index = rank * 6 + 4 + division - 1;
    } else if (rank == 0)
    {
        index = 10 - remaining_placement;
    } else if (rank == 7)
    {
        index = 41;
    }
    
    return rank_urls[index];
}

std::string PlaylistRanksContainer::rounded_string(double toCast, int precision, double multiplier)
{
    std::ostringstream result;
    result << std::fixed << std::setprecision(precision) << toCast * multiplier;
    return result.str();
}

void PlaylistRanksContainer::stats_to_table(Wt::WTable *table, int row, int playlist_index)
{
    std::vector<PlaylistRank> playlist_stats = Spartan_->getPlaylistStats();
    
    Wt::WImage *pl2 = new Wt::WImage(Wt::WLink(getRankEmblemUrl(playlist_stats[playlist_index].rank_,
                                                                playlist_stats[playlist_index].level_,
                                                                playlist_stats[playlist_index].remaining_placement_)),
                                     table->elementAt(row, 1));
    pl2->setWidth(40);
    pl2->setHeight(40);
    new Wt::WText(std::to_string(calculate_true_csr(playlist_stats[playlist_index].rank_, playlist_stats[playlist_index].level_, playlist_stats[playlist_index].progress_, playlist_stats[playlist_index].csr_)), table->elementAt(row, 2));
    new Wt::WText(std::to_string(playlist_stats[playlist_index].total_games_won_), table->elementAt(row, 3));
    new Wt::WText(std::to_string(playlist_stats[playlist_index].total_games_lost_), table->elementAt(row, 4));
    new Wt::WText(std::to_string(playlist_stats[playlist_index].total_kills_), table->elementAt(row, 5));
    new Wt::WText(std::to_string(playlist_stats[playlist_index].total_deaths_), table->elementAt(row, 6));
    
    double win_rate = (double)playlist_stats[playlist_index].total_games_won_/((double)playlist_stats[playlist_index].total_games_lost_+(double)playlist_stats[playlist_index].total_games_won_);
    std::string win_perc = rounded_string(win_rate, 1, 100.0) + "%";
    new Wt::WText(win_perc, table->elementAt(row, 7));
    
    double kda = ( (float)playlist_stats[playlist_index].total_kills_ + ((float)playlist_stats[playlist_index].total_assists_/3.0) )/(float)playlist_stats[playlist_index].total_deaths_;
    new Wt::WText(rounded_string(kda, 2, 1.0), table->elementAt(row, 8));
}

// Get what should be shown in the CSR column
// If Onyx (6) or Champion (7) return CSR
// Else return the percent progress towards the next rank
int PlaylistRanksContainer::calculate_csr(int division, int perc_to_next, int csr)
{
    if (division == 6 || division == 7)
    {
        return csr;
    }
    else
    {
        return perc_to_next;
    }
}

int PlaylistRanksContainer::calculate_true_csr(int division, int level, int perc_to_next, int csr)
{
    if (division == 0)
    {
        return 0;
    }
    else if (division == 6 || division == 7)
    {
        return csr;
    }
    else
    {
        return (division - 1) * 6 * 50 + (level - 1) * 50 + perc_to_next / 2;
    }
}
