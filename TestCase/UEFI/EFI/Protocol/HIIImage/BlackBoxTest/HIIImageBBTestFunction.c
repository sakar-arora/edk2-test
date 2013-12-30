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
    HIIImageBBTestFunction.c

Abstract:
    for EFI Driver HII Image Protocol's function Test

--*/
#include "HIIImageBBTestMain.h"

extern UINT8 mPackageList1[];

extern UINT8 mImage[];

extern UINT8 mSetNewImage[];

#define mImage1 ((EFI_IMAGE_INPUT*)(mImage))
#define mImage2 ((EFI_IMAGE_INPUT*)(mSetNewImage))
#define Image1Length 1
#define Image2Length 1

EFI_STATUS
BBTestNewImageFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_IMAGE_PROTOCOL                     *HIIImage
  );
  
EFI_STATUS
BBTestGetImageFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_IMAGE_PROTOCOL                     *HIIImage
  );
  
EFI_STATUS
BBTestSetImageFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_IMAGE_PROTOCOL                     *HIIImage
  );

EFI_STATUS
BBTestDrawImageFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_IMAGE_PROTOCOL                     *HIIImage
  );

EFI_STATUS
BBTestDrawImageFunctionTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_IMAGE_PROTOCOL                     *HIIImage
  );

EFI_STATUS
BBTestDrawImageFunctionTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_GRAPHICS_OUTPUT_PROTOCOL               *GraphicsOutput,
  IN EFI_HII_IMAGE_PROTOCOL                     *HIIImage
  );

EFI_STATUS
BBTestDrawImageIdFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_IMAGE_PROTOCOL                     *HIIImage
  );

EFI_STATUS
BBTestDrawImageIdFunctionTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_IMAGE_PROTOCOL                     *HIIImage
  );

EFI_STATUS
BBTestDrawImageIdFunctionTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_GRAPHICS_OUTPUT_PROTOCOL               *GraphicsOutput,
  IN EFI_HII_IMAGE_PROTOCOL                     *HIIImage
  );


//
//Test Cases
//
EFI_STATUS
BBTestNewImageFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_HII_IMAGE_PROTOCOL                *HIIImage;
  EFI_HII_DATABASE_PROTOCOL             *HIIDatabase;

  //
  // init
  //
  HIIImage = (EFI_HII_IMAGE_PROTOCOL*) ClientInterface;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }
  
  Status = GetHIIDatabaseInterface (&HIIDatabase);
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  //
  //Call check points
  //
  BBTestNewImageFunctionTestCheckpoint1 (StandardLib, HIIDatabase, HIIImage);
  
  return EFI_SUCCESS;
}

EFI_STATUS
BBTestGetImageFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_HII_IMAGE_PROTOCOL                *HIIImage;
  EFI_HII_DATABASE_PROTOCOL             *HIIDatabase;

  //
  // init
  //
  HIIImage = (EFI_HII_IMAGE_PROTOCOL*) ClientInterface;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }
  
  Status = GetHIIDatabaseInterface (&HIIDatabase);
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  //
  //Call check points
  //
  BBTestGetImageFunctionTestCheckpoint1 (StandardLib, HIIDatabase, HIIImage);
  
  return EFI_SUCCESS;
}

EFI_STATUS
BBTestSetImageFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_HII_IMAGE_PROTOCOL                *HIIImage;
  EFI_HII_DATABASE_PROTOCOL             *HIIDatabase;

  //
  // init
  //
  HIIImage = (EFI_HII_IMAGE_PROTOCOL*) ClientInterface;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }
  
  Status = GetHIIDatabaseInterface (&HIIDatabase);
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  //
  //Call check points
  //
  BBTestSetImageFunctionTestCheckpoint1 (StandardLib, HIIDatabase, HIIImage);
  
  return EFI_SUCCESS;
}

EFI_STATUS
BBTestDrawImageFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_HII_IMAGE_PROTOCOL                *HIIImage;
  EFI_GRAPHICS_OUTPUT_PROTOCOL          *GraphicsOutput;

  //
  // init
  //
  HIIImage = (EFI_HII_IMAGE_PROTOCOL*) ClientInterface;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }
  
  Status = GetGraphicsOutputInterface (&GraphicsOutput);
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  //
  //Call check points
  //
  BBTestDrawImageFunctionTestCheckpoint1 (StandardLib, HIIImage);

  BBTestDrawImageFunctionTestCheckpoint2 (StandardLib, HIIImage);

//  BBTestDrawImageFunctionTestCheckpoint3 (StandardLib, GraphicsOutput, HIIImage);
  
  return EFI_SUCCESS;
}

EFI_STATUS
BBTestDrawImageIdFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_HII_IMAGE_PROTOCOL                *HIIImage;
  EFI_HII_DATABASE_PROTOCOL             *HIIDatabase;
  EFI_GRAPHICS_OUTPUT_PROTOCOL          *GraphicsOutput;  

  //
  // init
  //
  HIIImage = (EFI_HII_IMAGE_PROTOCOL*) ClientInterface;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }
  
  Status = GetHIIDatabaseInterface (&HIIDatabase);
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  Status = GetGraphicsOutputInterface (&GraphicsOutput);
  if ( EFI_ERROR(Status) ) {
    return Status;
  }
  
  //
  //Call check points
  //
  BBTestDrawImageIdFunctionTestCheckpoint1 (StandardLib, HIIDatabase, HIIImage);

  BBTestDrawImageIdFunctionTestCheckpoint2 (StandardLib, HIIDatabase, HIIImage);

//  BBTestDrawImageIdFunctionTestCheckpoint3 (StandardLib, HIIDatabase, GraphicsOutput, HIIImage);
  
  
  return EFI_SUCCESS;
}


//
//Check Points
//
EFI_STATUS
BBTestNewImageFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_IMAGE_PROTOCOL                     *HIIImage
  )
{
  EFI_STATUS                     Status;
  EFI_TEST_ASSERTION             AssertionType;
  
  EFI_HII_HANDLE                 Handle;
  EFI_HII_PACKAGE_LIST_HEADER    *PackageList;  
  EFI_IMAGE_ID                   ImageId;
  EFI_IMAGE_INPUT                *Image;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL  *Bitmap;

  PackageList = (EFI_HII_PACKAGE_LIST_HEADER*) mPackageList1;
  //
  // Add the PackageList to HII database
  //
  Status = HIIDatabase->NewPackageList (
                          HIIDatabase,
                          PackageList,
                          NULL,
                          &Handle
                          );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  //
  // Init the Image
  //
  Image = (EFI_IMAGE_INPUT *) AllocateZeroPool (sizeof(EFI_IMAGE_INPUT));
  if ( Image == NULL ) {
    Status = HIIDatabase->RemovePackageList (
                            HIIDatabase,
                            Handle
                            );
    if ( EFI_ERROR(Status) ) {
      return Status;
    }
  	return EFI_UNSUPPORTED;
  }
  Image->Flags = 0;
  Image->Width = 50;
  Image->Height = 60;
  Bitmap = (EFI_GRAPHICS_OUTPUT_BLT_PIXEL *) AllocateZeroPool (Image->Width * Image->Height * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));
  if ( Bitmap == NULL ) {
    gtBS->FreePool (Image);
	Status = HIIDatabase->RemovePackageList (
                            HIIDatabase,
                            Handle
                            );
    if ( EFI_ERROR(Status) ) {
      return Status;
    }
	return EFI_UNSUPPORTED;
  }
  Image->Bitmap = Bitmap;
  
  //
  // Call NewImage with valid parameters
  //
  Status = HIIImage->NewImage (
                       HIIImage,
                       Handle,
                       &ImageId,
                       Image
                       );
  
  if ( EFI_SUCCESS != Status && EFI_OUT_OF_RESOURCES != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIImageBBTestFunctionAssertionGuid001,
                 L"HII_IMAGE_PROTOCOL.NewImage - NewImage() returns EFI_SUCCESS with valid parameters and result checked.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Remove the PackageList from the HII database
  //
  gtBS->FreePool (Bitmap);
  gtBS->FreePool (Image);

  Status = HIIDatabase->RemovePackageList (
                          HIIDatabase,
                          Handle
                          );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  return EFI_SUCCESS;
}

EFI_STATUS
BBTestGetImageFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_IMAGE_PROTOCOL                     *HIIImage
  )
{
  EFI_STATUS                     Status;
  EFI_STATUS                     TempStatus;
  EFI_TEST_ASSERTION             AssertionType;
  
  EFI_HII_HANDLE                 Handle;
  EFI_HII_PACKAGE_LIST_HEADER    *PackageList;
  EFI_IMAGE_ID                   ImageId;
  EFI_IMAGE_INPUT                *Image;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL  *Bitmap;
  
  
  PackageList = (EFI_HII_PACKAGE_LIST_HEADER*) mPackageList1;
  //
  // Add the PackageList to HII database
  //
  Status = HIIDatabase->NewPackageList (
                          HIIDatabase,
                          PackageList,
                          NULL,
                          &Handle
                          );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  //
  // Init the Image
  //
  Image = (EFI_IMAGE_INPUT *) AllocateZeroPool (sizeof(EFI_IMAGE_INPUT));
  if ( Image == NULL ) {
    Status = HIIDatabase->RemovePackageList (
                            HIIDatabase,
                            Handle
                            );
    if ( EFI_ERROR(Status) ) {
      return Status;
    }  	
  	return EFI_UNSUPPORTED;
  }
  Image->Flags = 0;
  Image->Width = 50;
  Image->Height = 60;
  Bitmap = (EFI_GRAPHICS_OUTPUT_BLT_PIXEL *) AllocateZeroPool (Image->Width * Image->Height * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));
  if ( Bitmap == NULL ) {
    gtBS->FreePool ( Image );
    Status = HIIDatabase->RemovePackageList (
                            HIIDatabase,
                            Handle
                            );
    if ( EFI_ERROR(Status) ) {
      return Status;
    }  		
	return EFI_UNSUPPORTED;
  }
  Image->Bitmap = Bitmap;
  //
  // Call NewImage to add a new image
  //
  Status = HIIImage->NewImage (
                       HIIImage,
                       Handle,
                       &ImageId,
                       Image
                       );
  if ( EFI_ERROR(Status) ) {
    gtBS->FreePool (Bitmap);
    gtBS->FreePool (Image);
    TempStatus = HIIDatabase->RemovePackageList (
                                HIIDatabase,
                                Handle
                                );
    if ( EFI_ERROR(TempStatus) ) {
      return TempStatus;
	}
	return Status;
  }

  //
  // Call GetImage to with valid parameters
  //
  Status = HIIImage->GetImage (
                       HIIImage,
                       Handle,
                       ImageId,
                       Image
                       );

//  if ( EFI_SUCCESS == Status && ImageSize == (Image->Width * Image->Height * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL) + 8) ) {
  if ( EFI_SUCCESS == Status ) {	
	AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIImageBBTestFunctionAssertionGuid002,
                 L"HII_IMAGE_PROTOCOL.GetImage - GetImage() returns EFI_SUCCESS with valid parameters and the result checked.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Remove the PackageList from the HII database
  //
  gtBS->FreePool (Bitmap);
  gtBS->FreePool (Image);

  Status = HIIDatabase->RemovePackageList (
                          HIIDatabase,
                          Handle
                          );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  return EFI_SUCCESS;
}

EFI_STATUS
BBTestSetImageFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_IMAGE_PROTOCOL                     *HIIImage
  )
{
  EFI_STATUS                     Status;
  EFI_STATUS                     TempStatus;
  EFI_TEST_ASSERTION             AssertionType;
  
  EFI_HII_HANDLE                 Handle;
  EFI_HII_PACKAGE_LIST_HEADER    *PackageList; 
  EFI_IMAGE_ID                   ImageId;
  EFI_IMAGE_INPUT                *Image1;
  EFI_IMAGE_INPUT                *Image2;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL  *Bitmap1; 
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL  *Bitmap2;

  PackageList = (EFI_HII_PACKAGE_LIST_HEADER*) mPackageList1;
  //
  // Add the PackageList to HII database
  //
  Status = HIIDatabase->NewPackageList (
                          HIIDatabase,
                          PackageList,
                          NULL,
                          &Handle
                          );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  //
  // Init the Image1
  //
  Image1 = (EFI_IMAGE_INPUT *) AllocateZeroPool (sizeof(EFI_IMAGE_INPUT));
  if ( Image1 == NULL ) {
    Status = HIIDatabase->RemovePackageList (
                            HIIDatabase,
                            Handle
                            );
    if ( EFI_ERROR(Status) ) {
      return Status;
    }  	  	
  	return EFI_UNSUPPORTED;
  }
  Image1->Flags = 0;
  Image1->Width = 50;
  Image1->Height = 60;
  Bitmap1 = (EFI_GRAPHICS_OUTPUT_BLT_PIXEL *) AllocateZeroPool (Image1->Width * Image1->Height * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));
  if ( Bitmap1 == NULL ) {
    gtBS->FreePool (Image1);
    Status = HIIDatabase->RemovePackageList (
                            HIIDatabase,
                            Handle
                            );
    if ( EFI_ERROR(Status) ) {
      return Status;
    }  		
	return EFI_UNSUPPORTED;
  }
  Image1->Bitmap = Bitmap1;
  
  //
  // Call NewImage to add a new image
  //
  Status = HIIImage->NewImage (
                       HIIImage,
                       Handle,
                       &ImageId,
                       Image1
                       );
  if ( EFI_ERROR(Status) ) {
  	gtBS->FreePool (Bitmap1);
	gtBS->FreePool (Image1);
    TempStatus = HIIDatabase->RemovePackageList (
                                HIIDatabase,
                                Handle
                                );
	if ( EFI_ERROR(TempStatus) ) {
		return TempStatus;
	}
    return Status;
  }
  
  //
  // Init the Image2
  //
  Image2 = (EFI_IMAGE_INPUT *) AllocateZeroPool (sizeof(EFI_IMAGE_INPUT));
  if ( Image2 == NULL ) {
  	gtBS->FreePool (Bitmap1);
	gtBS->FreePool (Image1);
	Status = HIIDatabase->RemovePackageList (
                            HIIDatabase,
                            Handle
                            ); 
    if ( EFI_ERROR (Status) ) {
      return Status;
    }
  	return EFI_UNSUPPORTED;
  }

  Image2->Flags = 0;
  Image2->Width = 30;
  Image2->Height = 40;
  Bitmap2= (EFI_GRAPHICS_OUTPUT_BLT_PIXEL *) AllocateZeroPool (Image2->Width * Image2->Height * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));
  if ( Bitmap2 == NULL ) {
  	gtBS->FreePool (Bitmap1);
	gtBS->FreePool (Image1);
    gtBS->FreePool (Image2);
    Status = HIIDatabase->RemovePackageList (
                            HIIDatabase,
                            Handle
                            );
    if ( EFI_ERROR (Status) ) {
      return Status;
    }
	return EFI_UNSUPPORTED;
  }
  Image2->Bitmap = Bitmap2;

  
  //
  // Call SetImage with valid parameters
  //
  Status = HIIImage->SetImage(
                       HIIImage,
                       Handle,
                       ImageId,
                       Image2
                       );
  
  if ( EFI_SUCCESS != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIImageBBTestFunctionAssertionGuid003,
                 L"HII_IMAGE_PROTOCOL.SetImage - SetImage() returns EFI_SUCCESS with valid parameters and result checked.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Remove the PackageList from the HII database
  //
  gtBS->FreePool (Bitmap1);
  gtBS->FreePool (Image1);
  gtBS->FreePool (Bitmap2);
  gtBS->FreePool (Image2);
  
  Status = HIIDatabase->RemovePackageList (
                          HIIDatabase,
                          Handle
                          );
  if ( EFI_ERROR(Status) ) {
    return Status; 
  }

  return EFI_SUCCESS;
}


EFI_STATUS
BBTestDrawImageFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_IMAGE_PROTOCOL                     *HIIImage
)
{
  EFI_STATUS                     Status;
  EFI_TEST_ASSERTION             AssertionType;
  
  EFI_HII_DRAW_FLAGS             Flag;
  EFI_IMAGE_OUTPUT               *Blt;
  UINTN                          BltX;
  UINTN                          BltY;
  EFI_IMAGE_INPUT                *Image;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL  *Bitmap;
  //
  // Init the Flag and Blt
  //
  Flag = EFI_HII_DRAW_FLAG_FORCE_OPAQUE;
  Blt = NULL;
  BltX = 0;
  BltY = 0;
  //
  // Init the Image
  //
  Image = (EFI_IMAGE_INPUT *) AllocateZeroPool (sizeof(EFI_IMAGE_INPUT));
  if ( Image == NULL )
    return EFI_UNSUPPORTED;
  Image->Flags = 0;
  Image->Width = 50;
  Image->Height = 60;
  Bitmap = (EFI_GRAPHICS_OUTPUT_BLT_PIXEL *) AllocateZeroPool (Image->Width * Image->Height * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));
  if ( Bitmap == NULL ) {
    gtBS->FreePool ( Image );
    return EFI_UNSUPPORTED;
  }
  Image->Bitmap = Bitmap;

  //
  // Call DrawImage with with valid parameter
  //
  Status = HIIImage->DrawImage(
                       HIIImage,
                       Flag,
                       Image,
                       &Blt,
                       BltX,
                       BltY
                       );
  if ( EFI_SUCCESS != Status && EFI_OUT_OF_RESOURCES != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIImageBBTestFunctionAssertionGuid004,
                 L"HII_IMAGE_PROTOCOL.DrawImage - DrawImage() returns EFI_SUCCESS with valid parameter.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  gtBS->FreePool (Image->Bitmap);
  gtBS->FreePool (Image);
  gtBS->FreePool (Blt);
  
  return EFI_SUCCESS;
}


EFI_STATUS
BBTestDrawImageFunctionTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_IMAGE_PROTOCOL                     *HIIImage
)
{
  EFI_STATUS                     Status;
  EFI_TEST_ASSERTION             AssertionType;
  
  EFI_IMAGE_OUTPUT               *Blt;
  UINTN                          BltX;
  UINTN                          BltY;
  EFI_IMAGE_INPUT                *Image;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL  *Bitmap;
  UINT16                         Index;

  EFI_HII_DRAW_FLAGS             ValidFlags[] = {
                                   EFI_HII_DRAW_FLAG_CLIP,
                                   EFI_HII_DRAW_FLAG_DEFAULT,
                                   EFI_HII_DRAW_FLAG_FORCE_TRANS,
                                   EFI_HII_DRAW_FLAG_FORCE_OPAQUE,
                                   0xFFFFFFFF 
                                 };

  //
  // Init the Flag and Blt
  //
  BltX = 0;
  BltY = 0;

  Blt = (EFI_IMAGE_OUTPUT *) AllocateZeroPool (sizeof(EFI_IMAGE_OUTPUT));
  if (Blt == NULL){
    return  EFI_UNSUPPORTED;
  }

  Blt->Width = 50;
  Blt->Height = 40;
  Blt->Image.Bitmap = (EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)AllocateZeroPool (Blt->Width *Blt->Height * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));
  if (Blt->Image.Bitmap == NULL){
  	gtBS->FreePool (Blt);
    return  EFI_UNSUPPORTED;
  } 
  
  //
  // Init the Image
  //
  Image = (EFI_IMAGE_INPUT *) AllocateZeroPool (sizeof(EFI_IMAGE_INPUT));
  if ( Image == NULL ) {
  	gtBS->FreePool (Blt->Image.Bitmap);
	gtBS->FreePool (Blt);
    return EFI_UNSUPPORTED;
  }
  Image->Flags = 0;
  Image->Width = 50;
  Image->Height = 60;
  Bitmap = (EFI_GRAPHICS_OUTPUT_BLT_PIXEL *) AllocateZeroPool (Image->Width * Image->Height * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));
  if ( Bitmap == NULL ) {
  	gtBS->FreePool (Blt->Image.Bitmap);
	gtBS->FreePool (Blt);  	
    gtBS->FreePool (Image);
    return EFI_UNSUPPORTED;
  }
  Image->Bitmap = Bitmap;

  //
  // Call DrawImage with with valid parameter
  //
  for (Index=0; ValidFlags[Index] != 0xFFFFFFFF; Index++) {
    Status = HIIImage->DrawImage(
                         HIIImage,
                         ValidFlags[Index],
                         Image,
                         &Blt,
                         BltX,
                         BltY
                         );
    if ( EFI_SUCCESS != Status && EFI_OUT_OF_RESOURCES != Status ) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gHIIImageBBTestFunctionAssertionGuid005,
                   L"HII_IMAGE_PROTOCOL.DrawImage - DrawImage() returns EFI_SUCCESS with valid parameter.",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }
  
  gtBS->FreePool (Image->Bitmap);
  gtBS->FreePool (Image);
  gtBS->FreePool (Blt);
  
  return EFI_SUCCESS;
}



EFI_STATUS
BBTestDrawImageFunctionTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_GRAPHICS_OUTPUT_PROTOCOL               *GraphicsOutput,
  IN EFI_HII_IMAGE_PROTOCOL                     *HIIImage
  )
{

  EFI_STATUS                     Status;
  EFI_TEST_ASSERTION             AssertionType;
  
  EFI_HII_DRAW_FLAGS             Flag;
  EFI_IMAGE_OUTPUT               *Blt;
  UINTN                          BltX;
  UINTN                          BltY;
  EFI_IMAGE_INPUT                *Image;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL  *Bitmap; 
  UINT32                         HorizontalResolution;
  UINT32                         VerticalResolution;
  UINT32                         CurrentMode;
  
  
  //
  // Init the Flag and Blt
  //
  Flag = EFI_HII_DIRECT_TO_SCREEN;
  BltX = 0;
  BltY = 0;

  if (GraphicsOutput != NULL) {
    HorizontalResolution = GraphicsOutput->Mode->Info->HorizontalResolution;
    VerticalResolution = GraphicsOutput->Mode->Info->VerticalResolution;
  } else {
    return EFI_UNSUPPORTED;
  }

  Blt = (EFI_IMAGE_OUTPUT *) AllocateZeroPool (sizeof(EFI_IMAGE_OUTPUT));
  if (Blt == NULL)
    return  EFI_UNSUPPORTED;
  
  Blt->Width = (UINT16) (HorizontalResolution);
  Blt->Height = (UINT16) (VerticalResolution);
  Blt->Image.Screen = GraphicsOutput;

  //
  // Init the Image
  //
  Image = (EFI_IMAGE_INPUT *) AllocateZeroPool (sizeof(EFI_IMAGE_INPUT));
  if ( Image == NULL ){
	gtBS->FreePool (Blt);
  	return EFI_UNSUPPORTED;
  }
  Image->Flags = 0;
  Image->Width = 50;
  Image->Height = 60;
  Bitmap = (EFI_GRAPHICS_OUTPUT_BLT_PIXEL *) AllocateZeroPool (Image->Width * Image->Height * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));
  if ( Bitmap == NULL ) {
	gtBS->FreePool (Blt);
    gtBS->FreePool (Image);
	return EFI_UNSUPPORTED;
  }
  Image->Bitmap = Bitmap;

  CurrentMode = GraphicsOutput->Mode->Mode;


  //
  // Call DrawImage with with valid parameter
  //
  Status = HIIImage->DrawImage(
                       HIIImage,
                       Flag,
                       Image,
                       &Blt,
                       BltX,
                       BltY
                       );

  Status = GraphicsOutput->SetMode (GraphicsOutput, CurrentMode);
  
  if ( EFI_SUCCESS != Status && EFI_OUT_OF_RESOURCES != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIImageBBTestFunctionAssertionGuid006,
                 L"HII_IMAGE_PROTOCOL.DrawImage - DrawImage() returns EFI_SUCCESS with valid parameter.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  
  gtBS->FreePool (Blt);
  gtBS->FreePool (Image->Bitmap);
  gtBS->FreePool (Image);
  
  return EFI_SUCCESS;
}


EFI_STATUS
BBTestDrawImageIdFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_IMAGE_PROTOCOL                     *HIIImage
  )
{
  EFI_STATUS                     Status;
  EFI_STATUS                     TempStatus;
  EFI_TEST_ASSERTION             AssertionType;
  
  EFI_HII_HANDLE                 Handle;
  EFI_HII_PACKAGE_LIST_HEADER    *PackageList;  
  EFI_HII_DRAW_FLAGS             Flag;
  EFI_IMAGE_OUTPUT               *Blt;
  UINTN                          BltX;
  UINTN                          BltY;
  EFI_IMAGE_INPUT                *Image;
  EFI_IMAGE_ID                   ImageId;
  
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL  *Bitmap;
  
  //
  // Init the Flag and Blt
  //
  Flag = EFI_HII_DRAW_FLAG_FORCE_OPAQUE;
  Blt = NULL;
  BltX = 0;
  BltY = 0;

  //
  // Init the Image
  //
  Image = (EFI_IMAGE_INPUT *) AllocateZeroPool (sizeof(EFI_IMAGE_INPUT));
  if ( Image == NULL )
    return EFI_UNSUPPORTED;
  Image->Flags = 0;
  Image->Width = 50;
  Image->Height = 60;
  Bitmap = (EFI_GRAPHICS_OUTPUT_BLT_PIXEL *) AllocateZeroPool (Image->Width * Image->Height * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));
  if ( Bitmap == NULL ) {
    gtBS->FreePool ( Image );
    return EFI_UNSUPPORTED;
  }
  Image->Bitmap = Bitmap;

  PackageList = (EFI_HII_PACKAGE_LIST_HEADER*) mPackageList1;
  //
  // Add the PackageList to HII database
  //
  Status = HIIDatabase->NewPackageList (
                          HIIDatabase,
                          PackageList,
                          NULL,
                          &Handle
                          );
  if ( EFI_ERROR(Status) ) {
    gtBS->FreePool (Image->Bitmap);
    gtBS->FreePool (Image);
    return Status;
  }

  //
  // Call NewImage to get the ImageId
  //
  Status = HIIImage->NewImage (
                       HIIImage,
                       Handle,
                       &ImageId,
                       Image
                       );
  if ( EFI_ERROR(Status) ) {
    gtBS->FreePool (Image->Bitmap);
    gtBS->FreePool (Image);
    TempStatus = HIIDatabase->RemovePackageList (
                                HIIDatabase,
                                Handle
                                );
	if ( EFI_ERROR(TempStatus) ) {
      return TempStatus;
	}                                
    return Status;
  }

  //
  // Call DrawImageId with with valid parameter
  //
  Status = HIIImage->DrawImageId(
                       HIIImage,
                       Flag,
                       Handle,
                       ImageId,
                       &Blt,
                       BltX,
                       BltY
                       );
  if ( EFI_SUCCESS != Status && EFI_OUT_OF_RESOURCES != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIImageBBTestFunctionAssertionGuid007,
                 L"HII_IMAGE_PROTOCOL.DrawImageId - DrawImageId() returns EFI_SUCCESS with valid parameter.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  
  gtBS->FreePool (Image->Bitmap);
  gtBS->FreePool (Image);
  gtBS->FreePool (Blt);

  Status = HIIDatabase->RemovePackageList (
                          HIIDatabase,
                          Handle
                          );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }                 
  
  return EFI_SUCCESS;

}

EFI_STATUS
BBTestDrawImageIdFunctionTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_HII_IMAGE_PROTOCOL                     *HIIImage
  )
{
  EFI_STATUS                     Status;
  EFI_STATUS                     TempStatus;
  EFI_TEST_ASSERTION             AssertionType;
  
  EFI_HII_HANDLE                 Handle;
  EFI_HII_PACKAGE_LIST_HEADER    *PackageList; 
  EFI_IMAGE_OUTPUT               *Blt;
  UINTN                          BltX;
  UINTN                          BltY;
  EFI_IMAGE_INPUT                *Image;
  EFI_IMAGE_ID                   ImageId;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL  *Bitmap;
  UINT16                         Index;

  EFI_HII_DRAW_FLAGS             ValidFlags[] = {
                                   EFI_HII_DRAW_FLAG_CLIP,
                                   EFI_HII_DRAW_FLAG_DEFAULT,
                                   EFI_HII_DRAW_FLAG_FORCE_TRANS,
                                   EFI_HII_DRAW_FLAG_FORCE_OPAQUE,
                                   0xFFFFFFFF 
                                 };

  BltX = 0;
  BltY = 0;
  
  PackageList = (EFI_HII_PACKAGE_LIST_HEADER*) mPackageList1;
  //
  // Add the PackageList to HII database
  //
  Status = HIIDatabase->NewPackageList (
                          HIIDatabase,
                          PackageList,
                          NULL,
                          &Handle
                          );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  //
  // Init Blt
  //
  Blt = (EFI_IMAGE_OUTPUT *) AllocateZeroPool (sizeof(EFI_IMAGE_OUTPUT));
  if (Blt == NULL){
  	Status = HIIDatabase->RemovePackageList (
                            HIIDatabase,
                            Handle
                            );
    if ( EFI_ERROR(Status) ) {
      return Status;
    }             
    return  EFI_UNSUPPORTED;
  }

  Blt->Width = 50;
  Blt->Height = 40;
  Blt->Image.Bitmap = (EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)AllocateZeroPool (Blt->Width *Blt->Height * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));
  if (Blt->Image.Bitmap == NULL){
  	gtBS->FreePool (Blt);
	Status = HIIDatabase->RemovePackageList (
                            HIIDatabase,
                            Handle
                            );
    if ( EFI_ERROR(Status) ) {
      return Status;
    }  
    return  EFI_UNSUPPORTED;
  }

  
  //
  // Init the Image
  //
  Image = (EFI_IMAGE_INPUT *) AllocateZeroPool (sizeof(EFI_IMAGE_INPUT));
  if ( Image == NULL ) {
  	gtBS->FreePool (Blt->Image.Bitmap);
    gtBS->FreePool (Blt);
	Status = HIIDatabase->RemovePackageList (
                            HIIDatabase,
                            Handle
                            );
    if ( EFI_ERROR(Status) ) {
      return Status;
    }
    return EFI_UNSUPPORTED;
  }
  Image->Flags = 0;
  Image->Width = 50;
  Image->Height = 60;
  Bitmap = (EFI_GRAPHICS_OUTPUT_BLT_PIXEL *) AllocateZeroPool (Image->Width * Image->Height * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));
  if ( Bitmap == NULL ) {
  	gtBS->FreePool (Blt->Image.Bitmap);
    gtBS->FreePool (Blt);  	
    gtBS->FreePool (Image);
	Status = HIIDatabase->RemovePackageList (
                            HIIDatabase,
                            Handle
                            );
    if ( EFI_ERROR(Status) ) {
      return Status;
    }
	return EFI_UNSUPPORTED;
  }
  Image->Bitmap = Bitmap;

  //
  // Call NewImage to get the ImageId
  //
  Status = HIIImage->NewImage (
                       HIIImage,
                       Handle,
                       &ImageId,
                       Image
                       );
  if ( EFI_ERROR(Status) ) {
  	gtBS->FreePool (Blt->Image.Bitmap);
    gtBS->FreePool (Blt);
    gtBS->FreePool (Image->Bitmap);
    gtBS->FreePool (Image);
    TempStatus = HIIDatabase->RemovePackageList (
                                HIIDatabase,
                                Handle
                                );
	if ( EFI_ERROR(TempStatus) ) {
      return TempStatus;
	}                                
    return Status;
  }


  //
  // Call DrawImage with with valid parameter
  //
  for (Index=0; ValidFlags[Index] != 0xFFFFFFFF; Index++) {
    Status = HIIImage->DrawImageId(
                         HIIImage,
                         ValidFlags[Index],
                         Handle,
                         ImageId,
                         &Blt,
                         BltX,
                         BltY
                         );
    if ( EFI_SUCCESS != Status && EFI_OUT_OF_RESOURCES != Status ) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gHIIImageBBTestFunctionAssertionGuid008,
                   L"HII_IMAGE_PROTOCOL.DrawImageId - DrawImageId() returns EFI_SUCCESS with valid parameter.",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }
  
  gtBS->FreePool (Image->Bitmap);
  gtBS->FreePool (Image);
  gtBS->FreePool (Blt);

  Status = HIIDatabase->RemovePackageList (
                          HIIDatabase,
                          Handle
                          );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }  
  
  return EFI_SUCCESS;

}

EFI_STATUS
BBTestDrawImageIdFunctionTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_HII_DATABASE_PROTOCOL                  *HIIDatabase,
  IN EFI_GRAPHICS_OUTPUT_PROTOCOL               *GraphicsOutput,
  IN EFI_HII_IMAGE_PROTOCOL                     *HIIImage
  )
{
  EFI_STATUS                     Status;
  EFI_STATUS                     TempStatus;
  EFI_TEST_ASSERTION             AssertionType;

  EFI_HII_HANDLE                 Handle;
  EFI_HII_PACKAGE_LIST_HEADER    *PackageList;    
  EFI_HII_DRAW_FLAGS             Flag;
  EFI_IMAGE_OUTPUT               *Blt;
  UINTN                          BltX;
  UINTN                          BltY;
  EFI_IMAGE_INPUT                *Image;
  EFI_IMAGE_ID                   ImageId;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL  *Bitmap; 
  UINT32                         HorizontalResolution;
  UINT32                         VerticalResolution;
  
  
  //
  // Init the Flag and Blt
  //
  Flag = EFI_HII_DIRECT_TO_SCREEN;
  BltX = 0;
  BltY = 0;

  if (GraphicsOutput != NULL) {
    HorizontalResolution = GraphicsOutput->Mode->Info->HorizontalResolution;
    VerticalResolution = GraphicsOutput->Mode->Info->VerticalResolution;
  } else {
    return EFI_UNSUPPORTED;
  }

  Blt = (EFI_IMAGE_OUTPUT *) AllocateZeroPool (sizeof(EFI_IMAGE_OUTPUT));
  if (Blt == NULL)
    return  EFI_UNSUPPORTED;
  
  Blt->Width = (UINT16) (HorizontalResolution);
  Blt->Height = (UINT16) (VerticalResolution);
  Blt->Image.Screen = GraphicsOutput;


  //
  // Init the Image
  //
  Image = (EFI_IMAGE_INPUT *) AllocateZeroPool (sizeof(EFI_IMAGE_INPUT));
  if ( Image == NULL ){
	gtBS->FreePool (Blt);
  	return EFI_UNSUPPORTED;
  }
  Image->Flags = 0;
  Image->Width = 50;
  Image->Height = 60;
  Bitmap = (EFI_GRAPHICS_OUTPUT_BLT_PIXEL *) AllocateZeroPool (Image->Width * Image->Height * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));
  if ( Bitmap == NULL ) {
	gtBS->FreePool (Blt);
    gtBS->FreePool (Image);
	return EFI_UNSUPPORTED;
  }
  Image->Bitmap = Bitmap;

  PackageList = (EFI_HII_PACKAGE_LIST_HEADER*) mPackageList1;
  //
  // Add the PackageList to HII database
  //
  Status = HIIDatabase->NewPackageList (
                          HIIDatabase,
                          PackageList,
                          NULL,
                          &Handle
                          );
  if ( EFI_ERROR(Status) ) {
  	gtBS->FreePool (Blt);
    gtBS->FreePool (Image->Bitmap);
    gtBS->FreePool (Image);
    return Status;
  }

  //
  // Call NewImage to get the ImageId
  //
  Status = HIIImage->NewImage (
                       HIIImage,
                       Handle,
                       &ImageId,
                       Image
                       );
  if ( EFI_ERROR(Status) ) {
  	gtBS->FreePool (Blt);
    gtBS->FreePool (Image->Bitmap);
    gtBS->FreePool (Image);
    TempStatus = HIIDatabase->RemovePackageList (
                                HIIDatabase,
                                Handle
                                );
	if ( EFI_ERROR(TempStatus) ) {
      return TempStatus;
	}                                
    return Status;
  }

  //
  // Call DrawImageId with with valid parameter
  //
  Status = HIIImage->DrawImageId(
                       HIIImage,
                       Flag,
                       Handle,
                       ImageId,
                       &Blt,
                       BltX,
                       BltY
                       );
  
  if ( EFI_SUCCESS != Status && EFI_OUT_OF_RESOURCES != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gHIIImageBBTestFunctionAssertionGuid009,
                 L"HII_IMAGE_PROTOCOL.DrawImageId - DrawImageId() returns EFI_SUCCESS with valid parameter.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  gtBS->FreePool (Blt);
  gtBS->FreePool (Image->Bitmap);
  gtBS->FreePool (Image);

  Status = HIIDatabase->RemovePackageList (
                          HIIDatabase,
                          Handle
                          );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }  

  return EFI_SUCCESS;
}
