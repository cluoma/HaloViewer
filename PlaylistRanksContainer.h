//
//  PlaylistRanksContainer.h
//  wtHaloViewer
//
//  Created by Colin Luoma on 2016-03-28.
//
//

#ifndef __wtHaloViewer__PlaylistRanksContainer__
#define __wtHaloViewer__PlaylistRanksContainer__

#include <Wt/WContainerWidget>
#include "SpartanProfile.h"

class PlaylistRanksContainer : public Wt::WContainerWidget
{
public:
    PlaylistRanksContainer(SpartanProfile*);
    
    void update();
    
private:
    SpartanProfile *Spartan_;
    
    std::string getRankEmblemUrl(int rank, int division, int remaining_placement);
    std::string rounded_string(double toCast, int precision, double multiplier);
    void stats_to_table(Wt::WTable *table, int row, int playlist_index);
    int calculate_csr(int division, int perc_to_next, int csr);
    int calculate_true_csr(int division, int level, int perc_to_next, int csr);
};

#endif /* defined(__wtHaloViewer__PlaylistRanksContainer__) */
