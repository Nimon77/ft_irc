#ifndef PACKETMANAGER_HPP
#define PACKETMANAGER_HPP

#include "../User/User.hpp"
#include "../Channel/ChannelManager.hpp"
#include <vector>
#include <string>

namespace irc
{
	class Server;

	struct packetParams
	{
		std::vector<std::string> args;
		User *user;
		ChannelManager *channels;
		Server *server;
	};

	void CAP(struct packetParams params);
	void NICK(struct packetParams params);
	void QUIT(struct packetParams params);

	class PacketManager
	{
	private:
		ChannelManager &channels;
		Server &server;
		std::map<std::string, void (*)(struct packetParams)> functions;

		std::vector<std::string> split(std::string str, std::string delimiter);
		void call(std::string line, User *user);

	public:
		PacketManager(ChannelManager &channels, Server &server);

		void request(std::string query, User *user);
	};
}
#include "../Server/Server.hpp"
#endif
