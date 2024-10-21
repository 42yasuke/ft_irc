#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "Client.hpp"

class Channel
{
	private:
		int invit_only;
		int topic;
		int key;
		int limit;
		bool topic_restriction;
		std::string name;
		std::string time_creation;
		std::string password;
		std::string created_at;
		std::string topic_name;
		std::vector<Client*> clients;
		std::vector<Client*> admins;
		std::vector<std::pair<char, bool> > modes;
	public:
		Channel();
		~Channel();
		Channel(Channel const &src);
		Channel &operator=(Channel const &src);
		//---------------//Setters
		void SetInvitOnly(int invit_only);
		void SetTopic(int topic);
		void SetKey(int key);
		void SetLimit(int limit);
		void SetTopicName(std::string topic_name);
		void SetPassword(std::string password);
		void SetName(std::string name);
		void SetTime(std::string time);
		void set_topicRestriction(bool value);
		void setModeAtindex(size_t index, bool mode);
		void set_createiontime(void);
		//---------------//Getters
		int GetInvitOnly(void);
		int GetTopic(void);
		int GetKey(void);
		int GetLimit(void);
		int GetClientsNumber(void);
		bool Gettopic_restriction(void) const;
		bool getModeAtindex(size_t index);
		bool clientInChannel(std::string &nick);
		std::string GetTopicName(void);
		std::string GetPassword(void);
		std::string GetName(void);
		std::string GetTime(void);
		std::string get_creationtime(void);
		std::string getModes(void);
		std::string clientChannel_list(void);
		Client *get_client(int fd);
		Client *get_admin(int fd);
		Client *GetClientInChannel(std::string name);
		//---------------//Methods
		void add_client(Client *newClient);
		void add_admin(Client *newClient);
		void remove_client(int fd);
		void remove_admin(int fd);
		bool change_clientToAdmin(std::string& nick);
		bool change_adminToClient(std::string& nick);
		//---------------//SendToAll
		void sendTo_all(std::string rpl1);
		void sendTo_all_but_not_him(std::string rpl1, int fd);
};

#endif