/**
 * @file fud.h
 * @brief Main include file for client and server applications using FuD.
 *
 * FuD: FuDePAN Ubiquitous Distribution, a framework for work distribution.
 * <http://fud.googlecode.com/>
 * Copyright (C) 2009 Guillermo Biset, FuDePAN
 *
 * This file is part of the FuD project.
 *
 * Contents:       Main header file for FuD's client and server applications.
 *
 * System:         FuD
 * Homepage:       <http://fud.googlecode.com/>
 * Language:       C++
 *
 *  @author     Lucas Besso     -   E-Mail: lbesso AT gmail.com
 *  @author     Raul Striglio   -   E-Mail: rulitox.s AT gmail.com
 *
 *  @Last Update:
 *      $Id:
 *      $URL: 
 *      $LastChangedBy: 
 *
 *
 * FuD is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * FuD is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with FuD.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifdef _WIN32
    #include "common\fud_client.h"
    #include "common\fud_server.h"
#else
    #include "fud/fud_client.h"
    #include "fud/fud_server.h"
#endif

