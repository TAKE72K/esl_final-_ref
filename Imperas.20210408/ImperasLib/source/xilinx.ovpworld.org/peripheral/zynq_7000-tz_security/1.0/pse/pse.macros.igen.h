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

#ifndef PSE_MACROS_IGEN_H
#define PSE_MACROS_IGEN_H               

// Before including this file in the application, define the indicated macros
// to fix the base address of each slave port.

// Set the macro 'BPORT1' to the base of port 'bport1'
#ifndef BPORT1
#error BPORT1 is undefined. It needs to be set to the port base address
#endif


#define BPORT1_AB_POFFSET               0x0
#define BPORT1_AB_SECURITY2_SDIO0_POFFSET  0x8
#define BPORT1_AB_SECURITY2_SDIO0       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SECURITY2_SDIO0_POFFSET)

#define BPORT1_AB_SECURITY3_SDIO1_POFFSET  0xc
#define BPORT1_AB_SECURITY3_SDIO1       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SECURITY3_SDIO1_POFFSET)

#define BPORT1_AB_SECURITY4_QSPI_POFFSET  0x10
#define BPORT1_AB_SECURITY4_QSPI        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SECURITY4_QSPI_POFFSET)

#define BPORT1_AB_SECURITY6_APB_SLAVES_POFFSET  0x18
#define BPORT1_AB_SECURITY6_APB_SLAVES  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SECURITY6_APB_SLAVES_POFFSET)

#define BPORT1_AB_SECURITY7_SMC_POFFSET  0x1c
#define BPORT1_AB_SECURITY7_SMC         (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SECURITY7_SMC_POFFSET)

#define BPORT1_AB_BUFFER_POFFSET        0x0
#define BPORT1_AB_BUFFER                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_BUFFER_POFFSET)
#define BPORT1_AB_BUFFER_BYTES          0x20


#endif
