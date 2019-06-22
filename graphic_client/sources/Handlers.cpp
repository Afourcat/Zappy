/*
** EPITECH PROJECT, 2019
** Zappy
** File description:
** Graphical Client
*/

#include <algorithm>
#include "Handlers.hpp"

const std::vector<std::tuple<GRAPHIC_PACKETS_FROM_SERVER, data_processor_t>> Handlers::HANDLERS = {
    std::make_tuple(SRV_MAP_SIZE, gotMapSize),
    std::make_tuple(SRV_TILE_CONTENT, gotTileContent),
    std::make_tuple(SRV_TEAMS_NAMES, nullptr),
    std::make_tuple(SRV_NEW_PLAYER_CONNECT, gotNewPlayerConnect),
    std::make_tuple(SRV_PLAYER_POSITION, gotPlayerPosition),
    std::make_tuple(SRV_PLAYER_LEVEL, gotPlayerLevel),
    std::make_tuple(SRV_PLAYER_INVENTORY, nullptr),
    std::make_tuple(SRV_EXPULSION, nullptr),
    std::make_tuple(SRV_BROADCAST, nullptr),
    std::make_tuple(SRV_INCANTATION_START, nullptr),
    std::make_tuple(SRV_INCANTATION_END, nullptr),
    std::make_tuple(SRV_EGG_LAYING, nullptr),
    std::make_tuple(SRV_RESOURCE_DROP, nullptr),
    std::make_tuple(SRV_RESOURCE_COLLECT, nullptr),
    std::make_tuple(SRV_PLAYER_DEATH, gotDeathPlayer),
    std::make_tuple(SRV_EGG_LAYED, nullptr),
    std::make_tuple(SRV_EGG_HATCHING, nullptr),
    std::make_tuple(SRV_PLAYER_CONNECT_EGG, nullptr),
    std::make_tuple(SRV_PLAYER_DEATH_EGG, nullptr),
    std::make_tuple(SRV_TIME_UNIT_REQUEST, nullptr),
    std::make_tuple(SRV_TIME_UNIT_CHANGE, nullptr),
    std::make_tuple(SRV_END_GAME, nullptr),
    std::make_tuple(SRV_MESSAGE_FROM_SRV, nullptr),
    std::make_tuple(SRV_UNKNOWN_COMMAND, nullptr),
    std::make_tuple(SRV_COMMAND_PARAMETER, nullptr),
};

const std::vector<std::tuple<GRAPHIC_PACKETS_FROM_SERVER, std::string>> Handlers::NAMES = {
    std::make_tuple(SRV_MAP_SIZE, std::string("SRV_MAP_SIZE")),
    std::make_tuple(SRV_TILE_CONTENT, std::string("SRV_TILE_CONTENT")),
    std::make_tuple(SRV_TEAMS_NAMES, std::string("SRV_TEAMS_NAMES")),
    std::make_tuple(SRV_NEW_PLAYER_CONNECT, std::string("SRV_NEW_PLAYER_CONNECT")),
    std::make_tuple(SRV_PLAYER_POSITION, std::string("SRV_PLAYER_POSITION")),
    std::make_tuple(SRV_PLAYER_LEVEL, std::string("SRV_PLAYER_LEVEL")),
    std::make_tuple(SRV_PLAYER_INVENTORY, std::string("SRV_PLAYER_INVENTORY")),
    std::make_tuple(SRV_EXPULSION, std::string("SRV_EXPULSION")),
    std::make_tuple(SRV_BROADCAST, std::string("SRV_BROADCAST")),
    std::make_tuple(SRV_INCANTATION_START, std::string("SRV_INCANTATION_START")),
    std::make_tuple(SRV_INCANTATION_END, std::string("SRV_INCANTATION_END")),
    std::make_tuple(SRV_EGG_LAYING, std::string("SRV_EGG_LAYING")),
    std::make_tuple(SRV_RESOURCE_DROP, std::string("SRV_RESOURCE_DROP")),
    std::make_tuple(SRV_RESOURCE_COLLECT, std::string("SRV_RESOURCE_COLLECT")),
    std::make_tuple(SRV_PLAYER_DEATH, std::string("SRV_PLAYER_DEATH")),
    std::make_tuple(SRV_EGG_LAYED, std::string("SRV_EGG_LAYED")),
    std::make_tuple(SRV_EGG_HATCHING, std::string("SRV_EGG_HATCHING")),
    std::make_tuple(SRV_PLAYER_CONNECT_EGG, std::string("SRV_PLAYER_CONNECT_EGG")),
    std::make_tuple(SRV_PLAYER_DEATH_EGG, std::string("SRV_PLAYER_DEATH_EGG")),
    std::make_tuple(SRV_TIME_UNIT_REQUEST, std::string("SRV_TIME_UNIT_REQUEST")),
    std::make_tuple(SRV_TIME_UNIT_CHANGE, std::string("SRV_TIME_UNIT_CHANGE")),
    std::make_tuple(SRV_END_GAME, std::string("SRV_END_GAME")),
    std::make_tuple(SRV_MESSAGE_FROM_SRV, std::string("SRV_MESSAGE_FROM_SRV")),
    std::make_tuple(SRV_UNKNOWN_COMMAND, std::string("SRV_UNKNOWN_COMMAND")),
    std::make_tuple(SRV_COMMAND_PARAMETER, std::string("SRV_COMMAND_PARAMETER")),
};

void Handlers::gotMapSize(GameState &state, Window &window)
{
    if (state.tileList.empty())
    {
        std::string path = REALPATH("grass.bmp");
        auto *packet = (srv_map_size_t *)state.lastData;
        std::cout << "Map size: (" << packet->x << ", " << packet->y << ")" << std::endl;
        state.mapSize = *packet;
        for (auto elem : state.tileList)
            delete elem;
        state.tileList = std::vector<Tile *>(0);

        unsigned int count = (packet->x * packet->y);
        for (unsigned int i = 0; i < count; i += 1)
            state.tileList.push_back(new Tile(path, window.getRender()));
        state.protocol.askMapContent();
    }
}

void Handlers::gotDeathPlayer(GameState &state, Window &window)
{
    auto *packet = (srv_player_death_t *)state.lastData;

    state.playerList.erase(
        std::remove_if(state.playerList.begin(), state.playerList.end(), [packet](Player *player) {
            return player->getPlayerNum() == packet->player_num;
        }),
        state.playerList.end()
    );
}

void Handlers::gotTileContent(GameState& state, Window& window)
{
    auto* packet = (srv_tile_content_t*)state.lastData;
    size_t pos = (packet->y * state.mapSize.x) + packet->x;
    std::vector<int> temp(0);
    std::cout << "Tile: (" << packet->x << ", " << packet->y << ") data" << std::endl;

    temp.push_back(packet->q0);
    temp.push_back(packet->q1);
    temp.push_back(packet->q2);
    temp.push_back(packet->q3);
    temp.push_back(packet->q4);
    temp.push_back(packet->q5);
    temp.push_back(packet->q6);
    state.tileList.at(pos)->setTileContent(packet->x, packet->y, temp, packet->players);
}

void Handlers::gotNewPlayerConnect(GameState& state, Window& window)
{
    auto* packet = (srv_new_player_connect_t*)state.lastData;
    std::string path = REALPATH("player.bmp");
    Player* temp = new Player(path, window.getRender());

    temp->setPosition(packet->x, packet->y);
    temp->setPlayerNum(packet->player_num);
    temp->setOrientation(packet->orientation);
    temp->setTeamName(std::string(packet->team_name));
    state.playerList.push_back(temp);
    std::cout << "Player connection at (" << packet->x << ", " << packet->y << ")." << std::endl;
}

void Handlers::gotPlayerPosition(GameState& state, Window& window)
{
    auto* packet = (srv_player_pos_t*)state.lastData;

    std::cout << "Placket: " << packet->x << ", " << packet->y << std::endl;

    for (auto elem : state.playerList) {
        if (elem->getPlayerNum() == packet->player_num) {
            elem->setPosition(packet->x, packet->y);
        }
    }
}

void Handlers::gotPlayerLevel(GameState& state, Window& window)
{
    auto* packet = (srv_player_level_t*)state.lastData;

    for (auto elem : state.playerList) {
        if (elem->getPlayerNum() == packet->player_num) {
            elem->setLevel(packet->level);
        }
    }
}
