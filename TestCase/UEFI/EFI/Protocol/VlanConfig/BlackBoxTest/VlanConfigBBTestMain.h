/*++
  The material contained herein is not a license, either        
  expressly or impliedly, to any intellectual property owned    
  or controlled by any of the authors or developers of this     
  material or to any contribution thereto. The material         
  contained herein is provided on an "AS IS" basis and, to the  
  maximum extent permitted by applicable law, this information  
  is provided AS IS AND WITH ALL FAULTS, and the authors and    
  developers of this material hereby disclaim all other         
  warranties and conditions, either express, implied or         
  statutory, including, but not limited to, any (if any)        
  implied warranties, duties or conditions of merchantability,  
  of fitness for a particular purpose, of accuracy or           
  completeness of responses, of results, of workmanlike         
  effort, of lack of viruses and of lack of negligence, all     
  with regard to this material and any contribution thereto.    
  Designers must not rely on the absence or characteristics of  
  any features or instructions marked "reserved" or             
  "undefined." The Unified EFI Forum, Inc. reserves any         
  features or instructions so marked for future definition and  
  shall have no responsibility whatsoever for conflicts or      
  incompatibilities arising from future changes to them. ALSO,  
  THERE IS NO WARRANTY OR CONDITION OF TITLE, QUIET ENJOYMENT,  
  QUIET POSSESSION, CORRESPONDENCE TO DESCRIPTION OR            
  NON-INFRINGEMENT WITH REGARD TO THE TEST SUITE AND ANY        
  CONTRIBUTION THERETO.                                         
                                                                
  IN NO EVENT WILL ANY AUTHOR OR DEVELOPER OF THIS MATERIAL OR  
  ANY CONTRIBUTION THERETO BE LIABLE TO ANY OTHER PARTY FOR     
  THE COST OF PROCURING SUBSTITUTE GOODS OR SERVICES, LOST      
  PROFITS, LOSS OF USE, LOSS OF DATA, OR ANY INCIDENTAL,        
  CONSEQUENTIAL, DIRECT, INDIRECT, OR SPECIAL DAMAGES WHETHER   
  UNDER CONTRACT, TORT, WARRANTY, OR OTHERWISE, ARISING IN ANY  
  WAY OUT OF THIS OR ANY OTHER AGREEMENT RELATING TO THIS       
  DOCUMENT, WHETHER OR NOT SUCH PARTY HAD ADVANCE NOTICE OF     
  THE POSSIBILITY OF SUCH DAMAGES.                              
                                                                
  Copyright 2006, 2007, 2008, 2009, 2010 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  VlanConfigBBTestMain.h

Abstract:

  Test Driver of Vlan Config Protocol header file

--*/

#ifndef _VLAN_CONFIG_BB_TEST_MAIN
#define _VLAN_CONFIG_BB_TEST_MAIN

#include "Efi.h"
#include "EfiTestLib.h"
#include "VlanConfigProtocol.h"
#include "Guid.h"


#define EFI_VLAN_CONFIG_PROTOCOL_TEST_REVISION    0x00010000


//
// Entry GUIDs for Func Test
//
#define EFI_VLAN_CONFIG_PROTOCOL_TEST_ENTRY_GUID0101 \
{ 0xe7bbe8f0, 0x22c6, 0x4e6d, { 0x92, 0xb7, 0xf0, 0xc2, 0xab, 0x2c, 0xd4, 0xde } }

#define EFI_VLAN_CONFIG_PROTOCOL_TEST_ENTRY_GUID0102 \
{ 0x8c9f551e, 0xe931, 0x45dc, { 0x87, 0xdb, 0xd7, 0x78, 0xfa, 0x08, 0x44, 0x66 } }

#define EFI_VLAN_CONFIG_PROTOCOL_TEST_ENTRY_GUID0103 \
{ 0xa4d0f821, 0xaa43, 0x4764, { 0xb2, 0x10, 0x37, 0xb7, 0x8b, 0xea, 0x31, 0x11 } }


//
// Entry GUIDs for Conf Test
//
#define EFI_VLAN_CONFIG_PROTOCOL_TEST_ENTRY_GUID0201 \
{ 0xab5d2897, 0x915b, 0x4339, { 0x9c, 0x43, 0x45, 0xb5, 0x07, 0x61, 0x61, 0xc9 } }

#define EFI_VLAN_CONFIG_PROTOCOL_TEST_ENTRY_GUID0202 \
{ 0x3155723f, 0xc0c0, 0x4a94, { 0x81, 0x94, 0x52, 0x67, 0xb1, 0x75, 0x57, 0xc1 } }

#define EFI_VLAN_CONFIG_PROTOCOL_TEST_ENTRY_GUID0203 \
{ 0x8c7bcbdc, 0x06a8, 0x416c, { 0x92, 0x42, 0x21, 0x58, 0x50, 0x59, 0xd2, 0x1b } }


//
// Get a valid VlanId
//
EFI_STATUS
GetAValidVlanId (
  EFI_VLAN_CONFIG_PROTOCOL                   *VlanConfig,
  UINT16                                     *VlanId
  );

//
// Get a Invalid VlanId
//
EFI_STATUS
GetAnInvalidVlanId (
  EFI_VLAN_CONFIG_PROTOCOL                   *VlanConfig,
  UINT16                                     *VlanId
  );

//
//
//
EFI_STATUS
InitializeVlanConfigBBTest (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
  );
  
EFI_STATUS
UnloadVlanConfigBBTest (
  IN EFI_HANDLE                   ImageHandle
  );
  
  
//
//Test Cases
//
EFI_STATUS
BBTestSetConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
BBTestFindConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
BBTestRemoveConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

  
EFI_STATUS
BBTestSetFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestFindFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
BBTestRemoveFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );


VOID
InitializeLib (
  IN EFI_HANDLE                     ImageHandle,
  IN EFI_SYSTEM_TABLE               *SystemTable
  );

#endif
