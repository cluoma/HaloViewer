//
//  MetaDataLookup.cpp
//  wtHaloViewer
//
//  Created by Colin Luoma on 2016-04-16.
//
//

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <stdio.h>

#include "MetaDataLookup.h"


std::string getNameFromMap(std::string map_id)
{
    std::string ids[] = {"c93d708f-f206-11e4-a815-24be05e24f7e","cb251c51-f206-11e4-8541-24be05e24f7e","c854e54f-f206-11e4-bddc-24be05e24f7e","c8d69870-f206-11e4-b477-24be05e24f7e","73ed1fd0-45e5-4bb9-ab6a-d2852c04ea7d","96c3e3dd-7703-4086-9e64-e3a23932bdc4","1c4f8e19-b046-4f78-9e2d-959cba84663d","825065cf-df57-42e3-b845-830e7340ea43","9a188f67-1664-4d7b-83ca-1d74f714f764","2702ea83-2c3e-4fd5-8370-60d9a6e0422f","82f8471c-a2ef-4089-ac04-7e829fdec912","fcd7caa4-37c9-4365-bdda-9041dc6699ed","7dc80b62-dd39-41d5-9b7a-d71fd8832c07","db9f76c4-6f9a-4c1a-9b48-7aaf59472ccd","b486c8f6-0b00-4a46-b91a-0514969d7c94","37c717b8-7ae8-4be4-aaa2-945e083bcf3e","72c98d4a-4ee4-40db-baf3-1b1cc3672654","f352eafd-d307-4341-a192-16f7f3f5b43c","8d72dd82-3afb-409e-bee0-512dc97893d2","c822b1c0-f206-11e4-9755-24be05e24f7e","cae999f0-f206-11e4-9835-24be05e24f7e","c89dae21-f206-11e4-a1c2-24be05e24f7e","c74c9d0f-f206-11e4-8330-24be05e24f7e","c7edbf0f-f206-11e4-aa52-24be05e24f7e","cebd854f-f206-11e4-b46e-24be05e24f7e","cd844200-f206-11e4-9393-24be05e24f7e","cdb934b0-f206-11e4-8810-24be05e24f7e","cc040aa1-f206-11e4-a3e0-24be05e24f7e","caacb800-f206-11e4-81ab-24be05e24f7e","cdee4e70-f206-11e4-87a2-24be05e24f7e","cb914b9e-f206-11e4-b447-24be05e24f7e","ce1dc2de-f206-11e4-a646-24be05e24f7e","c7805740-f206-11e4-982c-24be05e24f7e","c7b7baf0-f206-11e4-ae9a-24be05e24f7e","c96ff240-f206-11e4-b581-24be05e24f7e","ca737f8f-f206-11e4-a7e2-24be05e24f7e","cbcea2c0-f206-11e4-8c4a-24be05e24f7e","cc74f4e1-f206-11e4-ad66-24be05e24f7e","5e130537-2275-40b5-9758-94b1986934ed","ce89a40f-f206-11e4-b83f-24be05e24f7e","cc3ca6d1-f206-11e4-87c3-24be05e24f7e"};
    
    std::string names[] = {"Urban","Raid on Apex 7","March on Stormbreak","Escape from A.R.C.","Osiris","Blue Team","Glassed","Unconfirmed","Alliance","Before the Storm","Genesis","The Breaking","Guardians","Meridian Station","Evacuation","Reunion","Sword of Sanghelios","Enemy Lines","Battle of Sunaion","Summit","Array","Dispatch","Alpine","Breakout Arena","Coliseum","Eden","Empire","Fathom","Plaza","Regret","The Rig","Truth","Glacier","Parallax","Battle of Noctus","Overgrowth","Riptide ","Torque","Skirmish at Darkstar","Tyrant","Stasis"};
    
    for (int i = 0; i < sizeof(ids)/sizeof(ids[0]); i++)
    {
        if (map_id == ids[i])
            return names[i];
    }
    return "Unknown";
}

std::string getNameFromHopper(std::string hopper_id)
{
    std::string ids[] = {"7b7e892c-d9b7-4b03-bef8-c6a071df28ef","f27a65eb-2d11-4965-aa9c-daa088fa5c9c","f72e0ef0-7c4a-4307-af78-8e38dac3fdba","892189e9-d712-4bdb-afa7-1ccab43fbed4","c98949ae-60a8-43dc-85d7-0feb0b92e719","b617e24f-71aa-432b-a8a0-a9b417a3d47e","bdd69f49-d962-4d9a-8a7a-ca1013609347","b6dc4d50-4c24-4b4e-8fc5-6a378eeb299d","505f3f9e-363f-4148-918b-46c43c33fe50","a3f93d83-d89c-4373-b311-ec482f8d236a","e10d9bd5-9efd-4b91-bf83-2f55b183a6f5","b50c4dc2-6c86-4d79-aa8a-23a65da292c6","27140f92-3b4e-4bca-b43c-ab33d7bf3986","78ba29d5-6fdf-4d2a-8e58-14baf004fd09","0e39ead4-383b-4452-bbd4-babb7becd82e","98c52586-04bb-4645-99ba-55c772ac6f01","0bcf2be1-3168-4e42-9fb5-3551d7dbce77","c00181ea-f931-41c0-aa6d-45904cb765eb","a355df34-acd9-45c3-bc1c-e024891df5c0","476afe03-3a33-4cf1-9134-7d8b8422bea3","69b4de92-7bd4-49ea-aa93-4aeefb730a9a","2b04d702-0996-4b8e-8402-a7fc8b888bef","8e393993-ea0d-4513-860e-a5acb0fe9234","b8d651a5-087e-4990-b209-d335b6c7a05a","9c4f9280-0054-44f6-a3bc-7a70ed4fda67","e31d2f7e-7aa0-47f4-b1f8-6cea9cc70bbe","0625fb37-6c3e-4526-b413-d252128b42ac","ea669123-09c0-4c93-bf95-bdbe74d55e3d","2d4afa59-b046-4e4e-b918-c02687f9ca87","35ddd45e-065e-42fc-8c25-fe765739bf12","8d3beae9-e4e8-4c14-bbf0-475286ff9404","62b0b398-c790-4003-87ef-b4024e96f619","79b6f0a6-5622-4c5a-a770-634d7dcc4391","e1aaa797-c544-426e-9a0b-66a0c86a85c7","91233698-8234-4330-be10-05d54d1d565c","c7ad591d-1c1e-4c11-8bc8-cf90d8638faf","00bb0332-6edc-4dbb-95dd-cbe6d25847be","c59a19c1-fa74-4952-ba40-b74e348813ae","a822dde2-106c-4740-88fa-e83c8219a77e","c506d28e-fd7c-4a45-b7d1-05e20f1d425b","a57e68b7-6623-410f-9663-c8f9e9942210","819eb188-1a1c-48b4-9af3-283d2447ff6f","5728f612-3f20-4459-98bd-3478c79c4861","88b7de19-113c-4beb-af7f-8553aeda3f4c","7385b4a1-86bf-4aec-b9c2-411a6aa48633","4b12472e-2a06-4235-ba58-f376be6c1b39","d0766624-dbd7-4536-ba39-2d890a6143a9","2323b76a-db98-4e03-aa37-e171cfbdd1a4","bc0f8ad6-31e6-4a18-87d9-ad5a2dbc8212","780cc101-005c-4fca-8ce7-6f36d7156ffe","ddfb6af3-2a64-4ecd-8eda-c1ce4413b676","fe2ad4e1-3def-46a9-a18e-9ab685aa66d4","d21c8381-26f1-4d65-832a-ef9fa0854eb5","355dc154-9809-4edb-8ed4-fff910c6ae9c","0504ca3c-de41-48f3-b9c8-3aab534d69e5","f0c9ef9a-48bd-4b24-9db3-2c76b4e23450","da2cbc67-fb2f-43b1-9a2f-88cc5e1c4dd0","f44a5508-e208-4c65-835d-a155e363abc8","2e812e09-912f-458b-a659-4ccb84232c65","14bdff11-2742-486b-b26a-4255b137752f","b5d5a242-ffa5-4d88-a229-5031916be036","86587043-e5b3-44ec-a478-261d61b30b2d","bf7e7002-5655-4ee3-86f9-8796d0c6b83e","e66af80b-9039-47a7-826e-3c694280b2c4","18dac69a-673b-4943-ac7f-8bd19f7672b1","84d7dafa-0419-4e6f-a990-4987ae57611c"};
        
    std::string names[] = {"Free-for-All","SWAT","Breakout","Slayer ","Team Arena Summer Preview","Warzone Turbo","Warzone Kraken 24p","Warzone Fast Test","Warzone Accelerated","Networking Warzone","2p Warzone Assault","Warzone","24p Warzone Test","Warzone Ring Only","Warzone Assault","24p Warzone Assault Test","Big Team Battle","2p Strongholds","2p Slayer ","2p Kraken","2p Capture The Flag","2p Breakout","2p Arena","ArenaMatchmakingFriendJIPDisabledBackfillJIPEnabled1RotationHopper","ArenaMatchmakingFriendJIPEnabledBackfillJIPEnabled1RotationHopper","ArenaMatchmakingFriendJIPEnabledBackfillJIPEnabled1RotationHopper","Broadsword_NightlyTest_Min4P","Warzone Hopper","RuleEngineBanRuleEVT Banning Rule Test Hopper","Warzone Hopper","Big Team Battle Hopper","Arena2pMinNoPresenceChecksHopper","ArenaMatchmaking3TeamsFriendJIPEnabledBackfillJIPEnabled1RotationHopper","LobbyRuleEngineEVT Test Hopper QOS Enabled","ArenaMatchmakingFriendJIPDisabledBackfillJIPDisabled1RotationHopper","ArenaMatchmakingFriendJIPEnabledBackfillJIPDisabled1RotationHopper","ArenaMatchmakingFriendJIPDisabledBackfillJIPEnabled1RotationHopper","ArenaMatchmakingFriendJIPEnabledBackfillJIPEnabled2RotationHopper","ArenaMatchmakingFriendJIPEnabledBackfillJIPEnabled1RotationHopper","Pre-Release Arena","Pre-Release Warzone","Social Shotty Snipers","Social Doubles","Social Rumble Rockets","Social Snipers","Social Arena Breakout","Free-for-All","SWAT","Super Fiesta","Big Team Battle","Social Rocket Party","Game Day Slayer","Social CTF","Grifball","Social Assault","Social Fiesta","Social Strongholds","Social SWAT","Social Slayer","Warzone Firefight Beta","Social Multi-team","FFA SWAT","Social Doubles","Test Hopper Y","Test Hopper X","Infection"};
    
    for (int i = 0; i < sizeof(ids)/sizeof(ids[0]); i++)
    {
        if (hopper_id == ids[i])
            return names[i];
    }
    return "Unknown";
}

std::string getNameFromBaseVariant(std::string base_variant)
{
    std::string ids[] = {"1571fdac-e0b4-4ebc-a73a-6e13001b71d3","257a305e-4dd3-41f1-9824-dfe7e8bd59e1","1e473914-46e4-408d-af26-178fb115de76","a2949322-dc84-45ab-8454-cf94fb28c189","42f97cca-2cb4-497a-a0fd-ceef1ba46bcc","f6de5351-3797-41e9-8053-7fb111a3a1a0","00000003-0000-0010-8000-00aa00389b71","8d4a3dbc-ef7a-405e-862b-34093ff582fd","b45854a7-e6e1-4a9c-9104-139934511779","65f033d2-1303-4748-bc26-ef62c38eced4","a2b0a49f-a1ca-cdc2-c0bf-8fa1cacdc2c0","b0df8938-0fb6-42ee-846f-a0c3593344d5","dda182c5-4b50-4a0f-86f3-fcb5e0db4df3","dfd51ee3-9060-46c3-b131-08d946c4c7b9","f6051f51-bbb6-4ccc-8ac0-cf42b7291c76"};
    
    std::string names[] = {"Strongholds","Slayer","Breakout","Capture the Flag","Warzone Assault","Warzone","Campaign","Big Team CTF","Big Team Strongholds","Big Team Slayer","NA","Assault","Grifball","Warzone Firefight","Infection"};
    
    for (int i = 0; i < sizeof(ids)/sizeof(ids[0]); i++)
    {
        if (base_variant == ids[i])
            return names[i];
    }
    return "Unknown";
}