//
//  RecentMatchesContainer.h
//  wtHaloViewer
//
//  Created by Colin Luoma on 2016-04-03.
//
//

#ifndef __wtHaloViewer__RecentMatchesContainer__
#define __wtHaloViewer__RecentMatchesContainer__

#include <Wt/WContainerWidget>
#include "SpartanProfile.h"

class RecentMatchesContainer : public Wt::WContainerWidget
{
public:
    RecentMatchesContainer(SpartanProfile*);
    
    void update();
    
private:
    SpartanProfile *Spartan_;
    
    std::string rounded_string(double toCast, int precision, double multiplier);
    void stats_to_table(Wt::WTable *table, int row, int playlist_index);
    int calculate_csr(int division, int perc_to_next, int csr);
    int calculate_true_csr(int division, int level, int perc_to_next, int csr);
    std::string time_from_double(double minutes);
};

#endif /* defined(__wtHaloViewer__RecentMatchesContainer__) */
