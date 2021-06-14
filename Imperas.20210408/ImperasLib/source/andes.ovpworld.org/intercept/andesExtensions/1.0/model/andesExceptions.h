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

#pragma once

// Imperas header files
#include "hostapi/impTypes.h"

// model header files
#include "riscvExceptionTypes.h"
#include "riscvTypeRefs.h"

//
// This is the index of the PMOVI interrupt
//
#define ANDES_PMOVI_INT 18

//
// This enumerates Andes-specific exceptions and interrupts
//
typedef enum andesExceptionE {
    andes_E_HSP_OVF = 32,
    andes_E_HSP_UDF = 33,
    andes_I_PMOVI   = ANDES_PMOVI_INT | riscv_E_Interrupt,
} andesException;

//
// Value subtracted from exception code above to map to vacant region of base
// exception table (entries 16-31)
//
#define ANDES_ECODE_OFFSET 16

//
// Check for pending interrupts
//
void andesTestInterrupt(riscvP riscv);

//
// Take Illegal Instruction exception
//
void andesIllegalInstruction(riscvP riscv);

//
// Take custom exception
//
void andesTakeException(riscvP riscv, andesException exception, Uns64 tval);

