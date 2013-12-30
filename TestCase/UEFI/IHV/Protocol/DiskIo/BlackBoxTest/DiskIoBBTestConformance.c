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

  DiskIoBBTestConformance.c

Abstract:

  Consistency Test Cases of Disk I/O Protocol

--*/


#include "DiskIoBBTestMain.h"


/**
 *  Entrypoint for EFI_DISK_IO_PROTOCOL.ReadDisk() Consistency Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.1
//
EFI_STATUS
BBTestReadDiskConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_DISK_IO_PROTOCOL                 *DiskIo;
  EFI_BLOCK_IO_PROTOCOL                *BlockIo;
  EFI_TEST_ASSERTION                   AssertionType;
  UINT32                               MediaId;
  BOOLEAN                              RemovableMedia;
  BOOLEAN                              MediaPresent;
  BOOLEAN                              LogicalPartition;
  BOOLEAN                              ReadOnly;
  BOOLEAN                              WriteCaching;
  UINT32                               BlockSize;
  UINT32                               IoAlign;
  EFI_LBA                              LastBlock;
  UINT64                               LastOffset;
  UINTN                                BufferSize;
  UINT8                                *Buffer;
  UINTN                                Index;
  UINT32                               NewMediaId;
  UINT64                               Offset;
  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;
  CHAR16                               *DevicePathStr;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - Handle standard test library",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  DiskIo = (EFI_DISK_IO_PROTOCOL *)ClientInterface;

  Status = LocateBlockIoFromDiskIo (DiskIo, &BlockIo, StandardLib);
  if (EFI_ERROR(Status)) {
    return EFI_DEVICE_ERROR;
  }

  //
  // Locate Device path of the current DiskIo device
  // and save it into log for investigating
  //
  LocateDevicePathFromDiskIo (DiskIo, &DevicePath, StandardLib);

  DevicePathStr = DevicePathToStr (DevicePath);
  if (DevicePathStr != NULL) {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"\r\nCurrent Device: %s",
                   DevicePathStr
                   );
    gtBS->FreePool (DevicePathStr);
    DevicePathStr = NULL;
  }

  //
  // Initialize variable
  //
  MediaId           = BlockIo->Media->MediaId;
  RemovableMedia    = BlockIo->Media->RemovableMedia;
  MediaPresent      = BlockIo->Media->MediaPresent;
  LogicalPartition  = BlockIo->Media->LogicalPartition;
  ReadOnly          = BlockIo->Media->ReadOnly;
  WriteCaching      = BlockIo->Media->WriteCaching;
  BlockSize         = BlockIo->Media->BlockSize;
  IoAlign           = BlockIo->Media->IoAlign;
  LastBlock         = BlockIo->Media->LastBlock;

  BufferSize        = (((UINT32)LastBlock)*BlockSize)>MAX_NUMBER_OF_READ_DISK_BUFFER ? \
                                MAX_NUMBER_OF_READ_DISK_BUFFER:((UINT32)LastBlock)*BlockSize;
  LastOffset        = MultU64x32 (LastBlock+1, BlockSize);

  if (BufferSize == 0) {
    BufferSize = 1;
  }

  Buffer = NULL;

  //
  // allocate buffer
  //
  Status = gtBS->AllocatePool (EfiBootServicesData, BufferSize, (VOID*)&Buffer);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.AllocatePool - Allocate pool",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  // If the floppy is ejected without "map -r", after first readdisk() or writedisk()
  // the DiskIo will be changed because of reinstall and the original DiskIo will be
  // invalid. Doing operation after this will hang the system. So add check error
  // status after that and once this condition happen return immediately.
  //

  //
  // Assertion Points 4.1.2.1
  // ReadDisk should not succeed to read from disk
  // When MedialId is not the id for the current media in the device
  //
  if (MediaPresent == TRUE) {
    for (Index = 0; Index < 5; Index++) {
      //
      // initialize test data
      //
      switch (Index) {
        case 0:
          NewMediaId = MediaId + 5;
          break;
        case 1:
          NewMediaId = MediaId + 1;
          break;
        case 2:
          NewMediaId = MediaId - 1;
          break;
        case 3:
          NewMediaId = MediaId - 5;
          break;
        case 4:
          NewMediaId = 0;
          break;
        default:
          NewMediaId = MediaId;
      }

      //
      // Verify test data
      //
      if (NewMediaId == MediaId) {
        continue;
      }

      //
      // Call ReadDisk with false MediaID
      //
      Status = DiskIo->ReadDisk (
                         DiskIo,
                         NewMediaId,
                         0,
                         BufferSize,
                         (VOID*)Buffer
                         );
      if (Status != EFI_MEDIA_CHANGED) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gDiskIoConformanceTestAssertionGuid001,
                     L"EFI_DISK_IO_PROTOCOL.ReadDisk - Read disk with MediaId not being the id for the current media in the device",
                     L"%a:%d:Actual MediaID = %d, MediaID = %d, Status = %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     MediaId,
                     NewMediaId,
                     Status
                     );
      if ((Status == EFI_NO_MEDIA) || (Status == EFI_DEVICE_ERROR)) {
        gtBS->FreePool (Buffer);
        return Status;
      }
    }
  }

  //
  // Assertion Point 4.1.2.2
  // ReadDisk should not succeed to read from device with invalid device addresses
  //
  if (MediaPresent == TRUE) {
    for (Index = 0; Index < 6; Index++) {
      //
      // initialize test data
      //
      switch (Index) {
        case 0:
          Offset = LastOffset + 1;
          break;
        case 1:
          Offset = LastOffset + 10;
          break;
        case 2:
          Offset = LastOffset - BufferSize + 1;
          break;
        case 3:
          Offset = LastOffset - BufferSize + 2;
          break;
        case 4:
          Offset = LastOffset - BufferSize + 3;
          break;
        case 5:
          Offset = LastOffset - BufferSize + 4;
          break;
        default:
          Offset = 0;
          break;
      }
      //
      // Verify test data
      //
      if (Offset + BufferSize <= LastOffset) {
        continue;
      }

      //
      // Call ReadDisk with invalid Offset
      //
      Status = DiskIo->ReadDisk (
                         DiskIo,
                         MediaId,
                         Offset,
                         BufferSize,
                         (VOID*)Buffer
                         );
      if (Status != EFI_INVALID_PARAMETER) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      }
      if ((Status == EFI_NO_MEDIA) || (Status == EFI_DEVICE_ERROR)) {
        gtBS->FreePool (Buffer);
        return Status;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gDiskIoConformanceTestAssertionGuid002,
                     L"EFI_DISK_IO_PROTOCOL.ReadDisk - Read disk with invalid Offset parameter",
                     L"%a:%d:BufferSize = %d, BlockSize = %d, Offset = 0x%lx, LastBlock = 0x%lx, Status = %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     BufferSize,
                     BlockSize,
                     Offset,
                     LastBlock,
                     Status
                     );
    }
  }

  //
  // Assertion Point 4.1.2.3
  // ReadDisk should not succeed to read from device that with no media present in the device
  //
  if (MediaPresent == FALSE) {
    //
    // Call ReadDisk with proper parameter
    //
    Status = DiskIo->ReadDisk (
                       DiskIo,
                       MediaId,
                       0,
                       BufferSize,
                       (VOID*)Buffer
                       );
    if (Status != EFI_NO_MEDIA) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gDiskIoConformanceTestAssertionGuid003,
                   L"EFI_DISK_IO_PROTOCOL.ReadDisk - Read disk from device without media present in the device",
                   L"%a:%d:BufferSize = %d, Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   BufferSize,
                   Status
                   );
  }

  gtBS->FreePool (Buffer);

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_DISK_IO_PROTOCOL.WriteDisk() Consistency Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.2
//
EFI_STATUS
BBTestWriteDiskConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_DISK_IO_PROTOCOL                 *DiskIo;
  EFI_BLOCK_IO_PROTOCOL                *BlockIo;
  EFI_TEST_ASSERTION                   AssertionType;
  UINT32                               MediaId;
  BOOLEAN                              RemovableMedia;
  BOOLEAN                              MediaPresent;
  BOOLEAN                              LogicalPartition;
  BOOLEAN                              ReadOnly;
  BOOLEAN                              WriteCaching;
  UINT32                               BlockSize;
  UINT32                               IoAlign;
  EFI_LBA                              LastBlock;
  UINT64                               LastOffset;
  UINTN                                BufferSize;
  UINT8                                *Buffer;
  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;
  CHAR16                               *DevicePathStr;
  UINTN                                Index;
  UINT32                               NewMediaId;
  UINT64                               Offset;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - Handle standard test library",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  DiskIo = (EFI_DISK_IO_PROTOCOL *)ClientInterface;

  Status = LocateBlockIoFromDiskIo (DiskIo, &BlockIo, StandardLib);
  if (EFI_ERROR(Status)) {
    return EFI_DEVICE_ERROR;
  }

  //
  // Locate Device path of the current DiskIo device
  // and save it into log for investigating
  //
  LocateDevicePathFromDiskIo (DiskIo, &DevicePath, StandardLib);

  DevicePathStr = DevicePathToStr (DevicePath);
  if (DevicePathStr != NULL) {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"\r\nCurrent Device: %s",
                   DevicePathStr
                   );
    gtBS->FreePool (DevicePathStr);
    DevicePathStr = NULL;
  }

  //
  // Initialize variable
  //
  MediaId           = BlockIo->Media->MediaId;
  RemovableMedia    = BlockIo->Media->RemovableMedia;
  MediaPresent      = BlockIo->Media->MediaPresent;
  LogicalPartition  = BlockIo->Media->LogicalPartition;
  ReadOnly          = BlockIo->Media->ReadOnly;
  WriteCaching      = BlockIo->Media->WriteCaching;
  BlockSize         = BlockIo->Media->BlockSize;
  IoAlign           = BlockIo->Media->IoAlign;
  LastBlock         = BlockIo->Media->LastBlock;

  BufferSize        = (((UINT32)LastBlock)*BlockSize)>MAX_NUMBER_OF_READ_DISK_BUFFER ? \
                                MAX_NUMBER_OF_READ_DISK_BUFFER:((UINT32)LastBlock)*BlockSize;
  LastOffset        = MultU64x32 (LastBlock+1, BlockSize);

  if (BufferSize == 0) {
    BufferSize = 1;
  }

  Buffer = NULL;

  //
  // allocate buffer
  //
  Status = gtBS->AllocatePool (EfiBootServicesData, BufferSize, (VOID*)&Buffer);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.AllocatePool - Allocate pool",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  // If the floppy is ejected without "map -r", after first readdisk() or writedisk()
  // the DiskIo will be changed because of reinstall and the original DiskIo will be
  // invalid. Doing operation after this will hang the system. So add check error
  // status after that and once this condition happen return immediately.
  //

  //
  // Assertion Points 4.2.2.1
  // WriteDisk should not succeed to write to disk
  // When MedialId is not the id for the current media in the device
  //
  if (MediaPresent == TRUE && ReadOnly == FALSE) {
    for (Index = 0; Index < 5; Index++) {
      //
      // initialize test data
      //
      switch (Index) {
        case 0:
          NewMediaId = MediaId + 5;
          break;
        case 1:
          NewMediaId = MediaId + 1;
          break;
        case 2:
          NewMediaId = MediaId - 1;
          break;
        case 3:
          NewMediaId = MediaId - 5;
          break;
        case 4:
          NewMediaId = 0;
          break;
        default:
          NewMediaId = MediaId;
      }

      //
      // Verify test data
      //
      if (NewMediaId == MediaId) {
        continue;
      }

      //
      // Call WriteDisk with false MediaID...Read first for avoid error writting
      //
      Status = DiskIo->ReadDisk (
                         DiskIo,
                         NewMediaId,
                         0,
                         BufferSize,
                         (VOID*)Buffer
                         );
      Status = DiskIo->WriteDisk (
                         DiskIo,
                         NewMediaId,
                         0,
                         BufferSize,
                         (VOID*)Buffer
                         );
      if (Status != EFI_MEDIA_CHANGED) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gDiskIoConformanceTestAssertionGuid005,
                     L"EFI_DISK_IO_PROTOCOL.WriteDisk - Write disk with MediaId not being the id for the current media in the device",
                     L"%a:%d:Actual MediaID = %d, MediaID = %d, Status = %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     MediaId,
                     NewMediaId,
                     Status
                     );
    }
  }

  //
  // Assertion Point 4.2.2.2
  // WriteDisk should not succeed to write to device with invalid device addresses
  //
  if ((MediaPresent == TRUE) && (ReadOnly == FALSE)) {
    for (Index = 0; Index < 6; Index++) {
      //
      // initialize test data
      //
      switch (Index) {
        case 0:
          Offset = LastOffset + 1;
          break;
        case 1:
          Offset = LastOffset + 10;
          break;
        case 2:
          Offset = LastOffset - BufferSize + 1;
          break;
        case 3:
          Offset = LastOffset - BufferSize + 2;
          break;
        case 4:
          Offset = LastOffset - BufferSize + 3;
          break;
        case 5:
          Offset = LastOffset - BufferSize + 4;
          break;
        default:
          Offset = 0;
          break;
      }
      //
      // Verify test data
      //
      if (Offset + BufferSize <= LastOffset) {
        continue;
      }

      //
      // Call WriteDisk with invalid Offset&BufferSize
      //
      Status = DiskIo->ReadDisk (
                         DiskIo,
                         MediaId,
                         Offset,
                         BufferSize,
                         (VOID*)Buffer
                         );
      if ((Status == EFI_NO_MEDIA) || (Status == EFI_DEVICE_ERROR)) {
        gtBS->FreePool (Buffer);
        return Status;
      }
      Status = DiskIo->WriteDisk (
                         DiskIo,
                         MediaId,
                         Offset,
                         BufferSize,
                         (VOID*)Buffer
                         );
      if (Status != EFI_INVALID_PARAMETER) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gDiskIoConformanceTestAssertionGuid006,
                     L"EFI_DISK_IO_PROTOCOL.WriteDisk - Write disk with invalid Offset parameter",
                     L"%a:%d:BufferSize = %d, BlockSize = %d, Offset = 0x%lx, LastBlock = 0x%lx, Status = %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     BufferSize,
                     BlockSize,
                     Offset,
                     LastBlock,
                     Status
                     );
      if ((Status == EFI_NO_MEDIA) || (Status == EFI_DEVICE_ERROR)) {
        gtBS->FreePool (Buffer);
        return Status;
      }
    }
  }

  //
  // Assertion Point 4.2.2.3
  // WriteDisk should not succeed to write to a write-protected device
  //
  if ((MediaPresent == TRUE) && (ReadOnly == TRUE)) {
    //
    // Call WriteDisk with proper parameter
    //
    Status = DiskIo->ReadDisk (
                       DiskIo,
                       MediaId,
                       0,
                       BufferSize,
                       (VOID*)Buffer
                       );
    if ((Status == EFI_NO_MEDIA) || (Status == EFI_DEVICE_ERROR)) {
        gtBS->FreePool (Buffer);
        return Status;
    }
    Status = DiskIo->WriteDisk (
                       DiskIo,
                       MediaId,
                       0,
                       BufferSize,
                       (VOID*)Buffer
                       );
    if (Status != EFI_WRITE_PROTECTED) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gDiskIoConformanceTestAssertionGuid007,
                   L"EFI_DISK_IO_PROTOCOL.WriteDisk - Write disk to a write-protected disk",
                   L"%a:%d:BufferSize = %d, Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   BufferSize,
                   Status
                   );
  }
  if ((Status == EFI_NO_MEDIA) || (Status == EFI_DEVICE_ERROR)) {
    gtBS->FreePool (Buffer);
    return Status;
  }

  //
  // Assertion Point 4.2.2.4
  // WriteDisk should not succeed to write to device that with no media present in the device
  //
  if ((MediaPresent == FALSE) && (ReadOnly == FALSE)) {
    //
    // Call WriteDisk with proper parameter
    //
    Status = DiskIo->ReadDisk (
                       DiskIo,
                       MediaId,
                       0,
                       BufferSize,
                       (VOID*)Buffer
                       );
    Status = DiskIo->WriteDisk (
                       DiskIo,
                       MediaId,
                       0,
                       BufferSize,
                       (VOID*)Buffer
                       );
    if (Status != EFI_NO_MEDIA) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gDiskIoConformanceTestAssertionGuid008,
                   L"EFI_DISK_IO_PROTOCOL.WriteDisk - Write disk to device without media present in the device",
                   L"%a:%d:BufferSize = %d, Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   BufferSize,
                   Status
                   );
  }

  gtBS->FreePool (Buffer);

  return EFI_SUCCESS;
}
