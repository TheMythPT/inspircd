/*
 * InspIRCd -- Internet Relay Chat Daemon
 *
 *   Copyright (C) 2009 Daniel De Graaf <danieldg@inspircd.org>
 *   Copyright (C) 2007 Robin Burchell <robin+git@viroteck.net>
 *
 * This file is part of InspIRCd.  InspIRCd is free software: you can
 * redistribute it and/or modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation, version 2.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "inspircd.h"

/** Handle /LOADMODULE.
 */
class CommandLoadmodule : public Command
{
 public:
	/** Constructor for loadmodule.
	 */
	CommandLoadmodule ( Module* parent) : Command(parent,"LOADMODULE",1,1) { flags_needed='o'; syntax = "<modulename>"; }
	/** Handle command.
	 * @param parameters The parameters to the command
	 * @param user The user issuing the command
	 * @return A value from CmdResult to indicate command success or failure.
	 */
	CmdResult Handle(const std::vector<std::string>& parameters, User *user);
};

/** Handle /LOADMODULE
 */
CmdResult CommandLoadmodule::Handle (const std::vector<std::string>& parameters, User *user)
{
	if (ServerInstance->Modules->Load(parameters[0]))
	{
		ServerInstance->SNO->WriteGlobalSno('a', "NEW MODULE: %s loaded %s",user->nick.c_str(), parameters[0].c_str());
		user->WriteNumeric(RPL_LOADEDMODULE, "%s :Module successfully loaded.", parameters[0].c_str());
		return CMD_SUCCESS;
	}
	else
	{
		user->WriteNumeric(ERR_CANTLOADMODULE, "%s :%s", parameters[0].c_str(), ServerInstance->Modules->LastError().c_str());
		return CMD_FAILURE;
	}
}

COMMAND_INIT(CommandLoadmodule)
