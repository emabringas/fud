/**
 *  @file:      combeng.h
 *  @details    Main header file.\n
 *              System: CombEng \n
 *              Language: C++\n
 *
 *  @author     Favio Bettiol
 *  @email      favio.bettiol AT gmail.com
 *
 *  @author     Diego Diaz
 *  @email      diazdiego86 AT gmail.com
 *
 *  @date       August 2010
 *  @version    0.1
 *
 * This file is part of CombEng
 *
 * CombEng : Combinatory Engine, an FuD's abstraction layer for problems that
 * require to combine elements. Also, this layer provides ranking and prune
 * features for these combinations.
 * <http://fud.googlecode.com/>
 *
 * Copyright (C) 2010 - Favio Bettiol and Diego Diaz
 *
 * CombEng is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * CombEng is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with CombEng .  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef COMBENG_H
#define COMBENG_H
/* client */
#include ".private/client/l5_application_client.h"

/* common */
#include ".private/common/l4_node.h"
#include ".private/common/prune_policy.h"
#include ".private/common/combination_policy.h"
#include ".private/common/combination_observer.h"
#include ".private/common/state_set.h"

/*libplugin */
#include ".private/libplugin/composed_combination_policy_parallel.h"
#include ".private/libplugin/composed_combination_policy_sequencial.h"
#include ".private/libplugin/list_combination_policy.h"
#include ".private/libplugin/newtonian_combination_policy.h"
#include ".private/libplugin/observer_aux.h"

/*server */
#include ".private/server/l5_application_server.h"

#endif
