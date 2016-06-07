//
//  HaloAPI.h
//  wtHaloViewer
//
//  Created by Colin Luoma on 2016-04-03.
//
//

#ifndef __wtHaloViewer__HaloAPI__
#define __wtHaloViewer__HaloAPI__

#include <stdio.h>

class HaloAPI
{
public:
    HaloAPI();
    HaloAPI(std::string api_key);
    
    std::string getEmblemURL(std::string game);
    std::string getServiceRecord(std::string mode, std::string game);
    std::string getMatchesForPlayer(std::string mode, int count, int start, std::string game);
    std::string getPostGameCarnageArena(std::string match_id);
    
private:
    std::string api_key_;
};

#endif /* defined(__wtHaloViewer__HaloAPI__) */
