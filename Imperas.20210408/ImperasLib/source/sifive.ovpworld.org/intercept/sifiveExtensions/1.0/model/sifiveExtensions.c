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

// standard header files
#include <string.h>

// Imperas header files
#include "hostapi/impAlloc.h"

// VMI area includes
#include "vmi/vmiOSAttrs.h"
#include "vmi/vmiMessage.h"

// base model header files
#include "riscvConfig.h"
#include "riscvStructure.h"

// model header files
#include "sifiveConfig.h"
#include "sifiveCSR.h"
#include "sifiveDoc.h"
#include "sifiveFunctions.h"
#include "sifiveMessage.h"
#include "sifiveMorph.h"
#include "sifiveStructure.h"
#include "sifiveUtils.h"


////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTOR AND DESTRUCTOR
////////////////////////////////////////////////////////////////////////////////

//
// Constructor
//
static VMIOS_CONSTRUCTOR_FN(constructor) {

    riscvP       riscv  = (riscvP)processor;

    // save processor on object for later use
    object->riscv = riscv;

    // prepare client data
    object->extCB.clientData = object;

    // initialize CSR state
    sifiveCSRInit(object);

    // register extension with base model
    riscv->cb.registerExtCB(riscv, &object->extCB, SIFIVE_OVP_CONFIG_ID);

}

//
// Destructor
//
static VMIOS_DESTRUCTOR_FN(destructor) {
}


////////////////////////////////////////////////////////////////////////////////
// INTERCEPT ATTRIBUTES
////////////////////////////////////////////////////////////////////////////////

vmiosAttr modelAttrs = {

    ////////////////////////////////////////////////////////////////////////
    // VERSION
    ////////////////////////////////////////////////////////////////////////

    .versionString  = VMI_VERSION,                // version string
    .modelType      = VMI_INTERCEPT_LIBRARY,      // type
    .packageName    = "sifiveExtensions",          // name
    .objectSize     = sizeof(vmiosObject),        // size in bytes of OSS object

    ////////////////////////////////////////////////////////////////////////
    // VLNV INFO
    ////////////////////////////////////////////////////////////////////////

    .vlnv = {
        .vendor  = "sifive.ovpworld.org",
        .library = "intercept",
        .name    = "sifiveExtensions",
        .version = "1.0"
    },

    ////////////////////////////////////////////////////////////////////////
    // CONSTRUCTOR/DESTRUCTOR ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .constructorCB  = constructor,          // object constructor
    .destructorCB   = destructor,           // object destructor
    .docCB          = sifiveDoc,            // doc constructor

    ////////////////////////////////////////////////////////////////////////
    // INSTRUCTION INTERCEPT ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .morphCB = sifiveMorph,                  // morph override callback
    .disCB   = sifiveDisassemble,            // disassemble instruction

    ////////////////////////////////////////////////////////////////////////
    // ADDRESS INTERCEPT DEFINITIONS
    ////////////////////////////////////////////////////////////////////////

    .intercepts = {
        {0}
    }
};
