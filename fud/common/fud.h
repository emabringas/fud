/**
 * @file fud.h
 * @brief Main include file for application developers that use FuD.
 *
 */

/**
 * @mainpage FuD. FuDePAN Ubiquitous Distribution
 *
 * @authors Guillermo Biset, Daniel Gutson
 *
 * @section intro Introduction
 *
 * FuD is a framework for work distribution, it allows programmers to implement
 * distributed applications regardless of the problem domain or specific
 * communication middlewares that are available for such a purpose.
 *
 * Header files that are not meant for external access reside in the src
 * directory. Source files are located in the src directory.
 *
 * Note the existence of the following directories:
 * - apps : Contains example applications that use FuD
 * - doc : Contains all FuD documention and some additional information
 *
 *
 * This project is part of
 * <A HREF="http://www.fudepan.org.ar"> FuDePAN </A>
 *
 *
 * The projects' webpage is located at
 * <A HREF="http://fud.googlecode.com"> GoogleCode </A>
 *
 * <hr>
 * @section notes release.notes
 * release.notes
 * <hr>
 * @section requirements requirements
 * To compile FuD, you need:
 * - GetOpt
 * - MiLi
 * - Boost libraries
 *
 * <hr>
 * @todo Many ...
 * @todo ... many things
 *
 */

#include "common.h"
#include "distributable_job.h"
#include "job_unit.h"

namespace fud
{
    void finish();
}

