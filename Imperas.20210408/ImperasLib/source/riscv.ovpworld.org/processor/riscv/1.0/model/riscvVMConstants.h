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

//
// This is the minimum page shift
//
#define RISCV_PAGE_SHIFT 12

//
// This is the minimum page size
//
#define RISCV_PAGE_SIZE (1<<RISCV_PAGE_SHIFT)

//
// These define virtual memory mode settings
//
#define RISCV_VMM_BARE  (1<<0)
#define RISCV_VMM_SV32  (1<<1)
#define RISCV_VMM_SV39  (1<<8)
#define RISCV_VMM_SV48  (1<<9)

//
// These define composite virtual memory mode settings
//
#define RISCV_VMM_32    (RISCV_VMM_BARE|RISCV_VMM_SV32)
#define RISCV_VMM_64    (RISCV_VMM_BARE|RISCV_VMM_SV39|RISCV_VMM_SV48)


