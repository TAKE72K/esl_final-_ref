/*
 * Copyright (c) 2005-2021 Imperas Software Ltd., www.imperas.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied.
 *
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */


////////////////////////////////////////////////////////////////////////////////
//
//                W R I T T E N   B Y   I M P E R A S   I G E N
//
//                             Version 20210408.0
//
////////////////////////////////////////////////////////////////////////////////


#ifdef _PSE_
#    include "peripheral/impTypes.h"
#    include "peripheral/bhm.h"
#    include "peripheral/bhmHttp.h"
#    include "peripheral/ppm.h"
#else
#    include "hostapi/impTypes.h"
#endif

#include "pse.igen.h"

static ppmBusPort busPorts[] = {
    {
        .name            = "bport1",
        .type            = PPM_SLAVE_PORT,
        .addrHi          = 0x25f,
        .mustBeConnected = 1,
        .remappable      = 0,
        .description     = 0,
    },
    { 0 }
};

static PPM_BUS_PORT_FN(nextBusPort) {
    if(!busPort) {
        busPort = busPorts;
    } else {
        busPort++;
    }
    return busPort->name ? busPort : 0;
}

static ppmNetPort netPorts[] = {
    {
        .name            = "irq32",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq32,
        .netCB           = interruptIn,
        .userData        = (void*)32,
    },
    {
        .name            = "irq33",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq33,
        .netCB           = interruptIn,
        .userData        = (void*)33,
    },
    {
        .name            = "irq34",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq34,
        .netCB           = interruptIn,
        .userData        = (void*)34,
    },
    {
        .name            = "irq35",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq35,
        .netCB           = interruptIn,
        .userData        = (void*)35,
    },
    {
        .name            = "irq36",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq36,
        .netCB           = interruptIn,
        .userData        = (void*)36,
    },
    {
        .name            = "irq37",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq37,
        .netCB           = interruptIn,
        .userData        = (void*)37,
    },
    {
        .name            = "irq38",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq38,
        .netCB           = interruptIn,
        .userData        = (void*)38,
    },
    {
        .name            = "irq39",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq39,
        .netCB           = interruptIn,
        .userData        = (void*)39,
    },
    {
        .name            = "irq40",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq40,
        .netCB           = interruptIn,
        .userData        = (void*)40,
    },
    {
        .name            = "irq41",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq41,
        .netCB           = interruptIn,
        .userData        = (void*)41,
    },
    {
        .name            = "irq42",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq42,
        .netCB           = interruptIn,
        .userData        = (void*)42,
    },
    {
        .name            = "irq43",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq43,
        .netCB           = interruptIn,
        .userData        = (void*)43,
    },
    {
        .name            = "irq44",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq44,
        .netCB           = interruptIn,
        .userData        = (void*)44,
    },
    {
        .name            = "irq45",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq45,
        .netCB           = interruptIn,
        .userData        = (void*)45,
    },
    {
        .name            = "irq46",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq46,
        .netCB           = interruptIn,
        .userData        = (void*)46,
    },
    {
        .name            = "irq47",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq47,
        .netCB           = interruptIn,
        .userData        = (void*)47,
    },
    {
        .name            = "irq48",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq48,
        .netCB           = interruptIn,
        .userData        = (void*)48,
    },
    {
        .name            = "irq49",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq49,
        .netCB           = interruptIn,
        .userData        = (void*)49,
    },
    {
        .name            = "irq50",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq50,
        .netCB           = interruptIn,
        .userData        = (void*)50,
    },
    {
        .name            = "irq51",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq51,
        .netCB           = interruptIn,
        .userData        = (void*)51,
    },
    {
        .name            = "irq52",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq52,
        .netCB           = interruptIn,
        .userData        = (void*)52,
    },
    {
        .name            = "irq53",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq53,
        .netCB           = interruptIn,
        .userData        = (void*)53,
    },
    {
        .name            = "irq54",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq54,
        .netCB           = interruptIn,
        .userData        = (void*)54,
    },
    {
        .name            = "irq55",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq55,
        .netCB           = interruptIn,
        .userData        = (void*)55,
    },
    {
        .name            = "irq56",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq56,
        .netCB           = interruptIn,
        .userData        = (void*)56,
    },
    {
        .name            = "irq57",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq57,
        .netCB           = interruptIn,
        .userData        = (void*)57,
    },
    {
        .name            = "irq58",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq58,
        .netCB           = interruptIn,
        .userData        = (void*)58,
    },
    {
        .name            = "irq59",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq59,
        .netCB           = interruptIn,
        .userData        = (void*)59,
    },
    {
        .name            = "irq60",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq60,
        .netCB           = interruptIn,
        .userData        = (void*)60,
    },
    {
        .name            = "irq61",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq61,
        .netCB           = interruptIn,
        .userData        = (void*)61,
    },
    {
        .name            = "irq62",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq62,
        .netCB           = interruptIn,
        .userData        = (void*)62,
    },
    {
        .name            = "irq63",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq63,
        .netCB           = interruptIn,
        .userData        = (void*)63,
    },
    {
        .name            = "irq64",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq64,
        .netCB           = interruptIn,
        .userData        = (void*)64,
    },
    {
        .name            = "irq65",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq65,
        .netCB           = interruptIn,
        .userData        = (void*)65,
    },
    {
        .name            = "irq66",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq66,
        .netCB           = interruptIn,
        .userData        = (void*)66,
    },
    {
        .name            = "irq67",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq67,
        .netCB           = interruptIn,
        .userData        = (void*)67,
    },
    {
        .name            = "irq68",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq68,
        .netCB           = interruptIn,
        .userData        = (void*)68,
    },
    {
        .name            = "irq69",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq69,
        .netCB           = interruptIn,
        .userData        = (void*)69,
    },
    {
        .name            = "irq70",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq70,
        .netCB           = interruptIn,
        .userData        = (void*)70,
    },
    {
        .name            = "irq71",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq71,
        .netCB           = interruptIn,
        .userData        = (void*)71,
    },
    {
        .name            = "irq72",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq72,
        .netCB           = interruptIn,
        .userData        = (void*)72,
    },
    {
        .name            = "irq73",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq73,
        .netCB           = interruptIn,
        .userData        = (void*)73,
    },
    {
        .name            = "irq74",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq74,
        .netCB           = interruptIn,
        .userData        = (void*)74,
    },
    {
        .name            = "irq75",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq75,
        .netCB           = interruptIn,
        .userData        = (void*)75,
    },
    {
        .name            = "irq76",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq76,
        .netCB           = interruptIn,
        .userData        = (void*)76,
    },
    {
        .name            = "irq77",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq77,
        .netCB           = interruptIn,
        .userData        = (void*)77,
    },
    {
        .name            = "irq78",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq78,
        .netCB           = interruptIn,
        .userData        = (void*)78,
    },
    {
        .name            = "irq79",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq79,
        .netCB           = interruptIn,
        .userData        = (void*)79,
    },
    {
        .name            = "irq80",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq80,
        .netCB           = interruptIn,
        .userData        = (void*)80,
    },
    {
        .name            = "irq81",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq81,
        .netCB           = interruptIn,
        .userData        = (void*)81,
    },
    {
        .name            = "irq82",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq82,
        .netCB           = interruptIn,
        .userData        = (void*)82,
    },
    {
        .name            = "irq83",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq83,
        .netCB           = interruptIn,
        .userData        = (void*)83,
    },
    {
        .name            = "irq84",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq84,
        .netCB           = interruptIn,
        .userData        = (void*)84,
    },
    {
        .name            = "irq85",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq85,
        .netCB           = interruptIn,
        .userData        = (void*)85,
    },
    {
        .name            = "irq86",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq86,
        .netCB           = interruptIn,
        .userData        = (void*)86,
    },
    {
        .name            = "irq87",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq87,
        .netCB           = interruptIn,
        .userData        = (void*)87,
    },
    {
        .name            = "irq88",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq88,
        .netCB           = interruptIn,
        .userData        = (void*)88,
    },
    {
        .name            = "irq89",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq89,
        .netCB           = interruptIn,
        .userData        = (void*)89,
    },
    {
        .name            = "irq90",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq90,
        .netCB           = interruptIn,
        .userData        = (void*)90,
    },
    {
        .name            = "irq91",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq91,
        .netCB           = interruptIn,
        .userData        = (void*)91,
    },
    {
        .name            = "irq92",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq92,
        .netCB           = interruptIn,
        .userData        = (void*)92,
    },
    {
        .name            = "irq93",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq93,
        .netCB           = interruptIn,
        .userData        = (void*)93,
    },
    {
        .name            = "irq94",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq94,
        .netCB           = interruptIn,
        .userData        = (void*)94,
    },
    {
        .name            = "irq95",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq95,
        .netCB           = interruptIn,
        .userData        = (void*)95,
    },
    {
        .name            = "irq96",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq96,
        .netCB           = interruptIn,
        .userData        = (void*)96,
    },
    {
        .name            = "irq97",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq97,
        .netCB           = interruptIn,
        .userData        = (void*)97,
    },
    {
        .name            = "irq98",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq98,
        .netCB           = interruptIn,
        .userData        = (void*)98,
    },
    {
        .name            = "irq99",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq99,
        .netCB           = interruptIn,
        .userData        = (void*)99,
    },
    {
        .name            = "irq100",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq100,
        .netCB           = interruptIn,
        .userData        = (void*)100,
    },
    {
        .name            = "irq101",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq101,
        .netCB           = interruptIn,
        .userData        = (void*)101,
    },
    {
        .name            = "irq102",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq102,
        .netCB           = interruptIn,
        .userData        = (void*)102,
    },
    {
        .name            = "irq103",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq103,
        .netCB           = interruptIn,
        .userData        = (void*)103,
    },
    {
        .name            = "irq104",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq104,
        .netCB           = interruptIn,
        .userData        = (void*)104,
    },
    {
        .name            = "irq105",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq105,
        .netCB           = interruptIn,
        .userData        = (void*)105,
    },
    {
        .name            = "irq106",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq106,
        .netCB           = interruptIn,
        .userData        = (void*)106,
    },
    {
        .name            = "irq107",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq107,
        .netCB           = interruptIn,
        .userData        = (void*)107,
    },
    {
        .name            = "irq108",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq108,
        .netCB           = interruptIn,
        .userData        = (void*)108,
    },
    {
        .name            = "irq109",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq109,
        .netCB           = interruptIn,
        .userData        = (void*)109,
    },
    {
        .name            = "irq110",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq110,
        .netCB           = interruptIn,
        .userData        = (void*)110,
    },
    {
        .name            = "irq111",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq111,
        .netCB           = interruptIn,
        .userData        = (void*)111,
    },
    {
        .name            = "irq112",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq112,
        .netCB           = interruptIn,
        .userData        = (void*)112,
    },
    {
        .name            = "irq113",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq113,
        .netCB           = interruptIn,
        .userData        = (void*)113,
    },
    {
        .name            = "irq114",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq114,
        .netCB           = interruptIn,
        .userData        = (void*)114,
    },
    {
        .name            = "irq115",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq115,
        .netCB           = interruptIn,
        .userData        = (void*)115,
    },
    {
        .name            = "irq116",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq116,
        .netCB           = interruptIn,
        .userData        = (void*)116,
    },
    {
        .name            = "irq117",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq117,
        .netCB           = interruptIn,
        .userData        = (void*)117,
    },
    {
        .name            = "irq118",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq118,
        .netCB           = interruptIn,
        .userData        = (void*)118,
    },
    {
        .name            = "irq119",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq119,
        .netCB           = interruptIn,
        .userData        = (void*)119,
    },
    {
        .name            = "irq120",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq120,
        .netCB           = interruptIn,
        .userData        = (void*)120,
    },
    {
        .name            = "irq121",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq121,
        .netCB           = interruptIn,
        .userData        = (void*)121,
    },
    {
        .name            = "irq122",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq122,
        .netCB           = interruptIn,
        .userData        = (void*)122,
    },
    {
        .name            = "irq123",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq123,
        .netCB           = interruptIn,
        .userData        = (void*)123,
    },
    {
        .name            = "irq124",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq124,
        .netCB           = interruptIn,
        .userData        = (void*)124,
    },
    {
        .name            = "irq125",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq125,
        .netCB           = interruptIn,
        .userData        = (void*)125,
    },
    {
        .name            = "irq126",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq126,
        .netCB           = interruptIn,
        .userData        = (void*)126,
    },
    {
        .name            = "irq127",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq127,
        .netCB           = interruptIn,
        .userData        = (void*)127,
    },
    {
        .name            = "irq128",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq128,
        .netCB           = interruptIn,
        .userData        = (void*)128,
    },
    {
        .name            = "irq129",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq129,
        .netCB           = interruptIn,
        .userData        = (void*)129,
    },
    {
        .name            = "irq130",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq130,
        .netCB           = interruptIn,
        .userData        = (void*)130,
    },
    {
        .name            = "irq131",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq131,
        .netCB           = interruptIn,
        .userData        = (void*)131,
    },
    {
        .name            = "irq132",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq132,
        .netCB           = interruptIn,
        .userData        = (void*)132,
    },
    {
        .name            = "irq133",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq133,
        .netCB           = interruptIn,
        .userData        = (void*)133,
    },
    {
        .name            = "irq134",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq134,
        .netCB           = interruptIn,
        .userData        = (void*)134,
    },
    {
        .name            = "irq135",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq135,
        .netCB           = interruptIn,
        .userData        = (void*)135,
    },
    {
        .name            = "irq136",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq136,
        .netCB           = interruptIn,
        .userData        = (void*)136,
    },
    {
        .name            = "irq137",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq137,
        .netCB           = interruptIn,
        .userData        = (void*)137,
    },
    {
        .name            = "irq138",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq138,
        .netCB           = interruptIn,
        .userData        = (void*)138,
    },
    {
        .name            = "irq139",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq139,
        .netCB           = interruptIn,
        .userData        = (void*)139,
    },
    {
        .name            = "irq140",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq140,
        .netCB           = interruptIn,
        .userData        = (void*)140,
    },
    {
        .name            = "irq141",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq141,
        .netCB           = interruptIn,
        .userData        = (void*)141,
    },
    {
        .name            = "irq142",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq142,
        .netCB           = interruptIn,
        .userData        = (void*)142,
    },
    {
        .name            = "irq143",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq143,
        .netCB           = interruptIn,
        .userData        = (void*)143,
    },
    {
        .name            = "irq144",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq144,
        .netCB           = interruptIn,
        .userData        = (void*)144,
    },
    {
        .name            = "irq145",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq145,
        .netCB           = interruptIn,
        .userData        = (void*)145,
    },
    {
        .name            = "irq146",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq146,
        .netCB           = interruptIn,
        .userData        = (void*)146,
    },
    {
        .name            = "irq147",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq147,
        .netCB           = interruptIn,
        .userData        = (void*)147,
    },
    {
        .name            = "irq148",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq148,
        .netCB           = interruptIn,
        .userData        = (void*)148,
    },
    {
        .name            = "irq149",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq149,
        .netCB           = interruptIn,
        .userData        = (void*)149,
    },
    {
        .name            = "irq150",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq150,
        .netCB           = interruptIn,
        .userData        = (void*)150,
    },
    {
        .name            = "irq151",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq151,
        .netCB           = interruptIn,
        .userData        = (void*)151,
    },
    {
        .name            = "irq152",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq152,
        .netCB           = interruptIn,
        .userData        = (void*)152,
    },
    {
        .name            = "irq153",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq153,
        .netCB           = interruptIn,
        .userData        = (void*)153,
    },
    {
        .name            = "irq154",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq154,
        .netCB           = interruptIn,
        .userData        = (void*)154,
    },
    {
        .name            = "irq155",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq155,
        .netCB           = interruptIn,
        .userData        = (void*)155,
    },
    {
        .name            = "irq156",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq156,
        .netCB           = interruptIn,
        .userData        = (void*)156,
    },
    {
        .name            = "irq157",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq157,
        .netCB           = interruptIn,
        .userData        = (void*)157,
    },
    {
        .name            = "irq158",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq158,
        .netCB           = interruptIn,
        .userData        = (void*)158,
    },
    {
        .name            = "irq159",
        .type            = PPM_INPUT_PORT,
        .mustBeConnected = 0,
        .description     = 0,
        .handlePtr       = &handles.irq159,
        .netCB           = interruptIn,
        .userData        = (void*)159,
    },
    { 0 }
};

static PPM_NET_PORT_FN(nextNetPort) {
    if(!netPort) {
         netPort = netPorts;
    } else {
        netPort++;
    }
    return (netPort && netPort->name) ? netPort : 0;
}

ppmModelAttr modelAttrs = {

    .versionString    = PPM_VERSION_STRING,
    .type             = PPM_MT_PERIPHERAL,

    .busPortsCB       = nextBusPort,  
    .netPortsCB       = nextNetPort,  

    .saveCB        = peripheralSaveState,
    .restoreCB     = peripheralRestoreState,

    .docCB         = installDocs,

    .vlnv          = {
        .vendor  = "nxp.ovpworld.org",
        .library = "peripheral",
        .name    = "iMX6_GPC",
        .version = "1.0"
    },

    .family               = "nxp.ovpworld.org",
    .noRecursiveCallbacks = 1,

    .releaseStatus = PPM_UNSET,
    .visibility     = PPM_VISIBLE,
    .saveRestore    = 0,

};
