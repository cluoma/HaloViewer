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

#include <json/json.h>

#include "RecentMatchesContainer.h"
#include "HaloAPI.h"
#include "MetaDataLookup.h"

RecentMatchesContainer::RecentMatchesContainer(SpartanProfile *Spartan)
{
    Spartan_ = Spartan;
    Wt::WText *text = new Wt::WText("HELLO :)", this);
    this->setWidth("60%");
    this->setMinimumSize(500,0);
    this->setPadding(3);
}

// Updates all ranks
void RecentMatchesContainer::update()
{
    this->clear();
    
    std::vector<RecentMatch> recent_matches = Spartan_->getRecentMatches();
    
    // Create halo api with an api key (get api key from 343i api site)
    //HaloAPI halo_api("05cdc66c52ca4465b0b6e3c56bb87b71");
    
    for (int i = 0; i < recent_matches.size() && i < 10; i++)
    {
        // CUSTOM CONTAINERS
        Wt::WContainerWidget *myContainer = new Wt::WContainerWidget();
        myContainer->decorationStyle().setBorder(Wt::WBorder(Wt::WBorder::Style::Solid, Wt::WBorder::Width::Thin, Wt::WColor(0, 0, 0)));
        myContainer->decorationStyle().setBackgroundColor(Wt::WColor(240, 240, 240));
        myContainer->setPadding(3);
        myContainer->setMargin(3, Wt::Bottom);
        
        std::string title_string = "<b>" + getNameFromHopper(recent_matches[i].hopper_id_) + " / </b>" + getNameFromBaseVariant(recent_matches[i].base_variant_) + "<b> / </b>" + getNameFromMap(recent_matches[i].map_id_) + "";
        Wt::WText *someText = new Wt::WText(title_string, myContainer);
        
        Wt::WPushButton *myButton = new Wt::WPushButton(" + ", myContainer);
        myButton->setFloatSide(Wt::Right);
        
        std::string game_time = time_from_double(recent_matches[i].match_length_);
        Wt::WText *someMoreText = new Wt::WText(game_time, myContainer);
        someMoreText->setFloatSide(Wt::Right);
        
        Wt::WStackedWidget *myStack = new Wt::WStackedWidget(myContainer);
        Wt::WText *text1 = new Wt::WText("text1", myStack);

        
        myButton->clicked().connect(std::bind([=]()
        {
            if (myStack->currentIndex() == 0)
            {
                myButton->setText(" - ");
                Wt::WContainerWidget *stats_table = new Wt::WContainerWidget(myStack);
                Wt::WTable *table = new Wt::WTable(stats_table);
                table->setHeaderCount(1);
                table->elementAt(0, 0)->addWidget(new Wt::WText("Gamertag"));
                HaloAPI halo_api("05cdc66c52ca4465b0b6e3c56bb87b71");
                std::vector<std::string> gamertags;
                
                std::string json_data = halo_api.getPostGameCarnageArena(recent_matches[i].match_id_);
                Json::Value root;   // will contains the root value after parsing.
                Json::Reader reader;
                bool parsingSuccessful = reader.parse( json_data, root );
                if ( !parsingSuccessful )
                {
                    // report to the user the failure and their locations in the document.
                    std::cout  << "Failed to parse configuration\n"
                    << reader.getFormattedErrorMessages();
                }
                const Json::Value plugins = root;
                
                for (int j = 0; j < plugins["PlayerStats"].size(); j++)
                {
                    std::string tag(
                                    plugins["PlayerStats"][j]["Player"]["Gamertag"].asString()
                                    );
                    gamertags.push_back(tag);
                    table->elementAt(j+1, 0)->addWidget(new Wt::WText(tag));
                }
                table->addStyleClass("table table-condensed");
                myStack->setCurrentIndex(1);
            } else
            {
                delete myStack->currentWidget();
                myStack->setCurrentIndex(0);
                myButton->setText(" + ");
            }
        }));
        this->addWidget(myContainer);
    }
}

std::string RecentMatchesContainer::rounded_string(double toCast, int precision, double multiplier)
{
    std::ostringstream result;
    result << std::fixed << std::setprecision(precision) << toCast * multiplier;
    return result.str();
}

void RecentMatchesContainer::stats_to_table(Wt::WTable *table, int row, int playlist_index)
{
    
}

// Get what should be shown in the CSR column
// If Onyx (6) or Champion (7) return CSR
// Else return the percent progress towards the next rank
int RecentMatchesContainer::calculate_csr(int division, int perc_to_next, int csr)
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

int RecentMatchesContainer::calculate_true_csr(int division, int level, int perc_to_next, int csr)
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

std::string RecentMatchesContainer::time_from_double(double minutes)
{
    std::ostringstream result;
    result << std::fixed << std::setprecision(0) << minutes << "m " << (minutes - floor(minutes)) * 60 << "s   ";
    return result.str();
}
