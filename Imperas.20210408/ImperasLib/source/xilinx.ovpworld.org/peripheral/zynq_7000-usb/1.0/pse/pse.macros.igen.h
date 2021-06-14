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
#define BPORT1_AB_ID_POFFSET            0x0
#define BPORT1_AB_ID                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ID_POFFSET)

#define BPORT1_AB_HWGENERAL_POFFSET     0x4
#define BPORT1_AB_HWGENERAL             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_HWGENERAL_POFFSET)

#define BPORT1_AB_HWHOST_POFFSET        0x8
#define BPORT1_AB_HWHOST                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_HWHOST_POFFSET)

#define BPORT1_AB_HWDEVICE_POFFSET      0xc
#define BPORT1_AB_HWDEVICE              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_HWDEVICE_POFFSET)

#define BPORT1_AB_HWTXBUF_POFFSET       0x10
#define BPORT1_AB_HWTXBUF               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_HWTXBUF_POFFSET)

#define BPORT1_AB_HWRXBUF_POFFSET       0x14
#define BPORT1_AB_HWRXBUF               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_HWRXBUF_POFFSET)

#define BPORT1_AB_GPTIMER0LD_POFFSET    0x80
#define BPORT1_AB_GPTIMER0LD            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_GPTIMER0LD_POFFSET)

#define BPORT1_AB_GPTIMER0CTRL_POFFSET  0x84
#define BPORT1_AB_GPTIMER0CTRL          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_GPTIMER0CTRL_POFFSET)

#define BPORT1_AB_GPTIMER1LD_POFFSET    0x88
#define BPORT1_AB_GPTIMER1LD            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_GPTIMER1LD_POFFSET)

#define BPORT1_AB_GPTIMER1CTRL_POFFSET  0x8c
#define BPORT1_AB_GPTIMER1CTRL          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_GPTIMER1CTRL_POFFSET)

#define BPORT1_AB_SBUSCFG_POFFSET       0x90
#define BPORT1_AB_SBUSCFG               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SBUSCFG_POFFSET)

#define BPORT1_AB_CAPLENGTH_HCIVERSION_POFFSET  0x100
#define BPORT1_AB_CAPLENGTH_HCIVERSION  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CAPLENGTH_HCIVERSION_POFFSET)

#define BPORT1_AB_HCSPARAMS_POFFSET     0x104
#define BPORT1_AB_HCSPARAMS             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_HCSPARAMS_POFFSET)

#define BPORT1_AB_HCCPARAMS_POFFSET     0x108
#define BPORT1_AB_HCCPARAMS             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_HCCPARAMS_POFFSET)

#define BPORT1_AB_DCIVERSION_POFFSET    0x120
#define BPORT1_AB_DCIVERSION            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DCIVERSION_POFFSET)

#define BPORT1_AB_DCCPARAMS_POFFSET     0x124
#define BPORT1_AB_DCCPARAMS             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DCCPARAMS_POFFSET)

#define BPORT1_AB_USBCMD_POFFSET        0x140
#define BPORT1_AB_USBCMD                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_USBCMD_POFFSET)

#define BPORT1_AB_USBSTS_POFFSET        0x144
#define BPORT1_AB_USBSTS                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_USBSTS_POFFSET)

#define BPORT1_AB_USBINTR_POFFSET       0x148
#define BPORT1_AB_USBINTR               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_USBINTR_POFFSET)

#define BPORT1_AB_FRINDEX_POFFSET       0x14c
#define BPORT1_AB_FRINDEX               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FRINDEX_POFFSET)

#define BPORT1_AB_PERIODICLISTBASE_DEVICEADDR_POFFSET  0x154
#define BPORT1_AB_PERIODICLISTBASE_DEVICEADDR  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PERIODICLISTBASE_DEVICEADDR_POFFSET)

#define BPORT1_AB_ASYNCLISTADDR_ENDPOINTLISTADDR_POFFSET  0x158
#define BPORT1_AB_ASYNCLISTADDR_ENDPOINTLISTADDR  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ASYNCLISTADDR_ENDPOINTLISTADDR_POFFSET)

#define BPORT1_AB_TTCTRL_POFFSET        0x15c
#define BPORT1_AB_TTCTRL                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TTCTRL_POFFSET)

#define BPORT1_AB_BURSTSIZE_POFFSET     0x160
#define BPORT1_AB_BURSTSIZE             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_BURSTSIZE_POFFSET)

#define BPORT1_AB_TXFILLTUNING_POFFSET  0x164
#define BPORT1_AB_TXFILLTUNING          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TXFILLTUNING_POFFSET)

#define BPORT1_AB_TXTTFILLTUNING_POFFSET  0x168
#define BPORT1_AB_TXTTFILLTUNING        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TXTTFILLTUNING_POFFSET)

#define BPORT1_AB_IC_USB_POFFSET        0x16c
#define BPORT1_AB_IC_USB                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_IC_USB_POFFSET)

#define BPORT1_AB_ULPI_VIEWPORT_POFFSET  0x170
#define BPORT1_AB_ULPI_VIEWPORT         (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ULPI_VIEWPORT_POFFSET)

#define BPORT1_AB_ENDPTNAK_POFFSET      0x178
#define BPORT1_AB_ENDPTNAK              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ENDPTNAK_POFFSET)

#define BPORT1_AB_ENDPTNAKEN_POFFSET    0x17c
#define BPORT1_AB_ENDPTNAKEN            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ENDPTNAKEN_POFFSET)

#define BPORT1_AB_CONFIGFLAG_POFFSET    0x180
#define BPORT1_AB_CONFIGFLAG            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CONFIGFLAG_POFFSET)

#define BPORT1_AB_PORTSC1_POFFSET       0x184
#define BPORT1_AB_PORTSC1               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PORTSC1_POFFSET)

#define BPORT1_AB_OTGSC_POFFSET         0x1a4
#define BPORT1_AB_OTGSC                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_OTGSC_POFFSET)

#define BPORT1_AB_USBMODE_POFFSET       0x1a8
#define BPORT1_AB_USBMODE               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_USBMODE_POFFSET)

#define BPORT1_AB_ENDPTSETUPSTAT_POFFSET  0x1ac
#define BPORT1_AB_ENDPTSETUPSTAT        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ENDPTSETUPSTAT_POFFSET)

#define BPORT1_AB_ENDPTPRIME_POFFSET    0x1b0
#define BPORT1_AB_ENDPTPRIME            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ENDPTPRIME_POFFSET)

#define BPORT1_AB_ENDPTFLUSH_POFFSET    0x1b4
#define BPORT1_AB_ENDPTFLUSH            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ENDPTFLUSH_POFFSET)

#define BPORT1_AB_ENDPTSTAT_POFFSET     0x1b8
#define BPORT1_AB_ENDPTSTAT             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ENDPTSTAT_POFFSET)

#define BPORT1_AB_ENDPTCOMPLETE_POFFSET  0x1bc
#define BPORT1_AB_ENDPTCOMPLETE         (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ENDPTCOMPLETE_POFFSET)

#define BPORT1_AB_ENDPTCTRL0_POFFSET    0x1c0
#define BPORT1_AB_ENDPTCTRL0            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ENDPTCTRL0_POFFSET)

#define BPORT1_AB_ENDPTCTRL1_POFFSET    0x1c4
#define BPORT1_AB_ENDPTCTRL1            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ENDPTCTRL1_POFFSET)

#define BPORT1_AB_ENDPTCTRL2_POFFSET    0x1c8
#define BPORT1_AB_ENDPTCTRL2            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ENDPTCTRL2_POFFSET)

#define BPORT1_AB_ENDPTCTRL3_POFFSET    0x1cc
#define BPORT1_AB_ENDPTCTRL3            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ENDPTCTRL3_POFFSET)

#define BPORT1_AB_ENDPTCTRL4_POFFSET    0x1d0
#define BPORT1_AB_ENDPTCTRL4            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ENDPTCTRL4_POFFSET)

#define BPORT1_AB_ENDPTCTRL5_POFFSET    0x1d4
#define BPORT1_AB_ENDPTCTRL5            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ENDPTCTRL5_POFFSET)

#define BPORT1_AB_ENDPTCTRL6_POFFSET    0x1d8
#define BPORT1_AB_ENDPTCTRL6            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ENDPTCTRL6_POFFSET)

#define BPORT1_AB_ENDPTCTRL7_POFFSET    0x1dc
#define BPORT1_AB_ENDPTCTRL7            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ENDPTCTRL7_POFFSET)

#define BPORT1_AB_ENDPTCTRL8_POFFSET    0x1e0
#define BPORT1_AB_ENDPTCTRL8            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ENDPTCTRL8_POFFSET)

#define BPORT1_AB_ENDPTCTRL9_POFFSET    0x1e4
#define BPORT1_AB_ENDPTCTRL9            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ENDPTCTRL9_POFFSET)

#define BPORT1_AB_ENDPTCTRL10_POFFSET   0x1e8
#define BPORT1_AB_ENDPTCTRL10           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ENDPTCTRL10_POFFSET)

#define BPORT1_AB_ENDPTCTRL11_POFFSET   0x1ec
#define BPORT1_AB_ENDPTCTRL11           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ENDPTCTRL11_POFFSET)

#define BPORT1_AB_BUFFER_POFFSET        0x0
#define BPORT1_AB_BUFFER                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_BUFFER_POFFSET)
#define BPORT1_AB_BUFFER_BYTES          0x1000


#endif