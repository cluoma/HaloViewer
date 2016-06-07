//
//  MatchData.h
//  wtHaloViewer
//
//  Created by Colin Luoma on 2016-04-17.
//
//

#ifndef __wtHaloViewer__MatchData__
#define __wtHaloViewer__MatchData__

#include <stdio.h>

class MatchData
{
public:
    MatchData(std::string match_id);
    
private:
    std::string match_id_;
    
    std::vector<std::string> gamertags_;
};

#endif /* defined(__wtHaloViewer__MatchData__) */
