/**
 * \file  common.h
 * \brief Common type definitions.
 *
 * Copyright (C) 2010 Guillermo Biset
 *
 * This file is part of the FuD project.
 *
 * Language:       C++
 *
 * Author:         Guillermo Biset
 * E-Mail:         billybiset AT gmail.com
 *
 */

#ifndef COMMON_HPP
#define COMMON_HPP

#include <stdlib.h>
#include <string>

#define MILI_NAMESPACE
#include "mili/mili.h"

typedef std::string Message;

/**
 * ID of a connected Client.
 * Should be unique for each connected client thoroughout the programs lifetime.
 *
 * \sa ClientProxy
 */
typedef size_t       ClientID;

/**
 * Size of a JobUnit, meaning is user defined. Generally it will be
 * proportional to the amount of bytes it occupies.
 *
 * \sa JobUnit
 */
typedef size_t       MessageSize;

/**
 * Size of header for a message packet. For now it's just twice the length
 * of a single number, since the header consists of id + size.
 */
const MessageSize HEADER_LENGTH = sizeof(MessageSize);

/** Possible responses from clients. */
enum ResponseCode
{
    Ok,
    Error
};

/**
 * Size of header for a response packet. Just the length
 * of a single number, since the header consists of a ResponseCode.
 */
const MessageSize RESPONSE_HEADER_LENGTH = sizeof(ResponseCode);

/** A Port type. */
typedef size_t Port;

/** A message you take data from. */
typedef mili::bistream InputMessage;

/** A message you put data into. */
typedef mili::bostream OutputMessage;

#endif