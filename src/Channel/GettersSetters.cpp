#include "Channel.hpp"

/* ******************** Getters ******************** */
bool Channel::GetInvitOnly(void) { return this->inviteOnly;}

int Channel::GetLimit(void) { return this->limit; }

int Channel::GetClientsNumber(void) { return this->clients.size() + this->admins.size(); }

std::string Channel::get_creationtime(void) {return created_at;}

bool Channel::GetTopicRestriction() const { return this->topic_restriction; }

bool Channel::getModeAtindex(size_t index) { return modes[index].second; }

bool Channel::clientInChannel(std::string &nick)
{
	for (size_t i = 0; i < clients.size(); i++)
	{
		if (clients[i]->GetNickName() == nick)
			return true;
	}
	for (size_t i = 0; i < admins.size(); i++)
	{
		if (admins[i]->GetNickName() == nick)
			return true;
	}
	return false;
}

std::string Channel::GetTopicName(void) { return this->topic_name; }

std::string Channel::GetPassword(void) { return this->password; }

std::string Channel::GetName(void) { return this->name; }

std::string Channel::GetTime(void) { return this->time_creation; }

std::string Channel::getModes(void)
{
	std::string mode;
	for (size_t i = 0; i < modes.size(); i++)
	{
		if (modes[i].first != 'o' && modes[i].second)
			mode.push_back(modes[i].first);
	}
	if (!mode.empty())
		mode.insert(mode.begin(), '+');
	return mode;
}

std::string Channel::clientChannel_list()
{
	std::string list;
	for (size_t i = 0; i < admins.size(); i++)
	{
		list += "@" + admins[i]->GetNickName();
		if ((i + 1) < admins.size())
			list += " ";
	}
	if (clients.size())
		list += " ";
	for (size_t i = 0; i < clients.size(); i++)
	{
		list += clients[i]->GetNickName();
		if ((i + 1) < clients.size())
			list += " ";
	}
	return list;
}

Client *Channel::get_client(int fd)
{
	for (std::vector<Client*>::iterator it = clients.begin(); it != clients.end(); ++it)
	{
		if ((*it)->GetFd() == fd)
			return (*it);
	}
	return NULL;
}

Client *Channel::get_client(std::string nick)
{
	for (std::vector<Client*>::iterator it = clients.begin(); it != clients.end(); ++it)
	{
		if ((*it)->GetNickName() == nick)
			return (*it);
	}
	return NULL;
}

Client *Channel::get_admin(int fd)
{
	for (std::vector<Client*>::iterator it = admins.begin(); it != admins.end(); ++it)
	{
		if ((*it)->GetFd() == fd)
			return (*it);
	}
	return NULL;
}

Client *Channel::GetClientInChannel(std::string name)
{
	for (std::vector<Client*>::iterator it = clients.begin(); it != clients.end(); ++it)
	{
		if ((*it)->GetNickName() == name)
			return (*it);
	}
	for (std::vector<Client*>::iterator it = admins.begin(); it != admins.end(); ++it)
	{
		if ((*it)->GetNickName() == name)
			return (*it);
	}
	return NULL;
}

/* ******************** Setters ******************** */
void Channel::SetInvitOnly(bool inviteOnly) { this->inviteOnly = inviteOnly;}

void Channel::SetTime(std::string time) { this->time_creation = time; }

void Channel::SetLimit(int limit) { this->limit = limit; }

void Channel::SetTopicName(std::string topic_name) { this->topic_name = topic_name; this->set_createiontime();}

void Channel::SetPassword(std::string password) { this->password = password; }

void Channel::SetName(std::string name) { this->name = name; }

void Channel::setTopicRestriction(bool value) { this->topic_restriction = value; }

void Channel::setModeAtindex(size_t index, bool mode) { modes[index].second = mode; }

void Channel::set_createiontime()
{
	std::time_t _time = std::time(NULL);
	std::ostringstream oss;
	oss << _time;
	this->created_at = std::string(oss.str());
}
