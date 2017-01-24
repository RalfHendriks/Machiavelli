//
//  ClientCommand.h
//  socketexample
//
//  Created by Bob Polis on 27/11/14.
//  Modified by Jeroen de Haas on 23/11/2016.
//  Copyright (c) 2016 Avans Hogeschool, 's-Hertogenbosch. All rights reserved.
//

#ifndef __socketexample__ClientCommand__
#define __socketexample__ClientCommand__

#include <string>
#include <memory>

class ClientInfo;


class ClientCommand {
public:
    ClientCommand(const std::string& command_text, std::weak_ptr<ClientInfo> client_info) : _cmd{command_text}, _info{client_info} {}

    std::string GetCommand() const { return _cmd; }
    std::weak_ptr<ClientInfo> get_client_info() const { return _info; }

private:
    std::string _cmd;
    std::weak_ptr<ClientInfo> _info;
};

#endif /* defined(__socketexample__ClientCommand__) */
