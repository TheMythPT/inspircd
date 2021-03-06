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
#include "core_user.h"

CmdResult CommandUserhost::Handle(User* user, const Params& parameters)
{
	const bool has_privs = user->HasPrivPermission("users/auspex");

	std::string retbuf;

	unsigned int max = parameters.size();
	if (max > 5)
		max = 5;

	for (unsigned int i = 0; i < max; i++)
	{
		User *u = ServerInstance->FindNickOnly(parameters[i]);

		if ((u) && (u->registered == REG_ALL))
		{
			retbuf += u->nick;

			if (u->IsOper())
			{
				// XXX: +H hidden opers must not be shown as opers
				if ((u == user) || (has_privs) || (!u->IsModeSet(hideopermode)))
					retbuf += '*';
			}

			retbuf += '=';
			retbuf += (u->IsAway() ? '-' : '+');
			retbuf += u->ident;
			retbuf += '@';
			retbuf += u->GetHost(u == user || has_privs);
			retbuf += ' ';
		}
	}

	user->WriteNumeric(RPL_USERHOST, retbuf);

	return CMD_SUCCESS;
}
