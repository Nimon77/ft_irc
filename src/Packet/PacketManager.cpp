#include "PacketManager.hpp"
#include <iostream>

std::vector<std::string> irc::PacketManager::split(std::string str, std::string delimiter)
{
	std::vector<std::string> args;
	size_t index;
	while ((index = str.find(delimiter)) != std::string::npos)
	{
		args.push_back(str.substr(0, index));
		str.erase(0, index + delimiter.length());
	}
	args.push_back(str);
	return args;
}
void irc::PacketManager::call(std::string line, User *user)
{
	struct packetParams params;
	params.args = split(line, " ");
	if (!params.args[0].size())
		return;
	if (!functions.count(params.args[0]))
	{
		std::cout << "Unknown command: " << line << std::endl;
		return;
	}

	params.user = user;
	params.channels = &channels;
	params.server = &server;
	functions[params.args[0]](params);
}

irc::PacketManager::PacketManager(ChannelManager &channels, Server &server)
	: channels(channels), server(server), functions()
{
	functions["CAP"] = CAP;
	functions["NICK"] = NICK;
	functions["QUIT"] = QUIT;
	functions["USER"] = USER;
	functions["PING"] = PING;
	functions["JOIN"] = JOIN;
}

void irc::PacketManager::request(std::string query, User *user)
{
	std::vector<std::string> lines = split(query, "\r\n");
	size_t index = 0;
	size_t len = lines.size();
	while (index < len)
	{
		call(lines[index], user);
		index++;
	}
}
